local MyObject = 0
local hero = 0

function OnLoad()
	lua_print('Turrent DrawCircle\n')
	MyObject = CreateObjectAI()
end

function OnMain()
 hero = GetMyHero()
end

function OnDraw()
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
end
