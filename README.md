# cstring.h

String and String array implementation in pure C99


## Requirements
- C99 or newer gcc compiler
- That's it?
## Usage

- Clone the repo in your third party folder or simply get it via curl


    - With git
    ```bash
    git clone https://github.com/mirsahebali/cstring.h
    ```

    - Or with wgeg
    ```bash
    wget https://raw.githubusercontent.com/mirsahebali/cstring.h/refs/heads/main/cstring.h
     
     ``` 
    - Or with curl

    ```bash

    curl -O https://raw.githubusercontent.com/mirsahebali/cstring.h/refs/heads/main/cstring.h

    ```


- First define implementation before including the file, then put the include it in your required file

**add it to the end or at last of your all of your includes** 
```c
#define CSTRING_IMPLEMENTATION
#include "cstring.h"

```

- Don't forget to free the strings and array after done using them with:

```c

free_string(&foo_string);
free_string_array(&foo_string_array);

```


> [!IMPORTANT]
> Also free the bindings if they were heap allocated else leave it be as the stack will clean it up
> - Be careful of the `lifetimes` of each string you allocate



> [!NOTE]
> - I have tried to handle as much errors and edge cases as possible and update it on the go based on requirements
> - I have added asserts all around the projects, so they may vanish in release mode
> - This may or may not be production ready to use it at your own caution
> It is recommended to use this with memory arenas/bump allocators


Check [usage here](USAGE.md) 
