#include <windows.h>
#include "GL/gl.h"
#include "glut.h"

#include "Ghost.h"
#include "Plane.h"
#include "Consts.h"
#include "Textures.h"

const int Plane::_map[_len][_wid] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1 },
		{ 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1 },
		{ 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1 },
		{ 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1 },
		{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1 },
		{ 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

Plane::Plane()
{
	createFieldsFromMap();

	Drawable::setMaterial(
		new GLfloat[4] {0.5f, 0.2f, 0.2f, 1.0},
		new GLfloat[4] {1.0f, 0.5f, 0.5f, 1.0},
		new GLfloat[4] {0.5f, 0.2f, 0.2f, 1.0},
		100
		);
}

void Plane::createGhosts(int count)
{
	static const std::vector<std::pair<int, int>> ghostFieldsCoords = { 
		std::make_pair(10, 8), std::make_pair(10, 9), std::make_pair(10, 10), std::make_pair(10, 11), std::make_pair(10, 12), std::make_pair(10, 13),
		std::make_pair(11, 9), std::make_pair(11, 10), std::make_pair(11, 11), std::make_pair(11, 12),
		std::make_pair(12, 9), std::make_pair(12, 10), std::make_pair(12, 11), std::make_pair(12, 12),
	};
	while (count-- > 0)
	{
		std::pair<int, int> coords = ghostFieldsCoords[rand() % ghostFieldsCoords.size()];
		_fields[coords.first][coords.second]->addCreature(new Ghost());
	}
}

void Plane::start(Pacman* pacman, int ghostCount)
{
	_fields[20][11]->addCreature(pacman);
	createGhosts(ghostCount);
}

Plane::~Plane()
{
}

void Plane::draw() const
{

	glPushMatrix();
		Drawable::draw();

		//place the plane in center
		glTranslatef(-_wid/2, 0, _len/2);

		
		static float texRepeat = 1;

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, Textures::getTexGround());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glPushMatrix();
			glBegin(GL_QUADS);
			glNormal3d(0, 1, 0);
			//draw a few times to make mesh more dense
			for (int i = 1; i < _len; ++i)
			{
				for (int j = 1; j < _wid; ++j)
				{
					glTexCoord2f(0.0f, texRepeat); glVertex3f(j - 1, 0, -i + 1);
					glTexCoord2f(texRepeat, texRepeat); glVertex3f(j, 0, -i + 1);
					glTexCoord2f(texRepeat, 0.0f); glVertex3f(j, 0, -i);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(j - 1, 0, -i);
				}
			}
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		//draw each field of plane
		for (int i = 0; i < _len; ++i)
		{
			for (int j = 0; j < _wid; ++j)
			{
				glPushMatrix();
					//place the field properly to the plane.
					glTranslatef(j, 0, -i);
					_fields[i][j]->draw();
					_fields[i][j]->updateCreatures();
				glPopMatrix();
			}
		}
	glPopMatrix();
}

void Plane::createFieldsFromMap()
{
	//create fields and mark them as allowed or dissallowed
	for (int i = 0; i < _len; ++i)
	{
		_fields.push_back(std::vector<Field*>());
		for (int j = 0; j < _wid; ++j)
		{
			Field::Type fieldType = _map[i][j] == 0 ? Field::Type::Allowed : Field::Type::Disallowed;
			_fields[i].push_back(new Field(fieldType));
		}
	}

	//establish relationsh of neighbourhood between fields
	Direction directions[4] = { Direction::South, Direction::North, Direction::West, Direction::East };
	Field* nullField = new Field(Field::Type::NonExistent);
	for (int i = 0; i < _len; ++i)
	{
		for (int j = 0; j < _wid; ++j)
		{
			Field* current = _fields[i][j];
			for (Direction direction : directions)
			{
				std::pair<int, int> change = directionToCoordinateChange.find(direction)->second;
				int neigh_i = i - change.second;
				int neigh_j = j - change.first;
				if (neigh_i < 0 || neigh_i >= _len || neigh_j < 0 || neigh_j >= _wid)
				{
					current->setNeighbour(direction, nullField);
				}
				else
				{
					current->setNeighbour(direction, _fields[neigh_i][neigh_j]);
				}
			}
		}
	}
}

//removes all creatures from plane and returns them from function
std::set<Creature*> Plane::clearCreatures()
{
	std::set<Creature*> toReturn;
	for (auto row : _fields)
	{
		for (auto field : row)
		{
			auto fieldCollection = field->clearCreatures();
			toReturn.insert(fieldCollection.begin(), fieldCollection.end());
		}
	}
	return toReturn;
}