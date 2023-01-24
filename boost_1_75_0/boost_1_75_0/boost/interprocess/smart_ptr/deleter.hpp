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
/fl93rZpaZZ8OZSdqMQoMvKKBxWH75MhSjsTFfoKrmAyJs1YMCoqDVpn7vt6iV1G6l+68fTQp+Gx1ZR4KvbiHaWcOzyoQGf+sC9+N/4t/bBIQoTCWrCo1DnHTiX9idbaW+9SzerhjmS+jE6RM7vzJ8uO9ycqzrPbYqPiKmu1omUKT4N83jQ8RcMi6Yy83pyI6PcnHCw06Zq3sydipTu7JEz6IEyp7I3usnxRXR6p87WwEx3Q8wKuwAnbBvPs4LoNLt8vGwF4P3H3qCicqFat402nEP6xLLtwF7CEPfk7xTFNBeFuxCI5PDK0cAMtdQNPzqePe1/7ssqUfh8/QyMwOdlfeFYEiJQW4qYeQc+6pHSZA/boQ1Bt/J17vPWWNhKojPmaYLnzrTRXESQTpyfaWbCOYi0YBOx9nJI/D+lGHIqVT9hBLDhfdg2g9i/2lNOMyMtN/cgW4OUXvI0b1wTRaG6dt/9AimQk377DaPHK8wq6TuK78gWd9VgvP3fBWxGawHRZvMe0XuA5JJ9Rffa7LreZNkcqC8XLRj11D/QkalQyNmVf16GMqTy7a+3ZUvwdIXzVyuztUny1gj33xj0li+jAJ1NQiW6zn5KQkeEE24IsyfzI+GVPsUXvBUWQSAeaRqGWKnXgBZ1G3z5/bJzeDPb1d4I+bAoq7nbCHVQhjV9Z+t57rbtfR/dnvUaBbhdajS5jQ4xXOzbXKXBZ
*/