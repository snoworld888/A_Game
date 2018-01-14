#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Base.h"
using namespace std;
/*
ID
Name
Type
Quality
Price
*/
class Obj
{
	NUM(Id);
	NAME(Name);
	ADD_MEMBER(OBJ_TYPE,Type);
	ADD_MEMBER(int32_t, Quality);
	ADD_MEMBER(uint32_t, Price);
public:
	Obj() {}
	Obj(int id, string name, OBJ_TYPE type, uint32_t quality, uint32_t price) :
		m_Id(id), m_Name(name), m_Quality(quality), m_Price(price) {}
	~Obj() {}
};

/* �䷽
ID
Quality
Num
*/
struct FormulaObj
{
	uint32_t m_ID;
	uint32_t m_QA;
	uint32_t m_Num;
	FormulaObj(uint32_t id, uint32_t qa, uint32_t num) :m_ID(id), m_QA(qa), m_Num(num) {}
};
/*
*/
enum REQUIRE { WOOD_R=0, STONE_R, IRON_R, FUR_R, R_NUM};

struct Formula_
{ 
	vector<pair<REQUIRE, uint32_t>> m_Require;
	vector<FormulaObj> m_Obj;
	Formula_(vector<pair<REQUIRE, uint32_t>> &Require, vector<FormulaObj> formula) :
		m_Require(Require), m_Obj(formula)
	{
	}
	Formula_(){}
};
/* ͼֽ
ID
Name
Level
Require
Formula
*/
class ObjFormula
{
	NUM(Id);
	NAME(Name);
	CLASS_MEMBER(OBJ_TYPE, Type);
	NUM(Level); 
	Formula_ m_Formula;
public: 
	ObjFormula(uint32_t id, string name, uint32_t level,
		Formula_ &formula) :
		m_Id(id), m_Name(name), m_Level(level), m_Formula(formula)
	{ 
	}
	ObjFormula() {}
};

class RecoverObj : public Obj
{

};