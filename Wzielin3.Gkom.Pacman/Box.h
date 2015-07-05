#pragma once
#include <windows.h>
#include "GL/gl.h"
#include "glut.h"

#include "Drawable.h"
class Box :
	public Drawable
{
private:

	const GLfloat _size;
	const GLenum _type;

	static const GLfloat normals[6][3];
	static const GLint faces[6][4];

	GLfloat vertices[8][3];
	GLfloat textureCoords[4][2];
	GLuint texture;

	void drawCube() const;
public:
	Box(GLfloat size, GLenum type, GLuint texture);
	~Box();
	virtual void draw() const;
};

