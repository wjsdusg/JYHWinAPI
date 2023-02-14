#include "PlayLevel.h"

// 프로젝트 순서에 따라서 정렬
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>

// 나랑 같은 등급의 헤더들
#include "Player.h"
#include "Map.h"
#include "BackGround.h"
#include "MapCover.h"
#include "Bomb.h"
PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Loading()
{
	// 상대경로 탐색
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	// 이미지 로드
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BazziMoveAll.BMP"));
		Image->Cut(4,4);
		GameEngineImage* Image2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WaitBazzi.BMP"));
		Image2->Cut(3, 1);
	}
	
	
	
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PlayUI.BMP"));
		GameEngineImage* MapImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Camp_Back.BMP"));
		GameEngineImage* COlMapImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Camp_ColMap.BMP"));
		GameEngineImage* CoverMapImage = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Camp_Front.BMP"));

		
		
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Bomb.BMP"));
		Image->Cut(4, 1);
		GameEngineImage* Image2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("unit_bombwaterAll.BMP"));
		Image2->Cut(4, 10);
	}
	// 액터 생성
	{
		BackGround* Actor = CreateActor<BackGround>();
	}
	{
		Map* Actor = CreateActor<Map>();
	}
	{
		Player* Actor = CreateActor<Player>();
	}
	{
		MapCover* Actor = CreateActor< MapCover>();
	}


	if (false == GameEngineInput::IsKey("PlayerOff"))
	{
		GameEngineInput::CreateKey("PlayerOff", 'R');
	}


	
}

void PlayLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("PlayerOff"))
	{
		Player::MainPlayer->OnOffSwtich();
		// Player::MainPlayer->Death()p;
	}



	

}