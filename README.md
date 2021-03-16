# Lockless

A header-only library for high speed inter thread communication

Dependencies
---

- Google Benchmark (for benchmarks)

Building on OSX
---

- `mkdir build`
- `cd build`
- ```cmake -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl -DCMAKE_INSTALL_PREFIX:PATH=`pwd`/usr ..```
- `cmake --build . --config Release --target install -- -j $(nproc)`

Running tests
---

- `./tests/tests`


Usage
---

Steps

```
#include "lockless/lockless.hpp"


```