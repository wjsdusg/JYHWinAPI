#include <Windows.h>
#include <GameEngineContents/StudyGameCore.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineRandom.h>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	int a=GameEngineRandom::MainRandom.RandomInt(0, 3);
	int b= GameEngineRandom::MainRandom.RandomInt(0, 3);
	StudyGameCore::GetInst().CoreStart(hInstance);
	return 1;
}