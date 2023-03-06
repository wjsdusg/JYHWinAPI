#pragma once

#include "DropItem.h"

// Ό³Έν :
class Player;

class SpeedItem : public DropItem
{
	friend Player;

public:

	SpeedItem();
	~SpeedItem();

	// delete Function
	SpeedItem(const SpeedItem& _Other) = delete;
	SpeedItem(SpeedItem&& _Other) noexcept = delete;
	SpeedItem& operator=(const SpeedItem& _Other) = delete;
	SpeedItem& operator=(SpeedItem&& _Other) noexcept = delete;

protected:
	void Start() override;
	//void Update(float _DeltaTime) override;

private:



};

