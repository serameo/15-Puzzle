
///////////////////////////////////////////////////////////////////////////////
// TGameNode.cpp
// Author: Seree Rakwong
// Date: 18-Aug-2013
//
//#include "TGameNode.h"
#include "TGameApp.h"
#include <algorithm>

using namespace std;

unsigned long g_ID = 0;

////////////////////////////////////////////////////////////////////////////

TGameNode::TGameNode()
: m_zOrder(0),
m_nodeType(GameNodeTypeNode),
m_bVisible(true),
m_pParent(NULL)
{
    m_rect.left = m_rect.top = m_rect.right = m_rect.bottom = 0;
    g_ID++;
    m_nID = g_ID;
}

bool TGameNode::ZOrderSort(TGameNode *pNode1, TGameNode *pNode2)
{
    return (pNode1->m_zOrder < pNode2->m_zOrder);
}

TGameController *TGameNode::GetController()
{
    TGameLayer *pLayer = (TGameLayer*) GetParent();
    if (pLayer)
        return pLayer->GetController();
    return NULL;
}

////////////////////////////////////////////////////////////////////////////

TGameLayer::TGameLayer()
// : m_nodeType(GameNodeTypeLayer)
{
    m_pNodes = new TGameNodes();
    m_nodeType = GameNodeTypeLayer;
}

TGameLayer::~TGameLayer()
{
    if (m_pNodes)
        delete m_pNodes;
}

TGameNode *TGameLayer::HitTest(int x, int y)
{
    TGameNodesIterator it = m_pNodes->begin();
    for (; it != m_pNodes->end(); ++it)
    {
        TGameNode *pNode = (*it)->HitTest(x, y);
        if (pNode != NULL)
            return pNode;
    }
    return NULL;
}

void TGameLayer::Draw(HDC hdc)
{
    TGameNodesIterator it = m_pNodes->begin();
    for (; it != m_pNodes->end(); ++it)
    {
        if ((*it)->IsVisible())
            (*it)->Draw(hdc);
    }
}

TGameNode *TGameLayer::GetNodeAt(int i)
{
    if (i < 0 || i >= (int) m_pNodes->size())
        return NULL;

    return (*m_pNodes)[i];
}

void TGameLayer::AddNode(TGameNode *pNode)
{
    pNode->SetParent(this);
    m_pNodes->push_back(pNode);
}

void TGameLayer::DeleteNode(TGameNode *pNode)
{
    TGameNodesIterator it = find(m_pNodes->begin(), m_pNodes->end(), pNode);
    if (it == m_pNodes->end()) return;

    m_pNodes->erase(it);
}

void TGameLayer::SortNodes()
{
    std::sort(m_pNodes->begin(), m_pNodes->end(), TGameNode::ZOrderSort);
}

// to implement its objects update

void TGameLayer::Update()
{
    TGameNodesIterator it = m_pNodes->begin();
    for (; it != m_pNodes->end(); ++it)
    {
        (*it)->Update();
    }
}

TGameController *TGameLayer::GetController()
{
    TGameScene *pScene = (TGameScene*) GetParent();
    if (pScene)
        return pScene->GetController();
    return NULL;
}

////////////////////////////////////////////////////////////////////////////

TGameScene::TGameScene()
: m_pController(NULL)

{
    m_pLayers = new TGameLayers();
    m_nodeType = GameNodeTypeScene;
}

TGameScene::~TGameScene()
{
    if (m_pLayers)
        delete m_pLayers;
}

TGameNode *TGameScene::HitTest(int x, int y)
{
    TGameNode *pNode = NULL;
    TGameLayersIterator it = m_pLayers->begin();
    for (; it != m_pLayers->end(); ++it)
    {
        pNode = (*it)->HitTest(x, y);
        if (pNode != NULL)
            return pNode;
    }
    TGameNodesIterator it2 = m_pNodes->begin();
    for (; it2 != m_pNodes->end(); ++it2)
    {
        pNode = (*it2)->HitTest(x, y);
        if (pNode != NULL)
            return pNode;
    }
    return pNode;
}

void TGameScene::Draw(HDC hdc)
{
    TGameLayersIterator it = m_pLayers->begin();
    for (; it != m_pLayers->end(); ++it)
    {
        if ((*it)->IsVisible())
            (*it)->Draw(hdc);
    }
    TGameNodesIterator it2 = m_pNodes->begin();
    for (; it2 != m_pNodes->end(); ++it2)
    {
        if ((*it2)->IsVisible())
            (*it2)->Draw(hdc);
    }
}

