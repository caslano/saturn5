// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_STD_HPP
#define BOOST_ASSIGN_STD_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/std/vector.hpp>
#include <boost/assign/std/deque.hpp>
#include <boost/assign/std/list.hpp>
#include <boost/assign/std/slist.hpp>
#include <boost/assign/std/stack.hpp>
#include <boost/assign/std/queue.hpp>
#include <boost/assign/std/set.hpp>
#include <boost/assign/std/map.hpp>

#endif

/* std.hpp
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
*/