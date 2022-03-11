// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_UTIL_PROMOTE_INTEGRAL_HPP
#define BOOST_GEOMETRY_UTIL_PROMOTE_INTEGRAL_HPP

// For now deactivate the use of multiprecision integers
// TODO: activate it later
#define BOOST_GEOMETRY_NO_MULTIPRECISION_INTEGER

#include <climits>
#include <cstddef>

#include <boost/mpl/begin.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/size_t.hpp>

#if !defined(BOOST_GEOMETRY_NO_MULTIPRECISION_INTEGER)
#include <boost/multiprecision/cpp_int.hpp>
#endif

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_unsigned.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace promote_integral
{

// meta-function that returns the bit size of a type
template
<
    typename T,
    bool IsFundamental = boost::is_fundamental<T>::type::value
>
struct bit_size
{};


// for fundamental types, just return CHAR_BIT * sizeof(T)
template <typename T>
struct bit_size<T, true>
    : boost::mpl::size_t<(CHAR_BIT * sizeof(T))>
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
    > : boost::mpl::size_t<MaxSize>
{};
#endif // BOOST_GEOMETRY_NO_MULTIPRECISION_INTEGER


template
<
    typename T,
    typename Iterator,
    typename EndIterator,
    std::size_t MinSize
>
struct promote_to_larger
{
    typedef typename boost::mpl::deref<Iterator>::type current_type;

    typedef typename boost::mpl::if_c
        <
            (bit_size<current_type>::type::value >= MinSize),
            current_type,
            typename promote_to_larger
                <
                    T,
                    typename boost::mpl::next<Iterator>::type,
                    EndIterator,
                    MinSize
                >::type
        >::type type;
};

// The following specialization is required to finish the loop over
// all list elements
template <typename T, typename EndIterator, std::size_t MinSize>
struct promote_to_larger<T, EndIterator, EndIterator, MinSize>
{
    // if promotion fails, keep the number T
    // (and cross fingers that overflow will not occur)
    typedef T type;
};

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

    If the macro BOOST_GEOMETRY_NO_MULTIPRECISION_INTEGER is not
    defined, boost's multiprecision integer cpp_int<> is used as a
    last resort.

    If BOOST_GEOMETRY_NO_MULTIPRECISION_INTEGER is defined and an
    appropriate type cannot be detected, the input type is returned as is.

    Finally, if the passed type is either a floating-point type or a
    user-defined type it is returned as is.

    \note boost::long_long_type and boost::ulong_long_type are
    considered only if the macro BOOST_HAS_LONG_LONG is defined

    \note boost::int128_type and boost::uint128_type are considered
    only if the macros BOOST_HAS_INT128 and BOOST_GEOMETRY_ENABLE_INT128
    are defined
*/
template
<
    typename T,
    bool PromoteUnsignedToUnsigned = false,
    bool UseCheckedInteger = false,
    bool IsIntegral = boost::is_integral<T>::type::value
>
class promote_integral
{
private:
    static bool const is_unsigned = boost::is_unsigned<T>::type::value;

    typedef detail::promote_integral::bit_size<T> bit_size_type;

#if !defined(BOOST_GEOMETRY_NO_MULTIPRECISION_INTEGER)
    // Define the proper check policy for the multiprecision integer
    typedef typename boost::mpl::if_c
        <
            UseCheckedInteger,
            boost::integral_constant
                <
                    boost::multiprecision::cpp_int_check_type,
                    boost::multiprecision::checked
                >,
            boost::integral_constant
                <
                    boost::multiprecision::cpp_int_check_type,
                    boost::multiprecision::unchecked
                >
        >::type check_policy_type;

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
    typedef typename boost::mpl::if_c
        <
            (PromoteUnsignedToUnsigned && is_unsigned),
            boost::mpl::size_t<(2 * bit_size_type::value)>,
            typename boost::mpl::if_c
                <
                    is_unsigned,
                    boost::mpl::size_t<(2 * bit_size_type::value + 1)>,
                    boost::mpl::size_t<(2 * bit_size_type::value - 1)>
                >::type
        >::type min_bit_size_type;

    // Define the list of signed integral types we are going to use
    // for promotion
    typedef boost::mpl::list
        <
            short, int, long
#if defined(BOOST_HAS_LONG_LONG)
            , boost::long_long_type
#endif
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
    typedef boost::mpl::list
        <
            unsigned short, unsigned int, unsigned long, std::size_t
#if defined(BOOST_HAS_LONG_LONG)
            , boost::ulong_long_type
#endif
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
    typedef typename boost::mpl::if_c
        <
            (is_unsigned && PromoteUnsignedToUnsigned),
            unsigned_integral_types,
            signed_integral_types
        >::type integral_types;

public:
    typedef typename detail::promote_integral::promote_to_larger
        <
            T,
            typename boost::mpl::begin<integral_types>::type,
            typename boost::mpl::end<integral_types>::type,
            min_bit_size_type::value
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