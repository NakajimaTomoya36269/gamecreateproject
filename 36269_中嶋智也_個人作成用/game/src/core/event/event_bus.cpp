#include "event_bus.h"

CEventBus& CEventBus::GetInstance(void)
{
	static CEventBus instance;

	return instance;
}

CEventBus::CEventBus(void)
{
}
