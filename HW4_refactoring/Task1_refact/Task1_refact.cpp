#include <iostream>
#include "shape.h"
#include "transform.h"

int main()
{
    coord x{ { 0.0, 0.0, 0.0, 0.0 }, { 2.1,3.3,0.5,1.2} } ;
   
    Square Sq1(x);

    coord center{ {0.0},{1.0} };
    Circle Crcl(center, 10);

    transform tr1(Sq1,4);
    std::cout<< Sq1.getType()<<"\n";
    std::cout << Sq1.getDimension() << "\n";
    
    std::cout << Crcl.getType() << "\n";
}


