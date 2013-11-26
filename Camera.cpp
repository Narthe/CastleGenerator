#include "Camera.h"
#include "GL/GLU.h"


// TUTO :  http://fr.openclassrooms.com/informatique/cours/creez-des-programmes-en-3d-avec-opengl/implementation-de-la-camera-1

Camera::Camera(const Vector3D & position)
{
	_position = position; //si aucune position n'est définie on reçoit quand même (0,0,0) en paramètre
	_phi = 0;
	_theta = 0;
	VectorsFromAngles(); //décrit un peu plus loin

	_speed = 0.01;
	_sensivity = 0.001;
	_verticalMotionActive = false;
	//Initialisation de la configuration des touches
	_keyconf["forward"] = 0x5A;
	_keyconf["backward"] = 0x53;
	_keyconf["strafright"] = 0x44;
	_keyconf["strafleft"] = 0x51;
	_keyconf["up"] = VK_SPACE;
	_keyconf["down"] = VK_LCONTROL;

	//Initialisation des KeyStates
	_keystates[_keyconf["forward"]] = false;
	_keystates[_keyconf["backward"]] = false;
	_keystates[_keyconf["strafleft"]] = false;
	_keystates[_keyconf["strafright"]] = false;
	_keystates[_keyconf["up"]] = false;
	_keystates[_keyconf["down"]] = false;
	_keystates[_keyconf["boost"]] = false;

}

void Camera::OnMouseMotion(POINT pos)
{
	_theta -= pos.x*_sensivity;
	_phi -= pos.y*_sensivity;
	VectorsFromAngles();
}

void Camera::VectorsFromAngles()
{
	static const Vector3D up(0, 1, 0); //une constante, le vecteur vertical du monde, utilisé dans les calculs
	//On limite les valeurs de _phi, on vole certes, mais on en fait pas de loopings :p
	if (_phi > 89)
		_phi = 89;
	else if (_phi < -89)
		_phi = -89;
	//passage des coordonnées sphériques aux coordonnées cartésiennes
	double r_temp = cos(_phi*M_PI / 180);
	_forward.Z = sin(_phi*M_PI / 180);
	_forward.X = r_temp*cos(_theta*M_PI / 180);
	_forward.Y = r_temp*sin(_theta*M_PI / 180);

	_left = up.crossProduct(_forward);
	_left.normalize();

	//avec la position de la caméra et la direction du regard, on calcule facilement ce que regarde la caméra (la cible)
	_target = _position + _forward;
}

void Camera::OnKeyUp(int key)
{
	//on parcourt tous les keystates actuels
	for (KeyStates::iterator it = _keystates.begin(); it != _keystates.end();
		it++)
	{
		if (key == it->first) //est-ce que la touche responsable de l'événement est celle du keystate ?
		{
			it->second = false;
			break; //la touche responsable de l'événement a été utilisée, on quitte le for
		}
	}
}

void Camera::OnKeyDown(int key)
{
	//on parcourt tous les keystates actuels
	for (KeyStates::iterator it = _keystates.begin(); it != _keystates.end();
		it++)
	{
		if (key == it->first) //est-ce que la touche responsable de l'événement est celle du keystate ?
		{
			it->second = true;
			break; //la touche responsable de l'événement a été utilisée, on quitte le for
		}
	}
}

void Camera::animate(int timestep)
{
	//la vitesse réelle du déplacement est soit la vitesse de croisière, soit 10*la vitesse, en fonction
	//de l'état enfoncé ou non de la touche correspondant à l'action "boost"
	double realspeed = (_keystates[_keyconf["boost"]]) ? 10 * _speed : _speed;
	if (_keystates[_keyconf["forward"]])
		_position += _forward * (realspeed * timestep); //on avance
	if (_keystates[_keyconf["backward"]])
		_position -= _forward * (realspeed * timestep); //on recule
	if (_keystates[_keyconf["strafe_left"]])
		_position += _left * (realspeed * timestep); //on se déplace sur la gauche
	if (_keystates[_keyconf["strafe_right"]])
		_position -= _left * (realspeed * timestep); //on se déplace sur la droite
	if (_verticalMotionActive)
	{
		if (timestep > _timeBeforeStoppingVerticalMotion)
			_verticalMotionActive = false;
		else
			_timeBeforeStoppingVerticalMotion -= timestep;
		//_position += Vector3D(0, 0, _verticalMotionDirection*realspeed*timestep); //on monte ou on descend, en fonction de la valeur de _verticalMotionDirection
	}
	_target = _position + _forward; //comme on a bougé, on recalcule la cible fixée par la caméra

}

void Camera::look()
{
	gluLookAt(_position.X, _position.Y, _position.Z, _target.X, _target.Y, _target.Z, 0, 1, 0);
}

void Camera::setSpeed(double speed)
{
	_speed = speed;
}

void Camera::setSensivity(double sensivity)
{
	_sensivity = sensivity;
}

void Camera::setPosition(const Vector3D & position)
{
	_position = position;
	_target = _position + _forward;
}