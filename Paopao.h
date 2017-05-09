#pragma once
#include"math.h"

// 作者：  www.gudianxiaoshuo.com    needdown.com
// 微信：  gudianxiaoshuo
// Q：     869321632
// 软件：  快乐课堂、藏书笔记、任性动图、古典小说朗读等

#define PAI 3.1415926

class CPaopao{

public:
   CPaopao();
   ~CPaopao(void);
   CPaopao(int xPos,int yPos, int r,int nx,int ny,COLORREF color);

   CRect rc;//泡泡的位置
   bool bAdd;//角度增减
   int nx;  //泡泡的运动 X分量
   int ny;  //泡泡的运动 Y分量
   float fAngle;
   float rRadius;// 围绕旋转点的半径
   COLORREF color;


   short nIdOfBitmap;
   short nIdOfPng;

public:
   void SetBitmapID(short nBitmapID);
   void SetPngID(short nPngID);
   void Draw(CDC &dc,int nDrawStyle=0,BOOL bPransparent=TRUE);

   void Run(CRect clientRc);
   void RunCircle(CRect clientRc);//圆形运动
   void RunSin(CRect clientRc,float fStartAngle,float fEndAngle);//正弦运动




   void MoveTo(int x, int y);

   float GetAngle(CPoint centerPoint, CPoint pt);
   CPoint GetCenter() const ;
   int GetXRadius()const;//x方向半径
   int GetYRadius()const;

   int GetInt(float f);//正数往下取最小整数floor  负数往上取最大整数ceil


   float Distance(CPoint pt1, CPoint pt2) const;
   float Distance(const CPaopao& ortherPaopao) const ;
   

   BOOL bCrash(const CPaopao &ortherPaopao)const ;
   void Crash(CPaopao &ortherPaopao);



  
};

