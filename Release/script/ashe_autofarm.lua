local DrawMyObject = 0
local MyObject = 0
local hero = 0

local tmp_time = 0
local time_finity = 0

local spell_buffer = 0

local action_attack = 0

local range_attack = 735.0

function OnLoad()
	lua_print('Script Ashe Auto Farm\n')
	MyObject = CreateObjectAI()
	DrawMyObject = CreateObjectAI()
	SetMaxZoom(10000.0)

	tmp_time = GetTimeTick()
end


function OnMain()
 hero = GetMyHero()

 if hero.SkinName == 'Ashe' then
  if hero.hp <= 0 then
   spell_buffer = 0
  end

  if hero.mp >= 8 and hero.hp >= 1 and hero.LevelSkill_Q >= 1 and hero.StatusSkill_Q == 0 and spell_buffer == 0 then
   ActionSpell(_Q, MyObject.map_x, MyObject.map_y, MyObject.map_z)
   spell_buffer = 1
  end

  time_finity = GetTimeTick() - tmp_time

  while time_finity >= 1 do
   MyObject = GetMinionAI(MyObject.count_obj)


    if MyObject.type ~= 0 and hero.hp >= 1 then
	 if MyObject.team_ally ~= hero.my_team then
	  if ColisionRadius(hero.map_x, hero.map_y, MyObject.map_x, MyObject.map_y, range_attack) == 1 then

	   if hero.mp >= 60 and hero.LevelSkill_W >= 1 and hero.StatusSkill_W == 0 and MyObject.hp ~= 0 then
		ActionSpell(_W, MyObject.map_x, MyObject.map_y, MyObject.map_z)
		break
	   end

	   if MyObject.hp <= (hero.Attack - MyObject.Armor)+10 and MyObject.hp ~= 0 then
	    PlayerAttackTo(MyObject.map_x, MyObject.map_y, MyObject.map_z, MyObject.InitObj)
		tmp_time = GetTimeTick()
	    break
	   end

	 end
	end
	else
     break
    end
   end
  end

end

function OnDraw()
	if hero.SkinName == 'Ashe' then
     while true do
	  DrawMyObject = GetMinionAI(DrawMyObject.count_obj)

	  if DrawMyObject.type ~= 0 then
	   if DrawMyObject.team_ally ~= hero.my_team and DrawMyObject.hp >= 1 then
	    if ColisionRadius(hero.map_x, hero.map_y, DrawMyObject.map_x, DrawMyObject.map_y, range_attack) == 1 then
	     DrawGameCircleD3D(DrawMyObject.map_x, DrawMyObject.map_y, DrawMyObject.map_z, 150.0)
	    end
	   end
	  else
	   break
	  end
    end

	 DrawGameCircleD3D(hero.map_x, hero.map_y, hero.map_z, range_attack)
   end
end
