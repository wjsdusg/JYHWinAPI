#include "IceMonster.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>

IceMonster::IceMonster()
{
}

IceMonster::~IceMonster()
{
}

int IceMonster::num = 0;

void IceMonster::Start() {
	NewMonsterDirection = static_cast<MonsterDirection>(GameEngineRandom::MainRandom.RandomInt(static_cast<int>(MonsterDirection::Left), static_cast<int>(MonsterDirection::Right)));

	BodyCollision = CreateCollision(CrazyRenderOrder::Monster);
	BodyCollision->SetScale(float4(40, 40));

	SetPos(Block::OwnerBlock->GetTileMap()->ConvertIndexToTilePosition(MonstersPos[num]));

	num++;
	AnimationRender = CreateRender(CrazyRenderOrder::Monster);
	AnimationRender->SetScale({ 40, 40 });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_Up",  .ImageName = "iceMonster.bmp", .Start = 0, .End = 1,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_Down",  .ImageName = "iceMonster.bmp", .Start = 2, .End = 3,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_Left",  .ImageName = "iceMonster.bmp", .Start = 6, .End = 7,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_Right",  .ImageName = "iceMonster.bmp", .Start = 4, .End = 5,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Ice",  .ImageName = "iceMonster.bmp", .Start = 8, .End = 10,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Icing",  .ImageName = "iceMonster.bmp", .Start = 10, .End = 10,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Die1",  .ImageName = "iceMonster.bmp", .Start = 11, .End = 11,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Die2",  .ImageName = "iceMonsterDie.bmp", .Start = 0, .End = 2,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Resurrection",  .ImageName = "iceMonster.bmp", .Start = 12, .End = 14,.InterTime = 0.2f });
	AnimationRender->ChangeAnimation("Move_Left");

}

void IceMonster::Update(float _DeltaTime) {
	if (true == IsUptime) {
		UpTime += _DeltaTime;
	}
	if (1.f < UpTime) {
		IsUptime = false;
		UpTime = 0.f;
	}

	UpdateState(_DeltaTime);

	float4 s = BodyCollision->GetPosition();
	std::vector<GameEngineCollision*> Collision;
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CrazyRenderOrder::BombPower) }, Collision)) {
		for (size_t i = 0; i < Collision.size(); i++) {
			
			NewMonsterDirection = MonsterDirection::Ice;
		}

	}

	if (NewMonsterDirection == MonsterDirection::Ice) {
		std::vector<GameEngineCollision*> Collision;
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CrazyRenderOrder::Player),.TargetColType = CT_Point , .ThisColType = CT_CirCle }, Collision)) {
			for (size_t i = 0; i < Collision.size(); i++) {

				NewMonsterDirection = MonsterDirection::DieIce;
			}

		}
	}
}