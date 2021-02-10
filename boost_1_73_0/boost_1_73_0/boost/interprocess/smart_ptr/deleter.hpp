//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DELETER_HPP
#define BOOST_INTERPROCESS_DELETER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/intrusive/pointer_traits.hpp>

//!\file
//!Describes the functor to delete objects from the segment.

namespace boost {
namespace interprocess {

//!A deleter that uses the segment manager's destroy_ptr
//!function to destroy the passed pointer resource.
//!
//!This deleter is used
template<class T, class SegmentManager>
class deleter
{
   public:
   typedef typename boost::intrusive::
      pointer_traits<typename SegmentManager::void_pointer>::template
         rebind_pointer<T>::type                pointer;

   private:
   typedef typename boost::intrusive::
      pointer_traits<pointer>::template
         rebind_pointer<SegmentManager>::type                segment_manager_pointer;

   segment_manager_pointer mp_mngr;

   public:
   deleter(segment_manager_pointer pmngr)
      :  mp_mngr(pmngr)
   {}

   void operator()(const pointer &p)
   {  mp_mngr->destroy_ptr(ipcdetail::to_raw_pointer(p));   }
};

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DELETER_HPP

/* deleter.hpp
vOUQZSfJWMP9OZJjPEOauVxJhZJjJlcm2Upcgyp2Flem2nNZrCpmBldi/cWvxpZx9lYGyYQ9Lnzfk3jO28qrQfn8l4Yvss8VzihdqbvNiKeMyLnCLFpwfoBk2INJVtrwniucXxVBDw7X3Zz2ps6VZt8T96s2JXtuPEEvWO656qV1OOm01ykXlJVft929NcrOeNWeONeQc7a7UXjOGYupb2zMSGgxOGsR8/IjIPe4lyARQgg0QjTQSipI1P50ZWfViNuprvQ68hJzq4Ycs+Xam6cNovPNlndvnm+oiFMh+PbmLIFTEUIINIKY3jxmLjX3jMXUN3bOodBicHilyDcyulkQDuUQkHOG3pBX9lm6w1LKIqDeyW92xT53MjT5LNPaeOXMtcmzBbV5lCUvDTiUg2fOAmrJ66HPyrko3PKgHO98U190xRCOW0m41znJq+fPNkGl4J4vx2bOMt4klmmCSsEvX+41zPOQd9o7nyrsDFwy7ZM73VwUYb+vaQZEXVbxTJ/4I3hefZ9mhDYCW7OfFqV5frAsmjf2Gfy9KHPLNW5pubcuD5L5QrQJsb1PJoZOt6POd9rrEnR6Rs+azujvq3vOZ64+1f9e1Kp7pj2OZoRQLzd0Orh2YBq6ST7NzbF3+vRxppmL7zWem8YT
*/