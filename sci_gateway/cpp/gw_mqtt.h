#ifndef __GW_MQTT_GW_H__
#define __GW_MQTT_GW_H__

#include "c_gateway_prototype.h"

STACK_GATEWAY_PROTOTYPE(sci_int_mqtt_client_connect);
STACK_GATEWAY_PROTOTYPE(sci_int_mqtt_client_disconn);
STACK_GATEWAY_PROTOTYPE(sci_int_mqtt_client_receive);
STACK_GATEWAY_PROTOTYPE(sci_int_mqtt_client_sub);
STACK_GATEWAY_PROTOTYPE(sci_int_mqtt_pub);
STACK_GATEWAY_PROTOTYPE(sci_int_mqtt_sub);

#endif /* __GW_MQTT_GW_H__ */
