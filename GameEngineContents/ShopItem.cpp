#include "ShopItem.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnums.h"
#include "Player.h"

ShopItem::ShopItem()
{


}

ShopItem::~ShopItem()
{
}



void ShopItem::Start() {


	AnimationRender = CreateRender(CrazyRenderOrder::DropItem);
	//AnimationRender->SetPosition(float4(200, 200));
	AnimationRender->CreateAnimation({ .AnimationName = "Shop",.ImageName = "Shop.BMP",.Start = 0,.End = 1,.InterTime = 0.8f });
	AnimationRender->SetScale(float4{ 40.0f,40.0f });
	AnimationRender->ChangeAnimation("Shop");

	{
		BodyCollision = CreateCollision(CrazyRenderOrder::DropItem);
		BodyCollision->SetScale(float4(40, 40));

	}

}

