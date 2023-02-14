#include "BombPower.h"
#include "ContentsEnums.h"

#include <vector>
BombPower::BombPower()
{


}

BombPower::~BombPower()
{
}



void BombPower::Start() {


	std::vector<float> _FrameTime;
	_FrameTime.push_back(0.3f);
	_FrameTime.push_back(0.1f);
	_FrameTime.push_back(0.1f);
	_FrameTime.push_back(0.1f);

	AnimationRender[0] = CreateRender(CrazyRenderOrder::Item);
	AnimationRender[0]->CreateAnimation({.AnimationName = "BombUpEnd",.ImageName = "unit_bombwaterAll.BMP",.Start = 8,.End = 11,.FrameTime = _FrameTime});
	AnimationRender[0]->CreateAnimation({.AnimationName = "BombUping",.ImageName = "unit_bombwaterAll.BMP",.Start = 24,.End = 27,.InterTime = 0.1f });
	AnimationRender[0]->SetScale(float4{45.0f,45.0f});
	AnimationRender[0]->ChangeAnimation("BombUpEnd");
	float4 MovePosition0 = float4::Up * 40;
	MovePosition0 += GetPos();
	AnimationRender[0]->SetPosition(MovePosition0);

	AnimationRender[1] = CreateRender(CrazyRenderOrder::Item);
	AnimationRender[1]->CreateAnimation({ .AnimationName = "BombDownEnd",.ImageName = "unit_bombwaterAll.BMP",.Start = 8,.End = 11,.FrameTime = _FrameTime });
	AnimationRender[1]->CreateAnimation({ .AnimationName = "BombDowning",.ImageName = "unit_bombwaterAll.BMP",.Start = 24,.End = 27,.InterTime = 0.1f });
	AnimationRender[1]->SetScale(float4{ 45.0f,45.0f });
	AnimationRender[1]->ChangeAnimation("BombDownEnd");
	float4 MovePosition1 = float4::Down * 40;
	MovePosition1 += GetPos();
	AnimationRender[1]->SetPosition(MovePosition1);


}

void BombPower::Update(float _DelataTime) {
	
	
	if (GetLiveTime() >= 0.5f) {
		Death();
	}
		
	
}
