#pragma once

#include "Monster.h"


// Ό³Έν :


class IceMonster : public Monster
{
public:
	// constrcuter destructer
	IceMonster();
	~IceMonster();

	// delete Function
	IceMonster(const IceMonster& _Other) = delete;
	IceMonster(IceMonster&& _Other) noexcept = delete;
	IceMonster& operator=(const IceMonster& _Other) = delete;
	IceMonster& operator=(IceMonster&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	static int num;

	float4 MonstersPos[3] = { float4{600,200} ,float4{500,300},float4{400,400} };
	Block* Block = Block::OwnerBlock;

};

