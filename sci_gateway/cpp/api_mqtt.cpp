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

int SetString(int nPos, char *&pstName,void* pvApiCtx)
{
	int iRet    = 0;
	char* pstData = NULL;

	pstData = pstName;

	iRet = createSingleString(pvApiCtx, nbInputArgument(pvApiCtx) + nPos, pstData);
	if(iRet)
	{
		freeAllocatedSingleString(pstData);
		return iRet;
	}

	freeAllocatedSingleString(pstData);
	
	AssignOutputVariable(pvApiCtx, nPos) = nbInputArgument(pvApiCtx) + nPos;
	
	return 0;

}



int GetString(int nPos, char *&pstName,void* pvApiCtx)
{

	SciErr sciErr;
	int* piAddr = NULL;
	int iType   = 0;
	int iRet    = 0;

	sciErr = getVarAddressFromPosition(pvApiCtx, nPos, &piAddr);
	if(sciErr.iErr)
	{
		printError(&sciErr, 0);
		return -1;
	}

	if(isStringType(pvApiCtx, piAddr))
	{
		//sciprint("Is String Type\n");
		if(isScalar(pvApiCtx, piAddr))
		{
			char* pstData = NULL;
			//char* pstName = NULL;


			iRet = getAllocatedSingleString(pvApiCtx, piAddr, &pstData);
			//sciprint("Answer (Single String) : %s\n",  pstData);
			pstName = pstData;


			if(iRet)
			{
				freeAllocatedSingleString(pstData);
				return iRet;
			}


		}
		else
		{
			sciprint("Not Scalar Type\n");
			return -1;
		}

		//AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
	}
	else
	{
		sciprint("Not String Type\n");
		return -1;
		//AssignOutputVariable(pvApiCtx, 1) = 0;
	}
	return 0;
}

//int GetString(int nPos, char *&pstName)
int GetDouble2(int nPos, double *&pstdata, int& iRows,int& iCols,void* pvApiCtx)
{

	SciErr sciErr;
	int* piAddr = NULL;
	int iType   = 0;
	int iRet    = 0;


	//CheckInputArgument(pvApiCtx, 1, 1);
	//CheckOutputArgument(pvApiCtx, 0, 1);

	sciErr = getVarAddressFromPosition(pvApiCtx, nPos, &piAddr);
	if(sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 0;
	}

	if(isDoubleType(pvApiCtx, piAddr))
	{
		if(isScalar(pvApiCtx, piAddr))
		{
			double dblReal	= 1;
			iRows = 1;
			iCols = 1;
			iRet = getScalarDouble(pvApiCtx, piAddr, &dblReal);
			pstdata = &dblReal;

			if(iRet)
			{
				return iRet;
			}

			//sciprint("%f\n",*pstdata);
		}
		else
		{
			double* pdblReal	= NULL;
			sciErr = getMatrixOfDouble(pvApiCtx, piAddr, &iRows, &iCols, &pdblReal);
			pstdata = pdblReal;

			if(sciErr.iErr)
			{
				printError(&sciErr, 0);
				return sciErr.iErr;
			}


		}

	}
	else 
	{
		printError(&sciErr, 0);
		return -1;
	}

	ReturnArguments(pvApiCtx);
	return 0;
}

int GetDouble(int nPos, double *&pstdata, int& iRows,int& iCols,void* pvApiCtx)
{

	SciErr sciErr;
	int* piAddr = NULL;
	int iType   = 0;
	int iRet    = 0;


	sciErr = getVarAddressFromPosition(pvApiCtx, nPos, &piAddr);
	if(sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 0;
	}

	if(isDoubleType(pvApiCtx, piAddr))
	{

		double* pdblReal	= NULL;
		sciErr = getMatrixOfDouble(pvApiCtx, piAddr, &iRows, &iCols, &pdblReal);
		pstdata = pdblReal;

		if(sciErr.iErr)
		{
			printError(&sciErr, 0);
			return sciErr.iErr;
		}


	}
	else 
	{
		printError(&sciErr, 0);
		return -1;
	}

	ReturnArguments(pvApiCtx);
	return 0;
}

int SetDouble(int nPos, double *&pstdata, int& iRows,int& iCols,void* pvApiCtx)
{
	//int iRows			= 0;
	//int iCols			= 0;
	double* pdblReal	= NULL;

	SciErr sciErr;
	pdblReal = pstdata;
	//sciErr = getMatrixOfDouble(pvApiCtx, piAddr, &iRows, &iCols, &pdblReal);
	sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + nPos, iRows, iCols, pdblReal);      
	AssignOutputVariable(pvApiCtx, nPos) = nbInputArgument(pvApiCtx) + nPos;	
	ReturnArguments(pvApiCtx);

	return 0;
}



int GetHandle(int nPos, void *&pstdata,void* pvApiCtx)
{
	int iType			= 0;
	int* piAddr			= NULL;
	void* pvPtr			= NULL;
	double* pdblData	= NULL;
	SciErr sciErr;

	//	double *&pstdata
	//sciErr = getVarAddressFromPosition(pvApiCtx, nPos, &piAddr);
	//double* pdblReal	= NULL;
	//sciErr = getMatrixOfDouble(pvApiCtx, piAddr, &iRows, &iCols, &pdblReal);
	//pstdata = pdblReal;

	sciErr = getVarAddressFromPosition(pvApiCtx, nPos, &piAddr);
	if(sciErr.iErr)
	{
		printError(&sciErr, 0);
		return -1;
	}

	sciErr = getPointer(pvApiCtx, piAddr, &pvPtr);
	if(sciErr.iErr)
	{
		printError(&sciErr, 0);
		return -1;
	}
	pstdata = pvPtr;
	return 0;
}

volatile MQTTClient_deliveryToken deliveredtoken;

void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
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

void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}