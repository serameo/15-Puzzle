 ///////////////////////////////////////////////////////////////////////////////
 // TGenApp.h
 // Author: Seree Rakwong
 // Date: 5-Aug-2013
 //

 #ifndef TGENAPP_H
 #define TGENAPP_H


 #include <windows.h>
 #include <windowsx.h>
 #include <commctrl.h>
 #include <uxtheme.h>
 #include <richedit.h>
 // common control 32
 #pragma comment(lib, "comctl32.lib")

 //#ifdef USE_OLEIDL_H
 //#include <oleidl.h>
 //#endif

 // notify mapping functions
 #define DECLARE_NOTIFY_MAP()\
 protected:\
 virtual void OnNotify(LPNMHDR lpnmh, LRESULT *pRes);

 #define DECLARE_EMPTY_NOTIFY(fn)\
 virtual void fn(LPNMHDR lpnmh, LRESULT *pRes){}

 #define BEGIN_NOTIFY_MAP(theClass, baseClass)\
 void theClass::OnNotify(LPNMHDR lpnmh, LRESULT *pRes)\
 {

 #define ON_NOTIFY_MAP(id, code, fn)\
 if(id == lpnmh->idFrom && code == lpnmh->code){ fn(lpnmh, pRes); return; }

 #define END_NOTIFY_MAP(theClass, baseClass)\
 baseClass::OnNotify(lpnmh, pRes);\
 }


 // control messasge mapping functions
 #define DECLARE_COMMAND_MAP()\
 protected:\
 virtual void OnCommand(UINT nID, UINT nCode, HWND hwndCtl);

 #define DECLARE_EMPTY_COMMAND(fn)\
 virtual void fn(){}

 #define BEGIN_COMMAND_MAP(theClass, baseClass)\
 void theClass::OnCommand(UINT nID, UINT nCode, HWND hwndCtl)\
 {

 #define ON_COMMAND_MAP(id, code, fn)\
 if(id == nID && code == nCode){ fn(); return; }

 #define END_COMMAND_MAP(theClass, baseClass)\
 baseClass::OnCommand(nID, nCode, hwndCtl);\
 }



////////////////////////////////////////////////////////////////////////////
// class TWindow

template <class T>
class TWindow
{
protected:
    BOOL m_bIsAttached;
public:
    HWND m_hwnd;
    WNDPROC m_lpfnWndProc;
    // need to override these classes
public:
    virtual LPCTSTR GetClassName() = 0;

protected:
    static LRESULT WINAPI StaticWndProc(HWND, UINT, WPARAM, LPARAM);
    virtual LRESULT WndProc(UINT, WPARAM, LPARAM);

    virtual BOOL RegisterWnd(HINSTANCE)
    {
        return FALSE;
    }

public:
    TWindow();
    virtual ~TWindow();
    BOOL Create(LPCTSTR lpWindowName,
                DWORD dwStyle, int x, int y, int width, int height,
                HWND hwndParent, HMENU hMenu,
                HINSTANCE hInst);
    BOOL CreateEx(DWORD dwExStyle,
                  LPCTSTR lpWindowName,
                  DWORD dwStyle, int x, int y, int width, int height,
                  HWND hwndParent, HMENU hMenu,
                  HINSTANCE hInst);

    HWND GetHWND() const
    {
        return m_hwnd;
    }

    BOOL Destroy()
    {
        return ::DestroyWindow(m_hwnd);
    }
    BOOL SubclassWnd(HWND);
    HWND Attach(HWND hwnd);
    HWND Detach();

    // Win32 functions

    LRESULT DefWndProc(UINT message, WPARAM wParam, LPARAM lParam)
    {
        return ::DefWindowProc(m_hwnd, message, wParam, lParam);
    }

    LRESULT CallWndProc(UINT message, WPARAM wParam, LPARAM lParam)
    {
        return ::CallWindowProc(m_lpfnWndProc, m_hwnd, message, wParam, lParam);
    }

    LRESULT SendMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
    {
        return ::SendMessage(m_hwnd, message, wParam, lParam);
    }

    LRESULT PostMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
    {
        return ::PostMessage(m_hwnd, message, wParam, lParam);
    }

    BOOL ShowWindow(int nCmdShow)
    {
        return ::ShowWindow(m_hwnd, nCmdShow);
    }

    int GetWindowText(LPTSTR lpString, int nMaxCount)
    {
        return ::GetWindowText(m_hwnd, lpString, nMaxCount);
    }

    int GetWindowTextLength()
    {
        return ::GetWindowTextLength(m_hwnd);
    }

    int SetWindowText(LPCTSTR lpsz)
    {
        return ::SetWindowText(m_hwnd, lpsz);
    }

    BOOL GetClientRect(RECT *prc)
    {
        return ::GetClientRect(m_hwnd, prc);
    }


protected:
    // window messages

    virtual int OnCreate(LPCREATESTRUCT lpcs)
    {
        return 0;
    }

    virtual void OnDestroy()
    {
    }

    virtual void OnPaint(HDC hdc)
    {
    }

    virtual void OnSize(int cx, int cy, UINT flag)
    {
    }

    virtual void OnMove(int x, int y)
    {
    }

    virtual int OnClose()
    {
        return 0;
    }

    virtual BOOL OnQueryOpen()
    {
        return TRUE;
    }

    virtual void OnGetMinMaxInfo(LPMINMAXINFO lpmm)
    {
    }
    // owner draw messages

    virtual void OnCompareItem(LPCOMPAREITEMSTRUCT lpcis)
    {
    }

    virtual void OnDrawItem(LPDRAWITEMSTRUCT lpdis)
    {
    }

    virtual void OnMeasureItem(LPMEASUREITEMSTRUCT lpmis)
    {
    }

    virtual void OnDeleteItem(LPDELETEITEMSTRUCT lpdis)
    {
    }
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
    // keyboard messages

    virtual void OnActivate(UINT flag, BOOL bActivated, HWND hwndActivated)
    {
    }

    virtual void OnKillFocus(HWND hwndFocus)
    {
    }

    virtual void OnSetFocus(HWND hwndFocus)
    {
    }

    virtual void OnChar(TCHAR ch, int nCount, int nScanCode,
                        BOOL extendedKey, BOOL contextCode,
                        BOOL prevKeyState, BOOL transitionState)
    {
    }

    virtual void OnSysChar(TCHAR ch, int nCount, int nScanCode,
                           BOOL extendedKey, BOOL contextCode,
                           BOOL prevKeyState, BOOL transitionState)
    {
    }

    virtual void OnDeadChar(TCHAR ch, int nCount, int nScanCode,
                            BOOL extendedKey, BOOL contextCode,
                            BOOL prevKeyState, BOOL transitionState)
    {
    }

    virtual void OnSysDeadChar(TCHAR ch, int nCount, int nScanCode,
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

    virtual void OnSysKeyDown(UINT vkCode, int nCount, int nScanCode,
                              BOOL extendedKey, BOOL contextCode,
                              BOOL prevKeyState, BOOL transitionState)
    {
    }

    virtual void OnSysKeyUp(UINT vkCode, int nCount, int nScanCode,
                            BOOL extendedKey, BOOL contextCode,
                            BOOL prevKeyState, BOOL transitionState)
    {
    }
    // command

    virtual void OnCommand(UINT nID, UINT nCode, HWND hwndControl)
    {
    }

    virtual void OnSysCommand(int x, int y, UINT nType)
    {
    }

    // a control notification message

    virtual HBRUSH OnCtlColor(UINT message, HDC hdc, HWND hwndCtl)
    {
        return (HBRUSH) DefWndProc(message, (WPARAM) hdc, (LPARAM) hwndCtl);
    }

    virtual void OnNotify(LPNMHDR lpnmh, LRESULT *pRes)
    {
        *pRes = 0;
    }

    // drag list box notification messages

    virtual BOOL OnDLBeginDrag(LPDRAGLISTINFO pInfo)
    {
        return (BOOL) DefWindowProc(m_hwnd, DL_BEGINDRAG, 0, (LPARAM) pInfo);
    }

    virtual void OnDLCancelDrag(LPDRAGLISTINFO)
    {
    }

    virtual UINT OnDLDragging(LPDRAGLISTINFO pInfo)
    {
        return (UINT) DefWindowProc(m_hwnd, DL_DRAGGING, 0, (LPARAM) pInfo);
    }

    virtual void OnDLDropped(LPDRAGLISTINFO)
    {
    }
};

template <class T>
TWindow<T>::TWindow()
: m_hwnd(NULL),
m_lpfnWndProc(NULL),
m_bIsAttached(FALSE)
{
}

template <class T>
TWindow<T>::~TWindow()
{
    if (m_lpfnWndProc != NULL)
    {
        SetWindowLong(m_hwnd, GWL_WNDPROC, (LONG) m_lpfnWndProc);
    }
}

template <class T>
BOOL TWindow<T>::Create(LPCTSTR lpWindowName,
                        DWORD dwStyle, int x, int y, int width, int height,
                        HWND hwndParent, HMENU hMenu,
                        HINSTANCE hInst)
{
    if (m_bIsAttached)
    {
        // do not allow create if it is still attached another window handle
        return FALSE;
    }
    // all interited classes need to implement RegisterWnd() function
    BOOL b = RegisterWnd(hInst);
    if (!b) return FALSE;

    // create the registered window
    HWND hwnd = CreateWindow(GetClassName(), lpWindowName,
                             dwStyle, x, y, width, height,
                             hwndParent, hMenu, hInst, this);
    if (hwnd == NULL) return FALSE;

    // hook the created window handle
    m_hwnd = hwnd;
    return TRUE;
}

template <class T>
BOOL TWindow<T>::CreateEx(DWORD dwExStyle,
                          LPCTSTR lpWindowName,
                          DWORD dwStyle, int x, int y, int width, int height,
                          HWND hwndParent, HMENU hMenu,
                          HINSTANCE hInst)
{
    if (m_bIsAttached)
    {
        // do not allow create if it is still attached another window handle
        return FALSE;
    }
    // all interited classes need to implement RegisterWnd() function
    BOOL b = RegisterWnd(hInst);
    if (!b) return FALSE;

    // create the registered window
    HWND hwnd = CreateWindowEx(dwExStyle, GetClassName(), lpWindowName,
                               dwStyle, x, y, width, height,
                               hwndParent, hMenu, hInst, this);
    if (hwnd == NULL) return FALSE;

    // hook the created window handle
    m_hwnd = hwnd;
    return TRUE;
}

template <class T>
BOOL TWindow<T>::SubclassWnd(HWND hwndSubclass)
{
    if (m_hwnd || m_lpfnWndProc)
        return FALSE;

    m_hwnd = hwndSubclass;

    WNDPROC wndproc = (WNDPROC) GetWindowLong(hwndSubclass, GWL_WNDPROC);
    m_lpfnWndProc = wndproc;

    SetWindowLong(hwndSubclass, GWL_WNDPROC, (LONG) TControl<T>::StaticWndProc);
    SetWindowLong(hwndSubclass, GWL_USERDATA, (LONG)this);

    return TRUE;
}

template <class T>
LRESULT WINAPI TWindow<T>::StaticWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // get the user data memory stored
    TWindow<T> *pSelf = (TWindow<T>*)GetWindowLong(hwnd, GWL_USERDATA);
    switch (message)
    {
    case WM_CREATE:
    {
        // store the user data memory
        LPCREATESTRUCT lpcs = (LPCREATESTRUCT) lParam;
        TWindow<T> *pWnd = (TWindow<T>*)lpcs->lpCreateParams;

        if (pWnd)
        {
            pWnd->m_hwnd = hwnd;
            SetWindowLong(hwnd, GWL_USERDATA, (LONG) pWnd);
            // set the user data as a user data memory
            pSelf = pWnd;
        }
    }
        break;
    }
    // call the member function
    if (pSelf) return pSelf->WndProc(message, wParam, lParam);
    // do call a default procedure if there is no a window object
    return DefWindowProc(hwnd, message, wParam, lParam);
}

template <class T>
LRESULT TWindow<T>::WndProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: return OnCreate((LPCREATESTRUCT) lParam);
    case WM_CLOSE:
    {
        int ret = OnClose();
        if (ret != 0) return ret;
    }
        break;

    case WM_DESTROY: OnDestroy();
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
        OnPaint(hdc);
        EndPaint(m_hwnd, &ps);
    }
        break;

        // owner draw events
    case WM_COMPAREITEM:
    case WM_DRAWITEM:
    case WM_DELETEITEM:
    case WM_MEASUREITEM:
    {
        // seek the actual window child to get a message
        HWND hwndChild = GetWindow(m_hwnd, GW_CHILD);
        for (; hwndChild != NULL; hwndChild = GetWindow(hwndChild, GW_HWNDNEXT))
        {
            UINT nID = GetWindowLong(hwndChild, GWL_ID);
            if (nID == wParam)
            {
                // found the windows sent the message
                TWindow<T>* pWnd = (TWindow<T>*)GetWindowLong(hwndChild, GWL_USERDATA);
                if (pWnd)
                {
                    switch (message)
                    {
                    case WM_COMPAREITEM: pWnd->OnCompareItem((LPCOMPAREITEMSTRUCT) lParam);
                        break;
                    case WM_DRAWITEM: pWnd->OnDrawItem((LPDRAWITEMSTRUCT) lParam);
                        break;
                    case WM_DELETEITEM: pWnd->OnDeleteItem((LPDELETEITEMSTRUCT) lParam);
                        break;
                    case WM_MEASUREITEM: pWnd->OnMeasureItem((LPMEASUREITEMSTRUCT) lParam);
                        break;
                    }
                } // pWnd
                // after processing, stop finding a child
                break; // for-break
            } // nID == wParam
        }
    }
        return 1;

        // mouse events
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_LBUTTONDBLCLK:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_RBUTTONDBLCLK:
    case WM_MOUSEMOVE:
    {
        int x = GET_X_LPARAM(lParam);
        int y = GET_Y_LPARAM(lParam);
        UINT flags = (UINT) wParam;
        switch (message)
        {
        case WM_LBUTTONDOWN: OnLButtonDown(x, y, flags);
            break;
        case WM_LBUTTONUP: OnLButtonUp(x, y, flags);
            break;
        case WM_LBUTTONDBLCLK: OnLButtonDblClk(x, y, flags);
            break;
        case WM_RBUTTONDOWN: OnRButtonDown(x, y, flags);
            break;
        case WM_RBUTTONUP: OnRButtonUp(x, y, flags);
            break;
        case WM_RBUTTONDBLCLK: OnRButtonDblClk(x, y, flags);
            break;
        case WM_MOUSEMOVE: OnMouseMove(x, y, flags);
            break;
        }
    }
        break;

        // keyboard events
    case WM_CHAR:
    case WM_SYSCHAR:
    case WM_DEADCHAR:
    case WM_SYSDEADCHAR:
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    {
        UINT vkCode = (UINT) wParam;
        int nCount = (int) (lParam & 0x0000ffff);
        int nScanCode = (int) ((lParam & 0x00ff0000) >> 16);
        BOOL extendedKey = (BOOL) (lParam & 0x01000000);
        BOOL contextCode = (BOOL) (lParam & 0x20000000);
        BOOL prevKeyState = (BOOL) (lParam & 0x40000000);
        BOOL transitionState = (BOOL) (lParam & 0x80000000);

        switch (message)
        {
        case WM_CHAR:
            OnChar((TCHAR) vkCode, nCount, nScanCode, extendedKey,
                   contextCode, prevKeyState, transitionState);
            break;
        case WM_SYSCHAR:
            OnSysChar((TCHAR) vkCode, nCount, nScanCode, extendedKey,
                      contextCode, prevKeyState, transitionState);
            break;
        case WM_DEADCHAR:
            OnDeadChar((TCHAR) vkCode, nCount, nScanCode, extendedKey,
                       contextCode, prevKeyState, transitionState);
            break;
        case WM_SYSDEADCHAR:
            OnSysDeadChar((TCHAR) vkCode, nCount, nScanCode, extendedKey,
                          contextCode, prevKeyState, transitionState);
            break;
        case WM_KEYDOWN:
            OnKeyDown(vkCode, nCount, nScanCode, extendedKey,
                      contextCode, prevKeyState, transitionState);
            break;
        case WM_KEYUP:
            OnKeyUp(vkCode, nCount, nScanCode, extendedKey,
                    contextCode, prevKeyState, transitionState);
        case WM_SYSKEYDOWN:
            OnSysKeyDown(vkCode, nCount, nScanCode, extendedKey,
                         contextCode, prevKeyState, transitionState);
            break;
        case WM_SYSKEYUP:
            OnSysKeyUp(vkCode, nCount, nScanCode, extendedKey,
                       contextCode, prevKeyState, transitionState);
            break;
        }
    }
        break;

    case WM_SETFOCUS: OnSetFocus((HWND) wParam);
        break;
    case WM_KILLFOCUS: OnKillFocus((HWND) wParam);
        break;

    case WM_SIZE: OnSize((int) LOWORD(lParam), (int) HIWORD(lParam), (UINT) wParam);
        break;
    case WM_MOVE: OnMove((int) (short) LOWORD(lParam), (int) (short) HIWORD(lParam));
        break;

    case WM_QUERYOPEN: return (LRESULT) OnQueryOpen();

    case WM_ACTIVATE:
        OnActivate(LOWORD(wParam), (BOOL) HIWORD(wParam), (HWND) lParam);
        break;

    case WM_SYSCOMMAND:
        OnSysCommand(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (UINT) wParam);
        break;

    case WM_CTLCOLORMSGBOX:
    case WM_CTLCOLOREDIT:
    case WM_CTLCOLORLISTBOX:
    case WM_CTLCOLORBTN:
    case WM_CTLCOLORDLG:
    case WM_CTLCOLORSCROLLBAR:
    case WM_CTLCOLORSTATIC:
        return (LRESULT) OnCtlColor(message, (HDC) wParam, (HWND) lParam);

        // control notifications
    case WM_COMMAND:
    {
        UINT id = LOWORD(wParam);
        UINT code = HIWORD(wParam);
        HWND hwndCtl = (HWND) lParam;
        OnCommand(id, code, hwndCtl);
    }
        break;

    case WM_NOTIFY:
    {
        LPNMHDR lpnmh = (LPNMHDR) lParam;
        LRESULT res = 0;
        OnNotify(lpnmh, &res);
        return res;
    }
        break;

        // drag list box notifications
    case DL_BEGINDRAG:
        return OnDLBeginDrag((LPDRAGLISTINFO) lParam);
    case DL_CANCELDRAG:
        OnDLCancelDrag((LPDRAGLISTINFO) lParam);
        break;
    case DL_DRAGGING:
        return OnDLDragging((LPDRAGLISTINFO) lParam);
    case DL_DROPPED:
        OnDLDropped((LPDRAGLISTINFO) lParam);
        break;

    case WM_GETMINMAXINFO:
        OnGetMinMaxInfo((LPMINMAXINFO) lParam);
        break;
    }
    return DefWndProc(message, wParam, lParam);
}

template<class T>
HWND TWindow<T>::Attach(HWND hwnd)
{
    if (m_hwnd != NULL && !m_bIsAttached)
    {
        // cannot attach because the current handle
        // having been created
        return NULL;
    }
    if (hwnd == m_hwnd || hwnd == NULL)
    {
        return hwnd;
    }
    HWND hwndCur = m_hwnd;
    m_hwnd = hwnd;
    m_bIsAttached = TRUE;
    return hwndCur;
}

template<class T>
HWND TWindow<T>::Detach()
{
    if (m_bIsAttached)
    {
        m_bIsAttached = FALSE;
        HWND hwnd = m_hwnd;
        m_hwnd = NULL;
        return hwnd;
    }
    return NULL;
}

////////////////////////////////////////////////////////////////////////////
// class TControl
// ref: http://msdn.microsoft.com/en-us/library/windows/desktop/bb773169(v=vs.85).aspx
//

template <class T>
class TControl : public TWindow<T>
{
    // this is not implemented GetClassName()
    // because we need it to be a abstract class
protected:
    LRESULT WndProc(UINT message, WPARAM wParam, LPARAM lParam);

public:
    TControl();
    virtual ~TControl();
    BOOL Create(LPCTSTR lpWindowName,
                DWORD dwStyle, int x, int y, int width, int height,
                HWND hwndParent, UINT nID,
                HINSTANCE hInst = NULL);
    BOOL CreateEx(DWORD dwExStyle,
                  LPCTSTR lpWindowName,
                  DWORD dwStyle, int x, int y, int width, int height,
                  HWND hwndParent, UINT nID,
                  HINSTANCE hInst = NULL);
};

