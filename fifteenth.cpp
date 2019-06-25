///////////////////////////////////////////////////////////////////////////////
// fifteenth.cpp
// Author: Seree Rakwong
// Date: 18-Aug-2013
//

#include "TGameApp.h"
#include <time.h>

#define IDC_GAMEVIEW 100
#define MAX_PIECES 16
#define GAME_NAME TEXT("15-puzzle game")

///////////////////////////////////////////////////////////

struct TCellProperties
{
    int index;
    RECT rect;
};

///////////////////////////////////////////////////////////
// game map
#define MAX_MAPS (6)
int g_mapNumbers[MAX_MAPS][16] ={
    {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 0
    },
    {
        1, 2, 3, 4,
        8, 7, 6, 5,
        9, 10, 11, 12,
        0, 15, 14, 13
    },
    {
        1, 5, 9, 13,
        2, 6, 10, 14,
        3, 7, 11, 15,
        4, 8, 12, 0
    },
    {
        1, 8, 9, 0,
        2, 7, 10, 15,
        3, 6, 11, 14,
        4, 5, 12, 13
    },
    {
        1, 2, 3, 4,
        12, 13, 14, 5,
        11, 0, 15, 6,
        10, 9, 8, 7
    },
    {
        7, 11, 14, 0,
        4, 8, 12, 15,
        2, 5, 9, 13,
        1, 3, 6, 10
    },

};

int g_currentMap = 0;

class DigitTile : public TGameNode
{
public:
    COLORREF m_bkColor;
    COLORREF m_textColor;
    COLORREF m_emptyColor;
    int m_value;
    HBRUSH m_hbrBkColor;
    HPEN m_hpTextColor;
    HBRUSH m_hbrEmptyColor;
    int m_index;

public:

    DigitTile(int val, int ind)
    : m_value(val),
    m_index(ind),
    m_bkColor(RGB(255, 0, 255)),
    m_textColor(RGB(0, 0, 255)),
    m_emptyColor(RGB(128, 128, 128))
    {
        if (val <= 4) m_bkColor = RGB(255, 255, 128);
        else if (val <= 8) m_bkColor = RGB(255, 128, 255);
        else if (val <= 12) m_bkColor = RGB(200, 255, 255);
        else m_bkColor = RGB(128, 128, 255);

        m_hbrBkColor = CreateSolidBrush(m_bkColor);
        m_hpTextColor = CreatePen(PS_SOLID, 1, m_textColor);
        m_hbrEmptyColor = CreateSolidBrush(m_emptyColor);
    }

    virtual ~DigitTile()
    {
        DeleteObject(m_hbrBkColor);
        DeleteObject(m_hpTextColor);
        DeleteObject(m_hbrEmptyColor);
    }

    virtual void Draw(HDC hdc);
    virtual void Update();

};

