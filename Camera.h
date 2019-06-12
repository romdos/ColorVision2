#pragma once

//Для работы необходимо подключить directShow библиотеки : Strmiids.lib Quartz.lib

#define POINTER_64 __ptr64

//#include <BaseTsd.h>
#include <dshow.h>
//#include <qedit.h> //for CLSID_SampleGrabber
#include <uuids.h> //for CLSID_SampleGrabber


#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }
#endif;
class Camera
{
	public:
	Camera(int CameraNo);
	char * Capture(long &cbBuffer, BITMAPINFOHEADER &info);
	~Camera(void);

	private:	
	IGraphBuilder *pGraph;
	IBaseFilter *pCap;
	ICaptureGraphBuilder2 * pCapture;
	IMediaControl *pControl;
	IMediaEvent   *pEvent;
	IVideoWindow *pVidWin;
	ICreateDevEnum *pDevEnum;
	IEnumMoniker *pEnum;
	IMoniker *pMoniker;
	DWORD dwRegister;		
	
	char *pBuffer;

	IBaseFilter *pSmartTee;
	IBaseFilter *pSampleGrabber;
	//ISampleGrabber *pGrabber;
	IBaseFilter *pVideoRender;

//Сервисные функции
private:
	IPin* GetPin(IBaseFilter *pFilter, PIN_DIRECTION PinDir);
	HRESULT InitCaptureGraphBuilder(
		IGraphBuilder **ppGraph,  // Receives the pointer.
		ICaptureGraphBuilder2 **ppBuild  // Receives the pointer.
	);
	HRESULT ConnectFilters(
		IGraphBuilder *pGraph, // Filter Graph Manager.
		IPin *pOut,            // Output pin on the upstream filter.
		IBaseFilter *pDest)    // Downstream filter.
		;
	HRESULT ConnectFilters(
		IGraphBuilder *pGraph, 
		IBaseFilter *pSrc, 
		IBaseFilter *pDest
	);
	HRESULT GetUnconnectedPin(
		IBaseFilter *pFilter,   // Pointer to the filter.
		PIN_DIRECTION PinDir,   // Direction of the pin to find.
		IPin **ppPin)           // Receives a pointer to the pin.
		;
	HRESULT AddToRot(IUnknown *pUnkGraph, DWORD *pdwRegister);
	void RemoveFromRot(DWORD pdwRegister);
	HRESULT AddFilterByCLSID( IGraphBuilder *pGraph, const GUID& clsid,  LPCWSTR wszName, IBaseFilter **ppF);

};
