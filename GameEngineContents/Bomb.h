#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Bomb : public GameEngineActor
{
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

private:

};

