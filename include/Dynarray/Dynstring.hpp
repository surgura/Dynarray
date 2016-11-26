/// This Source Code Form is subject to the terms of the Mozilla Public
/// License, v. 2.0. If a copy of the MPL was not distributed with this
/// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @Author Aart Stuurman

#ifndef ASTUURMAN_DYNSTRING_HPP
#define ASTUURMAN_DYNSTRING_HPP

#include "Dynarray.hpp"
#include <cstring>

namespace Astuurman {

class Dynstring : public Dynarray<1, char>
{
public:
    Dynstring(const char* value) :
        Dynstring(value, std::strlen(value)) {}

    Dynstring(const char* value, u32 length) :
        Dynarray(value, length) {}

    const char& operator[] (u32 index) const
    {
          return At(index);
    }
};

}

#endif // ASTUURMAN_DYNSTRING_HPP
