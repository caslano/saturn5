//  boost thread_clock.cpp  -----------------------------------------------------------//

//  Copyright 2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/chrono for documentation.

//--------------------------------------------------------------------------------------//
#ifndef BOOST_CHRONO_DETAIL_INLINED_THREAD_CLOCK_HPP
#define BOOST_CHRONO_DETAIL_INLINED_THREAD_CLOCK_HPP

#include <boost/chrono/config.hpp>
#include <boost/version.hpp>
#if defined(BOOST_CHRONO_HAS_THREAD_CLOCK)
#include <boost/chrono/thread_clock.hpp>
#include <boost/throw_exception.hpp>
#if defined BOOST_CHRONO_PROVIDE_HYBRID_ERROR_HANDLING
#include <boost/system/system_error.hpp>
#endif
#include <boost/throw_exception.hpp>
#include <boost/chrono/detail/system.hpp>

//----------------------------------------------------------------------------//
//                                Windows                                     //
//----------------------------------------------------------------------------//
#if defined(BOOST_CHRONO_WINDOWS_API)
#include <boost/chrono/detail/inlined/win/thread_clock.hpp>

//----------------------------------------------------------------------------//
//                                 Mac                                        //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_MAC_API)
#include <boost/chrono/detail/inlined/mac/thread_clock.hpp>

//----------------------------------------------------------------------------//
//                                POSIX                                     //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_POSIX_API)
#include <boost/chrono/detail/inlined/posix/thread_clock.hpp>

#endif  // POSIX

#endif
#endif

/* thread_clock.hpp
E6wHF5MhcJko1LLldYmqlECEyaV1nF5Go/E0nDr+CfwhZFLUKYeXFKnRW/7a8XWJb0Nwk5xVcP/bLB3oU5b7ri0GXNKa1AYaa/cmGUXwcJQMVsDl0uTgQvcFwmepRXI6mPYn4XgWjiLHNjmrZUJzQvGueGX2KxCyrA3Ms7CJPs/GpCm2V2+6TUwyrbhB7VEAnCecSQaSr3HUCpUwc2PqQ1AUbWhCzxLU5NYJxSaVcVjvswdB7x8PjnrHHhz0DvDLp6/4gGRz8N+BtW0xN1pH3KIC14KznKWug281Fde5F0U4NBx98EYQNrNWvVQsca5yfs1SnogVK0DWK9xsXd9xwowqb0ikymkguB31I+h85pXqemRwp1GPumSN60BTwejf6eLEOMTq9/nMBHKn8AWZaPGZ+3C7M6nCWEgLsCThpXGaME0MXKZKLu1w40zOsxOSSXwefIjDaHwxi4eD6O3sjDJ1nsH5CRVmF1etzQ36rOJb2AShaeNNv4g2Sbv3AMlLleSwxjEGYXwrqEHUH53iEnG2A4PIzaYUCfZ906C2O0RlHv6qmmKQ9MSu4QXW7e1k4FhVUVn+D7jdH7WUGQaLjeG9xaZHV9K+1YKzr9KtDgg6Uf1JqnXB0yUnNVkoGd6sSYN0koikLnCu7uKy
*/