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
	

	int* Playerbombcount=nullptr;
	float BombActTime = 0.0f;
		
	GameEngineRender* AnimationRender = nullptr;	
	
	
};

