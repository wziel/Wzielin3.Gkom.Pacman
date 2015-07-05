#pragma once
#include "Drawable.h"
class Bonus :
	public Drawable
{
private:
	float height;
	static const float MAX_HEIGHT;
	static const float MIN_HEIGHT;
	static const float MOVE_SPEED;
	bool animatingUp;

	int _points;
public:
	Bonus(int points);
	virtual ~Bonus();
	virtual void update();

	int getPoints() const;
	virtual void draw() const = 0;
};

