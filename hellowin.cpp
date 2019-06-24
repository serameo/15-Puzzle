///////////////////////////////////////////////////////////////////////////////
// hellowin.cpp
// Author: Seree Rakwong
// Date: 5-Aug-2013
//

#include "resource.h"
#include "TGenApp.h"
#include "TDlgApp.h"

#define IDC_BUTTON1 100
#define IDC_EDIT1 101
#define IDC_COMBO1 102
#define IDC_LISTBOX1 103
#define IDC_STATIC1 104
#define IDC_BUTTON2 105

class TColorComboBox public TComboBox

{
protected:

    void OnMeasureItem(LPMEASUREITEMSTRUCT lpmis)
    {
        if (lpmis->itemID != -1)
        {
            lpmis->itemHeight = 24;

        }

    }

    void OnDrawItem(LPDRAWITEMSTRUCT lpdis)
    {
        if (lpdis->itemID == -1)
        {
            return;

        }
        COLORREF color = (COLORREF) lpdis->itemData;

        HBRUSH hbr = CreateSolidBrush(color);
        FillRect(lpdis->hDC, &lpdis->rcItem, hbr);

        DeleteObject(hbr);

    }

    /*
void OnCBNSelChange()
{
MessageBox(GetParent(m_hwnd), TEXT(â€œselect changedâ€?), TEXT(â€œhelloâ€?), MB_OK);
}*/


public:

    int AddColor(LPCTSTR text, COLORREF color)

    {
        int idx = this->SendMessage(CB_ADDSTRING, 0, (LPARAM) text);
        this->SendMessage(CB_SETITEMDATA, idx, (LPARAM) color);
        return idx;

    }

    COLORREF GetCurColor()

    {
        int idx = GetCurSel();
        return (COLORREF) GetItemData(idx);

    }

};

class TColorListBox public TListBox

{
protected:

    void OnMeasureItem(LPMEASUREITEMSTRUCT lpmis)
    {
        if (lpmis->itemID != -1)
        {
            lpmis->itemHeight = 24;

        }

    }

    void OnDrawItem(LPDRAWITEMSTRUCT lpdis)
    {
        if (lpdis->itemID == -1)
        {
            return;

        }
        COLORREF color = (COLORREF) lpdis->itemData;

        HBRUSH hbr = CreateSolidBrush(color);
        FillRect(lpdis->hDC, &lpdis->rcItem, hbr);

        DeleteObject(hbr);

    }



public:

    int AddColor(LPCTSTR text, COLORREF color)

    {
        int idx = this->SendMessage(LB_ADDSTRING, 0, (LPARAM) text);
        this->SendMessage(LB_SETITEMDATA, idx, (LPARAM) color);
        return idx;

    }

};

class MyDlg public TDialog<MyDlg >

{
public:
    TCHAR m_text[256];



public:

    MyDlg()
    TDialog<MyDlg>(IDD_EXAMPLE1)

    {
        lstrcpy(m_text, TEXT(â€œHelloâ€ ?));

    }


    //DECLARE_MESSAGE_MAP()


protected:

    int OnInitDialog()

    {
        TStatic static1;
        static1.Create(m_text,
                WS_CHILD | WS_VISIBLE,
                10, 180, 280, 30,
                m_hwnd,
                IDC_STATIC1,
                (HINSTANCE) GetModuleHandle(NULL));
        return 1;

    }

    void OnSysCommand(int x, int y, UINT nType)

    {
        if (nType == SC_CLOSE)
        {
            EndDialog(IDCANCEL);

        }

    }

    void OnTestClicked()

    {

        MessageBox(m_hwnd, m_text, TEXT(â€œHello Windowâ€ ?), MB_OK | MB_ICONINFORMATION);



    }

    DECLARE_COMMAND_MAP()



};

BEGIN_COMMAND_MAP(MyDlg, TDialog<MyDlg>)
ON_COMMAND_MAP(IDC_TEST, BN_CLICKED, OnTestClicked)
END_COMMAND_MAP(MyDlg, TDialog<MyDlg>)

