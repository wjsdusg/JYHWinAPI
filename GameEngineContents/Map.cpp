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
		/*float4 Map
		
		
= GameEngineWindow::GetScreenSize().half();
		MapSize.x -= 80.0f;*/

		AnimationRender->SetImageToScaleToImage("Camp_Back.Bmp");
		float4 MapSize = AnimationRender->GetScale().half();
		MapSize.x += 20.0f;
		MapSize.y += 40.0f;
		
		AnimationRender->SetPosition(MapSize);
		
		//600,520
		
	//	AnimationRender->SetPosition(AnimationRender->GetScale());
		AnimationRender->SetImage("Camp_Back.Bmp");
		// AnimationRender->ChangeAnimation("Loop");
	}

}