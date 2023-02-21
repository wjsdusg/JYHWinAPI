#include "Block.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineTileMap.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
Block::Block()
{
}

Block::~Block()
{
}

Block* Block::OwnerBlock=nullptr;


void Block::Start()
{
	OwnerBlock = this;
	NewGameEngineTileMap =GetLevel()->CreateActor<GameEngineTileMap>();
	NewGameEngineTileMap->SetPos(float4(20, 40));
	NewGameEngineTileMap->CreateTileMap(XTileNum, YTileNum, 10, static_cast<int>(CrazyRenderOrder::Block), float4(40, 40));
	NewGameEngineTileMap->SetFloorSetting(static_cast<int>(BlockType::Block1), "Block1.bmp");
	NewGameEngineTileMap->SetFloorSetting(static_cast<int>(BlockType::Block2), "Block2.bmp");
	NewGameEngineTileMap->SetFloorSetting(static_cast<int>(BlockType::WoodBlock), "WoodBlock.bmp");
	NewGameEngineTileMap->SetFloorSetting(static_cast<int>(BlockType::TownBush), "TownBush.bmp");
	NewGameEngineTileMap->SetFloorSetting(static_cast<int>(BlockType::Wood3Block), "Wood3Block.bmp");
	//NewGameEngineTileMap->SetTileFrame(0, 0,0, 0);


	//MapSize.x += 20.0f;
	//MapSize.y += 40.0f;
	
}

void Block::ItemCountInsert(ItemType _Type, int _Count)
{
	ItemCounts[_Type] = _Count;
}

// 이걸 호출하는 순간 블록에 맞춰서 아이템을 만든다.
void Block::ItemCreate()
{

}

bool Block::IsBlock(float4 _Pos) 
{
	
	 // += NewGameEngineTileMap->GetPos()
	
	
	GameEngineRender* TilePtr = NewGameEngineTileMap->GetTile(0, _Pos);
	if (nullptr == TilePtr)
	{
		return false;
	}

	bool check = TilePtr->IsUpdate();
	return check;


	//return NewGameEngineTileMap->GetTile(0, float4(1, 0))->IsUpdate();
}

bool Block::IsMapOut(float4 _Pos) {
	float4 Pos = NewGameEngineTileMap->GetIndex(_Pos);
	if (false == NewGameEngineTileMap->IsValidIndex(0, Pos.y, Pos.x))
	{
		return true;
	}
	return false;
}