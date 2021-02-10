//  abi_prefix header  -------------------------------------------------------//

// (c) Copyright John Maddock 2003
   
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CONFIG_ABI_PREFIX_HPP
# define BOOST_CONFIG_ABI_PREFIX_HPP
#else
# error double inclusion of header boost/config/abi_prefix.hpp is an error
#endif

#include <boost/config.hpp>

// this must occur after all other includes and before any code appears:
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#if defined( __BORLANDC__ )
#pragma nopushoptwarn
#endif


/* abi_prefix.hpp
+KUl0thlRWF6AAlD0SFWTPq+136anxj4LRG3lGx2s2dZBk+ZfjNcljNs9RqHzI3uE6RvNo+SaBxNY8vTHYw7/l/e5WzqW25dWkZDp4+KRmuqBsg8LQd6cwj/WPCY4p6fD7td4ySJQrEZh67A0SxJccF2Rghti120FwYHRMnFuouhDTCedvTT6AJOT7V9F/qp6+6wD9GeldOvfaYG/f/wASuKcioHdoIVeg8HtgFNJ9H80ktScx9NJtgmtntw9JYVtrNjAf8Tj4/M5Vh7f14Dxuub4WBndrAzG/bZfLW67whnPNtkW5QSI1ndNnA42mO2397x9NVyS2qK6H32gqn3KZgGycLyjIBQGd00MAZzP7mah/DZm1751pwonLUSvlFAu7HajQitQdk2DRdKi1XP8c7wKrwIo+swjUz3aaeaq05Wduz74E3jCMfLp/nT8oCNanTAfqKSby+erZx5a1v/AlBLAwQKAAAACAAtZ0pSzQB3LDYEAABECQAAQAAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxJTkZPX0NPTlRFTlRfTEVOR1RIX0RPV05MT0FELjNVVAUAAbZIJGCtVW1zm0YQ/s6v2NJpK3kwshq3rp00UyIrMWMFGIHiakYzzAkO
*/