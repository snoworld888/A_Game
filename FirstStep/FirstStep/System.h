#pragma once
#include "obj.h"
#include <atomic>
#include <random>

struct ResourceCollectInfo
{
	string Name;
	uint32_t CollectResource;
	uint32_t LimitedStore;
	uint32_t FiveSecondStore;
};

extern map<uint32_t, Obj> g_Objs;
extern map<uint32_t, ObjFormula> g_Formulas;
 
static string g_SpecialObj[] = { "老鼠的牙" , "毒蛇的皮", "野猪的牙" };
static string g_HeadObj[] = { "硬帽" , "铜帽", "铁帽", "鼠牙帽", "硬头盔",
"铜头盔", "铁头盔", "蛇纹头盔" };
extern map<uint32_t, ResourceCollectInfo> g_ResourceCollectInfos;
extern map<REQUIRE, string> g_ResourceCollectObjName;
extern map<REQUIRE, string> g_ResourceName;
static vector<Formula_> g_HeadObjRequire =
{
	{ Formula_(vector<pair<REQUIRE, uint32_t>>{pair<REQUIRE, uint32_t>(REQUIRE::STONE_R, 2)}, vector<FormulaObj>()) },
	{ Formula_(vector<pair<REQUIRE, uint32_t>>{pair<REQUIRE, uint32_t>(REQUIRE::STONE_R, 3)}, vector<FormulaObj>()) },
	{ Formula_(vector<pair<REQUIRE, uint32_t>>{pair<REQUIRE, uint32_t>(REQUIRE::STONE_R, 4)}, vector<FormulaObj>{FormulaObj(100,0,1)}) },
	{ Formula_(vector<pair<REQUIRE, uint32_t>>{pair<REQUIRE, uint32_t>(REQUIRE::STONE_R, 5)}, vector<FormulaObj>{FormulaObj(101,0,1),FormulaObj(1,0,1)}) },
	{ Formula_(vector<pair<REQUIRE, uint32_t>>{pair<REQUIRE, uint32_t>(REQUIRE::STONE_R, 6)}, vector<FormulaObj>{FormulaObj(102,0,1)}) },
	{ Formula_(vector<pair<REQUIRE, uint32_t>>{pair<REQUIRE, uint32_t>(REQUIRE::STONE_R, 7)}, vector<FormulaObj>{FormulaObj(103,0,1)}) },
	{ Formula_(vector<pair<REQUIRE, uint32_t>>{pair<REQUIRE, uint32_t>(REQUIRE::STONE_R, 8)}, vector<FormulaObj>{FormulaObj(104,0,1)}) },
	{ Formula_(vector<pair<REQUIRE, uint32_t>>{pair<REQUIRE, uint32_t>(REQUIRE::STONE_R, 9)}, vector<FormulaObj>{FormulaObj(105,0,1),FormulaObj(2,0,1)}) }
};
static string g_BodyObj[] = { "硬甲" , "铜甲", "铁甲", "鼠牙甲", "硬坚甲",
"铜坚甲", "铁坚甲", "蛇纹坚甲" };
static string g_ArmObj[] = { "硬护腕" , "铜护腕", "铁护腕", "鼠牙护腕", "硬坚护腕",
"铜坚护腕", "铁坚护腕", "蛇纹坚护腕" };
static string g_LegObj[] = { "硬护腿" , "铜护腿", "铁护腿", "鼠牙护腿", "硬坚护腿",
"铜坚护腿", "铁坚护腿", "蛇纹坚护腿" };
static string g_WeaponObj[] = { "短匕首" , "长匕首", "穿甲匕首", "鼠牙匕首",
"硬坚匕首","铜坚匕首", "铁坚匕首", "蛇纹坚匕首" };

extern map<uint32_t, uint32_t> g_FormulaNext;
extern map<uint32_t, uint32_t> g_FormulaNextNeed;



class System
{
private:

	void CreateObj(uint32_t id, uint32_t money, uint32_t size, string name[])
	{
		for (int i = 0; i < size; ++i)
		{
			g_Objs[id++] = Obj(id, name[i], RECOVER, 0, money*id);
		}
	} 
	 
