/// This Source Code Form is subject to the terms of the Mozilla Public
/// License, v. 2.0. If a copy of the MPL was not distributed with this
/// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @Author Aart Stuurman
/// @Source https://github.com/surgura/Dynarray

/// Class summary
/* template<u32 dimension, typename ValueType>
 * class Dynarray;
 *
 * Constructor(u32 size_x, u32 size_y, u32 size_z, ...)
 *     Construct the object with given sizes for each dimension.
 * Constructor(ValueType[] initialValue, u32 size_x, u32 size_y, u32 size_z, ...)
 *     Construct the object with given sizes for each dimension.
 *     InitialValue will be used to initialize the underlying array.
 *     Layout is row-major
 *     [x0y0, x0y1, x0y2, x1y0, x1y1, ...]
 *
 * void Dimension()
 *     Get the dimension of the array.
 *     Equal to the template parameter.
 *
 * template<u32 dim>
 * u32 Size()
 *     Get the size in the given dimension.
 *     Equal to the argument provided in the constructor.
 *
 * ValueType& At(u32 x, u32 y, u32 z, ...)
 *     Access the dynarray element at the position of choice.
 *
 * ValueType* Data()
 *     Get the underlying array*/

#ifndef ASTUURMAN_DYNARRAY_HPP
#define ASTUURMAN_DYNARRAY_HPP

#include <tuple>
#include <utility>

namespace Astuurman {

    /// Define as you like.
    // 32 bit unsigned integer
    using u32 = unsigned long;
    // 64 bit unsigned integer
    using u64 = unsigned long long;

    template<u32 dimension, typename ValueType, typename = std::make_index_sequence<dimension>>
    class Dynarray;

    template <u32 dimension, typename ValueType, std::size_t... Is>
    class Dynarray<dimension, ValueType, std::index_sequence<Is...>>
    {
        template<typename To, typename>
        using to = To;

        ValueType* value;
        std::tuple<to<u32, decltype(Is)>...> size;

        u64 MultiplySizes(to<u32, decltype(Is)>... sizes)
        {
            u64 res = 1;
            for (const u32& size : {sizes...})
                res *= size;
            return res;
        }

        template<u32 dimIndex>
        u64 _Index(u32 offset) const
        {
            return 0;
        }

        template<u32 dimIndex, typename Head, typename... Tail>
        u64 _Index(u32 offset, Head head, Tail... tail) const
        {
            return head * offset + _Index<dimIndex + 1, Tail...>(offset * std::get<dimIndex>(size), tail...);
        }

        template<typename Head, typename... Tail>
        u64 Index(Head head, Tail... tail) const
        {
            return head + _Index<1, Tail...>(std::get<0>(size), tail...);
        }
    public:
        Dynarray(const ValueType* value, to<u32, decltype(Is)>... sizes) :
            value(new ValueType[MultiplySizes(sizes...)]()),
            size(std::make_tuple(sizes...))
        {
            std::copy(value, value + MultiplySizes(sizes...), this->value);
        }

        Dynarray(to<u32, decltype(Is)>... sizes) :
            value(new ValueType[MultiplySizes(sizes...)]()),
            size(std::make_tuple(sizes...))
        {}

        ~Dynarray()
        {
            delete[] value;
        }

        // move constructor
        Dynarray(Dynarray&& other)
            : value(other.value), size(other.size)
        {
            other.value = nullptr;
        }

        // move assignment
        Dynarray& operator=(Dynarray&& other)
        {
            std::swap(value);
            size = other.size;
            return *this;
        }

        // copy constructor
        Dynarray(const Dynarray& other) :
            Dynarray(other.value, std::get<Is>(other.size)...)
        {}

        // copy assignment
        Dynarray& operator=(const Dynarray& other)
        {
            value = new ValueType[Multiply(std::get<Is>(other.size)...)](other.value);
            size = other.size;
        }

        constexpr u32 Dimension()
        {
            return dimension;
        }

        ValueType& At(to<u32, decltype(Is)>... indexes)
        {
            return value[Index(indexes...)];
        }

        const ValueType& At(to<u32, decltype(Is)>... indexes) const
        {
            return value[Index(indexes...)];
        }

        template<u32 dim>
        u32 Size() const
        {
            return std::get<dim>(size);
        }

        ValueType* Data()
        {
            return value;
        }

        const ValueType* Data() const
        {
            return value;
        }
    };
}

#endif // ASTUURMAN_DYNARRAY_HPP
