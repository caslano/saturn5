// Boost.Geometry

// Copyright (c) 2020-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_UTIL_SEQUENCE_HPP
#define BOOST_GEOMETRY_UTIL_SEQUENCE_HPP


#include <type_traits>


namespace boost { namespace geometry
{

namespace util
{


// An alternative would be to use std:tuple and std::pair
//   but it would add dependency.


template <typename ...Ts>
struct type_sequence {};


// true if T is a sequence
template <typename T>
struct is_sequence : std::false_type {};

template <typename ...Ts>
struct is_sequence<type_sequence<Ts...>> : std::true_type {};

template <typename T, T ...Is>
struct is_sequence<std::integer_sequence<T, Is...>> : std::true_type {};


// number of elements in a sequence
template <typename Sequence>
struct sequence_size {};

template <typename ...Ts>
struct sequence_size<type_sequence<Ts...>>
    : std::integral_constant<std::size_t, sizeof...(Ts)>
{};

template <typename T, T ...Is>
struct sequence_size<std::integer_sequence<T, Is...>>
    : std::integral_constant<std::size_t, sizeof...(Is)>
{};


// element of a sequence
template <std::size_t I, typename Sequence>
struct sequence_element {};

template <std::size_t I, typename T, typename ...Ts>
struct sequence_element<I, type_sequence<T, Ts...>>
{
    using type = typename sequence_element<I - 1, type_sequence<Ts...>>::type;
};

template <typename T, typename ...Ts>
struct sequence_element<0, type_sequence<T, Ts...>>
{
    using type = T;
};

template <std::size_t I, typename T, T J, T ...Js>
struct sequence_element<I, std::integer_sequence<T, J, Js...>>
    : std::integral_constant
        <
            T,
            sequence_element<I - 1, std::integer_sequence<T, Js...>>::value
        >
{};

template <typename T, T J, T ...Js>
struct sequence_element<0, std::integer_sequence<T, J, Js...>>
    : std::integral_constant<T, J>
{};


template <typename ...Ts>
struct pack_front
{
    static_assert(sizeof...(Ts) > 0, "Parameter pack can not be empty.");
};

template <typename T, typename ... Ts>
struct pack_front<T, Ts...>
{
    typedef T type;
};


template <typename Sequence>
struct sequence_front
    : sequence_element<0, Sequence>
{
    static_assert(sequence_size<Sequence>::value > 0, "Sequence can not be empty.");
};


template <typename Sequence>
struct sequence_back
    : sequence_element<sequence_size<Sequence>::value - 1, Sequence>
{
    static_assert(sequence_size<Sequence>::value > 0, "Sequence can not be empty.");
};


template <typename Sequence>
struct sequence_empty
    : std::integral_constant
        <
            bool,
            sequence_size<Sequence>::value == 0
        >
{};


// Defines type member for the first type in sequence that satisfies UnaryPred.
template
<
    typename Sequence,
    template <typename> class UnaryPred
>
struct sequence_find_if {};

template
<
    typename T, typename ...Ts,
    template <typename> class UnaryPred
>
struct sequence_find_if<type_sequence<T, Ts...>, UnaryPred>
    : std::conditional
        <
            UnaryPred<T>::value,
            T,
            // TODO: prevent instantiation for the rest of the sequence if value is true
            typename sequence_find_if<type_sequence<Ts...>, UnaryPred>::type
        >
{};

template <template <typename> class UnaryPred>
struct sequence_find_if<type_sequence<>, UnaryPred>
{
    // TODO: This is technically incorrect because void can be stored in a type_sequence
    using type = void;
};


// sequence_merge<type_sequence<A, B>, type_sequence<C, D>>::type is
//   type_sequence<A, B, C, D>
// sequence_merge<integer_sequence<A, B>, integer_sequence<C, D>>::type is
//   integer_sequence<A, B, C, D>
template <typename ...Sequences>
struct sequence_merge;

template <typename S>
struct sequence_merge<S>
{
    using type = S;
};

template <typename ...T1s, typename ...T2s>
struct sequence_merge<type_sequence<T1s...>, type_sequence<T2s...>>
{
    using type = type_sequence<T1s..., T2s...>;
};

template <typename T, T ...I1s, T ...I2s>
struct sequence_merge<std::integer_sequence<T, I1s...>, std::integer_sequence<T, I2s...>>
{
    using type = std::integer_sequence<T, I1s..., I2s...>;
};

template <typename S1, typename S2, typename ...Sequences>
struct sequence_merge<S1, S2, Sequences...>
{
    using type = typename sequence_merge
        <
            typename sequence_merge<S1, S2>::type,
            typename sequence_merge<Sequences...>::type
        >::type;
};


// sequence_combine<type_sequence<A, B>, type_sequence<C, D>>::type is
//   type_sequence<type_sequence<A, C>, type_sequence<A, D>,
//                 type_sequence<B, C>, type_sequence<B, D>>
template <typename Sequence1, typename Sequence2>
struct sequence_combine;

template <typename ...T1s, typename ...T2s>
struct sequence_combine<type_sequence<T1s...>, type_sequence<T2s...>>
{
    template <typename T1>
    using type_sequence_t = type_sequence<type_sequence<T1, T2s>...>;

    using type = typename sequence_merge<type_sequence_t<T1s>...>::type;
};

// sequence_combine<integer_sequence<T, 1, 2>, integer_sequence<T, 3, 4>>::type is
//   type_sequence<integer_sequence<T, 1, 3>, integer_sequence<T, 1, 4>,
//                 integer_sequence<T, 2, 3>, integer_sequence<T, 2, 4>>
template <typename T, T ...I1s, T ...I2s>
struct sequence_combine<std::integer_sequence<T, I1s...>, std::integer_sequence<T, I2s...>>
{
    template <T I1>
    using type_sequence_t = type_sequence<std::integer_sequence<T, I1, I2s>...>;

    using type = typename sequence_merge<type_sequence_t<I1s>...>::type;
};


// Selects least element from a parameter pack based on
// LessPred<T1, T2>::value comparison, similar to std::min_element
template
<
    template <typename, typename> class LessPred,
    typename ...Ts
>
struct pack_min_element;

template
<
    template <typename, typename> class LessPred,
    typename T
>
struct pack_min_element<LessPred, T>
{
    using type = T;
};

template
<
    template <typename, typename> class LessPred,
    typename T1, typename T2
>
struct pack_min_element<LessPred, T1, T2>
{
    using type = std::conditional_t<LessPred<T1, T2>::value, T1, T2>;
};

template
<
    template <typename, typename> class LessPred,
    typename T1, typename T2, typename ...Ts
>
struct pack_min_element<LessPred, T1, T2, Ts...>
{
    using type = typename pack_min_element
        <
            LessPred,
            typename pack_min_element<LessPred, T1, T2>::type,
            typename pack_min_element<LessPred, Ts...>::type
        >::type;
};


// Selects least element from a sequence based on
// LessPred<T1, T2>::value comparison, similar to std::min_element
template
<
    typename Sequence,
    template <typename, typename> class LessPred    
>
struct sequence_min_element;

template
<
    typename ...Ts,
    template <typename, typename> class LessPred
>
struct sequence_min_element<type_sequence<Ts...>, LessPred>
{
    using type = typename pack_min_element<LessPred, Ts...>::type;
};


// TODO: Since there are two kinds of parameter packs and sequences there probably should be two
//   versions of sequence_find_if as well as parameter_pack_min_element and sequence_min_element.
//   Currently these utilities support only types.


} // namespace util


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_SEQUENCE_HPP

/* sequence.hpp
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
*/