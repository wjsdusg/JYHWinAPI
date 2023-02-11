#pragma once
#include <GameEngineCore/GameEngineCore.h>


class StudyGameCore : public GameEngineCore
{
public:
	
	StudyGameCore(const StudyGameCore& _Other) = delete;
	StudyGameCore(StudyGameCore&& _Other) noexcept = delete;
	StudyGameCore& operator=(const StudyGameCore& _Other) = delete;
	StudyGameCore& operator=(StudyGameCore&& _Other) noexcept = delete;

	static StudyGameCore& GetInst()
	{
		return Core;
	}



protected:
	void Start() override;
	void Update() override;
	void End() override;


private:
	
	StudyGameCore();
	~StudyGameCore();


	static StudyGameCore Core;

};

