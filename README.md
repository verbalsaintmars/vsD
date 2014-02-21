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
   execute ninja under **/tmp/build**
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
2. [x] Dynamic Load Library Module : dynamic library loading mechenism
3. Integrate. Main.cpp
4. DBUS for IPC **
   1. vsD register to session bus. If ok, fork with new process with dbus info passed in.
   2. with universal Container to monitor child process from dbus/0mq
   3. iff an executable, take advantage of dbus activation mechanism
5.
   1. coredump/chkEnv
   2. sigwait for child
   3. Child's disposition, disestablish then raise again

6.
   privilege :
   1. raise/decrease privilege in setuid mode

7. zeroMQ + http://kentonv.github.io/capnproto/
8. Android NDK compile and run on Android device
9. nodes interaction
10. https://code.google.com/p/gflags/ integration

## P1:
1. (Delay)Hopscotch hashing library implement (for nodes lookup)

## P2:
1. Ranking component :
     * Host Information component
     * Algorithm of ranking

##P3:
1. https://code.google.com/p/google-glog/ integration

