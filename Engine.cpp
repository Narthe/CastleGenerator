#include "Engine.h"
#include <iostream>

#define PAS 10
using namespace std;

//GLUquadric *quadric = gluNewQuadric();
//int MatSpec[4] = { 1, 1, 1, 1 };
int LightPos[4] = { 0, 50, -20, 1 };

void Engine::Setup(HWND hWnd)
{
	
	//Chargement de la scène

	//if ((scene = ReadOBJFile("OBJ/Island_001.obj")) == NULL)
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

	//Matrices pour bouger la caméra
	translationMatrix[0] = 0.0;    //X
	translationMatrix[1] = 10.0;  //Y
	translationMatrix[2] = 0.0;	   //Z

	RotationAngle = 1.3;

	oldPos.x = 0;
	oldPos.y = 0;

	horizontal = 0.0;
	vertical = 0.0;
	rotate = false;

	
	//////////////////////////////////////////////////////

	//Initialisation des textures (à mettre dans une fonction)

	/*
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
	}*/
}

void Engine::Update(float fDT, Camera camera)
{
	//camera.animate(fDT);
}

void Engine::Render(unsigned int u32Width, unsigned int u32Height, Camera camera, Castle *castle)
{
	
	glClearColor(0, 0, 0, 0);
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	



	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluPerspective(60, (double)640 / 480, 0.5, 10000);
	
	//camera.look();
	gluLookAt(-200.0, 4000.0, -250.0, 200,0,200, 0, 1, 0);
	//updateCamera();
	glLightiv(GL_LIGHT0, GL_POSITION, LightPos);

	
	DrawCastle(castle->m_matrix, castle->m_settings.matrix_width, castle->m_settings.matrix_height);
	//DrawExampleCastle();

	//gluSphere(quadric, 100, 20, 20);
	//DrawObject(scene);
	//glFlush();
}

/*
void Engine::KeyDown(int s32VirtualKey)
{
	switch (s32VirtualKey)
	{
	case 0x5A: //Z
		KeyStates[KeyConf["forward"]] = true;
		//translationMatrix[2] += PAS;
		break;
	case 0x53: //S
		KeyStates[KeyConf["backward"]] = true;
		//translationMatrix[2] += -PAS;
		break;
	case VK_SPACE:
		//translationMatrix[1] += -PAS;
		break;
	case VK_LCONTROL:
		//translationMatrix[1] += PAS;
		break;
	case 0x51: //Q
		KeyStates[KeyConf["strafleft"]] = true;
		//translationMatrix[0] += PAS;
		break;
	case 0x44: //D
		KeyStates[KeyConf["strafright"]] = true;
		//translationMatrix[0] += -PAS;
		break;
	default:
		break;
	}
}
*/

void Engine::MouseMove(POINT Pos) 
{
	if (oldPos.x < Pos.x)
		horizontal += RotationAngle;
	else if (oldPos.x > Pos.x)
		horizontal -= RotationAngle;

	if (oldPos.y < Pos.y)
		vertical += RotationAngle;
	else if (oldPos.y > Pos.y)
		vertical -= RotationAngle;
	oldPos = Pos;
}



/*
void Engine::RButtonDown(POINT Pos)
{
	rotate = true;
}
void Engine::RButtonUp(POINT Pos)
{
	rotate = false;
}
*/
void Engine::updateCamera()
{
	gluPerspective(60, (double)640 / 480, 0.5, 10000);
	glRotatef(vertical, 1, 0, 0);
	glRotatef(horizontal, 0, 1, 0);
	//glTranslatef(translationMatrix[0], translationMatrix[1], translationMatrix[2]);
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
	//glFlush();
}

void Engine::DrawCastle(char **table, int width, int height)
{
	
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (table[i][j] != ' ')
			{
				glPushMatrix();
				if (table[i][j] == 'T')
				{
					glTranslatef(i*100.0, 0.0, j*100.0);
					DrawObject(tower);
				}
				else
				{
					glTranslatef(i*100.0, 0.0, j*100.0);
					DrawObject(wall);
				}
				glPopMatrix();
			}
		}
	}
	
}

void Engine::DrawExampleCastle()
{
	
	//glLoadIdentity();
	if (tower && wall && door)
	{
		for (int i = 0; i < 10; i++)
		{
			glPushMatrix();
			glTranslatef(i*100.0, 0.0, i*100.0);
			DrawObject(tower);
			glPopMatrix();
		}
		
	}
	else
	{
		perror("cannot open file");
	}
	
}

/*
void Engine::InitKeyConf()
{
	KeyConf["forward"] = 0x5A;
	KeyConf["backward"] = 0x53;
	KeyConf["strafright"] = 0x44;
	KeyConf["strafleft"] = 0x51;
	KeyConf["up"] = VK_SPACE;
	//KeyConf["down"] = VK_LCONTROL;

}

*/