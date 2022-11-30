// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_UTIL_PROMOTE_INTEGRAL_HPP
#define BOOST_GEOMETRY_UTIL_PROMOTE_INTEGRAL_HPP

// For now deactivate the use of multiprecision integers
// TODO: activate it later
#define BOOST_GEOMETRY_NO_MULTIPRECISION_INTEGER


#include <climits>
#include <cstddef>
#include <type_traits>

#if !defined(BOOST_GEOMETRY_NO_MULTIPRECISION_INTEGER)
#include <boost/multiprecision/cpp_int.hpp>
#endif


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace promote_integral
{

// meta-function that returns the bit size of a type
template
<
    typename T,
    bool IsFundamental = std::is_fundamental<T>::value
>
struct bit_size
{};


// for fundamental types, just return CHAR_BIT * sizeof(T)
template <typename T>
struct bit_size<T, true>
    : std::integral_constant<std::size_t, (CHAR_BIT * sizeof(T))>
{};


#if !defined(BOOST_GEOMETRY_NO_MULTIPRECISION_INTEGER)
// partial specialization for cpp_int
template
<
    unsigned MinSize,
    unsigned MaxSize,
    boost::multiprecision::cpp_integer_type SignType,
    boost::multiprecision::cpp_int_check_type Checked,
    typename Allocator,
    boost::multiprecision::expression_template_option ExpressionTemplates
>
struct bit_size
    <
        boost::multiprecision::number
            <
                boost::multiprecision::cpp_int_backend
                    <
                        MinSize, MaxSize, SignType, Checked, Allocator
                    >,
                ExpressionTemplates
            >,
        false
    >
    : std::integral_constant<std::size_t, MaxSize>
{};
#endif // BOOST_GEOMETRY_NO_MULTIPRECISION_INTEGER


template <typename T, std::size_t MinSize, typename ...Ts>
struct promote_to_larger
{
    // if promotion fails, keep the number T
    // (and cross fingers that overflow will not occur)
    typedef T type;
};

template <typename T, std::size_t MinSize, typename CurrentT, typename ...Ts>
struct promote_to_larger<T, MinSize, CurrentT, Ts...>
{
    typedef std::conditional_t
        <
            (bit_size<CurrentT>::value >= MinSize),
            CurrentT,
            typename promote_to_larger<T, MinSize, Ts...>::type
        > type;
};

template <typename ...Ts>
struct integral_types {};

template <typename T, std::size_t MinSize, typename ...Ts>
struct promote_to_larger<T, MinSize, integral_types<Ts...>>
    : promote_to_larger<T, MinSize, Ts...>
{};


}} // namespace detail::promote_integral
#endif // DOXYGEN_NO_DETAIL



