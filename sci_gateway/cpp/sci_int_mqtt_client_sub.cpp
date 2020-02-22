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


int sci_int_mqtt_client_sub(char * fname,void* pvApiCtx)
{

	CheckInputArgument(pvApiCtx, 3, 3);
	CheckOutputArgument(pvApiCtx, 0, 1);
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
	double *val = NULL;
	int iRows			= 0;
	int iCols			= 0;
	GetDouble(3,val,iRows,iCols,pvApiCtx);
	int QOS = int(*val);



	MQTTClient_subscribe(client, TOPIC, QOS);

    return 0;

}
