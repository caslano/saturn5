
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
khhRIr3FPqe5mF9uUyfepCpxX/nAOwoA3apYu7VX55xS7bPuWdlJLuoNdy0/C1U9NGPuu89IJ/w6U3q90kVxaIbJ4+Mb0h7ptrM65+oedJwdC1YWG8qRsz6PIPEh72JrCDmwPqpDHSWCg4y0nnsuEHnbd6/oduQ8GYvcdnpsuZPFNE+OPjZjxvDlgFwuSKBKh/c+V3igZrzWkz3fNJ5uE5REaVg1QdoInRtVDsGobbxppuRE83xJ9mvydXGobFYKnaKXCOSxJMPsN9K2c28KXhOSxzOtpC660NWYOdaJ0AhN/t4ChETXBIBD8yCSJIm2ODxvwS2lDpB0M7s7EvliIHqTw9fcQU40E2bgSTdUnfGRXSnDdLhp2gonYy9kfEl3BOSsTPb80pQafzVQYFQAtJH7VPNmRNmd+v4l80l2cZgRHeesPRD8EJiJ9Vp8gtgClj7y6VI5vVaaOagvJRj/1C3Pyd4KQ5fpk45f0hXgEHxGcQk+9DPUtgtsf3RAzzewfayNva+E6E1VoLEkLB4FpWypdueW1T1HUYQU02ROvumB+cLpJG/X37mD6g==
*/