void DigitTile::Draw(HDC hdc)
{

    HPEN hp = (HPEN) SelectObject(hdc, m_hpTextColor);
    int mode = SetBkMode(hdc, TRANSPARENT);

    FillRect(hdc, &m_rect, m_hbrBkColor);
    HBRUSH hbrOld = (HBRUSH) SelectObject(hdc, m_hbrBkColor);
    Rectangle(hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);

    TCHAR text[4];
    if (m_value != 0)
    {
        wsprintf(text, TEXT("%d"), m_value);
        DrawText(hdc, text, lstrlen(text), &m_rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    }
    else
    {
        FillRect(hdc, &m_rect, m_hbrEmptyColor);
        SelectObject(hdc, m_hbrEmptyColor);
        Rectangle(hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);

        wsprintf(text, TEXT("E"));
        DrawText(hdc, text, lstrlen(text), &m_rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    }

    SelectObject(hdc, hbrOld);
    SetBkMode(hdc, mode);
    SelectObject(hdc, hp);
}


///////////////////////////////////////////////////////////

class NewGameButton : public TGameButton
{
public:

    NewGameButton(LPCTSTR pText, RECT *prc)
    : TGameButton(pText, prc)
    {
    }

protected:
    virtual void OnClicked(TGameNode *pSender, unsigned long nID);
};

///////////////////////////////////////////////////////////
// GameView

class GameView : public TGameView
{
public:

    GameView()
    {
    }

    LPCTSTR GetClassName()
    {
        static TCHAR szClassName[] = TEXT("Game view class");
        return szClassName;
    }

protected:

    virtual BOOL RegisterWnd(HINSTANCE hinst)
    {
        WNDCLASS wc;
        wc.lpszClassName = GetClassName();
        wc.lpfnWndProc = GameView::StaticWndProc;
        wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
        wc.hInstance = hinst;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
        wc.lpszMenuName = NULL;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        return (BOOL) RegisterClass(&wc);
    }

public:
    int HitTest(int x, int y); // return cell
};

///////////////////////////////////////////////////////////

class MyController : public TGameController
{
    friend class DigitTile;

private:
    int m_aNumbers[MAX_PIECES];
    DWORD m_clicks;
    int m_aMap[16];


protected:
    virtual void OnLButtonDown(int x, int y, UINT flags);

public:

    MyController(TGameView *pView)
    : TGameController(pView),
    m_clicks(0)
    {

        for (int i = 0; i < MAX_PIECES; ++i)
        {
            m_aNumbers[i] = (i + 1) % 16;
        }

    }

    void SetMap(const int *pNumbers)
    {
        memcpy(m_aMap, pNumbers, sizeof (int)*16);
    }

    void Init()
    {
        for (int i = 0; i < MAX_PIECES; ++i)
        {
            m_aNumbers[i] = m_aMap[i];
        }
    }

    const int *GetTileArray()
    {
        return m_aNumbers;
    }

    void ShuffleTiles(int times = 10000)
    {
        Init();
        //
        srand((unsigned int) time(NULL));

        for (int i = 0; i < times; ++i)
        {
            int empty = GetEmptyTilePos();
            int moving_type = rand() % 2; // 0 - row, 1 - column
            int moving_dir = rand() % 2; // 0 - decrease, 1 - increase
            if (moving_type == 0)
            {
                // move rows
                if (moving_dir == 0)
                {
                    // move up
                    if (empty > 3)
                        SwapTiles(empty, empty - 4);
                    else
                        SlideTiles(empty, empty + 12, 10);
                }
                else
                {
                    // move down
                    if (empty < 12)
                        SwapTiles(empty, empty + 4);
                    else
                        SlideTiles(empty, empty - 12, 10);
                }
            }
            else
            {
                // move columns
                int empty_mod = empty % 4;
                if (moving_dir == 0)
                {
                    // move left
                    if (empty_mod > 0)
                        SwapTiles(empty, empty - 1);
                    else
                        SlideTiles(empty, empty + 3, 20);
                }
                else
                {
                    // move right
                    if (empty_mod < 3)
                        SwapTiles(empty, empty + 1);
                    else
                        SlideTiles(empty, empty - 3, 20);
                }
            }

        }

        int i = m_aNumbers[0];
        i++;
    }

    void Click()
    {
        ++m_clicks;
    }

    DWORD GetClicks() const
    {
        return m_clicks;
    }

    void ResetClicks()
    {
        m_clicks = 0;
    }

    bool IsOrderingSuccessful(TGameNode *pCheck);

    int CanMoveTile(int a, int empty)
    {
        int bCanMove = 0;
        if (a == empty) return bCanMove;

        int zPos = empty;
        int mod4 = a % 4;
        int zmod4 = zPos % 4;

        if (mod4 == zmod4)
        {
            bCanMove = 10 + mod4;
        }
        else
        {
            if (a >= 0 && a < 4 && zPos >= 0 && zPos < 4) bCanMove = 20;
            else if (a >= 4 && a < 8 && zPos >= 4 && zPos < 8) bCanMove = 21;
            else if (a >= 8 && a < 12 && zPos >= 8 && zPos < 12) bCanMove = 22;
            else if (a >= 12 && a < 16 && zPos >= 12 && zPos < 16) bCanMove = 23;
        }

        return bCanMove;
    }

    void SwapTiles(int a, int b)
    {
        int t = m_aNumbers[a];
        if (t < 0 || t > 15)
        {
            int i = t;
            i = t + 1;
        }
        m_aNumbers[a] = m_aNumbers[b];
        m_aNumbers[b] = t;
    }

    void SlideTiles(int from, int to, int action)
    {
        switch (action)
        {
            case 20: // row 0
            case 21: // row 1
            case 22: // row 2
            case 23: // row 3
            {
                if (from < to)
                {
                    for (int i = to; i > from; --i)
                    {
                        SwapTiles(i, i - 1);
                    }
                }
                else
                {
                    for (int i = to; i < from; ++i)
                    {
                        SwapTiles(i, i + 1);
                    }
                }
            }
                break;

            case 10: // column 0
            case 11: // column 1
            case 12: // column 2
            case 13: // column 3
            {
                if (from < to)
                {
                    for (int i = to; i > from; i -= 4)
                    {
                        SwapTiles(i, i - 4);
                    }
                }
                else
                {
                    for (int i = to; i < from; i += 4)
                    {
                        SwapTiles(i, i + 4);
                    }
                }
            }
                break;
        }
    }

    int GetTileAt(int i)
    {
        if (i < 0 || i >= MAX_PIECES) return -1;
        return m_aNumbers[i];
    }

    int GetEmptyTilePos()
    {
        int a = 0;
        for (int i = 0; i < MAX_PIECES; ++i)
        {
            if (m_aNumbers[i] == 0)
            {
                a = i;
                break;
            }
        }
        return a;
    }

};

void MyController::OnLButtonDown(int x, int y, UINT flags)
{
    TGameScene *pScene = GetScene();
    DigitTile *pNode = dynamic_cast<DigitTile*> (pScene->HitTest(x, y));
    if (pNode == NULL)
    {
        return;
    }

    Click(); // count the clicking

    GameView *pView = (GameView*) GetView();
    int a = pView->HitTest(x, y);

    int empty = GetEmptyTilePos();
    int bCanMove = CanMoveTile(a, empty);
    if (bCanMove > 0)
    {
        SlideTiles(a, empty, bCanMove);
    }
}

void NewGameButton::OnClicked(TGameNode *pSender, unsigned long nID)
{
    if (pSender != this) return;

    MyController *pCtl = (MyController*) GetController();
    if (pCtl == NULL) return;

    int ret = MessageBox(NULL, TEXT("Do you want to create a new game"),
            GAME_NAME, MB_YESNO | MB_ICONEXCLAMATION);
    if (ret == IDYES)
        pCtl->ShuffleTiles();
}

int GameView::HitTest(int x, int y)
{
    int cell = 0;

    RECT rc;
    GetClientRect(&rc);

    int cx = 60;
    int cy = 60;

    POINT pt = {x, y};

    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4; ++c)
        {
            RECT rcCell = {c*cx, r*cy, (c + 1) * cx, (r + 1) * cy};
            if (PtInRect(&rcCell, pt))
            {
                return cell;
            }
            ++cell;
        }
    }

    return cell;
}

