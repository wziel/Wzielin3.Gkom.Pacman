#include "Box.h"

const GLfloat Box::normals[6][3] =
{
	{ -1.0, 0.0, 0.0 },
	{ 0.0, 1.0, 0.0 },
	{ 1.0, 0.0, 0.0 },
	{ 0.0, -1.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{ 0.0, 0.0, -1.0 }
};

const GLint Box::faces[6][4] =
{
	{ 0, 1, 2, 3 },
	{ 3, 2, 6, 7 },
	{ 7, 6, 5, 4 },
	{ 4, 5, 1, 0 },
	{ 5, 6, 2, 1 },
	{ 7, 4, 0, 3 }
};

Box::Box(GLfloat size, GLenum type, GLuint texture) : _size(size), _type(type), texture(texture)
{

	vertices[0][0] = vertices[1][0] = vertices[2][0] = vertices[3][0] = 0;
	vertices[4][0] = vertices[5][0] = vertices[6][0] = vertices[7][0] = size;
	vertices[0][1] = vertices[1][1] = vertices[4][1] = vertices[5][1] = 0;
	vertices[2][1] = vertices[3][1] = vertices[6][1] = vertices[7][1] = size;
	vertices[0][2] = vertices[3][2] = vertices[4][2] = vertices[7][2] = 0;
	vertices[1][2] = vertices[2][2] = vertices[5][2] = vertices[6][2] = -size;

	float s = 0.2; //width and length for texture
	float r = ((float)rand() / RAND_MAX) * (1 - s); //random factor for texture

	textureCoords[0][0] = r;
	textureCoords[0][1] = r + s;
	textureCoords[1][0] = r + s;
	textureCoords[1][1] = r + s;
	textureCoords[2][0] = r + s;
	textureCoords[2][1] = r;
	textureCoords[3][0] = r;
	textureCoords[3][1] = r;
}


Box::~Box()
{
}

void Box::draw() const
{
	glPushMatrix(); 
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture);
			glPushMatrix();
				drawCube();
			glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void Box::drawCube() const
{
	for (int i = 5; i >= 0; i--) {
		glBegin(_type);
		glNormal3fv(&normals[i][0]);
		glTexCoord2f(textureCoords[0][0], textureCoords[0][1]);		glVertex3fv(&vertices[faces[i][0]][0]);
		glTexCoord2f(textureCoords[1][0], textureCoords[1][1]);		glVertex3fv(&vertices[faces[i][1]][0]);
		glTexCoord2f(textureCoords[2][0], textureCoords[2][1]);		glVertex3fv(&vertices[faces[i][2]][0]);
		glTexCoord2f(textureCoords[3][0], textureCoords[3][1]);		glVertex3fv(&vertices[faces[i][3]][0]);
		glEnd();
	}
}
