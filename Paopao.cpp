#include "stdafx.h"
#include "Paopao.h"


BOOL LoadImageFromResource(CImage *pImage, UINT nResID, LPCTSTR lpTyp)
{
	if (pImage == NULL)
		return false;
	pImage->Destroy();
	// ������Դ
	HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), lpTyp);
	if (hRsrc == NULL)
		return false;
	// ������Դ
	HGLOBAL hImgData = ::LoadResource(AfxGetResourceHandle(), hRsrc);
	if (hImgData == NULL)
	{
		::FreeResource(hImgData);
		return false;
	}
	// �����ڴ��е�ָ����Դ
	LPVOID lpVoid = ::LockResource(hImgData);
	LPSTREAM pStream = NULL;
	DWORD dwSize = ::SizeofResource(AfxGetResourceHandle(), hRsrc);
	HGLOBAL hNew = ::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte = (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);
	// ����ڴ��е�ָ����Դ
	::GlobalUnlock(hNew);
	// ��ָ���ڴ洴��������
	HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
	if (ht != S_OK)
	{
		GlobalFree(hNew);
	}
	else
	{
		// ����ͼƬ
		pImage->Load(pStream);
		GlobalFree(hNew);
	}
	// �ͷ���Դ
	::FreeResource(hImgData);
	return true;
}


CPaopao::CPaopao()
{	
      nx=0;
	  ny=0;
	  fAngle = 0;
	  rRadius=0;
	  bAdd = TRUE;
	  color=RGB(0,0,0);

}
CPaopao::CPaopao(int xPos,int yPos, int r,int nx,int ny,COLORREF color){

	  rc.top=yPos-r;
	  rc.left=xPos-r;
	  rc.right=xPos+r;
	  rc.bottom=yPos+r;
	  fAngle = 0;

      this->nx=nx;
	  this->ny=ny;
	  this->color=color;
   }

void CPaopao::SetPngID(short nPngID){
	nIdOfPng = nPngID;
}

void CPaopao::SetBitmapID(short nBitmapID){

	nIdOfBitmap = nBitmapID;
}
 void CPaopao::Draw(CDC &dc,int nDrawStyle,BOOL bPransparent){


	   CPen pen;
	   pen.CreatePen(0,1,color);

       CPen *pOldPen=dc.SelectObject(&pen);

       CBrush* pOldBrush=NULL;
	   CBrush brush;
	   CBitmap bmp;
	   CDC memDC;
	   if(bPransparent)
			pOldBrush=(CBrush*)dc.SelectStockObject(NULL_BRUSH);
	   else{
		   brush.CreateSolidBrush(color);
		   pOldBrush=dc.SelectObject(&brush);
	   }

	   switch(nDrawStyle){

	   case 0:
		   {
              dc.Ellipse(rc);
		   }
		   break;

	   case 1:
		   {
              dc.Rectangle(rc);
		   }
		   break;

	   case 2:
		   {
			 bmp.LoadBitmap(nIdOfBitmap);
			 memDC.CreateCompatibleDC(&dc);
		     memDC.SelectObject(&bmp);

			 BITMAP bmpInfo;
			 bmp.GetBitmap(&bmpInfo);
             
			 dc.BitBlt(rc.left,rc.top,rc.Width(),rc.Height(),&memDC,0,0,SRCCOPY);
			// dc.StretchBlt(rc.left, rc.top, rc.Width(), rc.Height(), &memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, NOTSRCCOPY);
		//	TransparentBlt(dc.GetSafeHdc(),rc.left,rc.top,rc.Width(),rc.Height(),memDC.GetSafeHdc(),0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,RGB(255, 255, 255));

		   }
		   break;

	   case 3:
	   {
				 CImage Image;

				 LoadImageFromResource(&Image, nIdOfPng, _T("PNG"));
				 if (Image.IsNull())
				 {
					 return;
				 }
				 if (Image.GetBPP() == 32) //ȷ�ϸ�ͼ�����Alphaͨ��
				 {
					 int i;
					 int j;
					 for (i = 0; i<Image.GetWidth(); i++)
					 {
						 for (j = 0; j<Image.GetHeight(); j++)
						 {
							 byte *pByte = (byte *)Image.GetPixelAddress(i, j);
							 pByte[0] = pByte[0] * pByte[3] / 255;
							 pByte[1] = pByte[1] * pByte[3] / 255;
							 pByte[2] = pByte[2] * pByte[3] / 255;
						 }
					 }
				 }
				 Image.Draw(dc.GetSafeHdc(), rc.left, rc.top, rc.Width(), rc.Height());
				 Image.Destroy();
				


	   }

		   break;


	   }


	   dc.SelectObject(pOldBrush);
	   dc.SelectObject(pOldPen);

   }

   void CPaopao::Run(CRect clientRc)
   {
			//λ����Ϣ
            rc.top+=ny;
			rc.bottom+=ny;

            rc.left+=nx;
			rc.right+=nx;

			if(rc.top<0)
				ny=abs(ny);

			if(rc.bottom>clientRc.bottom)
				ny=-abs(ny);


			if(rc.left<0)
				nx=abs(nx);

			if(rc.right>clientRc.right)
				nx=-abs(nx);

   }

   void CPaopao::MoveTo(int x, int y){

	   CPoint ptPaoPaoCenter = GetCenter();
	   rc.OffsetRect(x - ptPaoPaoCenter.x, y - ptPaoPaoCenter.y);
   }

   void CPaopao::RunSin(CRect clientRc, float fStartAngle, float fEndAngle)//�����˶�
   {
	  
	   CPoint ptCenter = clientRc.CenterPoint();
	   CPoint ptPaoPaoCenter = GetCenter();

	   //   int nRadius =Distance(ptCenter, ptPaoPaoCenter);
	   long x = ptCenter.x + rRadius*cos(fAngle);
	   long y = ptCenter.y - rRadius*sin(fAngle);//�ۺϳ�����  

	   MoveTo(x,y);

	   if (bAdd)
		   fAngle += 0.1;
	   else
		   fAngle -= 0.1;


	   if (fAngle>fEndAngle)
		   bAdd = FALSE;

	   if (fAngle<fStartAngle)
		   bAdd = TRUE;



   }


   void CPaopao::RunCircle(CRect clientRc){

	   CPoint ptCenter = clientRc.CenterPoint();
	   CPoint ptPaoPaoCenter = rc.CenterPoint();

	//   int nRadius =Distance(ptCenter, ptPaoPaoCenter);
	   long x = ptCenter.x + rRadius*cos(fAngle);
	   long y = ptCenter.y - rRadius*sin(fAngle);

	   rc.OffsetRect(x-ptPaoPaoCenter.x, y-ptPaoPaoCenter.y );
	   fAngle += 0.03;
   }
   CPoint CPaopao::GetCenter() const
   {
	   return rc.CenterPoint();
   }

   int CPaopao::GetXRadius()const//x����뾶
   {
	   return rc.Width()/2;
   }
   int CPaopao::GetYRadius()const{

	    return rc.Height()/2;
   }
   float CPaopao::Distance(CPoint pt1, CPoint pt2) const {

	   return sqrt((pt1.x - pt2.x)*(pt1.x - pt2.x)*1.0 + (pt1.y - pt2.y)*(pt1.y - pt2.y));
   }

   //ortherPaopao Ϊconst ��������  ������const�����ڵ��ó�Ա������ʱ�򣬻Ὣthisָ��ǿ��ת��Ϊconst this,������ֻ�ܵ���const ��������
    float CPaopao::Distance(const CPaopao& ortherPaopao) const{

		CPoint pt1=GetCenter();
		CPoint pt2=ortherPaopao.GetCenter();

		return Distance(pt1, pt2);
	}

   float CPaopao::GetAngle(CPoint centerPoint, CPoint pt){
	   int dx = (pt.x - centerPoint.x);
	   int dy = (centerPoint.y - pt.y);//�ۺϳ����� 

	   float rRadius = Distance(centerPoint, pt);
	   float angle = asin((double)dy / rRadius);

	   if (dx < 0)
		   angle = PAI - angle;

	   return angle;
   }
