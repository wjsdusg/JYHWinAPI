#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

// ???? :
class Player;

class DropItem : public GameEngineActor
{
	friend Player;

public:

	DropItem();
	~DropItem();

	// delete Function
	DropItem(const DropItem& _Other) = delete;
	DropItem(DropItem&& _Other) noexcept = delete;
	DropItem& operator=(const DropItem& _Other) = delete;
	DropItem& operator=(DropItem&& _Other) noexcept = delete;
	ItemType GetItemType();
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

private:
	
	


};

