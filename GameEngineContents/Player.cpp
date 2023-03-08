#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsEnums.h"
#include "Bomb.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineTileMap.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "PlayLevel.h"
#include "Block.h"
#include "DropItem.h"
#include "ContentsValue.h"
#include "BackGround.h"
Player* Player::MainPlayer;

Player::Player()
{
}

Player::~Player()
{
}



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
	
		AnimationRender->CreateAnimation({ .AnimationName = "Trap",  .ImageName = "trap.bmp", .Start = 0, .End = 12,.InterTime=0.3f });
		AnimationRender->CreateAnimation({ .AnimationName = "Start",  .ImageName = "ready.bmp", .Start = 0, .End = 17,.InterTime = 0.1f });
		AnimationRender->CreateAnimation({ .AnimationName = "Live",  .ImageName = "Live.bmp", .Start = 0, .End = 4,.InterTime = 0.1f });
		AnimationRender->CreateAnimation({ .AnimationName = "Die",  .ImageName = "die.bmp", .Start = 0, .End = 12,.InterTime = 0.2f });
	}
	
	StateValue = PlayerState::START;
	//ChangeState(PlayerState::IDLE);
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
		if (Block::OwnerBlock->GetTileMap()->GetTile(static_cast<int>(BlockType::Block1), CollisionDiretion)->GetFrame() == 1)
		{
			// 밀었는데 
			WoodStartPos = CollisionDiretion;
			WoodDir = MoveDir;
			WoodRender = Block::OwnerBlock->GetTileMap()->GetTile(static_cast<int>(BlockType::Block1), CollisionDiretion);
			ChangeState(PlayerState::PUSH);
		}
		return false;
	}
	Bomb* FindBomb = Bomb::GetBomb(CollisionDiretion);
	if (nullptr != FindBomb)
	{		
			// 나의 미래의 위치에도 폭탄이 있다면 안된다.
			Bomb* NextBomb = Bomb::GetBomb(GetPos() + MoveDir * 40.0f);
			if (nullptr != NextBomb)
			{
				if (true == KickOn)
				{
					NextBomb->BombDir = MoveDir;
					NextBomb->ChangeState(BombState::KICK);
				}
				return false;
			}

			PlayerCollisionData BombData;
			BombData.Position = FindBomb->GetPos();
			BombData.Scale = FindBomb->AnimationRender->GetScale();
			if (true == CollisionRectToRect(BombData, NewPlayerCollisionData)) {

				return true;
			}
	      return false;
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
					BombCountUp();
				}
				if (NewItemType == ItemType::Skate) {
					SpeedUp();
				}
				if (NewItemType == ItemType::PowerMax) 
				{
					for (int i = 0; i < 7; i++)
					{
						BombPowerCountUp();
					}
				}
				if (NewItemType == ItemType::Shop)
				{
					BackGround::MainBackGround->ActiveItemRender->On();
				}
				if (NewItemType == ItemType::Kick)
				{
					KickOn = true;
				}
				ColActor->Death();
			}
		}
	}
	std::vector<GameEngineCollision*> Collision2;
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(CrazyRenderOrder::BombPower), .TargetColType = CT_Rect , .ThisColType = CT_Rect }, Collision2)) {

		for (size_t i = 0; i < Collision2.size(); i++)
		{
			BackGround::MainBackGround->ActiveOnOffSwicth();
			AnimationRender->ChangeAnimation("Trap");
		}
	}
	float4 BombPos = GetPos();
	BombPos.y += 10.f;
	if (GameEngineInput::IsDown("Space") && BombCount > 0 && nullptr == Bomb::GetBomb(BombPos))
	{
		
		Bomb* NewBomb = GetLevel()->CreateActor<Bomb>();
	
		NewBomb->InitBomb(Block::OwnerBlock->GetTileMap()->ConvertIndexToTilePosition(BombPos));

		
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
	
	std::string Text = "PlayerPos : ";
	Text += GetPos().ToString();
	GameEngineLevel::DebugTextPush(Text);
	
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

void Player::SpeedUp()
{
	MoveSpeed += 20.f;
	if (MoveSpeed >= 220.f) {
		MoveSpeed = 220.f;
	}
}

void Player::BombCountUp()
{
	BombCount += 1;
	if (BombCount >= 7) {
		BombCount = 7;
	}
}
void Player::BombPowerCountUp()
{
	BombPowerCount += 1;
	if (BombPowerCount >= 7) 
	{
		BombPowerCount = 7;
	}
}
