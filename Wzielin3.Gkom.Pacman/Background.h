#pragma once
#include "Drawable.h"
class Background :
	public Drawable
{
private:
	static const float MIN_FRAME;
	static const float MAX_FRAME;
	static const float DIF_FRAME;
	float _frameNo = 0;

	float _width;
	float _length;
	int _repeatX;
public:
	Background(float width, float height, int repeatX);
	~Background();
	virtual void draw() const;
	void update();
};

