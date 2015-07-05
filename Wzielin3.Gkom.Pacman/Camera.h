
#pragma once
#include <set>
#include "Enums.h"

class Camera
{
private:
	//set of currently pressed keys
	std::set<CameraMovemement> registeredMovememnts;

	//position on sphere
	float _radius;
	//angle that makes camera go up
	float _Yangle;
	//angle that rotates camera around Y axis
	float _Xangle;

	//point i am looking at
	float _x;
	float _z;

	static const float DEF_X;
	static const float DIF_X;

	static const float DEF_Z;
	static const float DIF_Z;

	static const float MIN_YANGLE;
	static const float MAX_YANGLE;
	static const float DEF_YANGLE;
	static const float DIF_YANGLE;

	static const float MIN_RADIUS;
	static const float DEF_RADIUS;
	static const float DIF_RADIUS;

	static const float DEF_XANGLE;
	static const float DIF_XANGLE;

	void move(CameraMovemement movement);
public:
	void createLook() const;
	Camera();
	~Camera();

	void registerEvent(CameraMovemement movement, KeyEvent keyEvent);
	void move();
};

