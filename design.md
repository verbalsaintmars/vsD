vsD:
   Send:
      .so name
      .so hash
      .so expected version
      status report : standalone, report, heartbeat(only)
      child run_time lease.
      Force close child
      Random UUID that vsD talk with Child

Child:
   return:
      .so name
      .so hash (vsD will compare, if ok, Child continue)
      run .so get Version (vsD will compare version, if ok, continue)
      Startup report engine, heartbeat engine, or none.
      Maintain lease.
      Close mechenism

----------------
Child:
   Send:
      request to open a new .so
         1. so name , so hash, so version , runtime lease

vsD:
   Start up .so
   Pass in status report as standalone.
   Maintain a tunnel with new .so and requested child.

----------------
vsD broadcast signal to children


