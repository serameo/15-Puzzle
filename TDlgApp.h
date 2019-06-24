///////////////////////////////////////////////////////////////////////////////
// TDlgApp.h
// Author: Seree Rakwong
// Date: 8-Aug-2013
//

#ifndef TDLGAPP_H
#define TDLGAPP_H


#include "TGenApp.h"
#include <vector>

using std::vector;

///////////////////////////////////////////////////////////////////////////////
// Using common dialog
// ref: http://msdn.microsoft.com/en-us/library/windows/desktop/ms646829(v=vs.85).aspx
//

template<class T>
class TComDlg
{
protected:
    HWND m_hwndP;
    T m_struct;

public:

    TComDlg(HWND hwndP)
    : m_hwndP(hwndP)
    {
        ZeroMemory(&m_struct, sizeof (m_struct));
        m_struct.lStructSize = sizeof (m_struct);
        m_struct.hwndOwner = m_hwndP;
    }

    virtual BOOL Execute() = 0;
};

///////////////////////////////////////////////////////////////////////////////
// choose color

class TChooseColor : public TComDlg<CHOOSECOLOR>
{
    COLORREF m_aColors[16];

public:

    TChooseColor(HWND hwndP)
    : TComDlg<CHOOSECOLOR>(hwndP)
    {
        ZeroMemory(m_aColors, sizeof (COLORREF)*16);
        m_struct.lpCustColors = m_aColors;
    }

    virtual BOOL Execute()
    {
        return ChooseColor(&m_struct);
    }

    void Init(COLORREF cr = RGB(0, 0, 0), DWORD flags = CC_RGBINIT)
    {
        m_struct.Flags = flags;
        m_struct.rgbResult = cr;
    }

    COLORREF GetSelColor()
    {
        return m_struct.rgbResult;
    }

    void SetSelColor(COLORREF cr)
    {
        m_struct.rgbResult = cr;
    }
};

///////////////////////////////////////////////////////////////////////////////
// choose font

class TChooseFont : public TComDlg<CHOOSEFONT>
{
    LOGFONT m_logfont;

public:

    TChooseFont(HWND hwndP)
    : TComDlg<CHOOSEFONT>(hwndP)
    {

    }

    virtual BOOL Execute()
    {
        return ChooseFont(&m_struct);
    }

    void Init(COLORREF crFont = RGB(0, 0, 0), DWORD flags = CF_SCREENFONTS | CF_EFFECTS)
    {
        m_struct.lpLogFont = &m_logfont;
        m_struct.Flags = flags;
        m_struct.rgbColors = crFont;
    }

    void GetLogFont(LOGFONT *plf)
    {
        memcpy(plf, &m_logfont, sizeof (m_logfont));
    }

    void SetLogFont(LOGFONT *plf)
    {
        memcpy(&m_logfont, plf, sizeof (m_logfont));
    };
};

///////////////////////////////////////////////////////////////////////////////
// open file

class TOpenSaveFileName : public TComDlg<OPENFILENAME>
{
    BOOL m_bOpen;
    TCHAR m_szFileName[MAX_PATH];

public:

    TOpenSaveFileName(HWND hwndP, BOOL bOpen = TRUE)
    : TComDlg<OPENFILENAME>(hwndP),
    m_bOpen(bOpen)
    {
        m_szFileName[0] = 0;
    }

    virtual BOOL Execute()
    {
        return (m_bOpen ? GetOpenFileName(&m_struct) : GetSaveFileName(&m_struct));
    }

    LPCTSTR GetFileName() const
    {
        return m_szFileName;
    }

    void Init(LPCTSTR pFilter = TEXT("All files(*.*)*.*"), DWORD flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST)
    {
        m_szFileName[0] = 0;
        m_struct.lpstrFile = m_szFileName;
        m_struct.nMaxFile = MAX_PATH;
        m_struct.lpstrFilter = pFilter;
        m_struct.nFilterIndex = 1;
        m_struct.lpstrFileTitle = NULL;
        m_struct.nMaxFileTitle = 0;
        m_struct.lpstrInitialDir = NULL;
        m_struct.Flags = flags;
    }

};

///////////////////////////////////////////////////////////////////////////////
// print dlg

class TPrintDlg : public TComDlg<PRINTDLG>
{
public:

    TPrintDlg(HWND hwndP)
    : TComDlg<PRINTDLG>(hwndP)
    {

    }

    virtual ~TPrintDlg()
    {
        if (m_struct.hDevMode != NULL)
            GlobalFree(m_struct.hDevMode);
        if (m_struct.hDevNames != NULL)
            GlobalFree(m_struct.hDevNames);
        DeleteObject(m_struct.hDC);
    }

