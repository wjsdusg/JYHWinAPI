#include "Bomb.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

Bomb::Bomb()
{
}

Bomb::~Bomb()
{
}

void Bomb::Start()
{
	{
		GameEngineRender* AnimationRender = CreateRender(CrazyRenderOrder::Item);
		AnimationRender->SetPosition(GameEngineWindow::GetScreenSize().half());
		AnimationRender->CreateAnimation({ .AnimationName="Bomb",.ImageName="Bomb.BMP",.Start=0,.End=3,.InterTime=0.2f});
		AnimationRender->SetScale(float4{ 40.0f,40.0f });
		AnimationRender->ChangeAnimation("Bomb");
	}

}