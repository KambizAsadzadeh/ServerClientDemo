# Modern Project-Template (PT)
A very simple server and client demonstrates.

## Building

- You need CMake tool for building source code
- CMake 3.23 or higher is required.

```
cd build
cmake ..
make
./SimpleServerClient

```

> How to config for server and client?
- if you want compile it for server only, then set macro as below:

```
-DCOMPILE_AS_SERVER=true
-DCOMPILE_AS_CLIENT=false
```
Otherwise you can compile it for client only line this:
```
-DCOMPILE_AS_SERVER=false
-DCOMPILE_AS_CLIENT=true
```
