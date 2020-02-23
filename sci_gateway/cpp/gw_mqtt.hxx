#ifndef __GW_MQTT_GW_HXX__
#define __GW_MQTT_GW_HXX__

#ifdef _MSC_VER
#ifdef GW_MQTT_GW_EXPORTS
#define GW_MQTT_GW_IMPEXP __declspec(dllexport)
#else
#define GW_MQTT_GW_IMPEXP __declspec(dllimport)
#endif
#else
#define GW_MQTT_GW_IMPEXP
#endif

extern "C" GW_MQTT_GW_IMPEXP int gw_mqtt(wchar_t* _pwstFuncName);



#endif /* __GW_MQTT_GW_HXX__ */
