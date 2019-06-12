#include "stdafx.h"
#include "Camera.h"// модуль камеры
#include "ColorVision.h"


Camera::Camera(int CameraNo)
{
	HRESULT hr = CoInitialize(NULL);
// Create the filter graph manager and query for interfaces.
    hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                        IID_IGraphBuilder, (void **)&pGraph);
	if (FAILED(hr))

		//capture
	// Create the System Device Enumerator.
	pDevEnum=NULL;
	pEnum=NULL;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
		CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, 
		reinterpret_cast<void**>(&pDevEnum));
	if (SUCCEEDED(hr)){
		// Create an enumerator for the video capture category.
		hr = pDevEnum->CreateClassEnumerator(
			CLSID_VideoInputDeviceCategory,
			&pEnum, 0);
	}

	//list avaliable Capture;
	pMoniker = NULL;
	pCap	=	NULL;
	int counter=0;
	while (pEnum->Next(1, &pMoniker, NULL) == S_OK){
		IPropertyBag *pPropBag;
		hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, 
			(void**)(&pPropBag));
		if (FAILED(hr)){
			pMoniker->Release();
			continue;  // Skip this one, maybe the next one will work.
		}

		// Find the description or friendly name.
		VARIANT varName;
		VariantInit(&varName);
		hr = pPropBag->Read(L"Description", &varName, 0);
		if (FAILED(hr)){
			hr = pPropBag->Read(L"FriendlyName", &varName, 0);
		}
		//CString str(varName.bstrVal);
		//scannong camera devices
	
		if (SUCCEEDED(hr)){

			//=========================
			//====== if current device num is equal to CameraNo then start capture
			//=========================

			if(counter==CameraNo){
				
				hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL,
							CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, 
							(void **)&pCapture);
				if (SUCCEEDED(hr)){
					pCapture->SetFiltergraph(pGraph);
				};
				// Creating VideoCapture filter
				hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&pCap);
				if (SUCCEEDED(hr)){
					hr = pGraph->AddFilter(pCap, NULL);
				}

				pPropBag->Release();			
				pMoniker->Release();
				pPropBag= NULL;
				pMoniker=NULL;
				break;
			};
			counter++;
		}
		pPropBag->Release();
		pMoniker->Release();
	}

	//hr = AddFilterByCLSID(pGraph, CLSID_SampleGrabber, L"Sample Greabber", &pSampleGrabber);
	hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, reinterpret_cast<void**>(&pSampleGrabber));
	if (FAILED(hr))
	{
		// Error handling is omitted for clarity;
	}

	hr = pSampleGrabber->QueryInterface(IID_ISampleGrabber,
		reinterpret_cast<void**>(&pGrabber));

	hr = pGraph->AddFilter(pSampleGrabber, L"SampleGrabber");

	/*********************************************/
//	hr = AddFilterByCLSID(pGraph, CLSID_VideoRenderer, L"Render", &pVideoRender);	
	
	ConnectFilters(pGraph, pCap, pSampleGrabber);
//	ConnectFilters(pGraph, pSampleGrabber, pVideoRender);

	#ifdef _DEBUG
		hr = AddToRot(pGraph, &dwRegister);
	#endif

	hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
    hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);

    // Build the graph.
    	
	//create an Window for Video;	
	//pGraph->QueryInterface(IID_IVideoWindow, (void **)&pVidWin);
	//Bind it to Main window
	//pVidWin->put_Owner((OAHWND)(CCameraDialog::GetSafeHwnd()));
	//Change the style of the video window 
	//pVidWin->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
	//resize
	//pVidWin->SetWindowPosition(0, 0, 320, 240);
    //Query the Sample Grabber for the ISampleGrabber interface
