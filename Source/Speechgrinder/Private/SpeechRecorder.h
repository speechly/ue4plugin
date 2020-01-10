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

// Audio recorder with downsampling to 16000hz
class FSpeechRecorder
{
public:
	FSpeechRecorder(int NumFramesDesired, int SampleRate);
	virtual ~FSpeechRecorder();
	void Start();
	void Stop();
	void OnAudioCapture(const float* InAudio, int32 NumFrames, int32 NumChannels, double StreamTime, bool bOverflow);

	ISpeechAudioCallback* Callback;

private:
	void generateFilter();

	int NumFramesDesired;
	int SampleRate;
	TArray<float> Filter;
	float SampleRatio;
	TArray<float> Buffer;
	TArray<float> Output;
	bool bIsCapturing{ false };
	FAudioCapture AudioCapture;
	FCaptureDeviceInfo OutInfo;
	FCriticalSection CriticalSection;
};