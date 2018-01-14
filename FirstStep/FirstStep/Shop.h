#pragma once
#include "Base.h"
#include "place.h"
class Shoper
{
	NAME(Name);
	ADD_MEM(string, Word);
	Shoper() { SetWord("你好，陌生人！"); }
};
class Shop : public Place
{
	NAME(Name);
	ADD_MEM(Shoper, Waiter);
	Shop(string name) : Place(name)
	{
		auto eventManager = GetEventManager();
		SetEventName("商店交易");
		ShopEvent *event = new ShopEvent(GetEventName().c_str());
		//	event->initial(GetpObj(), GetpTime());
		eventManager->AddEvents(event);
	}
};