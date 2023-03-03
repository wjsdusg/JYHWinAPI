#include "Monster.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include "Block.h"

Monster::Monster() 
{
}

Monster::~Monster() 
{
}

void Monster::Start() {
	
}

void Monster::Update(float _DeltaTime) {
	
	UpdateState(_DeltaTime);
		
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



	if (true == Block::OwnerBlock->IsMapOut(_Pos)) {
		return false;
	}


		return false;
	}
