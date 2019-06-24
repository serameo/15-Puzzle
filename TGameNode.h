
///////////////////////////////////////////////////////////////////////////////
// TGameNode.h
// Author: Seree Rakwong
// Date: 18-Aug-2013
//
#ifndef TGAMENODE_H
#define TGAMENODE_H

#include <windows.h>
#include <vector>
#include <string>
#include "TThread.h"


class TGameController; // declare below
////////////////////////////////////////////////////////////////////////////
// game app

enum TGameNodeType
{
    GameNodeTypeNode,
    GameNodeTypeLayer,
    GameNodeTypeScene
};

////////////////////////////////////////////////////////////////////////////

class TGameNode : public TLockableObject
{
    // attributes
public:
    unsigned long m_nID;
    int m_zOrder;
    TGameNodeType m_nodeType;
    RECT m_rect;
    bool m_bVisible;
    TGameNode *m_pParent;
    // TLockableObject m_lock;

    // methods
public:
    TGameNode();

    bool IsVisible()
    {
        return m_bVisible;
    }

    void SetVisible(bool fVisible = TRUE)
    {
        m_bVisible = fVisible;
    }

    TGameNode *GetParent()
    {
        return m_pParent;
    }

    TGameNode *SetParent(TGameNode *pParent)
    {
        if (m_pParent == pParent) return pParent;
        TGameNode *pCurParent = m_pParent;
        m_pParent = pParent;
        return pCurParent;
    }

public:
    static bool ZOrderSort(TGameNode *pNode1, TGameNode *pNode2);

public:
    virtual void Draw(HDC hdc) = 0;

    virtual TGameNode *HitTest(int x, int y)
    {
        POINT pt = {x, y};
        if (PtInRect(&m_rect, pt))
        {
            OnClicked(this, m_nID);
            return this;
        }
        return NULL;
    }

    TGameController *GetController();

    virtual void Update()
    {
    }

protected:

    virtual void OnClicked(TGameNode *pSender, unsigned long ID)
    {
    }

};
typedef std::vector<TGameNode*> TGameNodes;
typedef std::vector<TGameNode*>::iterator TGameNodesIterator;

////////////////////////////////////////////////////////////////////////////

class TGameMovableNode : public TGameNode
{
public:
    virtual void Move() = 0;
};

////////////////////////////////////////////////////////////////////////////

class TGameLabel : public TGameNode
{
protected:
#ifdef UNICODE
    std::vector<std::wstring> m_lines;
#else
    std::vector<std::string> m_lines;
#endif
    COLORREF m_bkColor;
    COLORREF m_textColor;
    HFONT m_hFont;
    HBRUSH m_hbr;
    HPEN m_hpen;

public:
    TGameLabel(LPCTSTR pText, RECT *prc);
    virtual ~TGameLabel();

    virtual void Draw(HDC hdc);

    void SetText(LPCTSTR pText)
    {
        //m_lock.Enter();
        Enter();
        m_lines.clear();
        m_lines.push_back(pText);
        //m_lock.Leave();
        Leave();
    }

    int GetText(LPTSTR pText, int cchMax)
    {
        if (pText == NULL) return -1;

        *pText = NULL;
        //m_lock.Enter();
        Enter();
        int len = (int) m_lines[0].length();
        if (cchMax < len)
        {
            //m_lock.Leave();
            Leave();
            return len;
        }
        lstrcpy(pText, m_lines[0].c_str());
        //m_lock.Leave();
        Leave();

        return len;
    }
};

///////////////////////////////////////////////////////////

class TTimerLabel : public TGameLabel
{
public:
    TCounterTimer m_counterTimer;

public:
    TTimerLabel(RECT *prc);
    virtual ~TTimerLabel();

    virtual void Update();

    void Reset();

};


////////////////////////////////////////////////////////////////////////////

class TGameBitmapLabel : public TGameLabel
{
};

////////////////////////////////////////////////////////////////////////////

class TGameButton : public TGameLabel
{
public:
    TGameButton(LPCTSTR pText, RECT *prc);
};

////////////////////////////////////////////////////////////////////////////

class TGameEdit : public TGameNode
{
};

////////////////////////////////////////////////////////////////////////////

class TGameLayer : public TGameNode
{
protected:
    TGameNodes *m_pNodes;

public:
    TGameLayer();
    virtual ~TGameLayer();

