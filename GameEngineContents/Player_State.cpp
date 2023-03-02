#include "Player.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineTileMap.h>
#include "ContentsEnums.h"
#include "Block.h"

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
	case PlayerState::PUSH:
		//PushStart();
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
	case PlayerState::PUSH:
		//PushEnd();
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
	case PlayerState::PUSH:
		//PushUpdate(_Time);
		break;
	default:
		break;
	}

}

// FSM ���� ����� �Ҷ� �̵��ϸ鼭 ������ ������ ����.
void Player::IdleStart() 
{
	DirCheck("Idle");
}
void Player::IdleUpdate(float _Time) 
{
	WaitTime += _Time;
	GetLiveTime();
	
	Movecalculation(GetPos());
	if (Block::OwnerBlock->GetTileMap()->GetTile(static_cast<int>(BlockType::TownBush), GetPos())->IsUpdate() == true) {
		AnimationRender->ChangeAnimation("BlankMode");
	}
	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove")|| GameEngineInput::IsPress("UpMove")|| GameEngineInput::IsPress("DownMove"))
	{
		ChangeState(PlayerState::MOVE);
		return; // ���� ������Ʈ�� ü�����ϸ� �Ʒ� �ڵ带 ����Ǹ� 
	}
	if (WaitTime >= 3.f) {
		AnimationRender->ChangeAnimation("wait");
		NewPlayerDiretion = PlayerDirection::Down;
		
		Movecalculation(GetPos());
		if (Block::OwnerBlock->GetTileMap()->GetTile(static_cast<int>(BlockType::TownBush), GetPos())->IsUpdate() == true) {
			AnimationRender->ChangeAnimation("BlankMode");
		}
	}
}
void Player::IdleEnd() {
	WaitTime = 0.f;
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
		NewPlayerDiretion = PlayerDirection::Left;

		if (true == Movecalculation(GetPos()+(float4::Left * MoveSpeed * _Time))) 
		{

			SetMove(float4::Left * MoveSpeed * _Time);
		}
		
		
	} else if (true == GameEngineInput::IsPress("RightMove"))
	{
		NewPlayerDiretion = PlayerDirection::Right;
		if (true == Movecalculation(GetPos() + (float4::Right * MoveSpeed * _Time))) {
			SetMove(float4::Right * MoveSpeed * _Time);
		}
		
	}
	else if (true == GameEngineInput::IsPress("UpMove")) {
		NewPlayerDiretion = PlayerDirection::Up;
		if (true == Movecalculation(GetPos() + (float4::Up * MoveSpeed * _Time))) {
			SetMove(float4::Up * MoveSpeed * _Time);
		}
		
	}

	else if (true == GameEngineInput::IsPress("DownMove")) {
		NewPlayerDiretion = PlayerDirection::Down;
		if (true == Movecalculation(GetPos() + (float4::Down * MoveSpeed * _Time))) {
			SetMove(float4::Down * MoveSpeed * _Time);
		}
		
	}


	DirCheck("Move");
	if (Block::OwnerBlock->GetTileMap()->GetTile(static_cast<int>(BlockType::TownBush), GetPos())->IsUpdate() == true) {
		AnimationRender->ChangeAnimation("BlankMode");
	}
	if (true == WoodBlockCheck) {

	}
}
void Player::MoveEnd() {

}