template <class T>
TControl<T>::TControl()
{
}

template <class T>
TControl<T>::~TControl()
{

}

template <class T>
BOOL TControl<T>::Create(LPCTSTR lpWindowName,
                         DWORD dwStyle, int x, int y, int width, int height,
                         HWND hwndParent, UINT nID,
                         HINSTANCE hInst)
{
    if (m_bIsAttached)
    {
        // do not allow create if it is still attached another window handle
        return FALSE;
    }
    HWND hwnd = CreateWindow(GetClassName(), lpWindowName,
                             dwStyle, x, y, width, height,
                             hwndParent, (HMENU) nID,
                             (hInst == NULL ? (HINSTANCE) GetModuleHandle(NULL) : hInst),
                             this);
    if (hwnd == NULL) return FALSE;

    m_hwnd = hwnd;

    WNDPROC wndproc = (WNDPROC) GetWindowLong(hwnd, GWL_WNDPROC);
    m_lpfnWndProc = wndproc;

    SetWindowLong(hwnd, GWL_WNDPROC, (LONG) TControl<T>::StaticWndProc);
    SetWindowLong(hwnd, GWL_USERDATA, (LONG)this);

    return TRUE;
}

template <class T>
BOOL TControl<T>::CreateEx(DWORD dwExStyle,
                           LPCTSTR lpWindowName,
                           DWORD dwStyle, int x, int y, int width, int height,
                           HWND hwndParent, UINT nID,
                           HINSTANCE hInst)
{
    if (m_bIsAttached)
    {
        // do not allow create if it is still attached another window handle
        return FALSE;
    }
    HWND hwnd = CreateWindowEx(dwExStyle, GetClassName(), lpWindowName,
                               dwStyle, x, y, width, height,
                               hwndParent, (HMENU) nID,
                               (hInst == NULL ? (HINSTANCE) GetModuleHandle(NULL) : hInst),
                               this);
    if (hwnd == NULL) return FALSE;
    m_hwnd = hwnd;

    WNDPROC wndproc = (WNDPROC) GetWindowLong(hwnd, GWL_WNDPROC);
    m_lpfnWndProc = wndproc;

    SetWindowLong(hwnd, GWL_WNDPROC, (LONG) TControl<T>::StaticWndProc);
    SetWindowLong(hwnd, GWL_USERDATA, (LONG)this);

    return TRUE;
}

template <class T>
LRESULT TControl<T>::WndProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message != WM_PAINT)
    {
        LRESULT res = TWindow<T>::WndProc(message, wParam, lParam);
    }
    return CallWndProc(message, wParam, lParam);
}


///////////////////////////////////////
// button

class TButton : public TControl<TButton>
{
public:

    TButton()
    {
    }

    LPCTSTR GetClassName()
    {
        static LPCTSTR s_pszClassName = TEXT("BUTTON");
        return s_pszClassName;
    }
    // button messages mapping

    void Click()
    {
        SendMessage(BM_CLICK);
    }

    UINT GetCheck()
    {
        return (UINT) SendMessage(BM_GETCHECK);
    }

    HICON GetIcon()
    {
        return (HICON) SendMessage(BM_GETIMAGE, IMAGE_ICON);
    }

    HBITMAP GetBitmap()
    {
        return (HBITMAP) SendMessage(BM_GETIMAGE, IMAGE_BITMAP);
    }

    UINT GetState()
    {
        return (UINT) SendMessage(BM_GETSTATE);
    }

    void SetCheck(UINT fCheck)
    {
        SendMessage(BM_SETCHECK, (WPARAM) fCheck);
    }

    void SetDontClick(BOOL fDontClick = TRUE)
    {
        SendMessage(BM_SETDONTCLICK, (WPARAM) fDontClick);
    }

    HICON SetIcon(HICON hIcon)
    {
        return (HICON) SendMessage(BM_SETIMAGE, IMAGE_ICON, (LPARAM) hIcon);
    }

    HBITMAP SetBitmap(HBITMAP hbmp)
    {
        return (HBITMAP) SendMessage(BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hbmp);
    }

    void SetState(BOOL fState = TRUE)
    {
        SendMessage(BM_SETSTATE, (WPARAM) fState);
    }

    void SetStyle(DWORD dwStyle, BOOL fRedraw)
    {
        SendMessage(BM_SETSTYLE, (WPARAM) dwStyle, MAKELPARAM(fRedraw, 0));
    }

    BOOL GetIdealSize(SIZE *pSize)
    {
        return (BOOL) SendMessage(BCM_GETIDEALSIZE, 0, (LPARAM) pSize);
    }

    BOOL GetImageList(BUTTON_IMAGELIST *pImg)
    {
        return (BOOL) SendMessage(BCM_GETIMAGELIST, 0, (LPARAM) pImg);
    }

    BOOL GetNote(LPTSTR pszNote, DWORD *pdwSize)
    {
        return (BOOL) SendMessage(BCM_GETNOTE, (WPARAM) pdwSize, (LPARAM) pszNote);
    }

    UINT GetNoteLength()
    {
        return (UINT) SendMessage(BCM_GETNOTELENGTH);
    }

    BOOL GetSplitInfo(BUTTON_SPLITINFO *pSplitInfo)
    {
        return (BOOL) SendMessage(BCM_GETSPLITINFO, 0, (LPARAM) pSplitInfo);
    }

    BOOL GetTextMargin(RECT *pRect)
    {
        return (BOOL) SendMessage(BCM_GETTEXTMARGIN, 0, (LPARAM) pRect);
    }

    BOOL SetDropDownState(BOOL fState = TRUE)
    {
        return (BOOL) SendMessage(BCM_SETDROPDOWNSTATE, (WPARAM) fState);
    }

    BOOL SetImageList(BUTTON_IMAGELIST *pImg)
    {
        return (BOOL) SendMessage(BCM_SETIMAGELIST, 0, (LPARAM) pImg);
    }

    BOOL SetNote(LPCTSTR pszNote)
    {
        return (BOOL) SendMessage(BCM_SETNOTE, 0, (LPARAM) pszNote);
    }

    BOOL SetShield(BOOL fShield)
    {
        return (BOOL) SendMessage(BCM_SETNOTE, 0, (LPARAM) fShield);
    }

    BOOL SetSplitInfo(BUTTON_SPLITINFO *pSplitInfo)
    {
        return (BOOL) SendMessage(BCM_SETSPLITINFO, 0, (LPARAM) pSplitInfo);
    }

    BOOL SetTextMargin(RECT *pRect)
    {
        return (BOOL) SendMessage(BCM_SETTEXTMARGIN, 0, (LPARAM) pRect);
    }

};

///////////////////////////////////////
// combo box

class TComboBox : public TControl<TComboBox>
{
public:

    TComboBox()
    {
    }

    LPCTSTR GetClassName()
    {
        static LPCTSTR s_pszClassName = TEXT("COMBOBOX");
        return s_pszClassName;
    }

    // combo box messages mapping

    int AddItemData(LPARAM data)
    {
        return ComboBox_AddItemData(m_hwnd, data);
    }

    int AddString(LPCTSTR lpsz)
    {
        return ComboBox_AddString(m_hwnd, lpsz);
    }

    int DeleteString(int index)
    {
        return ComboBox_DeleteString(m_hwnd, index);
    }

    int Dir(UINT attrs, LPCTSTR lpszFileSpec)
    {
        return ComboBox_Dir(m_hwnd, attrs, lpszFileSpec);
    }

    BOOL Enable(BOOL fEnable = TRUE)
    {
        return ComboBox_Enable(m_hwnd, fEnable);
    }

    int FindItemData(LPARAM data, int indexStart = -1)
    {
        return ComboBox_FindItemData(m_hwnd, indexStart, data);
    }

    int FindString(LPCTSTR lpsz, int indexStart = -1)
    {
        return ComboBox_FindString(m_hwnd, indexStart, lpsz);
    }

    int FindStringExact(LPCTSTR lpsz, int indexStart = -1)
    {
        return ComboBox_FindStringExact(m_hwnd, indexStart, lpsz);
    }

    int GetCount()
    {
        return ComboBox_GetCount(m_hwnd);
    }

    BOOL GetCueBannerText(LPTSTR lpsz, int cchText)
    {
        return (BOOL) ComboBox_GetCueBannerText(m_hwnd, lpsz, cchText);
    }

    int GetCurSel()
    {
        return ComboBox_GetCurSel(m_hwnd);
    }

    void GetDroppedControlRect(RECT *pRect)
    {
        return ComboBox_GetDroppedControlRect(m_hwnd, pRect);
    }

    BOOL GetDroppedState()
    {
        return ComboBox_GetDroppedState(m_hwnd);
    }

    UINT GetExtendedUI()
    {
        return ComboBox_GetExtendedUI(m_hwnd);
    }

    LRESULT GetItemData(int index)
    {
        return ComboBox_GetItemData(m_hwnd, index);
    }

    int GetItemHeight()
    {
        return ComboBox_GetItemHeight(m_hwnd);
    }

    int GetLBText(int index, LPTSTR lpszBuffer)
    {
        return ComboBox_GetLBText(m_hwnd, index, lpszBuffer);
    }

    int GetLBTextLen(int index)
    {
        return ComboBox_GetLBTextLen(m_hwnd, index);
    }

    int GetMinVisible()
    {
        return ComboBox_GetMinVisible(m_hwnd);
    }

    int GetText(LPTSTR lpsz, int cchMax)
    //{ return ComboBox_GetText(m_hwnd, lpsz, cchMax); }
    {
        return GetWindowText(lpsz, cchMax);
    }

    int GetTextLength()
    //{ return ComboBox_GetTextLength(m_hwnd); }
    {
        return GetWindowTextLength();
    }

    int InsertItemData(LPARAM data, int index = -1)
    {
        return ComboBox_InsertItemData(m_hwnd, index, data);
    }

    int InsertString(LPCTSTR lpsz, int index = -1)
    {
        return ComboBox_InsertString(m_hwnd, index, lpsz);
    }

    int LimitText(int cchMax)
    {
        return ComboBox_LimitText(m_hwnd, cchMax);
    }

    int ResetContent()
    {
        return ComboBox_ResetContent(m_hwnd);
    }

    int SelectItemData(LPARAM data, int indexStart = -1)
    {
        return ComboBox_SelectItemData(m_hwnd, indexStart, data);
    }

    int SelectString(LPCTSTR lpsz, int indexStart = -1)
    {
        return ComboBox_SelectString(m_hwnd, indexStart, lpsz);
    }

    BOOL SetCueBannerText(LPCTSTR lpsz)
    {
        return ComboBox_SetCueBannerText(m_hwnd, lpsz);
    }

    int SetCurSel(int index)
    {
        return ComboBox_SetCurSel(m_hwnd, index);
    }

    int SetExtendedUI(UINT flags)
    {
        return ComboBox_SetExtendedUI(m_hwnd, flags);
    }

    int SetItemData(int index, LPARAM data)
    {
        return ComboBox_SetItemData(m_hwnd, index, data);
    }

    int SetItemHeight(int index, int cyItem)
    {
        return ComboBox_SetItemHeight(m_hwnd, index, cyItem);
    }

    BOOL SetMinVisible(int iMinVisible)
    {
        return ComboBox_SetMinVisible(m_hwnd, iMinVisible);
    }

    int SetText(LPCTSTR lpsz)
    {
        return SetWindowText(lpsz);
    }

    BOOL ShowDropdown(BOOL fShow = TRUE)
    {
        return ComboBox_ShowDropdown(m_hwnd, fShow);
    }

};

///////////////////////////////////////
// list box

class TListBox : public TControl<TListBox>
{
public:

    TListBox()
    {
    }

    LPCTSTR GetClassName()
    {
        static LPCTSTR s_pszClassName = TEXT("LISTBOX");
        return s_pszClassName;
    }

    void DrawInsert(int nItem)
    {
        return ::DrawInsert(GetParent(m_hwnd), m_hwnd, nItem);
    }

    DWORD GetListBoxInfo()
    {
        return ::GetListBoxInfo(m_hwnd);
    }

    int LBItemFromPt(POINT pt, BOOL bAutoScroll)
    {
        return ::LBItemFromPt(m_hwnd, pt, bAutoScroll);
    }

    BOOL MakeDragList()
    {
        return ::MakeDragList(m_hwnd);
    }

    int AddFile(LPCTSTR lpFileName)
    {
        return SendMessage(LB_ADDFILE, 0, (LPARAM) lpFileName);
    }

    int AddString(LPCTSTR lpString)
    {
        return SendMessage(LB_ADDSTRING, 0, (LPARAM) lpString);
    }

    int DeleteString(int index)
    {
        return SendMessage(LB_DELETESTRING, (WPARAM) index);
    }

    int Dir(UINT flags, LPCTSTR lpPath)
    {
        return SendMessage(LB_DIR, (WPARAM) flags, (LPARAM) lpPath);
    }

    int FindString(int index, LPCTSTR lpString)
    {
        return SendMessage(LB_FINDSTRING, (WPARAM) index, (LPARAM) lpString);
    }

    int FindStringExact(int index, LPCTSTR lpString)
    {
        return SendMessage(LB_FINDSTRINGEXACT, (WPARAM) index, (LPARAM) lpString);
    }

    int GetAnchorIndex()
    {
        return SendMessage(LB_GETANCHORINDEX);
    }

    int GetCaretIndex()
    {
        return SendMessage(LB_GETCARETINDEX);
    }

    int GetCount()
    {
        return SendMessage(LB_GETCOUNT);
    }

    int GetCurSel()
    {
        return SendMessage(LB_GETCURSEL);
    }

    int GetHorizontalExtent()
    {
        return SendMessage(LB_GETHORIZONTALEXTENT);
    }

    DWORD GetItemData(int index)
    {
        return SendMessage(LB_GETITEMDATA, (WPARAM) index);
    }

    int GetItemHeight(int index)
    {
        return SendMessage(LB_GETITEMHEIGHT, (WPARAM) index);
    }

    int GetItemRect(int index, RECT *pRect)
    {
        return SendMessage(LB_GETITEMRECT, (WPARAM) index, (LPARAM) pRect);
    }
    // int GetListBoxInfo()
    // { return SendMessage(LB_GETLISTBOXINFO); }

    int GetLocale()
    {
        return SendMessage(LB_GETLOCALE);
    }

    int GetSel(int index)
    {
        return SendMessage(LB_GETSEL, (WPARAM) index);
    }

    int GetSelCount()
    {
        return SendMessage(LB_GETSELCOUNT);
    }

    int GetSelItems(int *pIndexes, int cMax)
    {
        return SendMessage(LB_GETSELITEMS, (WPARAM) cMax, (LPARAM) pIndexes);
    }

    int GetText(int index, LPTSTR lpString)
    {
        return SendMessage(LB_GETTEXT, (WPARAM) index, (LPARAM) lpString);
    }

    int GetTextLen(int index)
    {
        return SendMessage(LB_GETTEXTLEN, (WPARAM) index);
    }

    int GetTopIndex()
    {
        return SendMessage(LB_GETTOPINDEX);
    }

    int InitStorage(int number, DWORD dwSize)
    {
        return SendMessage(LB_INITSTORAGE, (WPARAM) number, (LPARAM) dwSize);
    }

    int InsertString(int index, LPCTSTR lpString)
    {
        return SendMessage(LB_INSERTSTRING, (WPARAM) index, (LPARAM) lpString);
    }

    int ItemFromPoint(int x, int y)
    {
        return SendMessage(LB_ITEMFROMPOINT, 0, MAKELPARAM(x, y));
    }

    void ResetContent()
    {
        SendMessage(LB_RESETCONTENT);
    }

    int SelectString(int index, LPCTSTR lpString)
    {
        return SendMessage(LB_SELECTSTRING, (WPARAM) index, (LPARAM) lpString);
    }

    int SelItemRange(int start, int end, BOOL fSelected = TRUE)
    {
        return SendMessage(LB_SELITEMRANGE, (WPARAM) fSelected, MAKELPARAM(start, end));
    }

    int SelItemRangeEx(int start, int end)
    {
        return SendMessage(LB_SELITEMRANGEEX, (WPARAM) start, (LPARAM) end);
    }

    int SetAnchorIndex(int index)
    {
        return SendMessage(LB_SETANCHORINDEX, (WPARAM) index);
    }

    int SetCaretIndex(int index, BOOL fScroll = TRUE)
    {
        return SendMessage(LB_SETCARETINDEX, (WPARAM) index, (LPARAM) fScroll);
    }

    void SetColumnWidth(int width)
    {
        SendMessage(LB_SETCOLUMNWIDTH, (WPARAM) width);
    }

    int SetCount(int count)
    {
        return SendMessage(LB_SETCOUNT, (WPARAM) count);
    }

    int SetCurSel(int index)
    {
        return SendMessage(LB_SETCURSEL, (WPARAM) index);
    }

    void SetHorizontalExtent(int horz)
    {
        SendMessage(LB_SETHORIZONTALEXTENT, (WPARAM) horz);
    }

    int SetItemData(int index, DWORD data)
    {
        return SendMessage(LB_SETITEMDATA, (WPARAM) index, (LPARAM) data);
    }

    int SetItemHeight(int index, int height)
    {
        return SendMessage(LB_SETITEMHEIGHT, (WPARAM) index, (LPARAM) height);
    }

    int SetLocale(int locale)
    {
        return SendMessage(LB_SETLOCALE, (WPARAM) locale);
    }

    int SetSel(int index, BOOL fSelect = TRUE)
    {
        return SendMessage(LB_SETSEL, (WPARAM) fSelect, (LPARAM) index);
    }

    BOOL SetTabStops(int *pTabs, int number)
    {
        return (BOOL) SendMessage(LB_SETTABSTOPS, (WPARAM) number, (LPARAM) pTabs);
    }

    int SetTopIndex(int index)
    {
        return SendMessage(LB_SETTOPINDEX, (WPARAM) index);
    }

};

///////////////////////////////////////
// static

class TStatic : public TControl<TStatic>
{
public:

    TStatic()
    {
    }

    LPCTSTR GetClassName()
    {
        static LPCTSTR s_pszClassName = TEXT("STATIC");
        return s_pszClassName;
    }

    HBITMAP GetBitmap()
    {
        return (HBITMAP) SendMessage(STM_GETIMAGE, IMAGE_BITMAP);
    }

    HCURSOR GetCursor()
    {
        return (HCURSOR) SendMessage(STM_GETIMAGE, IMAGE_CURSOR);
    }

    HMETAFILE GetMetaFile()
    {
        return (HMETAFILE) SendMessage(STM_GETIMAGE, IMAGE_ENHMETAFILE);
    }

    HICON GetIcon()
    {
        return (HICON) SendMessage(STM_GETIMAGE, IMAGE_ICON);
    }

    HBITMAP SetBitmap(HBITMAP hbmp)
    {
        return (HBITMAP) SendMessage(STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hbmp);
    }

    HCURSOR SetCursor(HCURSOR hCursor)
    {
        return (HCURSOR) SendMessage(STM_SETIMAGE, IMAGE_CURSOR, (LPARAM) hCursor);
    }

    HMETAFILE SetMetaFile(HMETAFILE hbmp)
    {
        return (HMETAFILE) SendMessage(STM_SETIMAGE, IMAGE_ENHMETAFILE, (LPARAM) hbmp);
    }

    HICON SetIcon(HICON hIcon)
    {
        return (HICON) SendMessage(STM_SETIMAGE, IMAGE_ICON, (LPARAM) hIcon);
    }
};

///////////////////////////////////////
// edit

class TEdit : public TControl<TEdit>
{
public:

    TEdit()
    {
    }

    LPCTSTR GetClassName()
    {
        static LPCTSTR s_pszClassName = TEXT("EDIT");
        return s_pszClassName;
    }

    // edit messages mapping

    BOOL CanUndo()
    {
        return Edit_CanUndo(m_hwnd);
    }

    void EmptyUndoBuffer()
    {
        Edit_EmptyUndoBuffer(m_hwnd);
    }

    BOOL Enable(BOOL fEnable = TRUE)
    {
        return Edit_Enable(m_hwnd, fEnable);
    }

