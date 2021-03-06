#ifndef __SERVER_H__
#define __SERVER_H__

#include <sys/select.h>
#include <sys/ioctl.h>
#include "thr_pool.h"

#define PORT_NUMBER 8080
#define LISTENQ     1024

/* Information structure for file descriptor (FD) sets */
typedef struct fileDescriptorPool {
    int maxfd;                  /* Max value of FD in all sets */
    fd_set read_set;            /* fd_set of active FDs to read from */
    int clientfd[FD_SETSIZE];   /* Set of active FDs */
    struct sockaddr_in clientAddr[FD_SETSIZE]; /* Address of active clients */
    int maxi;                   /* Max index used in clientfd */
    fd_set ready_set;           /* fd_set of FDs ready to be read */
    int nready;                 /* Number of FDs ready to be read */
} fileDescriptorPool;

/*
 * Function: openNBServerSock()
 * Open non-blocking socket and listen for client request
 * Return non-blocking listening socket descriptor
 */
int openNBServerSock(int portNum);

/*
 * Function: initPool()
 * Initialize pool structure
 */
void initPool(int sockfd, fileDescriptorPool* fdPool);

/*
 * Function: addClient()
 * Add client to read fd set
 * Store its IP address and port
 */
void addClient(int sockfd, struct sockaddr_in* clientAddr,
    fileDescriptorPool* fdPool);

/*
 * Function: handleClientFds()
 * Handle client fds ready to be read
 */
void handleClientFds(fileDescriptorPool* fdPool, threadPool* thrPool,
    unsigned int* assignedThrId);

/*
 * Function: handleClientRequest()
 * Handle each client request by adding task to task queue
 */
void handleClientRequest(int clientSock, struct sockaddr_in* clientAddr,
    threadPool* thrPool, unsigned int assignedThrId);

/*
 * Function: httpResponse()
 * Response to HTTP request from client
 */
void httpResponse(void* sockfd);

#endif  /*__SERVER_H__*/
