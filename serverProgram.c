#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include <string.h> 
#include <sys/wait.h> 
  
#define bufsize 1024

void eatZombies(int n){
  // This function removes the zombie process state left
  // after the child exits. Learn about this in NWEN 301!

  wait3(NULL,WNOHANG,NULL); // Nom Nom 
}

int main(int argc, char *argv[]){
  int sock, length, msgsock, status;
  struct sockaddr_in server;

  // for forking, and cleaning up zombie child state afterwards
  // You must not change this code. 

  pid_t id;       
  signal(SIGCHLD, &eatZombies);
 
  // OK, NWEN 243 code starts here. 

  
  //lenth of server
  int length = sizeof(server);

  //char buffer[1024] = {0};
  //char *hello = "Hello from server!";

  // Create a socket (see Lab 2) - it is exactly the same for a server!
  // YOUR CODE HERE 
    //int socket(int family, int type, int protocol);
      sock = socket(AF_INET, SOCK_STREAM, 0);
        if(socket == 0){
          error("socket failure");
          return -1;
        }

  // Next, create the socket addressing structure
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(atoi(argv[1])); // this time 1st arg is port#

  // Next you need to BIND your socket.  
  // YOUR CODE HERE   

  int bind = bind(socket, INADDR_ANY, length);
  
  // Right, now we are in the main server loop.
  // YOUR CODE HERE   
  int listen = listen(socket, 5);

  // Start by listening

  while(1){
    
    // you need to accept the connection request
    int accept(socket. sockaddr *cliaddr, socklen_t *addrlen);

    // the next call makes a new child process that will actually handle the client.
    id = fork();
    
    // when id == 0, this is the child and needs to do the work for the server. 
    // when if > 0, this is the parent, and it should just loop around,
    // when id < 0, we had an error.

    // Your code here for the child process, that will read from the connection socket, process the data 
    // write back to the socket, and then close and finally call exit(0) when done.

    // Note:  make sure the parent process (id > 0) does not execute this code, but immediately loops back
    // around (via the while) to get another connection request.

  }
}