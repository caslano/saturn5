/*
 *          Copyright Andrey Semashev 2007 - 2013.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

/*!
 * \file   explicit_operator_bool.hpp
 * \author Andrey Semashev
 * \date   08.03.2009
 *
 * This header defines a compatibility macro that implements an unspecified
 * \c bool operator idiom, which is superseded with explicit conversion operators in
 * C++11.
 */

#ifndef BOOST_CORE_EXPLICIT_OPERATOR_BOOL_HPP
#define BOOST_CORE_EXPLICIT_OPERATOR_BOOL_HPP

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if !defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)

/*!
 * \brief The macro defines an explicit operator of conversion to \c bool
 *
 * The macro should be used inside the definition of a class that has to
 * support the conversion. The class should also implement <tt>operator!</tt>,
 * in terms of which the conversion operator will be implemented.
 */
#define BOOST_EXPLICIT_OPERATOR_BOOL()\
    BOOST_FORCEINLINE explicit operator bool () const\
    {\
        return !this->operator! ();\
    }

/*!
 * \brief The macro defines a noexcept explicit operator of conversion to \c bool
 *
 * The macro should be used inside the definition of a class that has to
 * support the conversion. The class should also implement <tt>operator!</tt>,
 * in terms of which the conversion operator will be implemented.
 */
#define BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()\
    BOOST_FORCEINLINE explicit operator bool () const BOOST_NOEXCEPT\
    {\
        return !this->operator! ();\
    }

#if !BOOST_WORKAROUND(BOOST_GCC, < 40700)

/*!
 * \brief The macro defines a constexpr explicit operator of conversion to \c bool
 *
 * The macro should be used inside the definition of a class that has to
 * support the conversion. The class should also implement <tt>operator!</tt>,
 * in terms of which the conversion operator will be implemented.
 */
#define BOOST_CONSTEXPR_EXPLICIT_OPERATOR_BOOL()\
    BOOST_FORCEINLINE BOOST_CONSTEXPR explicit operator bool () const BOOST_NOEXCEPT\
    {\
        return !this->operator! ();\
    }

#else

#define BOOST_CONSTEXPR_EXPLICIT_OPERATOR_BOOL() BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()

#endif

#else // !defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)

#if (defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x530)) && !defined(BOOST_NO_COMPILER_CONFIG)
// Sun C++ 5.3 can't handle the safe_bool idiom, so don't use it
#define BOOST_NO_UNSPECIFIED_BOOL
#endif // (defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x530)) && !defined(BOOST_NO_COMPILER_CONFIG)

#if !defined(BOOST_NO_UNSPECIFIED_BOOL)

namespace boost {

namespace detail {

#if !defined(_MSC_VER) && !defined(__IBMCPP__)

    struct unspecified_bool
    {
        // NOTE TO THE USER: If you see this in error messages then you tried
        // to apply an unsupported operator on the object that supports
        // explicit conversion to bool.
        struct OPERATORS_NOT_ALLOWED;
        static void true_value(OPERATORS_NOT_ALLOWED*) {}
    };
    typedef void (*unspecified_bool_type)(unspecified_bool::OPERATORS_NOT_ALLOWED*);

#else

    // MSVC and VACPP are too eager to convert pointer to function to void* even though they shouldn't
    struct unspecified_bool
    {
        // NOTE TO THE USER: If you see this in error messages then you tried
        // to apply an unsupported operator on the object that supports
        // explicit conversion to bool.
        struct OPERATORS_NOT_ALLOWED;
        void true_value(OPERATORS_NOT_ALLOWED*) {}
    };
    typedef void (unspecified_bool::*unspecified_bool_type)(unspecified_bool::OPERATORS_NOT_ALLOWED*);

#endif

} // namespace detail

} // namespace boost

#define BOOST_EXPLICIT_OPERATOR_BOOL()\
    BOOST_FORCEINLINE operator boost::detail::unspecified_bool_type () const\
    {\
        return (!this->operator! () ? &boost::detail::unspecified_bool::true_value : (boost::detail::unspecified_bool_type)0);\
    }

#define BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()\
    BOOST_FORCEINLINE operator boost::detail::unspecified_bool_type () const BOOST_NOEXCEPT\
    {\
        return (!this->operator! () ? &boost::detail::unspecified_bool::true_value : (boost::detail::unspecified_bool_type)0);\
    }

#define BOOST_CONSTEXPR_EXPLICIT_OPERATOR_BOOL()\
    BOOST_FORCEINLINE BOOST_CONSTEXPR operator boost::detail::unspecified_bool_type () const BOOST_NOEXCEPT\
    {\
        return (!this->operator! () ? &boost::detail::unspecified_bool::true_value : (boost::detail::unspecified_bool_type)0);\
    }

#else // !defined(BOOST_NO_UNSPECIFIED_BOOL)

#define BOOST_EXPLICIT_OPERATOR_BOOL()\
    BOOST_FORCEINLINE operator bool () const\
    {\
        return !this->operator! ();\
    }

