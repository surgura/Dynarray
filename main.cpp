/// This Source Code Form is subject to the terms of the Mozilla Public
/// License, v. 2.0. If a copy of the MPL was not distributed with this
/// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "Dynarray/Dynarray.hpp"
#include "Dynarray/Dynstring.hpp"
#include <iostream>

using namespace Astuurman;

int main()
{
    Dynarray<3, u32> myDynarray(2,3,4);

    std::cout << "Dimension: " << myDynarray.Dimension() << std::endl;
    std::cout << "Size " << 0 << ": " << myDynarray.Size<0>() << std::endl;
    std::cout << "Size " << 1 << ": " << myDynarray.Size<1>() << std::endl;
    std::cout << "Size " << 2 << ": " << myDynarray.Size<2>() << std::endl;

    myDynarray.At(0,0,0) = 5;
    myDynarray.At(1,2,3) = 10;

    for(u32 z = 0; z < myDynarray.Size<2>(); ++z)
    {
        for(u32 y = 0; y < myDynarray.Size<1>(); ++y)
        {
            for(u32 x = 0; x < myDynarray.Size<0>(); ++x)
            {
                std::cout << x << " " << y << " " << z << " " << myDynarray.At(x,y,z) << std::endl;
            }
        }
    }

    system("pause");

	return 0;
}
