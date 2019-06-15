
#include "debug.h"

#include <stdio.h>
#include <lua.h>

// skynet_main.c _init_env(lua_State *L)
void lua_table_print(FILE * file, lua_State * L, int index) {
    lua_pushnil(L);  /* first key */
    while (lua_next(L, index) != 0) {
        int keyt = lua_type(L, -2);
        if (keyt != LUA_TSTRING) {
            fprintf(stderr, "Invalid config table\n");
        }
        const char * key = lua_tostring(L,-2);

        fprintf(file, "%s=", key);
        int type = lua_type(L, -1);
        switch(type) {
            case LUA_TNIL:
                fprintf(file, "nil");
                break;
            case LUA_TBOOLEAN:
                fprintf(file, "%s", lua_toboolean(L, -1) ? "true" : "false" );
                break;
            case LUA_TNUMBER:
                fprintf(file, "%f", lua_tonumber(L, -1));
                break;
            case LUA_TSTRING:
                fprintf(file, "%s", lua_tostring(L, -1));
                break;
            case LUA_TTABLE:
                // TODO
                break;
            case LUA_TFUNCTION:
                // TODO
                break;
            case LUA_TLIGHTUSERDATA:
                // TODO
                break;
            case LUA_TTHREAD:
                // TODO
                break;
            case LUA_TNONE:
                fprintf(file, "[none]");
                break;
            default:
                fprintf(file, "[unrecognized type] %d", type);
                break;
        }
        fprintf(file, "\n");
        lua_pop(L,1);
    }
    lua_pop(L,1);
}