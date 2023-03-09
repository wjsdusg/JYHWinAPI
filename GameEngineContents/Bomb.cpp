#include "Bomb.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>
#include "ContentsEnums.h"
#include "Player.h"

#include "Block.h"
#include <GameEngineCore/GameEngineTileMap.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsValue.h"
#include <GameEngineCore/GameEngineTileMap.h>
#include "DropItem.h"
std::vector<std::vector<Bomb*>> Bomb::AllBomb;

float4 ArrBombDir[4] = { float4::Up,float4::Down, float4::Right,float4::Left };


Bomb::Bomb()
{
}

Bomb::~Bomb()
{
	
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
	if (0 > Index.ix() || 0 > Index.iy()) {
		return true;
	}
	return IsBomb(Index.ix(), Index.iy());
}

bool Bomb::IsBomb(int _X, int _Y)
{
	return AllBomb[_Y][_X] != nullptr;
}

Bomb* Bomb::GetBomb(const float4& _Pos)
{
	float4 Index = Block::OwnerBlock->GetTileMap()->GetIndex(_Pos);
	return GetBomb(Index.ix(), Index.iy());
}

Bomb* Bomb::GetBomb(int _X, int _Y)
{
	/*if (_Y >= 13) {
		return nullptr;
	}*/
	return AllBomb[_Y][_X];
}

bool Bomb::IsBombExceptMe(Bomb* _BombPtr, const float4& _Pos) {
	

	float4 NewIndexPos=Block::OwnerBlock->GetTileMap()->GetIndex(_Pos);
	if (_BombPtr->Index == NewIndexPos) {
		return true;
	}
	else {
		return false;
	}
	
	
}

void Bomb::Start() {

	BodyCollision = CreateCollision(CrazyRenderOrder::Bomb);
	BodyCollision->SetScale(float4(40, 40));

	BlockCollision = CreateCollision(CrazyRenderOrder::BombtoPlayer);

	AnimationRender = CreateRender(CrazyRenderOrder::Item);
	AnimationRender->SetPosition(GetPos());
	AnimationRender->CreateAnimation({ .AnimationName = "Bomb",.ImageName = "Bomb.BMP",.Start = 0,.End = 3,.InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "BombEnd",.ImageName = "unit_bombwaterAll.BMP",.Start = 4,.End = 7,.InterTime = 0.2f });
	AnimationRender->SetScale(float4{ 40.0f,40.0f });
	AnimationRender->ChangeAnimation("Bomb");

	Playerbombcount = Player::MainPlayer->BombCountptr;
	
}

void Bomb::Update(float _DeltaTime)
{
	
	UpdateState(_DeltaTime);
	
}

void Bomb::InitBomb(float4 _Pos)
{
	SetPos(_Pos);

	Index = Block::OwnerBlock->GetTileMap()->GetIndex(_Pos);
	AllBomb[Index.iy()][Index.ix()] = this;
}

void Bomb::ChangeState(BombState _State)
{

	BombState NextState = _State;
	NewBombState = NextState;
	switch (NextState)
	{
	case BombState::KICK:
		KickStart();
	default:
		break;
	}
}

void Bomb::UpdateState(float _Time)
{
	switch (NewBombState)
	{
	case BombState::IDLE:
		IdleUpdate(_Time);
		break;
	case BombState::FIRE:
		FireUpdate(_Time);
		break;
	case BombState::KICK:
		KickUpdate(_Time);
		break;
	default:
		break;
	}
	
}

