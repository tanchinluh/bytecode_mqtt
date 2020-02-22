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
//#include "sciprint.h"
//#include <iostream>
//#include <stdio.h>
//#include "api_scilab.h"
//#include <Scierror.h>
//#include "stdlib.h"
//#include "string.h"

#include "common.h"
#include "MQTTClient.h"
//#include "MQTTAsync.h"

using namespace std;

void delivered(void *context, MQTTClient_deliveryToken dt);
int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message);
void connlost(void *context, char *cause);
volatile MQTTClient_deliveryToken deliveredtoken;