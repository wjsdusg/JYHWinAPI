#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <map>
#include "ContentsEnums.h"

// ???? :
class GameEngineTileMap;
class Player;
class Bomb;
class Monster;
class Block : public GameEngineActor
{
	friend Player;
	friend Bomb;
	friend Monster;
	// LevelStart???? ?? OwnerBlock?? ???? ??ä?????? ?Ѵ?.
// ???? ???????? ????.
public:
	static Block* OwnerBlock;
	void  AllBlockDestroy();

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
	void MoveWoodBlock(GameEngineRender* _GameEngineRender, float4 StartPos, float4 TargetPos, float _DeltaTime);
	
protected:
	void Start() override;
	void Update(float DeltaTime) override;
private:
	GameEngineTileMap* NewGameEngineTileMap=nullptr;
	std::map<ItemType, int> ItemCounts;

	float BlockMoveTime = 0.0f;

};
