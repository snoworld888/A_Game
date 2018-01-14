#include "System.h"
#include "SystemShop.h"
using namespace std;
map<uint32_t, Obj> g_Objs;
map<uint32_t, ObjFormula> g_Formulas;
map<uint32_t, ResourceCollectInfo> g_ResourceCollectInfos;
map<REQUIRE, string> g_ResourceCollectObjName;
map<REQUIRE, string> g_ResourceName; 
map<uint32_t, uint32_t> g_FormulaNext;
map<uint32_t, uint32_t> g_FormulaNextNeed;
System sys;
SystemShop g_SystemShop;
bool GoodShop::ReciveGood(uint32_t num, uint32_t money, uint32_t playerId, uint32_t objId)
{
	if (!free)
		return false;
	free = false;
	m_good.Num = num;
	m_good.Money = money;
	m_good.OwnerId = playerId;
	m_good.ShopId = m_Id;
	g_SystemShop.GetGoods(objId, m_good);
	return true;
}

bool GoodShop::CancelGood(uint32_t objId, uint32_t &num)
{
	num = m_good.Num;
	return g_SystemShop.CancelGoods(objId, m_good);
}

bool PlayerLive::BuyGood(uint32_t objId, uint32_t money)
{
	if (money > GetMoney())
		return false;
	cout << GetName().c_str() << ":����" << g_Objs.find(objId)->second.GetName().c_str();
	if (!g_SystemShop.BuyGood(objId, money))
	{
		cout << " ʧ��" << endl;
		return false;
	}
	m_Money -= money;
	GetObj(objId, 1);
	cout << " �ɹ�" << endl;
	return true;
}

void PlayerLive::CancelGood(uint32_t objId, uint32_t shopId)
{
	uint32_t num;
	if (m_GoodShops[shopId].CancelGood(objId, num))
	{
		m_ObjsProperty[objId]->num+= num;
		cout << GetName().c_str() << ": ��ȡ��" << m_Objs[objId]->GetName().c_str() <<" - "<<num<< endl;
	}
	else
	{
		cout << GetName().c_str() << ": ��Ʒ���������޷�ȡ��" << endl;
	}
}