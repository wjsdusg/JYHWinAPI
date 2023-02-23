#include "Bomb.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "BombPower.h"
#include <GameEngineCore/GameEngineCollision.h>
Bomb::Bomb()
{


}

Bomb::~Bomb()
{
}



void Bomb::Start() {

	BodyCollision = CreateCollision(CrazyRenderOrder::Bomb);
	BodyCollision->SetScale(float4(40, 40));

	BlockCollision = CreateCollision(CrazyRenderOrder::BombtoPlayer);

	AnimationRender = CreateRender(CrazyRenderOrder::Item);
	AnimationRender->SetPosition(GetPos());
	AnimationRender->CreateAnimation({ .AnimationName = "Bomb",.ImageName = "Bomb.BMP",.Start = 0,.End = 3,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "BombEnd",.ImageName = "unit_bombwaterAll.BMP",.Start = 4,.End = 7,.InterTime = 0.17f });
	AnimationRender->SetScale(float4{ 40.0f,40.0f });
	AnimationRender->ChangeAnimation("Bomb");
}

void Bomb::Update(float _DeltaTime)
{

	Playerbombcount = Player::MainPlayer->BombCountptr;



	//if (Player::MainPlayer->BodyCollision->GetPosition() - this->GetPos() > float4{ 20.f })
	if (GetLiveTime() >= 4.5 || true == BombDeath)
	{

		AnimationRender->ChangeAnimation("BombEnd");


		BombPower* NewBombPower = GetLevel()->CreateActor<BombPower>();

		NewBombPower->SetPos(GetPos());

		/*PlusPos *=num;
		NewBombPower->PlusPos = PlusPos;*/
		if (BombAnimationCheck == true) {
			NewBombPower->BombAnimation();
		}


		BombAnimationCheck = false;
		//PlusPos *= num;

		num++;

		if (true == BombDeath) {
			*Playerbombcount += 1;
			Death();
		}



	}

	if (GetLiveTime() >= 5.0)
	{

		*Playerbombcount += 1;
		Death();

	}

}

