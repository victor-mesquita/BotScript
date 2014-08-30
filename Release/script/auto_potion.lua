local hero = 0
local quantity_item = 0

local tmp_time_hp = 0
local time_finity_hp = 0

local tmp_time_mp = 0
local time_finity_mp = 0

local tmp_other = 0
local tmp_finity_other = 0

local quantity_item_hp = 0
local quantity_item_mp = 0

local pct_hp = 0
local pct_mp = 0

local slot_hp = 0
local slot_mp = 0

local buy_potion_hp = 3
local buy_potion_mp = 4


function OnLoad()
	lua_print('Auto Potion Script\n')
	tmp_time_hp = GetTimeTick()
	tmp_time_mp = GetTimeTick()
	tmp_other = GetTimeTick()
end

function OnMain()
		hero = GetMyHero()

		slot_hp = 0
		slot_mp = 0

		while true do
		 if GetInventorySlot(slot_hp) == 2003 then
		  break
		 end
		 if slot_hp >= 6 then
		  break
		 end
		 slot_hp = slot_hp + 1
		end

		while true do
		 if GetInventorySlot(slot_mp) == 2004 then
		  break
		 end
		 if slot_mp >= 6 then
		  break
		 end
		 slot_mp = slot_mp + 1
		end

		tmp_finity_other = GetTimeTick() - tmp_other

		 quantity_item_hp = GetItemQuantity(slot_hp)
		 quantity_item_mp = GetItemQuantity(slot_mp)

		-- Aguarda 1 minuto para fazer a compra das poções
		if tmp_finity_other >= 1 then
		 -- compra 5x o regeneration potion
		 if ShopStatus() == 1 and quantity_item_hp < buy_potion_hp and hero.money >= 35 then
		   BuyItem(2003)
		   tmp_other = GetTimeTick()
		 end

		 if ShopStatus() == 1 and quantity_item_mp < buy_potion_mp and hero.money >= 35 then
		   BuyItem(2004)
		   tmp_other = GetTimeTick()
		 end
		end

		if quantity_item_hp >= 1 then
		 DrawTextD3D(0, 420, "You have "..quantity_item_hp.." potions hp regeneration!", LUA_COLOR(255, 0, 0))
		end

		if quantity_item_mp >= 1 then
		 DrawTextD3D(0, 440, "You have "..quantity_item_mp.." potions mp regeneration!", LUA_COLOR(255, 0, 0))
		end

		time_finity_hp = GetTimeTick() - tmp_time_hp
		time_finity_mp = GetTimeTick() - tmp_time_mp

		DrawTextD3D(0, 460, "TIME: " ..time_finity_hp, LUA_COLOR(255, 0, 0))
		DrawTextD3D(0, 480, "TIME: " ..time_finity_mp, LUA_COLOR(255, 0, 0))

		-- time_finity >= 15 (15 seg)
		-- Usa a poção caso o HP for 20% menor
		pct_hp = (hero.max_hp*80)/100

		if ShopStatus() ~= 1 and hero.hp <= pct_hp and time_finity_hp >= 15 and quantity_item_hp >= 1 then
		 UseItemSlot(slot_hp)
		 tmp_time_hp = GetTimeTick()
		end

		pct_mp = (hero.max_mp*80)/100

		if ShopStatus() ~= 1 and hero.mp <= pct_mp and time_finity_mp >= 15 and quantity_item_mp >= 1 then
		 UseItemSlot(slot_mp)
		 tmp_time_mp = GetTimeTick()
		end
end

function OnDraw()
end
