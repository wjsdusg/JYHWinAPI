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
#include "Bomb.h"
#include "Block.h"
#include "ContentsEnums.h"
#include "DropItem.h"
#include "SpeedItem.h"
#include "BombItem.h"
#include "Monster.h"
#include "PirateMonster.h"
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
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Monster.BMP"));
		Image->Cut(8, 1);
		GameEngineImage* Image2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("monsterdie.BMP"));
		Image2->Cut(4, 1);
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
	{
		Block* Actor = CreateActor< Block>();
	}
	{
		PirateMonster* Actor = CreateActor<PirateMonster>();
	}
	{

	}
	if (false == GameEngineInput::IsKey("CollisionRender")) {
		GameEngineInput::CreateKey("CollisionRender", 'R');
	}

	

}


void MonsterPLevel::Update(float _DeltaTime)
{


	if (GameEngineInput::IsDown("CollisionRender")) {
		DebugRenderSwitch();
	}



}