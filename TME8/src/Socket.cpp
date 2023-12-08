#include "Socket.h"


namespace pr {

    void Socket::connect(const std::string & host, int port){
        struct addrinfo * res;
        struct addrinfo * backup;
        
        if ((fd = socket(AF_INET,SOCK_STREAM,0)) == -1) {
            perror("socket");
            exit(1);
        }

        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
        hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
        hints.ai_flags = 0;
        hints.ai_protocol = 0;   
        
        char service [5]; 
        sprintf(service,"%d", port);
        int s = getaddrinfo(host.c_str(), service, &hints, &res);
        if (s != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
            exit(EXIT_FAILURE);
        }

        backup = res;

        while (res){
            if (res->ai_family == AF_INET) break;
            res = res->ai_next;
        }

        /* Etablir la connexion */
        if (::connect(fd, res->ai_addr, res->ai_addrlen) == -1) {
            ::close(fd);
            perror("connect");
            exit(1);
        }

        freeaddrinfo(backup);

    }

    void Socket::connect(in_addr ipv4, int port){
        
        struct sockaddr_in sin;
        char host[64];
        
        memset((void*)&sin, 0, sizeof(sin));
        sin.sin_addr = ipv4;
        sin.sin_family = AF_INET;
        char service [5];
        sprintf(service,"%d", port); 
        if (getnameinfo((struct sockaddr*)&sin, sizeof(sin), host, sizeof(host), service, NULL, 0) != 0) {
            perror("getnameinfo");
            exit(EXIT_FAILURE);
        }
        connect(host,port);
    }


    void Socket::close(){
        shutdown(fd,2);
        ::close(fd);
    }

    std::ostream & operator<< (std::ostream & os, struct sockaddr_in * addr){
        char host[64];
        if (getnameinfo((struct sockaddr*)addr, sizeof(*addr), host, sizeof(host), NULL, NULL, 0) != 0) {
            perror("getnameinfo");
            exit(EXIT_FAILURE);
        }
        
        return os << std::string(host) << ": " << inet_ntoa(addr->sin_addr) << " " << addr->sin_port;
    }
}

