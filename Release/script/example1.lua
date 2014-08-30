local MyObject = 0
local hero = 0
local draw_y = 0
local team = 'COLOR_TEAM'

function OnLoad()
	lua_print('Start Script\n')
	MyObject = CreateObjectAI()
end

function OnMain()
	hero = GetMyHero()

	if hero.SkinName == "Soraka" then
	 DrawTextD3D(150, 400, "Soraka: " ..hero.money , LUA_COLOR(255, 0, 255));

	 if hero.my_team == 0x64 then
	  team = 'BLUE'
	 else
	  team = 'RED'
	 end

	 DrawTextD3D(150, 450, " X: " ..hero.map_x.. " Y: " ..hero.map_y.. " Z: " ..hero.map_z.. " Level: " ..hero.level.. " Team: " ..team, LUA_COLOR(255, 0, 255));
	end

	draw_y = 200
	while true do
	 MyObject = GetHeroAI(MyObject.count_obj)

	 if MyObject.type == 0 then
		break
	 end

	 DrawTextD3D(100, draw_y, "NAME: ", LUA_COLOR(0, 0, 255));
	 DrawTextD3D(160, draw_y, MyObject.HeroName, LUA_COLOR(0, 255, 0));
	 DrawTextD3D(300, draw_y, '' ..MyObject.hp.. '/' ..MyObject.max_hp ..' ', LUA_COLOR(0, 255, 0));

	 if MyObject.team_ally == 0x64 then
	  team = 'BLUE'
	 else
	  team = 'RED'
	 end

	 DrawTextD3D(380, draw_y, " X: " ..MyObject.map_x.. " Y: " ..MyObject.map_y.. " Z: " ..MyObject.map_z.. " Level: " ..MyObject.level.. " Team: " ..team, LUA_COLOR(255, 0, 255));

	 draw_y = draw_y + 20
	end
end

function OnDraw()
 DrawTextD3D(20, 20, 'by Firefox', LUA_COLOR(0, 0, 255));
end
