/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   process_id.hpp
 * \author Andrey Semashev
 * \date   12.09.2009
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_PROCESS_ID_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_PROCESS_ID_HPP_INCLUDED_

#include <iosfwd>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/id.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The process id descriptor
struct process
{
    typedef unsigned long native_type;
    typedef boost::log::aux::id< process > id;
};

namespace this_process {

//! The function returns current process identifier
BOOST_LOG_API process::id get_id();

} // namespace this_process

template< typename CharT, typename TraitsT >
BOOST_LOG_API std::basic_ostream< CharT, TraitsT >&
operator<< (std::basic_ostream< CharT, TraitsT >& strm, process::id const& pid);

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_PROCESS_ID_HPP_INCLUDED_

/* process_id.hpp
APC3UpDDf7y8kDp26BApXXgzbLQVcmdmM8sdGCHAjvgp0p070Re6f4nyj8zzmAb+9JsYUy/+F43cvY3WDBKn/k3o6r835oe9vHPbJlV0Dq/ZA13i17b64btoHUHfEXaJ9fx/fcAPQw+EP02Jm++B3+ZfPOOHw6nzlk1b0hs7O7e/9ArTNKBfN/3beT4NDdNz4J1FWf7656gsfo6AP5fGWv1rqUPidwG46Qza5/VMvnDk4NF9ar8Fti1p5vG5g8Rjc8dmLgLjp/agrx7sUr09k4F90fBO9PcHpom2c+OOjUw8RfiON7EHte7f2fjNJEgQVvkmZMZ7X9330gm2DwCu6ROQ0z//8PE9R+RESvkuRhozlG5l1adzhQKMv5D4/kHgU5vQj37oC++yUZjqYcjnrU+gXP9qwCeX8p6j8VBddf0AyksKOQfJVY5MI40pj2VCfb3UHfcD4C/w+XTNXwG5e9eWHemdGzuAv9KBNv6V5xjfuXPHZivs9puQ419Zw2HUbySI+bVj3mn6p69zWFea1rGbGD/J/W1sHeONeOe8X81i3P7x8AESs5C9sAfL78Fac/FWjLttu7a/qmajTAZh43uQxpoZFcC9k/F3enCWtWGf4LVP8I9tTqt4wx9H+M/8WCC8c6eEn9qDdfIzTeHwHZtflrxeT0PubPls3+HjyGrmDsUrQJ63/Fwj5XXTxo6OTVQjCp9BPldkN23a
*/