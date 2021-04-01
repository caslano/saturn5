
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_STACK_CONTEXT_H
#define BOOST_CONTEXT_STACK_CONTEXT_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

#if ! defined(BOOST_CONTEXT_NO_CXX11)
struct BOOST_CONTEXT_DECL stack_context {
# if defined(BOOST_USE_SEGMENTED_STACKS)
    typedef void *  segments_context[BOOST_CONTEXT_SEGMENTS];
# endif

    std::size_t             size{ 0 };
    void                *   sp{ nullptr };
# if defined(BOOST_USE_SEGMENTED_STACKS)
    segments_context        segments_ctx{};
# endif
# if defined(BOOST_USE_VALGRIND)
    unsigned                valgrind_stack_id{ 0 };
# endif
};
#else
struct BOOST_CONTEXT_DECL stack_context {
# if defined(BOOST_USE_SEGMENTED_STACKS)
    typedef void *  segments_context[BOOST_CONTEXT_SEGMENTS];
# endif

    std::size_t             size;
    void                *   sp;
# if defined(BOOST_USE_SEGMENTED_STACKS)
    segments_context        segments_ctx;
# endif
# if defined(BOOST_USE_VALGRIND)
    unsigned                valgrind_stack_id;
# endif

    stack_context() :
        size( 0),
        sp( 0)
# if defined(BOOST_USE_SEGMENTED_STACKS)
        , segments_ctx()
# endif
# if defined(BOOST_USE_VALGRIND)
        , valgrind_stack_id( 0)
# endif
        {}
};
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_STACK_CONTEXT_H

/* stack_context.hpp
W064/8nrrAkADgSHET5jnQ2AnqMmGddXVmT+wPgEjCmJcEM5mBL5ww9av7Z4SuVySAZKdjyt2rmj/IjOXswMZUr4fPZfps+fTdAOc/ElkJisGF/XoeBfM9Fu/c7deKEDxgnWtK/uPIxpsueI9j0LXQIw3N8z/TLu2YW9tlJTSGbDDGIOTSwXnh5Je7eAuf2zzlv1B7nzR2aGnd5zxFQaniCG0N+yiNfnWip+IkV0PgoSlDBBZCZ5S/dtw353ZkodNvvk/4kYBS73kL3ODniF1XiKUNJuA2ddWpO6u0sXc57ZoaYRQiLFC1U7eptQm8MuvP+MBqPv4oZBWojk5IZvF9B0/eERUxPDTqwxGuaTIDwqEuUK5Xa70xSE7/0HVFwkD1P7/W7Fb5Cc/rQQdjhKiOW2xPn/JceHIG/mVUaOT/ANzS7T9zXSXhFUPCcFS4ZOZpenDWzGlmX2az28U6BNTStGNVWuFdKgLvakj4m4Q22Lr9ppQpECMsXbUrM3ut/yiXl0lT/EGlIBipWaCyN5Ev+AY+GBMGL5VcxSWP3rueGytrOrtRwGLgJweg==
*/