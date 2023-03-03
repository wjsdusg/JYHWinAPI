#include "Monster.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "ContentsEnums.h"
Monster::Monster() 
{
}

Monster::~Monster() 
{
}

void Monster::Start() {
	SetMove(GameEngineWindow::GetScreenSize().half() + float4{ 200,0 });


	GameEngineRender* AnimationRender = CreateRender(CrazyRenderOrder::Monster);
	AnimationRender->SetScale({ 40, 40 });

	AnimationRender->CreateAnimation({ .AnimationName = "Idle",  .ImageName = "Monster.bmp", .Start = 2, .End = 4 });
	AnimationRender->ChangeAnimation("Idle");
}