


# VorpalLibraryEx-CPP
C++ wrapper based on VorpalLibraryEx-Interface to be used with the Vorpal Extended Library. This wrapper follows an asynchronous model which is ideal for all sorts of applications including videogames.


## Examples
Here are a few examples to get you up to speed, should you need it, if you want a project implementing the whole API check out the "example" folder.

<br />
<br />

- Initialize the library and set up the Tick()

```cpp
    #include "..\..\include\VorpalLibrary.h"
    
    //Initialize vorpal
    Vorpal v("Your valor id here");
    
    int main(){
    	//Check for initialization status   
    	if (v.GetInitializationStatus() != VORPAL_STATUS::OK) {
    		std::cout << "[-] Error initializing vorpal: " << std::hex << (int)v.GetLastStatus() << "\n";
	}
    }

    //Make sure you Tick the vorpal library somewhere that's looped.
    void aLoop(){
    	v.Tick();
    }
```
<br />
<br />

- Log a user in

```cpp
    v.Login("Peter2", "hunter3", [](Vorpal* vorpal, Protected_Login* login) {
        auto user = vorpal->GetReadOnly<std::string>(&login->Username);
        if (user.has_value()) {
            std::cout << "Username: " << user.value() << "\n";
        }
        else {
            std::cout << "[-] Error fetching username\n";

            if (vorpal->GetLastStatus() == VORPAL_STATUS::NOT_ENOUGH_MEMORY) {
                std::cout << "[?] We have allocated more memory for you, please try again...\n";
            }
        }

        //License Keys don't need open/close as they are not protected
        if (login->KeyAmount < VORPAL_MAX_LICENSEKEYS) {
            for (int i = 0; i < login->KeyAmount; ++i) {
                std::cout  << "Days Left: " << login->Keys[i].ExpiryDays << "\n";
            }
        }
        else {
            std::cout << "[-] This error shouldn't happen ever.\n";
        }
        });
```

<br />

- Fetch a variable

```cpp
    //Fetch a variable from the vorpal api, given that we are logged in
    v.GetVariable("Test", "test2", [](Vorpal* vorpal, ReadOnlyData* varData) {
        std::optional<std::string> var = vorpal->GetReadOnly<std::string>(varData);

        if (var.has_value()) {
            std::cout << "Variable: " << var.value() << "\n";
        }
        else {
            std::cout << "[-] There was an error when fetching a variable\n";

            if (vorpal->GetLastStatus() == VORPAL_STATUS::NOT_ENOUGH_MEMORY) { 
                std::cout << "[?] We have allocated more memory for you, please try again...\n";
            }
        }
    });
```
<br />
<br />

## License
TODO: Pick a license, all rights reserved for now.
