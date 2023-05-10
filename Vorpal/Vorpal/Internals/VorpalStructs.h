#pragma once
#include "VorpalInternals.h"

//Structs used by the Vorpal Client
extern "C" struct Protected_Application {
	//std::string Error;
	//ReadOnlyVar<bool> Result;
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

extern "C" struct Protected_LoginApplication {
	//ReadOnlyVar<std::string> Error;
	//ReadOnlyVar<bool> Result;
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

extern "C" struct LicenseKey {
	char AppId[VORPAL_APPID_MAX_CHAR_COUNT];
	char ApplicationName[VORPAL_APPLICATION_NAME_MAX_CHAR_COUNT];
	char License[VORPAL_LICENSE_STR_MAX_CHAR_COUNT];
	uint64_t ExpiryDays;
	uint64_t ExpiryDate;
	int status;
	char HWID[VORPAL_HWID_MAX_CHAR_COUNT];
};

extern "C" struct Protected_Login {
	ReadOnlyData/*std::string*/  HashedID;
	ReadOnlyData/*std::string*/  Username;
	ReadOnlyData/*std::string*/  Email;
	ReadOnlyData/*std::string*/  Status;
	ReadOnlyData/*std::string*/ Rank;

	//Non Protected
	LicenseKey Keys[VORPAL_MAX_LICENSEKEYS]; size_t KeyAmount;
};


//New
extern "C" struct VorpalClient { //Vorpalclient represents the data that the client has, this data is linked to their Vorpal (classPtr) instance
	uint64_t inst;

	Protected_Application app; size_t app_size;
	Protected_LoginApplication loginApp; size_t loginApp_size;
	Protected_Login login; size_t login_size;

	ReadOnlyData currentVar;
	ReadOnlyData currentFile;

	Proc vorpalProcs[VORPAL_MAX_PROCS] = { {{}} };
	Proc vorpalProcs2[VORPAL_MAX_PROCS] = { {{}} };
};