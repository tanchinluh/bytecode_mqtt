/***********************************************************************
* ArtemisModule - Scilab Module for Artemis Camera
* Original work Copyright (C) 2017  Tan Chin Luh
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
***********************************************************************/
#include "common.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "MQTTAsync.h"

#if !defined(WIN32)
#include <unistd.h>
#else
#include <windows.h>
#endif

#define ADDRESS     "tcp://192.168.0.119:1883"
#define CLIENTID    "ChuwiSub2"
#define TOPIC       "debug2"
#define PAYLOAD     "Scilab!"
#define QOS         1
#define TIMEOUT     10000L

volatile MQTTAsync_token deliveredtoken_sub_async;

int disc_finished = 0;
int subscribed = 0;
int finished2 = 0;

void connlost_sub_async(void *context, char *cause)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	int rc;

	sciprint("\nConnection lost\n");
	sciprint("     cause: %s\n", cause);

	sciprint("Reconnecting\n");
	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;
	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		sciprint("Failed to start connect, return code %d\n", rc);
	    finished2 = 1;
	}
}


int msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
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
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    return 1;
}


void onDisconnect_sa(void* context, MQTTAsync_successData* response)
{
	sciprint("Successful disconnection\n");
	disc_finished = 1;
}


void onSubscribe(void* context, MQTTAsync_successData* response)
{
	sciprint("Subscribe succeeded\n");
	subscribed = 1;
}

void onSubscribeFailure(void* context, MQTTAsync_failureData* response)
{
	sciprint("Subscribe failed, rc %d\n", response ? response->code : 0);
	finished2 = 1;
}


void onConnectFailure_sa(void* context, MQTTAsync_failureData* response)
{
	sciprint("Connect failed, rc %d\n", response ? response->code : 0);
	finished2 = 1;
}


void onConnect_sa(void* context, MQTTAsync_successData* response)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
	MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
	int rc;

	sciprint("Successful connection\n");

	sciprint("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
           "Press Q<Enter> to quit\n\n", TOPIC, CLIENTID, QOS);
	opts.onSuccess = onSubscribe;
	opts.onFailure = onSubscribeFailure;
	opts.context = client;

	deliveredtoken_sub_async = 0;

	if ((rc = MQTTAsync_subscribe(client, TOPIC, QOS, &opts)) != MQTTASYNC_SUCCESS)
	{
		sciprint("Failed to start subscribe, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}
}

int sci_int_mqtt_sub_async(char * fname,void* pvApiCtx)
{
	MQTTAsync client;
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;
	MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
	MQTTAsync_token token;
	int rc;
	int ch;

	MQTTAsync_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

	MQTTAsync_setCallbacks(client, NULL, connlost_sub_async, msgarrvd, NULL);

	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;
	conn_opts.onSuccess = onConnect_sa;
	conn_opts.onFailure = onConnectFailure_sa;
	conn_opts.context = client;
	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		sciprint("Failed to start connect, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}

	while	(!subscribed)
		#if defined(WIN32)
			Sleep(100);
		#else
			usleep(10000L);
		#endif

	if (finished2)
		goto exit;

	/*do 
	{
		ch = getchar();
	} while (ch!='Q' && ch != 'q');*/

	disc_opts.onSuccess = onDisconnect_sa;
	if ((rc = MQTTAsync_disconnect(client, &disc_opts)) != MQTTASYNC_SUCCESS)
	{
		sciprint("Failed to start disconnect, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}
 	while	(!disc_finished)
		#if defined(WIN32)
			Sleep(100);
		#else
			usleep(10000L);
		#endif

exit:
	MQTTAsync_destroy(&client);
 	return rc;

}
