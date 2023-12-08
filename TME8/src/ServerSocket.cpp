#include "ServerSocket.h"

namespace pr {

    ServerSocket::ServerSocket(int port){
        // struct sockaddr_in sin; /* Nom de la socket de connexion */
        
        /* creation de la socket */
        if ((socketfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
            perror("socket"); exit(1);
        }
        
        /* memset((char *)&sin,0, sizeof(sin));
        sin.sin_addr.s_addr = htonl(INADDR_ANY);
        sin.sin_port = htons(port);
        sin.sin_family = AF_INET; */

        struct addrinfo  hints;
        struct addrinfo  *result;
        int s;

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
        hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
        hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

        char tservice[5];
        char * service =tservice;
        sprintf(service, "%d", port);
    
        if(port) 
        {    s = getaddrinfo(NULL, service, &hints, &result);
            if (s != 0) {
                fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
                exit(EXIT_FAILURE);
            }
        }
        else {
            s = getaddrinfo(NULL, "", &hints, &result);
            if (s != 0) {
                fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
                exit(EXIT_FAILURE);
            }

        }
    
        /* nommage */
        if (bind(socketfd,result->ai_addr,result->ai_addrlen) < 0) {
            perror("bind");
            exit(1);
        }

        struct sockaddr* addr;
        socklen_t len = sizeof( struct sockaddr_in);
        getsockname(socketfd, addr,&len);


        std::cout<<"Using port :"<< ntohs(((sockaddr_in*)addr)->sin_port) <<std::endl;
        listen(socketfd, 5); 
    }

    Socket ServerSocket::accept(){

        int scom; /* Socket de communication */
        struct sockaddr exp;
        int fromlen = sizeof(exp);
        
        if ((scom = ::accept(socketfd, (struct sockaddr *)&exp, (socklen_t*) &fromlen))== -1) {
            perror("accept"); 
            exit(3);
        }
        return Socket(scom);
    }

	void ServerSocket::close(){
        shutdown(socketfd,2);
        ::close(socketfd);
    }
}