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
9ptZm0Caqu2HEgUbe16eeeaZWX/uwv3f9nF8Cgc//cT2P8YPXrdO40p95In5vkMcf4HmDx3neP2FVIew8/oSd+GXvL5Ax3rFba6XdB/Hv5BuTiDp65Cc5zHd4pPGs/Xvq3JTiWVuoNPvwoPj42fQg4dHD488OGVS8AKmhssFr5YevEztk79ydn3ta/7aA26AFf6tgLNcaNAqM2tWccD7QiRcap4C05BynVRigT+EBJNzyETBoT8aX4bRWw/WuUjyNs5G1aBzVRcp5OyKQ8UTLq6aMCWrDKgMI2D8VGiDMWsjlPQxPQfDq5VuwxAIVmgF7IqJgi0wHTOQG1Pq54eHSV0VWMlhqhJ9mGyp8HOz+qaqS0SzYhtQpQGjoNbcA7L3YKVSkdEVKcKHZb0ohM69HSxMKNNDVYHmRdGGQ1fBdVMCh2nLlkeWUCJ6YeiildSUbZ2r1S1DpLUNlNWVxHRIC9qlCon3oJYpr6y9JWKbpWXZUv6Tlu2wp6AkogI3mEI4dWHBtNAevA9nZ6OLGbwPJpMgml3C6A0E0WUb7+8wOkVtCMxaAb8uK64RRQViVRaCp7eS/9ZJd/zZGVBPY870JkaxsZLDI3CfQlBWokBhHz1xwS3Egqzgqf/gsf/n3oNzJmtWYJzpGUTB+cC5
*/