	void CreateFormulas(uint32_t id, uint32_t size, string name[],
		vector<Formula_>& require)
	{
		for (int32_t i = 0; i<size; i++)
		{
			g_Formulas[i] = (ObjFormula(id++, name[i], 1, require[i]));
			g_FormulaNext[i] = i+1;
			g_FormulaNextNeed[i] = i*i *0.001 + i+3;
		}
	}
public:
	void CreateObjs()
	{
		CreateObj(1, 1250, sizeof(g_SpecialObj) / sizeof(string), g_SpecialObj);
		CreateObj(100, 25, sizeof(g_HeadObj) / sizeof(string), g_HeadObj);
		CreateObj(200, 125, sizeof(g_BodyObj) / sizeof(string), g_BodyObj);
		CreateObj(300, 25, sizeof(g_ArmObj) / sizeof(string), g_ArmObj);
		CreateObj(400, 25, sizeof(g_LegObj) / sizeof(string), g_LegObj);
		CreateObj(500, 75, sizeof(g_WeaponObj) / sizeof(string), g_WeaponObj);
	}
	void ShowObjs()
	{
		for (auto obj : g_Objs)
		{
			cout << obj.second.GetName().c_str() << endl;
		}
	}

	void CreateFormulas()
	{
		vector<FormulaObj> formula;
		CreateFormulas(100, sizeof(g_HeadObj) / sizeof(string), g_HeadObj, g_HeadObjRequire);
	}

	void ShowFormulas()
	{
		for (auto formula : g_Formulas)
		{
			cout << formula.second.GetName().c_str() << endl;
			cout << formula.second.m_Formula.m_Require.at(0).first << endl;
		}
	}
	 
	void CreateResourceCollectInfos()
	{
		
		g_ResourceCollectObjName = { { REQUIRE::WOOD_R,"木桶"},{ REQUIRE::STONE_R,"石桶"},
		{ REQUIRE::IRON_R, "铁桶"},{ REQUIRE::FUR_R, "皮桶"} };
		g_ResourceName = { { REQUIRE::WOOD_R,"木头" },{ REQUIRE::STONE_R,"石头" },
		{ REQUIRE::IRON_R, "铁块" },{ REQUIRE::FUR_R, "皮革" } };
		for (int i = 0; i < REQUIRE::R_NUM; i++)
		{
			g_ResourceCollectInfos[i].CollectResource = i;
			g_ResourceCollectInfos[i].LimitedStore = (i+1) * 5;
			g_ResourceCollectInfos[i].FiveSecondStore = (i+1);
			g_ResourceCollectInfos[i].Name = g_ResourceCollectObjName[(REQUIRE)i];
		}
	}
	System() 
	{
		CreateObjs(); 
		CreateFormulas();
		CreateResourceCollectInfos();
	}
};

struct Property
{
	uint32_t num;
	uint32_t quality;
	Property() :num(0), quality(0) {}
};
#include <mutex>
#include <condition_variable>
class ResourceCollect
{
	NUM(Id);
	NUM(Level);
	NUM(ResourceId);
	NAME(Name);
	uint32_t type;

