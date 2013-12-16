#include "Engine.h"
#include <iostream>

#define PAS 10
using namespace std;

//GLUquadric *quadric = gluNewQuadric();
//int MatSpec[4] = { 1, 1, 1, 1 };
int LightPos[4] = { 0, 500, -20, 1 };

Engine::Engine(void)
{
	//commandes
	//InitKeyConf();
}

void Engine::Setup(HWND hWnd)
{

	//OBJs
	if ((tower = ReadOBJFile("OBJ/tower.obj")) == NULL || (door = ReadOBJFile("OBJ/door.obj")) == NULL || (wall = ReadOBJFile("OBJ/wall.obj")) == NULL || (ground = ReadOBJFile("OBJ/ground.obj")) == NULL)
	{
		MessageBox(hWnd, "Impossible de charger la scène", "erreur de chargement", 1);
		exit(0);
	}
	
	//Options OpenGL
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);

	//textures
	initTextures();

	// Activation de l'éclairage
	glEnable(GL_LIGHTING);	
 	glEnable(GL_LIGHT0);	// Allume la lumière n°1

	//Matrices pour bouger la caméra
	translationMatrix[0] = 0.0;    //X
	translationMatrix[1] = 10.0;  //Y
	translationMatrix[2] = 0.0;	   //Z

	RotationAngle = 10;

	oldPos.x = 0;
	oldPos.y = 0;

	horizontal = 0.0;
	vertical = 0.0;
	rotate = false;

	eyeX = -100.0;
	eyeY = 1000.0;
	eyeZ = -150.0;
	lookX = 500.0;
	lookY = 0.0;
	lookZ = 500.0;

	
	//////////////////////////////////////////////////////

	//Initialisation des textures (à mettre dans une fonction)
}

void Engine::Update(float fDT, Camera camera)
{
	//camera.animate(fDT);
}

void Engine::Render(unsigned int u32Width, unsigned int u32Height, Camera camera, Castle *castle, bool texON, bool readyForRedraw)
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
	//gluLookAt(-100.0, 3000.0, -150.0, 500,0,500, 0, 1, 0);
	gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, 0, 1, 0);
	updateCamera();
	glLightiv(GL_LIGHT0, GL_POSITION, LightPos);

	if (texON)
	{
		glEnable(GL_TEXTURE_2D);
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}

	glBindTexture(GL_TEXTURE_2D, grass);
	//DrawObject(ground);
	DrawGround();
	
	glBindTexture(GL_TEXTURE_2D, stone);
	if(readyForRedraw)
		DrawCastle(castle->m_matrix, castle->m_settings.matrix_width, castle->m_settings.matrix_height);
	//DrawExampleCastle();

}


void Engine::KeyDown(int s32VirtualKey)
{
	switch (s32VirtualKey)
	{
	case 0x5A: //Z
		eyeZ += PAS;
		//keystates[keyconf["forward"]] = true;
		//translationMatrix[2] += PAS;
		break;
	case 0x53: //S
		eyeZ -= PAS;
		//keystates[keyconf["backward"]] = true;
		//translationMatrix[2] += -PAS;
		break;
	case VK_SPACE:
		eyeY += PAS;
		//translationMatrix[1] += -PAS;
		//keystates[keyconf["up"]] = true;
		break;
	case VK_LCONTROL:
		eyeY -= PAS;
		//translationMatrix[1] += PAS;
		//keystates[keyconf["down"]] = true;
		break;
	case 0x51: //Q
		eyeX -= PAS;
		//keystates[keyconf["strafleft"]] = true;
		//translationMatrix[0] += PAS;
		break;
	case 0x44: //D
		eyeX += PAS;
		//keystates[keyconf["strafright"]] = true;
		//translationMatrix[0] += -PAS;
		break;
	default:
		break;
	}
}

/*
void Engine::KeyUp(int s32VirtualKey)
{
	switch (s32VirtualKey)
	{
	case 0x5A: //Z
		keystates[keyconf["forward"]] = false;
		//translationMatrix[2] += PAS;
		break;
	case 0x53: //S
		keystates[keyconf["backward"]] = false;
		//translationMatrix[2] += -PAS;
		break;
	case VK_SPACE:
		//translationMatrix[1] += -PAS;
		keystates[keyconf["up"]] = false;
		break;
	case VK_LCONTROL:
		//translationMatrix[1] += PAS;
		keystates[keyconf["down"]] = false;
		break;
	case 0x51: //Q
		keystates[keyconf["strafleft"]] = false;
		//translationMatrix[0] += PAS;
		break;
	case 0x44: //D
		keystates[keyconf["strafright"]] = false;
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
		lookX += RotationAngle;
	else if (oldPos.x > Pos.x)
		lookX -= RotationAngle;

	if (oldPos.y < Pos.y)
		lookY += RotationAngle;
	else if (oldPos.y > Pos.y)
		lookY -= RotationAngle;
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
	/*
	if (keystates[keyconf["forward"]])
		eyeZ += 1; //on avance
	if (keystates[keyconf["backward"]])
		eyeZ -= 1; //on recule
	if (keystates[keyconf["strafe_left"]])
		eyeX -= 1; //on se déplace sur la gauche
	if (keystates[keyconf["strafe_right"]])
		eyeX += 1;
	*/
	glPushMatrix();
	gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, 0, 1, 0);
	//glRotatef(vertical, 1, 0, 0);
	//glRotatef(horizontal, 0, 1, 0);
	//glTranslatef(translationMatrix[0], translationMatrix[1], translationMatrix[2]);
	glPopMatrix();
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

void Engine::initTextures()
{
	/*
	GLubyte Texture[16] =
	{
		0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0
	};*/
	int widthGrass, heightGrass, widthStone, heightStone;
	unsigned char* texGrass = SOIL_load_image("OBJ/grass.jpg", &widthGrass, &heightGrass, 0, SOIL_LOAD_RGBA);
	unsigned char* texStone = SOIL_load_image("OBJ/stone.jpg", &widthStone, &heightStone, 0, SOIL_LOAD_RGBA);

	glEnable(GL_TEXTURE_2D);
	
	glGenTextures(1, &grass);
	glGenTextures(1, &stone);
	glBindTexture(GL_TEXTURE_2D, grass);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		widthGrass,
		heightGrass,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		texGrass
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, stone);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		widthStone,
		heightStone,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		texStone
		);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Engine::DrawGround()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			glPushMatrix();
			glTranslatef(i*100.0, 0.0, j*100.0);
			DrawObject(ground);
			glPopMatrix();
		}
	}
}


void Engine::InitKeyConf()
{	
	keyconf["forward"] = 0x5A;
	keyconf["backward"] = 0x53;
	keyconf["strafright"] = 0x44;
	keyconf["strafleft"] = 0x51;
	keyconf["up"] = VK_SPACE;
	keyconf["down"] = VK_LCONTROL;
	
	keystates[keyconf["forward"]] = false;
	keystates[keyconf["backward"]] = false;
	keystates[keyconf["strafleft"]] = false;
	keystates[keyconf["strafright"]] = false;
	keystates[keyconf["up"]] = false;
	keystates[keyconf["down"]] = false;
}
