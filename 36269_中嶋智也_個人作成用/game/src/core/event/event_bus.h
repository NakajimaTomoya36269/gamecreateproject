#pragma once

#include <map>
#include <vector>
#include <typeindex>
#include <functional>

class CEventBus
{
public:
	// インスタンスの取得
	static CEventBus& GetInstance(void);

	// =============================
	// Subscribe（登録）
	// =============================
	template<typename EventType, typename Func>
	void Subscribe(Func&& func)
	{
		std::type_index index(typeid(EventType));

		m_Subscribers[index].push_back(
			[f = std::forward<Func>(func)](const void* event)
			{
				f(*static_cast<const EventType*>(event));
			}
		);
	}

	// =============================
	// Publish（通知）
	// =============================
	template<typename EventType>
	void Publish(const EventType& event)
	{
		std::type_index index(typeid(EventType));

		if (m_Subscribers.find(index) == m_Subscribers.end())
			return;

		std::vector<std::function<void(const void*)>>& list
			= m_Subscribers[index];

		for (size_t i = 0; i < list.size(); i++)
		{
			list[i](&event);
		}
	}

private:
	// コンストラクタ
	CEventBus(void);

	// コピーコンストラクタ
	CEventBus(const CEventBus& rhs) = delete;

	// デストラクタ
	~CEventBus(void) = default;

	// 代入演算子
	CEventBus operator=(const CEventBus& rhs) = delete;

	std::map<std::type_index, std::vector<std::function<void(const void*)>>>
		m_Subscribers;
};