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

void BackGround::Start() 
{
	{
		GameEngineRender* AnimationRender = CreateRender(CrazyRenderOrder::BackGround);
		AnimationRender->SetPosition(GameEngineWindow::GetScreenSize().half());
		AnimationRender->SetScale(GameEngineWindow::GetScreenSize());
		AnimationRender->SetImage("PlayUI.BMP");
	}

}