class MyWnd public TWindow<MyWnd >

{
private:
    TButton button1;
    TButton button2;
    TEdit edit1;
    TColorComboBox combo1;
    TColorListBox list1;
    MyDlg dlg1;



public:

    MyWnd()

    {

    }



protected:

    BOOL RegisterWnd(HINSTANCE hInst)

    {
        WNDCLASS wc;
        wc.lpszClassName = GetClassName();
        wc.lpfnWndProc = MyWnd::StaticWndProc;
        wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
        wc.hInstance = hInst;
        wc.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
        wc.lpszMenuName = NULL;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        return (BOOL) RegisterClass(&wc);

    }

    int OnCreate(LPCREATESTRUCT lpcs)
    {
        button1.Create(Lâ€ ? OKâ€ ?, WS_CHILD | WS_VISIBLE,
                10, 10, 80, 30,
                GetHWND(), IDC_BUTTON1, lpcs->hInstance);
        button2.Create(Lâ€ ? Cancelâ€ ?, WS_CHILD | WS_VISIBLE,
                10, 100, 80, 30,
                GetHWND(), IDC_BUTTON2, lpcs->hInstance);

        edit1.CreateEx(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                10, 50, 80, 30,
                GetHWND(), IDC_EDIT1, lpcs->hInstance);

        // subclass technique
        HWND hwndCombo = CreateWindow(TEXT(â€œCOMBOBOXâ€ ?), NULL,
                WS_CHILD | WS_VISIBLE |
                CBS_OWNERDRAWFIXED | CBS_HASSTRINGS | CBS_DROPDOWNLIST,
                100, 10, 80, 120,
                GetHWND(), (HMENU) IDC_COMBO1, lpcs->hInstance, NULL);
        combo1.SubclassWnd(hwndCombo);

        combo1.SendMessage(CB_ADDSTRING, 0, (LPARAM) TEXT(â€œREDâ€ ?));
        combo1.SendMessage(CB_SETITEMDATA, 0, (LPARAM) RGB(255, 0, 0));

        combo1.SendMessage(CB_ADDSTRING, 0, (LPARAM) TEXT(â€œGREENâ€ ?));
        combo1.SendMessage(CB_SETITEMDATA, 1, (LPARAM) RGB(0, 255, 0));

        combo1.SendMessage(CB_ADDSTRING, 0, (LPARAM) TEXT(â€œBLUEâ€ ?));
        combo1.SendMessage(CB_SETITEMDATA, 2, (LPARAM) RGB(0, 0, 255));

        combo1.AddColor(TEXT(â€œCYANâ€ ?), RGB(0, 255, 255));

        // test listbox
        list1.CreateEx(WS_EX_CLIENTEDGE, NULL,
                WS_CHILD | WS_VISIBLE | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS,
                200, 10, 80, 120,
                GetHWND(), IDC_LISTBOX1, lpcs->hInstance);
        list1.SendMessage(LB_ADDSTRING, 0, (LPARAM) TEXT(â€œYELLOWâ€ ?));
        list1.SendMessage(LB_SETITEMDATA, 0, (LPARAM) RGB(255, 255, 0));

        list1.SendMessage(LB_ADDSTRING, 0, (LPARAM) TEXT(â€œCYANâ€ ?));
        list1.SendMessage(LB_SETITEMDATA, 1, (LPARAM) RGB(0, 255, 255));

        list1.SendMessage(LB_ADDSTRING, 0, (LPARAM) TEXT(â€œMAGENTAâ€ ?));
        list1.SendMessage(LB_SETITEMDATA, 2, (LPARAM) RGB(255, 0, 255));

        list1.AddColor(TEXT(â€œREDâ€ ?), RGB(255, 0, 0));
        list1.AddColor(TEXT(â€œGREENâ€ ?), RGB(0, 255, 0));
        list1.AddColor(TEXT(â€œBLUEâ€ ?), RGB(0, 0, 255));

        //dlg1.Create();
        return 0;

    }

