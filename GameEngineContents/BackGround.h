#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>
// Ό³Έν :
class Player;
class Monster;
class BackGround : public GameEngineActor
{
	friend Player;
	friend Monster;
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
	void Update(float _DeltaTime);
private:
	
	GameEngineRender* ActiveItemRender = nullptr;

	void ActiveOnOffSwicth();
	NumberRenderObject NewNumberObject;
	int Value = 59;
	float ActTime = 0.f;

	NumberRenderObject NewNumberObject2;
	int Value2 = 3;
	float ActTime2 = 0.f;

	GameEngineRender* StartRender = nullptr;
	GameEngineRender* WinRender = nullptr;
	GameEngineRender* NewBazzifront = nullptr;
};

