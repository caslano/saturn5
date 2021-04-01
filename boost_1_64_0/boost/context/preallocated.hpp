
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_PREALLOCATED_H
#define BOOST_CONTEXT_PREALLOCATED_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

struct preallocated {
    void        *   sp;
    std::size_t     size;
    stack_context   sctx;

    preallocated( void * sp_, std::size_t size_, stack_context sctx_) noexcept :
        sp( sp_), size( size_), sctx( sctx_) {
    }
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_PREALLOCATED_H

/* preallocated.hpp
kIxglNzpygECAWywbYqD1LPlTeoDk+BlLwxZQm8ZZwNUzgtSHi+l+gLNYjlSwQAsHEY9Glll6DfhZeKeXJ4cfV/aS/0FeCwloMRmjYJ9g7bO8CsPyjyjacAiGSaBRx/63KmcDe+MrarY98pjw0w+qXKxe0Ex02tPifXt+ZH0lkY+V7QS2+vINHaCKsCmypzAkbyF77VB7kS878Zq3fCWvZ3jaFSnIVMAi5LkYxyn6WQviSg4QvOgfRE8qJJT72sXuuI3E1xFGiGgTH0C7UcJuM0RkCk24nr070DjMM0Y14qcDwHzYvNyuAGgXxB/4sH8Q27aFgn8xpbzryXbTZam9UlmTO6U4oofVI/grupAiGtI3/Orn8rwHErL6BbshlOVOocf2bsPTBAkZzU8H5v/tigsUzHOFSwGRHB7tgtSd6pMvcha5H7Lyjqxc2xxb8eNta1H3J6vlhVOcdT32gMId20PAKgvpbSkoMvw5YlmXD9wEAyMlXDr1uCzzLoi0rb34lKiLU2HS5hYztn3B7dTuoK3Mc4+y1JY18j3sbYPegpJJTbE3NrlTgL59Q==
*/