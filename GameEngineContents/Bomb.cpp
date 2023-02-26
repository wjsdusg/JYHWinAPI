#include "Bomb.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"
#include "BombPower.h"
#include "Block.h"
#include <GameEngineCore/GameEngineTileMap.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsValue.h"

std::vector<std::vector<Bomb*>> Bomb::AllBomb;

Bomb::Bomb()
{
}

Bomb::~Bomb()
{
	float4 pos = GetPos();
	float4 Index = Block::OwnerBlock->GetTileMap()->GetIndex(GetPos());
	AllBomb[Index.iy()][Index.ix()] = nullptr;
}

void Bomb::BombMapInit()
{
	int _X = ContentsValue::XTileNum;
	int _Y = ContentsValue::YTileNum;

	AllBomb.resize(_Y);
	for (size_t y = 0; y < AllBomb.size(); y++)
	{
		AllBomb[y].resize(_X);

		for (size_t x = 0; x < AllBomb[y].size(); x++)
		{
			AllBomb[y][x] = nullptr;
		}
	}
}

bool Bomb::IsBomb(const float4& _Pos)
{
	float4 Index = Block::OwnerBlock->GetTileMap()->GetIndex(_Pos);
	return IsBomb(Index.ix(), Index.iy());
}

bool Bomb::IsBomb(int _X, int _Y)
{
	return AllBomb[_Y][_X] != nullptr;
}


void Bomb::Start() {

	BodyCollision = CreateCollision(CrazyRenderOrder::Bomb);
	BodyCollision->SetScale(float4(40, 40));

	BlockCollision = CreateCollision(CrazyRenderOrder::BombtoPlayer);

	AnimationRender = CreateRender(CrazyRenderOrder::Item);
	AnimationRender->SetPosition(GetPos());
	AnimationRender->CreateAnimation({ .AnimationName = "Bomb",.ImageName = "Bomb.BMP",.Start = 0,.End = 3,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "BombEnd",.ImageName = "unit_bombwaterAll.BMP",.Start = 4,.End = 7,.InterTime = 0.17f });
	AnimationRender->SetScale(float4{ 40.0f,40.0f });
	AnimationRender->ChangeAnimation("Bomb");
}

void Bomb::Update(float _DeltaTime)
{

	Playerbombcount = Player::MainPlayer->BombCountptr;



	//if (Player::MainPlayer->BodyCollision->GetPosition() - this->GetPos() > float4{ 20.f })
	if (GetLiveTime() >= 4.5 || true == BombDeath)
	{

		AnimationRender->ChangeAnimation("BombEnd");


		BombPower* NewBombPower = GetLevel()->CreateActor<BombPower>();

		NewBombPower->SetPos(GetPos());

		/*PlusPos *=num;
		NewBombPower->PlusPos = PlusPos;*/
		if (BombAnimationCheck == true) {
			NewBombPower->BombAnimation();
		}


		BombAnimationCheck = false;
		//PlusPos *= num;

		num++;

		if (true == BombDeath) {
			*Playerbombcount += 1;
			Death();
		}



	}

	if (GetLiveTime() >= 5.0)
	{

		*Playerbombcount += 1;
		Death();

	}

}

void Bomb::InitBomb(float4 _Pos)
{
	SetPos(_Pos);

	float4 Index = Block::OwnerBlock->GetTileMap()->GetIndex(_Pos);
	AllBomb[Index.iy()][Index.ix()] = this;
}