	uint32_t m_clollected;
	uint32_t m_limit;
	uint32_t m_clollectFiveSecond;
	std::atomic<bool> m_working;
	mutex m_lock;
	condition_variable m_condition;
public:
	ResourceCollect(uint32_t id) :m_Id(id), m_working(false), m_clollected(0)
	{
		SetLevel(1);
		SetResourceId(g_ResourceCollectInfos[id].CollectResource);
		SetName(g_ResourceCollectInfos[id].Name);
		m_limit = g_ResourceCollectInfos[id].LimitedStore;
		m_clollectFiveSecond = g_ResourceCollectInfos[id].FiveSecondStore;
	}
	void StartCollect()
	{
		if (m_working) return;
		m_working = true;
		thread collect(&ResourceCollect::CollecteEvent, this);
		collect.detach();
	}
	void StopCollect()
	{
		m_working = false;
	}
	void CollecteEvent()
	{
		while (m_working)
		{ 
			this_thread::sleep_for(chrono::seconds(1));
			std::unique_lock<std::mutex> lock{ m_lock };
			if (m_clollected >= m_limit)
			{
				cout << "收集资源:" << g_ResourceName[(REQUIRE)GetResourceId()].c_str() << "-装不下了" << endl;
				m_clollected = m_limit;
				m_condition.wait(lock);
				continue;
			}
			m_clollected += m_clollectFiveSecond;
			cout << "收集资源:" << g_ResourceName[(REQUIRE)GetResourceId()].c_str() << "-" << m_clollected << endl;
		}
	}
	uint32_t CollectResource()
	{
		auto result = m_clollected;
		m_clollected = 0;
		m_condition.notify_one();
		return result;
	}
	~ResourceCollect()
	{
		m_working = false;
	}
};
class HeroShoping
{
	NAME(Name);
	NUM(Id);
	//std::random_device rd;
	uint32_t m_ObjId;
	map<uint32_t, Property*>* m_PlayerObjNum;
	uint32_t *m_PlayerMoney;
	uint32_t m_Price;
	map<uint32_t, Obj*> *m_playerObj;
private:
	void ComeToBuy()
	{
		/*std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, m_playerObj->size());*/
		 
		auto m_ObjIndex = rand()% m_playerObj->size();//dis(gen);
	
		for (auto obj : *m_playerObj)
		{
			if (--m_ObjIndex)
				continue;
			cout << GetName().c_str() << "想付 ￥" << obj.second->GetPrice() << " 买" << obj.second->GetName().c_str() << endl;
			m_Price = obj.second->GetPrice();
			m_ObjId = obj.first; 
		}
	}
public:
	HeroShoping(string name, map<uint32_t, Obj*>* playerObj,map<uint32_t, Property*>* objsProperty, uint32_t* money):
		m_Name(name), m_playerObj(playerObj), m_PlayerObjNum(objsProperty), m_PlayerMoney(money)
	{
		ComeToBuy();
	}
	~HeroShoping()
	{

	}
	/*HeroShoping(const HeroShoping& sp)
	{
		this->m_Player = sp.m_Player;
		this->m_Id = sp.m_Id;
		this->m_ObjId = sp.m_ObjId;
		this->m_PlayerMoney = sp.m_PlayerMoney;
		this->m_Price = sp.m_Price;
		this->m_playerObj = sp.m_playerObj; 
	}*/
	bool Agree()
	{
		if ((*m_PlayerObjNum).end() == (*m_PlayerObjNum).find(m_ObjId))
		{
			cout << "没有此物品" << endl;
			return false;
		}
		if ((*m_PlayerObjNum)[m_ObjId]->num > 0)
		{
			(*m_PlayerObjNum)[m_ObjId]->num--;
			*m_PlayerMoney += m_Price;
			cout << "成交" << endl;
			Leave();
			return true;
		}
		cout << "缺货" << endl;
		return false;
	}
	void Refuse()
	{
		Leave();
	}
	void Leave()
	{
		cout << GetName().c_str() << "离开" << endl;
		ComeToBuy();
	}
};
struct ResourceInfo
{
	string name;
	uint32_t num;
};  
struct GoodsInfo
{
	uint32_t OwnerId;
	uint32_t Money;
	uint32_t TimeIndex;
	uint32_t Num;
	uint32_t ShopId;
	GoodsInfo()
	{
		Money = 0;
		Num = 0;
		OwnerId = 0;
		ShopId = 0;
	}
};
class GoodShop
{
	NUM(Id);
	uint32_t m_ObjId;
	uint32_t m_StoreMoney;
	GoodsInfo m_good;
	bool free;
public:
	GoodShop():m_StoreMoney(0){}
	GoodShop(uint32_t shopId) :free(true), m_Id(shopId), m_StoreMoney(0),m_ObjId(0){
	}
	
	bool ReciveGood(uint32_t num, uint32_t money, uint32_t, uint32_t);
	void SellGood(uint32_t money)
	{
		m_good.Num--;
		m_StoreMoney += money;
		if (m_good.Num == 0)free = true;
	}
	bool CancelGood(uint32_t objId, uint32_t &num);
	bool GetMoney(uint32_t &money)
	{
		if (0==m_StoreMoney)
			return false;
		money = m_StoreMoney;
		m_StoreMoney = 0;
		return true;
	}
};

class PlayerLive
{
	NAME(Name);
	NUM(Id);
	map<uint32_t, Obj*>m_Objs;
	map<uint32_t, Property*>m_ObjsProperty;

	map<uint32_t, ObjFormula*> m_Formulas;
	map<uint32_t, uint32_t> m_CreateFormulaNum;
	map<uint32_t, uint32_t>* m_pFormulaNext;
	map<uint32_t, uint32_t>* m_pFormulaNextNeed;
	map<REQUIRE, ResourceInfo> m_Resources;
	map<uint32_t, ResourceCollect*> m_ResourceCollectResource;
	map<uint32_t, uint8_t> m_CollectNums;
	uint32_t m_ResourceColloctObjNum;

