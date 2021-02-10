/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MAX_ALIGN_HPP
#define BOOST_ALIGN_DETAIL_MAX_ALIGN_HPP

#include <boost/align/detail/max_size.hpp>
#include <boost/align/alignment_of.hpp>

namespace boost {
namespace alignment {
namespace detail {

template<class A, class B>
struct max_align
    : max_size<alignment_of<A>::value, alignment_of<B>::value> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* max_align.hpp
CtbQ6FDdAw9aP3r+AlUpdPARSTsmfti4Qm1eXTNuGmHseBJH9rD9hkameGvNnNRTKNPmx+TI4VDot4+z3t7U86Lv6Q6tkM2jUtjug9F9V3v0XLMRhX+6dy8Q8AHLAo2dGizR3WxEqjxD4rq2PemtGF0oABYWgFmsaf/d7CiCznZBT6YwoGmiec/VjQq9rEU0wKDAiqShxq0ZcqOr3h7w8HMT1GDvGK6W7gCz1wfRlkvdyloTy3jMoe/XElH4x+4xMZSe4FWz4DqpI2951jKaBQKqrvhZonMpSwjNJK1dr7vKgKgWOUecDSEciFghIWfgKIaLEGHwsJlVGFZjn6eNKx+qnYOoG6hRFm7TZm8PL9vQO0lmGC5WFeM+u2J6U5XIpAnWEreeaEyc2jALT7zsoX2yUi5ec6SrkMQGaKWeQt20bRhiHmNdhUZYdly+VmtiCID32qRpZLaIQ56PifjszDE38T2wjSOky0qj4hzJtdSCt0zZMH6t/bqp5FynpR48DjcpM4Zl07hfbDpZzWpdxa8W5ptFapWGb4T0wVT02NJ+wayMpAWtKu8NTcf0ZhKCQhN7hb8gRnMxnluxpm9n2FAMHlp7wOQQSs/Ct0st0sIqDIzu2FhAj5Rk2cWq7Cg9x3ETn2tQOUq70l6l
*/