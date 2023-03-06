#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineTileMap.h>
#include "ContentsEnums.h"
#include "Block.h"
// Ό³Έν :

enum class MonsterState
{
	IDLE,
	FIGHT

};
enum class MonsterDirection {
	Up,
	Down,
	Left,
	Right,
	Die,
	Ice,
	Resurrection,
	DieIce,
	Max

};
class Monster : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	GameEngineRender* AnimationRender = nullptr;
	MonsterState NewMonsterState = MonsterState::IDLE;
	void ChangeState(MonsterState _State);
	void UpdateState(float _Time);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void FightStart();
	void FightUpdate(float _Time);
	void FightEnd();
	bool Movecalculation(float4 _Pos);
	float MoveSpeed = 40.f;
	float4 CollisionDiretion = { 0,0 };
	float DieTime = 0.f;
	float IceDieTime = 0.f;
	float UpTime = 0.f;
	bool IsUptime = false;
	MonsterDirection NewMonsterDirection = MonsterDirection::Max;
	GameEngineCollision* BodyCollision = nullptr;
	
};

