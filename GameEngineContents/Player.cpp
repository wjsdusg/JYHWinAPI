#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsEnums.h"

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

	SetMove(GameEngineWindow::GetScreenSize().half());


	if (false == GameEngineInput::IsKey("LeftMove"))
	{
		GameEngineInput::CreateKey("LeftMove", 'A');
		GameEngineInput::CreateKey("RightMove", 'D');
		GameEngineInput::CreateKey("DownMove", 'S');
		GameEngineInput::CreateKey("UpMove", 'W');
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
	
		// ColMap.BMP 이걸 변수로하면 
	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("Camp_ColMap.BMP");
	if (nullptr == ColImage)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}

	// 내 미래의 위치는 여기인데/.

	bool Check = true;
	//float4 NextPos = GetPos() + MoveDir * _DeltaTime;

	if (RGB(0, 0, 0) == ColImage->GetPixelColor(_Pos, RGB(0, 0, 0)))
	{
		Check = false;
		
	}

	return Check;
	
}

void Player::Update(float _DeltaTime) 
{
	UpdateState(_DeltaTime);
	
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