    void FmtLines(BOOL fAddEOL = TRUE)
    {
        Edit_FmtLines(m_hwnd, fAddEOL);
    }

    BOOL GetCueBannerText(LPTSTR lpsz, int cchMax)
    {
        return Edit_GetCueBannerText(m_hwnd, lpsz, cchMax);
    }

    int GetFirstVisibleLine()
    {
        return Edit_GetFirstVisibleLine(m_hwnd);
    }

    HLOCAL GetHandle()
    {
        return Edit_GetHandle(m_hwnd);
    }

    int GetLine(int line, LPTSTR lpsz, int cchMax)
    {
        return Edit_GetLine(m_hwnd, line, lpsz, cchMax);
    }

    int GetLineCount()
    {
        return Edit_GetLineCount(m_hwnd);
    }

    BOOL GetModify()
    {
        return Edit_GetModify(m_hwnd);
    }

    TCHAR GetPasswordChar()
    {
        return Edit_GetPasswordChar(m_hwnd);
    }

    void GetRect(RECT *lprc)
    {
        Edit_GetRect(m_hwnd, lprc);
    }

    DWORD GetSel()
    {
        return Edit_GetSel(m_hwnd);
    }

    int GetText(LPTSTR lpsz, int cchMax)
    {
        return GetWindowText(lpsz, cchMax);
    }

    int GetTextLength()
    {
        return GetWindowTextLength();
    }

    EDITWORDBREAKPROC GetWordBreakProc()
    {
        return Edit_GetWordBreakProc(m_hwnd);
    }

    BOOL HideBalloonTip()
    {
        return Edit_HideBalloonTip(m_hwnd);
    }

    void LimitText(int cchMax)
    {
        Edit_LimitText(m_hwnd, cchMax);
    }

    int LineFromChar(int ch)
    {
        return Edit_LineFromChar(m_hwnd, ch);
    }

    int LineIndex(int line)
    {
        return Edit_LineIndex(m_hwnd, line);
    }

    int LineLength(int line)
    {
        return Edit_LineLength(m_hwnd, line);
    }

#if (_WIN_NT >= 0x0800)

    DWORD NoSetFocus()
    {
        return Edit_NoSetFocus(m_hwnd);
    }

    DWORD TakeFocus()
    {
        return Edit_TakeFocus(m_hwnd);
    }
#endif

    void ReplaceSel(LPCTSTR lpszReplace)
    {
        Edit_ReplaceSel(m_hwnd, lpszReplace);
    }

    void Scroll(int dv, int dh)
    {
        Edit_Scroll(m_hwnd, dv, dh);
    }

    BOOL ScrollCaret()
    {
        return Edit_ScrollCaret(m_hwnd);
    }

    BOOL SetCueBannerText(LPCTSTR lpsz)
    {
        return Edit_SetCueBannerText(m_hwnd, lpsz);
    }

    BOOL SetCueBannerTextFocused(LPCWSTR lpcwText, BOOL fDrawFocused)
    {
        return Edit_SetCueBannerTextFocused(m_hwnd, lpcwText, fDrawFocused);
    }

    void SetHandle(HLOCAL hLocal)
    {
        Edit_SetHandle(m_hwnd, hLocal);
    }

    void SetModify(BOOL fModified = TRUE)
    {
        Edit_SetModify(m_hwnd, fModified);
    }

    void SetPasswordChar(TCHAR ch)
    {
        Edit_SetPasswordChar(m_hwnd, ch);
    }

    BOOL SetReadOnly(BOOL fReadOnly = TRUE)
    {
        return Edit_SetReadOnly(m_hwnd, fReadOnly);
    }

    void SetRect(RECT *lprc)
    {
        Edit_SetRect(m_hwnd, lprc);
    }

    void SetRectNoPaint(RECT *lprc)
    {
        Edit_SetRectNoPaint(m_hwnd, lprc);
    }

    void SetSel(int start = 0, int end = -1)
    {
        Edit_SetSel(m_hwnd, start, end);
    }

    void SetTabStops(int cTabs, int *pTabs)
    {
        Edit_SetTabStops(m_hwnd, cTabs, pTabs);
    }

    int SetText(LPCTSTR lpsz)
    {
        return SetWindowText(lpsz);
    }

    void SetWordBreakProc(EDITWORDBREAKPROC lpfnWordBreak)
    {
        Edit_SetWordBreakProc(m_hwnd, lpfnWordBreak);
    }

    BOOL ShowBalloonTip(PEDITBALLOONTIP peditballoontip)
    {
        return Edit_ShowBalloonTip(m_hwnd, peditballoontip);
    }

    BOOL Undo()
    {
        return Edit_Undo(m_hwnd);
    }


};

///////////////////////////////////////
// animate

class TAnimate : public TControl<TAnimate>
{
public:

    TAnimate()
    {
    }

    LPCTSTR GetClassName()
    {
        return ANIMATE_CLASS;
    }

public:
    BOOL Create(DWORD dwStyle, HWND hwndParent, UINT nID, HINSTANCE hInst);

    BOOL Close()
    {
        return Animate_Close(m_hwnd);
    }

    BOOL IsPlaying()
    {
        return Animate_IsPlaying(m_hwnd);
    }

    BOOL Open(LPCTSTR lpszName)
    {
        return Animate_Open(m_hwnd, lpszName);
    }

    BOOL Open(LPCTSTR lpszName, HINSTANCE hInst)
    {
        return Animate_OpenEx(m_hwnd, hInst, lpszName);
    }

    BOOL Play(UINT wFrom, UINT wTo, UINT cRepeat)
    {
        return Animate_Play(m_hwnd, wFrom, wTo, cRepeat);
    }

    BOOL Seek(UINT wFrame)
    {
        return Animate_Seek(m_hwnd, wFrame);
    }

    BOOL Stop()
    {
        return Animate_Stop(m_hwnd);
    }

};

///////////////////////////////////////
// scroll bar

class TScrollBar : public TControl<TScrollBar>
{
public:

    TScrollBar()
    {
    }

    LPCTSTR GetClassName()
    {
        return TEXT("SCROLLBAR");
    }

public:

    BOOL EnableArrows(UINT flag)
    {
        return SendMessage(SBM_ENABLE_ARROWS, flag);
    }

    int GetPos()
    {
        return SendMessage(SBM_GETPOS);
    }

    void GetRange(int *pmin, int *pmax)
    {
        SendMessage(SBM_GETRANGE, (WPARAM) pmin, (LPARAM) pmax);
    }

    int GetScrollBarInfo(SCROLLBARINFO *ps)
    {
        return SendMessage(SBM_GETSCROLLBARINFO, 0, (LPARAM) ps);
    }

    BOOL GetScrollInfo(SCROLLINFO *ps)
    {
        return SendMessage(SBM_GETSCROLLINFO, (LPARAM) ps);
    }

    int SetPos(int pos, BOOL fRedraw = TRUE)
    {
        return SendMessage(SBM_GETSCROLLINFO, pos, fRedraw);
    }

    int SetRange(int min, int max)
    {
        return SendMessage(SBM_SETRANGE, min, max);
    }

    int SetRangeRedraw(int min, int max)
    {
        return SendMessage(SBM_SETRANGEREDRAW, min, max);
    }

    int SetScrollInfo(UINT flags, BOOL fRedraw = TRUE)
    {
        return SendMessage(SBM_SETSCROLLINFO, fRedraw, flags);
    }

};

////////////////////////////////////////////////////////////////////////////
// class TComCtl
// ref: http://msdn.microsoft.com/en-us/library/windows/desktop/bb773169(v=vs.85).aspx
//

template <class T>
class TComCtl : public TControl<T>
{
private:
    DWORD m_dwICC;

protected:

    virtual BOOL InitControl()
    {
        INITCOMMONCONTROLSEX icex;
        icex.dwSize = sizeof (INITCOMMONCONTROLSEX);
        icex.dwICC = m_dwICC;
        return InitCommonControlsEx(&icex);
    }

public:
    TComCtl(DWORD dwICC);

    BOOL Create(LPCTSTR lpWindowName,
                DWORD dwStyle, int x, int y, int width, int height,
                HWND hwndParent, UINT nID,
                HINSTANCE hInst);
    BOOL CreateEx(DWORD dwExStyle,
                  LPCTSTR lpWindowName,
                  DWORD dwStyle, int x, int y, int width, int height,
                  HWND hwndParent, UINT nID,
                  HINSTANCE hInst);
};

template <class T>
TComCtl<T>::TComCtl(DWORD dwICC)
: m_dwICC(dwICC)
{

}

template <class T>
BOOL TComCtl<T>::Create(LPCTSTR lpWindowName,
                        DWORD dwStyle, int x, int y, int width, int height,
                        HWND hwndParent, UINT nID,
                        HINSTANCE hInst)
{
    if (!InitControl()) return FALSE;

    return TControl<T>::Create(lpWindowName,
                               dwStyle, x, y, width, height,
                               hwndParent, nID, hInst);
}

template <class T>
BOOL TComCtl<T>::CreateEx(DWORD dwExStyle,
                          LPCTSTR lpWindowName,
                          DWORD dwStyle, int x, int y, int width, int height,
                          HWND hwndParent, UINT nID,
                          HINSTANCE hInst)
{
    if (!InitControl()) return FALSE;

    return TControl<T>::CreateEx(dwExStyle,
                                 lpWindowName, dwStyle, x, y, width, height,
                                 hwndParent, nID, hInst);
}


////////////////////////////////////////////////////////////////////////////
// class TComboBoxEx

class TComboBoxEx : public TComCtl<TComboBoxEx>
{
public:

    TComboBoxEx()
    : TComCtl<TComboBoxEx>(ICC_USEREX_CLASSES)
    {
    }

    LPCTSTR GetClassName()
    {
        return WC_COMBOBOXEX;
    }

    int DeleteItem(int nIndex)
    {
        return (int) SendMessage(CBEM_DELETEITEM, (WPARAM) nIndex);
    }

    HWND GetComboControl()
    {
        return (HWND) SendMessage(CBEM_GETCOMBOCONTROL);
    }

    HWND GetEditContro()
    {
        return (HWND) SendMessage(CBEM_GETEDITCONTROL);
    }

    DWORD GetExtendexStyle()
    {
        return (DWORD) SendMessage(CBEM_GETEXTENDEDSTYLE);
    }

    HIMAGELIST GetImageList()
    {
        return (HIMAGELIST) SendMessage(CBEM_GETIMAGELIST);
    }

    BOOL GetItem(COMBOBOXEXITEM *pItem)
    {
        return (BOOL) SendMessage(CBEM_GETITEM, 0, (LPARAM) pItem);
    }

    BOOL GetUnicodeFormat()
    {
        return (BOOL) SendMessage(CBEM_GETUNICODEFORMAT);
    }

    BOOL HasEditChanged()
    {
        return (BOOL) SendMessage(CBEM_HASEDITCHANGED);
    }

    int InsertItem(COMBOBOXEXITEM *pItem)
    {
        return (BOOL) SendMessage(CBEM_INSERTITEM, 0, (LPARAM) pItem);
    }

    DWORD SetExtendexStyle(DWORD dwExStyle, DWORD dwExStyleAffected = 0)
    {
        return (DWORD) SendMessage(CBEM_SETEXTENDEDSTYLE, dwExStyleAffected, dwExStyle);
    }

    HIMAGELIST SetImageList(HIMAGELIST hImg)
    {
        return (HIMAGELIST) SendMessage(CBEM_SETIMAGELIST, 0, (LPARAM) hImg);
    }

    BOOL SetItem(COMBOBOXEXITEM *pItem)
    {
        return (BOOL) SendMessage(CBEM_SETITEM, 0, (LPARAM) pItem);
    }

    BOOL SetUnicodeFormat(BOOL fUnicode = TRUE)
    {
        return (BOOL) SendMessage(CBEM_SETUNICODEFORMAT, (WPARAM) fUnicode);
    }

};

////////////////////////////////////////////////////////////////////////////
// class TDateTimePicker

class TDateTimePicker : public TComCtl<TDateTimePicker>
{
public:

    TDateTimePicker()
    : TComCtl<TDateTimePicker>(ICC_DATE_CLASSES)
    {
    }

    LPCTSTR GetClassName()
    {
        return DATETIMEPICK_CLASS;
    }

    // date time picker messages mapping

    LRESULT CloseMonthCal()
    {
        return DateTime_CloseMonthCal(m_hwnd);
    }

    LRESULT GetDateTimePickerInfo(DATETIMEPICKERINFO *pdtpi)
    {
        return DateTime_GetDateTimePickerInfo(m_hwnd, pdtpi);
    }

    BOOL GetIdealSize(SIZE *pSize)
    {
        return DateTime_GetIdealSize(m_hwnd, pSize);
    }

    HWND GetMonthCal()
    {
        return DateTime_GetMonthCal(m_hwnd);
    }

    COLORREF GetMonthCalColor(int flag)
    {
        return DateTime_GetMonthCalColor(m_hwnd, flag);
    }

    HFONT GetMonthCalFont()
    {
        return (HFONT) DateTime_GetMonthCalFont(m_hwnd);
    }

    DWORD GetMonthCalStyle()
    {
        return DateTime_GetMonthCalStyle(m_hwnd);
    }

    DWORD GetRange(LPSYSTEMTIME lpSysTimeArray)
    {
        return DateTime_GetRange(m_hwnd, lpSysTimeArray);
    }

    DWORD GetSystemTime(LPSYSTEMTIME lpSysTime)
    {
        return DateTime_GetSystemtime(m_hwnd, lpSysTime);
    }

    BOOL SetFormat(LPCTSTR lpszFormat)
    {
        return DateTime_SetFormat(m_hwnd, lpszFormat);
    }

    COLORREF SetMonthCalColor(int flag, COLORREF color)
    {
        return DateTime_SetMonthCalColor(m_hwnd, flag, color);
    }

    void SetMonthCalFont(HFONT hFont, BOOL fRedraw = TRUE)
    {
        DateTime_SetMonthCalFont(m_hwnd, hFont, fRedraw);
    }

    DWORD SetMonthCalStyle(DWORD dwStyle)
    {
        return DateTime_SetMonthCalStyle(m_hwnd, dwStyle);
    }

    BOOL SetRange(DWORD flags, LPSYSTEMTIME lpSysTimeArray)
    {
        return DateTime_SetRange(m_hwnd, flags, lpSysTimeArray);
    }

    BOOL SetSystemTime(DWORD flag, LPSYSTEMTIME lpSysTime)
    {
        return DateTime_SetSystemtime(m_hwnd, flag, lpSysTime);
    }


};

////////////////////////////////////////////////////////////////////////////
// class THeaderCtl

class THeaderCtl : public TComCtl<THeaderCtl>
{
public:

    THeaderCtl()
    : TComCtl<THeaderCtl>(ICC_LISTVIEW_CLASSES)
    {
    }

    LPCTSTR GetClassName()
    {
        return WC_HEADER;
    }

    int ClearFilter(int i)
    {
        return Header_ClearFilter(m_hwnd, i);
    }

    int ClearAllFilters()
    {
        return Header_ClearAllFilters(m_hwnd);
    }

    HIMAGELIST CreateDragImage(int index)
    {
        return Header_CreateDragImage(m_hwnd, index);
    }

    BOOL DeleteItem(int index)
    {
        return Header_DeleteItem(m_hwnd, index);
    }

    int EditFilter(int index, BOOL fDiscardChanges = TRUE)
    {
        return Header_EditFilter(m_hwnd, index, fDiscardChanges);
    }

    int GetBitmapMargin()
    {
        return Header_GetBitmapMargin(m_hwnd);
    }

    int GetFocusedItem()
    {
        return Header_GetFocusedItem(m_hwnd);
    }

    HIMAGELIST GetImageList()
    {
        return Header_GetImageList(m_hwnd);
    }

    BOOL GetItem(int index, LPHDITEM phdi)
    {
        return Header_GetItem(m_hwnd, index, phdi);
    }

    int GetItemCount()
    {
        return Header_GetItemCount(m_hwnd);
    }

    BOOL GetItemDropDownRect(int index, RECT *pRect)
    {
        return Header_GetItemDropDownRect(m_hwnd, index, pRect);
    }

    BOOL GetItemRect(int index, RECT *pRect)
    {
        return Header_GetItemRect(m_hwnd, index, pRect);
    }

    BOOL GetOrderArray(int size, int *piArr)
    {
        return Header_GetOrderArray(m_hwnd, size, piArr);
    }

    BOOL GetOverflowRect(RECT *prc)
    {
        return Header_GetOverflowRect(m_hwnd, prc);
    }

    HIMAGELIST GetStateImageList()
    {
        return Header_GetStateImageList(m_hwnd);
    }

    BOOL GetUnicodeFormat()
    {
        return Header_GetUnicodeFormat(m_hwnd);
    }

    int InsertItem(int index, const LPHDITEM phdi)
    {
        return Header_InsertItem(m_hwnd, index, phdi);
    }

    BOOL Layout(LPHDLAYOUT phdl)
    {
        return Header_Layout(m_hwnd, phdl);
    }

    int OrderToIndex(int order)
    {
        return Header_OrderToIndex(m_hwnd, order);
    }

    int SetBitmapMargin(int width)
    {
        return Header_SetBitmapMargin(m_hwnd, width);
    }

    int SetFilterChangeTimeout(int i)
    {
        return Header_SetFilterChangeTimeout(m_hwnd, i);
    }

    BOOL SetFocusedItem(int item)
    {
        return Header_SetFocusedItem(m_hwnd, item);
    }

    int SetHotDivider(BOOL flag, DWORD dwInputValue)
    {
        return Header_SetHotDivider(m_hwnd, flag, dwInputValue);
    }

    HIMAGELIST SetImageList(HIMAGELIST himl)
    {
        return Header_SetImageList(m_hwnd, himl);
    }

    BOOL SetItem(int index, LPHDITEM phdi)
    {
        return Header_SetItem(m_hwnd, index, phdi);
    }

    BOOL SetOrderArray(int size, int *piArr)
    {
        return Header_SetOrderArray(m_hwnd, size, piArr);
    }

    HIMAGELIST SetStateImageList(HIMAGELIST himl)
    {
        return Header_SetStateImageList(m_hwnd, himl);
    }

    BOOL SetUnicodeFormat(BOOL fUnicode = TRUE)
    {
        return Header_SetUnicodeFormat(m_hwnd, fUnicode);
    }


};

////////////////////////////////////////////////////////////////////////////
// class TIPAddressCtl

class TIPAddressCtl : public TComCtl<TIPAddressCtl>
{
public:

    TIPAddressCtl()
    : TComCtl<TIPAddressCtl>(ICC_INTERNET_CLASSES)
    {
    }

    LPCTSTR GetClassName()
    {
        return WC_IPADDRESS;
    }

    void ClearAddress()
    {
        SendMessage(IPM_CLEARADDRESS);
    }

    DWORD GetAddress(DWORD *pdwAddr)
    {
        return SendMessage(IPM_GETADDRESS, 0, (LPARAM) pdwAddr);
    }

    BOOL IsBlank()
    {
        return (BOOL) SendMessage(IPM_ISBLANK);
    }

    void SetAddress(DWORD dwAddr)
    {
        SendMessage(IPM_SETADDRESS, 0, (LPARAM) dwAddr);
    }

    void SetFocus(int index)
    {
        SendMessage(IPM_SETFOCUS, (WPARAM) index);
    }

    BOOL SetRange(int index, WORD wRange)
    {
        return SendMessage(IPM_SETRANGE, (WPARAM) index, (LPARAM) wRange);
    }
};

////////////////////////////////////////////////////////////////////////////
// class TMonthCalCtl

class TMonthCalCtl : public TComCtl<TMonthCalCtl>
{
public:

    TMonthCalCtl()
    : TComCtl<TMonthCalCtl>(ICC_DATE_CLASSES)
    {
    }

    LPCTSTR GetClassName()
    {
        return MONTHCAL_CLASS;
    }

    DWORD GetCalendarBorder()
    {
        return MonthCal_GetCalendarBorder(m_hwnd);
    }

    DWORD GetCalendarCount()
    {
        return MonthCal_GetCalendarCount(m_hwnd);
    }

    BOOL GetCalendarGridInfo(MCGRIDINFO *pmcgi)
    {
        return MonthCal_GetCalendarGridInfo(m_hwnd, pmcgi);
    }

