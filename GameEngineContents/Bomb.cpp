#include "Bomb.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineMath.h>
#include "Player.h"

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
			AnimationRender->SetScale(float4{ 40.0f,40.0f });
			AnimationRender->ChangeAnimation("Bomb");
			  
}

void Bomb::Update(float _DeltaTime)
{
	
	Playerbombcount = Player::MainPlayer->BombCountptr;
	
	if (GetLiveTime() >= 5.0) 
	{
		*Playerbombcount+=1;
		Death();
		
	}
	
}

