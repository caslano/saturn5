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
SeBk2/OQX8tGDVJ6qZ0kASpAUJtDR1xWshoT7pFNFHjmUYbHakWY7n1urgtdZoDfQfr9dom46p0weKEhti174GQa3CGzB44hdc45swybS0PJULMVsuXrwLjfh75WTxNwmwocLU9hfW6r4lpp6/IXCqDYK0yhxxazgBOksGVuAiJSGktJKe4nCpXhOUkmhxE3vn3eRj9gc/Uptu1a9SiAOI1fukWiU/frGXgwr//DtJ3B7MDcluWeIVE47t3sz+bLdXI7XIw74nd464YSBE3vJpMeKo0VeJRWnNuy5giApVnrTc22WE32RBrtsHHf4PZXh5HZq6ystXKN37F9FLyYJbfpXU2pO3fDjBXs2Yb+3fqCGhfj5d1iSn8PJ3fjIC6+gW3FaMglHGG1bjneY3x20ALtgL05EPrIpMi/toyZoHU9wITJeEzDSTLDcrpe/G+/CQUSQ1AUhfRCNi9fYAXzg/0x0kbqlMljrDD4D1BLAwQKAAAACAAtZ0pSyMHQ9ioFAAAECwAAKwAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9jdXJsX2Vhc3lfZXNjYXBlLjNVVAUAAbZIJGCtVW1v2kgQ/u5fMfKpClTGSdvrS/qmcwhtrCMGAWmbE5K12Gu8rdm1vOsQeu39
*/