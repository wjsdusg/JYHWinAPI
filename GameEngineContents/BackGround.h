#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Player;
class BackGround : public GameEngineActor
{
	friend Player;
public:
	// constrcuter destructer
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	static BackGround* MainBackGround;
protected:
	void Start() override;

private:
	
	GameEngineRender* ActiveItemRender = nullptr;

	void ActiveOnOffSwicth();
};

