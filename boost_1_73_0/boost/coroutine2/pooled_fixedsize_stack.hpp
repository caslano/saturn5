
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
5c3cd3rl+dYq5z/oebBR5XnkldjrjaqctzTnv059kVdnO/b1vutRuO618ZEPn9h6d9/3334vLivmlRUbi7H03XKjyHHRN1Sv4lbMYP39JuZo/Z1iU4b6+wfMXc7ct40hriFq39xWnYzR7wpwtI/uo24B5Jhgd9gK9oAHwcPhwXAQ7Al7wUGwNxwK+8BRct3VMbZZ4znER8fYMNw5PB7WgyfANHgi7AjHarzjYGd4Muyu55oP
*/