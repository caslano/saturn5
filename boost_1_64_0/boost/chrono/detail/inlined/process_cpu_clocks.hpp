//  boost process_cpu_clocks.cpp  -----------------------------------------------------------//

//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/chrono for documentation.

//--------------------------------------------------------------------------------------//
#ifndef BOOST_CHRONO_DETAIL_INLINED_PROCESS_CPU_CLOCKS_HPP
#define BOOST_CHRONO_DETAIL_INLINED_PROCESS_CPU_CLOCKS_HPP


#include <boost/chrono/config.hpp>
#if defined(BOOST_CHRONO_HAS_PROCESS_CLOCKS)

#include <boost/version.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>
#include <boost/throw_exception.hpp>
#if defined BOOST_CHRONO_PROVIDE_HYBRID_ERROR_HANDLING
#include <boost/system/system_error.hpp>
#endif
//----------------------------------------------------------------------------//
//                                Windows                                     //
//----------------------------------------------------------------------------//
#if defined(BOOST_CHRONO_WINDOWS_API)
#include <boost/chrono/detail/inlined/win/process_cpu_clocks.hpp>

//----------------------------------------------------------------------------//
//                                 Mac                                        //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_MAC_API)
#include <boost/chrono/detail/inlined/mac/process_cpu_clocks.hpp>

//----------------------------------------------------------------------------//
//                                POSIX                                     //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_POSIX_API)
#include <boost/chrono/detail/inlined/posix/process_cpu_clocks.hpp>

#endif  // POSIX

#endif

#endif

/* process_cpu_clocks.hpp
ZbN+ZDvMpTbI5f87PBDHWBjkZy7fWuUpFHdx+EcIFfuXPeW38Xl1jmAxRrBtrlTf8HGJDFZH/OrCQCxU0Er3l2eE0zYWmi9EI66hfLYer2SsCJt5vRwl0UekK7KbutC3AVFU9SzRypvitPaxq8NBdt0uRQpvW5rW2PJURlcuM8szyJN+HViZCNwVoED/ILyjKmRUHQBfYvYMsldV9K6HqUYBv0wmjyhJ3TPy2+8wdou4gV9Pz1wngj+R0zHBg5m7V0Gt+RJXslKRGuaCUbhMkN+eruVrReyZhfto+I5GnvyKsHnpN7Ah9lvp4C8TeOXW6cr+FaIZJ6j8cIa2GNOltTuY1lsknn88kt54tL7bbFp+nb50FllfN4j+t3aV+rOUo7N+IeOQq9W/FHMRw5GCViRf9Rb7gRCrIVtdifb4Huja9W9lS5/aBQPSLjobvVGrlxljiHpWa0fNi6QmcmJ/DE/M/eFq3rOjq8jNmri89y8jdiwLwxhQM3WFbdSmaxi7uK/4a13wYl7KE0OXI3Sv7mmiQdGdeO9Hw+IBqkWmhPHY3LWXlU/21qjqcA==
*/