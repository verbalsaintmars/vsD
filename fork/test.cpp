/*
 * Before Fork:
 *    1. setting signal handler
 *    2. close unused fd
 *    3. setting thread handler
 * In Fork:
 *    1. Main Process continue running(daemon)
 * After Fork:
 *    1. Main Process
 *       1. Get child pid info , update information about child
 *       2. Test coomunication through
 *          * DBUS
 *          * tcp
 *       3. Receive info from child
 *       4. Prepare report structure , monitor childs
 *          * How many SO are running, 1 so 1 child
 *          * so's status
 *       5. If Main dies, sighup to all childs
 *       6. Create Response inferface so for vsD client to communicate.
 *          Main Process will monitor this Interface, if down, re-create one.
 *    2. Child Process
 *       1. Start up heartbeat
 *       2. Report back to mainship
 *       3. multi-thread start
 *       4. loadso
 *       5. main thread report to mainship
 *       6. if receiving sighup, notify so, then self-killed
 *
 */
