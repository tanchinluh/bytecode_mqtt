//=============================================================================
//=============================================================================

#include <Windows.h> // Used only for Sleep

/*--------------------------------------------------------------------------*/
#pragma comment(lib,"../../thirdparty/paho/windows/lib/paho-mqtt3a.lib")
#pragma comment(lib,"../../thirdparty/paho/windows/lib/paho-mqtt3as.lib")
#pragma comment(lib,"../../thirdparty/paho/windows/lib/paho-mqtt3c.lib")
#pragma comment(lib,"../../thirdparty/paho/windows/lib/paho-mqtt3cs.lib")

/*--------------------------------------------------------------------------*/
int WINAPI DllMain (HINSTANCE hInstance , DWORD reason, PVOID pvReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return 1;
}
/*--------------------------------------------------------------------------*/


