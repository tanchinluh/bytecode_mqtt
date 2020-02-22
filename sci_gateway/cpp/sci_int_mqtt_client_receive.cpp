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
//#define TIMEOUT     1000L

int test1_sendAndReceive(MQTTClient c, int qos, char* test_topic,void* pvApiCtx)
{

	//CheckInputArgument(pvApiCtx, 0, 1);
	//CheckOutputArgument(pvApiCtx, 0, 1);

	SciErr sciErr;
	int* piAddr = NULL;
	int iType   = 0;
	int iRet    = 0;

	MQTTClient_deliveryToken dt;
	MQTTClient_message pubmsg = MQTTClient_message_initializer;
	MQTTClient_message* m = NULL;
	char* topicName = NULL;
	int topicLen;
	int i = 0;
	int iterations = 500;
	int rc;

	pubmsg.payload = "a much longer message that we can shorten to the extent that we need to payload up to 11";
	pubmsg.payloadlen = 11;
	pubmsg.qos = qos;
	pubmsg.retained = 0;


	/* receive any outstanding messages */
	MQTTClient_receive(c, &topicName, &topicLen, &m, 10);


	//sciprint("pstData %s\n",  *pstData);

	//iRet = createSingleString(pvApiCtx, nbInputArgument(pvApiCtx) + 1, pstData);
	//AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;

	//char* pstData = NULL;
	//pstData = "aaa";

	//SetString(1,pstData,pvApiCtx);

	char* pstData = NULL;
	char* payloadptr= NULL;
	//char data; 

	while (topicName)
	{
		//sciprint("is %.*s.\n",  m->payloadlen, (char*)(m->payload));
		payloadptr = NULL;
		payloadptr = (char*)(m->payload);
		*(payloadptr+m->payloadlen) = '\0';
		//data = *payloadptr;
		MQTTClient_free(topicName);
		MQTTClient_freeMessage(&m);
		MQTTClient_receive(c, &topicName, &topicLen, &m, 10);
	}

	if (payloadptr)
	{
		iRet = createSingleString(pvApiCtx, nbInputArgument(pvApiCtx) + 1,payloadptr);
		AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
	}else{
		payloadptr = "[%nan]";
		iRet = createSingleString(pvApiCtx, nbInputArgument(pvApiCtx) + 1,payloadptr);
		AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
	
	}


	////sciprint("last %s\n", pstData);
	//if (payloadptr)
	//{
	//	//char lastdata[100]={}; // char text[1000] = {};  
	//	//for(i=0; i<m->payloadlen; i++)
	//	//{
	//	//	lastdata[i]=*payloadptr++;
	//	//}
	//	//pstData = &lastdata[0];
	//	sciprint("size : %s\n", data);
	////iRet = createSingleString(pvApiCtx, nbInputArgument(pvApiCtx) + 1,pstData);
	////AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
	//}




	return 0;

}

int sci_int_mqtt_client_receive(char * fname,void* pvApiCtx)
{

	CheckInputArgument(pvApiCtx, 2, 2);
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

	char *TOPIC = NULL;
	GetString(2, TOPIC,pvApiCtx);

	test1_sendAndReceive(client, 0, TOPIC,pvApiCtx);


	//do 
	//{
	//   ch = getchar();
	//} while(ch!='Q' && ch != 'q');

	//MQTTClient_disconnect(client, 10000);
	//MQTTClient_destroy(&client);
	return 0;

}
