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
}

void BackGround::ActiveOnOffSwicth() {
	ActiveItemRender->OnOffSwtich();
}