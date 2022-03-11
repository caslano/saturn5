
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