#include "Monster.h"
// State
void Monster::ChangeState(MonsterState _State)
{
	MonsterState NextState = _State;
	MonsterState PrevState = NewMonsterState;

	NewMonsterState = NextState;

	switch (NextState)
	{
	case MonsterState::IDLE:
		IdleStart();
		break;
	case MonsterState::FIGHT:
		FightStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case MonsterState::IDLE:
		IdleEnd();
		break;
	case MonsterState::FIGHT:
		FightEnd();
		break;
	
	default:
		break;
	}

}

void Monster::UpdateState(float _Time)
{
	switch (NewMonsterState)
	{
	case MonsterState::IDLE:
		IdleUpdate(_Time);
		break;
	case MonsterState::FIGHT:
		FightUpdate(_Time);
		break;
	
	default:
		break;
	}

}

// FSM ���� ����� �Ҷ� �̵��ϸ鼭 ������ ������ ����.
void Monster::IdleStart()
{
	
}
void Monster::IdleUpdate(float _Time)
{
	switch (NewMonsterDirection)
	{
	case MonsterDirection::Left:
		
		if (true == Movecalculation(GetPos() + (float4::Left * MoveSpeed * _Time)))
		{
			SetMove(float4::Left * MoveSpeed * _Time);
		}
		AnimationRender->ChangeAnimation("Move_Left");
		break;
	case MonsterDirection::Right:
		if (true == Movecalculation(GetPos() + (float4::Right * MoveSpeed * _Time)))
		{
			SetMove(float4::Right * MoveSpeed * _Time);
		}
		AnimationRender->ChangeAnimation("Move_Right");
		break;
	case MonsterDirection::Up:
	
		break;
	case MonsterDirection::Down:
		
		break;
	default:
		break;
	}
}
void Monster::IdleEnd() {

}

void Monster::FightStart()
{
	//DirCheck("Move");
}
void Monster::FightUpdate(float _Time)
{
	switch (NewMonsterDirection)
	{
	case MonsterDirection::Left:

		if (true == Movecalculation(GetPos() + (float4::Left * MoveSpeed * _Time)))
		{
			SetMove(float4::Left * MoveSpeed * _Time);
		}
		AnimationRender->ChangeAnimation("Move_Left");
		break;
	case MonsterDirection::Right:
		if (true == Movecalculation(GetPos() + (float4::Right * MoveSpeed * _Time)))
		{
			SetMove(float4::Right * MoveSpeed * _Time);
		}
		AnimationRender->ChangeAnimation("Move_Right");
		break;
	case MonsterDirection::Up:

		break;
	case MonsterDirection::Down:

		break;
	default:
		break;
	}
	
}
void Monster::FightEnd() {

}
