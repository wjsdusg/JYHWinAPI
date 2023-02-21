#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class BombState
{
	IDLE,
	Pung,
};

// Ό³Έν :
class Player;
class BombPower;
class Bomb : public GameEngineActor
{
	friend Player;
	friend BombPower;
public:
	
	Bomb();
	~Bomb();

	// delete Function
	Bomb(const Bomb& _Other) = delete;
	Bomb(Bomb&& _Other) noexcept = delete;
	Bomb& operator=(const Bomb& _Other) = delete;
	Bomb& operator=(Bomb&& _Other) noexcept = delete;
	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
private:
	
	int num = 1;
	int* Playerbombcount=nullptr;
	int BombPowerCount = 2;
	int PlusPos = 40;
	int* PlusPosPtr = &PlusPos;
	GameEngineRender* AnimationRender = nullptr;	
	bool BombAnimationCheck = true;
	
};

