
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
P8IeMGjTfmAInqjnJ8M0OBEmwQKYDKepfQmsD8v0/CvY3lK5BlhX0xXwyOW30Xpuq/UxNioLAE9Q93Uww6P5CFa63w0T4PewJdwDO8N/wJ7QJrwBMABHwrCGvyQ6bw47+ugRRC+TtLNbYGu4DHaBt8Fu8Ck4CN4JR8G74Gi4Ao7T61PhPfBiuAo+Ch+EL8FH4Q74mOpDehzWg0/ALPiUltuo6Nws7KPlkIg5EiPjjI5TG2AI
*/