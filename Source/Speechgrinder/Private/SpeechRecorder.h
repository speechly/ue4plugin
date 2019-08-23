#pragma once

#include "CoreMinimal.h"

#include "AudioCapture.h"

using namespace Audio;

class ISpeechAudioCallback
{
public:
	virtual void OnSpeechAudio(const float* Audio, const int32 AudioLength) = 0;
	virtual ~ISpeechAudioCallback() {}
};

// Audio recorder with downsampling to 8000hz
class FSpeechRecorder : public IAudioCaptureCallback
{
public:
	FSpeechRecorder();
	virtual ~FSpeechRecorder();
	void Start();
	void Stop();

	virtual void OnAudioCapture(float* AudioData, int32 NumFrames, int32 NumChannels, double StreamTime, bool bOverflow) override;
	ISpeechAudioCallback* Callback;

private:
	void generateFilter();

	TArray<float> Filter;
	float SampleRatio;
	TArray<float> Buffer;
	TArray<float> Output;
	bool bIsCapturing{ false };
	FAudioCapture AudioCapture;
	FCaptureDeviceInfo OutInfo;
	FCriticalSection CriticalSection;

};