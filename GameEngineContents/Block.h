#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTileMap;
class Player;
class BombPower;
class Block : public GameEngineActor
{
	friend Player;
	friend BombPower;
public:
	// constrcuter destructer
	Block();
	~Block();

	// delete Function
	Block(const Block& _Other) = delete;
	Block(Block&& _Other) noexcept = delete;
	Block& operator=(const Block& _Other) = delete;
	Block& operator=(Block&& _Other) noexcept = delete;
	bool IsBlock(float4 _Pos);
protected:
	void Start() override;

private:
	float4 MapSize = { 600,520 };
	int TileSize = 40;
	int XTileNum = static_cast<int>(MapSize.x / TileSize);
	int YTileNum = static_cast<int>(MapSize.y / TileSize);
	GameEngineTileMap* NewGameEngineTileMap=nullptr;
	static Block* OwnerBlock;
};
