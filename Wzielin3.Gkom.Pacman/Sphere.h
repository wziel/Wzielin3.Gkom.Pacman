#pragma once
#include <windows.h>
#include "GL/gl.h"
#include "glut.h"

#include "Drawable.h"
class Sphere :
	public Drawable
{
private:
	float size;
	int splices;
	int sections;

	int vertexCount;
	int indicesCount;

	GLfloat* vertices;
	GLushort* indices;

	GLfloat* normalsInverted;
	GLushort* indicesInverted;

	void calculateVerts();
	void calculateIndices();
	void calculateNormals();
public:
	Sphere(float size, int splices, int sections);
	~Sphere();

	virtual void draw() const;
};

