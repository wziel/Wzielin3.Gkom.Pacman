#include "Background.h"
#include "Textures.h"

const float Background::MIN_FRAME = 0;
const float Background::MAX_FRAME = 50;
const float Background::DIF_FRAME = 0.5f;

Background::Background(float width, float length, int repeatX)
{
	_width = width;
	_length = length;
	_repeatX = repeatX;

	Drawable::setMaterial(
		new GLfloat[4] {3, 3, 3, 1.0},
		new GLfloat[4] {0, 0, 0, 0},
		new GLfloat[4] {0, 0, 0, 0},
		0
		);
}


Background::~Background()
{
}

void Background::update()
{
	_frameNo += DIF_FRAME;
	if (_frameNo >= MAX_FRAME)
	{
		_frameNo = MIN_FRAME;
	}
}

void Background::draw() const
{
	glPushMatrix();
		Drawable::draw();

		glTranslatef(-_width / 2, 0, _length / 2);

		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, Textures::getTexFire(_frameNo));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glPushMatrix();
				glBegin(GL_QUADS);
					glNormal3d(0, 1, 0);
					glTexCoord2f(0.0f, 0.7f);				glVertex3f(0, 0, 0);
					glTexCoord2f(_repeatX, 0.7f);			glVertex3f(_width, 0, 0);
					glTexCoord2f(_repeatX, 0.0f);		glVertex3f(_width, 0, -_length);
					glTexCoord2f(0.0f, 0.0f);			glVertex3f(0, 0, -_length);
				glEnd();
			glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}