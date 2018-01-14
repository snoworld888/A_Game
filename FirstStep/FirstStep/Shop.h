#pragma once
#include "Base.h"
#include "place.h"
class Shoper
{
	NAME(Name);
	ADD_MEM(string, Word);
	Shoper() { SetWord("��ã�İ���ˣ�"); }
};
class Shop : public Place
{
	NAME(Name);
	ADD_MEM(Shoper, Waiter);
	Shop(string name) : Place(name)
	{
		auto eventManager = GetEventManager();
		SetEventName("�̵꽻��");
		ShopEvent *event = new ShopEvent(GetEventName().c_str());
		//	event->initial(GetpObj(), GetpTime());
		eventManager->AddEvents(event);
	}
};