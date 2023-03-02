#include "Block.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineTileMap.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "SpeedItem.h"
#include "MaxPower.h"
#include "BombItem.h"
#include "ContentsValue.h"


Block::Block()
{
}

Block::~Block()
{
}

Block* Block::OwnerBlock=nullptr;


void Block::Start()
{
	OwnerBlock = this;
	NewGameEngineTileMap =GetLevel()->CreateActor<GameEngineTileMap>();
	NewGameEngineTileMap->SetPos(float4(20, 40));
	NewGameEngineTileMap->CreateTileMap(ContentsValue::XTileNum, ContentsValue::YTileNum, static_cast<int>(BlockType::Max), static_cast<int>(CrazyRenderOrder::Block), float4(40, 40));
	NewGameEngineTileMap->SetFloorSetting(static_cast<int>(BlockType::Block1), "Block1.bmp");
	NewGameEngineTileMap->SetFloorSetting(static_cast<int>(BlockType::TownBush), "TownBush.bmp");

	
}

void Block::Update(float DeltaTime) {

	if (Player::MainPlayer->WoodBlockCheck == true) {
		//플레이어한테 위치를 받는다.
		// 렌더,목표위치를받는다
		//목표위치까지 일정시간으로 움직인다.

		// float4::Left;
		
		if (false == (Player::MainPlayer->WoodRender->GetPosition() == Player::MainPlayer->WoodTagetPos)) {
			MoveWoodBlock(Player::MainPlayer->WoodRender, Player::MainPlayer->WoodStartPos, Player::MainPlayer->WoodTagetPos, DeltaTime);
		}
		/*else if(true== (Player::MainPlayer->WoodRender->GetPosition() == Player::MainPlayer->WoodTagetPos)) {
			Player::MainPlayer->WoodBlockCheck = false;
		}*/
		
	}
}
void Block::ItemCountInsert(ItemType _Type, int _Count)
{
	ItemCounts[_Type] = _Count;
}

// 이걸 호출하는 순간 블록에 맞춰서 아이템을 만든다.
void Block::ItemCreate()
{   //전체타일개수
	std::vector<TileIndex> AllTileIndex = NewGameEngineTileMap->GetAllTileIndex(static_cast<int>(BlockType::Block1));

	for (size_t i = 0; i < 200; i++)
	{
		int Left = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(AllTileIndex.size() - 1));
		int Right = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(AllTileIndex.size() - 1));

		TileIndex Index = AllTileIndex[Left];
		AllTileIndex[Left] = AllTileIndex[Right];
		AllTileIndex[Right] = Index;
	}

	int Count = 0;

	for (std::pair<ItemType, int> ItemTypePair : ItemCounts)
	{
		for (size_t i = 0; i < ItemTypePair.second; i++)
		{
			ItemType Type = ItemTypePair.first;

			switch (Type)
			{
			case ItemType::Skate:
			{
				TileIndex Index = AllTileIndex[Count];
				SpeedItem* Item = GetLevel()->CreateActor<SpeedItem>();
				float4 CreatePos = Block::NewGameEngineTileMap->ConvertIndexToTilePosition(Index.X, Index.Y);
				Item->SetPos(CreatePos);
				break;
			}
			case ItemType::Bomb:
			{
				TileIndex Index = AllTileIndex[Count];
				BombItem* Item = GetLevel()->CreateActor<BombItem>();
				float4 CreatePos = Block::NewGameEngineTileMap->ConvertIndexToTilePosition(Index.X, Index.Y);
				Item->SetPos(CreatePos);
				break;
			}
			case ItemType::PowerMax:
			{
				TileIndex Index = AllTileIndex[Count];
				MaxPower* Item = GetLevel()->CreateActor<MaxPower>();
				float4 CreatePos = Block::NewGameEngineTileMap->ConvertIndexToTilePosition(Index.X, Index.Y);
				Item->SetPos(CreatePos);
				break;
			}
			case ItemType::Max:
				break;
			default:
				break;
			}

			Count++;

			if (Count >= AllTileIndex.size())
			{
				return;
			}
		}

	}
}

bool Block::IsBlock(float4 _Pos) 
{
	
	 // += NewGameEngineTileMap->GetPos()
	
	for (int i = 0; i < static_cast<int>(BlockType::Max); i++) {
		GameEngineRender* TilePtr = NewGameEngineTileMap->GetTile(i, _Pos);
		if (static_cast<int>(BlockType::TownBush) == i) {
			continue;
		}
		if (nullptr != TilePtr)
		{
			bool check = TilePtr->IsUpdate();
			if (true == check) {
				return true;
			}
		}
	}
	

	
	return false;


	//return NewGameEngineTileMap->GetTile(0, float4(1, 0))->IsUpdate();
}

bool Block::IsMapOut(float4 _Pos) {
	float4 Pos = NewGameEngineTileMap->GetIndex(_Pos);
	if (false == NewGameEngineTileMap->IsValidIndex(0, Pos.y, Pos.x))
	{
		return true;
	}
	return false;
}

void Block::AllBlockDestroy() {
	   
		std::vector<TileIndex> AllTileIndex = Block::NewGameEngineTileMap->GetAllTileIndex(static_cast<int>(BlockType::Block1));
		for (int i = 0; i < AllTileIndex.size(); i++) {
			int x = AllTileIndex[i].X;
			int y = AllTileIndex[i].Y;
			Block::NewGameEngineTileMap->GetTile(static_cast<int>(BlockType::Block1), x, y)->Death();
		}

}
	
void  Block::MoveWoodBlock(GameEngineRender* _GameEngineRender, float4 StartPos, float4 TargetPos,float _DeltaTime)
{
	// lerp를 사용하는 최선으로 보인다.

	// Lerp = (목적ㅈ)

	//              0, 0     100, 0
	// float4::Lerp(시작위치, 끝위치, 0~1.0f)
	// float4::Lerp(시작위치, 끝위치, 0.5f)

	BlockMoveTime += _DeltaTime;

	float4 Pos = float4::LerpClamp(StartPos, TargetPos, BlockMoveTime);

	_GameEngineRender->SetPosition(Pos);
	/*if (BlockMoveTime >= 1) {
		Player::MainPlayer->WoodBlockCheck = false;
	}*/

}
