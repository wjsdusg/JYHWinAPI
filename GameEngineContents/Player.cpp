#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsEnums.h"
#include "Bomb.h"
#include "BombPower.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineTileMap.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Block.h"
#include "DropItem.h"
Player* Player::MainPlayer;

Player::Player() 
{
}

Player::~Player() 
{
}

int Player::BombCount = 2;
int Player::PBombPower = 2;

void Player::Start()
{
	MainPlayer = this;

	SetMove(GameEngineWindow::GetScreenSize().half()-float4{200,0});

	NewGameEngineTileMap = GetLevel()->CreateActor<GameEngineTileMap>();
	NewGameEngineTileMap->SetPos(float4(20, 40));
	NewGameEngineTileMap->CreateTileMap(15, 13, 1, 0, float4{ 40,40 });
	
	BodyCollision = CreateCollision(CrazyRenderOrder::Player);
	BodyCollision->SetScale(float4(40, 40));

	if (false == GameEngineInput::IsKey("LeftMove"))
	{
		GameEngineInput::CreateKey("LeftMove", 'A');
		GameEngineInput::CreateKey("RightMove", 'D');
		GameEngineInput::CreateKey("DownMove", 'S');
		GameEngineInput::CreateKey("UpMove", 'W');
		GameEngineInput::CreateKey("Space", VK_SPACE);
	}

	{
		
		AnimationRender = CreateRender(CrazyRenderOrder::Player);
		AnimationRender->SetScale({ 160, 160 });

		AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle",  .ImageName = "WaitBazzi.bmp", .Start = 0, .End = 2, .InterTime = 0.4f});
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Move",  .ImageName = "BazziMoveAll.bmp", .Start = 0, .End = 3 });

		AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = "WaitBazzi.bmp", .Start = 0, .End = 2, .InterTime = 0.4f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = "BazziMoveAll.bmp", .Start = 4, .End = 7 });
	
		AnimationRender->CreateAnimation({ .AnimationName = "Up_Idle",  .ImageName = "WaitBazzi.bmp", .Start = 0, .End = 2, .InterTime = 0.4f });
		AnimationRender->CreateAnimation({ .AnimationName = "Up_Move",  .ImageName = "BazziMoveAll.bmp", .Start = 12, .End = 15 });

		AnimationRender->CreateAnimation({ .AnimationName = "Down_Idle",  .ImageName = "WaitBazzi.bmp", .Start = 0, .End = 2, .InterTime = 0.4f });
		AnimationRender->CreateAnimation({ .AnimationName = "Down_Move",  .ImageName = "BazziMoveAll.bmp", .Start = 8, .End = 11 });
	}

	ChangeState(PlayerState::IDLE);
}

bool Player::Movecalculation(float4 _Pos)
{
	
	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("Camp_ColMap.BMP");
	if (nullptr == ColImage)
	{
		MsgAssert("�浹�� �� �̹����� �����ϴ�.");
		return false;
	}
	

	if (RGB(0, 0, 0) == ColImage->GetPixelColor(_Pos, RGB(0, 0, 0)))
	{
		return false;
	}
	if (true == Block::OwnerBlock->IsBlock(_Pos)) {
		return false;
	}


	if (BodyCollision != nullptr) {

		std::vector<GameEngineCollision*> Collision;

		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CrazyRenderOrder::BombtoPlayer), .TargetColType = CT_CirCle , .ThisColType = CT_CirCle }, Collision)) {

			for (size_t i = 0; i < Collision.size(); i++)
			{
				if (nullptr != NewBomb2 && NewBomb2->GetBlockCollision() == Collision[i])
				{
					continue;
				}

				return false;
			}
		}
		else 
		{
			if (nullptr != NewBomb2)
			{
				NewBomb2 = nullptr;
			}
		}

	}

	return true;
	
}

void Player::Update(float _DeltaTime) 
{
	UpdateState(_DeltaTime);

	if (BodyCollision != nullptr) {

		std::vector<GameEngineCollision*> Collision;
	
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CrazyRenderOrder::DropItem), .TargetColType = CT_Point , .ThisColType = CT_CirCle }, Collision)) {

			for (size_t i = 0; i < Collision.size(); i++)
			{
				GameEngineActor* ColActor = Collision[i]->GetActor();  //DropItem������ϴ� Item
				DropItem* Drop = dynamic_cast<DropItem*>(ColActor);

				if (nullptr == Drop)
				{
					continue;
				}

				ItemType NewItemType = Drop->GetItemType();

				if (NewItemType == ItemType::Bomb) {
					this->BombCount++;
				}
				if (NewItemType == ItemType::Skate) {
					this->MoveSpeed += 10.f;
				}
				if (NewItemType == ItemType::PowerMax) {
					this->PBombPower = 7;
				}

				ColActor->Death();
			}
		}

	}
	
	if (GameEngineInput::IsDown("Space")&&BombCount>0 && nullptr == NewBomb2)
	{		
			NewBomb2 = GetLevel()->CreateActor<Bomb>();
			NewBomb2->SetPos(NewGameEngineTileMap->ConvertIndexToTilePosition(GetPos()));
			BombCount--;
	}
}

void Player::DirCheck(const std::string_view& _AnimationName)
{
	std::string PrevDirString = DirString;
	AnimationRender->ChangeAnimation(DirString + _AnimationName.data());

	if (GameEngineInput::IsPress("LeftMove"))
	{
		DirString = "Left_";
	}
	else if(GameEngineInput::IsPress("RightMove"))
	{
		DirString = "Right_";
	}
	else if (GameEngineInput::IsPress("UpMove")) {
		DirString = "Up_";
	}
	else if (GameEngineInput::IsPress("DownMove")) {
		DirString = "Down_";
	}

	

	if (PrevDirString != DirString)
	{
		AnimationRender->ChangeAnimation(DirString + _AnimationName.data());
	}
}

void Player::Render(float _DeltaTime)
{
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos();

	Rectangle(DoubleDC, 
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
		);

	// ������.
}