    void OnDestroy()
    {
        PostQuitMessage(0);
    }

    void OnPaint(HDC hdc)

    {
        static TCHAR sz[] = Lâ€ ? Hello windows by templateâ€ ?;

        RECT rc;
        GetClientRect(m_hwnd, &rc);
        DrawText(hdc, sz, lstrlen(sz), &rc, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

    }

    DECLARE_COMMAND_MAP()

    void OnButton2Clicked()

    {


        TChooseFont cf(m_hwnd);
        cf.Init();
        if (cf.Execute())
        {
            MessageBox(GetParent(m_hwnd), TEXT(â€œchoose font okâ€ ?), TEXT(â€œHelloâ€ ?), MB_OK);

            LOGFONT lf;
            cf.GetLogFont(&lf);
            int i = lf.lfCharSet;


        }
        else

        {
            MessageBox(m_hwnd, TEXT(â€œcancelâ€ ?), TEXT(â€œHelloâ€ ?), MB_OK);

            TOpenSaveFileName osf(m_hwnd);
            osf.Init();
            osf.Execute();

            MessageBox(m_hwnd, osf.GetFileName(), TEXT(â€œHelloâ€ ?), MB_OK);

        }

    }

    void OnButton1Clicked()

    {
        TCHAR szBuffer[256];
        edit1.GetWindowText(szBuffer, 256);

        //MyDlg dlg(m_hwnd);
        if (edit1.GetWindowTextLength() > 0)
            lstrcpy(dlg1.m_text, szBuffer);
        dlg1.Show(m_hwnd);

        TPrintDlg pd(m_hwnd);
        pd.Init();
        pd.Execute();

    }

    void OnCombo1SelChange()

    {
        int n = combo1.GetCurSel();
        //TCHAR szBuffer[256];
        //combo1.GetText(szBuffer, 256);
        //MessageBox(GetParent(m_hwnd), szBuffer, TEXT(â€œHelloâ€?), MB_OK);
        COLORREF cr = combo1.GetCurColor();

        TChooseColor cc(m_hwnd);
        cc.Init(cr, CC_RGBINIT);
        cc.Execute();

    }



public:

    LPCTSTR GetClassName()

    {
        static TCHAR szClassName[] = TEXT(â€œMyWnd_Classâ€ ?);
        return szClassName;

    }

};

BEGIN_COMMAND_MAP(MyWnd, TWindow<MyWnd>)
ON_COMMAND_MAP(IDC_BUTTON1, BN_CLICKED, OnButton1Clicked)
ON_COMMAND_MAP(IDC_COMBO1, CBN_SELCHANGE, OnCombo1SelChange)
ON_COMMAND_MAP(IDC_BUTTON2, BN_CLICKED, OnButton2Clicked)
END_COMMAND_MAP(MyWnd, TWindow<MyWnd>)

class MyApp public TGenApp<MyWnd >
//class MyApp public TDlgApp<MyWnd>

{
public:

    MyApp(HINSTANCE hInst, MyWnd& wnd)
    TGenApp<MyWnd>(hInst, wnd)
    //: TDlgApp<MyWnd>(hInst, wnd)

    {

    }

    virtual ~MyApp()
    {
    }



protected:

    BOOL InitInstance()

    {
        BOOL b = m_wndMain.CreateEx(WS_EX_CLIENTEDGE,
                Lâ€ ? Hello Windowsâ€ ?, WS_OVERLAPPEDWINDOW,
                0, 0, CW_USEDEFAULT, CW_USEDEFAULT,
                NULL, NULL, m_hInst);
        if (b) m_wndMain.ShowWindow(SW_SHOW);
        return b;

    }

};

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)

{
    MyWnd wnd;
    MyApp app(hInst, wnd);
    return app.Run();

}
