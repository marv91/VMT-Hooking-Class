#include "stdafx.h"
#include "VMT.h"


VMTHook::VMTHook(void* ptr)
{
	this->SetVMT(ptr);
}

auto VMTHook::SetVMT(void* ptr) -> bool
{
		if (!ptr) return false;

		m_pClass				=	ptr;
		m_pOriginalVMT	=	*reinterpret_cast<uint32_t**>(ptr);

		m_iVMTSize = 0;

		while (m_pOriginalVMT[m_iVMTSize] && !IsBadReadPtr((void*)m_pOriginalVMT[m_iVMTSize], 4))
			m_iVMTSize++;

		m_pHookedVMT = new uint32_t[m_iVMTSize];

		memcpy(
			m_pHookedVMT,
			reinterpret_cast<const void*>(m_pOriginalVMT),
			m_iVMTSize++ * sizeof(void*)
		);

		*reinterpret_cast<uint32_t**>(m_pClass) = m_pHookedVMT;

		return true;
}

auto VMTHook::RestoreOriginalVMT() -> void
{
	*reinterpret_cast<uint32_t**>(m_pClass) = m_pOriginalVMT;
	delete[] m_pHookedVMT;
}

auto VMTHook::HookFunction(uint32_t index, void *hkFunction) -> void*
{
	if (index > m_iVMTSize - 1) return nullptr;

	m_pHookedVMT[index] = reinterpret_cast<uint32_t>(hkFunction);

	return reinterpret_cast<void*>(m_pOriginalVMT[index]);
}

auto VMTHook::UnhookVMT() -> void
{
	*reinterpret_cast<uint32_t**>(m_pClass) = m_pOriginalVMT;
}

auto VMTHook::RehookVMT() -> void
{
	*reinterpret_cast<uint32_t**>(m_pClass) = m_pHookedVMT;
}
