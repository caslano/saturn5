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
oOm2+BBns9QelznXtiD629jacW6669JEp3l6/B1BTnNVI/Krt9MIOUjpTGFqLB0UAojrMRAuTYn8gzTisjpkk43fgSTCSBEx51dERIBFjeNO5KvWdpcsnFaSNyHqT4pc3mc2UZfM8pmNHYJE/cjsuTgkzmhreWmG2sM3p4OYfseomZNsXBNNZxOcGYrWI6RALgslSn7GPWakDlOQjh2kWvaQDFS4L6Pb2X6hCoWfcg6vtg0sdzRHpTdqf6H97MKsx2jB4IeYpp7UPH0GPf7FbqbM8GsS6nVUM+aXWo9qHNGUGs2A58ZGyOo3dg8zg6+mM4w2UV1a07v+qy9wWSf43gVzHTrBeY/WZV+RaAk3jSHQcN4yH0MFDX80kIOJu/7n52Aiq5vfcynood6rh17nkD8+Upt9Y6bQMVZ7lLLmkUA6uKGiNtX3gZu1dvAaW4G7//EC5cupTEuXT/qaD+33eqQWh+rDUNxi3r9nTAN+YX8Kn0eBE/RAP1fFcLwt0s43Su1RbMkLT7bkGc22HvudoZyrMCgpu9D5R/aB2WQsKeFVwWiJHxp3dxtHSdzkNs5bU/nkyBQ+KLVHoSXPfIclr6Wuxx6nGQpmH3Cezt6d1QjDpSQsKaoKWbId3xcVplgSz9P+tHyQELaB2BnH2Ol4vuYZH81s/o49TJGL11F3ItbR7EMungqCr2RLs2AioxKMOEdeR4VjDfwVVr7L
*/