void Bomb::IdleUpdate(float _Time)
{
	TargetPos = GetPos();
	BombIdleTime += _Time;
	if (Block::OwnerBlock->NewGameEngineTileMap->ConvertIndexToTilePosition(GetPos()) == Block::OwnerBlock->NewGameEngineTileMap->ConvertIndexToTilePosition(2, 6))
	{
		GameEngineResources::GetInst().SoundPlay("wave.wav");
		NewBombState = BombState::FIRE;
	}
	if (Block::OwnerBlock->NewGameEngineTileMap->ConvertIndexToTilePosition(GetPos()) == Block::OwnerBlock->NewGameEngineTileMap->ConvertIndexToTilePosition(12, 6))
	{
		GameEngineResources::GetInst().SoundPlay("wave.wav");
		NewBombState = BombState::FIRE;
	}
	if (4.3f < BombIdleTime)
	{
		GameEngineResources::GetInst().SoundPlay("wave.wav");
		NewBombState = BombState::FIRE;
	}
}
void Bomb::FireUpdate(float _Time)
{
	
	AnimationRender->ChangeAnimation("BombEnd");
	AnimationRender->SetScale(float4{ 40,40 });
	ActTime += _Time;
	BodyCollision->SetOrder(static_cast<int>(CrazyRenderOrder::BombPower));
	if (nullptr != Block::OwnerBlock->NewGameEngineTileMap->GetTile(static_cast<int>(BlockType::TownBush), GetPos()))
	{
		if (true == Block::OwnerBlock->NewGameEngineTileMap->GetTile(static_cast<int>(BlockType::TownBush), GetPos())->IsUpdate())
		{
			Block::OwnerBlock->NewGameEngineTileMap->GetTile(static_cast<int>(BlockType::TownBush), GetPos())->Death();
			Block::OwnerBlock->NewGameEngineTileMap->RemoveTile(static_cast<int>(BlockType::TownBush), GetPos());

		}
	}
	

	if (true == Cycle) {
		for (size_t i = 0; i < 4; i++)
		{
			for (int bombPowerIndex = 1; bombPowerIndex <= Player::MainPlayer->BombPowerCount; bombPowerIndex++) {

				float4 CheckPos = GetPos() + (ArrBombDir[i] * 40.0f * static_cast<float>(bombPowerIndex));

				if (true == Block::OwnerBlock->IsBlock(CheckPos))
				{					
					if (true == Block::OwnerBlock->NewGameEngineTileMap->GetTile(static_cast<int>(BlockType::TownBush), CheckPos)->IsUpdate()) {
						Block::OwnerBlock->NewGameEngineTileMap->GetTile(static_cast<int>(BlockType::TownBush), CheckPos)->Death();
						Block::OwnerBlock->NewGameEngineTileMap->RemoveTile(static_cast<int>(BlockType::TownBush), CheckPos);						
					}
					if (true == Block::OwnerBlock->NewGameEngineTileMap->GetTile(static_cast<int>(BlockType::Block1), CheckPos)->IsUpdate()) {
						Block::OwnerBlock->NewGameEngineTileMap->GetTile(static_cast<int>(BlockType::Block1), CheckPos)->Death();
						Block::OwnerBlock->NewGameEngineTileMap->RemoveTile(static_cast<int>(BlockType::Block1), CheckPos);
						break;
					}									
				}
				if (true == Block::OwnerBlock->IsMapOut(CheckPos)) {
					break;
				}
				
				GameEngineRender* NewRender = CreateRender(CrazyRenderOrder::Item);
				if (nullptr == NewRender)
				{
					break;
				}
				NewRender->CreateAnimation({ .AnimationName = "BombUpEnd",.ImageName = "unit_bombwaterAll.BMP",.Start = 8,.End = 11,.InterTime = 0.2f });
				NewRender->CreateAnimation({ .AnimationName = "BombUping",.ImageName = "unit_bombwaterAll.BMP",.Start = 24,.End = 27,.InterTime = 0.2f });

				NewRender->CreateAnimation({ .AnimationName = "BombDowning",.ImageName = "unit_bombwaterAll.BMP",.Start = 32,.End = 35,.InterTime = 0.2f });
				NewRender->CreateAnimation({ .AnimationName = "BombDownEnd",.ImageName = "unit_bombwaterAll.BMP",.Start = 16,.End = 19,.InterTime = 0.2f });

				NewRender->CreateAnimation({ .AnimationName = "BombLefting",.ImageName = "unit_bombwaterAll.BMP",.Start = 36,.End = 39,.InterTime = 0.2f });
				NewRender->CreateAnimation({ .AnimationName = "BombLeftEnd",.ImageName = "unit_bombwaterAll.BMP",.Start = 20,.End = 23,.InterTime = 0.2f });

				NewRender->CreateAnimation({ .AnimationName = "BombRighting",.ImageName = "unit_bombwaterAll.BMP",.Start = 28,.End = 31,.InterTime = 0.2f });
				NewRender->CreateAnimation({ .AnimationName = "BombRightEnd",.ImageName = "unit_bombwaterAll.BMP",.Start = 12,.End = 15,.InterTime = 0.2f });

				NewRender->SetScale(float4{ 45.0f,45.0f });
								
				if (float4::Up == ArrBombDir[i]) {
					NewRender->ChangeAnimation("BombUping");
					if (bombPowerIndex == Player::MainPlayer->BombPowerCount) {
						NewRender->ChangeAnimation("BombUpEnd");
					}
				}
				else if (float4::Down == ArrBombDir[i]) {
					NewRender->ChangeAnimation("BombDowning");
					if (bombPowerIndex == Player::MainPlayer->BombPowerCount) {
						NewRender->ChangeAnimation("BombDownEnd");
					}
				}
				else if (float4::Right == ArrBombDir[i]) {
					NewRender->ChangeAnimation("BombRighting");
					if (bombPowerIndex == Player::MainPlayer->BombPowerCount) {
						NewRender->ChangeAnimation("BombRightEnd");
					}
				}
				else if (float4::Left == ArrBombDir[i]) {
					NewRender->ChangeAnimation("BombLefting");
					if (bombPowerIndex == Player::MainPlayer->BombPowerCount) {
						NewRender->ChangeAnimation("BombLeftEnd");
					}
				}
				
				NewRender->SetPosition(ArrBombDir[i] * 40.0f * static_cast<float>(bombPowerIndex));

				GameEngineCollision* NewBodyCollision = CreateCollision(CrazyRenderOrder::BombPower);
				NewBodyCollision->SetScale(float4(20, 20));
				NewBodyCollision->SetPosition(ArrBombDir[i] * 40.0f * static_cast<float>(bombPowerIndex));
				std::vector<GameEngineCollision*> Collision;
				if (true == NewBodyCollision->Collision({ .TargetGroup = static_cast<int>(CrazyRenderOrder::Bomb) }, Collision))
				{
					for (size_t i = 0; i < Collision.size(); i++)
					{
						GameEngineActor* ColActor = Collision[i]->GetActor();
						Bomb* Bombptr = dynamic_cast<Bomb*>(ColActor);
						if (Bombptr->NewBombState == BombState::KICK)
						{
							return;
						}
						Bombptr->NewBombState = BombState::FIRE;
					}

				}

				std::vector<GameEngineCollision*> Collision2;
				if (true == NewBodyCollision->Collision({ .TargetGroup = static_cast<int>(CrazyRenderOrder::DropItem),.TargetColType = CT_Point , .ThisColType = CT_CirCle }, Collision))
				{
					for (size_t i = 0; i < Collision.size(); i++) 
					{
						GameEngineActor* ColActor = Collision[i]->GetActor();
						DropItem* DropItemptr = dynamic_cast<DropItem*>(ColActor);
						if (nullptr != Block::OwnerBlock->NewGameEngineTileMap->GetTile(static_cast<int>(BlockType::Block1), DropItemptr->GetPos()))
						{
							continue;
						}
						DropItemptr->Death();
					}

				}

			}
		
		}
		Cycle = false;
	}

	if (0.7f < ActTime) {
		*Playerbombcount += 1;
		if (nullptr != Block::OwnerBlock)
		{

			float4 Index = Block::OwnerBlock->GetTileMap()->GetIndex(GetPos());
			AllBomb[Index.iy()][Index.ix()] = nullptr;

		}
		Death();

	}
}

