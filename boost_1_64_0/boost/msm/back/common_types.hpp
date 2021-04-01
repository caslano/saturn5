// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_COMMON_TYPES_H
#define BOOST_MSM_COMMON_TYPES_H

#include <boost/tuple/tuple.hpp>
#include <boost/msm/common.hpp>

namespace boost { namespace msm { namespace back
{
// used for disable_if
template <int> struct dummy { dummy(int) {} };
// return value for transition handling
typedef enum
{
    HANDLED_FALSE=0,
    HANDLED_TRUE =1,
    HANDLED_GUARD_REJECT=2,
    HANDLED_DEFERRED=4
} HandledEnum;

typedef HandledEnum execute_return;

// source of event provided to RTC algorithm
enum EventSourceEnum
{
    EVENT_SOURCE_DEFAULT=0,
    EVENT_SOURCE_DIRECT=1,
    EVENT_SOURCE_DEFERRED=2,
    EVENT_SOURCE_MSG_QUEUE=4
};

typedef unsigned char EventSource;

}}}

#endif //BOOST_MSM_COMMON_TYPES_H


/* common_types.hpp
2UmXV34mFdrjI6TK4laCbLxCC0WbseZIDfVPrx3YCgZUKBFkzVhyYRSQcEsU9Pzu9b2BJ89DoweMB+HgDuRJZmOdA5Yl6RRchTGevZBTt/tNh7FbvfLrKz7tWjiMLDDTZe8UEJTFIRl88l/B1oeuCF9bSSjckt1RENGvsT6/cXefliQfPv3GSN+o/2b+W43XNb6ulkAHnLMZ9MjwTZEJ3Syk0WzumZpkJplkH+8GPOF3tOYT7DnJ60RSLO9OyDEye/3hRVcuyN7dCjO0dhI1+rBl3mWeyxEiDdaT/YErcbpvozAUDMuMTcZ3oYZXLyasWud5EFNxciMqMakss2emmCXJPtkBBTVUlmWV4m5ZnyXvp3DbwmLdnLIEgXRd2HG7o329I1yp+ZHd7ZLN+6ubTFCPvAVax25s8AJBEGmnASKFp/OmzSCpIzoGZr/G1gQhp/+pR5m9HeVNa66WKlFVD8wzd8fivzbs64K4q95enMV6Wss2WQa2PREICRk6W8aANfgH8SPeXjeW92r+rJ7TOmTXhxHDTnbH34fGhEfApm5jib9RdPBLtEWghg==
*/