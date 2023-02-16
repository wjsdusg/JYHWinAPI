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
Player* Player::MainPlayer;

Player::Player() 
{
}

Player::~Player() 
{
}

int Player::BombCount = 6;
int Player::PBombPower = 2;

void Player::Start()
{
	MainPlayer = this;

	SetMove(GameEngineWindow::GetScreenSize().half());


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
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}


	bool Check = true;

	if (RGB(0, 0, 0) == ColImage->GetPixelColor(_Pos, RGB(0, 0, 0)))
	{
		Check = false;
		
	}

	return Check;
	
}

void Player::Update(float _DeltaTime) 
{
	UpdateState(_DeltaTime);
	
	if (GameEngineInput::IsDown("Space")&&BombCount>0) {

		
			Bomb* NewBomb2 = GetLevel()->CreateActor<Bomb>();
			NewBomb2->SetPos(GetPos());
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

	// 디버깅용.
}