#include "StudyGameCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "PlayLevel.h"
#include "TitleLevel.h"

// StudyGameCore StudyGameCore::Core = new StudyGameCore();

// �߰��� ����� �������� �����ָ� ������������ ���� �����Ҵ��ؼ� ����Ѵٴ°�
// �������⿡�� ��??? �׷�������?
StudyGameCore StudyGameCore::Core;

StudyGameCore::StudyGameCore() 
{
}

StudyGameCore::~StudyGameCore() 
{
}

void StudyGameCore::Start()
{
	// ������ ���� �������? ������ ������ ���ɴϴ�.
	// �Ǽ� 1.2 ���Ѵٸ� 
	GameEngineWindow::SettingWindowSize({1280, 960});

	new int();

	CreateLevel<TitleLevel>("TitleLevel");
	//CreateLevel<PlayLevel>("PlayLevel");
	// static_assert
	// CreateLevel<HPlayer>("Title1");
	ChangeLevel("TitleLevel");

	float4 AAAA = {100, 100};

	AAAA = -AAAA;
}

void StudyGameCore::Update()
{
	
}
void StudyGameCore::End() 
{
	
}
//ffffffffffffffffffffffffffffff