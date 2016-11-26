/// This Source Code Form is subject to the terms of the Mozilla Public
/// License, v. 2.0. If a copy of the MPL was not distributed with this
/// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @Author Aart Stuurman

/// Class summary
/* template<u32 dimension, typename ValueType>
 * class Dynarray;
 *
 * Constructor(u32 size_x, u32 size_y, u32 size_z, ...)
 *     Construct the object with given sizes for each dimension.
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
 *     Access the dynarray element at the position of choice.*/

#ifndef ASTUURMAN_DYNARRAY_HPP
#define ASTUURMAN_DYNARRAY_HPP

#include <tuple>

// If you are using a C++14 compiler you can exchange this for the std index sequence.
#include "IntegerSequence.hpp"

namespace Astuurman {

    /// Define as you like.
    // 32 bit unsigned integer
    using u32 = unsigned long;
    // 64 bit unsigned integer
    using u64 = unsigned long long;

    /// If you have a C++14 compiler you can use the std index sequence instead.
    template<size_t... T>
    using indseq = index_sequence<T...>;
    template <std::size_t V>
    using make_indseq = make_index_sequence<V>;

    template<u32 dimension, typename ValueType, typename = make_indseq<dimension>>
    class Dynarray;

    template <u32 dimension, typename ValueType, std::size_t... Is>
    class Dynarray<dimension, ValueType, indseq<Is...>>
    {
        template<typename To, typename>
        using to = To;

        ValueType* value;
        std::tuple<to<u32, decltype(Is)>...> size;

        template<typename Head>
        u64 Multiply(Head head)
        {
            return head;
        }

        template<typename Head, typename... Tail>
        u64 Multiply(Head head, Tail... tail)
        {
            return head * Multiply(tail...);
        }

        template<u32 index, typename Head>
        u64 IndexOffset(Head head)
        {
            return 1;
        }

        template<u32 index, typename Head, typename... Tail>
        u64 IndexOffset(Head head, Tail... tail)
        {
            return std::get<index + 1>(size) * IndexOffset<index + 1, Tail...>(tail...);
        }

        template<u32 dimIndex>
        u64 Index()
        {
            return 0;
        }

        template<u32 dimIndex = 0, typename Head, typename... Tail>
        u64 Index(Head head, Tail... tail)
        {
            return head * IndexOffset<dimIndex, Head, Tail...>(head, tail...) + Index<dimIndex + 1, Tail...>(tail...);
        }
    public:
        Dynarray(decltype(Is, u32{})... sizes)
        {
            value = new ValueType[Multiply(sizes...)]();
            size = std::make_tuple(sizes...);
        }

        ~Dynarray()
        {
            delete[] value;
        }

        constexpr u32 Dimension()
        {
            return dimension;
        }

        ValueType& At(to<u32, decltype(Is)>... indexes)
        {
            return value[Index(indexes...)];
        }

        template<u32 dim>
        u32 Size() const
        {
            return std::get<dim>(size);
        }
    };
}

#endif // ASTUURMAN_DYNARRAY_HPP
