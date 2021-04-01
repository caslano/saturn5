
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
3MvZrVOIdqKGq0Jdjx5m+gHUss2Me57ZhuskZCxAwLRZrsdk4I0SkoBbDlJNemiHP2DWLvWiEUnGXItoVwxfeDUv4JTVeN5UoplI2yQ/kAfRdAeCVUu+ug7Zr52o8po5w9i7tWioAgshg2DMPItw6LDx5kxdO0xtxms8OsplM1QmcAfPnm8YOKm4bGpFAZsC1VZ/snCaYTz0SrQ4M550/7dCXdcfNnnuHKcsS64xF3T119VSN/B1RJ3YgCS/GzH0q2cX8pPzidudjSDpcPXF452K3q5XRIILt0QiGqwJ6k0qijatkf9mne9SdW6+coGbMIUnKNm90t4cEFCjvEpVYKx9/veikZJJi2shEyiGaS+lrhwOJesKD9jB7g/mAKZuVb/e7K2f0/hLGCqtMuawUptitwQxB7tupwRfjV+BNuJo+5W0cwW9ElxrBBeoKmtpYrxTQwbMFabH1/zGanjNlIVQga7AIYdOl86NhQ86ms4ncC+eNXdSCxAbBVeKY+QC36oR40awLKnXFfMCzo6ZRmt8kEnIhV8DTZoybv+2FjkQdleuAQ8S+UOxIA==
*/