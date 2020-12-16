/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/log_name.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c log_name keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_LOG_NAME_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_LOG_NAME_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass event log name to a sink backend
BOOST_PARAMETER_KEYWORD(tag, log_name)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_LOG_NAME_HPP_INCLUDED_

/* log_name.hpp
dSWR72ziv9YVWXVd6yrpFD/s4nN7Ngo71HXVz3Jtm5Uh3y3v1O+Ww1CGrhYCD9u2vm8ytv60GgqXl1SWLmCIXsRxBSMkzDa3etH4PBzTsFwLlxVqeL+9TfGT5VYfhHdrR6PExmG+uLX0qn6wlZP5gI3mSeIe73WMZZRxGK003YfFfULcCOtfHl9eqNlb7GOtHbYti0sXOmxbutmwbrbJ155D4tD1VDQOWrfzmvebTSbPYoM0RJdMGl+82fa3mm8HncXvHvV7nc/vfNJixlGMkvw0l/ymD9TyqAqs0XK1uL8bF9DtpVVkzuRjh6SpJCwfgfgkOmOL9RqJ7704O5/9JL5yGbjhXG+mTNKfrfsaJ9fCQJ1JlZk0XCdpaCdtJp7+4gUuSC/bNq2bzHbaHZT20kn9WE3Vj2fNm2Ir+6I6bGVrmGx/mCZrL9B4w/yMw88rYk97bcAeXoifJX4/zdZOiORnR1Nt9ynrkt3a/QyOpXLsaBcRM15lL5yofUCfVoF+IT8r8PtieBn7uNOfixAmcK833XWci7td0wtvqXv9nfSgb/jajsPskKLr6ne/sUMa0H/8ig6b60ZIvzRFE/mKhEP/kUc4X85m0y9h/LS8uMTfPVnh1wfTL0mYg279ksZHvo3uiuqaZ8PPi3t/Wmgjx7VAhkKb9jRV/DwUeh0w/c9scb9Pzn9C2+3CQLuV4yf12r2T/vjx5uZZ6Ak3PcniWGNL6pt6Njpg6vxwG1+dp0a2ty31/NZmU8+Rrh2S3pBru6R1oRwj/SG2Y5+W/9jYQTxIHrIKvyO2mHpbWrVwWunCMaULuaiH1pnp7/LE/wjy4XGrN43P43imR7fc78HwG2L7WfXQ9Xk8JO75bXxjzJx92Rxxbxc0tqyWOthGgX9APbzaus7n0gn1XavJT1D7SYGk27Sf0GfH/frQeBhpb+8j37XXjnAvc7nxtYLaSzGHA/c2T0q4e7mypbmVvcbrcdZd5XxH3T0m7g9Y1a7r/JnwEa+tLtdLc31sRxs5RK6zW/v6P2/nhDhv24T4FAqtjvqIWJevaF36r0vDttr77aWdadvTe2RfnY5z3n9F7keD69eUL/VrjlFmDewzpc5D1kZorwloh9xgP1NtdY4fDLuFlvun5XW8LyC8qZsTxm65e7ty+qW4+UVC3duU8evsz1a3rH8Mmb6H0PvXuaYMTwTbztbzcUzT4CyrI2nhYxBriO/4VjM2z6Ws6n+3IuH5Uxv1Oo4vgj1dl/yvieKZNvQ9jOZf7YxzPpNXtSWcHm5L+PGB/NvmtCVMX1BWUilrZmD02d8XPFa3/WDiOHO7z48Zm8DB6a1oE57eA/htESm98hYpuvS22Ba9veMW287c3vFjUdg7HqX5XZIRnt+8jsRo8js2b1Le5SPzCyeNvCxvWmFFeYW+6SPP8m637jwTj7nWFfvmkhB6QU3ZfPd8q3/He9no801aNN+Be0LOyTFzTjNm0zoDW8/uYzk/OZvOH8nYzLnDxzU/8OqxJS8OOvyFJ19/6/lIYy0/Pbaez5VNZ3fbzQ0fe/vfZuv5XNp01vUl5JvIaY/Ym5TnzxyYibwS+C3v7w7C1shYx+/xjt/5+nsbIrZI/d914CHkYIgt0r469nUAbAkHwrZwEBSb0vBiOBSOgcPhTDgKFsPRcJHuL4Z5sBJeClfDsXADvAxugjPgzXA83A4nwC+q+051vwdOgfvgNPg0nB6wgatjWfVbhub7YMhY1tbq704kR/3NVX8tkC3qbzn+bK6AKXAlbAGvhRlqczoTXg+7wVXwIvg52BfeAPvD1XCY2p4eDdfCifBGOA2uh3PgBlgENzrysVfT17yOfFQgR9TfOvVnbDs=
*/