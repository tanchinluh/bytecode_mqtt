#include <wchar.h>
#include "gw_mqtt.hxx"
extern "C"
{
#include "gw_mqtt.h"
#include "addfunction.h"
}

#define MODULE_NAME L"gw_mqtt"

int gw_mqtt(wchar_t* _pwstFuncName)
{
    if(wcscmp(_pwstFuncName, L"int_mqtt_client_connect") == 0){ addCStackFunction(L"int_mqtt_client_connect", &sci_int_mqtt_client_connect, MODULE_NAME); }
    if(wcscmp(_pwstFuncName, L"int_mqtt_client_disconn") == 0){ addCStackFunction(L"int_mqtt_client_disconn", &sci_int_mqtt_client_disconn, MODULE_NAME); }
    if(wcscmp(_pwstFuncName, L"int_mqtt_client_receive") == 0){ addCStackFunction(L"int_mqtt_client_receive", &sci_int_mqtt_client_receive, MODULE_NAME); }
    if(wcscmp(_pwstFuncName, L"int_mqtt_client_sub") == 0){ addCStackFunction(L"int_mqtt_client_sub", &sci_int_mqtt_client_sub, MODULE_NAME); }
    if(wcscmp(_pwstFuncName, L"int_mqtt_pub") == 0){ addCStackFunction(L"int_mqtt_pub", &sci_int_mqtt_pub, MODULE_NAME); }
    if(wcscmp(_pwstFuncName, L"int_mqtt_sub") == 0){ addCStackFunction(L"int_mqtt_sub", &sci_int_mqtt_sub, MODULE_NAME); }

    return 1;
}
