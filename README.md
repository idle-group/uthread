# uthread-A User Space Threading Library Supporting Multi-Core Systems
---
- Lightweight user threads with support for blocking IO and fast context switching (ie. similar to Erlang or Go but using C)
- Fast, scalable load balancing across multiple cores
- Lock-free data structures
- Supports x86 and x86_64. Further architectures can be added easily.
- Supports native event backends on Linux and Solaris
- Supports libev event backend
---
## Motivation
- Why Events Are A Bad Idea (for high-concurrency servers) - Rob von Behren, Jeremy Condit, and Eric Brewer
    - Specifically, the following quote summarizes nicely: "...the duality argument of Lauer and Needham ... implies that good implementations of thread systems and event systems will have similar performance."
---
## Building
- Type 'make' to build the library and run the unit tests
- Link your application to libfiber.so
- Be sure to define the architecture when including libfiber's headers. You can specify the following gcc flags:
    - For x86 64 bit: -m64 -DARCH_x86_64
    - For x86 32 bit: -m32 -march=i686 -DARCH_x86
- libfiber.so overrides many system calls so make sure you know what you're doing
- The makefile will attempt to detect gcc split stack support (Go uses this). This requires gcc 4.7 or higher. I recommend using this.
    - make CC=gcc-4.7
