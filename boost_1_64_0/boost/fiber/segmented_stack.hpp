
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
wTo80vfqneq9lm4taVV+UEmRhQPmT/t80wpPhuQyxWgePzK+uh/yZxaTeh6SgEJv6q/Xns03aStUUhoCpsDtt949EzYJ3Hx4fW8REB6ay3a4l4Gf5/3bh0F+qPq4xVzZ3/CYJoTcF63PG6opIoXOa8kboDFlY4qlxBfG+YiQprW3PS4EVwdS4MWjqUYU/vegiBL/yMMOoeeZIbclVcqOA07bK56s8RH4l4l28Z100ErrubHOJZXThvPtkCG2Hrd86EYq/YTB8Y0LEN1iJ7/mCmUtavrdRgtqRlPnyeUkKbvy8pNMqIuR/eY4zWiDiCO7B6Q7vK6J/Q361H6bt25tA6DZ148c/8Ky8lz6EuscaH6v3aEI1QMaOL88gN2jZo2LbYtXqtj3oUpzIBoLu5LuSF7aaQUnjf401ghUlRs3uwb3xU/pKUojkIX9hoxdhLNpVRmTmPR8QUvUogeo7JmgYybd+toWRlM2Gj4wWfrHGH3GjE6BCpF/7tUmrsVuOYsqj5XGOmA/Bchk+KUTMM0MF8/uf0FdJ6eSKuLBrZWtjCFmgiENkGb+H79Pvg==
*/