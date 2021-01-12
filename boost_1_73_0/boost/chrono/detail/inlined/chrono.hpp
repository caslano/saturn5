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
ELOPccO6dVCe9XX7q9a4x+5T3LAR+zrZTjue5Ybw9s6I8WM/8Rsnfq2syG/Aucfmrk+1Fb81T3ieOSX2s+j6/K0bj/sseobYS1m49cgf0PUNPZ8d9ZtWg8J7D1TPUP1y1Zv9n37/7JpsSXf3s/NvWuCfdNHLuVNmVUt8wfv+WeT3z/LClUq/eTYHaae/pyO95LcjrfR3S+Lsrr/3xpOu/h7BgfTW31343Vl/fx9wvqM2BckN
*/