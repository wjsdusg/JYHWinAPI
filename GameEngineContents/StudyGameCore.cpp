#include "StudyGameCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "PlayLevel.h"
#include "TitleLevel.h"


StudyGameCore StudyGameCore::Core;

StudyGameCore::StudyGameCore() 
{
}

StudyGameCore::~StudyGameCore() 
{
}

void StudyGameCore::Start()
{
	
	GameEngineWindow::SettingWindowSize({ 1040 , 780 });

	new int();

	CreateLevel<TitleLevel>("TitleLevel");
	
	ChangeLevel("TitleLevel");

	
}

void StudyGameCore::Update()
{
	
}
void StudyGameCore::End() 
{
	
}
