
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_ALL_H
#define BOOST_COROUTINES_ALL_H

#include <boost/coroutine/attributes.hpp>
#include <boost/coroutine/coroutine.hpp>
#include <boost/coroutine/exceptions.hpp>
#include <boost/coroutine/flags.hpp>
#include <boost/coroutine/protected_stack_allocator.hpp>
#include <boost/coroutine/segmented_stack_allocator.hpp>
#include <boost/coroutine/stack_allocator.hpp>
#include <boost/coroutine/stack_context.hpp>
#include <boost/coroutine/stack_traits.hpp>
#include <boost/coroutine/standard_stack_allocator.hpp>

#endif // BOOST_COROUTINES_ALL_H

/* all.hpp
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
*/