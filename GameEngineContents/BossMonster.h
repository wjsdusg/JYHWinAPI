#pragma once

#include "Monster.h"


// Ό³Έν :


class BossMonster : public Monster
{
public:
	// constrcuter destructer
	BossMonster();
	~BossMonster();

	// delete Function
	BossMonster(const BossMonster& _Other) = delete;
	BossMonster(BossMonster&& _Other) noexcept = delete;
	BossMonster& operator=(const BossMonster& _Other) = delete;
	BossMonster& operator=(BossMonster&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	bool Movecalculation(float4 _Pos) override;
private:
	
	Block* Block = Block::OwnerBlock;
	
};

