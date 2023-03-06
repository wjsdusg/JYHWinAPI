#include "BombPower.h"
#include <GameEngineCore/GameEngineTileMap.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"
#include "Player.h"
#include <vector>
#include "Block.h"
#include "Bomb.h"
float4 ArrBombDir[4] = {float4::Up,float4::Down, float4::Right,float4::Left};

BombPower::BombPower()
{
	

}

BombPower::~BombPower()
{
}



void BombPower::Start() {

	
	
	
	_FrameTime.push_back(0.3f);
	_FrameTime.push_back(0.1f);
	_FrameTime.push_back(0.1f);
	_FrameTime.push_back(0.1f);
		

}

void BombPower::Update(float _DelataTime) {
	

	if (GetLiveTime() >= 0.5f) {
	Death();
	}
		
	
}

void BombPower::BombAnimation() {
	bool check[4] = { false };
	for (int bombPowerIndex = 1; bombPowerIndex <= Player::MainPlayer->BombPowerCount; bombPowerIndex++) {

		for (size_t i = 0; i < 4; i++)
		{
			
			float4 CheckPos = GetPos() + (ArrBombDir[i] * 40.0f * static_cast<float>(bombPowerIndex));

			if (true == Block::OwnerBlock->IsBlock(CheckPos))
			{
				if (check[i] == false) {
					Block::OwnerBlock->NewGameEngineTileMap->GetTile(0, CheckPos)->Death();
					
				}
				check[i] = true;
				continue;
			}
			if (true == Block::OwnerBlock->IsMapOut(CheckPos)) {
				check[i] = true;
				continue;
			}
			if (true == check[i]) {
				continue;
			}

			GameEngineRender* NewRender = CreateRender(CrazyRenderOrder::Item);
			NewRender->CreateAnimation({ .AnimationName = "BombUpEnd",.ImageName = "unit_bombwaterAll.BMP",.Start = 8,.End = 11,.FrameTime = _FrameTime });
			NewRender->CreateAnimation({ .AnimationName = "BombUping",.ImageName = "unit_bombwaterAll.BMP",.Start = 24,.End = 27,.FrameTime = _FrameTime });
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
					Bombptr->BobmDie();
				}
				
			}
		}
	}
}