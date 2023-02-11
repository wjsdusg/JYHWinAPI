#pragma once
#include <string>
#include <string_view>

class GameEngineObject
{
public:
	
	GameEngineObject();
	virtual ~GameEngineObject();

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	bool IsUpdate()
	{
		//         조건          ?              true 일때                                      :         false 일때
		// 부모가 있다면
		// ((true == ObjectUpdate && false == IsDeath()) && true == Parent->IsUpdate())
		// 내가 켜져있어야하고 true == ObjectUpdate
		// 내가 죽지도 않았어야 한다. false == IsDeath()
		// 부모도 켜져있어야 한다 true == Parent->IsUpdate()

		return nullptr != Parent ? ((true == ObjectUpdate && false == IsDeath()) && true == Parent->IsUpdate()) : (ObjectUpdate && false == IsDeath());

		
	}

	bool IsDeath()
	{
		return nullptr != Parent ? (true == ObjectDeath || Parent->IsDeath()) : (true == ObjectDeath);
	}

	void Death()
	{
		ObjectDeath = true;
	}

	void On()
	{
		ObjectUpdate = true;
	}
	void Off()
	{
		ObjectUpdate = false;
	}

	void OnOffSwtich()
	{
		ObjectUpdate = !ObjectUpdate;
	}

	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	int GetOrder()
	{
		return Order;
	}

	virtual void SetOwner(GameEngineObject* _Parent)
	{
		Parent = _Parent;
	}

	template<typename ConvertType>
	ConvertType* GetOwner()
	{
		return dynamic_cast<ConvertType*>(Parent);
	}

	GameEngineObject* GetOwner()
	{
		return Parent;
	}

	void SetName(const std::string_view& _View)
	{
		Name = _View;
	}

	const std::string& GetName()
	{
		return Name;
	}

	std::string GetNameCopy()
	{
		return Name;
	}

protected:

private:
	int Order;

	GameEngineObject* Parent = nullptr;

	bool ObjectDeath = false;
	bool ObjectUpdate = true;

	std::string Name;

};

