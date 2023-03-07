#include "KickItem.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnums.h"
#include "Player.h"

KickItem::KickItem()
{


}

KickItem::~KickItem()
{
}



void KickItem::Start() {


	AnimationRender = CreateRender(CrazyRenderOrder::DropItem);
	//AnimationRender->SetPosition(float4(200, 200));
	AnimationRender->CreateAnimation({ .AnimationName = "KickItem",.ImageName = "KickItem.BMP",.Start = 0,.End = 1,.InterTime = 0.8f });
	AnimationRender->SetScale(float4{ 40.0f,40.0f });
	AnimationRender->ChangeAnimation("KickItem");

	{
		BodyCollision = CreateCollision(CrazyRenderOrder::DropItem);
		BodyCollision->SetScale(float4(40, 40));

	}

}

