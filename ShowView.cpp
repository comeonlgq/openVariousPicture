// ShowView.cpp : implementation of the CShowView class
//

#include "stdafx.h"
#include "Show.h"

#include "ShowDoc.h"
#include "ShowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowView

IMPLEMENT_DYNCREATE(CShowView, CView)

BEGIN_MESSAGE_MAP(CShowView, CView)
	//{{AFX_MSG_MAP(CShowView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowView construction/destruction

CShowView::CShowView()
{
	// TODO: add construction code here

}

CShowView::~CShowView()
{
}

BOOL CShowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CShowView drawing

void CShowView::OnDraw(CDC* pDC)
{
	CShowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
   
  
    //如果没有选择显示图形文件，则不用重绘 
	if(strOpenFileName.IsEmpty()) return;
    //显示当前打开的图像文件的全名 
	this->GetParent()->SetWindowText(strOpenFileName); 
	//建立图形对象 
	Graphics graphics(pDC->m_hDC);
    //装入图形文件 
   Image image(ToWChar(strOpenFileName.GetBuffer(strOpenFileName.GetLength()))) ; 
   Point destPoints[3] = { Point(0, 0), Point(image.GetWidth(), 0), 
	                       Point(0, image.GetHeight()) }; 
   Point* pdestPoints = destPoints;
   //在指定区域pdestPoints显示图像 
   graphics.DrawImage(&image, pdestPoints, 3); 


}

/////////////////////////////////////////////////////////////////////////////
// CShowView printing

BOOL CShowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CShowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CShowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CShowView diagnostics

#ifdef _DEBUG
void CShowView::AssertValid() const
{
	CView::AssertValid();
}

void CShowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShowDoc* CShowView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShowDoc)));
	return (CShowDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShowView message handlers

WCHAR* CShowView::ToWChar(char *str)
{
   //在GDI＋中，有关字符的参数类型全部都是WCHAR类型的
   //该函数是将传统字符串进行转换
   static WCHAR buffer[1024];
   wcsset(buffer,0);
   MultiByteToWideChar(CP_ACP,0,str,strlen(str),buffer,1024);
   return buffer;
}

int CShowView::GetImageCLSID(const WCHAR *format, CLSID *pCLSID)
{
 
   UINT num=0;
   UINT size=0;
   ImageCodecInfo* pImageCodecInfo=NULL;
   GetImageEncodersSize(&num,&size);
   if(size==0)
  
   return FALSE; // 编码信息不可用
  // 分配内存
   pImageCodecInfo=(ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo==NULL)
     return FALSE; // 分配失败
   // 获得系统中可用的编码方式的所有信息
   GetImageEncoders(num,size,pImageCodecInfo);
   // 在可用编码信息中查找 format 格式是否被支持
   for(UINT i=0;i<num;++i)
   {
     //MimeType: 编码方式的具体描述
     if (wcscmp(pImageCodecInfo[ i] .MimeType,format)==0)   
      {
         *pCLSID=pImageCodecInfo[i].Clsid;
         free(pImageCodecInfo);
         return TRUE;
	 }
   }
     free(pImageCodecInfo);
     return FALSE;
}

void CShowView::OnFileOpen() 
{
	// TODO: Add your command handler code here
	static char szFilter[ ]="常见图像格式文件(*.*)|*.*|";
    CFileDialog
    dlgChoseImage(1,NULL,NULL,NULL,szFilter);
    if(dlgChoseImage.DoModal() ==IDOK)
	{
       strOpenFileName=dlgChoseImage.GetPathName();
    // 打开文件后立即在窗口中显示 (重绘客户窗口)
      this->Invalidate() ;
	}
}

 

void CShowView::OnFileSave() 
{
	// TODO: Add your command handler code here
	
	if( strOpenFileName.IsEmpty() )
	{
      AfxMessageBox("当前没有打开图像文件, 不能进行保存!");
      return;
	}
    // 建立图形对象
    Graphics graphics(GetDC()->m_hDC);
    // 装入当前已经打开的图像文件
    Image image(ToWChar(strOpenFileName.GetBuffer(strOpenFileName.GetLength() )));
    CString strFileSave;
    // 将其他格式的图像全部另存为 BMP 文件
    static char szFilter[ ]= "位图(*.BMP)|*.BMP|";
   
    CFileDialog dlgChoseImage(0,"BMP",strOpenFileName,NULL,szFilter);
    if(dlgChoseImage.DoModal() ==IDOK)
	{
       strFileSave=dlgChoseImage.GetPathName();
       CLSID clsid;
       if(GetImageCLSID(L"image/bmp", &clsid))
	   {
		   image.Save(ToWChar(strFileSave.GetBuffer(strFileSave.GetLength() )), &clsid, NULL);
          // 将保存后的图像进行显示
          strOpenFileName=strFileSave;
          this->Invalidate() ;
	   }
	}
}

void CShowView::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	if(strOpenFileName.IsEmpty()) 
	{ 
      AfxMessageBox("当前没有打开图像文件，不能进行保存!"); 
      return; 
	} 
     //建立图形对像
     Graphics graphics(GetDC()->m_hDC); 
     //装入当前已经打开的图形文件
     Image image(ToWChar(strOpenFileName.GetBuffer(strOpenFileName.GetLength()))) 
     ; 
     CString strFileSave; 
     //当其他格式的图像全部另存为BMP文件
     static char szFilter[]="位图(*.BMP)|*.BMP|"; 
     CFileDialog dlgChoseImage(0,"bmp",NULL,NULL,szFilter); 
     if(dlgChoseImage.DoModal()==IDOK) 
	 { 
        strFileSave=dlgChoseImage.GetPathName(); 
        CLSID clsid; 
        if(GetImageCLSID(L"image/bmp", &clsid)) 
		{ 
           image.Save(ToWChar(strFileSave.GetBuffer(strFileSave.GetLength())), &clsid, 
           NULL); 
           //将保存后的图像进行显示
           strOpenFileName=strFileSave; 
          this->Invalidate(); 
		} 
	 } 
}
