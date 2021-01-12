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
ck48o6Adz2johltz8nCrNP3Vmv6aiHJeq+FyYpRzf01vAKwGL4VnwMs03QH2cWv4fho+Humu4d/Qct6q52c7bAV3wA5wN7T97oK94T9hH7F34u+MbNFyPVPjD9n1UuM/X+NvBcvB1jARttHz0xbWg+0jjvfIKY53iB7vUD3ePD3eYVCuK0vf7yTvp3LCN0Ku03l1J9Kpbx8/tOO8EA61ywYWw0vgVHgFvA8OgbNUf8RODz4B
*/