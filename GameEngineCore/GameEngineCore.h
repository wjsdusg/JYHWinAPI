#pragma once
#include <Windows.h>
#include <map>
#include <string_view>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineLevel.h>

class GameEngineLevel;
class GameEngineCore
{
private:

	static void GlobalStart();
	static void GlobalUpdate();
	static void GlobalEnd();

public:
	

	GameEngineCore();
	~GameEngineCore();


	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

	void CoreStart(HINSTANCE _instance);

	void ChangeLevel(const std::string_view& _Name);

	static GameEngineCore* GetInst();

	void DebugSwitch()
	{
		IsDebugValue = !IsDebugValue;
	}

	void SetDebugMode(bool _IsDebug)
	{
		IsDebugValue = _IsDebug;
	}

	bool IsDebug()
	{
		return IsDebugValue;
	}

protected:
	template<typename LevelType>
	void CreateLevel(const std::string_view& _Name)
	{
	
		if (Levels.end() != Levels.find(_Name.data()))
		{
			std::string Name = _Name.data();
			MsgAssert(Name + "�̹� �����ϴ� �̸��� ������ ������� �߽��ϴ�");
			return;
		}

		GameEngineLevel* Level = new LevelType();
		Level->SetName(_Name);
		LevelLoading(Level);
	
		Levels.insert(std::make_pair(_Name.data(), Level));
	}

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;

private:
	
	std::map<std::string, GameEngineLevel*> Levels;

	GameEngineLevel* NextLevel = nullptr;

	GameEngineLevel* MainLevel = nullptr;

	void LevelLoading(GameEngineLevel* _Level);

	bool IsDebugValue = false;

};

