#pragma once
#include "Internals/VorpalStructs.h"
#include <queue>
#include <chrono>

struct Vorpal {
private:
	VorpalClient client; //Vorpal client interface, you don't have to touch this
	std::queue<std::pair<Proc*, ProcExtraData>> callbacks;
	VORPAL_STATUS initStatus;
	VORPAL_STATUS lastStatus;

public:

	VORPAL_STATUS GetInitializationStatus() {
		return this->initStatus;
	}

	VORPAL_STATUS GetLastStatus() {
		return this->lastStatus;
	}

	void GetApplication(std::string appId, std::function<void(Vorpal*, Protected_Application*)> fn) {
		constexpr uint32_t procId = 0x6832ab00U;

		ProcArgs theargs = { {} };
		memcpy_s(theargs.args[0].arg_s, 25, appId.c_str(), appId.size() + 1);



		Protected_Application* app = &this->client.app;
		size_t app_size = this->client.app_size;

		std::vector<ReadOnlyData*> autoCloseFields = { //We will automatically open and close these fields then the callback gets called, freeing up the user from this arduous task
			&app->Result,
			&app->Name,
			&app->Domain,
			&app->Version,
			&app->Login,
			&app->Key,
			&app->HWID,
			&app->Maintenance,
			&app->Developer,
			&app->AntiDebug,
			&app->AntiVM
		};

		this->InvokeProcAsync(procId, theargs, *static_cast<std::function<void(uintptr_t, uintptr_t)>*>(static_cast<void*>(&fn)), reinterpret_cast<uintptr_t>(app), app_size, autoCloseFields);
	}

	void Login(std::string user, std::string password, std::function<void(Vorpal*, Protected_Login*)> fn) {
		constexpr uint32_t procId = 0xf8050339U;

		ProcArgs theargs = { {} };
		memcpy_s(theargs.args[0].arg_s, 25, user.c_str(), user.size() + 1);
		memcpy_s(theargs.args[1].arg_s, 25, password.c_str(), password.size() + 1);



		Protected_Login* login = &this->client.login;
		size_t login_size = this->client.login_size;

		std::vector<ReadOnlyData*> autoCloseFields = { //We will automatically open and close these fields then the callback gets called, freeing up the user from this arduous task
			&login->HashedID,
			&login->Username,
			&login->Email,
			&login->Status,
			&login->Rank
		};

		this->InvokeProcAsync(procId, theargs, *static_cast<std::function<void(uintptr_t, uintptr_t)>*>(static_cast<void*>(&fn)), reinterpret_cast<uintptr_t>(&this->client.login), this->client.login_size, autoCloseFields);
	}

	void LoginApplication(std::string appId, std::function<void(Vorpal*, Protected_LoginApplication*)> fn) {
		constexpr uint32_t procId = 0xa5b17bdU;

		ProcArgs theargs = { {} };
		memcpy_s(theargs.args[0].arg_s, 25, appId.c_str(), appId.size() + 1);


		Protected_LoginApplication* loginApp = &this->client.loginApp;
		size_t loginApp_size = this->client.loginApp_size;

		std::vector<ReadOnlyData*> autoCloseFields = { //We will automatically open and close these fields then the callback gets called, freeing up the user from this arduous task
			&loginApp->Result,
			&loginApp->HashedID,
			&loginApp->Username,
			&loginApp->Email,
			&loginApp->Status,
			&loginApp->Rank,
			&loginApp->Key,
			&loginApp->HWID,
		};

		this->InvokeProcAsync(procId, theargs, *static_cast<std::function<void(uintptr_t, uintptr_t)>*>(static_cast<void*>(&fn)), reinterpret_cast<uintptr_t>(loginApp), loginApp_size, autoCloseFields);
	}



	void Register(std::string username, std::string password, std::string email, std::function<void(Vorpal*, Protected_LoginApplication*)> fn) {
		constexpr uint32_t procId = 0x839c6e6e;

		ProcArgs theargs = { {} };
		memcpy_s(theargs.args[0].arg_s, 25, username.c_str(), username.size() + 1);
		memcpy_s(theargs.args[1].arg_s, 25, password.c_str(), password.size() + 1);
		memcpy_s(theargs.args[2].arg_s, 25, email.c_str(), email.size() + 1);


		Protected_LoginApplication* loginApp = &this->client.loginApp;
		size_t loginApp_size = this->client.loginApp_size;

		std::vector<ReadOnlyData*> autoCloseFields = { //We will automatically open and close these fields then the callback gets called, freeing up the user from this arduous task
			&loginApp->Result,
			&loginApp->HashedID,
			&loginApp->Username,
			&loginApp->Email,
			&loginApp->Status,
			&loginApp->Rank,
			&loginApp->Key,
			&loginApp->HWID,
		};

		this->InvokeProcAsync(procId, theargs, *static_cast<std::function<void(uintptr_t, uintptr_t)>*>(static_cast<void*>(&fn)), reinterpret_cast<uintptr_t>(loginApp), loginApp_size, autoCloseFields);
	}

