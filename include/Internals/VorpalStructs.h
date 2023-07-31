/**
* Copyright (C) 2023 Vorpal. All rights reserved.
*
* Licensed under the MIT License. You may obtain a copy
* in the file "LICENSE" found at the root of this repository.
*/

#ifndef VORPAL_STRUCTS_H_
#define VORPAL_STRUCTS_H_

#include "VorpalInternals.h"

//Structs used by the Vorpal Client
VORPAL_EXTERN struct Protected_Application {
	//ReadOnlyData Error;
	ReadOnlyData/*bool*/ Result;
	//uint64_t Time;

	ReadOnlyData/*string*/ Name;
	ReadOnlyData/*string*/ Domain;
	ReadOnlyData/*string*/ Version;
	ReadOnlyData/*string*/ Login;
	ReadOnlyData/*string*/ Key;

	ReadOnlyData/*bool*/ HWID;
	ReadOnlyData/*bool*/ Maintenance;
	ReadOnlyData/*bool*/ Developer;
	ReadOnlyData/*bool*/ AntiDebug;
	ReadOnlyData/*bool*/ AntiVM;
};

VORPAL_EXTERN struct Protected_LoginApplication {
	//ReadOnlyData Error;
	ReadOnlyData/*bool*/ Result;
	//uint64_t Time;

	ReadOnlyData/*std::string*/ HashedID;
	ReadOnlyData/*std::string*/ Username;
	ReadOnlyData/*std::string*/ Email;
	ReadOnlyData/*std::string*/ Status;
	ReadOnlyData/*std::string*/ Rank;
	ReadOnlyData/*std::string*/ Key;
	ReadOnlyData/*std::string*/ HWID;
	//uint64_t Expiry;
};

VORPAL_EXTERN struct LicenseKey {
	char AppId[VORPAL_APPID_MAX_CHAR_COUNT];
	char ApplicationName[VORPAL_APPLICATION_NAME_MAX_CHAR_COUNT];
	char License[VORPAL_LICENSE_STR_MAX_CHAR_COUNT];
	uint64_t ExpiryDays;
	uint64_t ExpiryDate;
	int status;
	char HWID[VORPAL_HWID_MAX_CHAR_COUNT];
};

VORPAL_EXTERN struct Protected_Login {
	ReadOnlyData/*std::string*/  HashedID;
	ReadOnlyData/*std::string*/  Username;
	ReadOnlyData/*std::string*/  Email;
	ReadOnlyData/*std::string*/  Status;
	ReadOnlyData/*std::string*/ Rank;

	//Non Protected
	LicenseKey Keys[VORPAL_MAX_LICENSEKEYS]; size_t KeyAmount;
};


VORPAL_EXTERN struct VorpalClient { //Vorpalclient represents the data that the client has, this data is linked to their Vorpal (classPtr) instance
	Protected_Application app; size_t app_size;
	Protected_LoginApplication loginApp; size_t loginApp_size;
	Protected_Login login; size_t login_size;

	ReadOnlyData currentVar;
	ReadOnlyData currentFile;

	Proc vorpalProcs[VORPAL_MAX_PROCS] = { {{}} };
	Proc vorpalProcs2[VORPAL_MAX_PROCS] = { {{}} };
};

#endif //VORPAL_STRUCTS_H