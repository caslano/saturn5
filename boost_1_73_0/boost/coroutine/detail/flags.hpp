
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_FLAGS_H
#define BOOST_COROUTINES_DETAIL_FLAGS_H

#include <boost/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

enum flag_t
{
    flag_started        = 1 << 1,
    flag_running        = 1 << 2,
    flag_complete       = 1 << 3,
    flag_unwind_stack   = 1 << 4,
    flag_force_unwind   = 1 << 5
};

struct unwind_t
{
    enum flag_t
    { force_unwind = 1 };
};

struct synthesized_t
{
    enum flag_t
    { syntesized = 1 };
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_FLAGS_H

/* flags.hpp
r9H2kC/92Cd96t+umjcjg/tXuf5AIJfR89RAgnUj5vZAxLd9mbDMOh+ZxzDldL9cP8h/jdDe7XjqHM/6pA/k+lN2Em86vuuGuB47xhSUVFRuSanyBbSvjY6bD+00pCcm8uaYqWGvE/ttVmskWi5T2U9n/z13/o0FK1omGfAbiev8wEy7n7XaHoxu4pBVHGig68mQZnnDuf4wshmlfuOXpOU5CaNSx8tO4npJzu8IVDdP/Ipc
*/