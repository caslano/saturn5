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
v59T40xGrtM81ClnJgdgAxgPz4Lnwz/Ay2BTOAG2gHfD1vBJ2AEuhp3hK7A73Ax7wHfgRXA37AkP2McE5XtdRt/XCYOaH1/EN+FeiDeTZVwNbf9Nw++1hDXVv+RX/Z+t/s+B6fA8WMMOp+Fz7Txr+Koa3q9xSduMP9stG1aGtSLCVddwGTHCVdZ00zXdDA3X2n3/H2Wo4YJ2PjVcPQ1XHybYxwErwYawsV3+kenreUuMkf7I
*/