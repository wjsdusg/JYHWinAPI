#include "StudyGameCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "PlayLevel.h"
#include "TitleLevel.h"
#include "Block.h"
#include "MonsterPLevel.h"

StudyGameCore StudyGameCore::Core;

StudyGameCore::StudyGameCore() 
{
}

StudyGameCore::~StudyGameCore() 
{
}

void StudyGameCore::Start()
{
	
	GameEngineWindow::SettingWindowSize({ 800 , 600 });

	new int();
	
    CreateLevel<TitleLevel>("TitleLevel");

	CreateLevel<PlayLevel>("PlayLevel");
	
	CreateLevel<MonsterPLevel>("MonsterPLevel");

	ChangeLevel("TitleLevel");

	
}

void StudyGameCore::Update()
{
	
}
void StudyGameCore::End() 
{
	Block::OwnerBlock = nullptr;
}
