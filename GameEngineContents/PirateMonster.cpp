#include "PirateMonster.h"

#include <GameEnginePlatform/GameEngineWindow.h>


PirateMonster::PirateMonster()
{
}

PirateMonster::~PirateMonster()
{
}

void PirateMonster::Start() {
	NewMonsterDirection = static_cast<MonsterDirection>(GameEngineRandom::MainRandom.RandomInt(static_cast<int>(MonsterDirection::Left), static_cast<int>(MonsterDirection::Right)));
	
	SetPos(GameEngineWindow::GetScreenSize().half() + float4{ 200,0 });
	AnimationRender = CreateRender(CrazyRenderOrder::Monster);
	AnimationRender->SetScale({ 40, 40 });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_Up",  .ImageName = "Monster.bmp", .Start = 0, .End = 1,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_Down",  .ImageName = "Monster.bmp", .Start = 2, .End = 3,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_Left",  .ImageName = "Monster.bmp", .Start = 4, .End = 5,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_Right",  .ImageName = "Monster.bmp", .Start = 6, .End = 7,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "die",  .ImageName = "monsterdie.bmp", .Start = 0, .End = 3,.InterTime = 0.2f });
	AnimationRender->ChangeAnimation("Move_Left");
}

void PirateMonster::Update(float _DeltaTime) {

	UpdateState(_DeltaTime);

}