    CALID GetCALID()
    {
        return MonthCal_GetCALID(m_hwnd);
    }

    COLORREF GetColor(int color)
    {
        return MonthCal_GetColor(m_hwnd, color);
    }

    DWORD GetCurrentView()
    {
        return MonthCal_GetCurrentView(m_hwnd);
    }

    BOOL GetCurSel(LPSYSTEMTIME lpst)
    {
        return MonthCal_GetCurSel(m_hwnd, lpst);
    }

    DWORD GetFirstDayOfWeek()
    {
        return MonthCal_GetFirstDayOfWeek(m_hwnd);
    }

    DWORD GetMaxSelCount()
    {
        return MonthCal_GetMaxSelCount(m_hwnd);
    }

    DWORD GetMaxTodayWidth()
    {
        return MonthCal_GetMaxTodayWidth(m_hwnd);
    }

    BOOL GetMinReqRect(LPRECT prc)
    {
        return MonthCal_GetMinReqRect(m_hwnd, prc);
    }

    int GetMonthDelta()
    {
        return MonthCal_GetMonthDelta(m_hwnd);
    }

    int GetMonthRange(DWORD dwFlag, LPSYSTEMTIME lpstArr)
    {
        return MonthCal_GetMonthRange(m_hwnd, dwFlag, lpstArr);
    }

    DWORD GetRange(LPSYSTEMTIME lpstArr)
    {
        return MonthCal_GetRange(m_hwnd, lpstArr);
    }

    BOOL GetSelRange(LPSYSTEMTIME lpstArr)
    {
        return MonthCal_GetSelRange(m_hwnd, lpstArr);
    }

    BOOL GetToday(LPSYSTEMTIME lpToday)
    {
        return MonthCal_GetToday(m_hwnd, lpToday);
    }

    BOOL GetUnicodeFormat()
    {
        return MonthCal_GetUnicodeFormat(m_hwnd);
    }

    DWORD HitTest(PMCHITTESTINFO pmchi)
    {
        return MonthCal_HitTest(m_hwnd, pmchi);
    }

    LRESULT SetCalendarBorder(BOOL fSet, int border)
    {
        return MonthCal_SetCalendarBorder(m_hwnd, fSet, border);
    }

    LRESULT SetCALID(UINT calid)
    {
        return MonthCal_SetCALID(m_hwnd, calid);
    }

    COLORREF SetColor(int i, COLORREF color)
    {
        return MonthCal_SetColor(m_hwnd, i, color);
    }

    BOOL SetCurrentView(DWORD dwNewView)
    {
        return MonthCal_SetCurrentView(m_hwnd, dwNewView);
    }

    BOOL SetCurSel(LPSYSTEMTIME lpst)
    {
        return MonthCal_SetCurSel(m_hwnd, lpst);
    }

    BOOL SetDayState(int months, LPMONTHDAYSTATE lpDays)
    {
        return MonthCal_SetDayState(m_hwnd, months, lpDays);
    }

    DWORD SetFirstDayOfWeek(int day)
    {
        return MonthCal_SetFirstDayOfWeek(m_hwnd, day);
    }

    BOOL SetMaxSelCount(UINT max)
    {
        return MonthCal_SetMaxSelCount(m_hwnd, max);
    }

    int SetMonthDelta(int delta)
    {
        return MonthCal_SetMonthDelta(m_hwnd, delta);
    }

    BOOL SetRange(DWORD dwWhichLimit, LPSYSTEMTIME lpstArr)
    {
        return MonthCal_SetRange(m_hwnd, dwWhichLimit, lpstArr);
    }

    BOOL SetSelRange(LPSYSTEMTIME lpstArr)
    {
        return MonthCal_SetSelRange(m_hwnd, lpstArr);
    }

    void SetToday(LPSYSTEMTIME lpst)
    {
        MonthCal_SetToday(m_hwnd, lpst);
    }

    BOOL SetUnicodeFormat(BOOL fUnicode = TRUE)
    {
        return MonthCal_SetUnicodeFormat(m_hwnd, fUnicode);
    }

    LRESULT SizeRectToMin(LPRECT prc)
    {
        return MonthCal_SizeRectToMin(m_hwnd, prc);
    }


};

////////////////////////////////////////////////////////////////////////////
// class TListViewCtl

class TListViewCtl : public TComCtl<TListViewCtl>
{
public:

    TListViewCtl()
    : TComCtl<TListViewCtl>(ICC_LISTVIEW_CLASSES)
    {
    }

    LPCTSTR GetClassName()
    {
        return WC_LISTVIEW;
    }

    DWORD ApproximateViewRect(int x, int y, int count)
    {
        return ListView_ApproximateViewRect(m_hwnd, x, y, count);
    }

    BOOL Arrange(UINT code)
    {
        return ListView_Arrange(m_hwnd, code);
    }

    void CancelEditLabel()
    {
        ListView_CancelEditLabel(m_hwnd);
    }

    HIMAGELIST CreateDragImage(int item, LPPOINT ptUL)
    {
        return ListView_CreateDragImage(m_hwnd, item, ptUL);
    }

    BOOL DeleteAllItems()
    {
        return ListView_DeleteAllItems(m_hwnd);
    }

    BOOL DeleteColumn(int col)
    {
        return ListView_DeleteColumn(m_hwnd, col);
    }

    BOOL DeleteItem(int item)
    {
        return ListView_DeleteItem(m_hwnd, item);
    }

    HWND EditLabel(int item)
    {
        return ListView_EditLabel(m_hwnd, item);
    }

    int EnableGroupView(BOOL fEnable = TRUE)
    {
        return ListView_EnableGroupView(m_hwnd, fEnable);
    }

    BOOL EnsureVisible(int item, BOOL fPartialOK = TRUE)
    {
        return ListView_EnsureVisible(m_hwnd, item, fPartialOK);
    }

    int FindItem(int start, const LVFINDINFO *plvfi)
    {
        return ListView_FindItem(m_hwnd, start, plvfi);
    }

    COLORREF GetBkColor()
    {
        return ListView_GetBkColor(m_hwnd);
    }

    BOOL GetBkImage(LVBKIMAGE *plvbki)
    {
        return ListView_GetBkImage(m_hwnd, plvbki);
    }

    UINT GetCallbackMask()
    {
        return ListView_GetCallbackMask(m_hwnd);
    }

    BOOL GetCheckState(UINT index)
    {
        return ListView_GetCheckState(m_hwnd, index);
    }

    BOOL GetColumn(int col, LVCOLUMN *pcol)
    {
        return ListView_GetColumn(m_hwnd, col, pcol);
    }

    BOOL GetColumnOrderArray(int count, int *piArr)
    {
        return ListView_GetColumnOrderArray(m_hwnd, count, piArr);
    }

    int GetColumnWidth(int col)
    {
        return ListView_GetColumnWidth(m_hwnd, col);
    }

    int GetCountPerPage()
    {
        return ListView_GetCountPerPage(m_hwnd);
    }

    HWND GetEditControl()
    {
        return ListView_GetEditControl(m_hwnd);
    }

    BOOL GetEmptyText(LPTSTR lpText, int cchMax)
    {
        return ListView_GetEmptyText(m_hwnd, lpText, cchMax);
    }

    DWORD GetExtendedListViewStyle()
    {
        return ListView_GetExtendedListViewStyle(m_hwnd);
    }

    int GetFocusedGroup()
    {
        return ListView_GetFocusedGroup(m_hwnd);
    }

    BOOL GetFooterInfo(LVFOOTERINFO *plvfi)
    {
        return ListView_GetFooterInfo(m_hwnd, plvfi);
    }

    BOOL GetFooterItem(int item, LVFOOTERITEM *pfi)
    {
        return ListView_GetFooterItem(m_hwnd, item, pfi);
    }

    BOOL GetFooterItemRect(int item, RECT *prc)
    {
        return ListView_GetFooterItemRect(m_hwnd, item, prc);
    }

    BOOL GetFooterRect(RECT *prc)
    {
        return ListView_GetFooterRect(m_hwnd, prc);
    }

    int GetGroupCount()
    {
        return ListView_GetGroupCount(m_hwnd);
    }

    HIMAGELIST GetGroupHeaderImageList()
    {
        return ListView_GetGroupHeaderImageList(m_hwnd);
    }

    int GetGroupInfo(int group, LVGROUP *pgrp)
    {
        return ListView_GetGroupInfo(m_hwnd, group, pgrp);
    }

    LRESULT GetGroupInfoByIndex(int index, LVGROUP *pgrp)
    {
        return ListView_GetGroupInfoByIndex(m_hwnd, index, pgrp);
    }

    void GetGroupMetrics(LVGROUPMETRICS *pgm)
    {
        ListView_GetGroupMetrics(m_hwnd, pgm);
    }

    BOOL GetGroupRect(int grp, long type, RECT *prc)
    {
        return ListView_GetGroupRect(m_hwnd, grp, type, prc);
    }

    UINT GetGroupState(UINT id, UINT mask)
    {
        return ListView_GetGroupState(m_hwnd, id, mask);
    }

    HWND GetHeader()
    {
        return ListView_GetHeader(m_hwnd);
    }

    HCURSOR GetHotCursor()
    {
        return ListView_GetHotCursor(m_hwnd);
    }

    int GetHotItem()
    {
        return ListView_GetHotItem(m_hwnd);
    }

    DWORD GetHoverTime()
    {
        return ListView_GetHoverTime(m_hwnd);
    }

    HIMAGELIST GetImageList(int i)
    {
        return ListView_GetImageList(m_hwnd, i);
    }

    BOOL GetInsertMark(LVINSERTMARK *pim)
    {
        return ListView_GetInsertMark(m_hwnd, pim);
    }

    COLORREF GetInsertMarkColor()
    {
        return ListView_GetInsertMarkColor(m_hwnd);
    }

    int GetInsertMarkRect(LPRECT prc)
    {
        return ListView_GetInsertMarkRect(m_hwnd, prc);
    }

    BOOL GetISearchString(LPTSTR lpString)
    {
        return ListView_GetISearchString(m_hwnd, lpString);
    }

    BOOL GetItem(LVITEM *pi)
    {
        return ListView_GetItem(m_hwnd, pi);
    }

    int GetItemCount()
    {
        return ListView_GetItemCount(m_hwnd);
    }

    BOOL GetItemIndexRect(LVITEMINDEX *pii, long subitem, long code, LPRECT prc)
    {
        return ListView_GetItemIndexRect(m_hwnd, pii, subitem, code, prc);
    }

    BOOL GetItemPosition(int i, POINT *ppt)
    {
        return ListView_GetItemPosition(m_hwnd, i, ppt);
    }

    BOOL GetItemRect(int i, RECT *prc, int code)
    {
        return ListView_GetItemRect(m_hwnd, i, prc, code);
    }

    DWORD GetItemSpacing(BOOL fSmall = TRUE)
    {
        return ListView_GetItemSpacing(m_hwnd, fSmall);
    }

    UINT GetItemState(int i, UINT mask)
    {
        return ListView_GetItemState(m_hwnd, i, mask);
    }

    void GetItemText(int item, int subitem, LPTSTR lpText, int cchMax)
    {
        ListView_GetItemText(m_hwnd, item, subitem, lpText, cchMax);
    }

    int GetNextItem(int start, UINT flags)
    {
        return ListView_GetNextItem(m_hwnd, start, flags);
    }

    BOOL GetNextItemIndex(LVITEMINDEX *pii, UINT flags)
    {
        return ListView_GetNextItemIndex(m_hwnd, pii, flags);
    }

    BOOL GetNumberOfWorkAreas(UINT *pWorkAreas)
    {
        return ListView_GetNumberOfWorkAreas(m_hwnd, pWorkAreas);
    }

    BOOL GetOrigin(POINT *ppt)
    {
        return ListView_GetOrigin(m_hwnd, ppt);
    }

    COLORREF GetOutlineColor()
    {
        return ListView_GetOutlineColor(m_hwnd);
    }

    UINT GetSelectedColumn()
    {
        return ListView_GetSelectedColumn(m_hwnd);
    }

    UINT GetSelectedCount()
    {
        return ListView_GetSelectedCount(m_hwnd);
    }

    int GetSelectionMark()
    {
        return ListView_GetSelectionMark(m_hwnd);
    }

    int GetStringWidth(LPCTSTR psz)
    {
        return ListView_GetStringWidth(m_hwnd, psz);
    }

    BOOL GetSubItemRect(int item, int subitem, int code, RECT *prc)
    {
        return ListView_GetSubItemRect(m_hwnd, item, subitem, code, prc);
    }

    COLORREF GetTextBkColor()
    {
        return ListView_GetTextBkColor(m_hwnd);
    }

    COLORREF GetTextColor()
    {
        return ListView_GetTextColor(m_hwnd);
    }

    void GetTileInfo(LVTILEINFO *pti)
    {
        ListView_GetTileInfo(m_hwnd, pti);
    }

    void GetTileViewInfo(LVTILEVIEWINFO *ptvi)
    {
        ListView_GetTileViewInfo(m_hwnd, ptvi);
    }

    HWND GetToolTips()
    {
        return ListView_GetToolTips(m_hwnd);
    }

    int GetTopIndex()
    {
        return ListView_GetTopIndex(m_hwnd);
    }

    BOOL GetUnicodeFormat()
    {
        return ListView_GetUnicodeFormat(m_hwnd);
    }

    DWORD GetView()
    {
        return ListView_GetView(m_hwnd);
    }

    BOOL GetViewRect(RECT *prc)
    {
        return ListView_GetViewRect(m_hwnd, prc);
    }

    void GetWorkAreas(int nWorkAreas, RECT *prc)
    {
        ListView_GetWorkAreas(m_hwnd, nWorkAreas, prc);
    }

    BOOL HasGroup(int grp)
    {
        return ListView_HasGroup(m_hwnd, grp);
    }

    int HitTest(LVHITTESTINFO *phi)
    {
        return ListView_HitTest(m_hwnd, phi);
    }

    int HitTestEx(LVHITTESTINFO *phi)
    {
        return ListView_HitTestEx(m_hwnd, phi);
    }

    int InsertColumn(int col, LVCOLUMN *pcol)
    {
        return ListView_InsertColumn(m_hwnd, col, pcol);
    }

    int InsertGroup(int index, LVGROUP *pgrp)
    {
        return ListView_InsertGroup(m_hwnd, index, pgrp);
    }

    void InsertGroupSorted(LVINSERTGROUPSORTED *pigs)
    {
        ListView_InsertGroupSorted(m_hwnd, pigs);
    }

    int InsertItem(const LVITEM *pi)
    {
        return ListView_InsertItem(m_hwnd, pi);
    }

    BOOL InsertMarkHitTest(POINT *ppt, LVINSERTMARK *pim)
    {
        return ListView_InsertMarkHitTest(m_hwnd, ppt, pim);
    }

    BOOL IsGroupViewEnabled()
    {
        return ListView_IsGroupViewEnabled(m_hwnd);
    }

    BOOL IsItemVisible(int index)
    {
        return ListView_IsItemVisible(m_hwnd, index);
    }

    UINT MapIDToIndex(UINT id)
    {
        return ListView_MapIDToIndex(m_hwnd, id);
    }

    UINT MapIndexToID(UINT index)
    {
        return ListView_MapIndexToID(m_hwnd, index);
    }

    BOOL RedrawItems(int first, int last)
    {
        return ListView_RedrawItems(m_hwnd, first, last);
    }

    void RemoveAllGroups()
    {
        ListView_RemoveAllGroups(m_hwnd);
    }

    int RemoveGroup(int grp)
    {
        return ListView_RemoveGroup(m_hwnd, grp);
    }

    BOOL Scroll(int dx, int dy)
    {
        return ListView_Scroll(m_hwnd, dx, dy);
    }

    BOOL SetBkColor(COLORREF clr)
    {
        return ListView_SetBkColor(m_hwnd, clr);
    }

    BOOL SetBkImage(LVBKIMAGE *pbi)
    {
        return ListView_SetBkImage(m_hwnd, pbi);
    }

    BOOL SetCallbackMask(UINT mask)
    {
        return ListView_SetCallbackMask(m_hwnd, mask);
    }

    void SetCheckState(UINT index, BOOL fCheck = TRUE)
    {
        ListView_SetCheckState(m_hwnd, index, fCheck);
    }

    BOOL SetColumn(int col, LVCOLUMN *pcol)
    {
        return ListView_SetColumn(m_hwnd, col, pcol);
    }

    BOOL SetColumnOrderArray(int cols, int *piArr)
    {
        return ListView_SetColumnOrderArray(m_hwnd, cols, piArr);
    }

    BOOL SetColumnWidth(int col, int cx)
    {
        return ListView_SetColumnWidth(m_hwnd, col, cx);
    }

    void SetExtendedListViewStyle(DWORD dwExStyle)
    {
        ListView_SetExtendedListViewStyle(m_hwnd, dwExStyle);
    }

    void SetExtendedListViewStyleEx(DWORD dwExStyle, DWORD mask)
    {
        ListView_SetExtendedListViewStyleEx(m_hwnd, dwExStyle, mask);
    }

    HIMAGELIST SetGroupHeaderImageList(HIMAGELIST himl)
    {
        return ListView_SetGroupHeaderImageList(m_hwnd, himl);
    }

    int SetGroupInfo(int grp, LVGROUP *pgrp)
    {
        return ListView_SetGroupInfo(m_hwnd, grp, pgrp);
    }

    void SetGroupMetrics(LVGROUPMETRICS *pgm)
    {
        ListView_SetGroupMetrics(m_hwnd, pgm);
    }

    void SetGroupState(UINT grp, UINT mask, UINT state)
    {
        ListView_SetGroupState(m_hwnd, grp, mask, state);
    }

    HCURSOR SetHotCursor(HCURSOR hcur)
    {
        return ListView_SetHotCursor(m_hwnd, hcur);
    }

    int SetHotItem(int index)
    {
        return ListView_SetHotItem(m_hwnd, index);
    }

    void SetHoverTime(DWORD dwHoverTime)
    {
        ListView_SetHoverTime(m_hwnd, dwHoverTime);
    }

    DWORD SetIconSpacing(int dx, int dy)
    {
        return ListView_SetIconSpacing(m_hwnd, dx, dy);
    }

    HIMAGELIST SetImageList(HIMAGELIST himl, int i)
    {
        return ListView_SetImageList(m_hwnd, himl, i);
    }

    BOOL SetInfoTip(LVSETINFOTIP *psit)
    {
        return ListView_SetInfoTip(m_hwnd, psit);
    }

    BOOL SetInsertMark(LVINSERTMARK *pim)
    {
        return ListView_SetInsertMark(m_hwnd, pim);
    }

    COLORREF SetInsertMarkColor(COLORREF clr)
    {
        return ListView_SetInsertMarkColor(m_hwnd, clr);
    }

    BOOL SetItem(const LVITEM *pi)
    {
        return ListView_SetItem(m_hwnd, pi);
    }

    void SetItemCount(int cItems)
    {
        ListView_SetItemCount(m_hwnd, cItems);
    }

    void SetItemCountEx(int cItems, DWORD flags)
    {
        ListView_SetItemCountEx(m_hwnd, cItems, flags);
    }

    void SetItemIndexState(LVITEMINDEX *pii, UINT data, UINT mask)
    {
        ListView_SetItemIndexState(m_hwnd, pii, data, mask);
    }

    BOOL SetItemPosition(int i, int x, int y)
    {
        return ListView_SetItemPosition(m_hwnd, i, x, y);
    }

    void SetItemPosition32(int i, int x, int y)
    {
        ListView_SetItemPosition32(m_hwnd, i, x, y);
    }

    void SetItemState(int i, int state, int mask)
    {
        ListView_SetItemState(m_hwnd, i, state, mask);
    }

    void SetItemText(int i, int sub, LPTSTR pText)
    {
        ListView_SetItemText(m_hwnd, i, sub, pText);
    }

    COLORREF SetOutlineColor(COLORREF clr)
    {
        return ListView_SetOutlineColor(m_hwnd, clr);
    }

    void SetSelectedColumn(int col)
    {
        ListView_SetSelectedColumn(m_hwnd, col);
    }

    int SetSelectionMark(int index)
    {
        return ListView_SetSelectionMark(m_hwnd, index);
    }

    BOOL SetTextBkColor(COLORREF clr)
    {
        return ListView_SetTextBkColor(m_hwnd, clr);
    }

