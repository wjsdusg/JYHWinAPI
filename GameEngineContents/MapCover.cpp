#include "MapCover.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

MapCover::MapCover()
{
}

MapCover::~MapCover()
{
}


void MapCover::Start()
{
	{
		// float4 Scree = GameEngineWindow::GetScreenSize();

		GameEngineRender* AnimationRender = CreateRender(CrazyRenderOrder::MapCover);
		/*float4 MapSize = GameEngineWindow::GetScreenSize().half();
		MapSize.x -= 80.0f;*/

		AnimationRender->SetImageToScaleToImage("Camp_Front.Bmp");
		float4 MapSize = AnimationRender->GetScale().half();
		MapSize.x += 20.0f;
		//MapSize.y += 20.0f;

		AnimationRender->SetPosition(MapSize);

		//600,520

	//	AnimationRender->SetPosition(AnimationRender->GetScale());
		AnimationRender->SetImage("Camp_Front.Bmp");
		// AnimationRender->ChangeAnimation("Loop");
	}

}