#include "Bomb.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineLevel.h>
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
	AnimationRender->CreateAnimation({ .AnimationName = "BombEnd",.ImageName = "unit_bombwaterAll.BMP",.Start = 4,.End = 7,.InterTime = 0.17f });
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

	default:
		break;
	}

}
int num = 0;
void Bomb::IdleUpdate(float _Time)
{
	if (4.3f < GetLiveTime())
	{
		NewBombState = BombState::FIRE;
	}
}
void Bomb::FireUpdate(float _Time)
{
	AnimationRender->ChangeAnimation("BombEnd");

	ActTime += _Time;

	
	if (true == Cycle) {
		for (size_t i = 1; i < 2; i++)
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
				NewRender->CreateAnimation({ .AnimationName = "BombUpEnd",.ImageName = "unit_bombwaterAll.BMP",.Start = 8,.End = 11, });
				NewRender->CreateAnimation({ .AnimationName = "BombUping",.ImageName = "unit_bombwaterAll.BMP",.Start = 24,.End = 27, });
				NewRender->SetScale(float4{ 45.0f,45.0f });
				NewRender->ChangeAnimation("BombUping");
				NewRender->SetPosition(ArrBombDir[i] * 40.0f * static_cast<float>(bombPowerIndex));

				GameEngineCollision* NewBodyCollision = CreateCollision(CrazyRenderOrder::BombPower);
				NewBodyCollision->SetScale(float4(40, 40));
				NewBodyCollision->SetPosition(ArrBombDir[i] * 40.0f * static_cast<float>(bombPowerIndex));
				std::vector<GameEngineCollision*> Collision;
				if (true == NewBodyCollision->Collision({ .TargetGroup = static_cast<int>(CrazyRenderOrder::Bomb) }, Collision)) {
					for (size_t i = 0; i < Collision.size(); i++) {
						GameEngineActor* ColActor = Collision[i]->GetActor();
						Bomb* Bombptr = dynamic_cast<Bomb*>(ColActor);
						Bombptr->NewBombState = BombState::FIRE;
					}

				}

				std::vector<GameEngineCollision*> Collision2;
				if (true == NewBodyCollision->Collision({ .TargetGroup = static_cast<int>(CrazyRenderOrder::DropItem),.TargetColType = CT_Point , .ThisColType = CT_CirCle }, Collision)) {
					for (size_t i = 0; i < Collision.size(); i++) {
						GameEngineActor* ColActor = Collision[i]->GetActor();
						DropItem* DropItemptr = dynamic_cast<DropItem*>(ColActor);
						if (nullptr != Block::OwnerBlock->NewGameEngineTileMap->GetTile(static_cast<int>(BlockType::Block1), DropItemptr->GetPos())) {
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