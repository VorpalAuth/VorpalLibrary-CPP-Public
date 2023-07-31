/**
* Copyright (C) 2023 Vorpal. All rights reserved.
*
* Licensed under the MIT License. You may obtain a copy
* in the file "LICENSE" found at the root of this repository.
*/

#ifndef VORPAL_INTERNALS_H_
#define VORPAL_INTERNALS_H_

#include <stdint.h>
#include <string>
#include <optional>
#include <functional>

#define VORPAL_API   extern "C" __declspec( dllimport )
#define VORPAL_EXTERN extern "C"

//Configuration
#define VORPAL_DEFAULT_STR_CHAR_COUNT 64

//DO NOT TOUCH
#define VORPAL_API_VERSION 4

#define VORPAL_MAX_PROCS 16
#define VORPAL_PROC_MAX_ARGS 10
#define VORPAL_PROC_STR_MAX_CHAR_COUNT 25

#define VORPAL_MAX_LICENSEKEYS 256

#define VORPAL_HWID_MAX_CHAR_COUNT 256
#define VORPAL_APPID_MAX_CHAR_COUNT 64
#define VORPAL_APPLICATION_NAME_MAX_CHAR_COUNT 64
#define VORPAL_LICENSE_STR_MAX_CHAR_COUNT 64



//Forward declarations
struct VorpalClient;


//Status/Error enum
enum class VORPAL_STATUS : uint32_t {
	NONE = 0x00,

	//Good statuses, proceed no problems
	MIN_GOOD = 0xA00,
	OK = 0xA01,
	DONE = 0xA02,
	MAX_GOOD = 0xAFF,

	//Neutral
	MIN_NEUTRAL = 0xB00,
	WAITING = 0xB01,
	BUSY = 0xB02,

	MAX_NEUTRAL = 0xBFF,

	//Errors
	MIN_ERROR = 0xF00,
	NOT_ENOUGH_MEMORY = 0xF01, //Allocate more memory for us please
	NOT_INITIALIZED = 0xF02, //You probably forgot to initialize/allocate something
	FULL = 0xF03,
	TIMED_OUT= 0xF04,
	BAD_DATA = 0xF05,
	API_MISMATCH = 0xF06,
	MAX_ERROR = 0xFFF,
};

//Structs used when dealing with VorpalProcedures
VORPAL_EXTERN union ProcArg {
	int arg_i;
	uint64_t arg_ull;
	float arg_f;
	char arg_s[VORPAL_PROC_STR_MAX_CHAR_COUNT];
};

VORPAL_EXTERN struct ProcArgs {
	ProcArg args[VORPAL_PROC_MAX_ARGS] = {};
};

VORPAL_EXTERN struct Proc {
	uint32_t proc{};
	ProcArgs args{};

	VORPAL_STATUS status = VORPAL_STATUS::NONE;
};

//Structs used when dealing with ReadOnly fields and ProtectedData
VORPAL_EXTERN struct ReadOnlyData {
	uintptr_t data;
	size_t size;

	VORPAL_STATUS status;
	size_t wantedSize;
};


///Vorpal Library imports
VORPAL_API VORPAL_STATUS Vorpal_Register(VorpalClient* info, char* valorid, int apiVersion);
VORPAL_API void Vorpal_Unregister(VorpalClient* info);


//Utility macros
#define initReadOnly(ro, type)ro.data = (uintptr_t) new type;\
ro.size = sizeof(type);

#define initReadOnlyProtected(ro, type)ro.data = (uintptr_t) new type;\
ro.size = sizeof(type);\
this->CloseProtected(&ro);

//C++ only
struct ProcExtraData {
	std::function<void(uintptr_t, uintptr_t)> callback;
	uintptr_t vorpal;

	uintptr_t protected_struct; size_t protected_struct_size;
	std::vector<ReadOnlyData*> readOnlyDatas; //Used for automatically closing/opening them before and after callback call
};

#endif //VORPAL_INTERNALS_H