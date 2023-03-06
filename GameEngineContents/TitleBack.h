#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class TitleBack : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleBack();
	~TitleBack();

	// delete Function
	TitleBack(const TitleBack& _Other) = delete;
	TitleBack(TitleBack&& _Other) noexcept = delete;
	TitleBack& operator=(const TitleBack& _Other) = delete;
	TitleBack& operator=(TitleBack&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	GameEngineRender* Render = nullptr;
	GameEngineRender* NewAnimation = nullptr;
	float ActTime = 0.f;
	bool IsAct = false;
};

