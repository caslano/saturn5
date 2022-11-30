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
+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
*/