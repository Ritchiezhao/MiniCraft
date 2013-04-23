#ifndef SCRIPT_SYSTEM
#define SCRIPT_SYSTEM

#include "Singleton.h"
#include "luna.h"
#include "KratosPrerequisites.h"

namespace Kratos
{

	/************************************************************************/
	/*								�ű�ϵͳ��                                */
	/************************************************************************/

	class ScriptSystem : public CSingleton<ScriptSystem>
	{
		ScriptSystem();
		~ScriptSystem(void) {}
		DECLEAR_SINGLETON(ScriptSystem);

	public:
		void	Init();
		void	Shutdown();
		void	Reset() { Shutdown(); Init(); }
		lua_State*	GetLuaState() { return m_pLuaState; }

	public:
		///ջͨ��
		const STRING		Get_String(int index);
		int					Get_Int(int index);
		float				Get_Float(int index);
		bool				Get_Bool(int index);

		void				Push_Bool(bool b);
		void				Push_Float(float f);
		void				Push_Int(int i);

		///ִ�нű�
		void				DoFile(const STRING& filename);

		///ע��C������lua����
		void				RegisterFunction(const STRING& name);

		//�󶨶���luaȫ�ֱ�(userdata)
		template<class T>
		void	BindObjectToLua(const STRING& nameInLua, T* pObject)
		{
			Luna<T>::userdataType *ud = static_cast<Luna<T>::userdataType*>(lua_newuserdata(m_pLuaState, sizeof(Luna<T>::userdataType)));
			assert(ud);

			int userdata = lua_gettop(m_pLuaState);

			ud->pT = pObject;  // store pointer to object in userdata
			luaL_getmetatable(m_pLuaState, T::className);  // lookup metatable in Lua registry
			lua_setmetatable(m_pLuaState, -2);

			//����ջ��userdata
			lua_pushvalue(m_pLuaState, -1);
			lua_setglobal(m_pLuaState, nameInLua.c_str());

			lua_remove(m_pLuaState, userdata);
		}

		//��C++����lua�Ķ�������(table)��,��table Unit[0] = userdata0, Unit[1] = ...
		template<class T>
		void	BindObjectToLua(const STRING& tableName, int index, T* pObject)
		{
			Luna<T>::userdataType *ud = static_cast<Luna<T>::userdataType*>(lua_newuserdata(m_pLuaState, sizeof(Luna<T>::userdataType)));
			assert(ud);

			int userdata = lua_gettop(m_pLuaState);

			ud->pT = pObject;  // store pointer to object in userdata
			luaL_getmetatable(m_pLuaState, T::className);  // lookup metatable in Lua registry
			lua_setmetatable(m_pLuaState, userdata);

			//��ȡ����table
			lua_getglobal(m_pLuaState, tableName.c_str());
			
			//û���򴴽�
			if(lua_istable(m_pLuaState, -1) == 0)
			{
				lua_newtable(m_pLuaState);
				lua_pushvalue(m_pLuaState, -1);
				lua_setglobal(m_pLuaState, tableName.c_str());
			}

			int table = lua_gettop(m_pLuaState);
			//��userdata�������
			lua_pushnumber(m_pLuaState, index);
			lua_pushvalue(m_pLuaState, userdata);
			lua_settable(m_pLuaState, table);

			// fix.��ֹ��ջһֱ���� [4/23/2013 mavaL]
			lua_remove(m_pLuaState, userdata);
			lua_remove(m_pLuaState, table);
		}

		template<class T>
		void	Push(T p);
		template<>
		void	Push( float p ) { lua_pushnumber(m_pLuaState, p); }
		template<>
		void	Push(int p)		{ lua_pushnumber(m_pLuaState, p); }

		///
		///C������ʽ����lua�ж���ĺ���
		///

		//�޲�,�޷���ֵ
		void Call(const char* name)
		{
			lua_pushcclosure(m_pLuaState, OnError, 0);
			int errfunc = lua_gettop(m_pLuaState);

			lua_pushstring(m_pLuaState, name);
			lua_gettable(m_pLuaState, LUA_GLOBALSINDEX);

			assert(lua_isfunction(m_pLuaState, -1));
			lua_pcall(m_pLuaState, 0, 0, errfunc);

			lua_remove(m_pLuaState, errfunc);
		}

		//1������,�޷���ֵ
		template<class T>
		void Call(const char* name, T p1)
		{
			lua_pushcclosure(m_pLuaState, OnError, 0);
			int errfunc = lua_gettop(m_pLuaState);

			lua_pushstring(m_pLuaState, name);
			lua_gettable(m_pLuaState, LUA_GLOBALSINDEX);

			assert(lua_isfunction(m_pLuaState, -1));
			Push(p1);
			lua_pcall(m_pLuaState, 1, 0, errfunc);

			lua_remove(m_pLuaState, errfunc);
		}

		//2������,�޷���ֵ
		template<class T1, class T2>
		void Call(const char* name, T1 p1, T2 p2)
		{
			lua_pushcclosure(m_pLuaState, OnError, 0);
			int errfunc = lua_gettop(m_pLuaState);

			lua_pushstring(m_pLuaState, name);
			lua_gettable(m_pLuaState, LUA_GLOBALSINDEX);

			assert(lua_isfunction(m_pLuaState, -1));
			Push(p1);
			Push(p2);
			lua_pcall(m_pLuaState, 2, 0, errfunc);

			lua_remove(m_pLuaState, errfunc);
		}

	private:
		///debug����,ȡ�� Lua_Tinker��
		static int	OnError(lua_State* L);
		static void	PrintError(lua_State *L, const char* fmt, ...);
		void		EnumStack(lua_State *L);
		static void CallStack(lua_State* L, int n);

	private:
		lua_State*	m_pLuaState;
	};

}


#endif