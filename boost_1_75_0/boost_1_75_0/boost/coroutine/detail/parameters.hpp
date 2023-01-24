
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
PONoPLHksNjaiXCYchaSiuugV8B3UYmmnEJymtJlo+KManVWBw0cjLn0ReG3PkzNCqebB2jyg1QEdmEVsllpDGyjM+5/gX1swB6ZYNcAfjbl1ZR7IgE7d9GGNuxHlDMkqD+wh68MKYmmWGapl3WD2PGvW1QDZGpxlZ++yF2o9695NBKSulDu0a+wD0gnmfNUPsX6P7/qQrpHvkI9wJjEygN8Arx6ApwC1gBjgC5AFSAbEA3wAdgBDAFKABEAK4AKgAN4wj3FXcMdw+3CrcLNxo2OcQvkDWULfRdKHUoSiltzDDVOoXIvsx+YO21tp4J7vJT+P5YhuJ267PhnO/Xt6vHPOYlrH9wXmvEYadBTWf5jESnBXwKa+wd/WcgS0pf/bT+FN/Utjh6BLWMtQ8+ebyZM5IFyHjf8mLYJvrrjkQmxM2q5W91z6oNkJm58ObfQO5OZkDtDlvmZ6HtHiVqNVOov1IO/gdworEfBGqUtpVBwPWn6jaHU7q8zSpyrBuP3K+S6h2bF0fmR+X75wHyrfP18lXyJfD47w8OFpMlErelgp2lvuqJD0aHtXASNqgLGa3GWm12Y0+tXr0SJXqkqoKASvXr98qImMGi++o/nw8tnam3Prg00l7Q2sXWwArJ//EdD3NzO2l7a2t4a+M3CXNLWis3d2vxUz9qWciDZlydrkzWiwFw3hbVDaWnWJP5vMo0fdBMYxsVx7NTU
*/