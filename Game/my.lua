

globalT = {1,2,3,4,5,6,7};

nNum = 12;
nNum2 = 20;

local tt = {1,2,3,4};

function fun()
	print("fun")
	local t = {1,2,3}

	print("lua call C function:", ForLuaTest(4))
	print("lua get C int value:", g_nLua);

	print("LuaMgr type", type(LuaMgr))
	print("LuaMgr ~ ", LuaMgr);
	print("LuaMgr : ", LuaMgr:Pin());
	print(myTable);
	--print("LuaMgr:Instance() type", type(LuaMgr.Instance()))


	----- C++ ��ʱ��û�м��lua����Ļ���!
end



testClass = {
	a = 1,
	test = function() print("test fun") end,
}

testClass:test()
testClass.test()

print(type(testClass))
print(type(testClass.test ) )

fun()