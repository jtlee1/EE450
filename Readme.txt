
a)Name: Justin Lee
b)Student ID: 4109118270
c)I finish all the required part but did not do the optional part.
d)
Makefile:Supports make all(compile all required code) and make clean(remove exe files)
client.cpp:Get instructions and pass to serverM. Recieve output from serverM and print.
monitor.cpp:Get instructions and pass to serverM. Recieve output from serverM and print.
serverM.cpp:Main server. Get instructions from client and monitor, gather data from serverA-C. Do all the data processing and send the result back to client/monitor(send update to serverA-C when needed).
serverA-C: server that have access to database(block1-3) pass data to serverM if request.
e)
instructions pass to client/monitor by user input.
client/monitor pass the instructions directly to serverM.
serverM encrypt the command(names) and pass the encrypted command(request) to serverA-C.
serverA-C pass back the data from block1-3.
serverM manage the data (pass update to serverA-C if needed).
serverM decrypt the names and pass the results to client.(for client command)
client print the result.(for client command)
g)This project should not fail.
h)
Cite:
TCP socket code from https://www.geeksforgeeks.org/socket-programming-cc/
parsing code from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c reply 102
sort code from https://www.geeksforgeeks.org/sorting-2d-vector-in-c-set-1-by-row-and-column/
encrypt code from https://stackoverflow.com/questions/12557135/converting-simple-c-encryption-to-c
    UDP socket code from https://www.geeksforgeeks.org/udp-server-client-implementation-c/
clear empty line code from https://stackoverflow.com/questions/41717167/erase-empty-lines-from-a-text-file-in-c
read text code from tutorial https://shengyu7697.github.io/cpp-read-text-file/ last 2 image
get write txt code from https://stackoverflow.com/questions/6932409/writing-a-string-to-the-end-of-a-file-c




