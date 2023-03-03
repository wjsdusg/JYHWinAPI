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
#include "PlayLevel.h"
#include "Block.h"
#include "DropItem.h"
#include "ContentsValue.h"
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

	SetMove(GameEngineWindow::GetScreenSize().half() - float4{ 200,0 });

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
		AnimationRender->SetScale({ 50, 60 });

		AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle",  .ImageName = "right.bmp", .Start = 0, .End = 0 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Move",  .ImageName = "right.bmp", .Start = 0, .End = 5 });

		AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle",  .ImageName = "left.bmp", .Start = 0, .End = 0, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Move",  .ImageName = "left.bmp", .Start = 0, .End = 5 });

		AnimationRender->CreateAnimation({ .AnimationName = "Up_Idle",  .ImageName = "up.bmp", .Start = 0, .End = 0 });
		AnimationRender->CreateAnimation({ .AnimationName = "Up_Move",  .ImageName = "up.bmp", .Start = 0, .End = 7 });

		AnimationRender->CreateAnimation({ .AnimationName = "Down_Idle",  .ImageName = "down.bmp", .Start = 0, .End = 0 });
		AnimationRender->CreateAnimation({ .AnimationName = "Down_Move",  .ImageName = "down.bmp", .Start = 0, .End = 7 });
		AnimationRender->CreateAnimation({ .AnimationName = "BlankMode",  .ImageName = "blank.bmp", .Start = 0, .End = 0 });
		AnimationRender->CreateAnimation({ .AnimationName = "Wait",  .ImageName = "wait.bmp", .Start = 0, .End = 0 });
	}

	ChangeState(PlayerState::IDLE);
}

