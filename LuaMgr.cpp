
#include "stdafx.h"
#include "LuaMgr.h"

extern "C"
{
    #include "lua\lua.h"
    #include "lua\lauxlib.h"
    #include "lua\lualib.h"
};


// 全局变量, test for lua (C变量给lua访问)
int g_nLua = 9;



LuaMgr::LuaMgr()
{

}

LuaMgr::~LuaMgr()
{

}
//////////////////////////

bool LuaMgr::Init()
{
    m_pL = lua_open();
    if (!m_pL)
    {
        printf("lua_open fail!\n");
        return false;
    }

    luaL_openlibs(m_pL); 


    //// 传入一个table 给 lua 用
//     lua_newtable(L);
//     for (int i = 1; i <= 3; ++i){
//         lua_pushnumber(L, i);
//         lua_pushstring(L, i);
//         lua_settable(L, -3);
//     }
    
    //lua_rawset(L,); //lua_settable
    


    //// 注册函数
    lua_CFunction p = ForLuaTest;
    lua_register(m_pL, "ForLuaTest", p); //global index 1 

    lua_pushinteger(m_pL, g_nLua);   //注册常量的原理~
    lua_setglobal(m_pL, "g_nLua");

    // table
//     lua_pushstring(m_pL, "myTable");
//     lua_rawget(m_pL, LUA_REGISTRYINDEX);
//     lua_newtable(m_pL); lua_pushliteral(L, "__mode"); lua_pushliteral(L, "v"); lua_rawset(L, -3);

    //// 注册C++类
     //lua_pushlightuserdata(m_pL, this);
     //lua_setglobal(m_pL, "LuaMgr");
    //int r = luaL_newmetatable(m_pL, "LuaMgr");
//     if (r) {
//         lua_pushvalue(m_pL, 1);
//         lua_pushstring(m_pL, "LuaMgr");
//         lua_settable(m_pL, LUA_REGISTRYINDEX);
//     }
//     lua_getfield(m_pL, LUA_REGISTRYINDEX, "LuaMgr");
//     
//     lua_pop(m_pL,1);
//     lua_newtable(m_pL);
//     lua_pushvalue(m_pL, -1);
//     lua_setfield(m_pL, LUA_GLOBALSINDEX, "LuaMgr");
// 
//      lua_register(m_pL, "Pin", ForLuaFun);
// 
//     lua_register(m_pL, "Instance", (lua_CFunction)&Instance);// instance
    
}

void LuaMgr::Test()
{
    if(NULL == m_pL)
        return ;

    const char* pszFileName = "my.lua";
    FILE *pFile = fopen(pszFileName, "r");
    if (NULL == pFile)
    {
        return ;
    }

    fseek(pFile, 0, SEEK_END);

    int nLen = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    char* pStr = new char[nLen];
    memset(pStr, 0, nLen);
    fread(pStr, 1, nLen, pFile);
    fclose(pFile);

    int err = luaL_loadbuffer(m_pL, pStr, strlen(pStr), pszFileName);
    delete[] pStr;

    if (0 != err)
    {
        const char *err;
        if (lua_isstring(m_pL, -1))
        {
            err = lua_tostring(m_pL, -1);
            printf("%s\n", err);
        }
    }

    lua_pcall(m_pL, 0, 0, 0); //执行 !   (luaL_dostring)
    //lua_pop(m_pL, -1);




    // debug;
    //lua_getstack
    CallFun(m_pL, "fun");

    int n = GetNum(m_pL, "nNum");
    int n2 = GetNum(m_pL, "nNum2");
//     lua_Debug d2;
//     lua_getinfo(m_pL, ">S", &d2);
// 
//     lua_Debug d1;
//     lua_getinfo(m_pL, "_G", &d1);

    
}


///
void LuaMgr::CallFun(lua_State *L, const char* szFun)
{
    lua_getfield(L, LUA_GLOBALSINDEX, szFun); //活动函数
    lua_pcall(L, 0, 0, 0);     /* call 'f' with 3 arguments and 1 result */

}

int LuaMgr::GetNum(lua_State *L, const char* szVar)
{
    lua_getfield(L, LUA_GLOBALSINDEX, szVar);
    int n = lua_tointeger(L, 1);
    lua_pop(L,1);
    return n;
}





























void LuaMgr::Pin()
{
    printf("C++ LuaMgr::Pin\n");
}


/////
int ForLuaTest(lua_State *L)
{
    int num = lua_gettop(L);
    
    int n = 1;
    if (num > 0)
    {
        n = lua_tointeger(L, 1);
    }

    lua_pushinteger(L, n);
    return 1;
}

int ForLuaFun(lua_State *L)
{
    if (lua_isuserdata(L, 1)) {
        LuaMgr* p = (LuaMgr*)lua_touserdata(L, 1);
        if (p)
        {
            p->Pin();
        }
        
    };
    
    return 0;
}

int ForLuaTable(lua_State *L)
{
    // new a table to lua
    return 0;
}