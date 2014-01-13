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

# TODO List

## P0:
- ~~cmake files~~
- Dynamic Load Library Module : dynamic library loading mechenism
- Hopscotch hashing library (for nodes lookup)
- thread library

## P1:
- IPC component :
      zeroMQ
      protocol buffer
- nodes interaction

## P2:
- Ranking component :
   Host Information component
   Algorithm of ranking

##P3:
- https://code.google.com/p/google-glog/ integration
- https://code.google.com/p/gflags/ integration

