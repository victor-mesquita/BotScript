local MyObject = 0
local hero = 0

function OnLoad()
	lua_print('Start Script\n')
	SetAutoCursorTarget(1)

	hero = CreateObjectAI()
	MyObject = CreateObjectAI()
end

function OnMain()
	hero = GetMyHero()
end

function OnDraw()
end
