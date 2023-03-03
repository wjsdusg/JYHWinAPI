#include "MonsterMap.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

MonsterMap::MonsterMap()
{
}

MonsterMap::~MonsterMap()
{
}


void MonsterMap::Start()
{
	{
	
		GameEngineRender* AnimationRender = CreateRender(CrazyRenderOrder::Map);
		AnimationRender->SetImageToScaleToImage("MonsterStage2_Back.Bmp");
		float4 MapSize = AnimationRender->GetScale().half();
		MapSize.x += 20.0f;
		//MapSize.y += 40.0f;
		AnimationRender->SetPosition(MapSize);
		AnimationRender->SetImage("MonsterStage2_Back.Bmp");
		
	}

}