bool Player::Movecalculation(float4 _Pos)
{
	NewPlayerCollisionData.Position = _Pos;
	NewPlayerCollisionData.Scale = float4{ 40,40 };

	float4 MoveDir;

	switch (NewPlayerDiretion)
	{
	case PlayerDirection::Left:
		MoveDir = float4::Left;
		CollisionDiretion = NewPlayerCollisionData.LeftPos();
		break;
	case PlayerDirection::Right:
		MoveDir = float4::Right;
		CollisionDiretion = NewPlayerCollisionData.RightPos();
		break;
	case PlayerDirection::Up:
		MoveDir = float4::Up;
		CollisionDiretion = NewPlayerCollisionData.TopPos();
		break;
	case PlayerDirection::Down:
		MoveDir = float4::Down;
		CollisionDiretion = NewPlayerCollisionData.DownPos();
		break;
	default:
		break;
	}

	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("Camp_ColMap.BMP");
	PlayLevel* NewPlayLevel = dynamic_cast<PlayLevel*>(GetLevel());
	if (nullptr != NewPlayLevel) {

		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("Camp_ColMap.BMP");
		if (nullptr == ColImage)
		{
			MsgAssert("충돌용 맵 이미지가 없습니다.");
			return false;
		}

		if (RGB(0, 0, 0) == ColImage->GetPixelColor(CollisionDiretion, RGB(0, 0, 0)))
		{
			return false;
		}
	}


	if (true == Block::OwnerBlock->IsMapOut(CollisionDiretion)) {
		return false;
	}

	if (true == Block::OwnerBlock->IsBlock(CollisionDiretion)) {

		if (Block::OwnerBlock->GetTileMap()->GetTile(static_cast<int>(BlockType::TownBush), CollisionDiretion)->IsUpdate() == true) {
			Block::OwnerBlock->GetTileMap()->GetTile(static_cast<int>(BlockType::TownBush), CollisionDiretion)->SetOrder(100);

			return true;
		}
		//나무블록확인
		if (Block::OwnerBlock->GetTileMap()->GetTile(static_cast<int>(BlockType::Block1), CollisionDiretion)->GetFrame() == 1) {
			// 밀었는데 
			WoodRender = Block::OwnerBlock->GetTileMap()->GetTile(static_cast<int>(BlockType::Block1), CollisionDiretion);

			WoodStartPos = WoodRender->GetPosition();
			WoodTagetPos = WoodRender->GetPosition();

			if (WoodBlockCheck == false) {

				WoodBlockCheck = true;
				float4 WoodPos = { 0.f,0.f };
				switch (NewPlayerDiretion)
				{

				case PlayerDirection::Left:

					WoodPos = CollisionDiretion;
					WoodPos.x -= ContentsValue::TileSize;
					WoodTagetPos += float4::Left * ContentsValue::TileSize;
					break;
				case PlayerDirection::Right:
					WoodPos = CollisionDiretion;
					WoodPos.x += ContentsValue::TileSize;
					WoodTagetPos += float4::Right * ContentsValue::TileSize;
					break;
				case PlayerDirection::Up:
					WoodPos = CollisionDiretion;
					WoodPos.y -= ContentsValue::TileSize;
					WoodTagetPos += float4::Up * ContentsValue::TileSize;
					break;
				case PlayerDirection::Down:
					WoodPos = CollisionDiretion;
					WoodPos.y += ContentsValue::TileSize;
					WoodTagetPos += float4::Down * ContentsValue::TileSize;
					break;
				default:
					break;
				}

				Block::OwnerBlock->NewGameEngineTileMap->TileIndexChange(static_cast<int>(BlockType::Block1), WoodStartPos, WoodTagetPos);

				/*if (true == Block::OwnerBlock->IsBlock(WoodPos)) {
					WoodBlockCheck = false;
					return false;
				}*/


				return true;
			}
		}


		return false;
	}


	Bomb* FindBomb = Bomb::GetBomb(CollisionDiretion);

	if (nullptr != FindBomb)
	{
		if (NewBomb != nullptr)
		{
			// 나의 미래의 위치에도 폭탄이 있다면 안된다.
			Bomb* NextBomb = Bomb::GetBomb(GetPos() + MoveDir * 40.0f);
			if (nullptr != NextBomb)
			{
				return false;
			}

			PlayerCollisionData BombData;
			BombData.Position = FindBomb->GetPos();
			BombData.Scale = FindBomb->AnimationRender->GetScale();
			if (true == CollisionRectToRect(BombData, NewPlayerCollisionData)) {

				return true;
			}
			if (false == NewBomb->IsUpdate())
			{
				NewBomb = nullptr;
			}
		}
		return false;
	}
	else {
		NewBomb = nullptr;
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
				GameEngineActor* ColActor = Collision[i]->GetActor();  //DropItem을상속하는 Item
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

	if (GameEngineInput::IsDown("Space") && BombCount > 0 && nullptr == NewBomb)
	{
		NewBomb = GetLevel()->CreateActor<Bomb>();
		float4 BombPos = GetPos();
		BombPos.y += 10.f;
		NewBomb->InitBomb(Block::OwnerBlock->GetTileMap()->ConvertIndexToTilePosition(BombPos));

		NewBombPos = NewBomb->GetPos();
		//Len = (GetPos() - NewBombPos).Size();
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
	else if (GameEngineInput::IsPress("RightMove"))
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
	float4 ActorPos = CollisionDiretion;

	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);
	std::string Text = "PlayerCollisonPos : ";
	Text += CollisionDiretion.ToString();
	GameEngineLevel::DebugTextPush(Text);

	if (NewBomb != nullptr) {

		std::string Text2 = "BombPos : ";
		Text2 += NewBomb->GetPos().ToString();
		GameEngineLevel::DebugTextPush(Text2);

	}
	std::string Text3 = "WoodBlockCheck : ";
	Text3 += WoodBlockCheck;
	GameEngineLevel::DebugTextPush(Text3);
	// 디버깅용.
}

bool Player::CollisionRectToRect(const PlayerCollisionData& _Left, const PlayerCollisionData& _Right)
{
	//둘이 감싸고있으면 true

		//왼쪽바텀이 오른쪽 탑보다  

	float a = _Left.Bot();
	float b = _Right.Top();
	if (a < b)
	{
		return false;
	}

	if (_Left.Top() > _Right.Bot())
	{
		return false;
	}

	if (_Left.Left() > _Right.Right())
	{
		return false;
	}

	if (_Left.Right() < _Right.Left())
	{
		return false;
	}

	return true;
}