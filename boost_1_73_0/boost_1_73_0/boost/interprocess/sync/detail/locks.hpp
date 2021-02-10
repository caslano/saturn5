//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_LOCKS_HPP
#define BOOST_INTERPROCESS_DETAIL_LOCKS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

template<class Lock>
class internal_mutex_lock
{
   typedef void (internal_mutex_lock::*unspecified_bool_type)();
   public:

   typedef typename Lock::mutex_type::internal_mutex_type  mutex_type;


   internal_mutex_lock(Lock &l)
      : l_(l)
   {}

   mutex_type* mutex() const
   {  return l_ ? &l_.mutex()->internal_mutex() : 0;  }

   void lock()    { l_.lock(); }

   void unlock()  { l_.unlock(); }

   operator unspecified_bool_type() const
   {  return l_ ? &internal_mutex_lock::lock : 0;  }

   private:
   Lock &l_;
};

template <class Lock>
class lock_inverter
{
   Lock &l_;
   public:
   lock_inverter(Lock &l)
      :  l_(l)
   {}
   void lock()    {   l_.unlock();   }
   void unlock()  {   l_.lock();     }
};

template <class Lock>
class lock_to_sharable
{
   Lock &l_;

   public:
   explicit lock_to_sharable(Lock &l)
      :  l_(l)
   {}
   void lock()    {  l_.lock_sharable();     }
   bool try_lock(){  return l_.try_lock_sharable(); }
   void unlock()  {  l_.unlock_sharable();   }
};

template <class Lock>
class lock_to_wait
{
   Lock &l_;

   public:
   explicit lock_to_wait(Lock &l)
      :  l_(l)
   {}
   void lock()    {  l_.wait();     }
   bool try_lock(){  return l_.try_wait(); }
};

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_LOCKS_HPP

/* locks.hpp
3nBGldSyMxsqudfiFUc5ofK4bmY2tl7g+6FbPDhOfjLI3yo5T2tl65qNBpVzEnScW9y7H+SsKDr2GbV781jXJ8G+zHhqURjWMVTFt6h+SsO03pKntIxJFKYJKf0kIUEZBoc0Dsqgrr/n3m+NLxOPi0GxcumCThNQoDaWBVrsQLYjMKthukBzNnDWfNWSe6+6but7t/3/APMOz62t/wmzC3e7OMx8ku2qA4kaPyJZdqxIEsR1dYyDY1VXd8IMMNiwRIOFGTgwYVkEhUW3/73+e9R3/kaSHsqkrBJSZ75PIupnJKvSkmRhVW2DbVke/O2dAIoCoxLorKDhE7RjD4oGVgYaJkD1GnrWwWXqrfBnAoV6ATuyWxNMooev5yvwjirWNFIQrv/OnnuvzjL3fp1/8QNQSwMECgAAAAAALWdKUgAAAAAAAAAAAAAAACIACQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDMTIvVVQFAAG2SCRgUEsDBAoAAAAIAC1nSlLP5dsBGQAAACAAAAAsAAkAY3VybC1tYXN0ZXIvcHJvamVjdHMvV2luZG93cy9WQzEyLy5naXRpZ25vcmVVVAUAAbZIJGDT19LLS07i0tfSyy9IzStOSQMxYVRpPhcAUEsDBAoA
*/