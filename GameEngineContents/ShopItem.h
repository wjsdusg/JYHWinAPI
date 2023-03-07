#pragma once

#include "DropItem.h"

// Ό³Έν :
class Player;

class ShopItem : public DropItem
{
	friend Player;

public:

	ShopItem();
	~ShopItem();

	// delete Function
	ShopItem(const ShopItem& _Other) = delete;
	ShopItem(ShopItem&& _Other) noexcept = delete;
	ShopItem& operator=(const ShopItem& _Other) = delete;
	ShopItem& operator=(ShopItem&& _Other) noexcept = delete;

protected:
	void Start() override;
	//void Update(float _DeltaTime) override;

private:



};

