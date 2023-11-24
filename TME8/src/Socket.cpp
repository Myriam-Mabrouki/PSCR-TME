#include "Socket.h"


namespace pr {

    void Socket::connect(const std::string & host, int port){
        struct addrinfo * res;
        struct addrinfo * backup;
        
        if ((fd = socket(AF_INET,SOCK_STREAM,0)) == -1) {
            perror("socket");
            exit(1);
        }
        
        getaddrinfo(host, sprinft("%d",port), NULL, &res);

        backup = res;

        while (res){
            if (ai_family == AF_INET) break;
            res = ai_next;
        }

        /* Etablir la connexion */
        if (connect(fd, &res, sizeof(res)) == -1) {
            perror("connect"); exit(1);
        }

        freeaddrinfo(backup);

    }

    void Socket::connect(in_addr ipv4, int port){
        
        struct sockaddr_in sin;
        char host[64];
        
        memset((void*)&sin, 0, sizeof(sin));
        sin.sin_addr.s_addr = ipv4;
        sin.sin_family = AF_INET;
        if (getnameinfo((struct sockaddr*)&sin, sizeof(sin), host, sizeof(host), sprinft("%d", port), NULL, 0) != 0) {
            perror("getnameinfo");
            exit(EXIT_FAILURE);
        }

        connect(host,port);
    }


    void Socket::close(){
        shutdown(fd,2);
        close(fd);
    }

    std::ostream & operator<< (std::ostream & os, struct sockaddr_in * addr){
        char host[64];
        if (getnameinfo((struct sockaddr*)addr, sizeof(*addr), host, sizeof(host), NULL, NULL, 0) != 0) {
            perror("getnameinfo");
            exit(EXIT_FAILURE);
        }
        return os << host << ": " << inet_ntoa(addr) << " " << addr->sin_port;
    }
}

