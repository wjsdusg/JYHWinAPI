#include "Bomb.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

#include "Player.h"

Bomb::Bomb()
{
	Bomb::BombPtr=this;
	
}

Bomb::~Bomb()
{
}
bool Bomb::Check = false;
bool IsCheck(bool _Check) {
	Bomb::Check = _Check;
	return Bomb::Check;
};
void Bomb::Update(float _DeltaTime)
{
	Bomb::UpdateState(_DeltaTime);


}

// GameEngineRender* ¹è¿­·Î