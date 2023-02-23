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
		GameEngineImage* Image1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Block1.BMP"));
		Image1->Cut(6, 1);
		GameEngineImage* Image2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Block2.BMP"));
		Image2->Cut(1, 1);
		GameEngineImage* Image3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TownBush.BMP"));
		Image3->Cut(1, 1);
		GameEngineImage* Image4 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Wood3Block.BMP"));
		Image4->Cut(3, 1);
		GameEngineImage* Image5 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WoodBlock.BMP"));
		Image5->Cut(1, 1);

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

		
		//1
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 0, 0, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 2, 0, 0);


		Actor->GetTileMap()->GetTile(static_cast<int>(BlockType::TownBush), 2, 0)->SetMove(float4{ 0,-5 });
		Actor->GetTileMap()->GetTile(static_cast<int>(BlockType::TownBush), 2,0)->SetScale(float4(40, 50));
		
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 5, 0, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 6, 0, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 8, 0, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 9, 0, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush),11, 0, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1),13, 0, 0);
		//2
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::WoodBlock), 2,1 , 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 3,1 , 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 4,1 , 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 5,1 , 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 6,1 , 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 8,1 , 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1),14,1, 0);        
		                                                      
		//3
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 0, 2, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 3, 2, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 6, 2, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 8, 2, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 9, 2, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::WoodBlock), 12, 2, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 14, 2, 0);
		//4
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 2, 3, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::WoodBlock), 1, 3, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::WoodBlock), 5, 3, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 6, 3, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 8, 3, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 9, 3, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::WoodBlock), 10, 3, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 11, 3, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 12, 3, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 13, 3, 0);
		//5
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::WoodBlock), 0, 4, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 1, 4, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 3, 4, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 4, 4, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 5, 4, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 6, 4, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 8, 4, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 9, 4, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Wood3Block), 11, 4, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 12, 4, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 13, 4, 0);
		//6
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 2, 5, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 4, 5, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 5, 5, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 6, 5, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 8, 5, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 9, 5, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 10, 5, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Wood3Block), 12, 5, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 14, 5, 0);
		//7
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 1, 6, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Wood3Block), 3, 6, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 5, 6, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Wood3Block), 6, 6, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Wood3Block), 8, 6, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 9, 6, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Wood3Block), 11, 6, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 13, 6, 0);
		//8
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 0, 7, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Wood3Block), 2, 7, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 4, 7, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 5, 7, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 6, 7, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 8, 7, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 9, 7, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 10, 7, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 12, 7, 0);
		//9
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 1, 8, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Wood3Block), 3, 8, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 5, 8, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 6, 8, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 8, 8, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 9, 8, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 10, 8, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 11, 8, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 13, 8, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::WoodBlock), 14, 8, 0);
		//10
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 1, 9, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 3, 9, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::WoodBlock), 4, 9, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 5, 9, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 6, 9, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 8, 9, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::WoodBlock), 9, 9, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::WoodBlock), 12, 9, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 13, 9, 0);
		//11
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 0, 10, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::WoodBlock), 2, 10, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 3, 10, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 4, 10, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 5, 10, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 6, 10, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 8, 10, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 11, 10, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 14, 10, 0);
		//12
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 0, 11, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 6, 11, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 8, 11, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 9, 11, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 10, 11, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 11, 11, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::WoodBlock), 12, 11, 0);
		//13
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 1, 12, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 3, 12, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 5, 12, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 6, 12, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block2), 8, 12, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 9, 12, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::TownBush), 12, 12, 0);
		Actor->GetTileMap()->SetTileFrame(static_cast<int>(BlockType::Block1), 14, 12, 0);
		
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