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
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
*/