/*!
    \brief Meta-function to define an integral type with size
    than is (roughly) twice the bit size of T
    \ingroup utility
    \details
    This meta-function tries to promote the fundamental integral type T
    to a another integral type with size (roughly) twice the bit size of T.

    To do this, two times the bit size of T is tested against the bit sizes of:
         short, int, long, long long, boost::int128_t
    and the one that first matches is chosen.

    For unsigned types the bit size of T is tested against the bit
    sizes of the types above, if T is promoted to a signed type, or
    the bit sizes of
         unsigned short, unsigned int, unsigned long, std::size_t,
         unsigned long long, boost::uint128_t
    if T is promoted to an unsigned type.

    By default an unsigned type is promoted to a signed type.
    This behavior is controlled by the PromoteUnsignedToUnsigned
    boolean template parameter, whose default value is "false".
    To promote an unsigned type to an unsigned type set the value of
    this template parameter to "true".

    If the macro BOOST_GEOMETRY_NO_MULTIPRECISION_INTEGER is not
    defined, boost's multiprecision integer cpp_int<> is used as a
    last resort.

    If BOOST_GEOMETRY_NO_MULTIPRECISION_INTEGER is defined and an
    appropriate type cannot be detected, the input type is returned as is.

    Finally, if the passed type is either a floating-point type or a
    user-defined type it is returned as is.

    \note boost::int128_type and boost::uint128_type are considered
    only if the macros BOOST_HAS_INT128 and BOOST_GEOMETRY_ENABLE_INT128
    are defined
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

    typedef detail::promote_integral::bit_size<T> bit_size_type;

#if !defined(BOOST_GEOMETRY_NO_MULTIPRECISION_INTEGER)
    // Define the proper check policy for the multiprecision integer
    typedef std::conditional_t
        <
            UseCheckedInteger,
            std::integral_constant
                <
                    boost::multiprecision::cpp_int_check_type,
                    boost::multiprecision::checked
                >,
            std::integral_constant
                <
                    boost::multiprecision::cpp_int_check_type,
                    boost::multiprecision::unchecked
                >
        > check_policy_type;

    // Meta-function to get the multiprecision integer type for the
    // given size and sign type (signed/unsigned)
    template
    <
        unsigned int Size,
        boost::multiprecision::cpp_integer_type SignType
    >
    struct multiprecision_integer_type
    {
        typedef boost::multiprecision::number
            <
                boost::multiprecision::cpp_int_backend
                    <
                        Size,
                        Size,
                        SignType,
                        check_policy_type::value,
                        void
                    >
            > type;
    };
#endif

    // Define the minimum size (in bits) needed for the promoted type
    // If T is the input type and P the promoted type, then the
    // minimum number of bits for P are (below b stands for the number
    // of bits of T):
    // * if T is unsigned and P is unsigned: 2 * b
    // * if T is signed and P is signed: 2 * b - 1
    // * if T is unsigned and P is signed: 2 * b + 1
    typedef std::conditional_t
        <
            (PromoteUnsignedToUnsigned && is_unsigned),
            std::integral_constant<std::size_t, (2 * bit_size_type::value)>,
            std::conditional_t
                <
                    is_unsigned,
                    std::integral_constant<std::size_t, (2 * bit_size_type::value + 1)>,
                    std::integral_constant<std::size_t, (2 * bit_size_type::value - 1)>
                >
        > min_bit_size_type;

    // Define the list of signed integral types we are going to use
    // for promotion
    typedef detail::promote_integral::integral_types
        <
            short,
            int,
            long,
            long long
#if defined(BOOST_HAS_INT128) && defined(BOOST_GEOMETRY_ENABLE_INT128)
            , boost::int128_type
#endif
#if !defined(BOOST_GEOMETRY_NO_MULTIPRECISION_INTEGER)
            , typename multiprecision_integer_type
                <
                    min_bit_size_type::value,
                    boost::multiprecision::signed_magnitude
                >::type
#endif
        > signed_integral_types;

    // Define the list of unsigned integral types we are going to use
    // for promotion
    typedef detail::promote_integral::integral_types
        <
            unsigned short,
            unsigned int,
            unsigned long,
            std::size_t,
            unsigned long long
#if defined(BOOST_HAS_INT128) && defined(BOOST_GEOMETRY_ENABLE_INT128)
            , boost::uint128_type
#endif
#if !defined(BOOST_GEOMETRY_NO_MULTIPRECISION_INTEGER)
            , typename multiprecision_integer_type
                <
                    min_bit_size_type::value,
                    boost::multiprecision::unsigned_magnitude
                >::type
#endif
        > unsigned_integral_types;

    // Define the list of integral types that will be used for
    // promotion (depending in whether we was to promote unsigned to
    // unsigned or not)
    typedef std::conditional_t
        <
            (is_unsigned && PromoteUnsignedToUnsigned),
            unsigned_integral_types,
            signed_integral_types
        > integral_types;

public:
    typedef typename detail::promote_integral::promote_to_larger
        <
            T,
            min_bit_size_type::value,
            integral_types            
        >::type type;
};


template <typename T, bool PromoteUnsignedToUnsigned, bool UseCheckedInteger>
class promote_integral
    <
        T, PromoteUnsignedToUnsigned, UseCheckedInteger, false
    >
{
public:
    typedef T type;
};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_PROMOTE_INTEGRAL_HPP

/* promote_integral.hpp
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
*/