//	pGrabberF->QueryInterface(IID_ISampleGrabber, (void**)&pGrabber);
	

	//Get a Media Type
	
	AM_MEDIA_TYPE mt;
	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
	mt.majortype = MEDIATYPE_Video;

	// Find the current bit depth.
	HWND hwnd = ::GetDesktopWindow();

	HDC hdc = GetDC(hwnd);

	int iBitDepth = ::GetDeviceCaps(hdc, BITSPIXEL);
	::ReleaseDC(hwnd, hdc);

	// Set the media type.
	mt.majortype = MEDIATYPE_Video;
	switch (iBitDepth)
	{
	case 8:
		mt.subtype = MEDIASUBTYPE_RGB8;
		break;
	case 16:
		mt.subtype = MEDIASUBTYPE_RGB555;
		break;
	case 24:
		mt.subtype = MEDIASUBTYPE_RGB24;
		break;
		case 32:
		mt.subtype = MEDIASUBTYPE_RGB32;
		break;
	default:
		return ;
	}

	//mt.subtype = MEDIASUBTYPE_RGB24;
	hr = pGrabber->SetMediaType(&mt);
	
	hr = pGrabber->SetBufferSamples(TRUE);	
	hr = pControl->Run();

}

Camera::~Camera(void)
{
	pControl->Stop();
	pControl->Release();
	//pVideoRender->Release();

	if(pGraph)
		pGraph->Release(); // Clean up after ourselves
	CoUninitialize(); // And uninitalize COM
	//delete pBuffer;
}

char * Camera::Capture(long &cbBuffer, BITMAPINFOHEADER &info){	
	
	HRESULT	hr = pGrabber->GetCurrentBuffer(&cbBuffer, NULL);
	
	if (FAILED(hr))
		return NULL;
CColorVisionApp *pApp= (CColorVisionApp *)AfxGetApp ();
if(!pApp->m_VideoCameraInput)
{
	pBuffer = new char[cbBuffer];
}

	if (!pBuffer) 
		return NULL;
		// Out of memory. Return an error code.
	
	hr = pGrabber->GetCurrentBuffer(&cbBuffer, (long*)pBuffer);
	if (FAILED(hr))
		return NULL;

	AM_MEDIA_TYPE mt;	
	hr = pGrabber->GetConnectedMediaType(&mt);

	info = ((VIDEOINFOHEADER*)mt.pbFormat)->bmiHeader;
	

	//RGBA *a = (RGBA *)pBuffer;	
	
	if (FAILED(hr))
		return NULL;

	return pBuffer;
	
};

//===============================================================================
HRESULT Camera::ConnectFilters(
		IGraphBuilder *pGraph, 
		IBaseFilter *pSrc, 
		IBaseFilter *pDest)
	{
		if ((pGraph == NULL) || (pSrc == NULL) || (pDest == NULL))
		{
			return E_POINTER;
		}

		// Find an output pin on the first filter.
		IPin *pOut = 0;
		HRESULT hr = GetUnconnectedPin(pSrc, PINDIR_OUTPUT, &pOut);
		if (FAILED(hr)) 
		{
			return hr;
		}
		hr = ConnectFilters(pGraph, pOut, pDest);
		pOut->Release();
		return hr;
	}

//===============================================================================
HRESULT Camera::ConnectFilters(
	IGraphBuilder *pGraph, // Filter Graph Manager.
	IPin *pOut,            // Output pin on the upstream filter.
	IBaseFilter *pDest)    // Downstream filter.
{
	if ((pGraph == NULL) || (pOut == NULL) || (pDest == NULL))
		return E_POINTER;
	
	#ifdef debug
		PIN_DIRECTION PinDir;
		pOut->QueryDirection(&PinDir);
		_ASSERTE(PinDir == PINDIR_OUTPUT);
	#endif

	//Find an input pin on the downstream filter.
	IPin *pIn = 0;
	HRESULT hr = GetUnconnectedPin(pDest, PINDIR_INPUT, &pIn);
	if (FAILED(hr))
	{
		return hr;
	}
	// Try to connect them.
	hr = pGraph->Connect(pOut, pIn);
	pIn->Release();
	return hr;
}
//===============================================================================
HRESULT Camera::AddFilterByCLSID( IGraphBuilder *pGraph, const GUID& clsid,  LPCWSTR wszName, IBaseFilter **ppF){
	if (!pGraph || ! ppF) return E_POINTER;
	*ppF = 0;
	IBaseFilter *pF = 0;
	HRESULT hr = CoCreateInstance(clsid, 0, CLSCTX_INPROC_SERVER, IID_IBaseFilter, reinterpret_cast<void**>(&pF));
	if (SUCCEEDED(hr)){
		hr = pGraph->AddFilter(pF, wszName);

		if (SUCCEEDED(hr))
			*ppF = pF;
		else
			pF->Release();
	};
	return hr;
}
//===============================================================================

