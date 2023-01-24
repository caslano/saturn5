
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
lvX3tD3LIwewIi/hHAWXK1gCDqcEwrpwHmTSlml/LSIIkRKyu9ZFJ3QYQScI1Upuv++GATv7hM4xdrgHkeYUiEM/6/4w17hnxKy/kn5PUlX1EggkoEnlv4eFGsOV/f7SgOE2AYBPfuZfDl/6vcfuLNb64WY2Fu9scL9i2MbWQSAwwZGVueDoYJNqXyMNOFEjdd4QaLa0SGUhE0jjWMxrrFyw1iuYmRljHbKt6tqHrrvSYX2Yvuui+Zk0s5Th4ZRAqZCtJxARADr+oCCSa+HvRvNHoUumeeAEggY3nqB9feh8U9eWytG0w/bGNeE7YaPQR0Ua5Mk3zH7DHXRj+83rcJhNWrBrs9JSFMADudaUchc7ukDfr7OWr1HaEoPB43GiRmhPTw1CMpO3SK0DUCmH1AqpPYuyxGcOZzV2ZHDiClIeDyAkoDWnuw50OInJxA/XIERDrLPI2DzVq3Bdbi3gSa6Ba/YlmkwdSDHQFEIMVy8QhKv+emshhOXS/sKXtDdvdEXaYSVdfmD52BqaIqSgMOx73nF2yGJx+CyApP0P6wIkhJDAuVv+0/e4bgsAOCL7d74sxQMI0TRe8M4Ff02GRpDz+oCqrqLCcLxj8yTua0e49mTOyS0LpcVJhzAOtEVYhzcWYSReeTAhhu6rCsuMWra+tfMeUQtQ4UI6QuNJ70BqiYraX7o0nCKgdAsA8WpHMiq5uKEMV9wCANZ7
*/