// myPaopaoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "myPaopao.h"
#include "myPaopaoDlg.h"
#pragma comment (lib, "msimg32.lib ")
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPaopaoDlg dialog

CMyPaopaoDlg::CMyPaopaoDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMyPaopaoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyPaopaoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	nSportStyle=0;
	nDrawStyle = 0;
	bTransparent = TRUE;


	m_nCount=0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyPaopaoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPaopaoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyPaopaoDlg, CDialog)
	//{{AFX_MSG_MAP(CMyPaopaoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EXIT, &CMyPaopaoDlg::OnExit)
	ON_COMMAND(ID_ELLIPSE, &CMyPaopaoDlg::OnEllipse)
	ON_COMMAND(ID_RECT, &CMyPaopaoDlg::OnRect)
	ON_COMMAND(ID_IMG, &CMyPaopaoDlg::OnImg)
	ON_COMMAND(ID_TRANSPARENT, &CMyPaopaoDlg::OnTransparent)
	ON_UPDATE_COMMAND_UI(ID_TRANSPARENT, &CMyPaopaoDlg::OnUpdateTransparent)
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_RAND_SPORT, &CMyPaopaoDlg::OnRandSport)
	ON_COMMAND(ID_HUANRAO_SPORT, &CMyPaopaoDlg::OnHuanraoSport)
	ON_COMMAND(ID_ARC_SPORT, &CMyPaopaoDlg::OnArcSport)
	ON_COMMAND(ID_RAND_CRASH_SPORT, &CMyPaopaoDlg::OnRandCrashSport)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPaopaoDlg message handlers

BOOL CMyPaopaoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	SetWindowPos(&wndTopMost,0,0,::GetSystemMetrics(SM_CXSCREEN),::GetSystemMetrics(SM_CYSCREEN),SWP_SHOWWINDOW);
	// TODO: Add extra initialization here
	
	CreateBmpAndDC();
	AddRandPaopao(10);
	SetTimer(1,200,NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyPaopaoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyPaopaoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{


		CPaintDC dc(this);
		


		CRect rc;
		GetClientRect(rc);

		//dcMem.FillSolidRect(&rc,RGB(0,0,0));
		dcMem.FillSolidRect(&rc,RGB(18,18,18));

		for(int nCount=0;nCount<m_nCount;nCount++)
		{      
			switch(nSportStyle){
			case 0:
				//随机
				 paopao[nCount].Run(rc);
				break;

			case 1:
				//圆形
				paopao[nCount].RunCircle(rc);
				break;

			case 2:
				//弧度
				paopao[nCount].RunSin(rc, 45.0 / 180 * PAI, PAI);
				break;

			case 3:
				//碰撞
				
				for(int nOrther=0;nOrther<m_nCount;nOrther++)
				{
					if(nOrther==nCount)
						continue;

					if (paopao[nCount].bCrash(paopao[nOrther]))
					{
						paopao[nCount].Crash(paopao[nOrther]);
						paopao[nCount].Run(rc);
					}

				}
				paopao[nCount].Run(rc);
				break;

			}
           
			
			paopao[nCount].Draw(dcMem, nDrawStyle, bTransparent);
		}



		dc.BitBlt(0,0,rc.Width(),rc.Height(),&dcMem,0,0,SRCCOPY);



	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyPaopaoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CMyPaopaoDlg::AddRandPaopao(int nNumOfPaopao){
     
	for(int nCount=0;nCount<nNumOfPaopao;nCount++)
	{
		if(m_nCount<NUMOFPAOPAO){

			int r=rand()%50+10;
			int nx=rand()%20-10; 
			int ny=rand()%20-10;

			CRect rc;
			GetClientRect(&rc);

			int xPos=rand()%rc.Width();
			int yPos=rand()%rc.Height();



			COLORREF color=RGB(rand()%255,rand()%255,rand()%255);

			CPaopao newPaopao(xPos,yPos,r,nx,ny,color);
			newPaopao.SetBitmapID(IDB_BITMAP1);
			//int dx = (xPos - rc.CenterPoint().x);
			//int dy = (rc.CenterPoint().y - yPos);//折合成坐标 
 
			newPaopao.rRadius=newPaopao.Distance(rc.CenterPoint(), CPoint(xPos, yPos));

			//float angle = asin((double)dy / newPaopao.rRadius);

			//if (dx < 0)
			//	angle = PAI - angle;

			newPaopao.fAngle = newPaopao.GetAngle(rc.CenterPoint(), CPoint(xPos,yPos));

			paopao[m_nCount]=newPaopao;
			m_nCount++;

		}
	}

}

void CMyPaopaoDlg::AddRandPaopao(CPoint point, int nNumOfPaopao){

	for(int nCount=0;nCount<nNumOfPaopao;nCount++)
	{
		if(m_nCount<NUMOFPAOPAO){

			int r=rand()%50+10;
			int nx=rand()%20-10; 
			int ny=rand()%20-10;

			CRect rc;
			GetClientRect(&rc);

			int xPos=point.x;
			int yPos=point.y;

			COLORREF color=RGB(rand()%255,rand()%255,rand()%255);
			CPaopao newPaopao(xPos,yPos,r,nx,ny,color);
			newPaopao.SetBitmapID(IDB_BITMAP1);

			//int dx = (xPos - rc.CenterPoint().x);
			//int dy = (rc.CenterPoint().y - yPos);//折合成坐标 

			//
			newPaopao.rRadius = newPaopao.Distance(rc.CenterPoint(), point);
			//float angle = asin((double)dy / newPaopao.rRadius);

			//if (dx < 0)
			//	angle = PAI - angle;
			
			newPaopao.fAngle = newPaopao.GetAngle(rc.CenterPoint(), point);

			paopao[m_nCount]=newPaopao;
			m_nCount++;

		}
	}

}
void CMyPaopaoDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	

	if(m_nCount<NUMOFPAOPAO)
	{
		AddRandPaopao(point);
		Invalidate();
	}


	CDialog::OnLButtonDown(nFlags, point);
}

void CMyPaopaoDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	

	if(nIDEvent==1)
		Invalidate();

	CDialog::OnTimer(nIDEvent);
}

