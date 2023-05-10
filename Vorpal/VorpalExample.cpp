#include <iostream>
#include <Windows.h>
#include "Vorpal/VorpalLibrary.h"

int main()
{
    //Initialize vorpal
    Vorpal v("Your valor id here");

    //Check for initialization status
    if (v.GetInitializationStatus() != VORPAL_STATUS::OK) {
        std::cout << "[-] Error when initializing vorpal: " << std::hex << (int)v.GetLastStatus() << "\n";
    }

    
    //Grab a file from the vorpal api, given that we are logged in
    //All vorpal APIs use callbacks and are asynchronous
    v.GetFile("Test", "test2", [](uintptr_t vorpal_address, uintptr_t fileData_address){
        auto vorpal = reinterpret_cast<Vorpal*>(vorpal_address);
        auto fileData = reinterpret_cast<ReadOnlyData*>(fileData_address);

        std::optional<std::string> file = vorpal->GetReadOnly<std::string>(fileData);

        //If it doesn't have a value, there's been an issue grabbing it
        if (file.has_value()) {
            std::cout << "File: " << file.value() << "\n";
        }
        else { //Something went wrong...
            std::cout << "[-] There was an error when fetching a file: "  << std::hex << "0x" << (uint32_t)vorpal->GetLastStatus() << "\n";

            if (vorpal->GetLastStatus() == VORPAL_STATUS::NOT_ENOUGH_MEMORY) {
                //If this happens we recommend either changing VORPAL_DEFAULT_STR_CHAR_COUNT to a higher value, or changing it for this specific one (in this case Vorpal::Constructor -> initReadOnly(client.currentFile, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);)
                //^ In order to avoid having to allocate memory twice. Otherwise you can just always call this whole function again as GetReadOnly automatically allocates memory for you (on this implementation)
                std::cout << "[?] Error identified as NOT_ENOUGH_MEMORY, we have allocated more memory for you, please try again...\n";
            }
        }

    });

    v.GetVariable("Test", "test2", [](uintptr_t vorpal_address, uintptr_t varData_address) {
        auto vorpal = reinterpret_cast<Vorpal*>(vorpal_address);
        auto varData = reinterpret_cast<ReadOnlyData*>(varData_address);

        std::optional<std::string> var = vorpal->GetReadOnly<std::string>(varData);

        if (var.has_value()) {
            std::cout << "Variable: " << var.value() << "\n";
        }
        else {
            std::cout << "[-] There was an error when fetching a variable: " << std::hex << "0x" << (uint32_t)vorpal->GetLastStatus() << "\n";

            if (vorpal->GetLastStatus() == VORPAL_STATUS::NOT_ENOUGH_MEMORY) { 
                std::cout << "[?] Error identified as NOT_ENOUGH_MEMORY, we have allocated more memory for you, please try again...\n";
            }

        }
    });


    //Functions that use protected fields, require manual handling, don't worry we made it easy for you
    v.GetApplication("appId", [](uintptr_t vorpal_address, uintptr_t app_address) {
        auto vorpal = reinterpret_cast<Vorpal*>(vorpal_address);
        Protected_Application* app = reinterpret_cast<Protected_Application*>(app_address);

        //Before using protected fields, we have to open them.
        vorpal->OpenProtected(app->Domain);

        auto name = vorpal->GetReadOnly<std::string>(&app->Domain);
        if (name.has_value()) {
            std::cout << "Domain: " << name.value() << "\n";
        }
        else {
            std::cout << "[-] Error fetching program domain: " << std::hex << "0x" << (uint32_t)vorpal->GetLastStatus() << "\n";

            if (vorpal->GetLastStatus() == VORPAL_STATUS::NOT_ENOUGH_MEMORY) {
                //If this happens we recommend either changing VORPAL_DEFAULT_STR_CHAR_COUNT to a higher value, or changing it for this specific one (in this case Vorpal::Constructor -> initReadOnlyProtected(client.app.Domain, char[VORPAL_DEFAULT_STR_CHAR_COUNT]);)
                //^ In order to avoid having to allocate memory twice. Otherwise you can just always call this whole function again as GetReadOnly automatically allocates memory for you (on this implementation)
                std::cout << "[?] Error identified as NOT_ENOUGH_MEMORY, we have allocated more memory for you, please try again...\n";
            }
        }

        //Don't forget to close
        vorpal->CloseProtected(app->Domain);
    });

    v.Login("username", "password", [](uintptr_t vorpal_address, uintptr_t login_address) {
        auto vorpal = reinterpret_cast<Vorpal*>(vorpal_address);
        auto login = reinterpret_cast<Protected_Login*>(login_address);

        //Before using protected fields, we have to open them.
        vorpal->OpenProtected(login->Username);

        auto user = vorpal->GetReadOnly<std::string>(&login->Username);
        if (user.has_value()) {
            std::cout << "Username: " << user.value() << "\n";
        }
        else {
            std::cout << "[-] Error fetching username: " << std::hex << "0x" << (uint32_t)vorpal->GetLastStatus() << "\n";

            if (vorpal->GetLastStatus() == VORPAL_STATUS::NOT_ENOUGH_MEMORY) {
                std::cout << "[?] Error identified as NOT_ENOUGH_MEMORY, we have allocated more memory for you, please try again...\n";
            }
        }

        //Don't forget to close
        vorpal->CloseProtected(login->Username);


        //License Keys don't need open/close as they are not protected
        if (login->KeyAmount < VORPAL_MAX_LICENSEKEYS) {
            for (int i = 0; i < login->KeyAmount; ++i) {
                std::cout << "APP: " << login->Keys[i].ApplicationName << " License Key: " << login->Keys[i].License << " Days Left: " << login->Keys[i].ExpiryDays << "\n";
            }
        }
        else {
            std::cout << "[-] This error shouldn't happen ever.\n";
        }


        });

    v.LoginApplication("appId", [](uintptr_t vorpal_address, uintptr_t loginApp_address) {
        auto vorpal = reinterpret_cast<Vorpal*>(vorpal_address);
        auto loginApp = reinterpret_cast<Protected_Login*>(loginApp_address);

        //Before using protected fields, we have to open them.
        vorpal->OpenProtected(loginApp->Username);

        auto user = vorpal->GetReadOnly<std::string>(&loginApp->Username);
        if (user.has_value()) {
            std::cout << "Username: " << user.value() << "\n";
        }
        else {
            std::cout << "[-] Error fetching username: " << std::hex << "0x" << (uint32_t)vorpal->GetLastStatus() << "\n";

            if (vorpal->GetLastStatus() == VORPAL_STATUS::NOT_ENOUGH_MEMORY) {
                std::cout << "[?] Error identified as NOT_ENOUGH_MEMORY, we have allocated more memory for you, please try again...\n";
            }
        }

        //Don't forget to close
        vorpal->CloseProtected(loginApp->Username);
    });

    while (true) {
        v.Tick(); //Make sure to tick this somewhere
        Sleep(20);
    }
}
