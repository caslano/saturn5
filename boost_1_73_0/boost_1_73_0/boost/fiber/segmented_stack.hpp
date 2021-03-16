
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_SEGMENTED_STACK_H
#define BOOST_FIBERS_SEGMENTED_STACK_H

#include <boost/config.hpp>
#include <boost/context/segmented_stack.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

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

#endif // BOOST_FIBERS_SEGMENTED_STACK_H

/* segmented_stack.hpp
HkyrJbXtcOejI904MJ8v5X00/HfAzLY/lVo9X9z56Gk573QPq8vKWs6dryniUA3znx/T+H4N7qtV/HhQ/bZeLfvyEcHgrq/m20v1136Nh/XcGr7+aOBfB/N6Bp8fvf1wFMxn7/HjEYH+a7rWwxqQyc8Puv/XdL2uvf7gLq/n29sCDQzegPrbaHMtDb5sHIR7b/KwLtmfVq5el0zjOz1Hzi8MSCq4A9tt1rSe0vE/cIeHNW2nzZnut8eg/06DCck=
*/