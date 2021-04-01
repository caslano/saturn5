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
pszTgcVmSegnz2ae2vw3kdQXN+Qw3QCIB0sGWis0fwPXXxkx5B69ekc9v5ypuAUuOeayWNcMCLEVkBWXM2L14Bujx2rzlgRGmA0xoZUotxSD+mcfycHhk90ww623CTKoPa2hNm2rQiDQ35GiD+YgpfjyHWNAT+wfPawxTzL9ziV54ANiFCFswghuue+akHqLAuHyKpUyDFIjAZY4AVchUZoZNFMo5EbNHqru++2xb81usGqRCyUkFJVS1zWfhBnX/iCbM5FkuxNHw6nxvBHmfdcovSuaNfMFk+8A4uLGBQErBMKC54rWtFkKqTlUct2g1W2q5hKdtUT6/vA/loAoUfYj3cnRwz8mKIiEgn6KnOA1y2Wirqy5b5D+8bKSGLKBxu4jJKb77HtmtBqQdIWGZqXOMyxD7fntIizFI124dP51011ay3OJA5Lw7i46ZQ4Szf5n1WdMeV3cStvpBzVp+XLNwdDtc0xVEX5vcC22bEZznEvRm630D2tyWnyz86Mdp6j6kj1Mik7blODXTDj04X8nty7PV/rvukKlGP3S7O26g17/U4P7oKbARQ==
*/