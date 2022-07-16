This implementation allows atmost 5 clients to connect to the server. At any instance, if a client wants 
to exit, it can type "quit" as the message. If using a linux machine, kindly comment out line number 28 in
client.c, it was added to deal with an edge case that arises if the user presses ctrl+c without typing in quit.

STEP 1: Open the terminal T1 to the Server folder and run the command
    gcc -o server ./server.c -lpthread

STEP 2: Open another terminal T2 to the Client folder and run the command
    gcc -o client ./client.c 

STEP 3: Run the server first in T1 using the following command:
        ./server [PORT_NUMBER]

STEP 4: Run the client in T2 using the following command:
        ./client 127.0.0.1 [PORT_NUMBER] if using client on the same machine 
        and 
        ./client [IP_server] [PORT_NUMBER] if using client on different machine

STEP 5: You can open as many clients as you want in separate terminals, but at a time, the server accepts only 5

STEP 6: After being denied, the client can try again and will be accepted once there is free space.

STEP 7: There will be a prompt in every active client to enter a file name

STEP 8: The file with the entered filename will be downloaded and saved to the local directory of the client if it exists at the server

STEP 9: After the message is displayed, the cycle continues and the client asks for a file name again.


