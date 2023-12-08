#include "ServerSocket.h"
#include "Socket.h"

using namespace pr;
using namespace std;

int main (){

    ServerSocket serv(0);

    while (true) {
        Socket client = serv.accept();
        int i = 0;
        read(client.getFD(), &i, sizeof(i));
        i *= 2;
        cout << i<<endl;
        write(client.getFD(), &i, sizeof(i));
        client.close();
    }

    serv.close();
    return 0;

}