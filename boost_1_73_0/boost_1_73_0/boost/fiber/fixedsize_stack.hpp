
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_FIXEDSIZE_STACK_H
#define BOOST_FIBERS_FIXEDSIZE_STACK_H

#include <boost/config.hpp>
#include <boost/context/fixedsize_stack.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

using fixedsize_stack = boost::context::fixedsize_stack;
#if !defined(BOOST_USE_SEGMENTED_STACKS)
using   default_stack = boost::context::default_stack;
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_FIXEDSIZE_STACK_H

/* fixedsize_stack.hpp
mOqr4MmHpptWHp/CsfjKZmq6BmSfW5VAVl18CsfiazBTffV9sKCHaTXIp3AsvnKElVHmS5p8vU2rCT6FY/E1hKm+hnZ5oq9pNduncCy+cplaNl4r6/yIabXap3AsvvKY6uuhHx/9wrTa7lM4Fl9DmZquL99+Z6Fp9VufwrH4GsZUXyvuTdloWj3rUzhMXWFrODPSZf+c8Ckcsfe/PtlOSkRdkWoEItzoQ73W77ZqprfljP2fz+R4LFYjhVV7nbc=
*/