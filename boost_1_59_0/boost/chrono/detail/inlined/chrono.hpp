//  chrono.cpp  --------------------------------------------------------------//

//  Copyright Beman Dawes 2008
//  Copyright Vicente J. Botet Escriba 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHRONO_DETAIL_INLINED_CHRONO_HPP
#define BOOST_CHRONO_DETAIL_INLINED_CHRONO_HPP

#include <boost/version.hpp>
#include <boost/chrono/chrono.hpp>
#if defined BOOST_CHRONO_PROVIDE_HYBRID_ERROR_HANDLING
#include <boost/system/system_error.hpp>
#endif
#include <boost/throw_exception.hpp>
#include <boost/chrono/detail/system.hpp>

//----------------------------------------------------------------------------//
//                                                                            //
//                     Platform-specific Implementations                      //
//                                                                            //
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//                                Windows                                     //
//----------------------------------------------------------------------------//
#if defined(BOOST_CHRONO_WINDOWS_API)
#include <boost/chrono/detail/inlined/win/chrono.hpp>

//----------------------------------------------------------------------------//
//                                 Mac                                        //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_MAC_API)
#include <boost/chrono/detail/inlined/mac/chrono.hpp>

//----------------------------------------------------------------------------//
//                                POSIX                                     //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_POSIX_API)
#include <boost/chrono/detail/inlined/posix/chrono.hpp>

#endif  // POSIX

#endif

/* chrono.hpp
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
*/