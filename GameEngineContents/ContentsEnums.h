#pragma once

enum class CrazyRenderOrder
{
	BackGround,
	Map,
	MapCover,
	Block,
	DropItem,
	Item=50,
	Bomb,
	BombPower,
	BombtoPlayer,
	Monster,
	Player=70,
};

enum class ItemType
{
	Skate,
	Bomb,
	PowerMax,
	Shop,
	Kick,
	Max
};
enum class BlockType
{
	Block1,
	WoodBlock,
	TownBush,
	Wall,
	Max
	
};

