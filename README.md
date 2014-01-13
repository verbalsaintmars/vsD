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
1. Create a directory for build result.
   
   e.g:
```bash
mkdir /tmp/build
```

2. go into the directory and cmake the src out of it
   
   e.g:
```bash
cd /tmp/build
cmake -G Ninja /path/to/the/vsD/source
```

3. vsD uses Ninja for building process, make sure your Ninja has been installed.

   execute ninja under /tmp/build
```bash
ninja
```

4. the main vsD binary executble is under
   **/tmp/build/bin**
   the test binary executables is under
   **/tmp/build/test_bin**

# TODO List

## P0:
1. [x] cmake files
2. Dynamic Load Library Module : dynamic library loading mechenism
3. Hopscotch hashing library (for nodes lookup)
4. thread library

## P1:
1. IPC component :
      zeroMQ
      protocol buffer
2. nodes interaction

## P2:
1. Ranking component :
     * Host Information component
     * Algorithm of ranking

##P3:
1. https://code.google.com/p/google-glog/ integration
2. https://code.google.com/p/gflags/ integration

