#pragma once
#include <Windows.h>
#include <stdint.h>

class VMTHook
{
public:

	~VMTHook()	= default;

	VMTHook(void* ptr);

	virtual auto UnhookVMT()            -> void;
	virtual auto RehookVMT()            -> void;

	virtual auto RestoreOriginalVMT()   -> void;

	template <class T>
	static VMTHook* Create(T* ptr) {
		return new VMTHook(reinterpret_cast<void*>(ptr));
	}

	template <class T>
	auto HookFunction(uint32_t index, void* hkFunction) -> T
	{
		return reinterpret_cast<T>(HookFunction(index, hkFunction));
	}


private:

	virtual auto HookFunction(uint32_t index, void* hkFunction) -> void*;
	virtual auto SetVMT(void*)							-> bool;

	void*		m_pClass;
	size_t		m_iVMTSize;
	uint32_t*	m_pOriginalVMT;
	uint32_t*	m_pHookedVMT;



};

//extern CVMT* VMTClient;
