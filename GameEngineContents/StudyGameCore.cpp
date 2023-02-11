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

	CreateLevel<PlayLevel>("PlayLevel");
	
	ChangeLevel("PlayLevel");

	
}

void StudyGameCore::Update()
{
	
}
void StudyGameCore::End() 
{
	
}
