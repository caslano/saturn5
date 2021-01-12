
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
1Pb5lrg/1d+HuYXzfDHWL31o1PfHWdmIR90g/Mh3zSW836Zua74G00VXtn8gNaOMHHiCWH+A+NEIOQUt42uR15FPEY+6RPiR756ZrHHdE2+X8H1Wb60raWJu6M/F9wSudz3n7qUkXkU+REb7eM/qS7L2+eKtvyFe9dF9zcqAGUd7rQ/BrXfd7aht63M539X/FOOLT5EE9IrP9MVZ69F0+74vwbL9Ca7nmnmz3fMxR8RvL6u7
*/