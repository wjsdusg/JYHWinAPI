#include "TitleBack.h"
#include "ContentsEnums.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
TitleBack::TitleBack() 
{
}

TitleBack::~TitleBack() 
{
}


void TitleBack::Start() 
{
	
	

	Render = CreateRender("login_scene.bmp", CrazyRenderOrder::BackGround);
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
	Render->SetScale(GameEngineWindow::GetScreenSize());

	NewAnimation = CreateRender( CrazyRenderOrder::BackGround);
	float4 GameStartPos = GameEngineWindow::GetScreenSize().half();
	GameStartPos.y += 100.f;
	NewAnimation->SetPosition(GameStartPos);
	NewAnimation->SetScale(float4{200,60});
	NewAnimation->CreateAnimation({ .AnimationName = "GameSart1",  .ImageName = "Button_Start_1.bmp", .Start = 0, .End = 0 });
	NewAnimation->CreateAnimation({ .AnimationName = "GameSart2",  .ImageName = "Button_Start_2.bmp", .Start = 0, .End = 0 });
	NewAnimation->ChangeAnimation("GameSart1");
	if (false == GameEngineInput::IsKey("GameSart"))
	{
		GameEngineInput::CreateKey("GameSart", VK_RETURN);
	}

}

void TitleBack::Update(float _DeltaTIme)
{
	if (GameEngineInput::IsDown("GameSart")) {
		NewAnimation->ChangeAnimation("GameSart2");
		IsAct = true;
	}
	if (true == IsAct) {
		ActTime += _DeltaTIme;
	}
	if (ActTime > 0.5f) {
		GameEngineCore::GetInst()->ChangeLevel("PlayLevel");
	}
}