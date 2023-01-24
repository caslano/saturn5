
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_POOLED_FIXEDSIZE_H
#define BOOST_COROUTINES2_POOLED_FIXEDSIZE_H

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/pooled_fixedsize_stack.hpp>

#include <boost/coroutine2/detail/coroutine.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {

using pooled_fixedsize_stack = boost::context::pooled_fixedsize_stack;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_POOLED_FIXEDSIZE_H

/* pooled_fixedsize_stack.hpp
mc4SlZbsy7uSNesqOITk/LkNKWxKwbwVqx+7FQESJ68ceLn2BUWunoPKkonueDLyQyW3kp1H3bGcbGDpLRmj+Ad9mVCgv3M6t+X53f3/LWiz/zdOCwL+9XNa3dzYzN78X5om8NNY+ntZexiAPfKd8f2DV9rg+14G3MCsNCK9FJp49Ly0BLek9DAEn6L5qH8Cn4oiR0ueXrMVoS50keCzNb7B0rB9AkCvQ0i32V2vxcH2Lt4DsZzS6LYi38Gj21JkS3UL+t2lSt4PaF7bcjwN6Dry3Ow4D8iK8/3ddaR/3Abh9drxV+UCxY/N8pTnLuELCZYUKlsllWVPf/TvMXz7an23X3U27k+45HRvJ/fstU6EMMSbrJZKBwOMX4k1hTG1BGNVJNCYR7xBbCnjsKN9ilcwjtyDTTs9avGZf/2YPCQEaXYGISR0kZXlvznsn7zMGm/XRo9Cw04pyusVT4oFCV5wKfgStYqgxdLoJuS/vbpkh9awSSeNCdBme6LrESQ7xnWaehqNpGzf/box5/l8/R4l1nn6CeY/d9yA0xqkD+9YMzy2IwCSZAv5Z5Q9U5dpIjc6wvrrpjc6sv+wTw8lPGGUOqcUyAMBL+pLogPWDi5iGgqkTB9Fuxpmi1DZ0+3V3H1hwaohzVjaHn4FrojoVh30R2+QWUUOD4I8f7ftZNZoxtsT6vLg5mUxH0FlwYiKfQn3C2hgv9Cd0niX
*/