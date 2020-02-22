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


int sci_int_mqtt_sub(char * fname,void* pvApiCtx)
{
	CheckInputArgument(pvApiCtx, 4, 6);
	CheckOutputArgument(pvApiCtx, 0, 1);

	char *ADDRESS = NULL;
	GetString(1, ADDRESS,pvApiCtx);
	char *TOPIC = NULL;
	GetString(2, TOPIC,pvApiCtx);
	char *CLIENTID = NULL;
	GetString(3, CLIENTID,pvApiCtx);
	//char *PAYLOAD = NULL;
	//GetString(4, PAYLOAD,pvApiCtx);
	double *val = NULL;
	int iRows			= 0;
	int iCols			= 0;
	GetDouble(4,val,iRows,iCols,pvApiCtx);
	int QOS = int(*val);
	//GetDouble(5,val,iRows,iCols,pvApiCtx);
	//unsigned long TIMEOUT = unsigned long(*val);

    char* username = NULL;
    GetString(5, username,pvApiCtx);
    char* password = NULL;
    GetString(6, password,pvApiCtx);
    
	MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;
    int ch;

	//const char* api = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6ImNoaW5sdWgiLCJyZWFkX3dyaXRlIjp0cnVlLCJpYXQiOjE1MDIxNjAzMDh9.C7CJs_2ggyHBkBr4LbXIBqvkUsrxYZ7z5svepDDV1MQ";

    MQTTClient_create(&client, ADDRESS, CLIENTID,
    MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 60;
    conn_opts.cleansession = 1;
	conn_opts.username = username;
	conn_opts.password = password;

    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        sciprint("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
    sciprint("Subscribing to topic %s\nfor client %s using QoS%d\n\n", TOPIC, CLIENTID, QOS);
    MQTTClient_subscribe(client, TOPIC, QOS);

    do 
    {
        ch = getchar();
    } while(ch!='Q' && ch != 'q');

    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);

    return rc;

}
