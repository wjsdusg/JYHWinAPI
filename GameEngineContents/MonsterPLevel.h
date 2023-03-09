#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>
// Ό³Έν :
class MonsterPLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MonsterPLevel();
	~MonsterPLevel();

	// delete Function
	MonsterPLevel(const MonsterPLevel& _Other) = delete;
	MonsterPLevel(MonsterPLevel&& _Other) noexcept = delete;
	MonsterPLevel& operator=(const MonsterPLevel& _Other) = delete;
	MonsterPLevel& operator=(MonsterPLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

private:
	GameEngineSoundPlayer SoundPlayerBGM;
};

