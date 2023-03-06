#include "Monster.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Block.h"
#include "Player.h"
#include "Bomb.h"
Monster::Monster() 
{
	
}

Monster::~Monster() 
{
}

void Monster::Start() {
	
}

void Monster::Update(float _DeltaTime) {
	
	

}


bool Monster::Movecalculation(float4 _Pos)
{

	float4 MoveDir;

	switch (NewMonsterDirection)
	{
	case MonsterDirection::Left:
		CollisionDiretion = _Pos;
		CollisionDiretion.x -= 20.f;

		break;
	case MonsterDirection::Right:
		CollisionDiretion = _Pos;
		CollisionDiretion.x += 20.f;
		break;
	case MonsterDirection::Up:
		CollisionDiretion = _Pos;
		CollisionDiretion.y -= 20.f;
		break;
	case MonsterDirection::Down:
		CollisionDiretion = _Pos;
		CollisionDiretion.y += 20.f;
		break;
	default:
		break;
	}

	float4 DistanceToPlayer;

	DistanceToPlayer = Player::MainPlayer->GetPos() - GetPos();
	float Distance = DistanceToPlayer.Size();

	if (80.f > Distance) {
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
		if (GetPos().x > Player::MainPlayer->GetPos().x)
		{
			NewMonsterDirection= MonsterDirection::Left;
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
	
	if ( true== Bomb::IsBomb(CollisionDiretion)) {
		NewMonsterDirection = MonsterDirection::Up;
		IsUptime = true;
		return false;
	}
	if (true == IsUptime) {
		NewMonsterDirection = MonsterDirection::Up;
	}

	

		return true;
	}
