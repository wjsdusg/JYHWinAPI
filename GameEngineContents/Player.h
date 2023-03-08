#pragma once
#include <GameEngineCore/GameEngineActor.h>


enum class PlayerState
{
	START,
	IDLE,
	MOVE,
	TRAP,
	LIVE,
	DIE,
	PUSH,

};

enum class PlayerDirection
{
	Up,
	Down,
	Right,
	Left,
	Max

};

class PlayerCollisionData
{
public:
	float4 Position;
	float4 Scale;

	float Left() const
	{
		return Position.x - Scale.hx();
	}
	float Right() const
	{
		return Position.x + Scale.hx();
	}
	float Top() const
	{
		return Position.y - Scale.hy();
	}
	float Bot() const
	{
		return Position.y + Scale.hy();
	}
	float4 LeftPos() const
	{
		float4 _NewPos = Position;
		_NewPos.x -= Scale.hx();
		_NewPos.y += 10;
		return _NewPos;
	}
	float4 RightPos() const
	{
		float4 _NewPos = Position;
		_NewPos.x += Scale.hx();
		_NewPos.y += 10;
		return _NewPos;
	}
	float4 TopPos() const
	{
		float4 _NewPos = Position;
		
		
		return _NewPos;
	}
	float4 DownPos() const
	{
		float4 _NewPos = Position;
		_NewPos.y += Scale.hy();
		_NewPos.y += 10;
		return _NewPos;
	}
};


// 설명 :
class Bomb;
class GameEngineTileMap;
class Player : public GameEngineActor
{
	friend Bomb;
	
public:
	
	static Player* MainPlayer;

	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;
		
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _Time) override;


private:
	
	
	
	
	int StartFrame = 0;
	int* BombCountptr = &BombCount;
	float MoveSpeed = 140.0f;
	int BombCount = 2;
	int BombPowerCount = 7;
	void SpeedUp();
	void BombCountUp();
	void BombPowerCountUp();
	std::string DirString = "Down_";
	PlayerState StateValue = PlayerState::IDLE;
	float4 MoveDir = float4::Zero;

	GameEngineRender* AnimationRender = nullptr;
	
	GameEngineCollision* BodyCollision = nullptr;

	void DirCheck(const std::string_view& _AnimationName);

	// State
	void ChangeState(PlayerState _State);
	void UpdateState(float _Time);

	// FSM 내가 어떤일을 할때 이동하면서 가만히 있을수 없다.
	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _Time);
	void MoveEnd();
	
	void StartUpdate(float _Time);
	void LiveUpdate(float _Time);
	void TrapUpdate(float _Time);
	void DieUpdate(float _Time);
	void PushStart();
	void PushUpdate(float _Time);
	void PushEnd();

	bool Movecalculation(float4 _Pos);
	bool CollisionRectToRect(const PlayerCollisionData& _Left, const PlayerCollisionData& _Right);
	
	
	PlayerCollisionData NewPlayerCollisionData;
	
	PlayerDirection NewPlayerDiretion = PlayerDirection::Down;
	float WaitTime = 0.f;

	float4 CollisionDiretion;
	bool KickOn = false;
	float StartTime = 0.f;
	float LiveTime = 0.f;
	float TrapTime = 0.f;
	float DieTime = 0.f;
	float4 WoodStartPos = { 0,0 };
	float4 WoodTargetPos = { 0,0 };
	float4 WoodDir = { 0,0 };
	float WoodMoveTime = 0.f;
	GameEngineRender* WoodRender = nullptr;
};

