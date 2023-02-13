#pragma once
#include <GameEngineCore/GameEngineActor.h>
enum class BombState
{
	IDLE,
	Pung,
};

// Ό³Έν :
class Player;
class Bomb : public GameEngineActor
{
	friend Player;
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
	static int BombCount;

	static bool BombCheck[10];
	
	float BombActTime = 0.0f;
	
	bool IsLive();
	GameEngineRender* AnimationRender = nullptr;
	
	bool Live = true;
	void UpdateState(float _DeltaTime);
	
	float ActTime = 0.0f;
};

