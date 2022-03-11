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