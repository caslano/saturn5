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
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
*/