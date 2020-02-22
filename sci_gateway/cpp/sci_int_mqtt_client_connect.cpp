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


int sci_int_mqtt_client_connect(char * fname,void* pvApiCtx)
{
		
	CheckInputArgument(pvApiCtx, 2, 4);
	CheckOutputArgument(pvApiCtx, 0, 1);

	char *ADDRESS = NULL;
	GetString(1, ADDRESS,pvApiCtx);
	char *CLIENTID = NULL;
	GetString(2, CLIENTID,pvApiCtx);	
	//char *USERNAME = NULL;
	//GetString(3, USERNAME, pvApiCtx);
	//char *PASSWORD = NULL;
	//GetString(4, PASSWORD, pvApiCtx);

	SciErr sciErr;
	MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;
    int ch;

    //MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
	MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_DEFAULT, NULL);
    conn_opts.keepAliveInterval = 60;
    conn_opts.cleansession = 1;
	//conn_opts.username = USERNAME;
	//conn_opts.password = PASSWORD;

    //MQTTClient_setCallbacks(client, NULL, connlost_connect, msgarrvd_connect, delivered_connect);
	
	//MQTTClient_setCallbacks(client, NULL, connlost_connect, msgarrvd_connect, delivered_connect);
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        sciprint("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
    sciprint("Connecting to broker %s with client ID %s \n\n", ADDRESS, CLIENTID);

	sciErr = createPointer(pvApiCtx, nbInputArgument(pvApiCtx) + 1, client);
	AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;

    //MQTTClient_subscribe(client, TOPIC, QOS);

    //do 
    //{
    //    ch = getchar();
    //} while(ch!='Q' && ch != 'q');

    //MQTTClient_disconnect(client, 10000);
    //MQTTClient_destroy(&client);
    return rc;

}
