local MenuObj = 0
local CategoryMenuObj = 0
local Category1 = 0
local Category2 = 0
local Category3 = 0
local Category4 = 0
local Category5 = 0

function OnLoad()
	lua_print('Menu Example\n')
	-- LUA_ARGB(R, B, G, ALPHA)
	-- CreateMenu(w, h, color, list_category)
	MenuObj = CreateMenu(200, 200, LUA_ARGB(0, 0, 0, 150), 16)

	Category1 = AddListCategory(MenuObj, 'Cheat Action', 0)
	AddCategoryBox(MenuObj, Category1, 'ON', 0)
	AddCategoryBox(MenuObj, Category1, 'OFF', 1)
	AddCategoryBox(MenuObj, Category1, ' - ', 2)

	Category2 = AddListCategory(MenuObj, 'Teste', 1)
	AddCategoryBox(MenuObj, Category2, 'ON', 0)
	AddCategoryBox(MenuObj, Category2, 'OFF', 1)
	AddCategoryBox(MenuObj, Category2, ' - ', 2)


	Category3 = AddListCategory(MenuObj, 'Menu 2' 2)

	CategoryMenuObj = CreateMenuCategory(MenuObj, Category3, 200, 200, LUA_ARGB(0, 0, 0, 150), 4)

	Category4 = AddListCategoryBox(CategoryMenuObj, MenuCategory3, 'Teste ->', 0)
	AddCategoryBox(MenuObj, Category4, 'Disable', 0)
	AddCategoryBox(MenuObj, Category4, 'Enabled', 1)

	Category5 = AddListCategoryBox(CategoryMenuObj, MenuCategory3, 'Teste 2 ->', 0)
	AddCategoryBox(MenuObj, Category5, 'YEAH', 0)

end

function OnMain()
end

function OnDraw()
 DrawMenu(MenuObj, 200, 200)
end

function myOnButton()
end

function myOnCheckBox()
end

