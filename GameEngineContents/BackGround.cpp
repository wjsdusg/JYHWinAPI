#include "BackGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

BackGround::BackGround() 
{
}

BackGround::~BackGround() 
{
}
BackGround* BackGround::MainBackGround = nullptr;
void BackGround::Start() 
{
	

	NewNumberObject.SetOwner(this);
	NewNumberObject.SetImage("Number.BMp", { 10, 12 }, 10, RGB(255, 255, 255), "Number.BMp");
	
	NewNumberObject.SetAlign(Align::Right);
	NewNumberObject.SetMove({ 758,48 });
	NewNumberObject.SetRenderPos({ 758,48 });
	NewNumberObject.SetValue(Value);

	NewNumberObject2.SetOwner(this);
	NewNumberObject2.SetImage("Number.BMp", { 10, 12 }, 10, RGB(255, 255, 255), "Number.BMp");

	NewNumberObject2.SetAlign(Align::Right);
	NewNumberObject2.SetMove({ 728,48 });
	NewNumberObject2.SetRenderPos({ 728,48 });
	NewNumberObject2.SetValue(Value2);

	MainBackGround = this;
	{
		GameEngineRender* AnimationRender = CreateRender(CrazyRenderOrder::BackGround);
		AnimationRender->SetPosition(GameEngineWindow::GetScreenSize().half());
		AnimationRender->SetScale(GameEngineWindow::GetScreenSize());
		AnimationRender->SetImage("PlayUI.BMP");
	}
	ActiveItemRender = CreateRender(CrazyRenderOrder::Player);
	ActiveItemRender->SetImage("Shop2.bmp");
	ActiveItemRender->SetPosition(float4{ 710,480 });
	ActiveItemRender->SetScale(float4{ 60,60 });
	ActiveOnOffSwicth();

	StartRender = CreateRender(CrazyRenderOrder::Player);
	StartRender->SetImage("GAMEStart.bmp");
	float4 Pos = GameEngineWindow::GetScreenSize().half();
	Pos.y -= 100;
	Pos.x -= 100;
	StartRender->SetPosition(Pos);
	StartRender->SetScale(float4{ 500,80 });

	WinRender=CreateRender(CrazyRenderOrder::Player);
	WinRender->SetImage("Win.bmp");
	WinRender->SetPosition(Pos);
	WinRender->SetScale(float4{ 500,80 });
	WinRender->Off();

	NewBazzifront = CreateRender(CrazyRenderOrder::Player);
	NewBazzifront->SetImage("Bazzifront.bmp");
	NewBazzifront->SetPosition(float4{ 680,80 });
	NewBazzifront->SetScale(float4{ 40,40 });
	
}

void BackGround::ActiveOnOffSwicth() {
	ActiveItemRender->OnOffSwtich();
}

void BackGround::Update(float _DeltaTime)
{
	
	ActTime += _DeltaTime;
	if (1.f <= ActTime)
	{
		NewNumberObject.SetValue(--Value);
		if (Value == 0) {
			Value = 59;
		}
		ActTime = 0.f;
	}
	ActTime2 += _DeltaTime;
	if (61.f < ActTime2)
	{
		NewNumberObject2.SetValue(--Value2);
		if (Value2 <= 0) 
		{
			Value2 = 0;
		}
		ActTime2 = 0.f;
	}

	if (2.f < GetLiveTime())
	{
		StartRender->Off();
	}
}