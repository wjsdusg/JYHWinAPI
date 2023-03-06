#pragma once
#include <GameEngineCore/GameEngineActor.h>
enum class BombState {
	IDLE,
	FIRE,
	MAX
};


// Ό³Έν :
class Player;

class Monster;
class Bomb : public GameEngineActor
{
	friend Player;

	friend Monster;
	static std::vector<std::vector<Bomb*>> AllBomb;

public:
	static Bomb* GetBomb(const float4& _Pos);
	static Bomb* GetBomb(int _X, int _Y);
	static bool IsBomb(const float4& _Pos);
	static bool IsBomb(int _X, int _Y);
	static void BombMapInit();
	static bool IsBombExceptMe(Bomb* _BombPtr, const float4& _Pos);
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
	float4 Index;
	void BobmDie() {
		BombDeath = true;

	}
	void UpdateState(float _Time);
	void IdleUpdate(float _Time);
	void FireUpdate(float _Time);
	BombState NewBombState = BombState::IDLE;
	float ActTime = 0.f;
	bool Cycle = true;
};

