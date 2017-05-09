// myPaopaoDlg.h : header file
//

#if !defined(AFX_MYPAOPAODLG_H__2113B347_AFE4_4223_863F_14A0F03B8A34__INCLUDED_)
#define AFX_MYPAOPAODLG_H__2113B347_AFE4_4223_863F_14A0F03B8A34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyPaopaoDlg dialog

#include "Paopao.h"
#define NUMOFPAOPAO 100

#define Rand_Sport 0
#define Circle_Sport 1
#define Arc_Sort 2
#define Crash_Sort 3

class CMyPaopaoDlg : public CDialog
{
// Construction
public:
	CMyPaopaoDlg(CWnd* pParent = NULL);	// standard constructor

	CPaopao paopao[NUMOFPAOPAO];
	int m_nCount;

	void AddRandPaopao(int nNumOfPaopao=1);
	void AddRandPaopao(CPoint point, int nNumOfPaopao=1);

// Dialog Data
	//{{AFX_DATA(CMyPaopaoDlg)
	enum { IDD = IDD_MYPAOPAO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPaopaoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL


	//

	short nSportStyle; //运动方式 0 随机 1 环绕
	short nDrawStyle;  //绘图样式  0 圆形  1 正方形 2 图片 
	BOOL bTransparent; //图像透明 空刷子填充

	BOOL bTranBg;//背景透明


	CDC dcMem;
	CBitmap bmp;
	void CreateBmpAndDC();

public:
	void SetDlgTransparent(HWND hWnd, COLORREF color = RGB(10, 10, 10));

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyPaopaoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnExit();
	afx_msg void OnEllipse();
	afx_msg void OnRect();
	afx_msg void OnImg();
	afx_msg void OnTransparent();
	afx_msg void OnUpdateTransparent(CCmdUI *pCmdUI);
	afx_msg void OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnRandSport();
	afx_msg void OnHuanraoSport();
	afx_msg void OnArcSport();
	afx_msg void OnRandCrashSport();
	afx_msg void OnShowpng();
	afx_msg void OnTransbg();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPAOPAODLG_H__2113B347_AFE4_4223_863F_14A0F03B8A34__INCLUDED_)
