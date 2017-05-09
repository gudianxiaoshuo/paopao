#pragma once
#include"math.h"

// ���ߣ�  www.gudianxiaoshuo.com    needdown.com
// ΢�ţ�  gudianxiaoshuo
// Q��     869321632
// �����  ���ֿ��á�����ʼǡ����Զ�ͼ���ŵ�С˵�ʶ���

#define PAI 3.1415926

class CPaopao{

public:
   CPaopao();
   ~CPaopao(void);
   CPaopao(int xPos,int yPos, int r,int nx,int ny,COLORREF color);

   CRect rc;//���ݵ�λ��
   bool bAdd;//�Ƕ�����
   int nx;  //���ݵ��˶� X����
   int ny;  //���ݵ��˶� Y����
   float fAngle;
   float rRadius;// Χ����ת��İ뾶
   COLORREF color;


   short nIdOfBitmap;
   short nIdOfPng;

public:
   void SetBitmapID(short nBitmapID);
   void SetPngID(short nPngID);
   void Draw(CDC &dc,int nDrawStyle=0,BOOL bPransparent=TRUE);

   void Run(CRect clientRc);
   void RunCircle(CRect clientRc);//Բ���˶�
   void RunSin(CRect clientRc,float fStartAngle,float fEndAngle);//�����˶�




   void MoveTo(int x, int y);

   float GetAngle(CPoint centerPoint, CPoint pt);
   CPoint GetCenter() const ;
   int GetXRadius()const;//x����뾶
   int GetYRadius()const;

   int GetInt(float f);//��������ȡ��С����floor  ��������ȡ�������ceil


   float Distance(CPoint pt1, CPoint pt2) const;
   float Distance(const CPaopao& ortherPaopao) const ;
   

   BOOL bCrash(const CPaopao &ortherPaopao)const ;
   void Crash(CPaopao &ortherPaopao);



  
};

