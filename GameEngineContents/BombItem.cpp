#include "BombItem.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnums.h"
#include "Player.h"

BombItem::BombItem()
{


}

BombItem::~BombItem()
{
}



void BombItem::Start() {


	AnimationRender = CreateRender(CrazyRenderOrder::DropItem);
	//AnimationRender->SetPosition(float4(200, 200));
	AnimationRender->CreateAnimation({ .AnimationName = "ballon",.ImageName = "ballon.BMP",.Start = 0,.End = 1,.InterTime = 0.8f });
	AnimationRender->SetScale(float4{ 40.0f,40.0f });
	AnimationRender->ChangeAnimation("ballon");

	{
		BodyCollision = CreateCollision(CrazyRenderOrder::DropItem);
		BodyCollision->SetScale(float4(200, 200));

	}

}

