
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
Oo+enaKDY0StzT3Bkkuj++vneQDPOPoKnRMAciLsIF+1Z50Vcxg6bzNXNNmgQpg6xehFVJuCIvlemV4DCZAbIoj4mQq1Q1zgPc+2TdX6ez3EIJv1ZEbWimgUd3OAnq7y43pSrTcvqBhC7faeXiRXwQkmYSqpRlIZPYmh5DvZ2dIe4/kRFo1ciYALsaRUMCWUuQcapkg7QZcsX5dcCetERRSKeDFlJN8TyfUjqo4B2gMi5UF8w2SkpbMVQkCHXhI=
*/