STEP 1: Open the terminal T1 to the Server folder and run the command
    
    gcc -o server server.c

STEP 2: Open another terminal T2 to the Client folder and run the command

    gcc -o client client.c

STEP 3: Place the relevant text file in the Server folder

STEP 4: Run the server first in T1 using the following command:

    ./server

STEP 5: Enter a port number(for e.g. 4444) and remember this number. The server is active now!


STEP 6: Run the client in T2 using the following command:
        ./client

STEP 7: Enter the address of the server as 127.0.0.1 and enter the port that was entered in step 5.

STEP 8: Enter the name of file to be read in T2, along with the extension(e.g. Networkingtrends.txt)


Now the first 10 characters if the file has more than 10 or n characters if the file has less than characters would be displayed on
both the terminals and there will be a file created in the Client folder with the same name that was entered with the contents
that were read from the file.
