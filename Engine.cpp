#include "Engine.h"
#include "GL/GL.h"
#include "GL/GLU.h"

#define PAS 10
using namespace std;

void Engine::Setup(HWND hWnd)
{

	//Chargement de la scène

	if ((tower = ReadOBJFile("OBJ/tower.obj")) == NULL || (door = ReadOBJFile("OBJ/door.obj")) == NULL || (wall = ReadOBJFile("OBJ/wall.obj")) == NULL)
	{
		MessageBox(hWnd, "Impossible de charger la scène", "erreur de chargement", 1);
		exit(0);
	}
	
	//Options OpenGL
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	// Activation de l'éclairage
	glEnable(GL_LIGHTING);	
 	glEnable(GL_LIGHT0);	// Allume la lumière n°1

	//Matrices pour bouger la caméra (la scène en réalité)
	translationMatrix[0] = -250.0;    //X
	translationMatrix[1] = -200.0;  //Y
	translationMatrix[2] = -1000.0;	   //Z

	RotationAngle = 1.3;

	oldPos.x = 0;
	oldPos.y = 0;

	horizontal = 0.0;
	vertical = 0.0;
	rotate = false;
	//////////////////////////////////////////////////////

	//Initialisation des textures (à mettre dans une fonction)


	for(unsigned int i = 0; i < tower->u32MaterialsCount; i++)
	{
		MATERIAL *material = &tower->pMaterials[i];
		if(material->pDiffuse != NULL)
		{
			GLuint nom;
			glGenTextures(1,&nom);
			material->pDiffuse->pUserData = (void *)nom;
			glBindTexture(GL_TEXTURE_2D, nom);
			glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

			switch (material->pDiffuse->PixelFormat){
			case PIXELFORMAT_R8G8B8:
				glTexImage2D(GL_TEXTURE_2D,0,3,material->pDiffuse->u32Width,material->pDiffuse->u32Height,0,GL_RGB,GL_UNSIGNED_BYTE,material->pDiffuse->pu8Pixels);
				break;
			case PIXELFORMAT_R8G8B8A8:
				glTexImage2D(GL_TEXTURE_2D,0,4,material->pDiffuse->u32Width,material->pDiffuse->u32Height,0,GL_RGBA,GL_UNSIGNED_BYTE,material->pDiffuse->pu8Pixels);
				break;
			}
		}		
	}
}

void Engine::Update(float fDT)
{
}

void Engine::Render(unsigned int u32Width, unsigned int u32Height)
{
	glClearColor(0, 0, 0, 0);
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Update Camera
	updateCamera();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (double) 640/480, 0.5, 1000);

	if (tower && wall && door)
	{
		DrawObject(tower);
		glTranslatef(100.0, 0.0, 0.0);
		DrawObject(wall);
		glTranslatef(100.0, 0.0, 0.0);
		DrawObject(wall);
		glTranslatef(100.0, 0.0, 0.0);
		DrawObject(door);
		glTranslatef(100.0, 0.0, 0.0);
		DrawObject(wall);
		glTranslatef(100.0, 0.0, 0.0);
		DrawObject(wall);
		glTranslatef(100.0, 0.0, 0.0);
		DrawObject(tower);

		glTranslatef(0.0, 0.0, 100.0);
		DrawObject(wall);
		glTranslatef(0.0, 0.0, 100.0);
		DrawObject(wall);
		glTranslatef(0.0, 0.0, 100.0);
		DrawObject(door);
		glTranslatef(0.0, 0.0, 100.0);
		DrawObject(wall);
		glTranslatef(0.0, 0.0, 100.0);
		DrawObject(wall);
		glTranslatef(0.0, 0.0, 100.0);
		DrawObject(tower);

		/*
		glTranslatef(-100.0, 0.0, 0.0);
		DrawObject(wall);
		glTranslatef(-100.0, 0.0, 0.0);
		DrawObject(wall);
		glTranslatef(-100.0, 0.0, 0.0);
		DrawObject(door);
		glTranslatef(-100.0, 0.0, 0.0);
		DrawObject(wall);
		glTranslatef(-100.0, 0.0, 0.0);
		DrawObject(wall);
		glTranslatef(-100.0, 0.0, 0.0);
		DrawObject(tower);*/
	}
	else
	{
		perror("cannot open file");
	}
}

