#ifndef BOOST_INTERPROCESS_DETAIL_SWAP_HPP
#define BOOST_INTERPROCESS_DETAIL_SWAP_HPP
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost { namespace interprocess {

template<class T>
void simple_swap(T&x, T&y)
{  T tmp(x); x = y; y = tmp;  }

}}  //namespace boost{ namespace interprocess {

#endif //#ifndef BOOST_INTERPROCESS_DETAIL_SWAP_HPP

/* simple_swap.hpp
DQZHwUl45A+DsP/SabfOZ5O1fLv1Lc1uxmm7tff6IioOFuz7m5kNstk0uVvm49Wb63S8mBZznK9g7vN4E1SM3gtHIyeMb5Z3juusXv+4j2dRNFq/GyU3UXRx+O93MvtyWAxmRNOTPx33yKmLWCAxxomSwSw69SLrJHucO1F0fbk9dBleaXmQETwRNTMYjwmQwGmsBDwd0WOWTiFXdz6HEqgR3n26M7iqp1Ao53yf5WecxuN5TD6jyPEcgS0fMRpMjvMSCDEmPQXtDGON4Qrp2EnnmX4IcQJUZhKmnkx1xgERcBIdiuK8WweodJVK1dybbKPLPuPvGSOanvyVjRwLJMY4UTKYRaeOn23METwRNTN6nkEDSOA0VgKeimj1etsCq3dQLyLR9ORVWDAWSIxxomQwi069fEUCP4cSqNVL16K3j6t6CoVyzvdZOGsAVjxHYMvHWANow3FeAiHGpKegXZXYawDOIB076dpEWANQwgjpKJhqMtpVihzPEVBBk65VynCcl0CIMekpVFctIAJOoqNQXLvK66jKsXJgJfc62/lssrOxUNloWG9EAPsM2XzxfqOBtsvRLd+kAVfCblCgPMSD6R1/Z6IGmv4ySSddr2GWwj6DuqxbSJyEWxMRDnp3SHlA7QAxPaLLQvUk
*/