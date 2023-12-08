#include "Socket.h"

using namespace pr;
using namespace std;

    int main(int argc, char** argv){

        Socket sock;
        sock.connect("localhost", atoi(argv[1]));

        if (sock.isOpen()){
            int fd = sock.getFD();
            int i = 1667;

            if (!write(fd, &i, sizeof(i))){
                perror("Error: peux po écrire");
                exit(1);
            }

            size_t lu;
            lu = read (fd, &i, sizeof(i));

            if (lu == 0){
                //sock fermé                       
            }

            cout << i << endl;
        }

        sock.close();
        
    }