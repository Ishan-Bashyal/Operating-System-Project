ST5004CEM — Operating Systems and Security Coursework


Project Structure
task1_process_threading/
threads.c — basic multithreading
race.c — race condition demo
mutex.c — mutex synchronization (race condition fixed)
deadlock.c — deadlock demo
deadlock_fix.c — deadlock prevention (consistent lock ordering)
round_robin.c — Round Robin scheduler simulation
task2_memory_management/
fifo.c — FIFO page replacement
lru.c — LRU page replacement
compare.c — FIFO vs LRU comparison
task3_filesystem_security/
login.c — authentication (password hashing)
files.c — file operations (create/read/write/delete)
permissions.c — file permissions (owner/group/others)
encrypt.c — XOR encryption/decryption
audit.c — audit logging
audit.log — sample audit log output
task4_network_ipc/
socket_client.c / socket_server.c — basic socket client/server
protocol_client.c / protocol_server.c — request/response protocol
auth_client.c / auth_server.c — authentication + multi-client support
validation_client.c / validation_server.c — final version with data validation
Outputs/
Task1.png, Task2.png, Task3.png, Task 4 Client.png, Task 4 Server.png — screenshots of program runs
outputs_task1.txt, outputs_task2.txt, outputs_task3.txt — captured terminal output
outputs_task4_stage1.txt through outputs_task4_stage4.txt — captured output for each stage of Task 4
Build & Run

Each .c file compiles independently with:

gcc <filename>.c -o <output_name>
./<output_name>

No external libraries are required beyond the standard C library and pthreads.
