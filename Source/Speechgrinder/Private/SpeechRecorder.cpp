#include "SpeechRecorder.h"

#include "GenericPlatformMath.h"

FSpeechRecorder::FSpeechRecorder(int NumFramesDesired, int SampleRate)
	: NumFramesDesired{NumFramesDesired},
	  SampleRate{SampleRate}
{
}

FSpeechRecorder::~FSpeechRecorder()
{
	AudioCapture.AbortStream();
	AudioCapture.CloseStream();
}

void FSpeechRecorder::Start()
{
	FScopeLock Lock(&CriticalSection);
	if (!AudioCapture.IsStreamOpen())
	{
		AudioCapture.GetCaptureDeviceInfo(OutInfo, INDEX_NONE);
		SampleRatio = static_cast<float>(OutInfo.PreferredSampleRate) / SampleRate;
		generateFilter();

		FAudioCaptureDeviceParams DeviceParams;
		DeviceParams.bUseHardwareAEC = true;
		DeviceParams.DeviceIndex = INDEX_NONE;
		FOnCaptureFunction OnCaptureFunction = [this](const float* InAudio, int32 NumFrames, int32 NumChannels, double StreamTime, bool bOverFlow) {
			return this->OnAudioCapture(InAudio, NumFrames, NumChannels, StreamTime, bOverFlow);
		};
		verifyf(AudioCapture.OpenCaptureStream(DeviceParams, OnCaptureFunction, NumFramesDesired), TEXT("Could not open capture stream"));

		AudioCapture.StartStream();
	}
	verifyf(AudioCapture.IsStreamOpen(), TEXT("Stream was not opened"));
	verifyf(AudioCapture.IsCapturing(), TEXT("Stream is not capturing"));
	bIsCapturing = true;
}

void FSpeechRecorder::Stop()
{
	FScopeLock Lock(&CriticalSection);
	bIsCapturing = false;
	Buffer.Empty();
}

void FSpeechRecorder::OnAudioCapture(const float* InAudio, int32 NumFrames, int32 NumChannels, double StreamTime, bool bOverflow)
{
	FScopeLock Lock(&CriticalSection);
	if (!bIsCapturing)
	{
		return;
	}

	if (bOverflow)
	{
		UE_LOG(LogSG, Warning, TEXT("Audio buffer overflow"));
	}

	// Pick the first channel
	for (int32 i = 0; i < NumFrames; ++i)
	{
		Buffer.Add(InAudio[i * NumChannels]);
	}

	int32 OutputLength = FGenericPlatformMath::CeilToInt((Buffer.Num() - Filter.Num()) / SampleRatio);
	Output.Empty(NumFramesDesired);

	for (int32 i = 0; i < OutputLength; ++i)
	{
		Output.Add(0.0f);
		int32 Offset = FGenericPlatformMath::RoundToInt(SampleRatio * i);
		for (int32 j = 0; j < Filter.Num(); ++j)
		{
			Output[i] += Buffer[Offset + j] * Filter[j];
		}
	}

	int32 RemainingOffset = FGenericPlatformMath::RoundToInt(SampleRatio * OutputLength);
	if (RemainingOffset < Buffer.Num())
	{
		// Move left over buffer to be the start of the next round
		for (int32 i = RemainingOffset, j = 0; i < Buffer.Num(); ++i, ++j)
		{
			Buffer[j] = Buffer[i];
		}
		Buffer.SetNum(Buffer.Num() - RemainingOffset);
	}
	else
	{
		Buffer.Empty(NumFramesDesired);
	}

	verifyf(Callback, TEXT("Audio callback not defined"));
	Callback->OnSpeechAudio(Output.GetData(), OutputLength);
}

void FSpeechRecorder::generateFilter()
{
	int32 PreferredSampleRate = OutInfo.PreferredSampleRate;
	int32 FilterLength = 23;
	Filter.Empty(FilterLength);
	auto Sinc = [](float x) {
		if (x == 0.0f)
		{
			return 1.0f;
		}
		float PIx = PI * x;
		return FGenericPlatformMath::Sin(PIx) / PIx;
	};
	float Sum = 0;
	for (int32 i = 0; i < FilterLength; ++i)
	{
		float x = Sinc((static_cast<float>(SampleRate) / PreferredSampleRate) * (i - (FilterLength - 1) / 2.0f));
		Filter.Add(x);
		Sum += x;
	}
	for (int32 i = 0; i < Filter.Num(); ++i)
	{
		Filter[i] /= Sum;
	}
}
