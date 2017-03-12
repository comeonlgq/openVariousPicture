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
   
  
    //���û��ѡ����ʾͼ���ļ��������ػ� 
	if(strOpenFileName.IsEmpty()) return;
    //��ʾ��ǰ�򿪵�ͼ���ļ���ȫ�� 
	this->GetParent()->SetWindowText(strOpenFileName); 
	//����ͼ�ζ��� 
	Graphics graphics(pDC->m_hDC);
    //װ��ͼ���ļ� 
   Image image(ToWChar(strOpenFileName.GetBuffer(strOpenFileName.GetLength()))) ; 
   Point destPoints[3] = { Point(0, 0), Point(image.GetWidth(), 0), 
	                       Point(0, image.GetHeight()) }; 
   Point* pdestPoints = destPoints;
   //��ָ������pdestPoints��ʾͼ�� 
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
   //��GDI���У��й��ַ��Ĳ�������ȫ������WCHAR���͵�
   //�ú����ǽ���ͳ�ַ�������ת��
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
  
   return FALSE; // ������Ϣ������
  // �����ڴ�
   pImageCodecInfo=(ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo==NULL)
     return FALSE; // ����ʧ��
   // ���ϵͳ�п��õı��뷽ʽ��������Ϣ
   GetImageEncoders(num,size,pImageCodecInfo);
   // �ڿ��ñ�����Ϣ�в��� format ��ʽ�Ƿ�֧��
   for(UINT i=0;i<num;++i)
   {
     //MimeType: ���뷽ʽ�ľ�������
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
	static char szFilter[ ]="����ͼ���ʽ�ļ�(*.*)|*.*|";
    CFileDialog
    dlgChoseImage(1,NULL,NULL,NULL,szFilter);
    if(dlgChoseImage.DoModal() ==IDOK)
	{
       strOpenFileName=dlgChoseImage.GetPathName();
    // ���ļ��������ڴ�������ʾ (�ػ�ͻ�����)
      this->Invalidate() ;
	}
}

 

void CShowView::OnFileSave() 
{
	// TODO: Add your command handler code here
	
	if( strOpenFileName.IsEmpty() )
	{
      AfxMessageBox("��ǰû�д�ͼ���ļ�, ���ܽ��б���!");
      return;
	}
    // ����ͼ�ζ���
    Graphics graphics(GetDC()->m_hDC);
    // װ�뵱ǰ�Ѿ��򿪵�ͼ���ļ�
    Image image(ToWChar(strOpenFileName.GetBuffer(strOpenFileName.GetLength() )));
    CString strFileSave;
    // ��������ʽ��ͼ��ȫ�����Ϊ BMP �ļ�
    static char szFilter[ ]= "λͼ(*.BMP)|*.BMP|";
   
    CFileDialog dlgChoseImage(0,"BMP",strOpenFileName,NULL,szFilter);
    if(dlgChoseImage.DoModal() ==IDOK)
	{
       strFileSave=dlgChoseImage.GetPathName();
       CLSID clsid;
       if(GetImageCLSID(L"image/bmp", &clsid))
	   {
		   image.Save(ToWChar(strFileSave.GetBuffer(strFileSave.GetLength() )), &clsid, NULL);
          // ��������ͼ�������ʾ
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
      AfxMessageBox("��ǰû�д�ͼ���ļ������ܽ��б���!"); 
      return; 
	} 
     //����ͼ�ζ���
     Graphics graphics(GetDC()->m_hDC); 
     //װ�뵱ǰ�Ѿ��򿪵�ͼ���ļ�
     Image image(ToWChar(strOpenFileName.GetBuffer(strOpenFileName.GetLength()))) 
     ; 
     CString strFileSave; 
     //��������ʽ��ͼ��ȫ�����ΪBMP�ļ�
     static char szFilter[]="λͼ(*.BMP)|*.BMP|"; 
     CFileDialog dlgChoseImage(0,"bmp",NULL,NULL,szFilter); 
     if(dlgChoseImage.DoModal()==IDOK) 
	 { 
        strFileSave=dlgChoseImage.GetPathName(); 
        CLSID clsid; 
        if(GetImageCLSID(L"image/bmp", &clsid)) 
		{ 
           image.Save(ToWChar(strFileSave.GetBuffer(strFileSave.GetLength())), &clsid, 
           NULL); 
           //��������ͼ�������ʾ
           strOpenFileName=strFileSave; 
          this->Invalidate(); 
		} 
	 } 
}
