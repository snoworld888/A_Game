#pragma once 
#include "obj.h"
#include "System.h"
#include <list>
class PlayerLive;
extern map<uint32_t, Obj> g_Objs;


class SystemShop
{
	map<uint32_t, list<GoodsInfo>*> m_GoodsList;
	vector<PlayerLive*> m_Players;
public:
	SystemShop()
	{
		CreateLists();
	}
	~SystemShop()
	{
		for (auto list : m_GoodsList)
		{
			delete list.second;
		}
		for (auto player : m_Players)
		{
			delete player;
		}
	}
	void AddPlayer(PlayerLive* player)
	{
		m_Players.push_back(player);
	}
	void CreateLists()
	{
		for (auto ojb : g_Objs)
		{
			m_GoodsList[ojb.first] = new list<GoodsInfo>;
		}
	}
	auto FindLess(uint32_t objId, uint32_t money)
	{
		auto size = m_GoodsList[objId]->size();
		auto list = m_GoodsList[objId];
		auto good = list->begin();
		if (money < good->Money)
			return good;
		good = list->end();
		if (money < good->Money)
			return good;
		uint32_t index = size; 
		do
		{
			index /= 2;
			good = list->begin();
			while (index--)
			{
				good++;
			}
		} while (money < good->Money);
	}
	auto FindListPlaceByLessMoney(uint32_t objId, uint32_t money)
	{
		auto list = m_GoodsList[objId];
		for (auto good = list->begin(); good != list->end(); good++)
		{
			if (money < good->Money)
				return good;
		}
		return list->end();
	}
	auto FindListPlaceByEqualMoney(uint32_t objId, uint32_t money)
	{
		auto list = m_GoodsList[objId]; 
		for (auto good = list->begin(); good != list->end(); good++)
		{
			if (money == good->Money)
				return good;
		}
		return list->end();
	}
	auto FindListPlaceByOwner(_List_iterator<_List_val<_List_simple_types<GoodsInfo>>> good,
		uint32_t objId,uint32_t ownerId)
	{ 
		auto list = m_GoodsList[objId];
		for (; good != list->end(); good++)
		{
			if (ownerId == good->OwnerId)
				return good;
		}
		return list->end();
	}
	void GetGoods(uint32_t objId, GoodsInfo& goods)
	{
		m_GoodsList[objId]->insert(FindListPlaceByLessMoney(objId, goods.Money), goods);
	}
	bool CancelGoods(uint32_t objId, GoodsInfo& goods)
	{
		auto goodInd = FindListPlaceByEqualMoney(objId, goods.Money);		
		goodInd = FindListPlaceByOwner(goodInd, objId, goods.OwnerId);
		if (goodInd == m_GoodsList[objId]->end())
			return false;
		goodInd->Num -= goods.Num; 
		return true;
	}
	PlayerLive* GetPlayer(uint32_t id)
	{
		for (auto player : m_Players)
		{
			if (player->GetId() == id)
				return player;
		}
		return NULL;
	}
	bool BuyGood(uint32_t objId, uint32_t money);
};