TGameLayer *TGameScene::GetLayerAt(int i)
{
    if (i < 0 || i >= (int) m_pLayers->size())
        return NULL;

    return (*m_pLayers)[i];
}

void TGameScene::AddLayer(TGameLayer *pLayer)
{
    pLayer->SetParent(this);
    m_pLayers->push_back(pLayer);
}

void TGameScene::DeleteLayer(TGameLayer *pLayer)
{
    TGameLayersIterator it = find(m_pLayers->begin(), m_pLayers->end(), pLayer);
    if (it == m_pLayers->end()) return;

    m_pLayers->erase(it);
}

void TGameScene::SortLayers()
{
    std::sort(m_pLayers->begin(), m_pLayers->end(), TGameNode::ZOrderSort);
}

TGameController *TGameScene::SetController(TGameController *pController)
{
    TGameController *pCurCtl = m_pController;
    m_pController = pController;
    return pCurCtl;
}


// to implement its objects update

void TGameScene::Update()
{
    TGameLayersIterator it = m_pLayers->begin();
    for (; it != m_pLayers->end(); ++it)
    {
        (*it)->Update();
    }
    TGameNodesIterator it2 = m_pNodes->begin();
    for (; it2 != m_pNodes->end(); ++it2)
    {
        (*it2)->Update();
    }
}

////////////////////////////////////////////////////////////////////////////

TGame::TGame()
: m_pActiveScene(NULL)
{
    m_pScenes = new TGameScenes();
}

TGame::~TGame()
{
    if (m_pScenes)
        delete m_pScenes;
}

void TGame::AddScene(TGameScene *pScene)
{
    m_pScenes->push_back(pScene);
}

void TGame::DeleteScene(TGameScene *pScene)
{
    TGameScenesIterator it = find(m_pScenes->begin(), m_pScenes->end(), pScene);
    if (it == m_pScenes->end()) return;

    m_pScenes->erase(it);
}

TGameScene * TGame::SetActiveScene(TGameScene *pScene)
{
    if (pScene == NULL) return NULL;

    TGameScenesIterator it = find(m_pScenes->begin(), m_pScenes->end(), pScene);
    if (it == m_pScenes->end()) return NULL;

    if (pScene == m_pActiveScene) return pScene;

    TGameScene *pCurScene = m_pActiveScene;
    TGameController *pCtl = NULL;
    TGameView *pView = NULL;
    if (pCurScene)
    {
        TGameController *pCtl = pCurScene->GetController();
        TGameView *pView = pCtl->GetView();
        pView->ShowWindow(SW_HIDE);
    }

    m_pActiveScene = pScene;
    pCtl = pScene->GetController();
    pView = pCtl->GetView();
    pView->ShowWindow(SW_SHOW);

    return pCurScene;
}

void TGame::RenderScene()
{
    TGameScene *pScene = GetActiveScene();
    if (!pScene) return;

    TGameController *pCtl = pScene->GetController();
    TGameView *pView = pCtl->GetView();

    // use double buffering technique to reduce flickering
    HWND hwndView = pView->GetHWND();
    RECT rc;
    GetClientRect(hwndView, &rc);

    HDC hdc = GetDC(hwndView);
    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hbmp = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
    HBITMAP hbmpOld = (HBITMAP) SelectObject(hdcMem, hbmp);

    pScene->Draw(hdcMem);
    BitBlt(hdc, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, SRCCOPY);

    SelectObject(hdcMem, hbmpOld);
    DeleteObject(hbmp);
    DeleteDC(hdcMem);

    ReleaseDC(hwndView, hdc);
}

void TGame::GameLoop()
{
    // this loop should handle the idle time
    BeginScene(); // prepare the active scene
    RenderScene(); // draw everthing need
    EndScene(); // end of drawing
}

void TGame::BeginScene()
{
    if (m_pActiveScene)
        m_pActiveScene->Update();
}

////////////////////////////////////////////////////////////////////////////
// mouse messages

void TGameView::OnLButtonDown(int x, int y, UINT flags)
{
    if (m_pController)
        m_pController->OnLButtonDown(x, y, flags);
}