    virtual BOOL Execute()
    {
        return PrintDlg(&m_struct);
    }

    void Init(DWORD flags = PD_USEDEVMODECOPIESANDCOLLATE | PD_RETURNDC)
    {
        m_struct.hDevMode = NULL; // Don't forget to free or store hDevMode.
        m_struct.hDevNames = NULL; // Don't forget to free or store hDevNames.
        m_struct.Flags = flags;
        m_struct.nCopies = 1;
        m_struct.nFromPage = 0xFFFF;
        m_struct.nToPage = 0xFFFF;
        m_struct.nMinPage = 1;
        m_struct.nMaxPage = 0xFFFF;
    }
};

///////////////////////////////////////////////////////////////////////////////
// page setup dlg

class TPageSetupDlg : public TComDlg<PAGESETUPDLG>
{
public:
    static BOOL CALLBACK StaticPagePaintHook(HWND, UINT, WPARAM, LPARAM);

public:

    TPageSetupDlg(HWND hwndP)
    : TComDlg<PAGESETUPDLG>(hwndP)
    {

    }

    virtual BOOL Execute()
    {
        return PageSetupDlg(&m_struct);
    }

    void Init(DWORD flags = PSD_INTHOUSANDTHSOFINCHES | PSD_MARGINS |
              PSD_ENABLEPAGEPAINTHOOK)
    {
        m_struct.Flags = flags;
        m_struct.rtMargin.top = 1000;
        m_struct.rtMargin.left = 1250;
        m_struct.rtMargin.right = 1250;
        m_struct.rtMargin.bottom = 1000;
        m_struct.lpfnPagePaintHook = (LPPAGEPAINTHOOK) StaticPagePaintHook;
    }

};

BOOL CALLBACK TPageSetupDlg::StaticPagePaintHook(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LPRECT lprc;
    COLORREF crMargRect;
    HDC hdc, hdcOld;

    switch (uMsg)
    {
        // Draw the margin rectangle.
    case WM_PSD_MARGINRECT:
        hdc = (HDC) wParam;
        lprc = (LPRECT) lParam;

        // Get the system highlight color.
        crMargRect = GetSysColor(COLOR_HIGHLIGHT);

        // Create a dash-dot pen of the system highlight color and
        // select it into the DC of the sample page.
        hdcOld = (HDC) SelectObject(hdc, CreatePen(PS_DASHDOT, 1, crMargRect));

        // Draw the margin rectangle.
        Rectangle(hdc, lprc->left, lprc->top, lprc->right, lprc->bottom);

        // Restore the previous pen to the DC.
        SelectObject(hdc, hdcOld);
        return TRUE;

    default:
        return FALSE;
    }
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// find & replace dlg

class TFindReplace : public TComDlg<FINDREPLACE>
{
    UINT m_msgFindReplace;
    HWND m_hdlg;

public:

    TFindReplace(HWND hwndP)
    : TComDlg<FINDREPLACE>(hwndP),
    m_msgFindReplace(0),
    m_hdlg(NULL)
    {
        m_msgFindReplace = RegisterWindowMessage(FINDMSGSTRING);
    }

    virtual BOOL Execute()
    {
        m_hdlg = FindText(&m_struct);
        return (m_hdlg != NULL);
    }

    void Init(LPTSTR pszFindWhat, int cchMax)
    {
        m_struct.lpstrFindWhat = pszFindWhat;
        m_struct.wFindWhatLen = cchMax;
        m_struct.Flags = 0;
    }

    UINT GetMessage() const
    {
        return m_msgFindReplace;
    }

    HWND GetHandle() const
    {
        return m_hdlg;
    }

};

///////////////////////////////////////////////////////////////////////////////
// dialog

template <class T>
class TDialog : public TWindow<T>
{
private:
    UINT m_nID;
    LPTSTR m_pszClassName;

public:
    TDialog(LPCTSTR lpTemplateName);
    TDialog(UINT nID);
    virtual ~TDialog();

    LPCTSTR GetClassName()
    {
        return (LPCTSTR) m_pszClassName;
    }
protected:
    static INT_PTR CALLBACK StaticDlgProc(HWND, UINT, WPARAM, LPARAM);
    virtual LRESULT WndProc(UINT message, WPARAM wParam, LPARAM lParam);

protected:

    virtual int OnInitDialog()
    {
        return 1;
    }

public:
    // modaless dialog
    BOOL Create(HWND hwndParent, HINSTANCE hInst = NULL);

    // modal dialog
    INT_PTR Show(HWND hwndParent, HINSTANCE hInst = NULL);

    // end dialog

    BOOL EndDialog(int nCode)
    {
        return ::EndDialog(m_hwnd, nCode);
    }
};

template <class T>
TDialog<T>::TDialog(LPCTSTR lpTemplateName)
: m_pszClassName(NULL),
m_nID(0)
{
    if (lpTemplateName)
    {
        m_pszClassName = (TCHAR*)new TCHAR[lstrlen(lpTemplateName) + 1];
        lstrcpy(m_pszClassName, lpTemplateName);
    }
}

template <class T>
TDialog<T>::TDialog(UINT nID)
: m_pszClassName(NULL),
m_nID(nID)
{

}

template <class T>
TDialog<T>::~TDialog()
{
    if (m_pszClassName)
    {
        delete[] m_pszClassName;
    }
}

template <class T>
BOOL TDialog<T>::Create(HWND hwndParent, HINSTANCE hInst)
{
    HWND hdlg = CreateDialogParam(
                                  (hInst == NULL ? (HINSTANCE) GetModuleHandle(NULL) : hInst),
                                  (m_nID != 0 ? MAKEINTRESOURCE(m_nID) : m_pszClassName),
                                  hwndParent,
                                  TDialog<T>::StaticDlgProc,
                                  (LPARAM)this);
    if (hdlg == NULL) return FALSE;

    m_hwnd = hdlg;

    return TRUE;
}

template <class T>
INT_PTR TDialog<T>::Show(HWND hwndParent, HINSTANCE hInst)
{
    INT_PTR nRet = DialogBoxParam(
                                  (hInst == NULL ? (HINSTANCE) GetModuleHandle(NULL) : hInst),
                                  (m_nID != 0 ? MAKEINTRESOURCE(m_nID) : m_pszClassName),
                                  hwndParent,
                                  TDialog<T>::StaticDlgProc,
                                  (LPARAM)this);

    return nRet;
}

template <class T>
INT_PTR CALLBACK TDialog<T>::StaticDlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    TDialog<T> *pSelf = (TDialog<T>*)GetWindowLong(hwnd, GWL_USERDATA);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        TDialog<T> *pDlg = (TDialog<T>*)lParam;

        if (pDlg)
        {
            pDlg->m_hwnd = hwnd;
            SetWindowLong(hwnd, GWL_USERDATA, (LONG) pDlg);
            pSelf = pDlg;
        }
    }
        break;
    }
    if (pSelf)
    {
        // call the window procedure
        int nRet = pSelf->WndProc(message, wParam, lParam);
        // check if the message is WM_INITDIALOG,
        // otherwise return 0
        if (message == WM_INITDIALOG) return nRet;
        else return 0;
    }

    return 0;
}

