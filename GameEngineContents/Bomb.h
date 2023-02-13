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
	static bool Check;

	static bool IsCheck(bool _Check);
protected:
	void Update(float _DeltaTime) override;

private:
	float BombActTime = 0.0f;
	bool Timer(float _DeltaTime);

	GameEngineRender* AnimationRender = nullptr;

	BombState StateValue = BombState::IDLE;


	void ChangeState(BombState _State);

	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void PungStart();
	void PungUpdate(float _Time);
	void PungEnd();

	void UpdateState(float _DeltaTime);
	Bomb* BombPtr = nullptr;

	

	int Bombnum = 0;

	float ActTime = 0.0f;
};