///////////////////////////////////////////////////////////

class ExpectedLayer : public TGameLayer
{
protected:
    int m_aExpectedNumbers[16];
    RECT m_rcDraw;
    HBRUSH m_hbrEmpty;

public:
    ExpectedLayer(int w, int h);
    virtual ~ExpectedLayer();

    void SetExpectedNumbers(const int *pExpectedNumbers);
    bool AreMatchedAllNumbers(const int *pTestedNumbers);

    void SetDrawPos(int left, int top, int right, int bottom);

    virtual void Update()
    {
    }
    virtual void Draw(HDC hdc);
};

ExpectedLayer::ExpectedLayer(int w, int h)
{
    m_rect.left = m_rect.top = 0;
    m_rect.right = w;
    m_rect.bottom = h;

    m_hbrEmpty = CreateSolidBrush(RGB(200, 200, 200));
}

ExpectedLayer::~ExpectedLayer()
{
    DeleteObject(m_hbrEmpty);
}

void ExpectedLayer::SetDrawPos(int left, int top, int right, int bottom)
{
    m_rcDraw.left = left;
    m_rcDraw.top = top;
    m_rcDraw.right = right;
    m_rcDraw.bottom = bottom;
}

void ExpectedLayer::Draw(HDC hdc)
{
    int w = m_rcDraw.right - m_rcDraw.left;
    int h = m_rcDraw.bottom - m_rcDraw.top;

    int cx = w / 4;
    int cy = h / 4;
    int row = 0;

    TCHAR sz[4];

    for (int i = 0; i < 16; ++i)
    {
        RECT rc;
        rc.left = m_rcDraw.left + cx * (i % 4);
        rc.top = m_rcDraw.top + cy * row;
        rc.right = rc.left + cx;
        rc.bottom = rc.top + cy;

        if (i % 4 + 1 == 4) ++row;

        if (m_aExpectedNumbers[i] == 0)
        {
            FillRect(hdc, &rc, m_hbrEmpty);
        }
        else
        {
            Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
            wsprintf(sz, TEXT("%d"), m_aExpectedNumbers[i]);
            DrawText(hdc, sz, lstrlen(sz), &rc, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
        }
    }
}

void ExpectedLayer::SetExpectedNumbers(const int *pExpectedNumbers)
{
    memcpy(m_aExpectedNumbers, pExpectedNumbers, sizeof (int)*16);
}

bool ExpectedLayer::AreMatchedAllNumbers(const int *pTestedNumbers)
{
    bool bAllMatched = true;
    for (int i = 0; i < 16; ++i)
    {
        if (m_aExpectedNumbers[i] != pTestedNumbers[i])
        {
            bAllMatched = false;
            break;
        }
    }
    return bAllMatched;
}


///////////////////////////////////////////////////////////

class CtlLayer : public TGameLayer
{
public:
    TGameLabel *m_pClicks;
    TTimerLabel *m_pTimeCount;

public:

    CtlLayer(RECT *prc)
    {
        m_rect = *prc;

        RECT rect;
        rect.left = 270;
        rect.top = 30;
        rect.right = rect.left + 100;
        rect.bottom = rect.top + 30;
        AddNode(new NewGameButton(TEXT("New Game"), &rect));

        rect.top = 70;
        rect.bottom = rect.top + 30;
        AddNode(new TGameLabel(TEXT("Clicks : "), &rect));

        rect.top = 110;
        rect.bottom = rect.top + 30;
        m_pClicks = new TGameLabel(TEXT("0"), &rect);
        AddNode(m_pClicks);

        rect.left = 30;
        rect.top = 270;
        rect.right = rect.left + 100;
        rect.bottom = rect.top + 30;
        AddNode(new TGameLabel(TEXT("Times : "), &rect));

        rect.left = 150;
        rect.right = rect.left + 100;
        m_pTimeCount = new TTimerLabel(&rect);
        AddNode(m_pTimeCount);
    }
};

class TileLayer : public TGameLayer
{
protected:
    TCellProperties m_aCellProperties[MAX_PIECES]; // to set the position

public:

    void Init(int w, int h)
    {
        m_rect.left = m_rect.top = 0;
        m_rect.right = w;
        m_rect.bottom = h;

        int cx = 60;
        int cy = 60;

        int row = 0;
        for (int i = 0; i < MAX_PIECES; ++i)
        {
            DigitTile *pNode = new DigitTile((i + 1) % MAX_PIECES, i);

            int j = i % 4;
            if (j == 0 && i > 0) ++row;

            pNode->m_rect.left = j*cx;
            pNode->m_rect.top = row*cy;
            pNode->m_rect.right = pNode->m_rect.left + cx;
            pNode->m_rect.bottom = pNode->m_rect.top + cy;


            // initialize the position for each cell
            m_aCellProperties[i].index = i;
            m_aCellProperties[i].rect.left = pNode->m_rect.left;
            m_aCellProperties[i].rect.top = pNode->m_rect.top;
            m_aCellProperties[i].rect.right = pNode->m_rect.right;
            m_aCellProperties[i].rect.bottom = pNode->m_rect.bottom;

            AddNode(pNode);
        }

    }

    TCellProperties *GetCellProperties()
    {
        return m_aCellProperties;
    }


};

///////////////////////////////////////////////////////////

class MyScene : public TGameScene
{
public:
    CtlLayer *m_pCtlLayer;
    ExpectedLayer *m_pExpectedLayer;

public:

    void Init(int w, int h)
    {
        m_rect.left = m_rect.top = 0;
        m_rect.right = w;
        m_rect.bottom = h;

        TileLayer *pLayer = new TileLayer();
        pLayer->Init(w, h);
        AddLayer(pLayer);

        RECT rect;
        rect.left = 0;
        rect.top = 0;
        rect.right = w;
        rect.bottom = h;
        m_pCtlLayer = new CtlLayer(&rect);

        AddLayer(m_pCtlLayer);
        m_pExpectedLayer = new ExpectedLayer(w, h);
        m_pExpectedLayer->SetDrawPos(270, 270, 370, 370);
        m_pExpectedLayer->SetExpectedNumbers(g_mapNumbers[g_currentMap]);
        AddLayer(m_pExpectedLayer);
    }
public:

    MyScene()
    {

    }

};

///////////////////////////////////////////////////////////

void DigitTile::Update()
{
    // update its position
    MyController *pCtl = (MyController*) GetController();
    const int *pNumbers = pCtl->GetTileArray();

    for (int i = 0; i < MAX_PIECES; ++i)
    {
        int val = pNumbers[i];
        if (val == m_value)
        {
            // set the new position
            TileLayer *pLayer = (TileLayer*) GetParent();
            TCellProperties *pProperties = pLayer->GetCellProperties();

            m_rect = pProperties[i].rect;
            m_index = i;
            break;
        }
    }
}


///////////////////////////////////////////////////////////
// MovingTileGame

class MovingTileGame : public TGame
{
    BOOL m_bRunning;
public:
    MovingTileGame();
    virtual ~MovingTileGame();
    BOOL CreateGame();
    BOOL EndGame();


    virtual BOOL IsRunning();
    virtual BOOL IsGameOver();
    virtual BOOL IsGameStart();
    virtual BOOL IsGamePause();

    virtual void EndScene();
};

MovingTileGame::MovingTileGame()
: m_bRunning(TRUE)
{
}

MovingTileGame::~MovingTileGame()
{
}

BOOL MovingTileGame::CreateGame()
{
    TGameScene *pScene = GetActiveScene();
    if (!pScene) return FALSE;

    MyController *pCtl = (MyController*) pScene->GetController();
    pCtl->SetMap(g_mapNumbers[g_currentMap]);
    pCtl->ShuffleTiles();

    return TRUE;
}

void MovingTileGame::EndScene()
{
    // update score
    MyScene *pScene = (MyScene*) GetActiveScene();
    MyController *pCtl = (MyController*) pScene->GetController();

    TCHAR sz[8];
    wsprintf(sz, TEXT("%d"), pCtl->GetClicks());
    pScene->m_pCtlLayer->m_pClicks->SetText(sz);

    BOOL bEnd = EndGame();
    if (bEnd)
    {
        UINT id = MessageBox(NULL, TEXT("Do you want to creat a new game ? "), GAME_NAME,
                MB_YESNO | MB_ICONINFORMATION);

        if (id == IDYES)
        {
            g_currentMap++;
            if (g_currentMap >= MAX_MAPS)
                g_currentMap = 0;
            pScene->m_pExpectedLayer->SetExpectedNumbers(g_mapNumbers[g_currentMap]);

            pCtl->SetMap(g_mapNumbers[g_currentMap]);
            pCtl->ShuffleTiles();
            pCtl->ResetClicks();
            //
            pScene->m_pCtlLayer->m_pTimeCount->Reset();
            pScene->m_pCtlLayer->m_pClicks->SetText(TEXT("0"));
        }
    }
}

BOOL MovingTileGame::EndGame()
{
    MyScene *pScene = (MyScene*) GetActiveScene();
    if (!pScene) return FALSE;

    MyController *pCtl = (MyController*) pScene->GetController();
    if (!pCtl) return FALSE;

    return pCtl->IsOrderingSuccessful(pScene->m_pExpectedLayer);
}

bool MyController::IsOrderingSuccessful(TGameNode *pCheck)
{
    ExpectedLayer *pLayer = (ExpectedLayer*) pCheck;

    return pLayer->AreMatchedAllNumbers(m_aNumbers);
}

BOOL MovingTileGame::IsRunning()
{
    return m_bRunning;
}

BOOL MovingTileGame::IsGameOver()
{
    return TRUE;
}

BOOL MovingTileGame::IsGameStart()
{
    return TRUE;
}

BOOL MovingTileGame::IsGamePause()
{
    return TRUE;
}



///////////////////////////////////////////////////////////
// MainWnd

class MainWnd : public TWindow<MainWnd>
{
public:

    LPCTSTR GetClassName()
    {
        static TCHAR szClassName[] = TEXT("15 - puzzle window class");
        return szClassName;
    }

protected:

    virtual BOOL RegisterWnd(HINSTANCE hinst)
    {
        WNDCLASS wc;
        wc.lpszClassName = GetClassName();
        wc.lpfnWndProc = MainWnd::StaticWndProc;
        wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
        wc.hInstance = hinst;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
        wc.lpszMenuName = NULL;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        return (BOOL) RegisterClass(&wc);
    }

    virtual void OnDestroy()
    {
        PostQuitMessage(0);
    }

    virtual void OnGetMinMaxInfo(LPMINMAXINFO lpmm)
    {
        lpmm->ptMaxTrackSize.x = 480;
        lpmm->ptMaxTrackSize.y = 480;
        lpmm->ptMinTrackSize.x = 480;
        lpmm->ptMinTrackSize.y = 480;
    }
};

///////////////////////////////////////////////////////////

class MovingTileGameApp : public TGameApp<MainWnd>
{
public:

    MovingTileGameApp(HINSTANCE hinst, MainWnd& wnd, TGame *pGame)
    : TGameApp(hinst, wnd, pGame)
    {
    }

protected:

    virtual BOOL InitInstance()
    {
        m_wndMain.ShowWindow(SW_SHOW);
        return TRUE;
    }

};

///////////////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
    // create the main window
    MainWnd wnd;
    wnd.CreateEx(0, //WS_EX_CLIENTEDGE,
            GAME_NAME, WS_OVERLAPPEDWINDOW,
            0, 0, 480, 480,
            NULL, NULL, hInst);

    // create the scene view
    TGameView *pView = new GameView();
    pView->Create(NULL, WS_CHILD, 0, 0, 480, 480, wnd.GetHWND(), (HMENU) IDC_GAMEVIEW, hInst);
    // create the scene controller
    TGameController *pCtl = new MyController(pView);
    pView->SetController(pCtl); // controller and view know together
    // create the main scene
    TGameScene *pScene = new MyScene();
    pScene->SetController(pCtl);
    ((MyScene*) pScene)->Init(480, 480);

    pCtl->SetScene(pScene);
    ((MyController*) pCtl)->SetMap(g_mapNumbers[g_currentMap]);

    // create the game
    TGame *pGame = new MovingTileGame();
    // add the main scene
    pGame->AddScene(pScene);
    // set active to the main scene
    pGame->SetActiveScene(pScene);

    ((MovingTileGame*) pGame)->CreateGame();

    // run the game application
    MovingTileGameApp app(hInst, wnd, pGame);
    return app.Run();
}
