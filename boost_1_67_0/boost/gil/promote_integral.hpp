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