#include "Subspaces.h"


using namespace std;
using namespace arma;

//Subspaces::Subspaces(){
////constructor
//}
//Subspaces::Subspaces(){
////destructor
//}

void Subspaces::probarArmadillo(){

    mat A;
    mat B;

    A   <<0<<1<<2<<endr
        <<3<<4<<5<<endr
        <<6<<7<<8<<endr;


    B = pinv(A);

    cout<<B<<endl;

}
