#ifndef ASTUURMAN_INTEGER_SEQUENCE_HPP
#define ASTUURMAN_INTEGER_SEQUENCE_HPP

/// This is --not-- written by Aart Stuurman
/// Source:
/// http://stackoverflow.com/a/40793363/2476219

namespace Astuurman {
    template <class T, T... Vs>
    struct integer_sequence { };

    template <class T, class, class, class = integer_sequence<T>, class = integer_sequence<T, 0>, class = void>
    struct make_integer_sequence_impl;

    template <class T, T ICV1, T... Res, T... Pow>
    struct make_integer_sequence_impl<T, std::integral_constant<T, ICV1>, std::integral_constant<T, 0>, integer_sequence<T, Res...>, integer_sequence<T, Pow...>, typename std::enable_if<(ICV1 > 0)>::type>: make_integer_sequence_impl<T, std::integral_constant<T, ICV1/2>, std::integral_constant<T, ICV1%2>, integer_sequence<T, Res...>, integer_sequence<T, Pow..., (Pow + sizeof...(Pow))...>> { };

    template <class T, T ICV1, T... Res, T... Pow>
    struct make_integer_sequence_impl<T, std::integral_constant<T, ICV1>, std::integral_constant<T, 1>, integer_sequence<T, Res...>, integer_sequence<T, Pow...>, void>: make_integer_sequence_impl<T, std::integral_constant<T, ICV1/2>, std::integral_constant<T, ICV1%2>, integer_sequence<T, Pow..., (Res + sizeof...(Pow))...>, integer_sequence<T, Pow..., (Pow + sizeof...(Pow))...>> { };

    template <class T, class Res, class Pow>
    struct make_integer_sequence_impl<T, std::integral_constant<T, 0>, std::integral_constant<T, 0>, Res, Pow, void> {
       using type = Res;
    };

    template <class T, T V>
    using make_integer_sequence = typename make_integer_sequence_impl<T, std::integral_constant<T, V/2>, std::integral_constant<T, V%2>>::type;

    template <std::size_t V>
    using make_index_sequence = make_integer_sequence<std::size_t, V>;

    template <std::size_t... V>
    using index_sequence = integer_sequence<std::size_t, V...>;
}

#endif // ASTUURMAN_INTEGER_SEQUENCE_HPP
