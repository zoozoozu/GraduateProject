#pragma once

const ULONG MAX_SAMPLE_COUNT = 50;

class CTimer
{
private:
	bool m_bHardwareHasPerformanceCounter;
	float m_fTimeScale;
	float m_fTimeElapsed;
	__int64 m_nCurrentTime;
	__int64 m_nLastTime;
	__int64 m_PerformanceFrequency;

	float m_fFrameTime[MAX_SAMPLE_COUNT];
	ULONG m_nSampleCount;

	unsigned long m_nCurrentFrameRate;
	unsigned long m_FramePerSecond;
	float m_fFPSTimeElapsed;

	HWND		m_hWnd{ nullptr };
	TCHAR		m_CaptionTitle[TITLE_MAX_LENGTH];
	int			m_TitleLength{ 0 };

public:
	CTimer();
	virtual ~CTimer();

	void Tick(float fLockFPS = 0.0f);
	unsigned long GetFrameRate(LPTSTR lpszString = NULL, int nCharacters = 0);
	float GetTimeElapsed();

	void SetUpdateCaptionHwnd(HWND hWnd);
};

