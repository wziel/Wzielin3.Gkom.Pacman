#include "Sphere.h"
#include<math.h>

Sphere::Sphere(float size, int splices, int sections)
	:size(size), splices(splices), sections(sections)
{
	this->size /= 2;

	vertexCount = (sections + 2) * splices;
	indicesCount = (sections + 1) * (splices - 1) * 4;

	vertices = new GLfloat[vertexCount * 3];
	indices = new GLushort[indicesCount];

	normalsInverted = new GLfloat[vertexCount * 3];
	indicesInverted = new GLushort[indicesCount];

	calculateVerts();
	calculateIndices();
	calculateNormals();
}

void Sphere::calculateNormals()
{
	for (int i = 0; i < vertexCount * 3; ++i)
	{
		normalsInverted[i] = -vertices[i];
	}
}


void Sphere::calculateVerts()
{
	int offset = 0;
	for (int section = 0; section < sections + 2; section++)
	{
		float angleSection = section / (float)sections * 2.0f * 3.14f;
		for (int splice = 0; splice < splices; splice++)
		{
			float angleSplice = splice / (float)(splices - 1) * 3.14f / 2;
			vertices[offset + 0] = size * sin(angleSection) * cos(angleSplice);
			vertices[offset + 1] = size * -sin(angleSplice);
			vertices[offset + 2] = size * cos(angleSection) * cos(angleSplice);
			offset += 3;
		}
	}
}

void Sphere::calculateIndices()
{
	int offset = 0;
	for (int section = 0; section < sections + 1; section++)
	{
		for (int splice = 0; splice < splices - 1; splice++)
		{
			indices[offset + 0] = section * splices + splice;
			indices[offset + 1] = section * splices + splice + 1;
			indices[offset + 2] = (section + 1) * splices + splice + 1;
			indices[offset + 3] = (section + 1) * splices + splice;

			indicesInverted[offset + 0] = (section + 1) * splices + splice;
			indicesInverted[offset + 1] = (section + 1) * splices + splice + 1;
			indicesInverted[offset + 2] = section * splices + splice + 1;
			indicesInverted[offset + 3] = section * splices + splice;

			offset += 4;
		}
	}
}

void Sphere::draw() const
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glPushMatrix();
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	//in case of sphere normals are the same as vertex coordinates
	glNormalPointer(GL_FLOAT, 0, vertices);
	glDrawElements(GL_QUADS, indicesCount, GL_UNSIGNED_SHORT, indices);

	//static GLfloat insideDiffuse[4] = { 0, 0, 0, 1 };
	//glNormalPointer(GL_FLOAT, 0, normalsInverted);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, insideDiffuse);
	//glDrawElements(GL_QUADS, indicesCount, GL_UNSIGNED_SHORT, indicesInverted);

	glPopMatrix();
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

Sphere::~Sphere()
{
}
