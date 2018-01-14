// FirstStep.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>

#include <thread>

#if 1
//#include "eventManager.h"
#include "roleManger.h"
#include "playerManger.h"
//
//#include "scene.h"
#include "sceneManager.h"
#include "mapManager.h"
#include "obj.h"
#include "System.h"
#include "SystemShop.h"
using namespace std;
// event
std::function<void(void)> eventWork;
 
PlayerManger playerManger;
#endif 
extern System sys;
extern SystemShop g_SystemShop;
int main()
{    
	//sys.CreateObjs();
	//sys.ShowObjs();
	//sys.CreateFormulas();
	sys.ShowFormulas();
	PlayerLive p("player1", 1);
	g_SystemShop.AddPlayer(&p);
	p.GetResource(REQUIRE::STONE_R, 1000);
	p.GetObj(1, 100);
	p.GetFormulas(0);
	//p.GetFormulas(3);
	p.ShowResource();
	for(int i=0;i<100;i++)
		p.CreatObj(0); 
	for (int i = 0; i<100; i++)
		p.CreatObj(1);
	for (int i = 0; i<20; i++)
		p.CreatObj(2); 
	for (int i = 0; i<1; i++)
		p.CreatObj(3);
		
	p.ShowResource();
//	p.GetResourceCollectOjb(1);
//	p.GetResourceCollectOjb(1);
//	p.GetResourceCollectOjb(1);
//	p.GetResourceCollectOjb(1);
//	p.StartResourceCollectObj(3);
//	p.StartResourceCollectObj(1);
//	p.StartResourceCollectObj(1);
///*	std::this_thread::sleep_for(6s);
//	p.CollectResource(0);
//*/	p.CollectResource(0);
	p.SetBusinessMan(new HeroShoping("晋武帝", p.GetPlayerObj(), p.GetPlayerObjInfo(), p.GetPlayerMoney()));
	p.Aggree(0);
	p.Aggree(0);
	p.Aggree(0);
	p.Aggree(0);
	if (p.SellInShop(1, 2, 300, 100))
	{
		cout << p.GetName() << ":上架物品-" << g_Objs.find(100)->second.GetName() << endl;
	}
	p.CancelGood(100, 1);
	PlayerLive p22("player2", 2);
	g_SystemShop.AddPlayer(&p22);
	p22.BuyGood(100, 300);
	p22.ShowResource();
	getchar();
	/*EventManager eventMangaer; 
	Event *event1 = new Event("no1");
	eventMangaer.AddEvents(event1);
	Event *event2 = new Event("no2");
	eventMangaer.AddEvents(event2);
	Event *event3 = new Event("no3");
	eventMangaer.AddEvents(event3);*/
	//eventWork = bind(&EventManager::StartEvent, eventMangaer);
	/*thread eventThread = thread(eventWork);
	eventThread.detach();*/
#if 1	
	FreshVillage fv;
 
	SceneManager sceneManager;
	sceneManager.AddScene(fv.GetName(), &fv);

	/*GameMapManager gameMapManager;
	GameMap gameMap;

	string mapName = "新手村";
	for (auto scene : *sceneManager.GetScene())
	{
		if (scene.first == mapName)
		{ 
			gameMap.SetCurScene(&fv);
		}
		else
		{
			gameMap.AddNearbyScene(scene.first, scene.second);
		}
	}
	gameMapManager.AddGameMap(mapName, &gameMap);*/
 

#if 0
	RoleManger roleManger;
	Farmer f("h1");
	Doctor d("h2");
	roleManger.AddRoles(&f);
	roleManger.AddRoles(&d);
	for (auto roles : *roleManger.GetRoles())
	{
		roles->ShowRoleInfo();
	}
#endif
	
	Player p1("p1");
	playerManger.AddPlayers(&p1);
	Player p2("p2");
	playerManger.AddPlayers(&p2);
	for (auto roles : *playerManger.GetPlayers())
	{
		roles->ShowRoleInfo();
	}

	p1.PlayerRunIntoSence(&fv); 

	cout << "按q离开游戏" << endl;
	while (true)
	{
		char q = getchar();
		if (q == 'q')
			break;
		this_thread::sleep_for(chrono::seconds(1));
	}
	getchar();

#endif
    return 0;
}

