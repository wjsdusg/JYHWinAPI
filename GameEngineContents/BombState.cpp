#include "Bomb.h"
#include "Player.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnums.h"




void Bomb::ChangeState(BombState _State)
{
	BombState NextState = _State;
	BombState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case BombState::IDLE:
		IdleStart();
		break;
	case BombState::Pung:
		PungStart();
		break;
	default:
		break;
	}

	switch (PrevState)
	{
	case BombState::IDLE:
		IdleEnd();
		break;
	case BombState::Pung:
		PungEnd();
		break;
	default:
		break;
	}

}

void Bomb::UpdateState(float _Time)
{
	switch (StateValue)
	{
	case BombState::IDLE:
		IdleUpdate(_Time);
		break;
	case BombState::Pung:		
		PungUpdate(_Time);
		break;
	default:
		break;
	}

}

void Bomb::IdleStart() {

}

void Bomb::IdleUpdate(float _DeltaTime) {
	if (true==Check)
	{
		ChangeState(BombState::Pung);
		return;
	}
}

void Bomb::IdleEnd() {

}



void Bomb:: PungStart() {

	{
		AnimationRender = CreateRender(CrazyRenderOrder::Item);
		//AnimationRender->SetPosition(Player::MainPlayer); ºÒ°¡´É
		AnimationRender->SetPosition(float4(200,200));
		AnimationRender->CreateAnimation({ .AnimationName = "Bomb",.ImageName = "Bomb.BMP",.Start = 0,.End = 3,.InterTime = 0.2f });
		AnimationRender->SetScale(float4{ 40.0f,40.0f });
		AnimationRender->ChangeAnimation("Bomb");

	}
    	
}
void Bomb::PungUpdate(float _Time) {
	Bomb::ActTime += _Time;
	if (ActTime >= 2.0f) {
		ChangeState(BombState::IDLE);
	}
};
void Bomb::PungEnd() {

};