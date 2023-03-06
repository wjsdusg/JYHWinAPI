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

// FSM 내가 어떤일을 할때 이동하면서 가만히 있을수 없다.
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
		NewMonsterDirection = MonsterDirection::Left;
		break;
	case MonsterDirection::Down:
		NewMonsterDirection = MonsterDirection::Left;
		break;
	case MonsterDirection::Die:
		AnimationRender->ChangeAnimation("Die");
		DieTime += _Time;
		if (DieTime > 0.6) {
			Death();
		}
		break;
	case MonsterDirection::Ice:
		DieTime += _Time;

		AnimationRender->ChangeAnimation("Ice");
		if (DieTime > 0.6f) {
			AnimationRender->ChangeAnimation("Icing");
		}
		if (DieTime > 10.f) {
			NewMonsterDirection = MonsterDirection::Resurrection;
			DieTime = 0;
		}
		break;

	case MonsterDirection::Resurrection:
		AnimationRender->ChangeAnimation("Resurrection");
		DieTime += _Time;
		if (DieTime > 0.6f) {
			NewMonsterDirection = MonsterDirection::Left;
			ChangeState(MonsterState::IDLE);
			DieTime = 0;
		}

		break;
	case MonsterDirection::DieIce:
		IceDieTime += _Time;
		if (IceDieTime < 0.2f) {
			AnimationRender->ChangeAnimation("Die1");
		}
		if (IceDieTime >= 0.2f) {
			AnimationRender->SetScale(float4{ 50,50 });
			AnimationRender->ChangeAnimation("Die2");
		}

		if (IceDieTime > 0.8f) {
			Death();
		}
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
		if (true == Movecalculation(GetPos() + (float4::Up * MoveSpeed * _Time)))
		{
			SetMove(float4::Up * MoveSpeed * _Time);
		}
		AnimationRender->ChangeAnimation("Move_Up");
		break;
	case MonsterDirection::Down:
		if (true == Movecalculation(GetPos() + (float4::Down * MoveSpeed * _Time)))
		{
			SetMove(float4::Down * MoveSpeed * _Time);
		}
		AnimationRender->ChangeAnimation("Move_Down");
		break;
	case MonsterDirection::Die:
		AnimationRender->ChangeAnimation("Die");
		DieTime += _Time;
		if (DieTime > 0.6) {
			Death();
		}
		break;
	case MonsterDirection::Ice:
		DieTime += _Time;

		AnimationRender->ChangeAnimation("Ice");
		if (DieTime > 0.6f) {
			AnimationRender->ChangeAnimation("Icing");
		}
		if (DieTime > 10.f) {
			NewMonsterDirection = MonsterDirection::Resurrection;
			DieTime = 0;
		}
		break;

	case MonsterDirection::Resurrection:
		AnimationRender->ChangeAnimation("Resurrection");
		DieTime += _Time;
		if (DieTime > 0.6f) {
			NewMonsterDirection = MonsterDirection::Left;
			ChangeState(MonsterState::IDLE);
			DieTime = 0;
		}

		break;
	case MonsterDirection::DieIce:
		IceDieTime += _Time;
		if (IceDieTime < 0.2f) {
			AnimationRender->ChangeAnimation("Die1");
		}
		if (IceDieTime >= 0.2f) {
			AnimationRender->SetScale(float4{ 50,50 });
			AnimationRender->ChangeAnimation("Die2");
		}

		if (IceDieTime > 0.8f) {
			Death();
		}
		break;
	default:
		break;
	}



}

void Monster::FightEnd() {
}