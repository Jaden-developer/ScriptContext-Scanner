/*
 [!] Modified by Jaden Wester
 [!] Use this how much you want, credits would be appreciated :)
*/

namespace Hook{
void* placeHook(DWORD address, void* hook, bool revert = false) {
	DWORD oldprot;
	if (!revert) {
		void* oldmem = new void*;
		void* result = new void*;
		memcpy(oldmem, (void*)address, sizeof(void*) * 4);
		VirtualProtect((LPVOID)address, 1, PAGE_EXECUTE_READWRITE, &oldprot);
		*(char*)address = 0xE9; *(DWORD*)(address + 1) = (DWORD)hook - address - 5;
		memcpy(result, oldmem, sizeof(void*) * 4);
		VirtualProtect((LPVOID)address, 1, oldprot, &oldprot);
		return result;
	}
	else {
		VirtualProtect((LPVOID)address, 1, PAGE_EXECUTE_READWRITE, &oldprot);
		memcpy((void*)address, hook, sizeof(void*) * 4);
		VirtualProtect((LPVOID)address, 1, oldprot, &oldprot);
		return NULL;
	}
}

}
DWORD a1 = 0;
DWORD r_l_gettop = 0x825d90; //gettop addr

int a2(DWORD rState)
{
	a1 = rState;
	return (*(DWORD *)(rState + top) - *(DWORD *)(rState + base)) >> 4;
}

int main()
{
  CONSOLEBYPASS(); // Console Bypass from Axon Source Code. 
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	HWND ConsoleHandle = GetConsoleWindow();
	SetWindowPos(ConsoleHandle, HWND_TOPMOST, 50, 20, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	ShowWindow(ConsoleHandle, 1);
	SetConsoleTitle("Exploit Name");
	cout << ipurple << "Scanning for ScriptContext.." << endl;
	DWORD stuff;
	VirtualProtect((LPVOID)&FindWindowA, 1, PAGE_EXECUTE_READWRITE, &stuff);
	*(char*)&FindWindowA = 0x90; // This is not an offset that requires updating!
	VirtualProtect((LPVOID)&FindWindowA, 1, stuff, &stuff);
	cout << igreen << "Done!" << endl;

	cout << ipurple << "LuaState.." << endl;
	void* old = Hook::placeHook(xxxTentacion(r_l_gettop), a2); 
	do { Sleep(1); } while (a1 == 0);
	Hook::placeHook(xxxTentacion(r_l_gettop), old, 1); // A cool scan.
	RLuaState = a1;
}