    BOOL SetTextColor(COLORREF clr)
    {
        return ListView_SetTextColor(m_hwnd, clr);
    }

    BOOL SetTileInfo(LVTILEINFO *pti)
    {
        return ListView_SetTileInfo(m_hwnd, pti);
    }

    BOOL SetTileViewInfo(LVTILEVIEWINFO *ptvi)
    {
        return ListView_SetTileViewInfo(m_hwnd, ptvi);
    }

    HWND SetToolTips(HWND hwndTT)
    {
        return ListView_SetToolTips(m_hwnd, hwndTT);
    }

    BOOL SetUnicodeFormat(BOOL fUnicode = TRUE)
    {
        return ListView_SetUnicodeFormat(m_hwnd, fUnicode);
    }

    int SetView(DWORD view)
    {
        return ListView_SetView(m_hwnd, view);
    }

    void SetWorkAreas(int nWorkAreas, RECT *prc)
    {
        ListView_SetWorkAreas(m_hwnd, nWorkAreas, prc);
    }

    int SortGroups(PFNLVGROUPCOMPARE pfn, void* pv)
    {
        return ListView_SortGroups(m_hwnd, pfn, pv);
    }

    BOOL SortItems(PFNLVCOMPARE pfn, LPARAM pv)
    {
        return ListView_SortItems(m_hwnd, pfn, pv);
    }

    BOOL SortItemsEx(PFNLVCOMPARE pfn, LPARAM pv)
    {
        return ListView_SortItemsEx(m_hwnd, pfn, pv);
    }

    int SubItemHitTest(LVHITTESTINFO *phi)
    {
        return ListView_SubItemHitTest(m_hwnd, phi);
    }

    int SubItemHitTestEx(LVHITTESTINFO *phi)
    {
        return ListView_SubItemHitTestEx(m_hwnd, phi);
    }

    BOOL Update(int item)
    {
        return ListView_Update(m_hwnd, item);
    }

};

////////////////////////////////////////////////////////////////////////////
// class TProgressBarCtl

class TProgressBarCtl : public TComCtl<TProgressBarCtl>
{
public:

    TProgressBarCtl()
    : TComCtl<TProgressBarCtl>(ICC_PROGRESS_CLASS)
    {
    }

    LPCTSTR GetClassName()
    {
        return PROGRESS_CLASS;
    }

    int DeltaPos(int pos)
    {
        return SendMessage(PBM_DELTAPOS, pos);
    }

    COLORREF GetBarColor()
    {
        return (COLORREF) SendMessage(PBM_GETBARCOLOR);
    }

    COLORREF GetBkColor()
    {
        return (COLORREF) SendMessage(PBM_GETBKCOLOR);
    }

    UINT GetPos()
    {
        return SendMessage(PBM_GETPOS);
    }

    int GetRange(BOOL fLow, PBRANGE *pr = NULL)
    {
        return SendMessage(PBM_GETRANGE, (WPARAM) fLow, (LPARAM) pr);
    }

    int GetState()
    {
        return SendMessage(PBM_GETSTATE);
    }

    int GetStep()
    {
        return SendMessage(PBM_GETSTEP);
    }

    COLORREF SetBarColor(COLORREF clr)
    {
        return (COLORREF) SendMessage(PBM_SETBARCOLOR, 0, (LPARAM) clr);
    }

    COLORREF SetBkColor(COLORREF clr)
    {
        return (COLORREF) SendMessage(PBM_SETBKCOLOR, 0, (LPARAM) clr);
    }

    BOOL SetMarquee(BOOL bOn = TRUE, DWORD dwUpdate = 0)
    {
        return (BOOL) SendMessage(PBM_SETMARQUEE, (WPARAM) bOn, (LPARAM) dwUpdate);
    }

    UINT SetPos(UINT pos)
    {
        return SendMessage(PBM_SETPOS, pos);
    }

    int SetRange(UINT low = 0, UINT high = 100)
    {
        return SendMessage(PBM_SETRANGE, 0, MAKELPARAM(low, high));
    }

    int SetRange32(UINT low = 0, UINT high = 100)
    {
        return SendMessage(PBM_SETRANGE32, low, high);
    }

    int SetState(int state)
    {
        return SendMessage(PBM_SETSTATE, state);
    }

    int SetStep(int step)
    {
        return SendMessage(PBM_SETSTEP, step);
    }

    int StepIt()
    {
        return SendMessage(PBM_STEPIT);
    }

};

////////////////////////////////////////////////////////////////////////////
// class TStatusBarCtl

class TStatusBarCtl : public TComCtl<TStatusBarCtl>
{
public:

    TStatusBarCtl()
    : TComCtl<TStatusBarCtl>(ICC_BAR_CLASSES)
    {
    }

    virtual BOOL InitControl()
    {
        InitCommonControls();
        return TRUE;
    }

    LPCTSTR GetClassName()
    {
        return STATUSCLASSNAME;
    }

    BOOL GetBorders(int *pw)
    {
        return SendMessage(SB_GETBORDERS, 0, (LPARAM) pw);
    }

    HICON GetIcon(int index)
    {
        return (HICON) SendMessage(SB_GETICON, index);
    }

    int GetParts(int nParts, int *pi)
    {
        return SendMessage(SB_GETPARTS, nParts, (LPARAM) pi);
    }

    BOOL GetRect(int index, RECT *prc)
    {
        return SendMessage(SB_GETRECT, index, (LPARAM) prc);
    }

    int GetText(int index, LPTSTR pText)
    {
        return SendMessage(SB_GETTEXT, index, (LPARAM) pText);
    }

    int GetTextLength(int index)
    {
        return SendMessage(SB_GETTEXTLENGTH, index);
    }

    void GetTipText(int index, int cchMax, LPTSTR pTip)
    {
        SendMessage(SB_GETTIPTEXT, MAKEWPARAM(index, cchMax), (LPARAM) pTip);
    }

    BOOL GetUnicodeFormat()
    {
        return SendMessage(SB_GETUNICODEFORMAT);
    }

    BOOL IsSimple()
    {
        return SendMessage(SB_ISSIMPLE);
    }

    COLORREF GetBkColor(COLORREF clr)
    {
        return (COLORREF) SendMessage(SB_SETBKCOLOR, 0, (LPARAM) clr);
    }

    BOOL SetIcon(int index, HICON hicon)
    {
        return SendMessage(SB_SETICON, index, (LPARAM) hicon);
    }

    void SetMinHeight(int cy)
    {
        SendMessage(SB_SETMINHEIGHT, cy);
    }

    BOOL SetParts(int nParts, int *pi)
    {
        return SendMessage(SB_SETPARTS, nParts, (LPARAM) pi);
    }

    BOOL SetText(int index, int flag, LPCTSTR pText)
    {
        return SendMessage(SB_SETTEXT, MAKEWPARAM(index, flag), (LPARAM) pText);
    }

    void SetTipText(int index, LPCTSTR pTip)
    {
        SendMessage(SB_SETTIPTEXT, index, (LPARAM) pTip);
    }

    BOOL SetUnicodeFormat(BOOL fUnicode = TRUE)
    {
        SendMessage(SB_SETUNICODEFORMAT, fUnicode);
    }

    void Simple(BOOL fSimple = TRUE)
    {
        SendMessage(SB_SIMPLE, fSimple);
    }

};

////////////////////////////////////////////////////////////////////////////
// class TToolbarCtl

class TToolbarCtl : public TComCtl<TToolbarCtl>
{
public:

    TToolbarCtl()
    : TComCtl<TToolbarCtl>(ICC_BAR_CLASSES)
    {
    }

    virtual BOOL InitControl()
    {
        InitCommonControls();
        return TRUE;
    }

    LPCTSTR GetClassName()
    {
        return TOOLBARCLASSNAME;
    }

    int AddBitmap(int nSize, TBADDBITMAP *ptb)
    {
        return SendMessage(TB_ADDBITMAP, nSize, (LPARAM) ptb);
    }

    BOOL AddButtons(int nSize, TBBUTTON *ptb)
    {
        return SendMessage(TB_ADDBUTTONS, nSize, (LPARAM) ptb);
    }

    int AddString(HINSTANCE hinst, UINT nID)
    {
        return SendMessage(TB_ADDSTRING, (WPARAM) hinst, (LPARAM) nID);
    }

    int AddString(LPCTSTR pString)
    {
        return SendMessage(TB_ADDSTRING, (WPARAM) NULL, (LPARAM) pString);
    }

    int AutoSize()
    {
        return SendMessage(TB_AUTOSIZE);
    }

    int ButtonCount()
    {
        return SendMessage(TB_BUTTONCOUNT);
    }

    void ButtonStructSize(int size)
    {
        SendMessage(TB_BUTTONSTRUCTSIZE, size);
    }

    BOOL ChangeBitmap(UINT nID, int index)
    {
        return SendMessage(TB_CHANGEBITMAP, nID, index);
    }

    BOOL CheckButton(UINT nID, BOOL fCheck = TRUE)
    {
        return SendMessage(TB_CHECKBUTTON, nID, MAKELPARAM(fCheck, 0));
    }

    int CommandToIndex(UINT nID)
    {
        return SendMessage(TB_COMMANDTOINDEX, nID);
    }

    void Customize()
    {
        SendMessage(TB_CUSTOMIZE);
    }

    BOOL DeleteButton(int index)
    {
        return SendMessage(TB_DELETEBUTTON, index);
    }

    BOOL EnableButton(int index, BOOL fEnable = TRUE)
    {
        return SendMessage(TB_ENABLEBUTTON, index, MAKELPARAM(fEnable, 0));
    }

    BOOL GetAnchorHighlight()
    {
        return SendMessage(TB_GETANCHORHIGHLIGHT);
    }

    int GetBitmap(UINT nID)
    {
        return SendMessage(TB_GETBITMAP, nID);
    }

    DWORD GetBitmapFlags()
    {
        return SendMessage(TB_GETBITMAPFLAGS);
    }

    BOOL GetButton(int index, TBBUTTON *ptb)
    {
        return SendMessage(TB_GETBUTTON, index, (LPARAM) ptb);
    }

    int GetButtonInfo(UINT nID, TBBUTTONINFO *ptbi)
    {
        return SendMessage(TB_GETBUTTONINFO, nID, (LPARAM) ptbi);
    }

    DWORD GetButtonSize()
    {
        return SendMessage(TB_GETBUTTONSIZE);
    }

    int GetButtonText(UINT nID, LPTSTR pText)
    {
        return SendMessage(TB_GETBUTTONTEXT, nID, (LPARAM) pText);
    }

    int GetColorScheme(COLORSCHEME *pcs)
    {
        return SendMessage(TB_GETCOLORSCHEME, 0, (LPARAM) pcs);
    }

    HIMAGELIST GetDisabledImageList()
    {
        return (HIMAGELIST) SendMessage(TB_GETDISABLEDIMAGELIST);
    }

    DWORD GetExtendedStyle()
    {
        return SendMessage(TB_GETEXTENDEDSTYLE);
    }

    HIMAGELIST GetHotImageList()
    {
        return (HIMAGELIST) SendMessage(TB_GETHOTIMAGELIST);
    }

    int GetHotItem()
    {
        return SendMessage(TB_GETHOTITEM);
    }

    BOOL GetIdealSize(BOOL fHeight, SIZE *psz)
    {
        return SendMessage(TB_GETIDEALSIZE, (WPARAM) fHeight, (LPARAM) psz);
    }

    HIMAGELIST GetImageList()
    {
        return (HIMAGELIST) SendMessage(TB_GETIMAGELIST);
    }

    int GetImageListCount()
    {
        return SendMessage(TB_GETIMAGELISTCOUNT);
    }

    BOOL GetInsertMark(TBINSERTMARK *ptb)
    {
        return SendMessage(TB_GETINSERTMARK, 0, (LPARAM) ptb);
    }

    COLORREF GetInsertMarkColor()
    {
        return (COLORREF) SendMessage(TB_GETINSERTMARKCOLOR);
    }

    int GetItemDropDownRect(int index, RECT *prc)
    {
        return SendMessage(TB_GETITEMDROPDOWNRECT, index, (LPARAM) prc);
    }

    BOOL GetItemRect(int index, RECT *prc)
    {
        return SendMessage(TB_GETITEMRECT, index, (LPARAM) prc);
    }

    int GetMaxSize(SIZE *psz)
    {
        return SendMessage(TB_GETMAXSIZE, 0, (LPARAM) psz);
    }

    void GetMetrics(TBMETRICS *ptb)
    {
        SendMessage(TB_GETMETRICS, 0, (LPARAM) ptb);
    }
    //#ifdef USE_OLEIDL_H
    // HRESULT GetObject(void **ppDropTarget)
    // { return SendMessage(TB_GETOBJECT, IID_IDropTarget, (LPARAM)ppDropTarget);
    //#endif // USE_OLEIDL_H

    DWORD GetPadding()
    {
        return SendMessage(TB_GETPADDING);
    }

    HIMAGELIST GetPressedImageList()
    {
        return (HIMAGELIST) SendMessage(TB_GETPRESSEDIMAGELIST);
    }

    int GetRect(UINT nID, RECT *prc)
    {
        return SendMessage(TB_GETRECT, nID, (LPARAM) prc);
    }

    int GetRows()
    {
        return SendMessage(TB_GETROWS);
    }

    int GetState(UINT nID)
    {
        return SendMessage(TB_GETSTATE, nID);
    }

    int GetString(int index, int cchMax, LPTSTR pString)
    {
        return SendMessage(TB_GETSTRING, MAKEWPARAM(cchMax, index), (LPARAM) pString);
    }

    DWORD GetStyle()
    {
        return SendMessage(TB_GETSTYLE);
    }

    int GetTextRows()
    {
        return SendMessage(TB_GETTEXTROWS);
    }

    HWND GetToolTips()
    {
        return (HWND) SendMessage(TB_GETTOOLTIPS);
    }

    BOOL GetUnicodeFormat()
    {
        return SendMessage(TB_GETUNICODEFORMAT);
    }

    BOOL HideButton(UINT nID, BOOL fHide = TRUE)
    {
        return SendMessage(TB_HIDEBUTTON, nID, MAKELPARAM(fHide, 0));
    }

    int HitTest(POINT *ppt)
    {
        return SendMessage(TB_HITTEST, 0, (LPARAM) ppt);
    }

    BOOL Indeterminate(UINT nID, BOOL fIndeterminate = TRUE)
    {
        return SendMessage(TB_INDETERMINATE, nID, MAKELPARAM(fIndeterminate, 0));
    }

    BOOL InsertButton(int index, TBBUTTON *ptb)
    {
        return SendMessage(TB_INSERTBUTTON, index, (LPARAM) ptb);
    }

    int InsertMarkHitTest(POINT *ppt, TBINSERTMARK *ptb)
    {
        return SendMessage(TB_INSERTMARKHITTEST, (WPARAM) ppt, (LPARAM) ptb);
    }

    BOOL IsButtonChecked(UINT nID)
    {
        return SendMessage(TB_ISBUTTONCHECKED, nID);
    }

    BOOL IsButtonEnabled(UINT nID)
    {
        return SendMessage(TB_ISBUTTONENABLED, nID);
    }

    BOOL IsButtonHidden(UINT nID)
    {
        return SendMessage(TB_ISBUTTONHIDDEN, nID);
    }

    BOOL IsButtonHighlighted(UINT nID)
    {
        return SendMessage(TB_ISBUTTONHIGHLIGHTED, nID);
    }

    BOOL IsButtonIndeterminate(UINT nID)
    {
        return SendMessage(TB_ISBUTTONINDETERMINATE, nID);
    }

    BOOL IsButtonPressed(UINT nID)
    {
        return SendMessage(TB_ISBUTTONPRESSED, nID);
    }

    int LoadImages(int flag)
    {
        return SendMessage(TB_LOADIMAGES, flag, (LPARAM) HINST_COMMCTRL);
    }

    int MarkButton(UINT nID, BOOL fMark = TRUE)
    {
        return SendMessage(TB_MARKBUTTON, nID, MAKELPARAM(fMark, 0));
    }

    int MoveButton(int from, int to)
    {
        return SendMessage(TB_MOVEBUTTON, from, to);
    }

    int PressButton(UINT nID, BOOL fPress = TRUE)
    {
        return SendMessage(TB_PRESSBUTTON, nID, MAKELPARAM(fPress, 0));
    }

    int ReplaceBitmap(TBREPLACEBITMAP *ptb)
    {
        return SendMessage(TB_REPLACEBITMAP, 0, (LPARAM) ptb);
    }

    void Save(TBSAVEPARAMS *ptb)
    {
        SendMessage(TB_SAVERESTORE, (WPARAM) TRUE, (LPARAM) ptb);
    }

    void Restore(TBSAVEPARAMS *ptb)
    {
        SendMessage(TB_SAVERESTORE, (WPARAM) FALSE, (LPARAM) ptb);
    }

    BOOL SetAnchorHighlight(BOOL bSet = TRUE)
    {
        return SendMessage(TB_SETANCHORHIGHLIGHT, bSet);
    }

    BOOL SetBitmapSize(int cx, int cy)
    {
        return SendMessage(TB_SETBITMAPSIZE, 0, MAKELPARAM(cx, cy));
    }

    int SetButtonInfo(UINT nID, TBBUTTONINFO *ptb)
    {
        return SendMessage(TB_SETBUTTONINFO, nID, (LPARAM) ptb);
    }

    BOOL SetButtonSize(int cx, int cy)
    {
        return SendMessage(TB_SETBUTTONSIZE, 0, MAKELPARAM(cx, cy));
    }

    int SetButtonWidth(int min, int max)
    {
        return SendMessage(TB_SETBUTTONWIDTH, 0, MAKELPARAM(min, max));
    }

    BOOL SetCmdID(int index, UINT nID)
    {
        return SendMessage(TB_SETCMDID, index, nID);
    }

    void SetColorScheme(COLORSCHEME *pcs)
    {
        SendMessage(TB_SETCOLORSCHEME, 0, (LPARAM) pcs);
    }

    HIMAGELIST SetDisabledImageList(HIMAGELIST himl)
    {
        return (HIMAGELIST) SendMessage(TB_SETDISABLEDIMAGELIST, 0, (LPARAM) himl);
    }

    UINT SetDrawTextFlags(UINT turnOffFlags, UINT drawingFlags)
    {
        return SendMessage(TB_SETDRAWTEXTFLAGS, turnOffFlags, drawingFlags);
    }

    DWORD SetExtendedStyle(DWORD dwNewStyle)
    {
        return SendMessage(TB_SETEXTENDEDSTYLE, 0, dwNewStyle);
    }

    HIMAGELIST SetHotImageList(HIMAGELIST himl)
    {
        return (HIMAGELIST) SendMessage(TB_SETHOTIMAGELIST, 0, (LPARAM) himl);
    }

    int SetHotItem(int index)
    {
        return SendMessage(TB_SETHOTITEM, index);
    }

    int SetHotItem2(int index, UINT flags)
    {
        return SendMessage(TB_SETHOTITEM2, index, flags);
    }

    HIMAGELIST SetImageList(HIMAGELIST himl)
    {
        return (HIMAGELIST) SendMessage(TB_SETIMAGELIST, 0, (LPARAM) himl);
    }

    int SetIndent(int cx)
    {
        return SendMessage(TB_SETINDENT, cx);
    }

    void SetInsertMark(TBINSERTMARK *ptb)
    {
        SendMessage(TB_SETINSERTMARK, 0, (LPARAM) ptb);
    }

    COLORREF SetInsertMarkColor(COLORREF clr)
    {
        return (COLORREF) SendMessage(TB_SETINSERTMARKCOLOR, 0, (LPARAM) clr);
    }

    void SetListGap(int gap)
    {
        SendMessage(TB_SETLISTGAP, gap);
    }

    int SetMaxTextRows(int rows)
    {
        return SendMessage(TB_SETMAXTEXTROWS, rows);
    }

    void SetMetrics(TBMETRICS *ptb)
    {
        SendMessage(TB_SETMETRICS, 0, (LPARAM) ptb);
    }

    DWORD SetPadding(int cx, int cy)
    {
        return SendMessage(TB_SETPADDING, 0, MAKELPARAM(cx, cy));
    }

    HWND SetParent(HWND hwndP)
    {
        return (HWND) SendMessage(TB_SETPARENT, 0, (LPARAM) hwndP);
    }

