#pragma once
#include<vector>

#include "Field.h"
#include "Pacman.h"

///Class that defines a plane on which pacman game is played
class Plane :
	public Drawable
{
private:
	//y distance
	static const int _len = 24;
	//x distance
	static const int _wid = 22;
	static const int _map[_len][_wid];

	std::vector<std::vector<Field*>> _fields;
	
	void createFieldsFromMap();
	void createGhosts(int count);
public:
	Plane();
	virtual ~Plane();

	void start(Pacman* pacman, int ghostCount);
	void virtual draw() const override;
	std::set<Creature*> clearCreatures();
};

