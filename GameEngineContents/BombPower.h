#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/NumberRenderObject.h>
class Bomb;
class BombPower : public GameEngineActor
{
	friend Bomb;
public:

	BombPower();
	~BombPower();

	// delete Function
	BombPower(const BombPower& _Other) = delete;
	BombPower(BombPower&& _Other) noexcept = delete;
	BombPower& operator=(const BombPower& _Other) = delete;
	BombPower& operator=(BombPower&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	int* BombPowerCountPtr = nullptr;
	GameEngineRender* AnimationRender[4] = {};
	float ActTime = 0.0f;

};

