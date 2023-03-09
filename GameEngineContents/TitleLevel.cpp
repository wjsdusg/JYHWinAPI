#include "TitleLevel.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "TitleBack.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}


void TitleLevel::Loading()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Title");

	// 이미지 로드
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("login_scene.BMP"));
	}

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Button_Start_1.BMP"));
		Image->Cut(1, 1);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Button_Start_2.BMP"));
		Image->Cut(1, 1);
	}
	
	Dir.MoveParentToDirectory("Sound");
	Dir.Move("Sound");

	{
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Login.mp3"));
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("bomb1.wav"));
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Camp_KCW.mp3"));
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("gamestart.wav"));
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("item.wav"));
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Stage1.wav"));
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Stage3.wav"));
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("wave.wav"));
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Win_Effect.wav"));
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Start_Effect.wav"));
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Pung.wav"));
	}
	//
	CreateActor<TitleBack>();
	
}
void TitleLevel::Update(float _DeltaTime)
{
	
	
}

void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	SoundPlayerBGM = GameEngineResources::GetInst().SoundPlayToControl("Login.mp3");
	SoundPlayerBGM.LoopCount(100);

}
void TitleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	SoundPlayerBGM.Stop();
}