#include <windows.h>
#include "GL/gl.h"
#include "glut.h"

#include "Field.h"
#include "Consts.h"
#include "PointBonus.h"
#include "MegaBonus.h"
#include "Pacman.h"
#include "Textures.h"

Field::Field(Type type)
{
	_type = type;
	if (type == Type::Allowed)
	{
		if (rand() % 10 < 1)
		{
			bonus = new MegaBonus(0.2);
		}
		else
		{
			bonus = new PointBonus();
		}
		wall = NULL;
	}
	else
	{
		bonus = NULL;
		wall = new Box(1, GL_QUADS, Textures::getTexWall());
	}

	Drawable::setMaterial(
		new GLfloat[4] {0.6f, 0.5, 0.5, 1.0},
		new GLfloat[4] {0.0f, 0.0f, 0.0f, 1.0},
		new GLfloat[4] {0.6f, 0.5, 0.5, 1.0},
		10
		);
}


Field::~Field()
{
	delete bonus;
}

void Field::draw() const
{
	//select color of field
	if (_type == Type::Disallowed)
	{
		glPushMatrix();
			Drawable::draw();
			wall->draw();
		glPopMatrix();
	}

	//draw bonus of this field if it exists
	if (bonus != NULL)
	{
		bonus->update();

		glPushMatrix();
			glTranslatef(0.5, 0, -0.5);
			bonus->draw();
		glPopMatrix();
	}

	//draw each creature on this field
	for (auto creature : _creatures)
	{
		creature->update();
		creature->draw();
	}
}


Field* Field::getNeighbour(Direction dir) const
{
	return _neighbours[dir];
}

void Field::setNeighbour(Direction dir, Field* field)
{
	_neighbours[dir] = field;
}

void Field::addCreature(Creature* creature)
{
	_creatures.insert(creature);

	//look for pacman in collection
	Pacman* pacman;
	for (Creature* creature : _creatures)
	{
		pacman = dynamic_cast<Pacman*>(creature);
		if (pacman != NULL)
		{
			break;
		}
	}

	if (pacman != NULL)
	{
		//we die
		if (_creatures.size() >= 2)
		{
			pacman->kill();
			return;
		}

		//check if bonus needs to be collected
		if (bonus != NULL)
		{
			pacman->addPoint(bonus->getPoints());
			delete bonus;
			bonus = NULL;
		}
	}
}

//updates position of all creatures on this field.
void Field::updateCreatures()
{
	std::set<Creature*> toBeDeleted;
	for (auto creature : _creatures)
	{
		creature->update();
		if (checkForFieldChange(creature))
		{
			toBeDeleted.insert(creature);
		}
		checkForTurn(creature);
	}
	for (auto creature : toBeDeleted)
	{
		_creatures.erase(creature);
	}
}

//check if creature needs to change field
bool Field::checkForFieldChange(Creature* creature)
{
	//have to change field of this creature
	if (abs(creature->getX()) > 0.7 || abs(creature->getY()) > 0.7)
	{
		Field* newField = getNeighbour(creature->getCurrentDirection());
		newField->addCreature(creature);

		std::pair<int, int> newCoords = directionToCoordinateChange.find(creature->getCurrentDirection())->second;
		creature->setX(newCoords.first * 0.3);
		creature->setY(-newCoords.second * 0.3);
		return true;
	}
	return false;
}

//check if creature needs to change diretion of its movement
bool Field::checkForTurn(Creature * creature)
{
	//turn around
	if (oppositeDirection.find(creature->getRequestedDirection())->second == creature->getCurrentDirection() &&
		getNeighbour(creature->getRequestedDirection())->_type == Type::Allowed)
	{
		creature->setCurrentDirection(creature->getRequestedDirection());
		creature->setSpeed(EPSILON);
		return true;
	}
	//creature is in the center of field so it can change direction
	if (abs(creature->getX()) < DOUBLE_EPSILON && abs(creature->getY()) < DOUBLE_EPSILON)
	{
		//turn left or right, or start moving entirely
		if (creature->getRequestedDirection() != creature->getCurrentDirection())
		{
			if (!tryTurn(creature, creature->getRequestedDirection()) &&
				!tryTurn(creature, creature->getCurrentDirection()))
			{
				creature->setSpeed(0);
				return false;
			}
			return true;
		}
		//stop the creature if there is nowhere to go
		if (getNeighbour(creature->getCurrentDirection())->_type != Type::Allowed)
		{
			creature->setSpeed(0);
		}
	}
	return false;
}

//make the turn if it's possible
bool Field::tryTurn(Creature* creature, Direction direction)
{
	Field* requested = getNeighbour(direction);
	if (requested->_type != Type::Allowed)
	{
		return false;
	}
	creature->setCurrentDirection(direction);
	creature->setSpeed(EPSILON);
	return true;
}

//removes all creatures from this field and returns them from function
std::set<Creature*> Field::clearCreatures()
{
	std::set<Creature*> toReturn = _creatures;
	_creatures.clear();
	return toReturn;
}