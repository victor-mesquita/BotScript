local hero = 0
local quantity_item = 0
local tmp_time = 0
local time_finity = 0

function OnLoad()
	lua_print('Start Script\n')
	tmp_time = GetTimeTick()
end

function OnMain()
		hero = GetMyHero()

		--[[
		-- compra 5x o regeneration potion
		if ShopStatus() == 1 and quantity_item < 5 and hero.money >= 35 then
		 BuyItem(2003)
		 quantity_item = quantity_item + 1
		end

		if quantity_item >= 5 then
		 DrawTextD3D(0, 500, "5 Potions comprado com sucesso!", LUA_COLOR(255, 0, 0))
		end

		time_finity = GetTimeTick() - tmp_time
		DrawTextD3D(0, 520, "TIME: " ..time_finity, LUA_COLOR(255, 0, 0))

		-- time_finity >= 15 (15 seg)
		if hero.hp < hero.max_hp and time_finity >= 15 then
		 if GetInventorySlot(0) == 2003 then
		  UseItemSlot(0)
		 end

		 if GetInventorySlot(1) == 2003 then
		  UseItemSlot(1)
		 end

		 if GetInventorySlot(2) == 2003 then
		  UseItemSlot(2)
		 end

		 if GetInventorySlot(3) == 2003 then
		  UseItemSlot(3)
		 end

		 if GetInventorySlot(4) == 2003 then
		  UseItemSlot(4)
		 end

		 if GetInventorySlot(5) == 2003 then
		  UseItemSlot(5)
		 end

		 if GetInventorySlot(6) == 2003 then
		  UseItemSlot(6)
		 end

		 tmp_time = GetTimeTick()
		end
		--]]
end

function OnDraw()
 DrawTextD3D(0, 300, "Q " ..hero.LevelSkill_Q.. " W "..hero.LevelSkill_W.." E "..hero.LevelSkill_E.." R "..hero.LevelSkill_R, LUA_COLOR(0, 0, 255));
 DrawTextD3D(0, 320, "SQ " ..hero.StatusSkill_Q.. " SW "..hero.StatusSkill_W.." SE "..hero.StatusSkill_E.." SR "..hero.StatusSkill_R, LUA_COLOR(0, 0, 255));
 DrawTextD3D(0, 340, "Slot: " .. GetInventorySlot(0), LUA_COLOR(255, 0, 0))
 DrawTextD3D(0, 360, "Slot: " .. GetInventorySlot(1), LUA_COLOR(255, 0, 0))
 DrawTextD3D(0, 380, "Slot: " .. GetInventorySlot(2), LUA_COLOR(255, 0, 0))
 DrawTextD3D(0, 400, "Slot: " .. GetInventorySlot(3), LUA_COLOR(255, 0, 0))
 DrawTextD3D(0, 420, "Slot: " .. GetInventorySlot(4), LUA_COLOR(255, 0, 0))
 DrawTextD3D(0, 440, "Slot: " .. GetInventorySlot(5), LUA_COLOR(255, 0, 0))
 DrawTextD3D(0, 460, "Slot: " .. GetInventorySlot(6), LUA_COLOR(255, 0, 0))
 DrawTextD3D(0, 480, "Shop Status: " ..ShopStatus(), LUA_COLOR(255, 0, 0))
end
