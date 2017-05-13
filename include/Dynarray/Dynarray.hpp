/// This Source Code Form is subject to the terms of the Mozilla Public
/// License, v. 2.0. If a copy of the MPL was not distributed with this
/// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @Author Aart Stuurman
/// @Source https://github.com/surgura/Dynarray

/// Class summary
/* template<size_t dimension, typename ValueType>
 * class Dynarray;
 *
 * Constructor(size_t size_x, size_t size_y, size_t size_z, ...)
 *     Construct the object with given sizes for each dimension.
 * Constructor(ValueType[] initialValue, size_t size_x, size_t size_y, size_t size_z, ...)
 *     Construct the object with given sizes for each dimension.
 *     InitialValue will be used to initialize the underlying array.
 *     Layout is column-major
 *     [x0y0, x1y0, x2y0, x0y1, x1y1, ...]
 *
 * void Dimension()
 *     Get the dimension of the array.
 *     Equal to the template parameter.
 *
 * template<size_t dim>
 * size_t Size()
 *     Get the size in the given dimension.
 *     Equal to the argument provided in the constructor.
 *
 * ValueType& At(size_t x, size_t y, size_t z, ...)
 *     Access the dynarray element at the position of choice.
 *
 * ValueType* Data()
 *     Get the underlying array*/

#ifndef ASTUURMAN_DYNARRAY_HPP
#define ASTUURMAN_DYNARRAY_HPP

#include <tuple>
#include <utility>

namespace Astuurman {

    template<std::size_t dimension, typename ValueType, typename = std::make_index_sequence<dimension>>
    class Dynarray;

    template <std::size_t dimension, typename ValueType, std::size_t... Is>
    class Dynarray<dimension, ValueType, std::index_sequence<Is...>>
    {
        template<typename To, std::size_t>
        using to = To;

        ValueType* value;
        std::tuple<to<std::size_t, Is>...> size;

        std::size_t MultiplySizes() const
        {
            return 1;
        }

        template<typename Head, typename... Tail>
        std::size_t MultiplySizes(Head head, Tail... tail) const
        {
            return head * MultiplySizes(tail...);
        }

        template<std::size_t dimIndex>
        std::size_t _Index(std::size_t offset) const
        {
            return 0;
        }

        template<std::size_t dimIndex, typename Head, typename... Tail>
        std::size_t _Index(std::size_t offset, Head head, Tail... tail) const
        {
            return head * offset + _Index<dimIndex + 1, Tail...>(offset * std::get<dimIndex>(size), tail...);
        }

        template<typename Head, typename... Tail>
        std::size_t Index(Head head, Tail... tail) const
        {
            return head + _Index<1, Tail...>(std::get<0>(size), tail...);
        }
    public:
        Dynarray(const ValueType* value, to<std::size_t, Is>... sizes) :
            value(new ValueType[MultiplySizes(sizes...)]()),
            size(std::make_tuple(sizes...))
        {
            std::copy(value, value + MultiplySizes(sizes...), this->value);
        }

        Dynarray(to<std::size_t, Is>... sizes) :
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

        constexpr std::size_t Dimension()
        {
            return dimension;
        }

        ValueType& At(to<std::size_t, Is>... indexes)
        {
            return value[Index(indexes...)];
        }

        const ValueType& At(to<std::size_t, Is>... indexes) const
        {
            return value[Index(indexes...)];
        }

        template<std::size_t dim>
        std::size_t Size() const
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
