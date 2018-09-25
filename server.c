#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include <string.h> 
#include <sys/wait.h> 
#include <unistd.h>
#include <ctype.h>
  
#define bufsize 1024

void eatZombies(int n){
  // This function removes the zombie process state left
  // after the child exits. Learn about this in NWEN 301!

  wait3(NULL,WNOHANG,NULL); // Nom Nom 
}

int main(int argc, char *argv[]){
  int sock, length, msgsock, status;
  struct sockaddr_in server;
  //makes a object
  struct sockaddr_in client;
  //
  char text[1024];

  // for forking, and cleaning up zombie child state afterwards
  // You must not change this code. 

  pid_t id;       
  signal(SIGCHLD, &eatZombies);
 
  // OK, NWEN 243 code starts here. 

  // Create a socket (see Lab 2) - it is exactly the same for a server!
  // YOUR CODE HERE 

  //makes the socket
  sock = socket(AF_INET, SOCK_STREAM, 0);

  //checks to make sure that 
  if(sock < 0 ){
    fprintf(stderr,'ERROR: could not create socket as id is -1');  
  }


  // Next, create the socket addressing structure
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(atoi(argv[1])); // this time 1st arg is port#

  // Next you need to BIND your socket.  
  // YOUR CODE HERE 
  bind(sock, (const struct sockaddr*) &server, sizeof(struct sockaddr));  
  
  if(bind < 0){
   fprintf(stderr,'ERROR: bind failed');   
  }
  // Right, now we are in the main server loop.
  // YOUR CODE HERE   
  listen(sock, 5);

  // Start by listening

  while(1){
    
    socklen_t len_of_client = sizeof(client);

    // you need to accept the connection request
    int connectaccept = accept(sock, (const struct sockaddr*) &client, &len_of_client);
    if(connectaccept < 0){
      fprintf(stderr,'ERROR: accept failure');  
    }
    // the next call makes a new child process that will actually handle the client.
    id = fork();
    
    // when id == 0, this is the child and needs to do the work for the server. 
    // when if > 0, this is the parent, and it should just loop around,
    // when id < 0, we had an error.

    if(id == 0){
        int readval = read(connectaccept, text, sizeof(text));

        //iterates through the word changing each letter to uppercase
        for(int i = 0; i < strlen(text); i++){
          //changes the letter to uppercase
          text[i] = toupper(text[i]);
        }
        
        //sends the message to the client 100 seperate times so it can be reciever 100 times.
        for(int k = 0; k < 100; k++){
          //sends the message to the client
        int sendval = write(connectaccept, text, sizeof(text));
        //sleeps for 3secs inbetween 
        sleep(3);
        }
        //closes the socket
        close(sock);
        exit(0);
    }
    //if the id is lss than 0 throw an error. 
    else if(id < 0){
        fprintf(stderr, "Error: Fork failure");
    }

    // Your code here for the child process, that will read from the connection socket, process the data 
    // write back to the socket, and then close and finally call exit(0) when done.

    // Note:  make sure the parent process (id > 0) does not execute this code, but immediately loops back
    // around (via the while) to get another connection request.

  }
}