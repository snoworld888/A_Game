#include "SystemShop.h"

bool SystemShop::BuyGood(uint32_t objId, uint32_t money)
{
	auto goodInd = FindListPlaceByEqualMoney(objId, money);
	auto list = m_GoodsList[objId];
	if (goodInd == list->end())
		return false;
	if (goodInd->Num == 0)
		return false;

	goodInd->Num--;
 
	auto playerSell = GetPlayer(goodInd->OwnerId);
	(*playerSell)->StoreMoney(goodInd->ShopId, money*0.9);

	return true;
}