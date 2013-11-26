#pragma once
#define _USE_MATH_DEFINES


#include "Vector3d.h"
#include <map>
#include <string>
#include <windows.h>
#include <cmath>

class Camera
{
public:
	static Camera *GetInstance(void) { return(g_CameraInstance); }

	Camera(const Vector3D & position = Vector3D(0, 0, 0));

	virtual void OnMouseMotion(POINT pos);
	//virtual void OnMouseButton(int event);
	virtual void OnKeyUp(int key);
	virtual void OnKeyDown(int key);

	virtual void animate(int timestep);
	virtual void setSpeed(double speed);
	virtual void setSensivity(double sensivity);

	virtual void setPosition(const Vector3D & position);

	virtual void look();

	//virtual ~Camera();

protected:
	static Camera *g_CameraInstance;

	double _speed;
	double _sensivity;

	int _timeBeforeStoppingVerticalMotion;
	bool _verticalMotionActive;
	int _verticalMotionDirection;

	typedef std::map<int, bool> KeyStates;
	KeyStates _keystates;
	typedef std::map<std::string, int> Keyconf;
	Keyconf _keyconf;

	Vector3D _position;
	Vector3D _target;
	Vector3D _forward;
	Vector3D _left;
	double _theta;
	double _phi;

	void VectorsFromAngles();
};

