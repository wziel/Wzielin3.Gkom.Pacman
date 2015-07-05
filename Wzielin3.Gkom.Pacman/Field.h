#pragma once
#include <map>
#include <set>

#include "Creature.h"
#include "Bonus.h"
#include "Box.h"

///Class defining single field of the plane
class Field : public Drawable
{
public:
	enum Type
	{
		Allowed = 0,
		Disallowed = 1,
		NonExistent = 2,
	};

private:
	//specifies whether field can be entered by player
	Type _type;
	Field* _neighbours[4];
	std::set<Creature*> _creatures;
	Bonus* bonus;
	Box* wall;

	bool tryTurn(Creature* creature, Direction direction);
	bool checkForTurn(Creature * creature);
	bool checkForFieldChange(Creature * creature);

public:
	Field(Type type);
	virtual ~Field();
	bool isAllowed() const;
	void virtual draw() const;

	Field* getNeighbour(Direction dir) const;
	void setNeighbour(Direction dir, Field* neighbour);

	void updateCreatures();
	void addCreature(Creature* creature);
	std::set<Creature*> clearCreatures();
};