/***********************************************************************
* MQTT Client Module - Scilab MQTT Client Module with PAHO Library 
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


//#define ADDRESS     "tcp://192.168.0.119:1883"
//#define CLIENTID    "ChuwiSub"
//#define TOPIC       "debug"
//#define PAYLOAD     "Hello Scilab!"
//#define QOS         0
//#define TIMEOUT     100L

//volatile MQTTClient_deliveryToken deliveredtoken_connect;

//void delivered_connect(void *context, MQTTClient_deliveryToken dt)
//{
//    printf("Message with token value %d delivery confirmed\n", dt);
//    deliveredtoken_connect = dt;
//}
//
//int msgarrvd_connect(void *context, char *topicName, int topicLen, MQTTClient_message *message)
//{
//    int i;
//    char* payloadptr;
//
//    sciprint("Message arrived\n");
//    sciprint("     topic: %s\n", topicName);
//    sciprint("   message: ");
//
//    payloadptr = (char *)message->payload;
//    for(i=0; i<message->payloadlen; i++)
//    {
//        sciprint("%c",*payloadptr++);
//    }
//    sciprint("\n");
//
//    MQTTClient_freeMessage(&message);
//    MQTTClient_free(topicName);
//    return 1;
//}
//
//void connlost_connect(void *context, char *cause)
//{
//    printf("\nConnection lost\n");
//    printf("     cause: %s\n", cause);
//}

int sci_int_mqtt_client_disconn(char * fname,void* pvApiCtx)
{

	CheckInputArgument(pvApiCtx, 1, 1);
	CheckOutputArgument(pvApiCtx, 0, 1);

	/////

	int iType			= 0;
	int* piAddr			= NULL;
	void* pvPtr			= NULL;
	double* pdblData	= NULL;
	SciErr sciErr;

	sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddr);
	if(sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 0;
	}

	sciErr = getPointer(pvApiCtx, piAddr, &pvPtr);
	if(sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 0;
	}
	MQTTClient client = pvPtr;



    //do 
    //{
    //   ch = getchar();
    //} while(ch!='Q' && ch != 'q');

    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return 0;

}
