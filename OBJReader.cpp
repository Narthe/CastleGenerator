#include "stdafx.h"
#include "OBJReader.h"
#include "OBJLoader.h"
#include "GL/GL.h"
#include "GL/GLU.h"
#include <MMSystem.h>
#include "Engine.h"
#include "Castle.h"

//*********************************************************************************

#define WDCLASS_NAME "OBJReaderWdClass"

#define REFERENCE_TIME	0.016f

using namespace std;
//*********************************************************************************
Engine MyEngine;

Castle castle;
HINSTANCE g_hAppInstance;
HWND g_hAppWnd;
HDC g_hDC;
HGLRC g_hGLContext;
BOOL g_bRun = TRUE;
C3DEngine *C3DEngine::g_pRendererInstance = NULL;


//*********************************************************************************

ATOM RegisterWindowClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void SetupOpenGL(void);
void ShutdownOpenGL(void);

//*********************************************************************************
// Application entry point
//
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	MSG Msg;
	DWORD u32Time, u32PrevTime;
	RECT R;
	float fDT;
	MyEngine = Engine();
	castle = Castle();

	//GENERATION DU MUR D'ENCEINTE
	SETTINGS s;
	s.wall_length = 20;
	s.door_number = 3;
	s.wall_tower_number = 5;

	castle.generateWall(s);
	castle.toString();

	if (!C3DEngine::GetInstance())
	{
		MessageBox(NULL, "No 3D renderer defined", "3D error", MB_OK | MB_ICONSTOP);
		return(0);
	}

	//--- Register custom window class

	RegisterWindowClass(hInstance);

	//--- Initialize application

	if (!InitInstance (hInstance, nCmdShow))
		return(FALSE);

	//--- Load scene files

	//C3DEngine::GetInstance()->Setup(g_hAppWnd);
	//--- Main message loop

	fDT = 0;
	u32PrevTime = timeGetTime();

	/*while (g_bRun)
	{
		//--- Messages handling

		while (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		//--- Scene refresh

		GetClientRect(g_hAppWnd, &R);
		C3DEngine::GetInstance()->Render(R.right, R.bottom);

		//--- Scene update

		u32Time = timeGetTime();
		fDT += (u32Time - u32PrevTime)/1000.f;
		while (fDT >= REFERENCE_TIME)
		{
			C3DEngine::GetInstance()->Update(REFERENCE_TIME);
			fDT -= REFERENCE_TIME;
		}

		u32PrevTime = u32Time;

		//--- Buffers swapping

		SwapBuffers(g_hDC);
	}*/

	//--- Shutdown renderer

	//C3DEngine::GetInstance()->Shutdown();

	//--- Terminate application

	//return((int)Msg.wParam);
	return 0;
}

//*********************************************************************************
// Custom window registration
//
ATOM RegisterWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX Class;

	Class.cbSize = sizeof(WNDCLASSEX);

	Class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	Class.lpfnWndProc = WndProc;
	Class.cbClsExtra = 0;
	Class.cbWndExtra = 0;
	Class.hInstance = hInstance;
	Class.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OBJREADER));
	Class.hCursor = LoadCursor(NULL, IDC_ARROW);
	Class.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	Class.lpszMenuName = NULL;
	Class.lpszClassName	= WDCLASS_NAME;
	Class.hIconSm = LoadIcon(Class.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return(RegisterClassEx(&Class));
}

//*********************************************************************************
// Application initialization
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   g_hAppInstance = hInstance;

   //--- Create window

   g_hAppWnd = CreateWindow(WDCLASS_NAME, "3D scene renderer", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, g_hAppInstance, NULL);
   if (!g_hAppWnd)
      return(FALSE);

   SetupOpenGL();

   //--- Display window

   ShowWindow(g_hAppWnd, nCmdShow);
   UpdateWindow(g_hAppWnd);

   return(TRUE);
}

