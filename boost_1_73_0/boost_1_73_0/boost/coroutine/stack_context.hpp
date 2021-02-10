
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
O4vdwCczhpVngxqiAKGP7TVoQJB2I/QkXwOhJTfYNuOpNGfZGjvqAT9XJOM5a0tNoRuzXDYrptcqGWJ17aivHYY6JqSQSn88rmWjP320nnx8opQSciYNQhgCg6Pu5GiPTt68pRM62d21nn5NrH16QF/TN4SY0KxGJKWsi5JJnKRK6p4m8AxfOK/7rBHE1S1SgMSRAJbjOJhuaSM01EH6POlQtjN77sXEn3seUiBWYTg1DKfutGZhEAfTwIuIbYYZJc6f9uXMcwitctJ3rAPWb0/6KSqht7A7It8ywm34m8D/220Ej23GxYLRmqeGEtFUrsa5lHQpqhE6fNHLBlhGG+U9fr2/WeHeYYNofpo70pDpc5/4ZsS05Kxq6/XWP4TmoiuJfWW7nn3iem68IB25DIBo+F+tQDbokbiewXtk9GUrSg33SBkIV9SQJQIJ2Sb9wrF1Rp2otjbAUT3rS0yMPVJ+usOM37XBAHJZlQ+g2rTAN+Q8YmdZf/Uc0r0DutslGzrxPPThyvbmDgm5RkJVXf2cJLgA0YP7P0DDkAXPrEFp7l/4wbWfBN3EGQPEokX6TT+Ik5O568WJ220N1t2RkWTNdZSZ+wj7WiMt72ix4mvbE/s0OZv7U+M2scMP80vHj/Eu4BXc4kXY0bKo
*/