# vsD

Light weight reliable daemon acts as nodes handling dynamic loading modules
to do it's jobs.

## Main Purpose

* React smart with client command.
* No Figure Head. Figure head is dynamically ranked by algorithm
* Auto-deploy , load balancing

## Language , tools vsD uses

* C++11/1y
* boost mpl graph regex (appeneding)
* g++ 4.9
* cmake
* ninja
* zeroMQ
* protocol buffer
* gflag
* glog

# Build
-  Create a directory for build result.
   e.g:
```bash
mkdir /tmp/build
```

-  go into the directory and cmake the src out of it
   e.g:
```bash
cd /tmp/build
cmake -G Ninja /path/to/the/vsD/source
```

-  vsD uses Ninja for building process, make sure your Ninja has been installed
```bash
ninja
```

-  the main vsD binary executble is under /tmp/build/bin
   the test binary executables is under /tmp/build/test_bin

# TODO List

## P0:
-  [X]cmake files
-  Dynamic Load Library Module : dynamic library loading mechenism
-  Hopscotch hashing library (for nodes lookup)
-  thread library

## P1:
-  IPC component :
      zeroMQ
      protocol buffer
-  nodes interaction

## P2:
-  Ranking component :
      Host Information component
      Algorithm of ranking

##P3:
-  https://code.google.com/p/google-glog/ integration
-  https://code.google.com/p/gflags/ integration

