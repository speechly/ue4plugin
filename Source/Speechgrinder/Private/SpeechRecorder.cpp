#include "SpeechRecorder.h"

namespace {
	static const int kNumFramesDesired = 1024;
};

FSpeechRecorder::FSpeechRecorder()
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
		AudioCapture.GetDefaultCaptureDeviceInfo(OutInfo);
		generateFilter();
		FAudioCaptureStreamParam StreamParam;
		StreamParam.Callback = this;
		StreamParam.NumFramesDesired = kNumFramesDesired;
		verifyf(AudioCapture.OpenDefaultCaptureStream(StreamParam), TEXT("Could not open capture stream"));
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

void FSpeechRecorder::OnAudioCapture(float* AudioData, int32 NumFrames, int32 NumChannels, double StreamTime, bool bOverflow)
{
	FScopeLock Lock(&CriticalSection);
	if (!bIsCapturing)
	{
		return;
	}

	// Pick the first channel
	for (int32 i = 0; i < NumFrames; ++i)
	{
		Buffer.Add(AudioData[i * NumChannels]);
	}

	int32 OutputLength = ceilf((Buffer.Num() - Filter.Num()) / SampleRatio);
	Output.Empty(kNumFramesDesired);

	for (int32 i = 0; i < OutputLength; ++i)
	{
		Output.Add(0.0f);
		int32 Offset = roundf(SampleRatio * i);
		for (int32 j = 0; j < Filter.Num(); ++j)
		{
			Output[i] += Buffer[Offset + j] * Filter[j];
		}
	}

	int32 RemainingOffset = roundf(SampleRatio * OutputLength);
	if (RemainingOffset < NumFrames)
	{
		Buffer.Empty(NumFrames);
		for (int32 i = RemainingOffset; i < NumFrames; ++i)
		{
			float Frame = 0.0f;
			for (int32 channel = 0; channel < NumChannels; ++channel)
			{
				Frame += AudioData[i * (channel + 1)];
			}
			Buffer.Add(Frame / NumChannels);
		}
	}
	else
	{
		Buffer.Empty(kNumFramesDesired);
	}

	verifyf(Callback, TEXT("Audio callback not defined"));
	Callback->OnSpeechAudio(Output.GetData(), OutputLength);
}

void FSpeechRecorder::generateFilter()
{
	int32 SampleRate = OutInfo.PreferredSampleRate;
	int32 Cutoff = kSampleRate;
	SampleRatio = static_cast<float>(SampleRate) / Cutoff;
	int32 FilterLength = 23;
	Filter.Empty(FilterLength);
	auto Sinc = [](float x) {
		if (x == 0.0f)
		{
			return 1.0f;
		}
		float PIx = PI * x;
		return sin(PIx) / PIx;
	};
	float Sum = 0;
	for (int32 i = 0; i < FilterLength; ++i)
	{
		float x = Sinc(Cutoff * 2.0f / SampleRate * (i - (FilterLength - 1) / 2.0f));
		Filter.Add(x);
		Sum += x;
	}
	for (int32 i = 0; i < Filter.Num(); ++i)
	{
		Filter[i] /= Sum;
	}
}
