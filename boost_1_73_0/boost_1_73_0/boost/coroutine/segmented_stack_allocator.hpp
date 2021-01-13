
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined(BOOST_USE_SEGMENTED_STACKS)
# if defined(BOOST_WINDOWS)
#  error "segmented stacks are not supported by Windows"
# else
#  include <boost/coroutine/posix/segmented_stack_allocator.hpp>
# endif
#endif

/* segmented_stack_allocator.hpp
Mprt6WkQufwWK+1ckYBaS720ccfEOxSfLQwV+sujJX8v0gI5lvQG9vlg
*/