    HIMAGELIST SetPressedImageList(HIMAGELIST himl)
    {
        return (HIMAGELIST) SendMessage(TB_SETPRESSEDIMAGELIST, 0, (LPARAM) himl);
    }

    void SetRows(int rows, BOOL fCreate, RECT *prc)
    {
        SendMessage(TB_SETROWS, MAKEWPARAM(rows, fCreate), (LPARAM) prc);
    }

    void SetState(UINT nID, UINT flags)
    {
        SendMessage(TB_SETSTATE, nID, MAKELPARAM(flags, 0));
    }

    void SetStyle(DWORD dwStyle)
    {
        SendMessage(TB_SETSTYLE, 0, dwStyle);
    }

    void SetToolTips(HWND hwndTT)
    {
        SendMessage(TB_SETTOOLTIPS, (WPARAM) hwndTT);
    }

    BOOL SetUnicodeFormat(BOOL bUnicode = TRUE)
    {
        return SendMessage(TB_SETUNICODEFORMAT, bUnicode);
    }

    void SetWindowTheme(LPCTSTR pTheme)
    {
        SendMessage(TB_SETWINDOWTHEME, 0, (LPARAM) pTheme);
    }



};

////////////////////////////////////////////////////////////////////////////
// class TUpDownCtl

class TUpDownCtl : public TComCtl<TUpDownCtl>
{
public:

    TUpDownCtl()
    : TComCtl<TUpDownCtl>(ICC_UPDOWN_CLASS)
    {
    }

    LPCTSTR GetClassName()
    {
        return UPDOWN_CLASS;
    }

    int GetAccel(int size, UDACCEL *pud)
    {
        return SendMessage(UDM_GETACCEL, size, (LPARAM) pud);
    }

    int GetBase()
    {
        return SendMessage(UDM_GETBASE);
    }

    HWND GetBuddy()
    {
        return (HWND) SendMessage(UDM_GETBUDDY);
    }

    int GetPos(int *pPos)
    {
        DWORD dw = SendMessage(UDM_GETPOS);
        *pPos = LOWORD(dw);
        return HIWORD(dw);
    }

    DWORD GetPos32(BOOL *pb)
    {
        return SendMessage(UDM_GETPOS32, 0, (LPARAM) pb);
    }

    DWORD GetRange(int *pmin, int *pmax)
    {
        DWORD dw = SendMessage(UDM_GETRANGE);
        *pmin = HIWORD(dw);
        *pmax = LOWORD(dw);
        return dw;
    }

    void GetRange32(int *pmin, int *pmax)
    {
        SendMessage(UDM_GETRANGE32, (WPARAM) pmin, (LPARAM) pmax);
    }

    BOOL GetUnicodeFormat()
    {
        return SendMessage(UDM_GETUNICODEFORMAT);
    }

    BOOL SetAccel(int size, UDACCEL *pud)
    {
        return SendMessage(UDM_SETACCEL, size, (LPARAM) pud);
    }

    int SetBase(int base = 10)
    {
        return SendMessage(UDM_SETBASE, base);
    }

    HWND SetBuddy(HWND hwndB)
    {
        return (HWND) SendMessage(UDM_SETBUDDY, (LPARAM) hwndB);
    }

    int SetPos(int pos)
    {
        return SendMessage(UDM_SETPOS, 0, pos);
    }

    int SetPos32(int pos)
    {
        return SendMessage(UDM_SETPOS32, 0, pos);
    }

    void SetRange(int min, int max)
    {
        SendMessage(UDM_SETRANGE, 0, MAKELPARAM(max, min));
    }

    void SetRange32(int min, int max)
    {
        SendMessage(UDM_SETRANGE32, min, max);
    }

    BOOL SetUnicodeFormat(BOOL fUnicode = TRUE)
    {
        return SendMessage(UDM_SETUNICODEFORMAT, fUnicode);
    }

};

////////////////////////////////////////////////////////////////////////////
// class TTrackbarCtl

class TTrackbarCtl : public TComCtl<TTrackbarCtl>
{
public:

    TTrackbarCtl()
    : TComCtl<TTrackbarCtl>(ICC_BAR_CLASSES)
    {
    }

    virtual BOOL InitControl()
    {
        InitCommonControls();
        return TRUE;
    }

    LPCTSTR GetClassName()
    {
        return TRACKBAR_CLASS;
    }

    void ClearSel(BOOL fClear = TRUE)
    {
        SendMessage(TBM_CLEARSEL, fClear);
    }

    void ClearTics(BOOL fClear = TRUE)
    {
        SendMessage(TBM_CLEARTICS, fClear);
    }

    HWND GetBuddy(BOOL fVert = TRUE)
    {
        return (HWND) SendMessage(TBM_GETBUDDY, fVert);
    }

    void GetChannelRect(RECT *prc)
    {
        SendMessage(TBM_GETCHANNELRECT, 0, (LPARAM) prc);
    }

    int GetLineSize()
    {
        return SendMessage(TBM_GETLINESIZE);
    }

    int GetNumTics()
    {
        return SendMessage(TBM_GETNUMTICS);
    }

    int GetPageSize()
    {
        return SendMessage(TBM_GETPAGESIZE);
    }

    int GetPos()
    {
        return SendMessage(TBM_GETPOS);
    }

    DWORD *GetPTics()
    {
        return (DWORD*) SendMessage(TBM_GETPTICS);
    }

    int GetRangeMax()
    {
        return SendMessage(TBM_GETRANGEMAX);
    }

    int GetRangeMin()
    {
        return SendMessage(TBM_GETRANGEMIN);
    }

    int GetSelEnd()
    {
        return SendMessage(TBM_GETSELEND);
    }

    int GetSelStart()
    {
        return SendMessage(TBM_GETSELSTART);
    }

    int GetThumbLength()
    {
        return SendMessage(TBM_GETTHUMBLENGTH);
    }

    void GetThumbRect(RECT *prc)
    {
        SendMessage(TBM_GETTHUMBRECT, 0, (LPARAM) prc);
    }

    int GetTic(int tic)
    {
        return SendMessage(TBM_GETTIC, tic);
    }

    int GetTicPos(int tic)
    {
        return SendMessage(TBM_GETTICPOS, tic);
    }

    HWND GetToolTips()
    {
        return (HWND) SendMessage(TBM_GETTOOLTIPS);
    }

    BOOL GetUnicodeFormat()
    {
        return SendMessage(TBM_GETUNICODEFORMAT);
    }

    HWND SetBuddy(BOOL fVert, HWND hwndB)
    {
        return (HWND) SendMessage(TBM_SETBUDDY, fVert, (LPARAM) hwndB);
    }

    int SetLineSize(int size)
    {
        return SendMessage(TBM_SETLINESIZE, 0, size);
    }

    int SetPageSize(int size)
    {
        return SendMessage(TBM_SETPAGESIZE, 0, size);
    }

    void SetPos(int pos, BOOL fRedraw = TRUE)
    {
        SendMessage(TBM_SETPOS, fRedraw, pos);
    }

    void SetPosNotify(int pos)
    {
        SendMessage(TBM_SETPOSNOTIFY, 0, pos);
    }

    void SetRange(int min, int max, BOOL fRedraw = TRUE)
    {
        SendMessage(TBM_SETRANGE, fRedraw, MAKELPARAM(min, max));
    }

    void SetRangeMax(int max, BOOL fRedraw = TRUE)
    {
        SendMessage(TBM_SETRANGEMAX, fRedraw, max);
    }

    void SetRangeMin(int min, BOOL fRedraw = TRUE)
    {
        SendMessage(TBM_SETRANGEMIN, fRedraw, min);
    }

    void SetSel(int start, int end, BOOL fRedraw = TRUE)
    {
        SendMessage(TBM_SETSEL, fRedraw, MAKELPARAM(start, end));
    }

    void SetSelEnd(int end, BOOL fRedraw = TRUE)
    {
        SendMessage(TBM_SETSELEND, fRedraw, end);
    }

    void SetSelStart(int start, BOOL fRedraw = TRUE)
    {
        SendMessage(TBM_SETSEL, fRedraw, start);
    }

    void SetThumbLength(int len)
    {
        SendMessage(TBM_SETTHUMBLENGTH, len);
    }

    BOOL SetTic(int tic)
    {
        return SendMessage(TBM_SETTIC, 0, tic);
    }

    void SetTicFreq(int freq)
    {
        SendMessage(TBM_SETTICFREQ, freq);
    }

    int SetTipSide(int tip)
    {
        return SendMessage(TBM_SETTIPSIDE, tip);
    }

    HWND SetToolTips(HWND hwndTT)
    {
        return (HWND) SendMessage(TBM_SETTOOLTIPS, (WPARAM) hwndTT);
    }

    BOOL SetUnicodeFormat(BOOL fUnicode = TRUE)
    {
        return SendMessage(TBM_SETUNICODEFORMAT, fUnicode);
    }


};

////////////////////////////////////////////////////////////////////////////
// class TToolTipCtl

class TToolTipCtl : public TComCtl<TToolTipCtl>
{
public:

    TToolTipCtl()
    : TComCtl<TToolTipCtl>(ICC_BAR_CLASSES)
    {
    }

    virtual BOOL InitControl()
    {
        InitCommonControls();
        return TRUE;
    }

    LPCTSTR GetClassName()
    {
        return TOOLTIPS_CLASS;
    }

    void Activate(BOOL fActivate = TRUE)
    {
        SendMessage(TTM_ACTIVATE, fActivate);
    }

    BOOL AddTool(TOOLINFO *pti)
    {
        return SendMessage(TTM_ADDTOOL, 0, (LPARAM) pti);
    }

    int AdjustRect(BOOL fOperation, RECT *prc)
    {
        return SendMessage(TTM_ADJUSTRECT, fOperation, (LPARAM) prc);
    }

    void DelTool(TOOLINFO *pti)
    {
        SendMessage(TTM_DELTOOL, 0, (LPARAM) pti);
    }

    BOOL EnumTools(int index, TOOLINFO *pti)
    {
        return SendMessage(TTM_ENUMTOOLS, index, (LPARAM) pti);
    }

    BOOL GetBubbleSize(TOOLINFO *pti)
    {
        return SendMessage(TTM_GETBUBBLESIZE, 0, (LPARAM) pti);
    }

    int GetCurrentTool(TOOLINFO *pti)
    {
        return SendMessage(TTM_GETCURRENTTOOL, 0, (LPARAM) pti);
    }

    int GetDelayTime(int flag)
    {
        return SendMessage(TTM_GETDELAYTIME, flag);
    }

    void GetMargin(RECT *prc)
    {
        SendMessage(TTM_GETMARGIN, 0, (LPARAM) prc);
    }

    void GetMargin(int *left, int *top, int *right, int *bottom)
    {
        RECT rc;
        SendMessage(TTM_GETMARGIN, 0, (LPARAM) & rc);
        *left = rc.left;
        *top = rc.top;
        *right = rc.right;
        *bottom = rc.bottom;
    }

    int GetMaxTipWidth()
    {
        return SendMessage(TTM_GETMAXTIPWIDTH);
    }

    void GetText(int cchMax, TOOLINFO *pti)
    {
        SendMessage(TTM_GETTEXT, cchMax, (LPARAM) pti);
    }

    COLORREF GetTipBkColor()
    {
        return (COLORREF) SendMessage(TTM_GETTIPBKCOLOR);
    }

    COLORREF GetTipTextColor()
    {
        return (COLORREF) SendMessage(TTM_GETTIPTEXTCOLOR);
    }

    void GetTitle(TTGETTITLE *ptt)
    {
        SendMessage(TTM_GETTITLE, 0, (LPARAM) ptt);
    }

    int GetToolCount()
    {
        return SendMessage(TTM_GETTOOLCOUNT);
    }

    BOOL GetToolInfo(TOOLINFO *pti)
    {
        return SendMessage(TTM_GETTOOLINFO, 0, (LPARAM) pti);
    }

    BOOL HitTest(TTHITTESTINFO *ptt)
    {
        return SendMessage(TTM_HITTEST, 0, (LPARAM) ptt);
    }

    void NewToolRect(TOOLINFO *pti)
    {
        SendMessage(TTM_NEWTOOLRECT, 0, (LPARAM) pti);
    }

    void Pop()
    {
        SendMessage(TTM_POP);
    }

    void Popup()
    {
        SendMessage(TTM_POPUP);
    }

    void RelayEvent(MSG *pmsg)
    {
        SendMessage(TTM_RELAYEVENT, 0, (LPARAM) pmsg);
    }

    void SetDelayTime(int flag, DWORD dwDelay)
    {
        SendMessage(TTM_SETDELAYTIME, flag, MAKELPARAM(dwDelay, 0));
    }

    void SetMargin(RECT *prc)
    {
        SendMessage(TTM_SETMARGIN, 0, (LPARAM) prc);
    }

    void SetMargin(int left, int top, int right, int bottom)
    {
        RECT rc = {left, top, right, bottom};
        SendMessage(TTM_SETMARGIN, 0, (LPARAM) & rc);
    }

    int SetMaxTipWidth(int w)
    {
        return SendMessage(TTM_SETMAXTIPWIDTH, 0, w);
    }

    COLORREF SetTipBkColor(COLORREF clr)
    {
        return (COLORREF) SendMessage(TTM_SETTIPBKCOLOR, (WPARAM) clr);
    }

    COLORREF SetTipTextColor(COLORREF clr)
    {
        return (COLORREF) SendMessage(TTM_SETTIPTEXTCOLOR, (WPARAM) clr);
    }

    BOOL SetTitle(int flag, LPCTSTR pText)
    {
        return SendMessage(TTM_SETTITLE, flag, (LPARAM) pText);
    }

    void SetToolInfo(TOOLINFO *pti)
    {
        SendMessage(TTM_SETTOOLINFO, 0, (LPARAM) pti);
    }

    void SetWindowTheme(LPCTSTR pTheme)
    {
        SendMessage(TTM_SETWINDOWTHEME, 0, (LPARAM) pTheme);
    }

    void TrackActivate(TOOLINFO *pti, BOOL fTrack = TRUE)
    {
        SendMessage(TTM_TRACKACTIVATE, fTrack, (LPARAM) pti);
    }

    void TrackPosition(int x, int y)
    {
        SendMessage(TTM_TRACKPOSITION, 0, MAKELPARAM(x, y));
    }

    void Update()
    {
        SendMessage(TTM_UPDATE);
    }

    void UpdateTipText(TOOLINFO *pti)
    {
        SendMessage(TTM_UPDATETIPTEXT, 0, (LPARAM) pti);
    }

    HWND WindowFromPoint(POINT *ppt)
    {
        return (HWND) SendMessage(TTM_WINDOWFROMPOINT, 0, (LPARAM) ppt);
    }


};

////////////////////////////////////////////////////////////////////////////
// class TTabCtl

class TTabCtl : public TComCtl<TTabCtl>
{
public:

    TTabCtl()
    : TComCtl<TTabCtl>(ICC_TAB_CLASSES)
    {
    }

    LPCTSTR GetClassName()
    {
        return WC_TABCONTROL;
    }

    void AdjustRect(BOOL fLarger, RECT *prc)
    {
        TabCtrl_AdjustRect(m_hwnd, fLarger, prc);
    }

    BOOL DeleteAllItems()
    {
        return TabCtrl_DeleteAllItems(m_hwnd);
    }

    BOOL DeleteItem(int index)
    {
        return TabCtrl_DeleteItem(m_hwnd, index);
    }

    void DeselectAll(UINT fExcludeFocus)
    {
        TabCtrl_DeselectAll(m_hwnd, fExcludeFocus);
    }

    int GetCurFocus()
    {
        return TabCtrl_GetCurFocus(m_hwnd);
    }

    int GetCurSel()
    {
        return TabCtrl_GetCurSel(m_hwnd);
    }

    DWORD GetExtendedStyle()
    {
        return TabCtrl_GetExtendedStyle(m_hwnd);
    }

    HIMAGELIST GetImageList()
    {
        return TabCtrl_GetImageList(m_hwnd);
    }

    BOOL GetItem(int item, TCITEM *pi)
    {
        return TabCtrl_GetItem(m_hwnd, item, pi);
    }

    int GetItemCount()
    {
        return TabCtrl_GetItemCount(m_hwnd);
    }

    BOOL GetItemRect(int item, RECT *prc)
    {
        return TabCtrl_GetItemRect(m_hwnd, item, prc);
    }

    int GetRowCount()
    {
        return TabCtrl_GetRowCount(m_hwnd);
    }

    HWND GetToolTips()
    {
        return TabCtrl_GetToolTips(m_hwnd);
    }

    BOOL GetUnicodeFormat()
    {
        return TabCtrl_GetUnicodeFormat(m_hwnd);
    }

    BOOL HighlightItem(int item, BOOL fHighlight = TRUE)
    {
        return TabCtrl_HighlightItem(m_hwnd, item, fHighlight);
    }

    int HitTest(TCHITTESTINFO *ptc)
    {
        return TabCtrl_HitTest(m_hwnd, ptc);
    }

    int InsertItem(int item, const TCITEM *ptc)
    {
        return TabCtrl_InsertItem(m_hwnd, item, ptc);
    }

    void RemoveImage(int i)
    {
        TabCtrl_RemoveImage(m_hwnd, i);
    }

    void SetCurFocus(int item)
    {
        TabCtrl_SetCurFocus(m_hwnd, item);
    }

    int SetCurSel(int item)
    {
        return TabCtrl_SetCurSel(m_hwnd, item);
    }

    DWORD SetExtendedStyle(DWORD dwStyle)
    {
        return TabCtrl_SetExtendedStyle(m_hwnd, dwStyle);
    }

    HIMAGELIST SetImageList(HIMAGELIST himl)
    {
        return TabCtrl_SetImageList(m_hwnd, himl);
    }

    BOOL SetItem(int item, TCITEM *ptc)
    {
        return TabCtrl_SetItem(m_hwnd, item, ptc);
    }

    BOOL SetItemExtra(int cb)
    {
        return TabCtrl_SetItemExtra(m_hwnd, cb);
    }

    DWORD SetItemSize(int cx, int cy)
    {
        return TabCtrl_SetItemSize(m_hwnd, cx, cy);
    }

    int SetMinTabWidth(int cx)
    {
        return TabCtrl_SetMinTabWidth(m_hwnd, cx);
    }

    void SetPadding(int cx, int cy)
    {
        TabCtrl_SetPadding(m_hwnd, cx, cy);
    }

    void SetToolTips(HWND hwndTT)
    {
        TabCtrl_SetToolTips(m_hwnd, hwndTT);
    }

    BOOL SetUnicodeFormat(BOOL fUnicode = TRUE)
    {
        return TabCtrl_SetUnicodeFormat(m_hwnd, fUnicode);
    }


};

////////////////////////////////////////////////////////////////////////////
// class TSysLinkCtl

class TSysLinkCtl : public TComCtl<TSysLinkCtl>
{
public:

    TSysLinkCtl()
    : TComCtl<TSysLinkCtl>(ICC_LINK_CLASS)
    {
    }

    LPCTSTR GetClassName()
    {
        return WC_LINK;
    }

    int GetIdealHeight()
    {
        return SendMessage(LM_GETIDEALHEIGHT);
    }

    int GetIdealSize(int max, SIZE *psz)
    {
        return SendMessage(LM_GETIDEALSIZE, max, (LPARAM) psz);
    }

    BOOL GetItem(LITEM *pi)
    {
        return SendMessage(LM_GETITEM, 0, (LPARAM) pi);
    }

    BOOL HitTest(LHITTESTINFO *pht)
    {
        return SendMessage(LM_HITTEST, 0, (LPARAM) pht);
    }

    BOOL SetItem(LITEM *pi)
    {
        return SendMessage(LM_SETITEM, 0, (LPARAM) pi);
    }

};

////////////////////////////////////////////////////////////////////////////
// class TPagerCtl

class TPagerCtl : public TComCtl<TPagerCtl>
{
public:

    TPagerCtl()
    : TComCtl<TPagerCtl>(ICC_PAGESCROLLER_CLASS)
    {
    }

    LPCTSTR GetClassName()
    {
        return WC_PAGESCROLLER;
    }

    void ForwardMouse(BOOL fForward = TRUE)
    {
        Pager_ForwardMouse(m_hwnd, fForward);
    }

    COLORREF GetBkColor()
    {
        return Pager_GetBkColor(m_hwnd);
    }

