#include "TCPServer.h"
#include

using namespace std;
using namespace pr;

namespace pr {

    void handlerClient(Socket scom){
        int i;
        read(scom.getFD(), &i, sizeof(i));
        write(scom.getFD(), &i, sizeof(i));
        scom.close();
    }
    
	bool startServer (int port){
        
    }

	// stoppe le serveur
	void stopServer () {

    }
}