void Bomb::BombTileIndexChange(float4 _CurIndex, float4 _TargetIndex)
{
	Bomb* NewBomb = nullptr;
	
	float4 CurIndex = Block::OwnerBlock->NewGameEngineTileMap->GetIndex(_CurIndex);
	float4 TargetIndex = Block::OwnerBlock->NewGameEngineTileMap->GetIndex(_TargetIndex);
	if (CurIndex.x < 0 || CurIndex.y < 0 || TargetIndex.x < 0 || TargetIndex.y < 0)
	{
		return;
	}
     NewBomb = AllBomb[CurIndex.iy()][CurIndex.ix()];
	AllBomb[CurIndex.iy()][CurIndex.ix()] = AllBomb[TargetIndex.iy()][TargetIndex.ix()];
	AllBomb[TargetIndex.iy()][TargetIndex.ix()] = NewBomb;
}

void Bomb::KickStart() {
	//방향<- 플레이어가 줌
	//어디까지 갈수있는지 목표거리계산
	//방향 곱하기 40씩한다.
	//이즈블럭이나 맵아웃,다른 폭탄이 있으면 멈춘다 그게 목표거리
	num2++;
	StartPos = GetPos();

	float4 NextPos = TargetPos + (BombDir * ContentsValue::TileSize);
	
	if (Block::OwnerBlock->NewGameEngineTileMap->ConvertIndexToTilePosition(TargetPos) == Block::OwnerBlock->NewGameEngineTileMap->ConvertIndexToTilePosition(12, 6))
	{
		BombTileIndexChange(GetPos(), TargetPos);
		return;
	}

	if (true == Block::OwnerBlock->IsMapOut(NextPos))
	{
		BombTileIndexChange(GetPos(), TargetPos);
		return;
	}
	if (true == IsBomb(NextPos))
	{
		BombTileIndexChange(GetPos(), TargetPos);
		return;
	}
	if (true == Block::OwnerBlock->IsBlock(NextPos))
	{
		if (true==Block::OwnerBlock->NewGameEngineTileMap->GetTile(static_cast<int>(BlockType::TownBush), NextPos)->IsUpdate())
		{
			TargetPos = NextPos;
			KickStart();
			return;
		}
		BombTileIndexChange(GetPos(), TargetPos);
		return;
	}
	TargetPos = NextPos;
	KickStart();
}

void Bomb::KickUpdate(float _Time)
{
	BombMoveTime += _Time;
	
	float4 Pos = float4::LerpClamp(StartPos, TargetPos, BombMoveTime*static_cast<float>((10/num2)));
	SetPos(Pos);
	
	if (Pos == TargetPos)
	{
		BombIdleTime = 0.f;
		NewBombState = BombState::IDLE;
	}
}