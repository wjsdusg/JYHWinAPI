#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BombPower.h"

enum class PlayerState
{
	IDLE,
	MOVE,
};

// ���� :
class Bomb;
class Player : public GameEngineActor
{
	friend Bomb;
	friend BombPower;
public:
	static Player* MainPlayer;
	static int BombCount;
	static int PBombPower;
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
	
	
	
	float AccTime = 0.0f;
	int StartFrame = 0;
	int* BombCountptr = &BombCount;
	float MoveSpeed = 200.0f;
	std::string DirString = "Right_";
	PlayerState StateValue = PlayerState::IDLE;
	float4 MoveDir = float4::Zero;

	GameEngineRender* AnimationRender = nullptr;


	void DirCheck(const std::string_view& _AnimationName);

	// State
	void ChangeState(PlayerState _State);
	void UpdateState(float _Time);

	// FSM ���� ����� �Ҷ� �̵��ϸ鼭 ������ ������ ����.
	void IdleStart();
	void IdleUpdate(float _Time);
	void IdleEnd();

	void MoveStart();
	void MoveUpdate(float _Time);
	void MoveEnd();

	bool Movecalculation(float4 _Pos);

};

