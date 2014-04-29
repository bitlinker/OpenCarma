#include <iostream>
#include <cstdio>

#include "ObjectFactory.h"

int main()
{
    using namespace OpenCarma::BRender;
    std::cout << "BRender test" << std::endl;

    ObjectFactory factory;
    bool bRes = factory.load(std::string("e:/Games/Carma/DATA/PIXELMAP/2XCOMBO.PIX"));

    return 0;
}