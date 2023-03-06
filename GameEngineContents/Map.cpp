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
		

		GameEngineRender* AnimationRender = CreateRender(CrazyRenderOrder::Map);
			
		AnimationRender->SetImageToScaleToImage("Camp_Back.Bmp");
		float4 MapSize = AnimationRender->GetScale().half();
		MapSize.x += 20.0f;
		MapSize.y += 40.0f;
		
		AnimationRender->SetPosition(MapSize);
		
		AnimationRender->SetImage("Camp_Back.Bmp");
		
	}

}