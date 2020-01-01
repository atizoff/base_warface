#include "header.h"
#include "cClasess.h"
#include "cFunction.h"
#include "vmt.h"

typedef __int64 (WINAPI* EndSceenFn)(IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
EndSceenFn pEndSceen;


VMTHookManager* VmtHook = new VMTHookManager;

HRESULT WINAPI myEndSceen(IDirect3DDevice9* m_pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	function();
	return pEndSceen(m_pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD64 dwReason, LPVOID)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		VmtHook->bInitialize((PDWORD64*)SSystemGlobalEnvironment::Singleton()->GetIRenderer()->GetDirectDevice());
		pEndSceen = (EndSceenFn)VmtHook->dwHookMethod((DWORD64)myEndSceen, 42);
		break;

	case DLL_PROCESS_DETACH:
		FreeLibraryAndExitThread(hModule, 0);
		break;
	}
}
