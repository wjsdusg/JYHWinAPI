#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <map>
#include "ContentsEnums.h"

// 설명 :
class GameEngineTileMap;
class Player;
class BombPower;
class Block : public GameEngineActor
{
	friend Player;
	friend BombPower;

	// LevelStart에서 이 OwnerBlock을 꼐속 교채해줘야 한다.
// 걱정 까먹을것 같다.
public:
	static Block* OwnerBlock;


public:
	// constrcuter destructer
	Block();
	~Block();

	// delete Function
	Block(const Block& _Other) = delete;
	Block(Block&& _Other) noexcept = delete;
	Block& operator=(const Block& _Other) = delete;
	Block& operator=(Block&& _Other) noexcept = delete;
	bool IsBlock(float4 _Pos);
	bool IsMapOut(float4 _Pos);

	// 
	void ItemCountInsert(ItemType _Type, int _Count);

	void ItemCreate();

	GameEngineTileMap* GetTileMap() 
	{
		
		return NewGameEngineTileMap;
	}

protected:
	void Start() override;

private:
	GameEngineTileMap* NewGameEngineTileMap=nullptr;
	std::map<ItemType, int> ItemCounts;


};
