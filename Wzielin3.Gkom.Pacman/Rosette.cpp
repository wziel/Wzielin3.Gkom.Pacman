#include<math.h>
#include "Rosette.h"


Rosette::Rosette(float radius, float height, int sections, int cycles)
	:_radius(radius), _height(height), _sections(sections), _cycles(cycles)
{
	_indicesCount = _sections * _cycles * 4;
	_vertexCount = _sections * _cycles * 2;

	_vertices = new GLfloat[_vertexCount * 3];
	_indices = new GLushort[_indicesCount];
	_normals = new GLfloat[_vertexCount * 3];

	calculateVerts();
	calculateIndices();
	calculateNormals();
}

void Rosette::calculateVerts()
{
	int offset = 0;
	for (int cycle = 0; cycle < _cycles; cycle++)
	{
		for (int section = 0; section < _sections; section++)
		{
			float angle = (cycle * _sections + section) / (float)(_cycles * _sections) * 2.0f * 3.14f;
			float lengthAngle = section / (float)_sections * 2.0f * 3.14f;
			_vertices[offset + 0] = _radius * sin(angle);
			_vertices[offset + 1] = 0.01;
			_vertices[offset + 2] = _radius * cos(angle);
			offset += 3;

			_vertices[offset + 0] = _radius * sin(angle);
			_vertices[offset + 1] = _height / 2 * cos(lengthAngle) - _height / 2;
			_vertices[offset + 2] = _radius * cos(angle);
			offset += 3;
		}
	}
}

void Rosette::calculateIndices()
{
	int offset = 0;
	for (int i = 0; i < _vertexCount - 2; i += 2)
	{
		_indices[offset + 0] = i;
		_indices[offset + 1] = i + 1;
		_indices[offset + 2] = i + 3;
		_indices[offset + 3] = i + 2;
		offset += 4;
	}
	_indices[_indicesCount - 1] = 0;
	_indices[_indicesCount - 2] = 1;
	_indices[_indicesCount - 3] = _vertexCount - 1;
	_indices[_indicesCount - 4] = _vertexCount - 2;
}

void Rosette::calculateNormals()
{
	int offset = 0;
	for (int i = 0; i < _vertexCount; ++i)
	{
		_normals[offset + 0] = _vertices[offset + 0];
		_normals[offset + 1] = 0;
		_normals[offset + 2] = _vertices[offset + 2];
		offset += 3;
	}
}

void Rosette::draw() const
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glPushMatrix();
	glVertexPointer(3, GL_FLOAT, 0, _vertices);

	glNormalPointer(GL_FLOAT, 0, _normals);
	glDrawElements(GL_QUADS, _indicesCount, GL_UNSIGNED_SHORT, _indices);

	glPopMatrix();
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

Rosette::~Rosette()
{
}
