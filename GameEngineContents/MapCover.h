#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MapCover : public GameEngineActor
{
public:
	// constrcuter destructer
	MapCover();
	~MapCover();

	// delete Function
	MapCover(const MapCover& _Other) = delete;
	MapCover(MapCover&& _Other) noexcept = delete;
	MapCover& operator=(const MapCover& _Other) = delete;
	MapCover& operator=(MapCover&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