    int GetBorder()
    {
        return Pager_GetBorder(m_hwnd);
    }

    int GetButtonSize()
    {
        return Pager_GetButtonSize(m_hwnd);
    }

    DWORD GetButtonState(int index)
    {
        return Pager_GetButtonState(m_hwnd, index);
    }

    void GetDropTarget(IDropTarget **ppDropTarget)
    {
        Pager_GetDropTarget(m_hwnd, ppDropTarget);
    }

    int GetPos()
    {
        return Pager_GetPos(m_hwnd);
    }

    void RecalSize()
    {
        Pager_RecalcSize(m_hwnd);
    }

    COLORREF SetBkColor(COLORREF clr)
    {
        return Pager_SetBkColor(m_hwnd, clr);
    }

    int SetBorder(int border)
    {
        return Pager_SetBorder(m_hwnd, border);
    }

    int SetButtonSize(int size)
    {
        return Pager_SetButtonSize(m_hwnd, size);
    }

    void SetChild(HWND hwndC)
    {
        Pager_SetChild(m_hwnd, hwndC);
    }

    int SetPos(int pos)
    {
        return Pager_SetPos(m_hwnd, pos);
    }

};

////////////////////////////////////////////////////////////////////////////
// class TRebarCtl

class TRebarCtl : public TComCtl<TRebarCtl>
{
public:

    TRebarCtl()
    : TComCtl<TRebarCtl>(ICC_COOL_CLASSES)
    {
    }

    LPCTSTR GetClassName()
    {
        return REBARCLASSNAME;
    }

    void BeginDrag(int index, int horz, int vert)
    {
        SendMessage(RB_BEGINDRAG, index, MAKELPARAM(horz, vert));
    }

    BOOL DeleteBand(int index)
    {
        return SendMessage(RB_DELETEBAND, index);
    }

    void DragMove(int index, int horz, int vert)
    {
        SendMessage(RB_DRAGMOVE, index, MAKELPARAM(horz, vert));
    }

    void EndDrag()
    {
        SendMessage(RB_ENDDRAG);
    }

    void GetBandBorders(int index, RECT *prc)
    {
        SendMessage(RB_GETBANDBORDERS, index, (LPARAM) prc);
    }

    UINT GetBandCount()
    {
        return SendMessage(RB_GETBANDCOUNT);
    }

    BOOL GetBandInfo(int index, REBARBANDINFO *prb)
    {
        return SendMessage(RB_GETBANDINFO, index, (LPARAM) prb);
    }

    void GetBandMargins(MARGINS *pm)
    {
        SendMessage(RB_GETBANDMARGINS, 0, (LPARAM) pm);
    }

    UINT GetBarHeight()
    {
        return SendMessage(RB_GETBARHEIGHT);
    }

    BOOL GetBarInfo(REBARINFO *prb)
    {
        return SendMessage(RB_GETBARINFO, 0, (LPARAM) prb);
    }

    COLORREF GetBkColor()
    {
        return (COLORREF) SendMessage(RB_GETBKCOLOR);
    }

    BOOL GetColorScheme(COLORSCHEME *pcs)
    {
        return SendMessage(RB_GETCOLORSCHEME, 0, (LPARAM) pcs);
    }

    void GetDropTarget(IDropTarget **ppDropTarget)
    {
        SendMessage(RB_GETDROPTARGET, 0, (LPARAM) ppDropTarget);
    }

    HPALETTE GetPalette()
    {
        return (HPALETTE) SendMessage(RB_GETPALETTE);
    }

    BOOL GetRect(int index, RECT *prc)
    {
        return SendMessage(RB_GETRECT, index, (LPARAM) prc);
    }

    UINT GetRowCount()
    {
        return SendMessage(RB_GETROWCOUNT);
    }

    UINT GetRowHeight(int index)
    {
        return SendMessage(RB_GETROWHEIGHT, index);
    }

    COLORREF GetTextColor()
    {
        return (COLORREF) SendMessage(RB_GETTEXTCOLOR);
    }

    HWND GetToolTips()
    {
        return (HWND) SendMessage(RB_GETTOOLTIPS);
    }

    BOOL GetUnicodeFormat()
    {
        return SendMessage(RB_GETUNICODEFORMAT);
    }

    int HitTest(RBHITTESTINFO *pht)
    {
        return SendMessage(RB_HITTEST, 0, (LPARAM) pht);
    }

    int IDToIndex(REBARBANDINFO *prb)
    {
        return SendMessage(RB_IDTOINDEX, (WPARAM) prb);
    }

    int InsertBand(int index, REBARBANDINFO *prb)
    {
        return SendMessage(RB_INSERTBAND, index, (LPARAM) prb);
    }

    void MaximizeBand(int index, UINT width = 0)
    {
        SendMessage(RB_MAXIMIZEBAND, index, width);
    }

    void MinimizeBand(int index)
    {
        SendMessage(RB_MINIMIZEBAND);
    }

    BOOL MoveBand(int from, int to)
    {
        return SendMessage(RB_MOVEBAND, from, to);
    }

    void PushChevron(int index, LPARAM arg)
    {
        SendMessage(RB_PUSHCHEVRON, index, arg);
    }

    BOOL SetBandInfo(int index, REBARBANDINFO *prb)
    {
        return SendMessage(RB_SETBANDINFO, index, (LPARAM) prb);
    }

    BOOL SetBandWidth(int index, int width)
    {
        return SendMessage(RB_SETBANDWIDTH, index, width);
    }

    BOOL SetBarInfo(REBARINFO *prb)
    {
        return SendMessage(RB_SETBARINFO, 0, (LPARAM) prb);
    }

    COLORREF SetBkColor(COLORREF clr)
    {
        return (COLORREF) SendMessage(RB_SETBKCOLOR, 0, clr);
    }

    void SetColorScheme(COLORSCHEME *pcs)
    {
        SendMessage(RB_SETCOLORSCHEME, 0, (LPARAM) pcs);
    }

    HPALETTE SetPalette(HPALETTE hpal)
    {
        return (HPALETTE) SendMessage(RB_SETPALETTE, 0, (LPARAM) hpal);
    }

    HWND SetParent(HWND hwndP)
    {
        return (HWND) SendMessage(RB_SETPARENT, (WPARAM) hwndP);
    }

    COLORREF SetTextColor(COLORREF clr)
    {
        return (COLORREF) SendMessage(RB_SETTEXTCOLOR, 0, clr);
    }

    HWND SetToolTips(HWND hwndTT)
    {
        return (HWND) SendMessage(RB_SETTOOLTIPS, (LPARAM) hwndTT);
    }

    BOOL SetUnicodeFormat(BOOL fUnicode = TRUE)
    {
        return SendMessage(RB_SETUNICODEFORMAT, fUnicode);
    }

    void SetWindowTheme(LPCTSTR pTheme)
    {
        SendMessage(RB_SETWINDOWTHEME, 0, (LPARAM) pTheme);
    }

    BOOL ShowBand(int index, BOOL fShow = TRUE)
    {
        return SendMessage(RB_SHOWBAND, index, fShow);
    }

    BOOL SizeToRect(RECT *prc)
    {
        return SendMessage(RB_SIZETORECT, 0, (LPARAM) prc);
    }


};

////////////////////////////////////////////////////////////////////////////
// class THotKeyCtl

class THotKeyCtl : public TComCtl<THotKeyCtl>
{
public:

    THotKeyCtl()
    : TComCtl<THotKeyCtl>(ICC_HOTKEY_CLASS)
    {
    }

    LPCTSTR GetClassName()
    {
        return HOTKEY_CLASS;
    }

    void GetHotKey(UINT *pVK, UINT *pFlags)
    {
        UINT code = LOWORD(SendMessage(HKM_GETHOTKEY));
        *pVK = LOBYTE(code);
        *pFlags = HIBYTE(code);
    }

    void SetHotKey(UINT vk, UINT flags)
    {
        SendMessage(HKM_SETHOTKEY, MAKEWPARAM(MAKEWORD(vk, flags), 0));
    }

    void SetRules(UINT *pInvalidFlags, UINT *pKeyFlags)
    {
        SendMessage(HKM_SETRULES, (WPARAM) pInvalidFlags, (LPARAM) pKeyFlags);
    }

};

////////////////////////////////////////////////////////////////////////////
// class TTreeViewCtl

class TTreeViewCtl : public TComCtl<TTreeViewCtl>
{
public:

    TTreeViewCtl()
    : TComCtl<TTreeViewCtl>(ICC_TREEVIEW_CLASSES)
    {
    }

    LPCTSTR GetClassName()
    {
        return WC_TREEVIEW;
    }

    HIMAGELIST CreateDragImage(HTREEITEM hi)
    {
        return TreeView_CreateDragImage(m_hwnd, hi);
    }

    BOOL DeleteAllItems()
    {
        return TreeView_DeleteAllItems(m_hwnd);
    }

    BOOL DeleteItem(HTREEITEM hi)
    {
        return TreeView_DeleteItem(m_hwnd, hi);
    }

    HWND EditLabel(HTREEITEM hi)
    {
        return TreeView_EditLabel(m_hwnd, hi);
    }

    BOOL EndEditLabelNow(BOOL fCancel = TRUE)
    {
        return TreeView_EndEditLabelNow(m_hwnd, fCancel);
    }

    BOOL EnsureVisible(HTREEITEM hi)
    {
        return TreeView_EnsureVisible(m_hwnd, hi);
    }

    BOOL Expand(HTREEITEM hi, UINT flag)
    {
        return TreeView_Expand(m_hwnd, hi, flag);
    }

    COLORREF GetBkColor()
    {
        return TreeView_GetBkColor(m_hwnd);
    }

    UINT GetCheckState(HTREEITEM hi)
    {
        return TreeView_GetCheckState(m_hwnd, hi);
    }

    HTREEITEM GetChild(HTREEITEM hi)
    {
        return TreeView_GetChild(m_hwnd, hi);
    }

    UINT GetCount()
    {
        return TreeView_GetCount(m_hwnd);
    }

    HTREEITEM GetDropHilight()
    {
        return TreeView_GetDropHilight(m_hwnd);
    }

    HWND GetEditControl()
    {
        return TreeView_GetEditControl(m_hwnd);
    }

    DWORD GetExtendedStyle()
    {
        return TreeView_GetExtendedStyle(m_hwnd);
    }

    HTREEITEM GetFirstVisible()
    {
        return TreeView_GetFirstVisible(m_hwnd);
    }

    HIMAGELIST GetImageList(int img)
    {
        return TreeView_GetImageList(m_hwnd, img);
    }

    UINT GetIndent()
    {
        return TreeView_GetIndent(m_hwnd);
    }

    COLORREF GetInsertMarkColor()
    {
        return TreeView_GetInsertMarkColor(m_hwnd);
    }

    BOOL GetISearchString(LPTSTR pString)
    {
        return TreeView_GetISearchString(m_hwnd, pString);
    }

    BOOL GetItem(TVITEM *pi)
    {
        return TreeView_GetItem(m_hwnd, pi);
    }

    int GetItemHeight()
    {
        return TreeView_GetItemHeight(m_hwnd);
    }

#if (_WIN_NT >= 0x0800)

    BOOL GetItemPartRect(HTREEITEM hi, RECT *prc, TVITEMPART *ptv)
    {
        return TreeView_GetItemPartRect(m_hwnd, hi, prc, ptv);
    }

    int SetBorder(DWORD flags, int cx, int cy)
    {
        return TreeView_SetBorder(m_hwnd, flags, cx, cy);
    }

    UINT SetCheckState(HTREEITEM hi, BOOL fCheck = TRUE)
    {
        return TreeView_SetCheckState(m_hwnd, hi, fCheck);
    }

    UINT SetItemState(HTREEITEM hi, UINT state, UINT mask)
    {
        return TreeView_SetItemState(m_hwnd, hi, state, mask);
    }

    BOOL SetHot(HTREEITEM hi)
    {
        return TreeView_SetHot(m_hwnd, hi);
    }
#endif

    BOOL GetItemRect(HTREEITEM hi, RECT *prc, BOOL fItem = TRUE)
    {
        return TreeView_GetItemRect(m_hwnd, hi, prc, fItem);
    }

    UINT GetItemState(HTREEITEM hi, UINT state)
    {
        return TreeView_GetItemState(m_hwnd, hi, state);
    }

    HTREEITEM GetLastVisible()
    {
        return TreeView_GetLastVisible(m_hwnd);
    }

    COLORREF GetLineColor()
    {
        return TreeView_GetLineColor(m_hwnd);
    }

    HTREEITEM GetNextItem(HTREEITEM hi, UINT flag)
    {
        return TreeView_GetNextItem(m_hwnd, hi, flag);
    }

    HTREEITEM GetNextSelected(HTREEITEM *phi)
    {
        return TreeView_GetNextSelected(m_hwnd, phi);
    }

    HTREEITEM GetNextItemSibling(HTREEITEM hi)
    {
        return TreeView_GetNextSibling(m_hwnd, hi);
    }

    HTREEITEM GetNextItemVisible(HTREEITEM hi)
    {
        return TreeView_GetNextVisible(m_hwnd, hi);
    }

    HTREEITEM GetParent(HTREEITEM hi)
    {
        return TreeView_GetParent(m_hwnd, hi);
    }

    HTREEITEM GetPrevItemSibling(HTREEITEM hi)
    {
        return TreeView_GetPrevSibling(m_hwnd, hi);
    }

    HTREEITEM GetPrevItemVisible(HTREEITEM hi)
    {
        return TreeView_GetPrevVisible(m_hwnd, hi);
    }

    HTREEITEM GetRoot()
    {
        return TreeView_GetRoot(m_hwnd);
    }

    UINT GetScrollTime()
    {
        return TreeView_GetScrollTime(m_hwnd);
    }

    HTREEITEM GetSelection()
    {
        return TreeView_GetSelection(m_hwnd);
    }

    COLORREF GetTextColor()
    {
        return TreeView_GetTextColor(m_hwnd);
    }

    HWND GetToolTips()
    {
        return TreeView_GetToolTips(m_hwnd);
    }

    BOOL GetUnicodeFormat()
    {
        return TreeView_GetUnicodeFormat(m_hwnd);
    }

    UINT GetVisibleCount()
    {
        return TreeView_GetVisibleCount(m_hwnd);
    }

    HTREEITEM HitTest(TVHITTESTINFO *pht)
    {
        return TreeView_HitTest(m_hwnd, pht);
    }

    HTREEITEM InsertItem(TVINSERTSTRUCT *pi)
    {
        return TreeView_InsertItem(m_hwnd, pi);
    }

    HTREEITEM MapAccIDToHTREEITEM(UINT id)
    {
        return TreeView_MapAccIDToHTREEITEM(m_hwnd, id);
    }

    UINT MapHTREEITEMtoAccID(HTREEITEM hi)
    {
        return TreeView_MapHTREEITEMToAccID(m_hwnd, hi);
    }

    BOOL Select(HTREEITEM hi, UINT flag)
    {
        return TreeView_Select(m_hwnd, hi, flag);
    }

    BOOL SelectDropTarget(HTREEITEM hi)
    {
        return TreeView_SelectDropTarget(m_hwnd, hi);
    }

    BOOL SelectItem(HTREEITEM hi)
    {
        return TreeView_SelectItem(m_hwnd, hi);
    }

    BOOL SelectSetFirstVisible(HTREEITEM hi)
    {
        return TreeView_SelectSetFirstVisible(m_hwnd, hi);
    }

    LRESULT SetAutoScrollInfo(UINT pixels, UINT update)
    {
        return TreeView_SetAutoScrollInfo(m_hwnd, pixels, update);
    }

    COLORREF SetBkColor(COLORREF clr)
    {
        return TreeView_SetBkColor(m_hwnd, clr);
    }

    HRESULT SetExtendedStyle(DWORD flags, UINT mask)
    {
        return TreeView_SetExtendedStyle(m_hwnd, flags, mask);
    }

    HIMAGELIST SetImageList(HIMAGELIST himl, int img)
    {
        return TreeView_SetImageList(m_hwnd, himl, img);
    }

    BOOL SetIndent(int indent)
    {
        return TreeView_SetIndent(m_hwnd, indent);
    }

    BOOL SetInsertMark(HTREEITEM hi, BOOL fAfter = TRUE)
    {
        return TreeView_SetInsertMark(m_hwnd, hi, fAfter);
    }

    COLORREF SetInsertMarkColor(COLORREF clr)
    {
        return TreeView_SetInsertMarkColor(m_hwnd, clr);
    }

    BOOL SetItem(TVITEM *pti)
    {
        return TreeView_SetItem(m_hwnd, pti);
    }

    int SetItemHeight(int cy)
    {
        return TreeView_SetItemHeight(m_hwnd, cy);
    }

    COLORREF SetLineColor(COLORREF clr)
    {
        return TreeView_SetLineColor(m_hwnd, clr);
    }

    UINT SetScrollTime(UINT time)
    {
        return TreeView_SetScrollTime(m_hwnd, time);
    }

    COLORREF SetTextColor(COLORREF clr)
    {
        return TreeView_SetTextColor(m_hwnd, clr);
    }

    HWND SetToolTips(HWND hwndTT)
    {
        return TreeView_SetToolTips(m_hwnd, hwndTT);
    }

    BOOL SetUnicodeFormat(BOOL fUnicode = TRUE)
    {
        return TreeView_SetUnicodeFormat(m_hwnd, fUnicode);
    }

    DWORD ShowInfoTip(HTREEITEM hi)
    {
        return TreeView_ShowInfoTip(m_hwnd, hi);
    }

    BOOL SortChildren(HTREEITEM hi, BOOL fRecurse = TRUE)
    {
        return TreeView_SortChildren(m_hwnd, hi, fRecurse);
    }

    BOOL SortChildrenCB(TVSORTCB *psort, BOOL fRecurse = TRUE)
    {
        return TreeView_SortChildrenCB(m_hwnd, psort, fRecurse);
    }

};

////////////////////////////////////////////////////////////////////////////
// class TRichEditCtl

//#define RICHEDIT_1_0_DLL TEXT("riched32.dll")
#define RICHEDIT_2_0_DLL TEXT("riched20.dll")
#define RICHEDIT_3_0_DLL TEXT("riched20.dll")
#define RICHEDIT_4_1_DLL TEXT("msftedit.dll")
#define RICHEDIT_DLL RICHEDIT_4_1_DLL

//#define RICHEDIT_1_0_VERSION 0x0100
#define RICHEDIT_2_0_VERSION 0x0200
#define RICHEDIT_3_0_VERSION 0x0300
#define RICHEDIT_4_1_VERSION 0x0401
#define RICHEDIT_VERSION RICHEDIT_4_1_VERSION

class TRichEditCtl : public TComCtl<TRichEditCtl>
{
public:

    TRichEditCtl()
    : TComCtl<TRichEditCtl>(ICC_WIN95_CLASSES)
    {
    }

    virtual BOOL InitControl()
    {
        InitCommonControls();
        LoadLibrary(RICHEDIT_3_0_DLL);
        //LoadLibrary(RICHEDIT_4_1_DLL);
        return TRUE;
    }

    LPCTSTR GetClassName()
    {
        //return MSFTEDIT_CLASS;
        return RICHEDIT_CLASS;
    }

    int AutoUrlDetect(UINT flag = 0, LPCTSTR pScheme = NULL)
    {
        return SendMessage(EM_AUTOURLDETECT, flag, (LPARAM) pScheme);
    }

    BOOL CanPaste(UINT flag = 0)
    {
        return SendMessage(EM_CANPASTE, flag);
    }

    BOOL CanRedo()
    {
        return SendMessage(EM_CANREDO);
    }

    BOOL DisplayBand(RECT *prc)
    {
        return SendMessage(EM_DISPLAYBAND, 0, (LPARAM) prc);
    }

    void ExGetSel(CHARRANGE *pcr)
    {
        SendMessage(EM_EXGETSEL, 0, (LPARAM) pcr);
    }

    void ExLimitText(DWORD dwLimit = 0)
    {
        SendMessage(EM_EXLIMITTEXT, 0, dwLimit);
    }

    int ExLineFromChar(int index)
    {
        return SendMessage(EM_EXLINEFROMCHAR, 0, index);
    }

    int ExSetSel(CHARRANGE *pcr)
    {
        return SendMessage(EM_EXSETSEL, 0, (LPARAM) pcr);
    }

