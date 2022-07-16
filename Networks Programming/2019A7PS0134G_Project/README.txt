This implementation allows atmost 5 clients to connect to the server. After a client's connection request
is accepted by the server, it is prompted to enter a message. After all active clients have sent a message,
the server will get a prompt to send a broadcast to all the active servers. At any instance, if a client wants 
to exit, it can type "quit" as the message.

STEP 1: Open the terminal T1 to the Server folder and run the command
    gcc -o server ./server.c -lpthread

STEP 2: Open another terminal T2 to the Client folder and run the command
    gcc -o client ./client.c 

STEP 3: Run the server first in T1 using the following command:
        ./server [PORT_NUMBER]

STEP 4: Run the client in T2 using the following command:
        ./client 127.0.0.1 [PORT_NUMBER]

STEP 5: You can open as many clients as you want in separate terminals, but at a time, the server accepts only 5

STEP 6: After being denied, the client can try again and will be accepted once there is free space.

STEP 7: There will be a prompt in every active client to enter a message

STEP 8: The entered message will be displayed in the T1

STEP 9: After the message is displayed, the cycle continues and the client asks for a message again.


