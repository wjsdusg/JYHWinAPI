#pragma once

#include "DropItem.h"

// Ό³Έν :
class Player;

class KickItem : public DropItem
{
	friend Player;

public:

	KickItem();
	~KickItem();

	// delete Function
	KickItem(const KickItem& _Other) = delete;
	KickItem(KickItem&& _Other) noexcept = delete;
	KickItem& operator=(const KickItem& _Other) = delete;
	KickItem& operator=(KickItem&& _Other) noexcept = delete;

protected:
	void Start() override;
	//void Update(float _DeltaTime) override;

private:



};