    int FindTextA(UINT flags, FINDTEXT *pft)
    {
        return SendMessage(EM_FINDTEXT, flags, (LPARAM) pft);
    }

    int FindTextEx(UINT flags, FINDTEXTEX *pft)
    {
        return SendMessage(EM_FINDTEXTEX, flags, (LPARAM) pft);
    }

    int FindTextExW(UINT flags, FINDTEXTEXW *pft)
    {
        return SendMessage(EM_FINDTEXTEXW, flags, (LPARAM) pft);
    }

    int FindTextW(UINT flags, FINDTEXTW *pft)
    {
        return SendMessage(EM_FINDTEXTW, flags, (LPARAM) pft);
    }

    UINT FindWordBreak(UINT flags)
    {
        return SendMessage(EM_FINDWORDBREAK, flags);
    }

    int FormatRange(BOOL fRender, FORMATRANGE *pfr)
    {
        return SendMessage(EM_FORMATRANGE, fRender, (LPARAM) pfr);
    }

    BOOL GetAutoUrlDetect()
    {
        return SendMessage(EM_GETAUTOURLDETECT);
    }

    void GetBiDiOptions(BIDIOPTIONS *pOp)
    {
        SendMessage(EM_GETBIDIOPTIONS, 0, (LPARAM) pOp);
    }

    DWORD GetCharFormat(UINT flag, CHARFORMAT *pcf)
    {
        return SendMessage(EM_GETCHARFORMAT, flag, (LPARAM) pcf);
    }

    DWORD GetCTFModeBias()
    {
        return SendMessage(EM_GETCTFMODEBIAS);
    }

    BOOL GetCTFOpenStatus()
    {
        return SendMessage(EM_GETCTFOPENSTATUS);
    }

    UINT GetEditStyle()
    {
        return SendMessage(EM_GETEDITSTYLE);
    }

#if (_WIN32_WINNT >= 0x0800)

    BOOL CallAutoCorrectProc(TCHAR ch)
    {
        return SendMessage(EM_CALLAUTOCORRECTPROC, (WPARAM) ch);
    }

    UINT GetEditStyleEx()
    {
        return SendMessage(EM_GETEDITSTYLEEX);
    }

    BOOL GetEllipsisMode(DWORD *pdwMode)
    {
        return SendMessage(EM_GETELLIPSISMODE, 0, (LPARAM) pdwMode);
    }

    HRESULT GetTableParams(TABLEROWPARAMS *ptr, TABLECELLPARAMS *ptc)
    {
        return SendMessage(EM_GETTABLEPARMS, (WPARAM) ptr, (LPARAM) ptc);
    }

    int GetStoryType(int index)
    {
        return SendMessage(EM_GETSTORYTYPE, index);
    }

    HRESULT InsertImage(RICHEDIT_IMAGE_PARAMETERS *pre)
    {
        return SendMessage(EM_INSERTIMAGE, 0, (LPARAM) pre);
    }

    HRESULT InsertTable(TABLEROWPARAMS *ptr, TABLECELLPARAMS *ptc)
    {
        return SendMessage(EM_INSERTTABLE, (WPARAM) ptr, (LPARAM) ptc);
    }

    BOOL SetAutoCorrectProc(AutoCorrectProc pfn)
    {
        return SendMessage(EM_SETAUTOCORRECTPROC, (WPARAM) pfn);
    }

    DWORD SetEditStyleEx(DWORD flags, DWORD masks)
    {
        return SendMessage(EM_SETEDITSTYLEEX, flags, masks);
    }

    BOOL SetEllipsisMode(DWORD dwMode)
    {
        return SendMessage(EM_SETELLIPSISMODE, 0, (LPARAM) dwMode);
    }

    UINT SetStoryType(int index, UINT types)
    {
        return SendMessage(EM_SETSTORYTYPE, index, types);
    }

    HRESULT SetTableParams(TABLEROWPARAMS *ptr, TABLECELLPARAMS *ptc)
    {
        return SendMessage(EM_SETTABLEPARMS, (WPARAM) ptr, (LPARAM) ptc);
    }

    void SetTouchOptions(UINT flag, BOOL fSet = TRUE)
    {
        SendMessage(EM_SETTOUCHOPTIONS, flag, fSet);
    }

    BOOL SetUIAName(LPCTSTR pName)
    {
        return SendMessage(EM_SETUIANAME, 0, (LPARAM) pName);
    }


#endif

    UINT GetEventMask()
    {
        return SendMessage(EM_GETEVENTMASK);
    }

    int GetHyphenateInfo(HYPHENATEINFO *phi)
    {
        return SendMessage(EM_GETHYPHENATEINFO, (WPARAM) phi);
    }

    int GetImeColor(COMPCOLOR *pcc)
    {
        return SendMessage(EM_GETIMECOLOR, 0, (LPARAM) pcc);
    }

    UINT GetImeCompMode()
    {
        return SendMessage(EM_GETIMECOMPMODE);
    }

    int GetImeCompText(IMECOMPTEXT *pic, DWORD *pcb)
    {
        return SendMessage(EM_GETIMECOMPTEXT, (WPARAM) pic, (LPARAM) pcb);
    }

    UINT GetImeModeBias()
    {
        return SendMessage(EM_GETIMEMODEBIAS);
    }

    UINT GetImeOptions()
    {
        return SendMessage(EM_GETIMEOPTIONS);
    }

    UINT GetImeProperty(UINT flag)
    {
        return SendMessage(EM_GETIMEPROPERTY, flag);
    }

    UINT GetLangOptions()
    {
        return SendMessage(EM_GETLANGOPTIONS);
    }

    int GetOleInterface(void **ppRichEditOle)
    {
        return SendMessage(EM_GETOLEINTERFACE, 0, (LPARAM) ppRichEditOle);
    }

    UINT GetOptions()
    {
        return SendMessage(EM_GETOPTIONS);
    }

    UINT GetPageRotate()
    {
        return SendMessage(EM_GETPAGEROTATE);
    }

    DWORD GetParaFormat(PARAFORMAT *ppf)
    {
        return SendMessage(EM_GETPARAFORMAT, 0, (LPARAM) ppf);
    }

    int GetPunctuation(UINT flag, PUNCTUATION *pp)
    {
        return SendMessage(EM_GETPUNCTUATION, flag, (LPARAM) pp);
    }

    int GetRedoName()
    {
        return SendMessage(EM_GETREDONAME);
    }

    int GetScrollPos(POINT *ppt)
    {
        return SendMessage(EM_GETSCROLLPOS, 0, (LPARAM) ppt);
    }

    int GetSelText(LPTSTR pBuffer)
    {
        return SendMessage(EM_GETSELTEXT, 0, (LPARAM) pBuffer);
    }

    int GetTextEx(GETTEXTEX *pgt, LPTSTR pBuffer)
    {
        return SendMessage(EM_GETTEXTEX, (WPARAM) pgt, (LPARAM) pBuffer);
    }

    int GetTextLengthEx(GETTEXTLENGTHEX *pgt)
    {
        return SendMessage(EM_GETTEXTLENGTHEX, (WPARAM) pgt);
    }

    int GetTextMode()
    {
        return SendMessage(EM_GETTEXTMODE);
    }

    int GetTextRange(TEXTRANGE *ptr)
    {
        return SendMessage(EM_GETTEXTRANGE, (LPARAM) ptr);
    }

    int GetTypoGraphyOptions()
    {
        return SendMessage(EM_GETTYPOGRAPHYOPTIONS);
    }

    int GetUndoName()
    {
        return SendMessage(EM_GETUNDONAME);
    }

    DWORD GetWordBreakProcEx()
    {
        return SendMessage(EM_GETWORDBREAKPROCEX);
    }

    DWORD GetWordWrapMode()
    {
        return SendMessage(EM_GETWORDWRAPMODE);
    }

    BOOL GetZoom(int *pn, int *pd)
    {
        return SendMessage(EM_GETZOOM, (WPARAM) pn, (LPARAM) pd);
    }

    void HideSelection(BOOL fHide = TRUE)
    {
        SendMessage(EM_HIDESELECTION, fHide);
    }

    BOOL IsIme()
    {
        return SendMessage(EM_ISIME);
    }

    void PasteSpecial(UINT flag, REPASTESPECIAL *pre)
    {
        SendMessage(EM_PASTESPECIAL, flag, (LPARAM) pre);
    }

    int ReConversion()
    {
        return SendMessage(EM_RECONVERSION);
    }

    int Redo()
    {
        return SendMessage(EM_REDO);
    }

    void RequestResize()
    {
        SendMessage(EM_REQUESTRESIZE);
    }

    int SelectionType()
    {
        return SendMessage(EM_SELECTIONTYPE);
    }

    void SetBiDiOptions(BIDIOPTIONS *pbi)
    {
        SendMessage(EM_SETBIDIOPTIONS, 0, (LPARAM) pbi);
    }

    COLORREF SetBkColor(UINT sysclr, COLORREF clr)
    {
        return (COLORREF) SendMessage(EM_SETBKGNDCOLOR, sysclr, (LPARAM) clr);
    }

    int SetCharFormat(UINT flag, CHARFORMAT *pcf)
    {
        return SendMessage(EM_SETCHARFORMAT, flag, (LPARAM) pcf);
    }

    DWORD SetCTFModeBias(UINT flag)
    {
        return SendMessage(EM_SETCTFMODEBIAS, flag);
    }

    BOOL SetCTFOpenStatus(BOOL fOpen = TRUE)
    {
        return SendMessage(EM_SETCTFOPENSTATUS, fOpen);
    }

    DWORD SetEditStyle(DWORD flags, DWORD masks)
    {
        return SendMessage(EM_SETEDITSTYLE, flags, masks);
    }

    UINT SetEventMask(UINT mask)
    {
        return SendMessage(EM_SETEVENTMASK, 0, mask);
    }

    int SetFontSize(int size)
    {
        return SendMessage(EM_SETFONTSIZE, size);
    }

    void SetHyphenateInfo(HYPHENATEINFO *ph)
    {
        SendMessage(EM_SETHYPHENATEINFO, (WPARAM) ph);
    }

    int SetImeColor(COMPCOLOR *pcc)
    {
        return SendMessage(EM_SETIMECOLOR, 0, (LPARAM) pcc);
    }

    UINT SetImeModeBias(UINT flag)
    {
        return SendMessage(EM_SETIMEMODEBIAS, flag, flag);
    }

    UINT SetImeOptions(UINT op, UINT flags)
    {
        return SendMessage(EM_SETIMEOPTIONS, op, flags);
    }

    int SetLangOptions(UINT ops)
    {
        return SendMessage(EM_SETLANGOPTIONS, 0, ops);
    }

    /*
    int SetOleCallback(IRichEditOleCallback *pRE)
    { return SendMessage(EM_SETOLECALLBACK, 0, (LPARAM)pRE); }
     */
    int SetOptions(UINT op, UINT flags)
    {
        return SendMessage(EM_SETOPTIONS, op, flags);
    }

    int SetParaFormat(PARAFORMAT *ppr)
    {
        return SendMessage(EM_SETPARAFORMAT, 0, (LPARAM) ppr);
    }

    int SetPageRotate(UINT flag)
    {
        return SendMessage(EM_SETPAGEROTATE, flag);
    }

    void SetPallete(HPALETTE hpal)
    {
        SendMessage(EM_SETPALETTE, (WPARAM) hpal);
    }

    int SetPunctuation(UINT flag, PUNCTUATION *pp)
    {
        return SendMessage(EM_SETPUNCTUATION, flag, (LPARAM) pp);
    }

    int SetScrollPos(POINT *ppt)
    {
        return SendMessage(EM_SETSCROLLPOS, 0, (LPARAM) ppt);
    }

    int SetTargetDevice(HDC hdc, UINT format)
    {
        return SendMessage(EM_SETTARGETDEVICE, (WPARAM) hdc, format);
    }

    int SetTextEx(SETTEXTEX *pst, LPCTSTR pText)
    {
        return SendMessage(EM_SETTEXTEX, (WPARAM) pst, (LPARAM) pText);
    }

    int SetTextMode(UINT flags)
    {
        return SendMessage(EM_SETTEXTMODE, flags);
    }

    BOOL SetTypoGraphyOptions(UINT flags, UINT mask)
    {
        return SendMessage(EM_SETTYPOGRAPHYOPTIONS, flags, mask);
    }

    int SetUndoLimit(int times = 100)
    {
        return SendMessage(EM_SETUNDOLIMIT, times);
    }

    EDITWORDBREAKPROCEX SetWordBreakProcEx(EDITWORDBREAKPROCEX pfn)
    {
        return (EDITWORDBREAKPROCEX) SendMessage(EM_SETWORDBREAKPROCEX, 0, (LPARAM) pfn);
    }

    UINT SetWordWrapMode(UINT flags)
    {
        return SendMessage(EM_SETWORDWRAPMODE, flags);
    }

    BOOL SetZoom(int n, int d)
    {
        return SendMessage(EM_SETZOOM, n, d);
    }

    void ShowScrollBar(UINT flag, BOOL fShow = TRUE)
    {
        SendMessage(EM_SHOWSCROLLBAR, flag, fShow);
    }

    int StopGroupTyping()
    {
        return SendMessage(EM_STOPGROUPTYPING);
    }

    int StreamIn(UINT flag, EDITSTREAM *pes)
    {
        return SendMessage(EM_STREAMIN, flag, (LPARAM) pes);
    }

    int StreamOut(UINT flag, EDITSTREAM *pes)
    {
        return SendMessage(EM_STREAMOUT, flag, (LPARAM) pes);
    }


};



////////////////////////////////////////////////////////////////////////////
// class image list

class TImageList
{
private:
    TImageList(const TImageList&);
    TImageList operator=(const TImageList&);

    HIMAGELIST m_himl;
    BOOL m_bIsAttached;

public:
    TImageList();
    virtual ~TImageList();

    HIMAGELIST GetHandle() const
    {
        return m_himl;
    }
    BOOL Create(int cx, int cy, UINT flags, int init, int grow);
    BOOL Destroy();

    HIMAGELIST Attach(HIMAGELIST himl);
    HIMAGELIST Detach();

    int Add(HBITMAP hbmp, HBITMAP hbmpMask)
    {
        return ImageList_Add(m_himl, hbmp, hbmpMask);
    }

    int AddMasked(HBITMAP hbmp, COLORREF crMask)
    {
        return ImageList_AddMasked(m_himl, hbmp, crMask);
    }

    BOOL BeginDrag(int track, int dx, int dy)
    {
        return ImageList_BeginDrag(m_himl, track, dx, dy);
    }

    BOOL Copy(int index, HIMAGELIST himlSrc, int isrc, UINT flags)
    {
        return ImageList_Copy(m_himl, index, himlSrc, isrc, flags);
    }

    static BOOL DragEnter(HWND hwndLock, int x, int y)
    {
        return ImageList_DragEnter(hwndLock, x, y);
    }

    static BOOL DragLeave(HWND hwndLock)
    {
        return ImageList_DragLeave(hwndLock);
    }

    static BOOL DragMove(int x, int y)
    {
        return ImageList_DragMove(x, y);
    }

    static BOOL DragShowNolock(BOOL fShow = TRUE)
    {
        return ImageList_DragShowNolock(fShow);
    }

    BOOL Draw(int i, HDC hdc, int x, int y, UINT fStyle)
    {
        return ImageList_Draw(m_himl, i, hdc, x, y, fStyle);
    }

    BOOL DrawEx(int i, HDC hdc, int x, int y, int dx, int dy, COLORREF rgbBk, COLORREF rgbFg, UINT fStyle)
    {
        return ImageList_DrawEx(m_himl, i, hdc, x, y, dx, dy, rgbBk, rgbFg, fStyle);
    }

    static BOOL DrawIndirect(IMAGELISTDRAWPARAMS *pimldp)
    {
        return ImageList_DrawIndirect(pimldp);
    }

    HIMAGELIST Duplicate()
    {
        return ImageList_Duplicate(m_himl);
    }

    static void EndDrag()
    {
        ImageList_EndDrag();
    }

    COLORREF GetBkColor()
    {
        return ImageList_GetBkColor(m_himl);
    }

    static HIMAGELIST GetDragImage(POINT *ppt, POINT *pptHotSpot)
    {
        return ImageList_GetDragImage(ppt, pptHotSpot);
    }

    HICON GetIcon(int i, UINT flags)
    {
        return ImageList_GetIcon(m_himl, i, flags);
    }

    BOOL GetIconSize(int *pcx, int *pcy)
    {
        return ImageList_GetIconSize(m_himl, pcx, pcy);
    }

    int GetImageCount()
    {
        return ImageList_GetImageCount(m_himl);
    }

    BOOL GetImageInfo(int i, IMAGEINFO *pi)
    {
        return ImageList_GetImageInfo(m_himl, i, pi);
    }

    static HIMAGELIST LoadImage(HINSTANCE hi,
                                LPCTSTR lpbmp,
                                int cx,
                                int cGrow,
                                COLORREF crMask,
                                UINT uType,
                                UINT uFlags)
    {
        return ImageList_LoadImage(hi, lpbmp, cx, cGrow, crMask, uType, uFlags);
    }

    HIMAGELIST Merge(int i1,
                     HIMAGELIST himl2,
                     int i2,
                     int dx,
                     int dy)
    {
        return ImageList_Merge(m_himl, i1, himl2, i2, dx, dy);
    }

    static HIMAGELIST Read(LPSTREAM pstm)
    {
        return ImageList_Read(pstm);
    }

    BOOL Remove(int i)
    {
        return ImageList_Remove(m_himl, i);
    }

    BOOL Replace(int i, HBITMAP hbmp, HBITMAP hbmpMask)
    {
        return ImageList_Replace(m_himl, i, hbmp, hbmpMask);
    }

    int ReplaceIcon(int i, HICON hicon)
    {
        return ImageList_ReplaceIcon(m_himl, i, hicon);
    }

    COLORREF SetBkColor(COLORREF clr)
    {
        return ImageList_SetBkColor(m_himl, clr);
    }

    /*
    int SetColorTable(int start, int end, RGBQUAD *prgb)
    { return ImageList_SetColorTable(m_himl, start, end, prgb); }
     */
    BOOL SetDragCursorImage(int i, int dx, int dy)
    {
        return ImageList_SetDragCursorImage(m_himl, i, dx, dy);
    }

    BOOL SetIconSize(int cx, int cy)
    {
        return ImageList_SetIconSize(m_himl, cx, cy);
    }

    BOOL SetImageCount(UINT newCount)
    {
        return ImageList_SetImageCount(m_himl, newCount);
    }

    BOOL SetOverlayImage(int i, int iOverlay)
    {
        return ImageList_SetOverlayImage(m_himl, i, iOverlay);
    }

    BOOL Write(LPSTREAM ps)
    {
        return ImageList_Write(m_himl, ps);
    }

    HRESULT WriteEx(DWORD dwFlags, LPSTREAM ps)
    {
        return ImageList_WriteEx(m_himl, dwFlags, ps);
    }

};

////////////////////////////////////////////////////////////////////////////
// class TGenApp

template <class TWnd>
class TGenApp
{
protected:
    TWnd m_wndMain;
    HINSTANCE m_hInst;

public:
    TGenApp(HINSTANCE, TWnd& wnd);
    virtual ~TGenApp();

public:
    int Run();

    TWnd& GetMainWindow()
    {
        return m_wndMain;
    }

    HINSTANCE GetInstance()
    {
        return m_hInst;
    }

protected:

    virtual BOOL InitInstance()
    {
        return TRUE;
    }

    virtual void ExitInstance(int nCode)
    {
    }
    // MainLoop may need to override to fit the application
    virtual void MainLoop();
};

template <class TWnd>
TGenApp<TWnd>::TGenApp(HINSTANCE hInst, TWnd& wnd)
: m_wndMain(wnd),
m_hInst(hInst)
{
}

template <class TWnd>
TGenApp<TWnd>::~TGenApp()
{
}

template <class TWnd>
int TGenApp<TWnd>::Run()
{
    // could be overridden to initialize the application
    if (!InitInstance())
    {
        // exit the application with the error code
        ExitInstance(-1);
        return -1;
    }

    // call the main loop
    MainLoop();

    // exit the application with the normal code
    ExitInstance(0);
    return 0;
}

template <class TWnd>
void TGenApp<TWnd>::MainLoop()
{
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}



#endif // TGENAPP_H
