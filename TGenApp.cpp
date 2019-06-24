
///////////////////////////////////////////////////////////////////////////////
// TGenApp.cpp
// Author: Seree Rakwong
// Date: 5-Aug-2013
//
#include "TGameApp.h"

///////////////////////////////////////////////////////////////////////////////

BOOL TAnimate::Create(DWORD dwStyle, HWND hwndParent, UINT nID, HINSTANCE hInst)
{
    HWND hwnd = Animate_Create(hwndParent, nID, dwStyle, hInst);
    if (hwnd == NULL) return FALSE;
    m_hwnd = hwnd;

    WNDPROC wndproc = (WNDPROC) GetWindowLong(hwnd, GWL_WNDPROC);
    m_lpfnWndProc = wndproc;

    SetWindowLong(hwnd, GWL_WNDPROC, (LONG) TControl<TAnimate>::StaticWndProc);
    SetWindowLong(hwnd, GWL_USERDATA, (LONG)this);

    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

TImageList::TImageList()
: m_himl(NULL),
m_bIsAttached(FALSE)
{
}

TImageList::~TImageList()
{
    if (!m_bIsAttached)
    {
        Destroy();
    }
}

BOOL TImageList::Create(int cx, int cy, UINT flags, int init, int grow)
{
    if (m_bIsAttached)
    {
        return NULL;
    }
    HIMAGELIST himl = ImageList_Create(cx, cy, flags, init, grow);
    if (himl == NULL) return FALSE;

    m_himl = himl;
    return TRUE;
}

BOOL TImageList::Destroy()
{
    if (m_bIsAttached)
    {
        return TRUE;
    }
    BOOL bDestroy = ImageList_Destroy(m_himl);
    return bDestroy;
}

HIMAGELIST TImageList::Attach(HIMAGELIST himl)
{
    if (m_himl != NULL && !m_bIsAttached)
    {
        // cannot attach because the current handle
        // having been created
        return NULL;
    }
    if (himl == m_himl || himl == NULL)
    {
        return himl;
    }
    HIMAGELIST himlCur = m_himl;
    m_himl = himl;
    m_bIsAttached = TRUE;
    return himlCur;
}

HIMAGELIST TImageList::Detach()
{
    if (!m_bIsAttached)
    {
        return NULL;
    }
    HIMAGELIST himl = m_himl;
    m_bIsAttached = FALSE;
    m_himl = NULL;
    return himl;
}

