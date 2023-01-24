
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_FORCED_UNWIND_HPP
#define BOOST_COROUTINES2_DETAIL_FORCED_UNWIND_HPP

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

struct forced_unwind {};

inline
void * unwind_coroutine( void * data) {
    throw forced_unwind{};
    return data;
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_FORCED_UNWIND_HPP

/* forced_unwind.hpp
EyXyvO+zezjWH/Y5z75XbnA7DJ4F73sU0bU4r6ckJVgUsfKM2vPgQKCGgvNSB1RDmxtF89yzuLNUrCxuqBmk1qhrBo5ne5Ln6b4ookztWzCNsodA3x9Qwp13RxPfkdyFSPE86Ckqx80Ar8Wt2W1SE0PJ4hLFGYs1foTqm14LisNSDeMNo8d/tPgWofQh5/7LJn6xktT7ExRTZHc2agWFsh2+W8L2q/4Eak6pmdWvAm2mFiv97TjJ8WOcv8Nb6ZWwNNPf69hc/wveLP8N3kJCfx8rW5uaO7j+G7rdNEfcu6/fMOJexvUuHx4xrqH/8VHqL2+4MGeRdWn0pjJm4mnMdKthN5UL1fA7bgYa8J8mq6wjvn+JVZj7AWOtsgYPr71mq05k9dhYtJ8rtp9tVMlgtc5KGrTfawTcOoOpGhGHljlaPVZ/5oD3wRNAz81Occ/DzTZXy8PuFcSqNkX3c4SSsH/ccCFMU2ZgxSUjWd4UT/br++2f5wMrdgD5KeQ7xMci2/cE1806k6a42X5TSoHmvS7bdt+wnP6Wj52yd2kzOT4YvVPY4J2DWIq9V/suLfbIHlTyOdi0JYh9Tp3DeUniPi6MYoLkhsLMnSGnBbahetb9UJaqU2f3Vh3X/QsYjvbjZxf+V5pgueZcEbM8mvSPyK+zcjDRuRlvtlo1DTGsrQ7mecPTlZfgu5/yRaI/IUuYRmxzySieb2QH++dW
*/