
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_STANDARD_STACK_ALLOCATOR_H
#define BOOST_COROUTINES_STANDARD_STACK_ALLOCATOR_H

#if defined(BOOST_USE_VALGRIND)
#include <valgrind/valgrind.h>
#endif

#include <cstddef>
#include <cstdlib>
#include <new>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/stack_context.hpp>
#include <boost/coroutine/stack_traits.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

template< typename traitsT >
struct basic_standard_stack_allocator
{
    typedef traitsT traits_type;

    void allocate( stack_context & ctx, std::size_t size = traits_type::minimum_size() )
    {
        BOOST_ASSERT( traits_type::minimum_size() <= size);
        BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= size) );

        void * limit = std::malloc( size);
        if ( ! limit) throw std::bad_alloc();

        ctx.size = size;
        ctx.sp = static_cast< char * >( limit) + ctx.size;
#if defined(BOOST_USE_VALGRIND)
        ctx.valgrind_stack_id = VALGRIND_STACK_REGISTER( ctx.sp, limit);
#endif
    }

    void deallocate( stack_context & ctx)
    {
        BOOST_ASSERT( ctx.sp);
        BOOST_ASSERT( traits_type::minimum_size() <= ctx.size);
        BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= ctx.size) );

#if defined(BOOST_USE_VALGRIND)
        VALGRIND_STACK_DEREGISTER( ctx.valgrind_stack_id);
#endif

        void * limit = static_cast< char * >( ctx.sp) - ctx.size;
        std::free( limit);
    }
};

typedef basic_standard_stack_allocator< stack_traits >  standard_stack_allocator;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_STANDARD_STACK_ALLOCATOR_H

/* standard_stack_allocator.hpp
dEWVDHOVmWG2h8Iv7fqjqm4om7XYgdpYsAoagwNg/QGsVS4LfhJEJNw0q0qacvCQFgWs86HSYLCqOndkKtG0JSAkHVoD1oQNZS8tP4yqDUfblmr9RJFg7RwVja4pHMFCerki4AfQ1Dlqp++A2EfpUHaQf6VlD7nnoGrKCnpBAlHSg5Uw0gzgOppfxIs5XAezWTCZ30B8DsHkpvP3PpqcETckRdWA9xuNhrLQINebSmL+JPh3nXTPn1/AaDEbx9N5ejZJ0uRicX4+DtPg7GwWJkmYwAn0TuBS6Kx0LO9Br5IrpgH87L869o9JwL9SFGaXGrTccHoTtwy5Ty5gElyG3pdjLJ9DUjZFwVzLc66eer0tkZCEUhlbizXz2VLvDPGHMLclYaxqdBGSm0k8TaLE8+vC+0HWWdXkCG84rZaw5VvPZZApkn+cbZ9P4Bk5zCti1BczHUCl6lsKrIri6FfPL6RL4CxMRrNoOo/iiXfdpu1SJmZQMapyU0hMfZI6RNN9ta0il4f5gIa4hYLY4CnN1CRCiqo6qDwCieaU/FnW3cFWktIKedjcvhCgKSqNgvPie462zFy5psnWPAHMc3cqqawV0uKQysW7RcvIr3auELdn2LRWDgHUngtCXF+TFmwqYQtFs+N7XvDQQc6n
*/