//*********************************************************************************
// Setup OpenGL renderer
//
void SetupOpenGL(void)
{
	PIXELFORMATDESCRIPTOR PFD;
	int s32PixelIndex;

	//--- Retrieve window DC

	g_hDC = ::GetDC(g_hAppWnd);
	if (!g_hDC)
		return;

	//--- Init desired pixel format

	memset(&PFD, 0, sizeof(PFD));

	PFD.nSize = sizeof(PFD);
	PFD.nVersion = 1;
	PFD.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_GENERIC_ACCELERATED | PFD_DOUBLEBUFFER;
	PFD.iPixelType = PFD_TYPE_RGBA;
	PFD.cColorBits = 24;
	PFD.cAlphaBits = 8;
	PFD.cDepthBits = 24;
	PFD.iLayerType = PFD_MAIN_PLANE;

	//--- Try to match the desired pixel format

	s32PixelIndex = ChoosePixelFormat(g_hDC, &PFD);
	if (!s32PixelIndex)
		s32PixelIndex = 1;	

	//--- Get pixel format description

	memset(&PFD, 0, sizeof(PFD));
	if (!DescribePixelFormat(g_hDC, s32PixelIndex, sizeof(PFD), &PFD))
		return;

	//--- Set pixel format

	if (s32PixelIndex != GetPixelFormat(g_hDC))
		if (!SetPixelFormat(g_hDC, s32PixelIndex, &PFD))
			return;

	//--- Create GL render context

	g_hGLContext = (HGLRC)wglCreateContext(g_hDC);

	//--- Activate render context

	wglMakeCurrent(g_hDC, g_hGLContext);
}

//*********************************************************************************
// Shutdown OpenGL renderer
//
void ShutdownOpenGL(void)
{
	//--- Release GL context

	if (g_hGLContext)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(g_hGLContext);
	}

	//--- Free up DC

	if (g_hDC)
		ReleaseDC(g_hAppWnd, g_hDC);
}

//*********************************************************************************
// Application message handler
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT PS;
	HDC hDC;
	POINT Pt;

	switch (message)
	{
	case WM_PAINT:
		//--- Window refresh notification

		hDC = BeginPaint(hWnd, &PS);
		EndPaint(hWnd, &PS);
		break;

	case WM_CLOSE:
		//--- Close window notification

		ShutdownOpenGL();
		DestroyWindow(g_hAppWnd);
		break;

	case WM_DESTROY:
		//--- Window destruction notification

		PostQuitMessage(0);
		g_bRun = FALSE;
		break;

	case WM_MOUSEWHEEL:
		//--- Mouse wheel notification

		C3DEngine::GetInstance()->MouseWheel(((float)(short)HIWORD(wParam))/WHEEL_DELTA);
		break;

	case WM_MOUSEMOVE:
		//--- Mouse move notification

		Pt.x = (short)LOWORD(lParam);
		Pt.y = (short)HIWORD(lParam);
		C3DEngine::GetInstance()->MouseMove(Pt);
		break;

	case WM_LBUTTONDOWN:
		//--- Left mouse button down notification

		Pt.x = (short)LOWORD(lParam);
		Pt.y = (short)HIWORD(lParam);
		C3DEngine::GetInstance()->LButtonDown(Pt);
		break;

	case WM_LBUTTONUP:
		//--- Left mouse button up notification

		Pt.x = (short)LOWORD(lParam);
		Pt.y = (short)HIWORD(lParam);
		C3DEngine::GetInstance()->LButtonUp(Pt);
		break;

	case WM_RBUTTONDOWN:
		//--- Right mouse button down notification

		Pt.x = (short)LOWORD(lParam);
		Pt.y = (short)HIWORD(lParam);
		C3DEngine::GetInstance()->RButtonDown(Pt);
		break;

	case WM_RBUTTONUP:
		//--- Right mouse button up notification

		Pt.x = (short)LOWORD(lParam);
		Pt.y = (short)HIWORD(lParam);
		C3DEngine::GetInstance()->RButtonUp(Pt);
		break;

	case WM_KEYDOWN:
		C3DEngine::GetInstance()->KeyDown((int)wParam);
		break;

	default:
		//--- Default message handling

		return(DefWindowProc(hWnd, message, wParam, lParam));
	}

	return(0);
}

