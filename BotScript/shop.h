#ifndef __SHOP_H_
#define __SHOP_H_

#include "library.h"

int SellItem(lua_State *L);
int BuyItem(lua_State *L);
int GetInventorySlot(lua_State *L);
int ShopStatus(lua_State *L);
int IntermedGetInventorySlot(int SlotID);
int GetItemQuantity(lua_State *L);
int IntermedGetQuantitySlot(int SlotID);

#endif