#pragma once

#include "DropItem.h"

// ���� :
class Player;

class BombItem : public DropItem
{
	friend Player;
	
public:

	BombItem();
	~BombItem();

	// delete Function
	BombItem(const BombItem& _Other) = delete;
	BombItem(BombItem&& _Other) noexcept = delete;
	BombItem& operator=(const BombItem& _Other) = delete;
	BombItem& operator=(BombItem&& _Other) noexcept = delete;

protected:
	void Start() override;
	//void Update(float _DeltaTime) override;

private:
	


};

