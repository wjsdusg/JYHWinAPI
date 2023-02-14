#include "Bomb.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "BombPower.h"
Bomb::Bomb()
{
	
	
}

Bomb::~Bomb()
{
}



void Bomb::Start() {
	
		
		
			AnimationRender = CreateRender(CrazyRenderOrder::Item);
			AnimationRender->SetPosition(GetPos());
			AnimationRender->CreateAnimation({ .AnimationName = "Bomb",.ImageName = "Bomb.BMP",.Start = 0,.End = 3,.InterTime = 0.2f });
			AnimationRender->CreateAnimation({ .AnimationName = "BombEnd",.ImageName = "unit_bombwaterAll.BMP",.Start = 4,.End = 7,.InterTime = 0.13333f });
			AnimationRender->SetScale(float4{ 40.0f,40.0f });
			AnimationRender->ChangeAnimation("Bomb");

			
}

void Bomb::Update(float _DeltaTime)
{
	
	Playerbombcount = Player::MainPlayer->BombCountptr;
	
	if (GetLiveTime() >= 4.5)
	{
		

	}
	if (GetLiveTime() >= 4.6)
	{
		AnimationRender->ChangeAnimation("BombEnd");
		if (BombPowerCount > 0) {
			BombPower* NewBombPower = GetLevel()->CreateActor<BombPower>();

			//NewBombPower->SetOwner(this);

			NewBombPower->SetPos(GetPos());
			NewBombPower->BombPowerCountPtr = BombPowerCountPtr;
			BombPowerCount--;
		}
		
	}
	
	if (GetLiveTime() >= 5.0) 
	{
		
		*Playerbombcount+=1;
		Death();
		
	}
	
}

