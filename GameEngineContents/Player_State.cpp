#include "Player.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnums.h"


// State
void Player::ChangeState(PlayerState _State) 
{
	PlayerState NextState = _State;
	PlayerState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case PlayerState::IDLE:
		IdleStart();
		break;
	case PlayerState::MOVE:
		MoveStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case PlayerState::IDLE:
		IdleEnd();
		break;
	case PlayerState::MOVE:
		MoveEnd();
		break;
	default:
		break;
	}

}

void Player::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case PlayerState::IDLE:
		IdleUpdate(_Time);
		break;
	case PlayerState::MOVE:
		MoveUpdate(_Time);
		break;
	default:
		break;
	}

}

// FSM 내가 어떤일을 할때 이동하면서 가만히 있을수 없다.
void Player::IdleStart() 
{
	DirCheck("Idle");
}
void Player::IdleUpdate(float _Time) 
{
	Movecalculation(GetPos());
	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove")|| GameEngineInput::IsPress("UpMove")|| GameEngineInput::IsPress("DownMove"))
	{
		ChangeState(PlayerState::MOVE);
		return; // 보통 스테이트를 체인지하면 아래 코드를 실행되면 
	}
}
void Player::IdleEnd() {

}

void Player::MoveStart() 
{
	DirCheck("Move");
}
void Player::MoveUpdate(float _Time) 
{
	if (
		false == GameEngineInput::IsPress("LeftMove") && 
		false == GameEngineInput::IsPress("RightMove")&&
		false == GameEngineInput::IsPress("UpMove")&&
		false == GameEngineInput::IsPress("DownMove")
		)
	{
		// 
		ChangeState(PlayerState::IDLE);
		return;
	}

	// float4 MoveDir = float4::Zero;

	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		
		if (true == Movecalculation(GetPos()+(float4::Left * MoveSpeed * _Time))) {
			SetMove(float4::Left * MoveSpeed * _Time);
		}
		
	} else if (true == GameEngineInput::IsPress("RightMove"))
	{
		if (true == Movecalculation(GetPos() + (float4::Right * MoveSpeed * _Time))) {
			SetMove(float4::Right * MoveSpeed * _Time);
		}
		
	}
	else if (true == GameEngineInput::IsPress("UpMove")) {
		if (true == Movecalculation(GetPos() + (float4::Up * MoveSpeed * _Time))) {
			SetMove(float4::Up * MoveSpeed * _Time);
		}
		
	}
	else if (true == GameEngineInput::IsPress("DownMove")) {
		if (true == Movecalculation(GetPos() + (float4::Down * MoveSpeed * _Time))) {
			SetMove(float4::Down * MoveSpeed * _Time);
		}
		
	}


	DirCheck("Move");
}
void Player::MoveEnd() {

}
