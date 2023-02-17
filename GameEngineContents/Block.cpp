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


void Block::Start()
{
	
	NewGameEngineTileMap =GetLevel()->CreateActor<GameEngineTileMap>();
	NewGameEngineTileMap->CreateTileMap(XTileNum, YTileNum, 3, static_cast<int>(CrazyRenderOrder::Block), float4(40, 40));
	NewGameEngineTileMap->SetFloorSetting(0, "Block1.bmp");
	NewGameEngineTileMap->SetTileFrame(0, float4{20,40}, 0);
	//MapSize.x += 20.0f;
	//MapSize.y += 40.0f;
	
}