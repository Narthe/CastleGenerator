#pragma once
#include "3DEngine.h"
#include "OBJLoader.h"
#include "GL/GL.h"
#include "GL/GLU.h"
#include "SOIL.h"
#include <map>


//using namespace std;

class Engine : public C3DEngine
{
public:

	static C3DEngine *GetInstance(void) {return(g_pRendererInstance);}
		//--- Application setup/shutdown

	void Setup(HWND hWnd);
	//virtual void Shutdown(void);

	//--- Update/render

	void Update(float fDT, Camera camera);
	void Render(unsigned int u32Width, unsigned int u32Height, Camera camera, Castle *castle);
	void updateCamera();
	void InitKeyConf();

	//--- Events notifications

	//virtual void MouseWheel(float fIncrement) {}
	void MouseMove(POINT Pos);
	//virtual void LButtonDown(POINT Pos) {}
	//virtual void LButtonUp(POINT Pos) {}
	//virtual void RButtonDown(POINT Pos);
	//virtual void RButtonUp(POINT Pos);
	//virtual void KeyDown(int s32VirtualKey);
	//virtual void KeyUp(int s32VirtualKey);

	//other
	void DrawObject(SCENE *scene);
	void DrawCastle(char **table, int width, int height);
	void DrawExampleCastle();
	void initTextures();

private:
	float translationMatrix[3];
	float RotationAngle;
	bool rotate;
	POINT oldPos;
	float horizontal;
	float vertical;
	Camera * camera;

protected:
	static Engine *g_pRendererInstance;
	SCENE *tower;
	SCENE *wall;
	SCENE *door;
	SCENE *ground;
	SCENE *scene;
};

