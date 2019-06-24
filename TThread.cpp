
///////////////////////////////////////////////////////////////////////////////
// TThread.cpp
// Author: Seree Rakwong
// Date: 21-Aug-2013
//
#include "TThread.h"

////////////////////////////////////////////////////////////////////////////

DWORD WINAPI TThread::StaticThreadProc(void *argv)
{
    TThread *pThread = (TThread*) argv;
    if (pThread)
        return pThread->Run();
    return 0;
}

TThread::TThread()
: m_hThread(NULL),
m_dwID(0)
{
}

TThread::~TThread()
{
}

BOOL TThread::Create()
{
    if (m_hThread) return TRUE;
    m_hThread = CreateThread(NULL, 0,
            (LPTHREAD_START_ROUTINE) TThread::StaticThreadProc,
            this, CREATE_SUSPENDED, &m_dwID);

    return (m_hThread != NULL);
}

void TThread::Destroy()
{
    CloseHandle(m_hThread);
    m_dwID = 0;
}

DWORD TThread::Suspend()
{
    return SuspendThread(m_hThread);
}

DWORD TThread::Resume()
{
    return ResumeThread(m_hThread);
}


////////////////////////////////////////////////////////////////////////////

TTimer::TTimer(DWORD msTick)
: m_msTick(msTick),
m_pfnCallback(NULL),
m_pCallbackData(NULL),
m_eTimerState(TimerStateStop),
m_bIsRunning(TRUE)
{
}

TTimer::~TTimer()
{
}

int TTimer::Run()
{
    //struct timeval tv = { 0, m_msTick };
    while (m_bIsRunning)
    {
        //select(0, 0, 0, 0, &tv);
        WaitForSingleObject(m_hThread, m_msTick);

        switch (m_eTimerState)
        {
            case TimerStateStop:
                m_bIsRunning = FALSE;
                break;
            case TimerStatePause:
                // do nothing
                break;
            case TimerStateStart:
                if (m_pfnCallback)
                    m_pfnCallback(m_pCallbackData);
                break;
        }
    }
    return 0;
}

void TTimer::SetTimerCallback(LPTIMERCALLBACK pfn, void *argv)
{
    m_pfnCallback = pfn;
    m_pCallbackData = argv;
}

void TTimer::Start()
{
    m_eTimerState = TimerStateStart;
    m_bIsRunning = TRUE;
    Create();
    Resume();
}

void TTimer::Stop()
{
    m_eTimerState = TimerStateStop;
    Suspend();
    Destroy();
}

void TTimer::Pause()
{
    m_eTimerState = TimerStatePause;
    Suspend();
}


////////////////////////////////////////////////////////////////////////////

TLockableObject::TLockableObject()
{
    //InitializeCriticalSectionEx(&m_cs, 0x400, 0);
    InitializeCriticalSection(&m_cs);
}

TLockableObject::~TLockableObject()
{
    DeleteCriticalSection(&m_cs);
}

void TLockableObject::Enter()
{
    EnterCriticalSection(&m_cs);
}

void TLockableObject::Leave()
{
    LeaveCriticalSection(&m_cs);
}

////////////////////////////////////////////////////////////////////////////

void TCounterTimer::StaticCounterTimer(void *argv)
{
    TCounterTimer *pTimer = (TCounterTimer*) argv;
    pTimer->IncreaseCount();
}

TCounterTimer::TCounterTimer()
: TTimer(1000),
m_dwCounter(0)
{
    SetTimerCallback(TCounterTimer::StaticCounterTimer, this);
}

TCounterTimer::~TCounterTimer()
{
}

/*
int TCounterTimer::GetText(LPTSTR pText, int cchMax)
{
return 0;
}
 */
int TCounterTimer::GetTextByClock(LPTSTR pText, int cchMax)
{
    m_lock.Enter();
    int hour = (int) (m_dwCounter / 3600);
    int min = (int) ((m_dwCounter - hour * 3600) / 60);
    int sec = m_dwCounter - hour * 3600 - min * 60;
    m_lock.Leave();

    TCHAR szText[16];
    wsprintf(szText, TEXT("%02d:%02d:%02d"), hour, min, sec);
    int len = (int) lstrlen(szText);

    *pText = NULL;
    if (cchMax < len) return len;
    lstrcpy(pText, szText);
    return len;
}

void TCounterTimer::IncreaseCount()
{
    m_lock.Enter();
    m_dwCounter++;
    m_lock.Leave();
}

void TCounterTimer::ResetCount()
{
    m_lock.Enter();
    m_dwCounter = 0;
    m_lock.Leave();
}

DWORD TCounterTimer::GetCount()
{
    m_lock.Enter();
    DWORD dw = m_dwCounter;
    m_lock.Leave();

    return dw;
}