	vector<HeroShoping*>m_BusinessMans;
	NUM(Money);
	map<uint32_t, GoodShop> m_GoodShops; 
public:
	PlayerLive(string name, uint32_t id): m_Name(name), m_Id(id), m_Money(1000)
	{ 
		m_pFormulaNext = &g_FormulaNext;
		m_pFormulaNextNeed = &g_FormulaNextNeed;
		for (int i = 0; i < 10; i++)
		{
			m_GoodShops[i].SetId(i);
		}
	}
	~PlayerLive() 
	{
		for (auto m : m_ObjsProperty)
		{
			delete m.second;
		}
		for (auto man : m_BusinessMans)
		{
			delete man;
		}
	}
	auto GetPlayerObj()
	{
		return &m_Objs;
	}
	auto GetPlayerObjInfo()
	{
		return &m_ObjsProperty;
	}
	auto GetPlayerMoney()
	{
		return GetpMoney();
	}
	void GetFormulas(uint32_t id)
	{
		m_Formulas[id] = &g_Formulas[id];
	}
	void SetObj(uint32_t id)
	{
		m_Objs[id] = &g_Objs[id];
	}
	void GetObj(uint32_t id, uint32_t num)
	{
		SetObj(id);

		if (m_ObjsProperty.find(id) == m_ObjsProperty.end())
			m_ObjsProperty[id] = new Property();

		m_ObjsProperty[id]->num += num;
	}
	void SetResource(REQUIRE r, uint32_t num)
	{
		m_Resources[r].num = num;
	}
	void GetResource(REQUIRE r, uint32_t num)
	{
		m_Resources[r].name = g_ResourceName[r];
		m_Resources[r].num += num;
	}
	void PayResource(REQUIRE r, uint32_t num)
	{
		m_Resources[r].num -= num;
	}
	bool PayObj(uint32_t id, uint32_t num, uint32_t quality)
	{
		if (m_ObjsProperty.find(id) == m_ObjsProperty.end())
			return false;
		if (m_ObjsProperty[id]->num < num|| m_ObjsProperty[id]->quality!= quality)
			return false;
		m_ObjsProperty[id]->num -= num;
		return true;
	}
	void ShowFormula(uint32_t id)
	{
		if (m_Formulas.find(id) == m_Formulas.end())
			return;

		auto formula = m_Formulas[id];
		cout << "图纸："<<formula->GetName().c_str() << ":"<<endl;
		for (auto require : formula->m_Formula.m_Require)
			cout << " " << require.first << "-" << require.second << endl;
		for (auto obj : formula->m_Formula.m_Obj)
			cout << " " << g_Objs[obj.m_ID].GetName().c_str() << " :" << obj.m_Num << " qulity:" << obj.m_QA << endl;
	}
	bool ChechResourceNum(uint32_t id)
	{
		auto formula = m_Formulas[id]; 
		if (NULL != formula)
		{
			auto require = formula->m_Formula.m_Require;
			auto size = require.size();
			for (int32_t i = 0; i < size; i++)
			{ 
				if (m_Resources[require[i].first].num < require[i].second)
				{ 
					return false;
				}
			}
			auto requireObj = formula->m_Formula.m_Obj;
			size = requireObj.size();
			for (int32_t i = 0; i < size; i++)
			{
				auto obj = requireObj[i]; 
				if (m_ObjsProperty.find(obj.m_ID) == m_ObjsProperty.end() ||
					m_ObjsProperty[obj.m_ID]->num < obj.m_Num ||
					m_ObjsProperty[obj.m_ID]->quality != obj.m_QA)
				{
					return false;
				}
			} 			
		}
		else
		{
			return false;
		}
		return true;
	}
	void PayObjAndResource(uint32_t id)
	{
		auto require = m_Formulas[id]->m_Formula.m_Require;
		auto size = require.size();
		for (int32_t i = 0; i < size; i++)
		{
			auto obj = require[i];
			PayResource(obj.first, obj.second);
			cout << "	消耗资源：" << obj.first << "-" << obj.second << endl;
		}
		auto objs = m_Formulas[id]->m_Formula.m_Obj;
		for (int32_t i = 0; i < objs.size(); i++)
		{
			auto obj = objs[i];
			PayObj(obj.m_ID, obj.m_Num, obj.m_QA);
			cout << "	消耗物品：" << g_Objs[obj.m_ID].GetName().c_str() << "-" << obj.m_Num << endl;
		}
	}
	void CreatObj(uint32_t id)
	{
		if (m_Formulas.find(id) == m_Formulas.end())
		{
			cout << "图纸未解锁" << endl;
			return;
		}

	//	ShowFormula(id);

		if (ChechResourceNum(id))
		{ 
			PayObjAndResource(id);

			auto objId = *m_Formulas[id]->GetpId();
			GetFormula(id);

			if (!m_Objs[objId])
				SetObj(objId); 

			if (m_ObjsProperty.find(objId) == m_ObjsProperty.end())
				m_ObjsProperty[objId] = new Property();

			m_ObjsProperty[objId]->num ++;

			cout << "完成:" << m_Objs[objId]->GetName().c_str() << endl;
		}	
		else
		{
			auto objId = *g_Formulas[id].GetpId();
			 
			cout << "资源不足:" << g_Objs[objId].GetName().c_str() << endl;
		}
	}
	bool CheckFormulaGetOk(uint32_t id)
	{ 
		if (m_Formulas.end() == m_Formulas.find((*m_pFormulaNext)[id]) &&
			m_CreateFormulaNum[id] > (*m_pFormulaNextNeed)[id])
		{
			cout << "获取图纸：" << g_Formulas[(*m_pFormulaNext)[id]].GetName().c_str() << endl;
			GetFormulas((*m_pFormulaNext)[id]);
			return true;
		}
		return false;
	}
	void GetFormula(uint32_t id) 
	{
		m_CreateFormulaNum[id]++;
		CheckFormulaGetOk(id);
	}
	void ShowResource()
	{
		cout << GetName().c_str() <<"包裹状态："<< endl;
		for (auto r : m_Resources)
		{
			cout << r.second.name.c_str() << "-" << r.second.num << endl;
		}
		for (auto o : m_ObjsProperty)
		{  
			cout << g_Objs[o.first].GetName().c_str() << "=" << o.second->num<< endl;
		}

		cout << "拥有金钱："<<m_Money << endl;
	}

