#include "Map.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

Map::Map() 
{
}

Map::~Map() 
{
}


void Map::Start()
{
	{
		// float4 Scree = GameEngineWindow::GetScreenSize();

		GameEngineRender* AnimationRender = CreateRender(CrazyRenderOrder::Map);
		AnimationRender->SetPosition(GameEngineWindow::GetScreenSize().half());
		//AnimationRender->SetScale(GameEngineWindow::GetScreenSize());
		AnimationRender->SetImageToScaleToImage("Camp_Back.Bmp");
		AnimationRender->SetImage("Camp_Back.Bmp");
		// AnimationRender->ChangeAnimation("Loop");
	}

}