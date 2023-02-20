#include "BombPower.h"
#include <GameEngineCore/GameEngineTileMap.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Player.h"
#include <vector>
#include "Block.h"

BombPower::BombPower()
{
	

}

BombPower::~BombPower()
{
}



void BombPower::Start() {

	
	NewGameEngineTileMap = GetLevel()->CreateActor<GameEngineTileMap>();
	NewGameEngineTileMap->SetPos(float4(20, 40));
	NewGameEngineTileMap->CreateTileMap(15, 13, 1, 0, float4{ 40,40 });
	
	_FrameTime.push_back(0.3f);
	_FrameTime.push_back(0.1f);
	_FrameTime.push_back(0.1f);
	_FrameTime.push_back(0.1f);

	for (int i = 1; i <= Player::PBombPower; i++) {

		AnimationRender[0] = CreateRender(CrazyRenderOrder::Item);
		AnimationRender[0]->CreateAnimation({ .AnimationName = "BombUpEnd",.ImageName = "unit_bombwaterAll.BMP",.Start = 8,.End = 11,.FrameTime = _FrameTime });
		AnimationRender[0]->CreateAnimation({ .AnimationName = "BombUping",.ImageName = "unit_bombwaterAll.BMP",.Start = 24,.End = 27,.FrameTime = _FrameTime });
		AnimationRender[0]->SetScale(float4{ 45.0f,45.0f });
		AnimationRender[0]->ChangeAnimation("BombUping");
		if (i == Player::PBombPower) {
			AnimationRender[0]->ChangeAnimation("BombUpEnd");
		}
		else if(i< Player::PBombPower) {
			AnimationRender[0]->ChangeAnimation("BombUping");
		}
		float4 MovePosition0 = float4::Up * static_cast<float>(PlusPos * i);
		MovePosition0 = MovePosition0 + GetPos();

		int a = 0;
		if (Block::OwnerBlock->IsBlock(MovePosition0)) {
			break;
		}
		AnimationRender[0]->SetPosition(MovePosition0);


		AnimationRender[1] = CreateRender(CrazyRenderOrder::Item);
		AnimationRender[1]->CreateAnimation({ .AnimationName = "BombDownEnd",.ImageName = "unit_bombwaterAll.BMP",.Start = 16,.End = 19,.FrameTime = _FrameTime });
		AnimationRender[1]->CreateAnimation({ .AnimationName = "BombDowning",.ImageName = "unit_bombwaterAll.BMP",.Start = 32,.End = 35,.FrameTime = _FrameTime });
		AnimationRender[1]->SetScale(float4{ 45.0f,45.0f });
		AnimationRender[1]->ChangeAnimation("BombDowning");
		if (i == Player::PBombPower) {
			AnimationRender[1]->ChangeAnimation("BombDownEnd");
		}
		else if(i<Player::PBombPower) {
			AnimationRender[1]->ChangeAnimation("BombDowning");
		}
		float4 MovePosition1 = float4::Down * static_cast<float>(PlusPos*i);
		MovePosition1 += GetPos();
		AnimationRender[1]->SetPosition(MovePosition1);

	}
	

}

void BombPower::Update(float _DelataTime) {
	
	
	if (GetLiveTime() >= 0.5f) {
	Death();
	}
		
	
}
