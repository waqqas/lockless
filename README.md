# Lockless

A header-only library for high speed inter thread communication

Dependencies
---

- Google Benchmark (for benchmarks)
- Catch2 (unit testing)

Building on OSX
---

- `mkdir build`
- `cd build`
- ```cmake -DCMAKE_INSTALL_PREFIX:PATH=`pwd`/usr ..```
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