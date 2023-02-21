#include "PlayLevel.h"

// 프로젝트 순서에 따라서 정렬
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineTileMap.h>

// 나랑 같은 등급의 헤더들
#include "Player.h"
#include "Map.h"
#include "BackGround.h"
#include "MapCover.h"
#include "Bomb.h"
#include "Block.h"
#include "ContentsEnums.h"
#include "DropItem.h"
#include "SpeedItem.h"
#include "BombItem.h"
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

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Block1.BMP"));
		Image->Cut(1, 1);
	}
	{
		GameEngineImage* Image1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ballon.BMP"));
		Image1->Cut(2, 1);
		GameEngineImage* Image2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("skate.BMP"));
		Image2->Cut(2, 1);
		GameEngineImage* Image3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("power_max.BMP"));
		Image3->Cut(2, 1);
	}
	// 액터 생성
	{
		BackGround* Actor = CreateActor<BackGround>();
	}
	{
		Map* Actor = CreateActor<Map>();
	}
	{
		Player* Actor = CreateActor<Player>(CrazyRenderOrder::Player);
	}
	{
		MapCover* Actor = CreateActor< MapCover>();
	}
	{
		Block* Actor = CreateActor< Block>();

		// 맵이 먼저 만들어지고
		Actor->GetTileMap()->SetTileFrame(0, 0, 0, 0);
		Actor->GetTileMap()->SetTileFrame(0, 2, 0, 0);
		Actor->GetTileMap()->SetTileFrame(0, 5, 0, 0);
		Actor->GetTileMap()->SetTileFrame(0, 6, 0, 0);
		Actor->GetTileMap()->SetTileFrame(0, 8, 0, 0);
		Actor->GetTileMap()->SetTileFrame(0, 9, 0, 0);
		Actor->GetTileMap()->SetTileFrame(0,11, 0, 0);
		Actor->GetTileMap()->SetTileFrame(0,13, 0, 0);

		Actor->GetTileMap()->SetTileFrame(0, 2,1 , 0);
		Actor->GetTileMap()->SetTileFrame(0, 3,1 , 0);
		Actor->GetTileMap()->SetTileFrame(0, 4,1 , 0);
		Actor->GetTileMap()->SetTileFrame(0, 5,1 , 0);
		Actor->GetTileMap()->SetTileFrame(0, 6,1 , 0);
		Actor->GetTileMap()->SetTileFrame(0, 8,1 , 0);
		Actor->GetTileMap()->SetTileFrame(0,14,1, 0);

		Actor->GetTileMap()->SetTileFrame(0, 0, 2, 0);
		Actor->GetTileMap()->SetTileFrame(0, 3, 2, 0);
		Actor->GetTileMap()->SetTileFrame(0, 6, 2, 0);
		Actor->GetTileMap()->SetTileFrame(0, 8, 2, 0);
		Actor->GetTileMap()->SetTileFrame(0, 9, 2, 0);
		Actor->GetTileMap()->SetTileFrame(0, 12, 2, 0);
		Actor->GetTileMap()->SetTileFrame(0, 14, 2, 0);

		Actor->GetTileMap()->SetTileFrame(0, 1, 3, 0);
		Actor->GetTileMap()->SetTileFrame(0, 2, 3, 0);
		Actor->GetTileMap()->SetTileFrame(0, 5, 3, 0);
		Actor->GetTileMap()->SetTileFrame(0, 6, 3, 0);
		Actor->GetTileMap()->SetTileFrame(0, 8, 3, 0);
		Actor->GetTileMap()->SetTileFrame(0, 9, 3, 0);
		Actor->GetTileMap()->SetTileFrame(0, 10, 3, 0);
		Actor->GetTileMap()->SetTileFrame(0, 11, 3, 0);
		Actor->GetTileMap()->SetTileFrame(0, 12, 3, 0);
		Actor->GetTileMap()->SetTileFrame(0, 13, 3, 0);

		Actor->GetTileMap()->SetTileFrame(0, 0, 4, 0);
		Actor->GetTileMap()->SetTileFrame(0, 1, 4, 0);
		Actor->GetTileMap()->SetTileFrame(0, 3, 4, 0);
		Actor->GetTileMap()->SetTileFrame(0, 4, 4, 0);
		Actor->GetTileMap()->SetTileFrame(0, 5, 4, 0);
		Actor->GetTileMap()->SetTileFrame(0, 6, 4, 0);
		Actor->GetTileMap()->SetTileFrame(0, 8, 4, 0);
		Actor->GetTileMap()->SetTileFrame(0, 9, 4, 0);
		Actor->GetTileMap()->SetTileFrame(0, 11, 4, 0);
		Actor->GetTileMap()->SetTileFrame(0, 12, 4, 0);
		Actor->GetTileMap()->SetTileFrame(0, 13, 4, 0);

		Actor->GetTileMap()->SetTileFrame(0, 2, 5, 0);
		Actor->GetTileMap()->SetTileFrame(0, 4, 5, 0);
		Actor->GetTileMap()->SetTileFrame(0, 5, 5, 0);
		Actor->GetTileMap()->SetTileFrame(0, 6, 5, 0);
		Actor->GetTileMap()->SetTileFrame(0, 8, 5, 0);
		Actor->GetTileMap()->SetTileFrame(0, 9, 5, 0);
		Actor->GetTileMap()->SetTileFrame(0, 10, 5, 0);
		Actor->GetTileMap()->SetTileFrame(0, 12, 5, 0);
		Actor->GetTileMap()->SetTileFrame(0, 14, 5, 0);

		Actor->GetTileMap()->SetTileFrame(0, 1, 6, 0);
		Actor->GetTileMap()->SetTileFrame(0, 3, 6, 0);
		Actor->GetTileMap()->SetTileFrame(0, 5, 6, 0);
		Actor->GetTileMap()->SetTileFrame(0, 6, 6, 0);
		Actor->GetTileMap()->SetTileFrame(0, 8, 6, 0);
		Actor->GetTileMap()->SetTileFrame(0, 9, 6, 0);
		Actor->GetTileMap()->SetTileFrame(0, 11, 6, 0);
		Actor->GetTileMap()->SetTileFrame(0, 13, 6, 0);

		Actor->GetTileMap()->SetTileFrame(0, 0, 7, 0);
		Actor->GetTileMap()->SetTileFrame(0, 2, 7, 0);
		Actor->GetTileMap()->SetTileFrame(0, 4, 7, 0);
		Actor->GetTileMap()->SetTileFrame(0, 5, 7, 0);
		Actor->GetTileMap()->SetTileFrame(0, 6, 7, 0);
		Actor->GetTileMap()->SetTileFrame(0, 8, 7, 0);
		Actor->GetTileMap()->SetTileFrame(0, 9, 7, 0);
		Actor->GetTileMap()->SetTileFrame(0, 10, 7, 0);
		Actor->GetTileMap()->SetTileFrame(0, 12, 7, 0);

		Actor->GetTileMap()->SetTileFrame(0, 1, 8, 0);
		Actor->GetTileMap()->SetTileFrame(0, 3, 8, 0);
		Actor->GetTileMap()->SetTileFrame(0, 5, 8, 0);
		Actor->GetTileMap()->SetTileFrame(0, 6, 8, 0);
		Actor->GetTileMap()->SetTileFrame(0, 8, 8, 0);
		Actor->GetTileMap()->SetTileFrame(0, 9, 8, 0);
		Actor->GetTileMap()->SetTileFrame(0, 10, 8, 0);
		Actor->GetTileMap()->SetTileFrame(0, 11, 8, 0);
		Actor->GetTileMap()->SetTileFrame(0, 13, 8, 0);
		Actor->GetTileMap()->SetTileFrame(0, 14, 8, 0);

		Actor->GetTileMap()->SetTileFrame(0, 1, 9, 0);
		Actor->GetTileMap()->SetTileFrame(0, 3, 9, 0);
		Actor->GetTileMap()->SetTileFrame(0, 4, 9, 0);
		Actor->GetTileMap()->SetTileFrame(0, 5, 9, 0);
		Actor->GetTileMap()->SetTileFrame(0, 6, 9, 0);
		Actor->GetTileMap()->SetTileFrame(0, 8, 9, 0);
		Actor->GetTileMap()->SetTileFrame(0, 9, 9, 0);
		Actor->GetTileMap()->SetTileFrame(0, 12, 9, 0);
		Actor->GetTileMap()->SetTileFrame(0, 13, 9, 0);

		Actor->GetTileMap()->SetTileFrame(0, 0, 10, 0);
		Actor->GetTileMap()->SetTileFrame(0, 2, 10, 0);
		Actor->GetTileMap()->SetTileFrame(0, 3, 10, 0);
		Actor->GetTileMap()->SetTileFrame(0, 4, 10, 0);
		Actor->GetTileMap()->SetTileFrame(0, 5, 10, 0);
		Actor->GetTileMap()->SetTileFrame(0, 6, 10, 0);
		Actor->GetTileMap()->SetTileFrame(0, 8, 10, 0);
		Actor->GetTileMap()->SetTileFrame(0, 11, 10, 0);
		Actor->GetTileMap()->SetTileFrame(0, 14, 10, 0);

		Actor->GetTileMap()->SetTileFrame(0, 0, 11, 0);
		Actor->GetTileMap()->SetTileFrame(0, 6, 11, 0);
		Actor->GetTileMap()->SetTileFrame(0, 8, 11, 0);
		Actor->GetTileMap()->SetTileFrame(0, 9, 11, 0);
		Actor->GetTileMap()->SetTileFrame(0, 10, 11, 0);
		Actor->GetTileMap()->SetTileFrame(0, 11, 11, 0);
		Actor->GetTileMap()->SetTileFrame(0, 12, 11, 0);
		
		Actor->GetTileMap()->SetTileFrame(0, 1, 12, 0);
		Actor->GetTileMap()->SetTileFrame(0, 3, 12, 0);
		Actor->GetTileMap()->SetTileFrame(0, 5, 12, 0);
		Actor->GetTileMap()->SetTileFrame(0, 6, 12, 0);
		Actor->GetTileMap()->SetTileFrame(0, 8, 12, 0);
		Actor->GetTileMap()->SetTileFrame(0, 9, 12, 0);
		Actor->GetTileMap()->SetTileFrame(0, 12, 12, 0);
		Actor->GetTileMap()->SetTileFrame(0, 14, 12, 0);

		// 아이템이 몇개 배치될지 결정한다음
		Actor->ItemCountInsert(ItemType::Skate, 1);
		Actor->ItemCountInsert(ItemType::PowerMax, 1);
		Actor->ItemCountInsert(ItemType::Bomb, 1);

		// 아이템을 진짜 배치한다.
		Actor->ItemCreate();

	}
	{
		DropItem* Actor = CreateActor<BombItem>(CrazyRenderOrder::DropItem);
		Actor->SetPos(float4(200, 200));
	}
	{
		DropItem* Actor = CreateActor<SpeedItem>(CrazyRenderOrder::DropItem);
		Actor->SetPos(float4(240, 200));
	}

	//if (false == GameEngineInput::IsKey("PlayerOff"))
	//{
	//	GameEngineInput::CreateKey("PlayerOff", 'R');
	//}

	if (false == GameEngineInput::IsKey("CollisionRender")) {
		GameEngineInput::CreateKey("CollisionRender", 'R');
	}
	
}

void PlayLevel::Update(float _DeltaTime)
{
	//if (GameEngineInput::IsDown("PlayerOff"))
	//{
	//	Player::MainPlayer->OnOffSwtich();
	//	// Player::MainPlayer->Death()p;
	//}

	if (GameEngineInput::IsDown("CollisionRender")) {
		DebugRenderSwitch();
	}

	

}