#pragma once
#include<map>

#include "Enums.h"


const std::map<Direction, std::pair<int, int>> directionToCoordinateChange = 
{
	{ Direction::North, std::make_pair(0, 1) },
	{ Direction::South, std::make_pair(0, -1) },
	{ Direction::West, std::make_pair(-1, 0) },
	{ Direction::East, std::make_pair(1, 0) }
};

const std::map<unsigned char, Direction> keyToDirection = 
{
	{ 'w', Direction::North },
	{ 's', Direction::South },
	{ 'a', Direction::West },
	{ 'd', Direction::East },

	{ 'W', Direction::North },
	{ 'S', Direction::South },
	{ 'A', Direction::West },
	{ 'D', Direction::East },
};

const std::map<unsigned char, CameraMovemement> keyToCamera =
{
	{ 'i', CameraMovemement::Up },
	{ 'k', CameraMovemement::Down },
	{ 'j', CameraMovemement::RotLeft },
	{ 'l', CameraMovemement::RotRight },
	{ 'p', CameraMovemement::Further },
	{ 'o', CameraMovemement::Closer },
	{ 't', CameraMovemement::Forward },
	{ 'g', CameraMovemement::Backward },
	{ 'h', CameraMovemement::Left },
	{ 'f', CameraMovemement::Right },
	{ 'm', CameraMovemement::Reset },

	{ 'I', CameraMovemement::Up },
	{ 'K', CameraMovemement::Down },
	{ 'J', CameraMovemement::RotLeft },
	{ 'L', CameraMovemement::RotRight },
	{ 'P', CameraMovemement::Further },
	{ 'O', CameraMovemement::Closer },
	{ 'T', CameraMovemement::Forward },
	{ 'G', CameraMovemement::Backward },
	{ 'H', CameraMovemement::Left },
	{ 'F', CameraMovemement::Right },
	{ 'M', CameraMovemement::Reset },
};

const std::map<Direction, Direction> oppositeDirection = 
{
	{ Direction::South, Direction::North },
	{ Direction::North, Direction::South },
	{ Direction::East, Direction::West },
	{ Direction::West, Direction::East }
};

//used to determine proximity of objects
const float DOUBLE_EPSILON = 0.06;
//used for movememnt of creatures
const float EPSILON = 0.04;