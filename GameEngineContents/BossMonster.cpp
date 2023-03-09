#include "BossMonster.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineResources.h>
#include "Player.h"
BossMonster::BossMonster()
{
}

BossMonster::~BossMonster()
{
}



void BossMonster::Start() {
	NewMonsterDirection = static_cast<MonsterDirection>(GameEngineRandom::MainRandom.RandomInt(static_cast<int>(MonsterDirection::Left), static_cast<int>(MonsterDirection::Right)));

	BodyCollision = CreateCollision(CrazyRenderOrder::Monster);
	BodyCollision->SetScale(float4(60, 60));

	SetPos(Block::OwnerBlock->GetTileMap()->ConvertIndexToTilePosition(float4{140,120}));

	
	AnimationRender = CreateRender(CrazyRenderOrder::Monster);
	AnimationRender->SetScale({ 160, 120 });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_Up",  .ImageName = "boss2.bmp", .Start = 1, .End = 2,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_Down",  .ImageName = "boss2.bmp", .Start = 1, .End = 2,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_Left",  .ImageName = "bossLeftRight.bmp", .Start = 2, .End = 3,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Move_Right",  .ImageName = "bossLeftRight.bmp", .Start = 0, .End = 1,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "Hit",  .ImageName = "boss2.bmp", .Start = 3, .End = 3, });
	AnimationRender->CreateAnimation({ .AnimationName = "Angry",  .ImageName = "boss2.bmp", .Start = 0, .End = 0,});
	AnimationRender->CreateAnimation({ .AnimationName = "Die",  .ImageName = "boss3.bmp", .Start = 6, .End = 7,.InterTime = 0.3f });
	AnimationRender->CreateAnimation({ .AnimationName = "Dieing",  .ImageName = "boss3.bmp", .Start = 5, .End = 5,});
	AnimationRender->CreateAnimation({ .AnimationName = "Die2",  .ImageName = "boss3.bmp", .Start = 4, .End = 5,.InterTime = 0.3f });
	AnimationRender->CreateAnimation({ .AnimationName = "Skill",  .ImageName = "boss3.bmp", .Start = 0, .End = 3,.InterTime = 0.2f });
	AnimationRender->ChangeAnimation("Move_Left");

}

void BossMonster::Update(float _DeltaTime) {
	

	UpdateState(_DeltaTime);

	//if(NewMonsterDirection ==MonsterDirection::Hit)
	std::vector<GameEngineCollision*> Collision;
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CrazyRenderOrder::BombPower) }, Collision)) {
		for (size_t i = 0; i < Collision.size(); i++) {
			
			NewMonsterState = MonsterState::FIGHT;

			if (0 >= HP)
			{
				NewMonsterDirection = MonsterDirection::Bubble;
			}
									
			if (0 < HP)
			{
				NewMonsterDirection = MonsterDirection::Hit;
			}
		}

	}

	if (NewMonsterDirection == MonsterDirection::Dieing) {
		std::vector<GameEngineCollision*> Collision;
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CrazyRenderOrder::Player),.TargetColType = CT_Point , .ThisColType = CT_CirCle }, Collision)) {
			for (size_t i = 0; i < Collision.size(); i++) {
				DieTime = 0.f;
				NewMonsterDirection = MonsterDirection::Die;
				Player::MainPlayer->BossDie = true;
				GameEngineResources::GetInst().SoundPlay("Pung.wav");
				GameEngineResources::GetInst().SoundPlay("Win_Effect.wav");
			}

		}
	}
}

bool BossMonster::Movecalculation(float4 _Pos)
{

	float4 MoveDir;

	switch (NewMonsterDirection)
	{
	case MonsterDirection::Left:
		CollisionDiretion = _Pos;
		CollisionDiretion.x -= 100.f;

		break;
	case MonsterDirection::Right:
		CollisionDiretion = _Pos;
		CollisionDiretion.x += 100.f;
		break;
	case MonsterDirection::Up:
		CollisionDiretion = _Pos;
		CollisionDiretion.y -= 100.f;
		break;
	case MonsterDirection::Down:
		CollisionDiretion = _Pos;
		CollisionDiretion.y += 100.f;
		break;
	default:
		break;
	}



	float4 DistanceToPlayer;

	DistanceToPlayer = Player::MainPlayer->GetPos() - GetPos();
	float Distance = DistanceToPlayer.Size();

	if (160.f > Distance) {
		ChangeState(MonsterState::FIGHT);
	}

	if (MonsterState::IDLE == NewMonsterState) {

		if (true == Block::OwnerBlock->IsMapOut(CollisionDiretion)) {
			switch (NewMonsterDirection)
			{
			case MonsterDirection::Left:
				NewMonsterDirection = MonsterDirection::Right;
				break;
			case MonsterDirection::Right:
				NewMonsterDirection = MonsterDirection::Left;
				break;
			case MonsterDirection::Up:
				NewMonsterDirection = MonsterDirection::Down;
				break;
			case MonsterDirection::Down:
				NewMonsterDirection = MonsterDirection::Up;
				break;
			default:
				break;
			}
			return false;
		}

	}

	if (nullptr == Player::MainPlayer) {
		ChangeState(MonsterState::IDLE);
	}
	
	if (MonsterState::FIGHT == NewMonsterState) {
		if (MonsterDirection::Skill != NewMonsterDirection)
		{
			if (GetPos().x > Player::MainPlayer->GetPos().x)
			{
				NewMonsterDirection = MonsterDirection::Left;
			}
			else if (GetPos().x <= Player::MainPlayer->GetPos().x)
			{
				NewMonsterDirection = MonsterDirection::Right;
			}

			if (20.f >= abs(GetPos().x - Player::MainPlayer->GetPos().x)) {

				if (GetPos().y <= Player::MainPlayer->GetPos().y) {
					NewMonsterDirection = MonsterDirection::Down;
				}
				else if (GetPos().y > Player::MainPlayer->GetPos().y) {
					NewMonsterDirection = MonsterDirection::Up;
				}
			}
		}
		

	}
	
	return true;
}
