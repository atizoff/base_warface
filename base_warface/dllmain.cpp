#include "header.h"
#include "cClasess.h"
#include "cFunction.h"
#include "vmt.h"

typedef __int64 (WINAPI* PresentSceneFN)(IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
PresentSceneFN oPresent;


VMTHookManager* VmtHook = new VMTHookManager;

HRESULT WINAPI PresentScene(IDirect3DDevice9* m_pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	function();
	return oPresent(m_pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD64 dwReason, LPVOID)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		VmtHook->bInitialize((PDWORD64*)SSystemGlobalEnvironment::Singleton()->GetIRenderer()->GetDirectDevice());
		oPresent = (PresentSceneFN)VmtHook->dwHookMethod((DWORD64)PresentScene, 17);
		break;

	case DLL_PROCESS_DETACH:
		FreeLibraryAndExitThread(hModule, 0);
		break;
	}
}
