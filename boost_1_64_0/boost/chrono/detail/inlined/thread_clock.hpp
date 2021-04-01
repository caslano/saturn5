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
RDGxXIq2qseoOqLwXt8eGbRxXgXvJER/Ers6CLEiIRzb+mPqGo7PufVco2JID1vO4jHSQWNv2WgbVKLBX2xEa0GOg1S9EEOCp7XE+ul130YNv4m5g5dl71LFdFuTXYvkkQlNm37YMBau2V4b0if66VI977fjfDPRaDvsQqbb0478AzoFhDVGZgFMzKKq95B+2jaTCJkXoH6jCvAlqIkQ93R2pCJjPBcvlbCdQHMY5z59agu7qy8g2sISKFk7w61kSxNdkmwdADmyNvjAghsc+AkfhwDol9C1pvc+Pg8R5NL8NT64MFZcsJJqpS491+Tn5NDrFa5AyD9UUqk5fxFC1HFU3FhS57IlDjJ5VGYy8toy8XZUKKG2Q4s2RqVeACvhRTA7fEpNOylWsgkbgip7wd/7juqQnoeC6AnK4OCi1U3WIQA8ABLQf81MdGTFWdMrOTugdijqAXEsszeh3S00JdsO6K75aqZMyKMtOk2cf+qom3SrBhvpdTo4X6OlQrZ4ztP28FfDFFaznjvy1kZ2XOuLLpPafNyrenVeTMRXtzlqjTm88UTtXnez0g==
*/