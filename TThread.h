///////////////////////////////////////////////////////////////////////////////
// TThread.h
// Author: Seree Rakwong
// Date: 21-Aug-2013
//
#ifndef TTHREAD_H
#define TTHREAD_H

#include <windows.h>

////////////////////////////////////////////////////////////////////////////

class TThread
{
protected:
    HANDLE m_hThread;
    DWORD m_dwID;

public:
    static DWORD WINAPI StaticThreadProc(void *);

public:
    TThread();
    virtual ~TThread();

    BOOL Create();
    void Destroy();
    DWORD Suspend();
    DWORD Resume();

    virtual int Run() = 0;
};

////////////////////////////////////////////////////////////////////////////

enum TTimerState
{
    TimerStateStart,
    TimerStateStop,
    TimerStatePause
};

typedef void (*LPTIMERCALLBACK)(void *);

class TTimer : public TThread
{
protected:
    DWORD m_msTick;
    LPTIMERCALLBACK m_pfnCallback;
    void *m_pCallbackData;
    BOOL m_bIsRunning;
    int m_eTimerState;

public:
    TTimer(DWORD msTick);
    virtual ~TTimer();

    virtual int Run();

    void SetTimerCallback(LPTIMERCALLBACK pfn, void *argv);

    void Start();
    void Stop();
    void Pause();
};


////////////////////////////////////////////////////////////////////////////

class TLockableObject
{
protected:
    CRITICAL_SECTION m_cs;

public:
    TLockableObject();
    virtual ~TLockableObject();

    void Enter();
    void Leave();
};


////////////////////////////////////////////////////////////////////////////

class TCounterTimer : public TTimer
{
protected:
    DWORD m_dwCounter;
    TLockableObject m_lock;

public:
    TCounterTimer();
    virtual ~TCounterTimer();

    static void StaticCounterTimer(void *);
    int GetTextByClock(LPTSTR pText, int cchMax);
    //int GetText(LPTSTR pText, int cchMax);

    void IncreaseCount();
    void ResetCount();
    DWORD GetCount();
};



#endif // TTHREAD_H
