#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTileMap;
class Player;
class Block : public GameEngineActor
{
	friend Player;
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
	int XTileNum = MapSize.x / TileSize;
	int YTileNum = MapSize.y / TileSize;
	GameEngineTileMap* NewGameEngineTileMap;
	static Block* OwnerBlock;
};
