#pragma once
#include <string>
#include <ostream>


enum ItemType
{
	Weapon,
	Shield,
	Armor,
	Potion,
	Utility,
	Charm,
	Count
};

struct Item
{
	std::string name;
	uint32_t quantity;
	ItemType type;
};

