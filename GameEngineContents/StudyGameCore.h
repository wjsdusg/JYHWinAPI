#pragma once
#include <GameEngineCore/GameEngineCore.h>

// �̷��� Ŭ������ ����� ��� ����ü�� �̱����̶�� �մϴ�.

// ���� :
class StudyGameCore : public GameEngineCore
{
public:
	// delete Function
	StudyGameCore(const StudyGameCore& _Other) = delete;
	StudyGameCore(StudyGameCore&& _Other) noexcept = delete;
	StudyGameCore& operator=(const StudyGameCore& _Other) = delete;
	StudyGameCore& operator=(StudyGameCore&& _Other) noexcept = delete;

	// �̱���
	static StudyGameCore& GetInst()
	{
		return Core;
	}

	// �����ͷ� ����ÿ��� �߰��� ������ �����ϴٴ� ������ �ִ�.
	//static StudyGameCore& Destroy()
	//{
	//	delete Core;
	//}

protected:
	void Start() override;
	void Update() override;
	void End() override;


private:
	// �����ڸ� ����.
	// constrcuter destructer
	StudyGameCore();
	~StudyGameCore();

	// �ڱ⸦ �ڽ��� ������
	// ���α׷��� ��Ʋ� ���� 1���� ��ü�� ���������
	// static StudyGameCore* Core;
	static StudyGameCore Core;

};

