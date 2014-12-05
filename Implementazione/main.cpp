#include <iostream>
#include ""

using namespace std;

int main()
{

    file_reader fr("mio_file");
    while(fr.file_ended()){
        cout << fr.read_next_bytes(2) << endl;
    }

}
