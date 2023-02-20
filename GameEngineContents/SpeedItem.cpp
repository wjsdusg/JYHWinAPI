#include "SpeedItem.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnums.h"
#include "Player.h"

SpeedItem::SpeedItem()
{


}

SpeedItem::~SpeedItem()
{
}



void SpeedItem::Start() {


	AnimationRender = CreateRender(CrazyRenderOrder::DropItem);
	//AnimationRender->SetPosition(float4(200, 200));
	AnimationRender->CreateAnimation({ .AnimationName = "skate",.ImageName = "skate.BMP",.Start = 0,.End = 1,.InterTime = 0.8f });
	AnimationRender->SetScale(float4{ 40.0f,40.0f });
	AnimationRender->ChangeAnimation("skate");

	{
		BodyCollision = CreateCollision(CrazyRenderOrder::DropItem);
		BodyCollision->SetScale(float4(100, 100));

	}

}

