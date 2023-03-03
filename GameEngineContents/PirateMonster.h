#pragma once

#include "Monster.h"
// Ό³Έν :


class PirateMonster : public Monster
{
public:
	// constrcuter destructer
	PirateMonster();
	~PirateMonster();

	// delete Function
	PirateMonster(const PirateMonster& _Other) = delete;
	PirateMonster(PirateMonster&& _Other) noexcept = delete;
	PirateMonster& operator=(const PirateMonster& _Other) = delete;
	PirateMonster& operator=(PirateMonster&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	
};

