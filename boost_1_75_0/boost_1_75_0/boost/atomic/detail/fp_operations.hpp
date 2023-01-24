/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/fp_operations.hpp
 *
 * This header defines floating point atomic operations, including the generic version.
 */

#ifndef BOOST_ATOMIC_DETAIL_FP_OPERATIONS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_FP_OPERATIONS_HPP_INCLUDED_

#include <boost/atomic/detail/fp_ops_generic.hpp>
#include <boost/atomic/detail/fp_ops_emulated.hpp>

#if !defined(BOOST_ATOMIC_DETAIL_FP_BACKEND_GENERIC)
#include BOOST_ATOMIC_DETAIL_FP_BACKEND_HEADER(boost/atomic/detail/fp_ops_)
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_ATOMIC_DETAIL_FP_OPERATIONS_HPP_INCLUDED_

/* fp_operations.hpp
4Lh5zGB5s7mbA3A8m/coBU6r2H3RO43Ii5JPy3dKXTz6v+BIyBSVzjdxQXy9ki+aKSgoSk/kHRcWMbpozMxqcqYNWbXotVSHfk78ZBQZiRG7qIjEZpkKs4RqbgbzJT+ZwGyObQiOnHKHa0O/KLs5Xef9YhcUKCLQFMIU3xW7QM+T018bhV9bEu4i4OiRLCnfnDXvSlwhb4Et7otty36xL9OxRLgqsbGEm2gpWNFeerMiCKa8A+ond39rGx1dF9JAXEeqoBXTp6cXJ8auyJ1XriqHZ911thafpmO2uFs3bovRm1xp/m1JJSZO38Uiv1ZffDZmgrMOyx68IJIeiMG/KUZKTqptMq4w552gVsQsz+cbVnAReLFO2xa+/X0oHckaWj3r13A6InlXTO2XWngQE6mO/ItxzMsYaC2mI44eIt+FlNWXfT1IwC7+tOjvHYg6p+6dQBJ8TduwwCcbb7ikPe8vFS2nba6MXQH/64Mn4ZjRdFmrMVAPRfvbU60jf+5Ax3QhkCnLoBz3lKJXknF+Eq9zuQU+jUqiC4fjgdc7d6dgd5GUaeVm8OvMAuzE+x/cdmCGlW6quzifp83rAieC+zgNUlDc+nUG1wH/AbEDUX5IQ8k7TKzEqeVh4u/inF0uALP9Cya1XUTPYZTvfHGsyZjHryCiPYE+e9ttJfwkhdGMI23KFeJjN57fnlpaybhJp5afUIx5O07CNNdA
*/