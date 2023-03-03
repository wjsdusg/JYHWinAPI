#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MonsterMap : public GameEngineActor
{
public:
	// constrcuter destructer
	MonsterMap();
	~MonsterMap();

	// delete Function
	MonsterMap(const MonsterMap& _Other) = delete;
	MonsterMap(MonsterMap&& _Other) noexcept = delete;
	MonsterMap& operator=(const MonsterMap& _Other) = delete;
	MonsterMap& operator=(MonsterMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

