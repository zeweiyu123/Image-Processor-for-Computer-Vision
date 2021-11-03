// Project UID af1f95f547e44c8ea88730dfb185559d
#include <iostream>
#include "Image.h"
#include <fstream>
#include "processing.h"
#include <cassert>
using namespace std;

int main(int argc, char *argv[]){
    if(argc != 4 && argc != 5){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return -1;
    }
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    if(!fin.is_open()){
        cout << "Error opening file: " << *argv[0] << endl;
        return 1;
    } else if (!fout.is_open()){
        cout << "Error opening file: " << *argv[1] << endl;
        return 1;
    } else{
        Image *output = new Image;
        Image_init(output, fin);
        if(argc==4 &&  (atoi(argv[3]) <= 0 || atoi(argv[3]) > Image_width(output))){
            cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
            << "WIDTH and HEIGHT must be less than or equal to original" << endl;
            return -1;
        } else if(argc==5 &&  (atoi(argv[3]) <= 0 || atoi(argv[3]) > Image_width(output) 
                    || atoi(argv[4]) <=0 || atoi(argv[4]) > Image_height(output))){
            cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
            << "WIDTH and HEIGHT must be less than or equal to original" << endl;
            return -1;
        } else{
            if(argc == 4){
                seam_carve(output, atoi(argv[3]), Image_height(output));
            } else{
                seam_carve(output, atoi(argv[3]), atoi(argv[4]));
            }
            Image_print(output, fout);
            fin.close();
            fout.close();
            delete output;
            return 0;
        }
    }
}