	void RedeemLicense(std::string license, std::function<void(Vorpal*, Protected_LoginApplication*)> fn) {
		constexpr uint32_t procId = 0xb3431b91;

		ProcArgs theargs = { {} };
		memcpy_s(theargs.args[0].arg_s, 25, license.c_str(), license.size() + 1);

		//Protected struct handling
		Protected_LoginApplication* loginApp = &this->client.loginApp;
		size_t loginApp_size = this->client.loginApp_size;

		std::vector<ReadOnlyData*> autoCloseFields = { //We will automatically open and close these fields then the callback gets called, freeing up the user from this arduous task
			&loginApp->Result,
			&loginApp->HashedID,
			&loginApp->Username,
			&loginApp->Email,
			&loginApp->Status,
			&loginApp->Rank,
			&loginApp->Key,
			&loginApp->HWID,
		};

		this->InvokeProcAsync(procId, theargs, *static_cast<std::function<void(uintptr_t, uintptr_t)>*>(static_cast<void*>(&fn)), reinterpret_cast<uintptr_t>(loginApp), loginApp_size, autoCloseFields);
	}

	void GetChangelogs(std::string appId) {
		ProcArgs theargs = { {} };
		memcpy_s(theargs.args[0].arg_s, 25, appId.c_str(), appId.size() + 1);

		//Vorpal_InvokeProc(this->client.inst, 0x5ff79718U, &theargs);
		
	}

	__forceinline void GetVariable(std::string key, std::string appId, std::function<void(Vorpal*, ReadOnlyData*)> fn) {
		constexpr uint32_t procId = 0x3d7d6bc9U;

		ProcArgs theargs = { {} };
		memcpy_s(theargs.args[0].arg_s, 25, key.c_str(), key.size() + 1);
		memcpy_s(theargs.args[1].arg_s, 25, appId.c_str(), appId.size() + 1);

		this->InvokeProcAsync(procId, theargs, *static_cast<std::function<void(uintptr_t, uintptr_t)>*>(static_cast<void*>(&fn)), reinterpret_cast<uintptr_t>(&this->client.currentVar));
	}

	__forceinline void GetFile(std::string key, std::string appId, std::function<void(Vorpal*, ReadOnlyData*)> fn) {
		constexpr uint32_t procId = 0x1be3f8afU;

		ProcArgs theargs = { {} };
		memcpy_s(theargs.args[0].arg_s, 25, key.c_str(), key.size() + 1);
		memcpy_s(theargs.args[1].arg_s, 25, appId.c_str(), appId.size() + 1);

		this->InvokeProcAsync(procId, theargs, *static_cast<std::function<void(uintptr_t, uintptr_t)>*>(static_cast<void*>(&fn)), reinterpret_cast<uintptr_t>(&this->client.currentFile));
	}

	void CloseProtected(uintptr_t p, size_t siz) {
		ProcArgs theargs = { {} };
		theargs.args[0].arg_ull = p;
		theargs.args[1].arg_ull = siz;

		this->InvokeProc(0x8722e8e0U, theargs);
	}

	void OpenProtected(uintptr_t p, size_t siz) {
		ProcArgs theargs = { {} };
		theargs.args[0].arg_ull = p;
		theargs.args[1].arg_ull = siz;

		this->InvokeProc(0x21051ccaU, theargs);
	}

	void OpenProtected(ReadOnlyData* d) {
		ProcArgs theargs = { {} };
		theargs.args[0].arg_ull = reinterpret_cast<uintptr_t>(d);

		this->InvokeProc(0x870689b4U, theargs);
	}

	void CloseProtected(ReadOnlyData* d) {
		ProcArgs theargs = { {} };
		theargs.args[0].arg_ull = reinterpret_cast<uintptr_t>(d);

		this->InvokeProc(0xe6457fdU, theargs);
	}

	Vorpal(std::string brandId) {
		this->initStatus = Vorpal_Register(&client, (char*)brandId.c_str(), VORPAL_API_VERSION);
		//Sleep(20000); MOVER BEHIND THE REGISTER ITSELF
		if (this->initStatus != VORPAL_STATUS::OK) {
			return;
		}

		initReadOnly(client.currentFile, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);
		initReadOnly(client.currentVar, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);

		//ProtectedStructs now
		//Application
		client.app_size = sizeof(Protected_Application);

		initReadOnlyProtected(client.app.Domain, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);
		initReadOnlyProtected(client.app.Name, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);
		initReadOnlyProtected(client.app.Version, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);
		initReadOnlyProtected(client.app.Login, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);
		initReadOnlyProtected(client.app.Key, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);

		initReadOnlyProtected(client.app.HWID, bool);
		initReadOnlyProtected(client.app.Maintenance, bool);
		initReadOnlyProtected(client.app.Developer, bool);
		initReadOnlyProtected(client.app.AntiDebug, bool);
		initReadOnlyProtected(client.app.AntiVM, bool);
		initReadOnlyProtected(client.app.Result, bool);

		//LoginApplication
		client.loginApp_size = sizeof(Protected_LoginApplication);

		initReadOnlyProtected(client.loginApp.HashedID, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);
		initReadOnlyProtected(client.loginApp.Username, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);
		initReadOnlyProtected(client.loginApp.Email, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);
		initReadOnlyProtected(client.loginApp.Status, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);
		initReadOnlyProtected(client.loginApp.Rank, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);
		initReadOnlyProtected(client.loginApp.Key, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);
		initReadOnlyProtected(client.loginApp.HWID, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);

		initReadOnlyProtected(client.loginApp.Result, bool);
		//Login
		client.login_size = sizeof(Protected_Login);

		initReadOnlyProtected(client.login.HashedID, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);
		initReadOnlyProtected(client.login.Username, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);
		initReadOnlyProtected(client.login.Email, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);
		initReadOnlyProtected(client.login.Status, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);
		initReadOnlyProtected(client.login.Rank, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);

		this->CloseProtected(reinterpret_cast<uintptr_t>(&client.app), sizeof(Protected_Application));
	}


