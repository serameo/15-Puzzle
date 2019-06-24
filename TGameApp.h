
///////////////////////////////////////////////////////////////////////////////
// TGameApp.h
// Author: Seree Rakwong
// Date: 18-Aug-2013
//
#ifndef TGAMEAPP_H
#define TGAMEAPP_H

#include "TGenApp.h"
#include "TGameNode.h"

////////////////////////////////////////////////////////////////////////////
// game controller
// this class is an abstract class
//
class TGameController;

class TGameView : public TWindow<TGameView>
{
protected:
    TGameController *m_pController;

public:

    TGameController *GetController()
    {
        return m_pController;
    }

    TGameController *SetController(TGameController *pController)
    {
        if (m_pController == pController)
            return pController;

        TGameController *pCurCtl = m_pController;
        m_pController = pController;
        return pCurCtl;
    }

protected:
    // mouse messages
    virtual void OnLButtonDown(int x, int y, UINT flags);
    virtual void OnLButtonUp(int x, int y, UINT flags);
    virtual void OnLButtonDblClk(int x, int y, UINT flags);
    virtual void OnRButtonDown(int x, int y, UINT flags);
    virtual void OnRButtonUp(int x, int y, UINT flags);
    virtual void OnRButtonDblClk(int x, int y, UINT flags);
    virtual void OnMouseMove(int x, int y, UINT flags);
    // some keyboard messages
    virtual void OnChar(TCHAR ch, int nCount, int nScanCode,
            BOOL extendedKey, BOOL contextCode,
            BOOL prevKeyState, BOOL transitionState);
    virtual void OnKeyDown(UINT vkCode, int nCount, int nScanCode,
            BOOL extendedKey, BOOL contextCode,
            BOOL prevKeyState, BOOL transitionState);
    virtual void OnKeyUp(UINT vkCode, int nCount, int nScanCode,
            BOOL extendedKey, BOOL contextCode,
            BOOL prevKeyState, BOOL transitionState);

};


////////////////////////////////////////////////////////////////////////////
// game app

template<class TWnd>
class TGameApp : public TGenApp<TWnd>
{
protected:
    TGame *m_pGame;

public:

    TGameApp(HINSTANCE hinst, TWnd& wnd, TGame *pGame)
    : TGenApp<TWnd>(hinst, wnd),
    m_pGame(pGame)
    {
    }

protected:
    virtual void MainLoop();
};

template<class TWnd>
void TGameApp<TWnd>::MainLoop()
{
    if (!m_pGame)
        return;

    MSG msg;
    PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

    while (msg.message != WM_QUIT && m_pGame->IsRunning())
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // otherwise process the incoming message
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // No message to do
            m_pGame->GameLoop();
        }
    }
}


#endif //TGAMEAPP_H
