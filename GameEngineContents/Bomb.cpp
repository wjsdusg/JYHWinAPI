#include "Bomb.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

#include "Player.h"

Bomb::Bomb()
{
	
	
}

Bomb::~Bomb()
{
}

bool Bomb::BombCheck[10] = { false };
 int Bomb::BombCount = 6;

void Bomb::Start() {
	for (int i = 0; i < BombCount; i++) {
		
		if (BombCheck[i] == false)
		{
			BombCheck[i] = true;
			AnimationRender = CreateRender(CrazyRenderOrder::Item);
			AnimationRender->SetPosition(GetPos());
			AnimationRender->CreateAnimation({ .AnimationName = "Bomb",.ImageName = "Bomb.BMP",.Start = 0,.End = 3,.InterTime = 0.2f });
			AnimationRender->SetScale(float4{ 40.0f,40.0f });
			AnimationRender->ChangeAnimation("Bomb");
			break;
		}
		
	}
	}

void Bomb::Update(float _DeltaTime)
{
	ActTime += _DeltaTime;
	if (ActTime >= 10.0) {
		Live = false;
	}
	//Bomb::UpdateState(_DeltaTime);
	
	//AnimationRender->SetPosition(Player::MainPlayer); ºÒ°¡´É
	if (Live == false) {
		Death();
		for (int i = 0; i < BombCount; i++) {
			if (BombCheck[i] == true) {
				BombCheck[i] = false;
				break;
			}
		}
	}
}


bool Bomb::IsLive() {
	return Live;
}