	template <typename T>
	__forceinline std::optional<T> GetReadOnly(ReadOnlyData* ro) {

		this->lastStatus = ro->status;

		if (ro->status != VORPAL_STATUS::OK) {
			switch (ro->status) {
				case VORPAL_STATUS::NOT_ENOUGH_MEMORY: { //Our string is too small, always handle this properly just in case.
					//Allocate more memory
					free((void*)ro->data);
					ro->data = (uintptr_t)malloc(ro->wantedSize);

					//Update size
					ro->size = ro->wantedSize;

					//You should try again
					return std::nullopt;
					break;
				}
			}
		}

		if constexpr (std::is_same<T, std::string>::value) {
			return reinterpret_cast<char*>(ro->data);
		}
		else {
			return *reinterpret_cast<T*>(ro->data);
		}
	}



	void Tick() {
		if (!this->callbacks.empty()) {
			
			auto front = this->callbacks.front();
			auto procData = front.first;
			auto procExtra = front.second;

			if (front.first->status == VORPAL_STATUS::DONE) {
				if (procExtra.protected_struct != 0) { //0 means not needed and not inside a protected struct
					this->OpenProtected(procExtra.protected_struct, procExtra.protected_struct_size);
				}
				
				//Open every relevant readonlydata
				for (ReadOnlyData* ro : procExtra.readOnlyDatas) {
					this->OpenProtected(ro);
				}

				procExtra.callback(procExtra.vorpal, procExtra.protected_struct);

				//Close every relevant readonlydata after we are done
				for (ReadOnlyData* ro : procExtra.readOnlyDatas) {
					this->CloseProtected(ro);
				}

				//Reset after we done
				front.first->status = VORPAL_STATUS::NONE;

				this->callbacks.pop();

				if (procExtra.protected_struct != 0) { //0 means not needed and not inside a protected struct
					this->CloseProtected(procExtra.protected_struct, procExtra.protected_struct_size);
				}
			}
		}
	}

	VORPAL_STATUS InvokeProcAsync(std::uint32_t proc, ProcArgs args, std::function<void(uintptr_t, uintptr_t)> callback, uintptr_t protected_struct = 0, uintptr_t protected_struct_size = 0, std::vector<ReadOnlyData*> readOnlyDatas = {}) {
		for (int i = 0; i < 16; ++i) {
			Proc* procData = &this->client.vorpalProcs[i];
			if (procData->status == VORPAL_STATUS::NONE) {
				procData->proc = proc;
				procData->status = VORPAL_STATUS::BUSY;
				procData->args = args;

				ProcExtraData extra;
				extra.vorpal = reinterpret_cast<uintptr_t>(this);
				extra.protected_struct = protected_struct;
				extra.protected_struct_size = protected_struct_size;
				extra.readOnlyDatas = readOnlyDatas;
				extra.callback = callback;

				callbacks.push(std::make_pair(procData, extra));
				return VORPAL_STATUS::OK;
			}
			else if (i == 15) {
				return VORPAL_STATUS::FULL;
			}
		}

		//Should never reach here...
		return VORPAL_STATUS::NONE;
	}

	VORPAL_STATUS InvokeProc(std::uint32_t proc, ProcArgs args) {
		for (int i = 0; i < 16; ++i) {
			Proc* procData = &this->client.vorpalProcs[i];
			if (procData->status == VORPAL_STATUS::NONE) {
				procData->proc = proc;
				procData->status = VORPAL_STATUS::BUSY;
				procData->args = args;

				//Wait for operation to be done
				std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
				while (true) {
					if (procData->status == VORPAL_STATUS::DONE) {
						//Reset status
						procData->status = VORPAL_STATUS::NONE;
						return VORPAL_STATUS::OK;
					}

					std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
					if (std::chrono::duration_cast<std::chrono::milliseconds>(now - begin).count() > 5000) {
						//Give up
						procData->status = VORPAL_STATUS::NONE;
						return VORPAL_STATUS::TIMED_OUT;
					}
				}
			}
			else if (i == 15) {
				return VORPAL_STATUS::FULL;
			}
		}

		//Should never reach here...
		return VORPAL_STATUS::NONE;
	}

};