	void GetResourceCollectOjb(uint32_t id)
	{
		if (m_CollectNums.find(id)!= m_CollectNums.end()&&m_CollectNums[id] > 2)
			return;
		m_ResourceCollectResource[m_ResourceColloctObjNum++]=new ResourceCollect(id);
		m_CollectNums[id]++;
		cout << "获得：" << g_ResourceCollectInfos[id].Name.c_str() << endl;
	}

	void StartResourceCollectObj(uint32_t clId)
	{
		if(m_ResourceCollectResource.end()!=m_ResourceCollectResource.find(clId))
			m_ResourceCollectResource[clId]->StartCollect();
	}

	void CollectResource(uint32_t clId)
	{
		if (m_ResourceCollectResource.end() == m_ResourceCollectResource.find(clId))
			return;
		auto index = *m_ResourceCollectResource[clId]->GetpResourceId();
		m_Resources[(REQUIRE)index].num+=
			m_ResourceCollectResource[clId]->CollectResource();
	}

	void SetBusinessMan(HeroShoping *man)
	{
		m_BusinessMans.push_back(man);
	}

	void Aggree(uint32_t index)
	{
		if (!m_BusinessMans[index]->Agree())
		{ 
			
		}
	}
	void Refuse(uint32_t index)
	{
		m_BusinessMans[index]->Refuse();
	}

	void StoreMoney(uint32_t shopId, uint32_t money)
	{
		m_GoodShops[shopId].SellGood(money);
	} 

	bool SellInShop(uint32_t shopId, uint32_t num, uint32_t money, uint32_t objId)
	{
		auto obj = m_ObjsProperty.find(objId);
		if (m_ObjsProperty.end() == obj)
			return false;
		if (obj->second->num >= num)
		{
			if (m_GoodShops[shopId].ReciveGood(num, money, GetId(), objId))
			{
				obj->second->num-=num;
				return true;
			}
		}		
		return false;		
	}
	void CancelSellInShop(uint32_t shopId)
	{
		m_GoodShops[shopId];
	}
	bool BuyGood(uint32_t objId, uint32_t money);

	void CancelGood(uint32_t objId, uint32_t shopId);

	bool GetMoneyFromShop(uint32_t shopId);
};






