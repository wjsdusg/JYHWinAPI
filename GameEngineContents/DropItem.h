#pragma once
#include <GameEngineCore/GameEngineActor.h>


// Ό³Έν :
class Player;
class BombPower;
class DropItem : public GameEngineActor
{
	friend Player;
	friend BombPower;
public:

	DropItem();
	~DropItem();

	// delete Function
	DropItem(const DropItem& _Other) = delete;
	DropItem(DropItem&& _Other) noexcept = delete;
	DropItem& operator=(const DropItem& _Other) = delete;
	DropItem& operator=(DropItem&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

private:
	
	


};

