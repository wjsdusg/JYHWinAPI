#pragma once
#include <GameEngineCore/GameEngineActor.h>



// Ό³Έν :
class Player;
class BombPower;

class Bomb : public GameEngineActor
{
	friend Player;
	friend BombPower;

	static std::vector<std::vector<Bomb*>> AllBomb;

public:
	static bool IsBomb(const float4& _Pos);
	static bool IsBomb(int _X, int _Y);
	static void BombMapInit();

public:
	
	Bomb();
	~Bomb();

	// delete Function
	Bomb(const Bomb& _Other) = delete;
	Bomb(Bomb&& _Other) noexcept = delete;
	Bomb& operator=(const Bomb& _Other) = delete;
	Bomb& operator=(Bomb&& _Other) noexcept = delete;
	
	GameEngineCollision* GetBlockCollision() 
	{
		return BlockCollision;
	}

	void InitBomb(float4 _Pos);

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
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineCollision* BlockCollision = nullptr;
	bool BombDeath = false;

	void BobmDie() {
		BombDeath = true;

	}
};

