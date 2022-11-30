// Boost.GIL (Generic Image Library)
//
// Copyright (c) 2015, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// 
// Copyright (c) 2020, Debabrata Mandal <mandaldebabrata123@gmail.com>
//
// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html
//
// Source: Boost.Geometry (aka GGL, Generic Geometry Library)
// Modifications: adapted for Boost.GIL
//  - Rename namespace boost::geometry to boost::gil
//  - Rename include guards
//  - Remove support for boost::multiprecision types
//  - Remove support for 128-bit integer types
//  - Replace mpl meta functions with mp11 equivalents
//
#ifndef BOOST_GIL_PROMOTE_INTEGRAL_HPP
#define BOOST_GIL_PROMOTE_INTEGRAL_HPP

#include <boost/mp11/list.hpp>

#include <climits>
#include <cstddef>
#include <type_traits>

namespace boost { namespace gil
{

namespace detail { namespace promote_integral
{

// meta-function that returns the bit size of a type
template
<
    typename T,
    bool IsFundamental = std::is_fundamental<T>::value
>
struct bit_size {};

// for fundamental types, just return CHAR_BIT * sizeof(T)
template <typename T>
struct bit_size<T, true> : std::integral_constant<std::size_t, (CHAR_BIT * sizeof(T))> {};

template
<
    typename T,
    typename IntegralTypes,
    std::size_t MinSize
>
struct promote_to_larger
{
    using current_type = boost::mp11::mp_first<IntegralTypes>;
    using list_after_front = boost::mp11::mp_rest<IntegralTypes>;

    using type = typename std::conditional
        <
            (bit_size<current_type>::value >= MinSize),
            current_type,
            typename promote_to_larger
                <
                    T,
                    list_after_front,
                    MinSize
                >::type
        >::type;
};

// The following specialization is required to finish the loop over
// all list elements
template <typename T, std::size_t MinSize>
struct promote_to_larger<T, boost::mp11::mp_list<>, MinSize>
{
    // if promotion fails, keep the number T
    // (and cross fingers that overflow will not occur)
    using type = T;
};

}} // namespace detail::promote_integral

/*!
    \brief Meta-function to define an integral type with size
    than is (roughly) twice the bit size of T
    \ingroup utility
    \details
    This meta-function tries to promote the fundamental integral type T
    to a another integral type with size (roughly) twice the bit size of T.

    To do this, two times the bit size of T is tested against the bit sizes of:
         short, int, long, boost::long_long_type, boost::int128_t
    and the one that first matches is chosen.

    For unsigned types the bit size of T is tested against the bit
    sizes of the types above, if T is promoted to a signed type, or
    the bit sizes of
         unsigned short, unsigned int, unsigned long, std::size_t,
         boost::ulong_long_type, boost::uint128_t
    if T is promoted to an unsigned type.

    By default an unsigned type is promoted to a signed type.
    This behavior is controlled by the PromoteUnsignedToUnsigned
    boolean template parameter, whose default value is "false".
    To promote an unsigned type to an unsigned type set the value of
    this template parameter to "true".

    Finally, if the passed type is either a floating-point type or a
    user-defined type it is returned as is.

    \note boost::long_long_type and boost::ulong_long_type are
    considered only if the macro BOOST_HAS_LONG_LONG is defined

*/
template
<
    typename T,
    bool PromoteUnsignedToUnsigned = false,
    bool UseCheckedInteger = false,
    bool IsIntegral = std::is_integral<T>::value
>
class promote_integral
{
private:
    static bool const is_unsigned = std::is_unsigned<T>::value;

    using bit_size_type = detail::promote_integral::bit_size<T>;

    // Define the minimum size (in bits) needed for the promoted type
    // If T is the input type and P the promoted type, then the
    // minimum number of bits for P are (below b stands for the number
    // of bits of T):
    // * if T is unsigned and P is unsigned: 2 * b
    // * if T is signed and P is signed: 2 * b - 1
    // * if T is unsigned and P is signed: 2 * b + 1
    using min_bit_size_type = typename std::conditional
        <
            (PromoteUnsignedToUnsigned && is_unsigned),
            std::integral_constant<std::size_t, (2 * bit_size_type::value)>,
            typename std::conditional
                <
                    is_unsigned,
                    std::integral_constant<std::size_t, (2 * bit_size_type::value + 1)>,
                    std::integral_constant<std::size_t, (2 * bit_size_type::value - 1)>
                >::type
        >::type;

    // Define the list of signed integral types we are going to use
    // for promotion
    using signed_integral_types = boost::mp11::mp_list
        <
            short, int, long
#if defined(BOOST_HAS_LONG_LONG)
            , boost::long_long_type
#endif
        >;

    // Define the list of unsigned integral types we are going to use
    // for promotion
    using unsigned_integral_types = boost::mp11::mp_list
        <
            unsigned short, unsigned int, unsigned long, std::size_t
#if defined(BOOST_HAS_LONG_LONG)
            , boost::ulong_long_type
#endif
        >;

    // Define the list of integral types that will be used for
    // promotion (depending in whether we was to promote unsigned to
    // unsigned or not)
    using integral_types = typename std::conditional
        <
            (is_unsigned && PromoteUnsignedToUnsigned),
            unsigned_integral_types,
            signed_integral_types
        >::type;

public:
    using type = typename detail::promote_integral::promote_to_larger
        <
            T,
            integral_types,
            min_bit_size_type::value
        >::type;
};


template <typename T, bool PromoteUnsignedToUnsigned, bool UseCheckedInteger>
class promote_integral
    <
        T, PromoteUnsignedToUnsigned, UseCheckedInteger, false
    >
{
public:
    using type = T;
};

}} // namespace boost::gil

#endif // BOOST_GIL_PROMOTE_INTEGRAL_HPP

/* promote_integral.hpp
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
*/