#define BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()\
    BOOST_FORCEINLINE operator bool () const BOOST_NOEXCEPT\
    {\
        return !this->operator! ();\
    }

#define BOOST_CONSTEXPR_EXPLICIT_OPERATOR_BOOL()\
    BOOST_FORCEINLINE BOOST_CONSTEXPR operator bool () const BOOST_NOEXCEPT\
    {\
        return !this->operator! ();\
    }

#endif // !defined(BOOST_NO_UNSPECIFIED_BOOL)

#endif // !defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)

#endif // BOOST_CORE_EXPLICIT_OPERATOR_BOOL_HPP

/* explicit_operator_bool.hpp
31XobJT2p5s+tmH3cpsLoSmvcZjEls/xDn/RjvAnLJc4Pja+fXTInNIa/PIA755jPyjEJzba27XnIVG6dBvu1I0eKnTcG+438D4fmEj/RivnAA8P+QiVnAiSn50Y8sQ81d+ErQPuxgfAZ0H3HjkbPFVgxypYu3EJI49vis+O15xesDh2hvJoNXbbt+1IW9Ecexf2fopfCs8+9MOwNDrSBX9Ef2/lRYvnP1eFUmLGdt++MzKjb8i+xMqkuNYr/TcjQmM2wDjlAeobX3r3eoOH9+seGxkPj2cf3CQ4E1D1J45dPl5eFNVYPk/K8JCbbr4JN8w46NT2fqpamUz/yOUjb0C+Orqf2gJZGKuRTSrDkPHifm4DHut4SvGUga07hyRfNO/vAz8zTXj4WIJ5xDxGQZP9jMnWJwoBra1jvozsknCtUed8ZJz4gN4Ske12mv4oZ9BLmjk3CnQFDdXAznD1VEjT9mlB22IVD9wY/JlOW43ks4GJeHvQEozmUjHCT72BzHFuMuCJcAnSfRU1BW3uPO3wcol4nMrGdrqwU1BVVdJpjy8PSwUcprSXzkJnHVmGwOhy17ERGTpDdGJ8lXUxfmnH+eJFGR4TUw+zabvX19P7PbP9jo7uWnb2cuJrbEBnGr6venusc3y8zfuN/AQ0aprqbquyg8XVXNx0HpPNvInt6g2jpGhvfMJ5BLu1GB8hINvkgNei0S+Rn/F/4CIHh20Y0tzUM9s8GzbxCUt/EJ8+El3fngt9RlSP9I8foY0PlzSC+vB84PQD2wjOs0iyKZc6V41PIV/JFc9qVtHzAJ6CLf1F+BMS0sSR4RdrOKRjGKqojcThWU5t2r0pwzdnnX3ei1rEB9Rv0WeXt0quxBwY1xBnTELz5S0ZPr3kNeHcOXub4Px4cPWRej2vlVA8nMknkhwZfV5L7bLc8yiyJyyW25dARw+Wn6lN55UaSLsKpMdLgIfVzLvMiyhum5Cu6L0+NaroNu3PzwO9sq+eQzZ2tn32Z/w0lvt8s53cB8ra3EflgxdCp7s/EPsA0F7T8Xoey4e+E82HLspspQxg7rdY3xtxkQb3qqxdovIRJdTiLp5jrr3GkTcJn3bX4hFvLTbnRsCZ8K490syhN6h2HjJHa0yV8ZGc5U3A+0sM63UJ8H5z41OC05PBtrmU4WJXngcjLtLg3u60m3Tm/GWCo92QyVGz9pervjoGhv9H7dtF85n1sbq8aznDXV4XmTZYr2i9u4rWi+GR4XE/x363j0dz3mO9z8ervir3Kk8hS62lmW9b7x2ZuTCL2Rw7L/h97MwG+yAjX0anWZ5plNOn+JszKudw90z61wZ1uQ3ShAy+xzSoF4BAnQUYvJrjH1mOOIA53g26a2Xef1RgqxSs43kf+72Au6L9vHmp9ek+cSZj6MkyVKS720fY2r4lVZvfPFY5G0c/nvlnWffS/hq0pflEjEaMktEcPNal4T2POW+J8Wkm9TRqUJy93qdLjE6G12cCGuJFPv850AkFhtO2/3zWPqIK599f9OgSl459humS7AeAM/xXKWcc3rZ9486tQyrqGfvdEOKDc+qvLTJ9Ee5W/tcj7XE6YOR/0+1Hkk4UstO3rJ3qzQqdJ8TaaWezNc8lHk2zoqiM7FtIN+q6kf2jY4xsdNnma99Hu41j24Oa9Q99fiYJtvb4cWwfST52a8BDZxI8prcRDQ8JxxIKIEmKTdMUqu37POxmwdjnFz6N3oAbO/xyOY970cBvN3C3Fvfr0BeidyN+y3QkmH3uDiNDj3wxsXdL/yDjoxDc5k6BT0DZ9PH6jmNikg/fNz6+O5YLLTrejLNEQvgl4USS4HQOuTJYC9xlQ34slsbZ8qk=
*/