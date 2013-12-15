#pragma once
#include "stdafx.h"
#include "Camera.h"
#include "Castle.h"

class C3DEngine
{
public:
	//--- 3D engine instance retrieval

	static C3DEngine *GetInstance(void) {return(g_pRendererInstance);}

	//--- Application setup/shutdown

	virtual void Setup(HWND hWnd) {}
	virtual void Shutdown(void) {}

	//--- Update/render

	virtual void Update(float fDT, Camera camera) {}
	virtual void Render(unsigned int u32Width, unsigned int u32Height, Camera camera, Castle *castle, bool texON) {}

	//--- Events notifications

	//virtual void MouseWheel(float fIncrement) {}
	virtual void MouseMove(POINT Pos) {}
	//virtual void LButtonDown(POINT Pos) {}
	//virtual void LButtonUp(POINT Pos) {}
	//virtual void RButtonDown(POINT Pos) {}
	//virtual void RButtonUp(POINT Pos) {}
	//virtual void KeyDown(int s32VirtualKey) {}
	//virtual void KeyUp(int s32VirtualKey){}

protected:
	//--- Constructor

	C3DEngine() {g_pRendererInstance = this;}

private:
	//--- Reference to 3D engine

	static C3DEngine *g_pRendererInstance;
};
