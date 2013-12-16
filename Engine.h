#pragma once
#include "3DEngine.h"
#include "OBJLoader.h"
#include "GL/GL.h"
#include "GL/GLU.h"
#include "SOIL.h"
#include <map>


class Engine : public C3DEngine
{
public:
	Engine(void);

	static C3DEngine *GetInstance(void) {return(g_pRendererInstance);}
		//--- Application setup/shutdown

	void Setup(HWND hWnd);
	//virtual void Shutdown(void);

	//--- Update/render

	void Update(float fDT, Camera camera);
	void Render(unsigned int u32Width, unsigned int u32Height, Camera camera, Castle *castle, bool texON, bool readyForRedraw);
	void updateCamera();
	void InitKeyConf();

	//--- Events notifications

	//virtual void MouseWheel(float fIncrement) {}
	void MouseMove(POINT Pos);
	//virtual void LButtonDown(POINT Pos) {}
	//virtual void LButtonUp(POINT Pos) {}
	//virtual void RButtonDown(POINT Pos);
	//virtual void RButtonUp(POINT Pos);
	void KeyDown(int s32VirtualKey);
	//void KeyUp(int s32VirtualKey);

	//other
	void DrawObject(SCENE *scene);
	void DrawCastle(char **table, int width, int height);
	void DrawExampleCastle();
	void DrawGround();
	void initTextures();

private:
	std::map<WPARAM, bool> keystates;
	std::map<std::string, WPARAM> keyconf;
	float translationMatrix[3];
	float RotationAngle;
	bool rotate;
	POINT oldPos;
	float horizontal;
	float vertical;
	Camera * camera;

	GLuint grass;
	GLuint stone;

	GLdouble eyeX;
	GLdouble eyeY;
	GLdouble eyeZ;
	GLdouble lookX;
	GLdouble lookY;
	GLdouble lookZ;


protected:
	static Engine *g_pRendererInstance;
	SCENE *tower;
	SCENE *wall;
	SCENE *door;
	SCENE *ground;
	SCENE *scene;
};