IPin* Camera::GetPin(IBaseFilter *pFilter, PIN_DIRECTION PinDir)
{
	BOOL bFound = FALSE;
	IEnumPins *pEnum;
	IPin *pPin;
	// Begin by enumerating all the pins on a filter
	HRESULT hr = pFilter->EnumPins(&pEnum);
	if (FAILED(hr))
	{
		return NULL;
		}
	// Now look for a pin that matches the direction characteristic.
	// When we've found it, we'll return with it.
	while(pEnum->Next(1, &pPin, 0) == S_OK)
	{
		PIN_DIRECTION PinDirThis;
		pPin->QueryDirection(&PinDirThis);
		if (bFound = (PinDir == PinDirThis))
			break;
		pPin->Release();
	}
	pEnum->Release();
	return (bFound ? pPin : NULL);

}

//===============================================================================
HRESULT Camera::AddToRot(IUnknown *pUnkGraph, DWORD *pdwRegister) 
{
	/*
	
	IMoniker * pMoniker;
    IRunningObjectTable *pROT;
    if (FAILED(GetRunningObjectTable(0, &pROT))) {
        return E_FAIL;
    }
    //WCHAR wsz[256];
    //wsprintf(wsz, L"FilterGraph %08x pid %08x", (DWORD_PTR)pUnkGraph, GetCurrentProcessId());

	CHAR wsz[256];
    sprintf(wsz, "FilterGraph %08x pid %08x", (DWORD_PTR)pUnkGraph, GetCurrentProcessId());
	char *z = "!";
    HRESULT hr = CreateItemMoniker(z, wsz, &pMoniker);
	if (SUCCEEDED(hr)) {
        hr = pROT->Register(ROTFLAGS_REGISTRATIONKEEPSALIVE, pUnkGraph,
            pMoniker, pdwRegister);
        pMoniker->Release();
    }
    pROT->Release();
	*/
	HRESULT hr=S_OK;
    return hr;
}
//===============================================================================
void Camera::RemoveFromRot(DWORD pdwRegister)
{
    IRunningObjectTable *pROT;
    if (SUCCEEDED(GetRunningObjectTable(0, &pROT))) {
        pROT->Revoke(pdwRegister);
        pROT->Release();
    }
}
//===============================================================================

HRESULT Camera::GetUnconnectedPin(
    IBaseFilter *pFilter,   // Pointer to the filter.
    PIN_DIRECTION PinDir,   // Direction of the pin to find.
    IPin **ppPin)           // Receives a pointer to the pin.
{
    *ppPin = 0;
    IEnumPins *pEnum = 0;
    IPin *pPin = 0;
    HRESULT hr = pFilter->EnumPins(&pEnum);
    if (FAILED(hr))
    {
        return hr;
    }
    while (pEnum->Next(1, &pPin, NULL) == S_OK)
    {
        PIN_DIRECTION ThisPinDir;
        pPin->QueryDirection(&ThisPinDir);
		if (ThisPinDir == PinDir)
        {
            IPin *pTmp = 0;
            hr = pPin->ConnectedTo(&pTmp);
            if (SUCCEEDED(hr))  // Already connected, not the pin we want.
            {
                pTmp->Release();
            }
            else  // Unconnected, this is the pin we want.
            {
                pEnum->Release();
                *ppPin = pPin;
                return S_OK;
            }
        }
		pPin->Release();
    }
    pEnum->Release();
    // Did not find a matching pin.
    return E_FAIL;
}
