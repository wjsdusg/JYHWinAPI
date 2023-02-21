#pragma once

enum class CrazyRenderOrder
{
	BackGround,
	Map,
	MapCover,
	Block,
	DropItem,
	Item=500,
	Player=1000,
};

enum class ItemType
{
	Skate,
	Bomb,
	PowerMax,
	Max
};