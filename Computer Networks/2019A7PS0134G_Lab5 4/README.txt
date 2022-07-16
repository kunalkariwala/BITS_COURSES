STEP 1: To compile the files, run these commands by opening the terminal to this folder

1) gcc -o server server.c
2) gcc -o client client.c

STEP 2: Open two different terminals, and change the directory to the folder where you compiled both the files

STEP 3: Run the command in terminal one:
        ./server

STEP 4: After the "SERVER IS RUNNING, WAITING FOR CLIENT TO CONNECT" is displayed on terminal 1, run the following command on Terminal 2:
        ./client

Now they're both connected!

Use the terminal 2 as the client input and view the output on the Terminal 1

If the name has the first letter as capital then the client can send a string of messages(Maximum of 2048 characters) and terminate with "."
ELSE, "." is sent automatically to terminate the session.

The messages can be at max 2048 characters in length.