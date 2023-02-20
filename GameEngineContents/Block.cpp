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
	NewGameEngineTileMap->CreateTileMap(XTileNum, YTileNum, 3, static_cast<int>(CrazyRenderOrder::Block), float4(40, 40));
	NewGameEngineTileMap->SetFloorSetting(0, "Block1.bmp");
	//NewGameEngineTileMap->SetTileFrame(0, 0,0, 0);

	NewGameEngineTileMap->SetTileFrame(0, 1,0, 0);
	NewGameEngineTileMap->SetTileFrame(0, 3, 6, 0);
	//MapSize.x += 20.0f;
	//MapSize.y += 40.0f;
	
}

bool Block::IsBlock(float4 _Pos) 
{
	
	_Pos; // += NewGameEngineTileMap->GetPos()
	
	float4 Pos = NewGameEngineTileMap->GetIndex(_Pos);
	if (false == NewGameEngineTileMap->IsValidIndex(0, Pos.y, Pos.x))
	{
		return true;
	}

	GameEngineRender* TilePtr = NewGameEngineTileMap->GetTile(0, _Pos);
	if (nullptr == TilePtr)
	{
		return true;
	}

	bool check = TilePtr->IsUpdate();
	return check;


	//return NewGameEngineTileMap->GetTile(0, float4(1, 0))->IsUpdate();
}