void Engine::KeyDown(int s32VirtualKey)
{
	switch (s32VirtualKey)
	{
	case 0x5A: //Z
		translationMatrix[2] += PAS;
		break;
	case 0x53: //S
		translationMatrix[2] += -PAS;
		break;
	case VK_SPACE:
		translationMatrix[1] += -PAS;
		break;
	case VK_LCONTROL:
		translationMatrix[1] += PAS;
		break;
	case 0x51: //Q
		translationMatrix[0] += PAS;
		break;
	case 0x44: //D
		translationMatrix[0] += -PAS;
		break;
	default:
		break;
	}
}

void Engine::MouseMove(POINT Pos) 
{
	if (rotate)
	{
		if (oldPos.x < Pos.x)
			horizontal += RotationAngle;
		else if (oldPos.x > Pos.x)
			horizontal -= RotationAngle;

		if (oldPos.y < Pos.y)
			vertical += RotationAngle;
		else if (oldPos.y > Pos.y)
			vertical -= RotationAngle;
	}
	oldPos = Pos;
}

void Engine::RButtonDown(POINT Pos)
{
	rotate = true;
}
void Engine::RButtonUp(POINT Pos)
{
	rotate = false;
}

void Engine::updateCamera()
{
	glTranslatef(translationMatrix[0], translationMatrix[1], translationMatrix[2]);
	glRotatef(vertical, 1, 0, 0);
	glRotatef(horizontal, 0, 1, 0);
}

void Engine::DrawObject(SCENE *scene)
{
	GLfloat ambient[] = { 0.01, 0.01, 0.01, 1.0 };
	GLfloat specular[] = { 1, 1, 1, 1 };
	GLfloat diffuse[] = { 1, 1, 1, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	//On parcourt les objets
	for (unsigned int i = 0; i < scene->u32ObjectsCount; i++)
	{
		//On récupère l'objet courant
		OBJECT * object = &scene->pObjects[i];

		//Chargement du material si l'objet en a un
		if (object->u32Material != 0xFFFFFFFF)
		{
			MATERIAL * material = &scene->pMaterials[object->u32Material];
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material->pfAmbient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material->pfDiffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material->pfSpecular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material->pfEmission);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material->fShininess);

			//Chargement de la texture si l'objet en a une
			if (material->pDiffuse != NULL)
				glBindTexture(GL_TEXTURE_2D, (GLuint)material->pDiffuse->pUserData);
		}
		else
		{
			glMaterialf(GL_FRONT, GL_AMBIENT, 0.1);
			glMaterialf(GL_FRONT, GL_DIFFUSE, 1);
			glMaterialf(GL_FRONT, GL_SPECULAR, 1);
			glMaterialf(GL_FRONT, GL_EMISSION, 0);
			glMaterialf(GL_FRONT, GL_SHININESS, 0);
		}

		//On parcourt chaque face de l'objet
		for (unsigned int j = object->u32FirstFace; j < object->u32FirstFace + object->u32FacesCount; j++)
		{
			FACE * face = &scene->pFaces[j];
			//On va dessiner chaque point de la face et spécifier les normales à opengl
			glBegin(GL_TRIANGLES);
			for (unsigned int k = 0; k < 3; k++)
			{
				glTexCoord2fv(&scene->pUV[face->pu32UV[k]].fU);
				glNormal3fv(&scene->pNormals[face->pu32Normals[k]].fX );
				glVertex3fv(&scene->pVertices[face->pu32Vertices[k]].fX);
			}
			glEnd();
		}
	}
	glFlush();
}