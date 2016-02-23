#ifndef LUA_MGR_H
#define LUA_MGR_H

struct lua_State;


class LuaMgr
{
public:
    LuaMgr();
    virtual ~LuaMgr();

    static LuaMgr& Instance(){
        static LuaMgr inst;
        return inst;
    }


    bool Init();   
    void Test();

    void Pin();

private:

    void CallFun(lua_State *L, const char* szFun);  //调用函数

    int GetNum(lua_State *L, const char* szVar);    //

    //test lua state
    lua_State *m_pL;


};


// lua 中调用的 C 函数
int ForLuaTest(lua_State *L);
int ForLuaFun(lua_State *L);
int ForLuaTable(lua_State *L);


#endif