template <class T>
LRESULT TDialog<T>::WndProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return OnInitDialog();

    default:
        TWindow<T>::WndProc(message, wParam, lParam);
        break;
    }
    return 0;
}


////////////////////////////////////////////////////////////
// TDlgApp

template <class TDlg>
class TDlgApp : public TGenApp<TDlg>
{
public:
    TDlgApp(HINSTANCE, TDlg& dlg);
    virtual ~TDlgApp();

protected:
    void MainLoop();

public:
    void AddDlgChild(HWND hdlg);
    BOOL AreDlgMessages(MSG *pMsg);

private:
    std::vector<HWND> m_vecDlgs;
};

template <class TDlg>
TDlgApp<TDlg>::TDlgApp(HINSTANCE hInst, TDlg& dlg)
: TGenApp<TDlg>(hInst, dlg)
{
}

template <class TDlg>
TDlgApp<TDlg>::~TDlgApp()
{
}

template <class TDlg>
BOOL TDlgApp<TDlg>::AreDlgMessages(MSG *pMsg)
{
    BOOL bRet = FALSE;
    std::vector<HWND>::iterator it = m_vecDlgs.begin();
    for (; it != m_vecDlgs.end(); ++it)
    {
        // check if it is a dialog message
        bRet = IsDialogMessage((*it), pMsg);
        if (bRet) break;
    }
    return bRet;
}

template <class TDlg>
void TDlgApp<TDlg>::AddDlgChild(HWND hdlg)
{
    m_vecDlgs.push_back(hdlg);
}

template <class TDlg>
void TDlgApp<TDlg>::MainLoop()
{
    BOOL bRet;
    MSG msg;
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    {
        if (bRet == -1)
        {
            // Handle the error and possibly exit
        }
        else if (!AreDlgMessages(&msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}




#endif // TDLGAPP_H


