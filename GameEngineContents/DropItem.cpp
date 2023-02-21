#include "DropItem.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "BombItem.h"
#include "SpeedItem.h"
#include "MaxPower.h"
DropItem::DropItem()
{


}

DropItem::~DropItem()
{
}

ItemType DropItem::GetItemType() {
	BombItem* NewBobmItem = dynamic_cast<BombItem*>(this);
	if (nullptr != NewBobmItem) {
		return ItemType::Bomb;
	}
	SpeedItem* NewSkateItem = dynamic_cast<SpeedItem*>(this);
	if (nullptr != NewSkateItem) {
		return ItemType::Skate;
	}
	MaxPower* NewMaxPower = dynamic_cast<MaxPower*>(this);
	if (nullptr != NewMaxPower) {
		return ItemType::PowerMax;
	}
	return ItemType::Max;

}

void DropItem::Start() {


	//AnimationRender = CreateRender(CrazyRenderOrder::DropItem);
	////AnimationRender->SetPosition(float4(200, 200));
	//AnimationRender->CreateAnimation({ .AnimationName = "ballon",.ImageName = "ballon.BMP",.Start = 0,.End = 1,.InterTime = 0.8f });
	//AnimationRender->SetScale(float4{ 40.0f,40.0f });
	//AnimationRender->ChangeAnimation("ballon");

	//{
	//	BodyCollision = CreateCollision(CrazyRenderOrder::DropItem);
	//	BodyCollision->SetScale(float4(200,200));
	//	
	//}
	

}

void DropItem::Update(float _DelataTime) {




}
