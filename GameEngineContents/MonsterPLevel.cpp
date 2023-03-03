#include "MonsterPLevel.h"

// ������Ʈ ������ ���� ����
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineTileMap.h>

// ���� ���� ����� �����
#include "Player.h"
#include "MonsterMap.h"
#include "BackGround.h"
#include "MapCover.h"
#include "Bomb.h"
#include "Block.h"
#include "ContentsEnums.h"
#include "DropItem.h"
#include "SpeedItem.h"
#include "BombItem.h"
MonsterPLevel::MonsterPLevel()
{
}

MonsterPLevel::~MonsterPLevel()
{
}

void MonsterPLevel::Loading()
{

}
void MonsterPLevel::LevelChangeStart(GameEngineLevel* _PrevLevel) {
	// ����� Ž��
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

	// �̹��� �ε�	
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MonsterStage2_Back.BMP"));

	}

	// ���� ����
	{
		BackGround* Actor = CreateActor<BackGround>();
	}
	{
		MonsterMap* Actor = CreateActor<MonsterMap>();
	}
	{
		Player* Actor = CreateActor<Player>(CrazyRenderOrder::Player);
	}

	Block* Actor = CreateActor< Block>();

	if (false == GameEngineInput::IsKey("CollisionRender")) {
		GameEngineInput::CreateKey("CollisionRender", 'R');
	}

	if (false == GameEngineInput::IsKey("BlockDestroy")) {
		GameEngineInput::CreateKey("BlockDestroy", 'P');
	}

}


void MonsterPLevel::Update(float _DeltaTime)
{


	if (GameEngineInput::IsDown("CollisionRender")) {
		DebugRenderSwitch();
	}

	if (GameEngineInput::IsDown("BlockDestroy")) {
		Block::OwnerBlock->AllBlockDestroy();
	}


}