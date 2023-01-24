
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
d6FKkgWE1vWXOBAsAYtwEsuZ9KwzX4Uo8luapoH5sqS8D38GMREOI608Dw3Qdp3xgxt9lit9lXM5WgaYmh6a2CqMKRKeyH3leI8uM+9518qugalzEJyhZ1yoJfI6w+7h0RFbBfvMfj8GyjrPQzZbRS553BPR+hhap82NuHXFRPu7B5ZOXtNO5ie/rPknqQfr6zVMeZVct/uSZR/d3rxAZj9PeDf2jVkwCA3kErNG1XBfr7yUWu6Q7jPvL6z/duAHuHBpYXF91exeZwZ2wLjtjTSf0ujHI+K3zgoqJjk26zfwWOZnxuPa60vOXfxQeixwHqVohYEtJkMj3zZKTc8vicfAzzKbRuT7KdupfCZU0OeIZGkQRTOVELUFs71MVNpIg6MZv+aBpLffhklm/Jb4CXnvzXzQZSmGlyd/0fiPVUA58CzbZBeAC7wMrhWEGu4K5LxFeBHf1nkke4SdEb5s3MB0HZuhZlEHVZ71JouOleRTnMCJ9u9RyXGhY688/Nf1gIcLzTYtlcKzOV7+l3Z+Y5vXy3ZRb64DUXUw/0J1f63XiqPqrlv4XPeeon1iNpJDFPTToUdM5jDLz8AzwIdU8PJqg3Il5Pxi+nAh3kkucb+3NsRzvdf6o4t6zXHkx0DcTb5HIM9pvwFOdXgD7ji1xMBV6zWacZAhW3ZXyPNB/P3E1NIftnFRCasrWZH9DU2DrLD8955Foii4e5zk
*/