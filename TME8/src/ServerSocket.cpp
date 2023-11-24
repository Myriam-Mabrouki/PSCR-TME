#include "ServerSocket.h"

namespace pr {

    ServerSocket::ServerSocket(int port){
        
        struct sockaddr_in sin; /* Nom de la socket de connexion */
        
        /* creation de la socket */
        if ((socketfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
            perror("socket"); exit(1);
        }
        
        memset((char *)&sin,0, sizeof(sin));
        sin.sin_addr.s_addr = htonl(INADDR_ANY);
        sin.sin_port = htons(port);
        sin.sin_family = AF_INET;
        
        /* nommage */
        if (bind(sc,(struct sockaddr *)&sin,sizeof(sin)) < 0) {
            perror("bind");
            exit(1);
        }

        listen(socketfd, 5); 
    }

    Socket ServerSocket::accept(){

        int scom; /* Socket de communication */
        struct sockaddr exp;
        int fromlen = sizeof(exp);
        
        if ((scom = accept(socketfd, (struct sockaddr *)&exp, &fromlen))== -1) {
            perror("accept"); 
            exit(3);
        }
        return Socket(scom);
    }

	void ServerSocket::close(){
        shutdown(socketfd,2);
        close(socketfd);
    }
}