CPaopao::~CPaopao(void)
{
}
 BOOL CPaopao::bCrash(const CPaopao &ortherPaopao)const{

	 float dis=Distance(ortherPaopao);

	 if(dis<GetXRadius()+ortherPaopao.GetXRadius())
		 return TRUE;
	 else
		 return FALSE;
 }
 //floor ceil
 //ceil(x)���ز�С��x����С����ֵ��Ȼ��ת��Ϊdouble�ͣ���

//	 floor(x)���ز�����x���������ֵ��

//	 round(x)����x��������������ֵ��
 int CPaopao::GetInt(float f){

	 int nValue=0;
	 if(f>0)
		 nValue = round(f);//����ȡ��
	 else
		 nValue = round(f);//����ȡ��

	 return nValue;
 }
 void CPaopao::Crash(CPaopao &ortherPaopao){

	 //����1���ٶ�
	 float V1x=nx;
	 float V1y=ny;

	 //����2���ٶ�
	 float V2x=ortherPaopao.nx;
	 float V2y=ortherPaopao.ny;

	 int x1=GetCenter().x;
	 int y1=GetCenter().y;

	 int x2=ortherPaopao.GetCenter().x;
	 int y2=ortherPaopao.GetCenter().y;

	 //��2 ��ײ������ٶ�
	 int nx2=V2x;
	 int ny2=V2y;

	 //������
	 float nDividend=V1x*pow(y2-y1,2.0)+V2x*pow(x2-x1,2.0)+(V2y-V1y)*(x2-x1)*(y2-y1);
	 //����
	 int nDivisor=pow(x2-x1,2.0)+pow(y2-y1,2.0);


		 //��ײ������ٶ�--x
	 if(nDivisor!=0){

		 nx=GetInt(nDividend/nDivisor);

		 nDividend=V1y*pow(x2-x1,2.0)+V2y*pow(y2-y1,2.0)+(V2x-V1x)*(x2-x1)*(y2-y1);
		  //��ײ������ٶ�--y
		 ny=GetInt(nDividend/nDivisor);

		 if(nx==0&&ny==0)
		 {
			 if (nDividend > 0)
				 ny = 2;
			 else
				 ny = -2;
		 }


		 //��2��ײ������ٶ�



		 nDividend=V1y*pow(y2-y1,2.0)+V2y*pow(x2-x1,2.0)-(V2x-V1x)*(x2-x1)*(y2-y1);
		 ny2=GetInt(nDividend/nDivisor);

		 nDividend = V1x*pow(x2 - x1, 2.0) + V2x*pow(y2 - y1, 2.0) - (V2y - V1y)*(x2 - x1)*(y2 - y1);
		 nx2 = GetInt(nDividend / nDivisor);

		 if(nx2==0&&ny2==0)
		 {
			 if (nDividend > 0)
				 nx2 = 2;
			 else
				 nx2 = -2;
		 }
		 ortherPaopao.nx=nx2;
		 ortherPaopao.ny=ny2;
	 }

 }