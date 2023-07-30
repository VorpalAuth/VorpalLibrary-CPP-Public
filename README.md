# VorpalLibraryEx-CPP
C++ wrapper based on VorpalLibraryEx-Interface to be used with the Vorpal Extended Library.


## Examples
Here are a few examples to get you up to speed, should you need it, if you want a project implementing the whole API check out the "example" folder.

- Initialize the library
```cpp
    #include "..\..\include\VorpalLibrary.h"
    
    //Initialize vorpal
    Vorpal v("Your valor id here");
    
    //Check for initialization status   
    if (v.GetInitializationStatus() != VORPAL_STATUS::OK) {
        std::cout << "[-] Error when initializing vorpal: " << std::hex << (int)v.GetLastStatus() << "\n";
    }
```

- Log a user in
```cpp
    v.Login("Peter2", "hunter3", [](Vorpal* vorpal, Protected_Login* login) {
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

        //License Keys don't need open/close as they are not protected
        if (login->KeyAmount < VORPAL_MAX_LICENSEKEYS) {
            for (int i = 0; i < login->KeyAmount; ++i) {
                std::cout << "APP: " << login->Keys[i].ApplicationName << " License Key: " << login->Keys[i].License << " Days Left: " << login->Keys[i].ExpiryDays << "\n";
            }
        }
        else {
            std::cout << "[-] This error shouldn't happen ever.\n" << login->KeyAmount;
        }
        });
```

- Fetch a variable
```cpp
    //Fetch a variable from the vorpal api, given that we are logged in
    v.GetVariable("Test", "test2", [](Vorpal* vorpal, ReadOnlyData* varData) {
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
```

## License
TODO: Pick a license, all rights reserved for now.

