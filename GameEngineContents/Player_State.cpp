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
#include "ContentsValue.h"
#include "Bomb.h"
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
		PushStart();
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
		PushEnd();
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
		PushUpdate(_Time);
		break;
	case PlayerState::START:
		StartUpdate(_Time);
		break;
	case PlayerState::TRAP:
		TrapUpdate(_Time);
		break;
	case PlayerState::LIVE:
		LiveUpdate(_Time);
		break;
	case PlayerState::DIE:
		DieUpdate(_Time);
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
	WaitTime += _Time;
		
	Movecalculation(GetPos());
	if (nullptr != Block::OwnerBlock->GetTileMap()->GetTile(static_cast<int>(BlockType::TownBush), GetPos()))
	{
		if (Block::OwnerBlock->GetTileMap()->GetTile(static_cast<int>(BlockType::TownBush), GetPos())->IsUpdate() == true) {
			AnimationRender->ChangeAnimation("BlankMode");
		}
	}
	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove")|| GameEngineInput::IsPress("UpMove")|| GameEngineInput::IsPress("DownMove"))
	{
		ChangeState(PlayerState::MOVE);
		return; // 보통 스테이트를 체인지하면 아래 코드를 실행되면 
	}
	if (WaitTime >= 3.f) {
		AnimationRender->ChangeAnimation("wait");
		NewPlayerDiretion = PlayerDirection::Down;
		
		Movecalculation(GetPos());
	if (nullptr != Block::OwnerBlock->GetTileMap()->GetTile(static_cast<int>(BlockType::TownBush), GetPos()))
	{
		if (Block::OwnerBlock->GetTileMap()->GetTile(static_cast<int>(BlockType::TownBush), GetPos())->IsUpdate() == true)
		{
			AnimationRender->ChangeAnimation("BlankMode");
		}
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
	if (nullptr != Block::OwnerBlock->GetTileMap()->GetTile(static_cast<int>(BlockType::TownBush), GetPos())) 
	{
		if (Block::OwnerBlock->GetTileMap()->GetTile(static_cast<int>(BlockType::TownBush), GetPos())->IsUpdate() == true) {
			AnimationRender->ChangeAnimation("BlankMode");
		}
	}
	
	
}
void Player::MoveEnd() {

}


void Player::StartUpdate(float _Time)
{
	AnimationRender->ChangeAnimation("Start");
	StartTime += _Time;
	if (1.8f < StartTime) {
		ChangeState(PlayerState::IDLE);
	}
}
void Player::LiveUpdate(float _Time)
{
	LiveTime += _Time;
	AnimationRender->ChangeAnimation("Live");
	if (0.5f < LiveTime)
	{
		ChangeState(PlayerState::IDLE);
	}
}
void Player::TrapUpdate(float _Time)
{
	MoveSpeed = 10.f;
	AnimationRender->ChangeAnimation("Trap");
	TrapTime += _Time;
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		NewPlayerDiretion = PlayerDirection::Left;

		if (true == Movecalculation(GetPos() + (float4::Left * MoveSpeed * _Time)))
		{
			SetMove(float4::Left * MoveSpeed * _Time);
		}
	}
	else if (true == GameEngineInput::IsPress("RightMove"))
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
	if (nullptr != Block::OwnerBlock->GetTileMap()->GetTile(static_cast<int>(BlockType::TownBush), GetPos()))
	{
		if (Block::OwnerBlock->GetTileMap()->GetTile(static_cast<int>(BlockType::TownBush), GetPos())->IsUpdate() == true) {
			AnimationRender->ChangeAnimation("BlankMode");
		}
	}

	if (3.6f < TrapTime) {
		StateValue = PlayerState::DIE;
	}
}
void Player::DieUpdate(float _Time)
{
	DieTime += _Time;
	AnimationRender->ChangeAnimation("die");
	if (1.f < DieTime) {
		StateValue = PlayerState::IDLE;
	}
}

void Player::PushStart() {
	
	WoodTargetPos = WoodStartPos + (WoodDir * ContentsValue::TileSize);
	
	if (true == Block::OwnerBlock->IsMapOut(WoodTargetPos))
	{
		ChangeState(PlayerState::MOVE);
	}
	if (true == Bomb::IsBomb(WoodTargetPos))
	{
		ChangeState(PlayerState::MOVE);
	}
	if (true == Block::OwnerBlock->IsBlock(WoodTargetPos))
	{
		if (true == Block::OwnerBlock->NewGameEngineTileMap->GetTile(static_cast<int>(BlockType::TownBush), WoodTargetPos)->IsUpdate())
		{
			return;
		}
		
		ChangeState(PlayerState::MOVE);
	}
	Block::OwnerBlock->NewGameEngineTileMap->TileIndexChange(static_cast<int>(BlockType::Block1), WoodStartPos, WoodTargetPos);
	WoodStartPos = Block::OwnerBlock->GetTileMap()->ConvertIndexToTilePosition(WoodStartPos);
	WoodTargetPos = Block::OwnerBlock->GetTileMap()->ConvertIndexToTilePosition(WoodTargetPos);
}

void Player::PushUpdate(float _Time)
{
	WoodMoveTime += _Time;
	float4 Pos = float4::LerpClamp(WoodStartPos, WoodTargetPos, WoodMoveTime);
	if (WoodDir == float4::Up || WoodDir == float4::Down) {
		Pos -= Block::OwnerBlock->NewGameEngineTileMap->GetPos();
	}
	if (WoodDir == float4::Left || WoodDir == float4::Right) {
		Pos.y -= Block::OwnerBlock->NewGameEngineTileMap->GetPos().y;
		Pos.x -= Block::OwnerBlock->NewGameEngineTileMap->GetPos().x;
	}
	WoodRender->SetPosition(Pos);
	if (1.f <= WoodMoveTime)
	{
		ChangeState(PlayerState::MOVE);
	}
}

void Player::PushEnd() {
	WoodStartPos = { 0,0 };
	WoodDir = { 0,0 };
	WoodTargetPos = { 0,0 };
	WoodMoveTime = 0.f;
	WoodRender = nullptr;
}