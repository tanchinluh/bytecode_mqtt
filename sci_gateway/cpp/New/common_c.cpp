#include "common_c.h"
//#include "MQTTClient.h"

	
//volatile MQTTClient_deliveryToken deliveredtoken;

static void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

static int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    int i;
    char* payloadptr;

    sciprint("Message arrived\n");
    sciprint("     topic: %s\n", topicName);
    sciprint("   message: ");

    payloadptr = (char *)message->payload;
    for(i=0; i<message->payloadlen; i++)
    {
        sciprint("%c",*payloadptr++);
    }
    sciprint("\n");

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

static void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}


