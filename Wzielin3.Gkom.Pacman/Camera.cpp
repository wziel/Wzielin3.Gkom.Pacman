#include <windows.h>
#include <math.h>
#include <map>

#include "GL/gl.h"
#include "glut.h"
#include "Camera.h"

const float Camera::DEF_Z = 0;
const float Camera::DIF_Z = 0.2;

const float Camera::DEF_X = 0;
const float Camera::DIF_X = 0.2;

const float Camera::MIN_YANGLE = 1.7;
const float Camera::MAX_YANGLE = 2.7;
const float Camera::DEF_YANGLE = 2.2;
const float Camera::DIF_YANGLE = 0.01;

const float Camera::MIN_RADIUS = 5;
const float Camera::DEF_RADIUS = 14;
const float Camera::DIF_RADIUS = 0.2;

const float Camera::DEF_XANGLE = 0;
const float Camera::DIF_XANGLE = 0.01;

Camera::Camera()
{
	_x = DEF_X;
	_z = DEF_Z;
	_Yangle = DEF_YANGLE;
	_Xangle = DEF_XANGLE;
	_radius = DEF_RADIUS;
}


Camera::~Camera()
{
}

void Camera::createLook() const
{
		gluLookAt(
			//eye position
			_radius * cos(_Yangle) * sin(_Xangle) + _x, 
			_radius * sin(_Yangle), 
			_radius * cos(_Yangle) * cos(_Xangle) + _z, 
			//what am i looking at
			_x, 
			0, 
			_z,		
			//up vector
			0, 1, 0);		
}

void Camera::registerEvent(CameraMovemement movement, KeyEvent keyEvent)
{
	if (keyEvent == KeyEvent::Pressed)
	{
		registeredMovememnts.insert(movement);
	}
	else
	{
		registeredMovememnts.erase(movement);
	}
}

void Camera::move()
{
	for (auto movement : registeredMovememnts)
	{
		move(movement);
	}
}

void Camera::move(CameraMovemement movement)
{
	if (movement == CameraMovemement::Up)
	{
		if (_Yangle > MIN_YANGLE)
			_Yangle -= DIF_YANGLE;
	}
	else if (movement == CameraMovemement::Down)
	{
		if (_Yangle < MAX_YANGLE)
			_Yangle += DIF_YANGLE;
	}
	else if (movement == CameraMovemement::Closer)
	{
		if (_radius > MIN_RADIUS)
			_radius -= DIF_RADIUS;
	}
	else if (movement == CameraMovemement::Further)
	{
		_radius += DIF_RADIUS;
	}
	else if (movement == CameraMovemement::RotLeft)
	{
		_Xangle -= DIF_XANGLE;
	}
	else if (movement == CameraMovemement::RotRight)
	{
		_Xangle += DIF_XANGLE;
	}
	else if (movement == CameraMovemement::Forward)
	{
		_z += DIF_Z * cos(_Xangle);
		_x += DIF_X * sin(_Xangle);
	}
	else if (movement == CameraMovemement::Backward)
	{
		_z -= DIF_Z * cos(_Xangle);
		_x -= DIF_X * sin(_Xangle);
	}
	else if (movement == CameraMovemement::Left)
	{
		_x -= DIF_X * cos(_Xangle);
		_z += DIF_Z * sin(_Xangle);
	}
	else if (movement == CameraMovemement::Right)
	{
		_x += DIF_X * cos(_Xangle);
		_z -= DIF_Z * sin(_Xangle);
	}
	else if (movement == CameraMovemement::Reset)
	{
		_x = DEF_X;
		_z = DEF_Z;
		_radius = DEF_RADIUS;
		_Yangle = DEF_YANGLE;
		_Xangle = DEF_XANGLE;
	}
}