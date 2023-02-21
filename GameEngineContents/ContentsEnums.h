#pragma once

enum class CrazyRenderOrder
{
	BackGround,
	Map,
	MapCover,
	Block,
	DropItem,
	Item=500,
	Bomb,
	BombPower,
	Player=1000,
};

enum class ItemType
{
	Skate,
	Bomb,
	PowerMax,
	Max
};
enum class BlockType
{
	Block1,
	Block2,
	WoodBlock,
	TownBush,
	Wood3Block
};
