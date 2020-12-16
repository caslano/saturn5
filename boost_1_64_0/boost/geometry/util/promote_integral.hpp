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
31u6LFz6Ycy3SZDVGWvj96S+l437P6lvk+73MZBV5Oj1xUsbHrqPz5Wyx/WyC8V+xhqaIrJT+vy1i00NnZeI/Q7pskfEzoZdnJIvXM+XJ/01/O8JyWesZavEBm8Y93/ShhHDNkDm6tRlz0gb53XZ85BFTtBl5TK+pcb9n7SxQLfBj2TMjd9SfyL63abbdA9knSF6fXvFpsbe4ucyRsZe4G3InEacrBNdjDu3wyIz1sHfih906GXfF9mvdFmTtGv8fnRSxjdFr+9DyfepXvZjsd9s4/5P/Mr4Hey82MWIJZ+Jzm/qNv1CbGqsjVekvp/qMo8+GKOf6POyN2Sdxl3uNyCrbtZ19pWyhv0GQBY2RJcNgSxwky67W2S/1W0VBJlzmN5GCGSR7+j9HQuZ66je3wkie1KXRUhZ415qirRxSW93GmS+xl3f/ZLPouscB1mrEa8SpA3jLL4AsrpoXfag9NeIzzbISo1Y7IDMYryT8LDYdJHet0fF9uv0NnJFl7/pZQuk3QBd9pT07U96fWulrOH3xZA1GuePzZBVGGfx5yAz7ztfFJ3v0u28Xexn09vYKbok6v34sYzHP/R8PxP/e1yvr1rs96Vx/ycyY916S/oxU2/jV2KXCr1v9ZJvsHH/J3PhTV32O9ElQJf9QWxwVNevWWTG/Dgl7Q7SZR+J727V/eCsjMc23QYdUtau57sg+Yx5/jlkljP6+P5T+hasy+TFPuvzen3ekIUZd0a3QtZq7L1vh8xlrKv9Iat7y3j/D7LAH+qyYZLvZ8b7f5DZZuj5giHrrNPzjRGdN+my8VI2R5d9W/T7lj6+k0VmzK2pkFUY/Zghstd12SzILMa+3Sp2Gavnmy86G+84PABZqfFuVCpkjcY7SunSt7V6vkyxlUv3q2WQRbbq+VbIuK3X8+WLXf6l67xS+jZf12+N6GzcXT8t9e017v9Ev4PG/Z/UZ+R7Qeoz7kF+AJn5/kGF6GfM1V1Sn5Hvp2KDb+n6vS5tGDatkfG4Yrz/J20Y4/ZLsf0Hun7vSrtG/DsivrvTeP9Pyr6uy34vMkPnP4l+1cb7f+IHf9Vlp8Wmxp3lJ+KnH+r6fQqZxZiDndJf48x0SWRz9HxfShvGb65fiS7rdZnXN9Cu8VtbH8jCDNltkJUG6rI7Iavup883f8gsT+htDBVZp67zCGnXeIfqHsjM93xDRRfjHc1xkJn+cp+0YfxO8l3IAu/W24iUfpzQZdGQmX46EzJfI17NEf126volShvGvjhZ8g3RZQ9BZq6XaaJzsZ4vA7LWNXo/skU/Y9+eI3bZqJd9XNpdrduqUGxl1cuuFht8Zrz/J7o8q/dtk/TNmB+l0sZVXbZV6uunt/GS1Ndh3P9J2RRdVil9M97l3A1ZpLG/fw0yW7tulzfFBq36nNkvOhtz9SBkVuNs9Y7oMkyv7zdiqzrj/g+yzk912XEp+ydd9kexwZe6/T4QnY36WiXfcL3dM6Kz+f6f5LtNn1t/h8z5a73sRbGVcb97WebWbt0u/xJdLuple/XFGBn7Ux/IwoxzQD/IKvbpNr0DMtsuXTYIstYLetkAyHyb9XzDpV2j7CjInBeN+z/IAg2/CpN2jb5NhKzueb1v3xHZer2+70vfjDuyKMg6jXclY6UN4+5wtujXqueb11d+s9HbSILM9Zmu3yLpr1PPtxgyq6HfUshKjRiRJe3213VeLvp9orfxmIyR8X7Ek1KfMY9ckq9El60TO7v0NjZC1uhn3P9Ju0eM9//EBr/R+7FN2jXm28tigx8Z7//JeCzQdamSfG/rsldFZqx5b4jOxtz6hfiaESdrpY0RuuyQ6Gzcb/xa+vuV3u57IkvSZY2ii7E=
*/