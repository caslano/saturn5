
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PARAMETERS_H
#define BOOST_COROUTINES_DETAIL_PARAMETERS_H

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/coroutine/detail/flags.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename Data >
struct parameters
{
    Data                *   data;
    bool                    do_unwind;
    void                *   coro;

    parameters() :
        data( 0), do_unwind( false), coro( 0)
    {}

    explicit parameters( void * coro_) :
        data( 0), do_unwind( false), coro( coro_)
    { BOOST_ASSERT( 0 != coro); }

    explicit parameters( Data * data_, void * coro_) :
        data( data_), do_unwind( false), coro( coro_)
    {
        BOOST_ASSERT( 0 != data);
        BOOST_ASSERT( 0 != coro);
    }

    explicit parameters( unwind_t::flag_t) :
        data( 0), do_unwind( true)
    {}
};

template< typename Data >
struct parameters< Data & >
{
    Data                *   data;
    bool                    do_unwind;
    void                *   coro;

    parameters() :
        data( 0), do_unwind( false), coro( 0)
    {}

    explicit parameters( void * coro_) :
        data( 0), do_unwind( false), coro( coro_)
    { BOOST_ASSERT( 0 != coro); }

    explicit parameters( Data * data_, void * coro_) :
        data( data_), do_unwind( false), coro( coro_)
    {
        BOOST_ASSERT( 0 != data);
        BOOST_ASSERT( 0 != coro);
    }

    explicit parameters( unwind_t::flag_t) :
        data( 0), do_unwind( true), coro( 0)
    {}
};

template<>
struct parameters< void >
{
    bool                    do_unwind;
    void                *   coro;

    parameters() :
        do_unwind( false), coro(0)
    {}

    parameters( void * coro_) :
        do_unwind( false), coro( coro_)
    { BOOST_ASSERT( 0 != coro); }

    explicit parameters( unwind_t::flag_t) :
        do_unwind( true), coro( 0)
    {}
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_PARAMETERS_H

/* parameters.hpp
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
*/