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
gTtGHqg8ztrjayy+B2jKhGZ2nbXnrSNXRrWGISEy2H9TndU6kpsWV+u8z8n+EmmtQlrsWH6+o8c2B5rsTOWs/Tsp8XBIU/+0nhZCoviy7v28XhNo96kdltza3tMxgo3bjRIz0M3AHprb5keGgrvYvIdgM+lPUCzUeBKMQ9VZYhpZfprwwyKTaZ14mlEyQT2xRjxNkZMfCTogh0Q8HZ6Or3OLlCSFES8DGz2cw/oRiwgF4B3L
*/