#pragma once
#include "header.h"

class SSystemGlobalEnvironment;
class IRenderer;

class SSystemGlobalEnvironment
{
public:
	IRenderer* GetIRenderer() { return (IRenderer*) * (DWORD64*)((DWORD64)this + 0x48); }

	static SSystemGlobalEnvironment* Singleton()
	{
		return *(SSystemGlobalEnvironment**)0x141D132D0;
	}
};

class IRenderer
{
public:
	DWORD64* GetDirectDevice()
	{
		return (DWORD64*) * (DWORD64*)((DWORD64)this + 0xA6D0);
	}
};
