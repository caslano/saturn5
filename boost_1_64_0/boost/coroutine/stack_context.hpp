
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_STACK_CONTEXT_H
#define BOOST_COROUTINES_STACK_CONTEXT_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

#if defined(BOOST_USE_SEGMENTED_STACKS)
struct BOOST_COROUTINES_DECL stack_context
{
    typedef void *  segments_context[BOOST_CONTEXT_SEGMENTS];

    std::size_t             size;
    void                *   sp;
    segments_context        segments_ctx;
#if defined(BOOST_USE_VALGRIND)
    unsigned                valgrind_stack_id;
#endif

    stack_context() :
        size( 0), sp( 0), segments_ctx()
#if defined(BOOST_USE_VALGRIND)
        , valgrind_stack_id( 0)
#endif
    {}
};
#else
struct BOOST_COROUTINES_DECL stack_context
{
    std::size_t             size;
    void                *   sp;
#if defined(BOOST_USE_VALGRIND)
    unsigned                valgrind_stack_id;
#endif

    stack_context() :
        size( 0), sp( 0)
#if defined(BOOST_USE_VALGRIND)
        , valgrind_stack_id( 0)
#endif
    {}
};
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_STACK_CONTEXT_H

/* stack_context.hpp
vyuK7/t7eg/heBeNfsSpQ8q5JM1jYIzYN79PkVMld6ilGVfHH9D1Yb/1IOuDnB4LyJH3gpohYtu5LNDbYEIFX7xxfliIS+ejPkesEvNyOeQZmyH6Zf+kzqlXwC/Ep3UObv9KnV4R5IuGp8bOxU4/q8pyPl4XZ5SvxA0vfO/kyji9feqKbaSOcq4iTs1a+ESlSS4FRotiA+InNpBDbis9H3Vf1stmRjrShr/KfZq5sdyg+8p1aJtfIyy+VOlW+Zaka7yYD6RTopVmrZC0Uij/N/V8jaE/wW9n1vE+bcVr09estWub/vfH4T8AHJujnLEDHBsatp9rQ45lCH4d4bTGmZmH6wHX8vALwLPy8EvgaHmYaTd4LYffebS3X60FHL8v+C4zc7ibaJvdzmxXJG+e6v2VjN1wbvtbnes1cMz779X0fd/zTfqdXl4Kyu/K9ndaRNTeHfvdfIq3Uh0Z+JxVGqeluaBpPrSfo43bli/R1hr/lNTHdC44ZyN2dTu3y51Ju4zfov4rx/cOs0A7/W17dNYlerPjb2tDjj4ev4N4pP8wr9IP3enySqcjkl1RiXsXYUE8k0Yra1+sW23ta/0SfR09ThPHk/dym8/S/X3cHgN8zvtRnOfJ+F5Nt5rff621dzmxIlD//2acrLSnZ6h3eDjXv5HHgjoO7f4/pqwVus1gr6SaOBheaUwULQLt6b+EmfuPfNNWwuet43D2nCB30dZJ/bOdVcwN3IL1GwE+WYk3MLKldwjOk4hPVsJCe881yTcK+PF7xLrIXtU35B9FvOlZ9PkYBTdujOQdUAUfhjnX4yzOajAV3RZh7IbagK3aer00pvUjw0u0+d/udrtHBR2XlOMn8z1M9IRzR8RxD/7x63wM7x4eSBjui/G0UIaN8maprS8QY8eLKX4w4DjNkb0GwsM5Smovh0Zx4zf9nxJx3B2+jtnLgkNESXOBzsU1E9KpLg/HUE/V5fA3T5dTD/YCDw9k1IO9+4UJ7td7uydb6lzCF0EcrO+nUzj487BzozE3HZH3KJX6xjJ1RLh/pucYPx11DnZswMG5ShYHx+iLdY5X4ajnpQGPx+nurVjCDaCNwVcwtq8xeKefRtYY3N1RID59v1CRop+1jMX25erheIWDY8VnC25li0/ZdfxdVNLtASwr3U3A0dLdIrgv+4QkvBbLjsfIoexwDBnhaRrb3PeHpn38/aGaSvew+wk3e9jjRg+t7YtRtY4an1LK+OVlS7S9jiFKawNldGO03YjnOzVOyVsnHtbkBN/dnVzXEQ84J3O9zMZ5TsKZnpVzivaNH61UJoHzfI1T8vfucvyNjdNquV6oV2go9XKuOk4r2DLaR7g39I2w9xLp/8Y4XwHe4vefTGVc+/6fp9rK+Doce8vrs0aI9N8TOqeckHBfweM5Dm2tuDsOPodOb8XplSMOpuf0WfV4IsfdQ/BwXUbD4zhc/OkRLk/EQr8948Wz6Yq/uBhLnGPI+4NhmkzAfJ1hbGEFuxITL/UZ+O5imT5Q3rz4ZRZnxLkzxPHbK0zZKgaL9XKmn0fq05Icil7OcnFLy8FP7tleP8inu8HeznF4nfCk6JP2LW/J17kBpwHrXq8TjGUH/dph9OuE2jzwTMKdXQs4mE9Z36Z0UuWZc+qsG0nDVhqKd/jBiLPo1vdxCrTFqfX5H/Hasay5U37Nsa6+TX0bu0d6ky2yvl451wb9vs7Ds/9v0WV552gvIk7/wEgf8XrhDCSnAVhwt/ytGC8Yc55Av+5AkhUKMhHz9kXftg6xeBwcHGLJj406/A/tiLt0s+P7+wJvX4e4pC95ewfhO8iPgS1zWCbE/DK904vn7zW8m7B4Y5asDNYoLiE=
*/