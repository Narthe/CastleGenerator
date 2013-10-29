#pragma once
#include "3DEngine.h"
#include "OBJLoader.h"

class Engine : public C3DEngine
{
public:

	static C3DEngine *GetInstance(void) {return(g_pRendererInstance);}
		//--- Application setup/shutdown

	virtual void Setup(HWND hWnd);
	//virtual void Shutdown(void);

	//--- Update/render

	virtual void Update(float fDT);
	virtual void Render(unsigned int u32Width, unsigned int u32Height);

	//--- Events notifications

	virtual void MouseWheel(float fIncrement) {}
	virtual void MouseMove(POINT Pos);
	virtual void LButtonDown(POINT Pos) {}
	virtual void LButtonUp(POINT Pos) {}
	virtual void RButtonDown(POINT Pos);
	virtual void RButtonUp(POINT Pos);
	virtual void KeyDown(int s32VirtualKey);
	virtual void updateCamera();

	//other
	void DrawObject(SCENE *scene,  float shift);

private:
	float translationMatrix[3];
	float RotationAngle;
	bool rotate;
	POINT oldPos;
	float horizontal;
	float vertical;

protected:
	static Engine *g_pRendererInstance;
	SCENE *tower;
	SCENE *wall;
	SCENE *door;
};

