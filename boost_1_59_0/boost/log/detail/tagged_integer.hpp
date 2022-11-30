/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   tagged_integer.hpp
 * \author Andrey Semashev
 * \date   11.01.2008
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_TAGGED_INTEGER_HPP_INCLUDED_
#define BOOST_LOG_TAGGED_INTEGER_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! A tagged integer wrapper for type safety
template< typename IntT, typename TagT >
struct tagged_integer
{
    //! Contained value type
    typedef IntT integer_type;
    //! Tag
    typedef TagT tag;

    //! Contained value
    integer_type value;

    //! Conversion operator
    BOOST_CONSTEXPR operator integer_type() const BOOST_NOEXCEPT { return value; }

    //  Increment
    tagged_integer& operator++ () BOOST_NOEXCEPT { ++value; return *this; }
    tagged_integer operator++ (int) BOOST_NOEXCEPT { tagged_integer temp = *this; ++value; return temp; }
    //  Decrement
    tagged_integer& operator-- () BOOST_NOEXCEPT { --value; return *this; }
    tagged_integer operator-- (int) BOOST_NOEXCEPT { tagged_integer temp = *this; --value; return temp; }

#define BOOST_LOG_TAGGED_INTEGER_OP(op)\
    tagged_integer& operator op (tagged_integer const& that) BOOST_NOEXCEPT { value op that.value; return *this; }

    BOOST_LOG_TAGGED_INTEGER_OP(|=)
    BOOST_LOG_TAGGED_INTEGER_OP(&=)
    BOOST_LOG_TAGGED_INTEGER_OP(^=)
    BOOST_LOG_TAGGED_INTEGER_OP(+=)
    BOOST_LOG_TAGGED_INTEGER_OP(-=)
    BOOST_LOG_TAGGED_INTEGER_OP(*=)
    BOOST_LOG_TAGGED_INTEGER_OP(/=)
    BOOST_LOG_TAGGED_INTEGER_OP(%=)

#undef BOOST_LOG_TAGGED_INTEGER_OP

    //! Inversion operator
    tagged_integer& operator~ () BOOST_NOEXCEPT { ~value; return *this; }

    //  Shift operators
    template< typename T >
    tagged_integer& operator<<= (T const& that) BOOST_NOEXCEPT { value <<= that; return *this; }
    template< typename T >
    tagged_integer& operator>>= (T const& that) BOOST_NOEXCEPT { value >>= that; return *this; }

private:
    //  Protection against improper usage
    template< typename T1, typename T2 >
    tagged_integer& operator<<= (tagged_integer< T1, T2 > const&);
    template< typename T1, typename T2 >
    tagged_integer& operator>>= (tagged_integer< T1, T2 > const&);
};

    //  Relational operators
#define BOOST_LOG_TAGGED_INTEGER_OP(op)\
    template< typename IntT, typename TagT >\
    inline bool operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right) BOOST_NOEXCEPT\
    {\
        return (left.value op right.value);\
    }

BOOST_LOG_TAGGED_INTEGER_OP(==)
BOOST_LOG_TAGGED_INTEGER_OP(!=)
BOOST_LOG_TAGGED_INTEGER_OP(<)
BOOST_LOG_TAGGED_INTEGER_OP(>)
BOOST_LOG_TAGGED_INTEGER_OP(<=)
BOOST_LOG_TAGGED_INTEGER_OP(>=)

#undef BOOST_LOG_TAGGED_INTEGER_OP

#define BOOST_LOG_TAGGED_INTEGER_OP(op)\
    template< typename IntT, typename TagT >\
    inline tagged_integer< IntT, TagT > operator op (\
        tagged_integer< IntT, TagT > const& left, tagged_integer< IntT, TagT > const& right) BOOST_NOEXCEPT\
    {\
        tagged_integer< IntT, TagT > temp = left;\
        temp op##= right;\
        return temp;\
    }

BOOST_LOG_TAGGED_INTEGER_OP(|)
BOOST_LOG_TAGGED_INTEGER_OP(&)
BOOST_LOG_TAGGED_INTEGER_OP(^)
BOOST_LOG_TAGGED_INTEGER_OP(+)
BOOST_LOG_TAGGED_INTEGER_OP(-)
BOOST_LOG_TAGGED_INTEGER_OP(*)
BOOST_LOG_TAGGED_INTEGER_OP(/)
BOOST_LOG_TAGGED_INTEGER_OP(%)

#undef BOOST_LOG_TAGGED_INTEGER_OP

#define BOOST_LOG_TAGGED_INTEGER_OP(op)\
    template< typename IntT, typename TagT, typename T >\
    inline tagged_integer< IntT, TagT > operator op (\
        tagged_integer< IntT, TagT > const& left, T const& right) BOOST_NOEXCEPT\
    {\
        tagged_integer< IntT, TagT > temp = left;\
        temp op##= right;\
        return temp;\
    }

BOOST_LOG_TAGGED_INTEGER_OP(<<)
BOOST_LOG_TAGGED_INTEGER_OP(>>)

#undef BOOST_LOG_TAGGED_INTEGER_OP

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_TAGGED_INTEGER_HPP_INCLUDED_

/* tagged_integer.hpp
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
*/