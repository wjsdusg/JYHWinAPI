#pragma once
#include <GameEngineCore/GameEngineActor.h>
enum class BombState
{
	IDLE,
	Pung,
};

// ���� :
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
	int BombPowerCount = 1;
	int* BombPowerCountPtr = &BombPowerCount;
	GameEngineRender* AnimationRender = nullptr;	
	GameEngineRender* BPAnimationRender = nullptr;
	
};

