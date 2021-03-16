
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_SEGMENTED_H
#define BOOST_COROUTINES2_SEGMENTED_H

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/segmented_stack.hpp>

#include <boost/coroutine2/detail/coroutine.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {

#if defined(BOOST_USE_SEGMENTED_STACKS)
# if ! defined(BOOST_WINDOWS)
using segmented_stack = boost::context::segmented_stack;
using default_stack = boost::context::default_stack;
# endif
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_SEGMENTED_H

/* segmented_stack.hpp
52t6pHOGaxpOClrh9ELgMseGyLr65M35TZcWxhu6yP2gR8/uUSSbzpZfy1fzyB5Yyi4+VSkrNoLA9Vg2PZRzFAi7lFBJelhr3HJusoUCu71HaDTUYVTfqemFiRR3+tcKesmvpIbwGrTCTxq26pgFBcUcBz8cmmw6bMsmO3j9Z5WeKxova0DmCEWqkk210Z6PF5qKZ34SRlbTUQ0suG12sgdkAq+7GiI7qQrP+emKvYj2QRdW16hxMvOJhmuIhqo=
*/