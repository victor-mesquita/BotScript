local MyObject = 0
local DrawMyObject = 0
local hero = 0
local draw_y = 0
local team = 'COLOR_TEAM'
local tmp_time = 0

function OnLoad()
	lua_print('Start Script\n')
	MyObject = CreateObjectAI()
	DrawMyObject = CreateObjectAI()
	SetMaxZoom(10000.0)
	lua_print('Use Skill OK\n')

	--SetMinZoom(-2000.0)
end

function OnMain()
	hero = GetMyHero()
	draw_y = 20

	while true do
	 MyObject = GetHeroAI(MyObject.count_obj)

	 if MyObject.type ~= 0 then
	  if MyObject.team_ally ~= hero.my_team then
	   DrawTextD3D(1, draw_y, "S: "..ShopStatus().. " Money: " ..hero.money.." Skin: " ..hero.SkinName.. " " ..MyObject.map_x.." "..MyObject.map_y.. " " ..MyObject.HeroName.. " " ..MyObject.hp.. '/' ..MyObject.max_hp.. " Lv: " ..MyObject.level.. " Atk: " ..MyObject.Attack.. " PA: " ..MyObject.PowerAbility, LUA_COLOR(0, 0, 255));
	  end

	  if MyObject.team_ally == hero.my_team then
	   DrawTextD3D(1, draw_y, "S: "..ShopStatus().. " Money:" ..hero.money.." Skin: " ..hero.SkinName.. " " ..MyObject.map_x.." "..MyObject.map_y.. " " ..MyObject.HeroName.. " " ..MyObject.hp.. '/' ..MyObject.max_hp.. " Lv: " ..MyObject.level.. " Atk: " ..MyObject.Attack.. " PA: " ..MyObject.PowerAbility, LUA_COLOR(0, 255, 0));
	  end

	  if MyObject.hp <= 200 and MyObject.hp >= 1 then
	   DrawTextD3D(550, draw_y, "HP DOWN", LUA_COLOR(255, 0, 0));
	  end

	  if MyObject.hp == 0 then
	   DrawTextD3D(550, draw_y, "DEAD", LUA_COLOR(255, 0, 0));
	  end

	  draw_y = draw_y + 18
	 else
	  break
	 end
	end

	while true do
	 MyObject = GetTurrentAI(MyObject.count_obj)

	 if MyObject.type ~= 0 then
	  if MyObject.team_ally ~= hero.my_team then
	   DrawGameCircleD3D(MyObject.map_x, MyObject.map_y, MyObject.map_z, 980.0)
	  end
	 else
	  break
	 end
	end

	while true do
	 MyObject = GetMinionAI(MyObject.count_obj)

	 if MyObject.type ~= 0 then
	  if MyObject.team_ally ~= hero.my_team then
	   if ColisionRadius(hero.map_x, hero.map_y, MyObject.map_x, MyObject.map_y, 720.0) == 1 then
	     if hero.LevelSkill_W >= 1 and hero.StatusSkill_W == 0 then
		  ActionSpell(_W, MyObject.map_x, MyObject.map_y, MyObject.map_z)
		 end

	     if MyObject.hp <= (hero.Attack - MyObject.Armor)+15 and MyObject.hp ~= 0 then
	      PlayerAttackTo(MyObject.map_x, MyObject.map_y, MyObject.map_z, MyObject.InitObj)
		 break
		end
	   end
	  end
	 else
	  break
	 end
	end
end

function OnDraw()
    while true do
	 DrawMyObject = GetMinionAI(DrawMyObject.count_obj)

	 if DrawMyObject.type ~= 0 then
	  if DrawMyObject.team_ally ~= hero.my_team and DrawMyObject.hp >= 1 then
	   if ColisionRadius(hero.map_x, hero.map_y, DrawMyObject.map_x, DrawMyObject.map_y, 720.0) == 1 then
	    DrawGameCircleD3D(DrawMyObject.map_x, DrawMyObject.map_y, DrawMyObject.map_z, 150.0)
	   end
	  end
	 else
	  break
	 end
	end

 --DrawTextD3D(50, 50, 'by Firefox', LUA_COLOR(255, 0, 255));
 DrawGameCircleD3D(hero.map_x, hero.map_y, hero.map_z, 735.0)
end