BOOL CMyPaopaoDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return TRUE;
	return CDialog::OnEraseBkgnd(pDC);
}
void CMyPaopaoDlg::CreateBmpAndDC(){

	CRect rc;
	GetClientRect(rc);

	CDC *pDC=GetDC();
	dcMem.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC,rc.Width(),rc.Height());

	dcMem.SelectObject(&bmp);

	ReleaseDC(pDC);

}
void CMyPaopaoDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnRButtonDown(nFlags, point);
}


void CMyPaopaoDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO:  在此处添加消息处理程序代码

	CMenu menu;
	menu.LoadMenuW(IDR_MENU1);

	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTALIGN, point.x, point.y, this);
}


void CMyPaopaoDlg::OnExit()
{
	// TODO:  在此添加命令处理程序代码
	OnOK();
}


void CMyPaopaoDlg::OnEllipse()
{
	// TODO:  在此添加命令处理程序代码

	nDrawStyle = 0;
	Invalidate();
}


void CMyPaopaoDlg::OnRect()
{
	// TODO:  在此添加命令处理程序代码


	nDrawStyle =1;
	Invalidate();
}


void CMyPaopaoDlg::OnImg()
{
	// TODO:  在此添加命令处理程序代码


	nDrawStyle = 2;
	Invalidate();
}


void CMyPaopaoDlg::OnTransparent()
{
	// TODO:  在此添加命令处理程序代码

	bTransparent = !bTransparent;
	Invalidate();
}


void CMyPaopaoDlg::OnUpdateTransparent(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码

	if (bTransparent)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
//1）添加 INITMENUPOPUP消息  ON_WM_INITMENUPOPUP()
//2） 复制如下代码，代码基本上是从CFrameWnd::OnInitMenuPopup（在WinFrm.cpp中)复制过来的
//确保选中时有对勾
void CMyPaopaoDlg::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	ASSERT(pPopupMenu != NULL);
	// Check the enabled state of various menu items.
	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);
	// Determine if menu is popup in top-level menu and set m_pOther to
	// it if so (m_pParentMenu == NULL indicates that it is secondary popup).
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
		state.m_pParentMenu = pPopupMenu;    // Parent == child for tracking popup.
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = this;
		// Child windows don't have menus--need to go to the top!
		if (pParent != NULL &&
			(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
				{
					// When popup is found, m_pParentMenu is containing menu.
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}
	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
		state.m_nIndex++)
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // Menu separator or invalid cmd - ignore it.
		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			// Possibly a popup menu, route to first item of that popup.
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue;       // First item of popup can't be routed to.
			}
			state.DoUpdate(this, TRUE);   // Popups are never auto disabled.
		}
		else
		{
			// Normal menu item.
			// Auto enable/disable if frame window has m_bAutoMenuEnable
			// set and command is _not_ a system command.
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, FALSE);
		}
		// Adjust for menu deletions and additions.
		UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}
}

void CMyPaopaoDlg::OnRandSport()
{
	// TODO: 在此添加命令处理程序代码

	nSportStyle=0;
}


void CMyPaopaoDlg::OnHuanraoSport()
{
	// TODO: 在此添加命令处理程序代码

	nSportStyle=1;
}


void CMyPaopaoDlg::OnArcSport()
{
	// TODO: 在此添加命令处理程序代码
	nSportStyle=2;
}


void CMyPaopaoDlg::OnRandCrashSport()
{
	// TODO:  在此添加命令处理程序代码
	nSportStyle = 3;
}
