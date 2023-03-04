#include "Monster.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include "Block.h"
#include "Player.h"
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
		
		break;
	case MonsterDirection::Right:
		
		break;
	case MonsterDirection::Up:
		
		break;
	case MonsterDirection::Down:
		
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

		if (true == Block::OwnerBlock->IsMapOut(_Pos)) {
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

		return true;
	}