void TGameView::OnLButtonUp(int x, int y, UINT flags)
{
    if (m_pController)
        m_pController->OnLButtonUp(x, y, flags);
}

void TGameView::OnLButtonDblClk(int x, int y, UINT flags)
{
    if (m_pController)
        m_pController->OnLButtonDblClk(x, y, flags);
}

void TGameView::OnRButtonDown(int x, int y, UINT flags)
{
    if (m_pController)
        m_pController->OnRButtonDown(x, y, flags);
}

void TGameView::OnRButtonUp(int x, int y, UINT flags)
{
    if (m_pController)
        m_pController->OnRButtonUp(x, y, flags);
}

void TGameView::OnRButtonDblClk(int x, int y, UINT flags)
{
    if (m_pController)
        m_pController->OnRButtonDblClk(x, y, flags);
}

void TGameView::OnMouseMove(int x, int y, UINT flags)
{
    if (m_pController)
        m_pController->OnMouseMove(x, y, flags);
}


// some keyboard messages

void TGameView::OnChar(TCHAR ch, int nCount, int nScanCode,
        BOOL extendedKey, BOOL contextCode,
        BOOL prevKeyState, BOOL transitionState)
{
    if (m_pController)
        m_pController->OnChar(ch, nCount, nScanCode,
            extendedKey, contextCode,
            prevKeyState, transitionState);
}

void TGameView::OnKeyDown(UINT vkCode, int nCount, int nScanCode,
        BOOL extendedKey, BOOL contextCode,
        BOOL prevKeyState, BOOL transitionState)
{
    if (m_pController)
        m_pController->OnKeyDown(vkCode, nCount, nScanCode,
            extendedKey, contextCode,
            prevKeyState, transitionState);
}

void TGameView::OnKeyUp(UINT vkCode, int nCount, int nScanCode,
        BOOL extendedKey, BOOL contextCode,
        BOOL prevKeyState, BOOL transitionState)
{
    if (m_pController)
        m_pController->OnKeyUp(vkCode, nCount, nScanCode,
            extendedKey, contextCode,
            prevKeyState, transitionState);
}



////////////////////////////////////////////////////////////////////////////

TGameLabel::TGameLabel(LPCTSTR pText, RECT *prc)
: m_bkColor(RGB(200, 200, 255)),
m_textColor(RGB(0, 0, 0))
{
    //nHeight = -MulDiv(PointSize, GetDeviceCaps(hDC, LOGPIXELSY), 72);
    m_hFont = CreateFont(0, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, THAI_CHARSET,
            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
            TEXT("MS Comics"));

    m_hbr = CreateHatchBrush(HS_BDIAGONAL, m_bkColor);
    m_hpen = CreatePen(PS_SOLID, 1, m_textColor);

    m_rect = *prc;

    if (pText)
        m_lines.push_back(pText);
    else
        m_lines.push_back(TEXT(""));
}

TGameLabel::~TGameLabel()
{
    DeleteObject(m_hFont);
    DeleteObject(m_hbr);
    DeleteObject(m_hFont);
}

void TGameLabel::Draw(HDC hdc)
{
    FillRect(hdc, &m_rect, m_hbr);

    int mode = SetBkMode(hdc, TRANSPARENT);
    HPEN hpen = (HPEN) SelectObject(hdc, m_hpen);
    HFONT hFont = (HFONT) SelectObject(hdc, m_hFont);

    //m_lock.Enter();
    LPCTSTR pText = m_lines[0].c_str();
    DrawText(hdc, pText, lstrlen(pText), &m_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    //m_lock.Leave();

    SelectObject(hdc, hpen);
    SelectObject(hdc, hFont);
    SetBkMode(hdc, mode);
}
////////////////////////////////////////////////////////////////////////////

TTimerLabel::TTimerLabel(RECT *prc)
: TGameLabel(TEXT("00:00:00"), prc)
{
    m_counterTimer.Start();
}

TTimerLabel::~TTimerLabel()
{
    m_counterTimer.Stop();
}

void TTimerLabel::Update()
{
    TCHAR szText[32];
    m_counterTimer.GetTextByClock(szText, 32);
    SetText(szText);
}

void TTimerLabel::Reset()
{
    m_counterTimer.ResetCount();
}

////////////////////////////////////////////////////////////////////////////

TGameButton::TGameButton(LPCTSTR pText, RECT *prc)
: TGameLabel(pText, prc)
{
}

