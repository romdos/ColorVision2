; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CVizStripView
LastTemplate=CScrollView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ColorVision.h"
LastPage=0

ClassCount=15
Class1=CColorVisionApp
Class2=CViewImageVw
Class3=CViewImageDoc
Class4=CMainFrame

ResourceCount=6
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CChildFrame
Class6=CAboutDlg
Resource3=IDD_DIALOG1
Class7=CChParam
Class8=CVizStripDoc
Class9=CVizStripFrame
Class10=CVizStripView
Resource4=IDR_COLORVTYPE
Class11=BunchNumDialog
Resource5=IDD_DIALOG2
Class12=ColorSectionDialog
Class13=CGlobalObjectsDoc
Class14=CGlobalObjectsFrame
Class15=CGlobalObjectsView
Resource6=IDD_DIALOG3

[CLS:CColorVisionApp]
Type=0
HeaderFile=ColorVision.h
ImplementationFile=ColorVision.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CColorVisionApp

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=ColorVision.cpp
ImplementationFile=ColorVision.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_MRU_FILE1
Command3=ID_APP_EXIT
Command4=ID_VIEW_STATUS_BAR
Command5=ID_APP_ABOUT
CommandCount=5

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_COLORVTYPE]
Type=1
Class=CColorVisionApp
Command1=ID_FILE_OPEN
Command2=ID_FILE_CLOSE
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_CHANGE_PARAM
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_SEGMENT
Command11=ID_VIZ_STRIPS
Command12=ID_GRAY_STRIPS
Command13=ID_BUNCH_DEMO
Command14=ID_COLOR_SECTIONS
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
CommandCount=21

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_CHANGE_PARAM
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_EDIT_CUT
Command14=ID_EDIT_UNDO
CommandCount=14

[CLS:CViewImageDoc]
Type=0
HeaderFile=ViewImageDoc.h
ImplementationFile=ViewImageDoc.cpp
BaseClass=CDocument
Filter=N
LastObject=ID_FILE_OPEN
VirtualFilter=DC

[CLS:CViewImageVw]
Type=0
HeaderFile=ViewImageVw.h
ImplementationFile=ViewImageVw.cpp
BaseClass=CScrollView
Filter=C
LastObject=CViewImageVw
VirtualFilter=VWC

[DLG:IDD_DIALOG1]
Type=1
Class=CChParam
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHECK1,button,1342177283
Control4=IDC_EDIT1,edit,1350566016
Control5=IDC_STATIC,static,1342177280

[CLS:CChParam]
Type=0
HeaderFile=ChParam.h
ImplementationFile=ChParam.cpp
BaseClass=CDialog
Filter=D
LastObject=CChParam
VirtualFilter=dWC

[CLS:CVizStripDoc]
Type=0
HeaderFile=VizStripDoc.h
ImplementationFile=VizStripDoc.cpp
BaseClass=CDocument
Filter=N

[CLS:CVizStripFrame]
Type=0
HeaderFile=VizStripFrame.h
ImplementationFile=VizStripFrame.cpp
BaseClass=CMDIChildWnd
Filter=M
VirtualFilter=mfWC
LastObject=CVizStripFrame

[CLS:CVizStripView]
Type=0
HeaderFile=VizStripView.h
ImplementationFile=VizStripView.cpp
BaseClass=CScrollView
Filter=C
LastObject=CVizStripView
VirtualFilter=VWC

[DLG:IDD_DIALOG2]
Type=1
Class=BunchNumDialog
ControlCount=2
Control1=IDC_SPIN1,msctls_updown32,1342177299
Control2=IDC_EDIT1,edit,1350631552

[CLS:BunchNumDialog]
Type=0
HeaderFile=BunchNumDialog.h
ImplementationFile=BunchNumDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

[DLG:IDD_DIALOG3]
Type=1
Class=ColorSectionDialog
ControlCount=2
Control1=IDC_EDIT2,edit,1350631552
Control2=IDC_SPIN2,msctls_updown32,1342177299

[CLS:ColorSectionDialog]
Type=0
HeaderFile=olorSectionDialog.h
ImplementationFile=olorSectionDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=ColorSectionDialog
VirtualFilter=dWC

[CLS:CGlobalObjectsDoc]
Type=0
HeaderFile=GlobalObjectsDoc.h
ImplementationFile=GlobalObjectsDoc.cpp
BaseClass=CDocument
Filter=N
LastObject=CGlobalObjectsDoc

[CLS:CGlobalObjectsFrame]
Type=0
HeaderFile=GlobalObjectsFrame.h
ImplementationFile=GlobalObjectsFrame.cpp
BaseClass=CMDIChildWnd
Filter=M
LastObject=CGlobalObjectsFrame
VirtualFilter=mfWC

[CLS:CGlobalObjectsView]
Type=0
HeaderFile=GlobalObjectsView.h
ImplementationFile=GlobalObjectsView.cpp
BaseClass=CScrollView
Filter=C
LastObject=CGlobalObjectsView
VirtualFilter=VWC

