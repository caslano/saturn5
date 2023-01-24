
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
4+0j2NukmxskaJxunGmcWzPuMOow7jDmMAEdjQwe/OxC24xn/M1YloWeVB3rMHj0M+Szm4kjbcvHetUFFJC5CJ5ditfdsWdeNcaR50biNArj9CuBhEdkOe9kesO4oPey9Q0sEwwJkOzdD0O2EeY8Mpx6b5cqExQjfjS8SYxZNKUPtU4A4Sd0EAythCTV8w9ph5gzqdQ3ynM2ytUTMqTL1RVFJZjbxklKyhIk0CMFgu8IwRfH4EOhGbWtMyIn15jWtk8G2M/E4CbMrXkWp0N+p31yp90bxSB+tYuNtxcGwT/sIn+wSHcmv8shpzViwgfY4UElw6wSwMyBYDrCBK4j4QvSIgfZWTuwJ0QVSiEK93yrtYDiKvKSW66XSJy1Nof0S1pcBRgERUj19Hfb6ut8cv2F9CuMjFPNwbi6T1JFLnFFhM66DLpE9IFx3SxDq61JjUoJ1WVJ5SxDU61JOUoJaWVJiSxD/a1JrzVICujRGIcecp2qSf+mD0WI6nsbQxFHT5CaT4Q7R/8qIbAG4/Kf8V1FztsWULbHph30DAHe7Z5fXdmk1BMySSvGpqFvb5U0M4sRLeHTTE4eSfyCUo9C4t4d43RTTlu/m5yzblkkKIne+w4ROlSaoixZNqxytchf18td42ePT6bCnBkUo0ux6J/m2k7vXg/p/aO85jamSMbqdBC3BFyenFO6GFb8UnsWqXBmDXD0l1N9uupI
*/