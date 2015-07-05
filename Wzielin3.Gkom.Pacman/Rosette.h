#pragma once
#include <windows.h>
#include "GL/gl.h"
#include "glut.h"

#include "Drawable.h"
class Rosette :
	public Drawable
{
private:
	float _radius;
	float _height;
	int _sections;
	int _cycles;

	int _vertexCount;
	int _indicesCount;

	GLfloat* _vertices;
	GLushort* _indices;
	GLfloat* _normals;

	void calculateVerts();
	void calculateIndices();
	void calculateNormals();

public:
	Rosette(float radius, float height, int sections, int cycles);
	~Rosette();

	virtual void draw() const;
};