    void AddNode(TGameNode *pNode);
    void DeleteNode(TGameNode *pNode);
    TGameNode *GetNodeAt(int i);

public:
    virtual void Draw(HDC);
    virtual void SortNodes();

    virtual void Update();

    virtual TGameNode *HitTest(int x, int y);

    TGameController *GetController();

};

typedef std::vector<TGameLayer*> TGameLayers;
typedef std::vector<TGameLayer*>::iterator TGameLayersIterator;

////////////////////////////////////////////////////////////////////////////

class TGameScene : public TGameLayer
{
protected:
    TGameLayers *m_pLayers;
    TGameController *m_pController;

public:
    TGameScene();
    virtual ~TGameScene();

    void AddLayer(TGameLayer *pLayer);
    void DeleteLayer(TGameLayer *pLayer);
    TGameLayer *GetLayerAt(int i);

    TGameController *GetController()
    {
        return m_pController;
    }
    TGameController *SetController(TGameController *pController);

public:
    virtual void Draw(HDC);
    virtual void SortLayers();

    virtual void Update();

    virtual TGameNode *HitTest(int x, int y);
};
typedef std::vector<TGameScene*> TGameScenes;
typedef std::vector<TGameScene*>::iterator TGameScenesIterator;

////////////////////////////////////////////////////////////////////////////
// game app
class TGameView; // declare in "TGameApp.h", it is a derived TWindow class

class TGameController
{
    friend class TGameView;

protected:
    TGameView *m_pView;
    TGameScene *m_pScene;

public:

    TGameController(TGameView *pView)
    : m_pView(pView),
    m_pScene(NULL)
    {
    }

    TGameView *SetView(TGameView *pView)
    {
        TGameView *pCurView = m_pView;
        m_pView = pView;
        return pCurView;
    }

    TGameView *GetView()
    {
        return m_pView;
    }

    TGameScene *SetScene(TGameScene *pScene)
    {
        TGameScene *pCurScene = m_pScene;
        m_pScene = pScene;
        return pCurScene;
    }

    TGameScene *GetScene()
    {
        return m_pScene;
    }

protected:

    virtual void OnClicked(TGameNode *pSender, unsigned long nID)
    {
    }

protected: // mapping messages from TGameView
    // mouse messages

    virtual void OnLButtonDown(int x, int y, UINT flags)
    {
    }

    virtual void OnLButtonUp(int x, int y, UINT flags)
    {
    }

    virtual void OnLButtonDblClk(int x, int y, UINT flags)
    {
    }

    virtual void OnRButtonDown(int x, int y, UINT flags)
    {
    }

    virtual void OnRButtonUp(int x, int y, UINT flags)
    {
    }

    virtual void OnRButtonDblClk(int x, int y, UINT flags)
    {
    }

    virtual void OnMouseMove(int x, int y, UINT flags)
    {
    }
    // some keyboard messages

    virtual void OnChar(TCHAR ch, int nCount, int nScanCode,
            BOOL extendedKey, BOOL contextCode,
            BOOL prevKeyState, BOOL transitionState)
    {
    }

    virtual void OnKeyDown(UINT vkCode, int nCount, int nScanCode,
            BOOL extendedKey, BOOL contextCode,
            BOOL prevKeyState, BOOL transitionState)
    {
    }

    virtual void OnKeyUp(UINT vkCode, int nCount, int nScanCode,
            BOOL extendedKey, BOOL contextCode,
            BOOL prevKeyState, BOOL transitionState)
    {
    }
};

////////////////////////////////////////////////////////////////////////////

class TGame
{
public:
    TGame();
    virtual ~TGame();

public:
    virtual void GameLoop();
    virtual void BeginScene();

    virtual void EndScene()
    {
    }

    virtual BOOL IsRunning() = 0;
    virtual BOOL IsGameOver() = 0;
    virtual BOOL IsGameStart() = 0;
    virtual BOOL IsGamePause() = 0;

protected:
    TGameScene *m_pActiveScene;
    TGameScenes *m_pScenes;

public:
    void AddScene(TGameScene *pScene);
    void DeleteScene(TGameScene *pScene);

    TGameScene *GetActiveScene()
    {
        return m_pActiveScene;
    }
    TGameScene *SetActiveScene(TGameScene *pScene);

    void RenderScene();

};


#endif //TGAMENODE_H
