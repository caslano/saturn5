/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   bind_to_log.hpp
 * \author Andrey Semashev
 * \date   06.11.2012
 *
 * This header contains a function object that puts the received value to the bound stream using the \c to_log manipulator.
 * This is a lightweight alternative to what Boost.Phoenix and Boost.Lambda provides.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_BIND_TO_LOG_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_BIND_TO_LOG_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/utility/manipulators/to_log.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The function object that outputs its second operand to the first one
template< typename TagT = void >
struct to_log_fun
{
    typedef void result_type;

    template< typename StreamT, typename T >
    void operator() (StreamT& strm, T const& val) const
    {
        strm << boost::log::to_log< TagT >(val);
    }
};

//! The function object that outputs its second operand to the first one
template< >
struct to_log_fun< void >
{
    typedef void result_type;

    template< typename StreamT, typename T >
    void operator() (StreamT& strm, T const& val) const
    {
        strm << boost::log::to_log(val);
    }
};

template< typename StreamT >
BOOST_FORCEINLINE binder1st< to_log_fun< >, StreamT& > bind_to_log(StreamT& strm)
{
    return binder1st< to_log_fun< >, StreamT& >(to_log_fun< >(), strm);
}

template< typename TagT, typename StreamT >
BOOST_FORCEINLINE binder1st< to_log_fun< TagT >, StreamT& > bind_to_log(StreamT& strm)
{
    return binder1st< to_log_fun< TagT >, StreamT& >(to_log_fun< TagT >(), strm);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_BIND_TO_LOG_HPP_INCLUDED_

/* bind_to_log.hpp
BXxhyertYygZjPW+0lRft43zsn1jYlV/oqN44t6/pjMv67Z55yefR9lU87dcZNBZiz+dF5Vf7VN6lYEi8HfbhNi1Xm/qMkeasDXNB7FmwSMMXfu9dG2eByPgxFoVKPtQQWX6HuLEzcLiTtXgCi+TnAwKpkrx9FqYm437tWkKO8Q7BTmQ8M15pS5AxSECKBi6pB58WXHOCwxQbuGgtCus07JRZhUS/9oATH7R/Tvy6FCbF/A720n3B+mlbvq1Xb0NF/zq2p/kxjf8c/61egv+ImQmXpXNQtzZiqYjE+Z7wd0FYx0BXKgggaIYAamGUHbPBCfdLTE6mtsZPUm32XGRxzUr9aVDI9lVdkH2EnIqL2P/de5PFwy0tEF+6TZ+FwrrYRi/nERiL8kvfDOV3tOVhmn54RbUN9u0vbr9fnE+asp3BGts5uFS6mleCQbLvYxIfDEkyEkAM/WokND4EvkKZuz9HkOv08IZf3yZhjE5FG9mgBdT6fkT4t176RBlnA95hGqZhBs5qxdbxfLg2NbdRrNiJebxiquFWvM3VYEBK9biStFr7XLLE6nURqKF6sUQAkh1sX/Ggmk7jUGRUdAa+rnFp2tx3WogGGjAFfKTv9fe+uQsioLRwCBDxqVsSVDHeHk6xKHHYKEk4rdqPJ+2f6ZAZy7xgu7U6S+mheEm0QcfZlMJJcYvgtbdEmnoFcaKtX1lsyN2wUkbDLDf
*/