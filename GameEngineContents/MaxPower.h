#pragma once

#include "DropItem.h"

// Ό³Έν :
class Player;
class BombPower;
class MaxPower : public DropItem
{
	friend Player;
	friend BombPower;
public:

	MaxPower();
	~MaxPower();

	// delete Function
	MaxPower(const MaxPower& _Other) = delete;
	MaxPower(MaxPower&& _Other) noexcept = delete;
	MaxPower& operator=(const MaxPower& _Other) = delete;
	MaxPower& operator=(MaxPower&& _Other) noexcept = delete;

protected:
	void Start() override;
	//void Update(float _DeltaTime) override;

private:



};

