#include "MaxPower.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnums.h"
#include "Player.h"

MaxPower::MaxPower()
{


}

MaxPower::~MaxPower()
{
}



void MaxPower::Start() {


	AnimationRender = CreateRender(CrazyRenderOrder::DropItem);
	//AnimationRender->SetPosition(float4(200, 200));
	AnimationRender->CreateAnimation({ .AnimationName = "MaxPower",.ImageName = "power_max.BMP",.Start = 0,.End = 1,.InterTime = 0.8f });
	AnimationRender->SetScale(float4{ 40.0f,40.0f });
	AnimationRender->ChangeAnimation("MaxPower");

	{
		BodyCollision = CreateCollision(CrazyRenderOrder::DropItem);
		BodyCollision->SetScale(float4(40, 40));

	}

}

