#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <map>
#include "ContentsEnums.h"

// ���� :
class GameEngineTileMap;
class Player;
class BombPower;
class Block : public GameEngineActor
{
	friend Player;
	friend BombPower;

	// LevelStart���� �� OwnerBlock�� ���� ��ä����� �Ѵ�.
// ���� ������� ����.
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
