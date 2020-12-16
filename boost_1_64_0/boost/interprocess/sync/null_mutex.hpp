//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NULL_MUTEX_HPP
#define BOOST_INTERPROCESS_NULL_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>


//!\file
//!Describes null_mutex classes

namespace boost {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace posix_time
{  class ptime;   }

#endif   //#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace interprocess {

//!Implements a mutex that simulates a mutex without doing any operation and
//!simulates a successful operation.
class null_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   null_mutex(const null_mutex&);
   null_mutex &operator= (const null_mutex&);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   //!Constructor.
   //!Empty.
   null_mutex(){}

   //!Destructor.
   //!Empty.
   ~null_mutex(){}

   //!Simulates a mutex lock() operation. Empty function.
   void lock(){}

   //!Simulates a mutex try_lock() operation.
   //!Equivalent to "return true;"
   bool try_lock()
   {  return true;   }

   //!Simulates a mutex timed_lock() operation.
   //!Equivalent to "return true;"
   bool timed_lock(const boost::posix_time::ptime &)
   {  return true;   }

   //!Simulates a mutex unlock() operation.
   //!Empty function.
   void unlock(){}

   //!Simulates a mutex lock_sharable() operation.
   //!Empty function.
   void lock_sharable(){}

   //!Simulates a mutex try_lock_sharable() operation.
   //!Equivalent to "return true;"
   bool try_lock_sharable()
   {  return true;   }

   //!Simulates a mutex timed_lock_sharable() operation.
   //!Equivalent to "return true;"
   bool timed_lock_sharable(const boost::posix_time::ptime &)
   {  return true;   }

   //!Simulates a mutex unlock_sharable() operation.
   //!Empty function.
   void unlock_sharable(){}

   //!Simulates a mutex lock_upgradable() operation.
   //!Empty function.
   void lock_upgradable(){}

   //!Simulates a mutex try_lock_upgradable() operation.
   //!Equivalent to "return true;"
   bool try_lock_upgradable()
   {  return true;   }

   //!Simulates a mutex timed_lock_upgradable() operation.
   //!Equivalent to "return true;"
   bool timed_lock_upgradable(const boost::posix_time::ptime &)
   {  return true;   }

   //!Simulates a mutex unlock_upgradable() operation.
   //!Empty function.
   void unlock_upgradable(){}

   //!Simulates unlock_and_lock_upgradable().
   //!Empty function.
   void unlock_and_lock_upgradable(){}

   //!Simulates unlock_and_lock_sharable().
   //!Empty function.
   void unlock_and_lock_sharable(){}

   //!Simulates unlock_upgradable_and_lock_sharable().
   //!Empty function.
   void unlock_upgradable_and_lock_sharable(){}

   //Promotions

   //!Simulates unlock_upgradable_and_lock().
   //!Empty function.
   void unlock_upgradable_and_lock(){}

   //!Simulates try_unlock_upgradable_and_lock().
   //!Equivalent to "return true;"
   bool try_unlock_upgradable_and_lock()
   {  return true;   }

   //!Simulates timed_unlock_upgradable_and_lock().
   //!Equivalent to "return true;"
   bool timed_unlock_upgradable_and_lock(const boost::posix_time::ptime &)
   {  return true;   }

   //!Simulates try_unlock_sharable_and_lock().
   //!Equivalent to "return true;"
   bool try_unlock_sharable_and_lock()
   {  return true;   }

   //!Simulates try_unlock_sharable_and_lock_upgradable().
   //!Equivalent to "return true;"
   bool try_unlock_sharable_and_lock_upgradable()
   {  return true;   }
};

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_NULL_MUTEX_HPP

/* null_mutex.hpp
cq3M9Y9rAeyi3VTGwtB4YB8X7gdtZ+BDcM9it2Wsr2Knxd/DQPilb5X4ViYN9Vet6zgz99YzLRdN0jwzF31PPPc9PM5QW+I3baJOkdsx0y3HdDsq6bj9xKCtSDpy43j8/X7jS+dz5yu1sX0su1zIoR2j7k95SKO6jPwEGtPgP6Qxjflm4ROPaSO439/PA0u8wzu2oMJSv38kYDrzS7jrx3Cl7PvNecjnFMa3ukf7QNutp0P2XyT38xw+Yt2hy36e3Wvt57+l7yd1Sz9v9jOTxuIbadaI1w15ut3Irb+eDGlPCIPKtge5PagH7utlX/4Vxfcf/Tk9HLIMG2mqPj8O+CXR/ai/qEMvBoytz+c+awjFfZs+Ro+z9XtGmh8nmrb6eu13rFPa1v+bY9mfiPZc/Q7tcvUYwmPFMXv/T/5zyP8w3z6U0zGevv3O1Gm0fZywxwXsr9fS974B+2v+ruyvPeN8++sKsjel/joNbemky+iv02z9dRLTpDZhGucoV3iU6ItdK6JdzhhlP8x+pjbhfi92sb2PZZpLDJqoeQFpNhtxR664gmlscVVzOEjW1f7hDIG9mdHHBtG3Mg33o7L/bFlH/7l9XHD95zeK/vOEov+sUfSfxxqg/xzWTD3XrhkWsF8q1UKYcw/rGvge9a5m9jn3FYng8Xh13DT1PoV71KauQbd9rChDfBX2+Eqsd9q7Bx4n4DekccJn7YNwbWufF93q8kCUtjSGcp99ta0cJF/SY+zlsEKMoQq+nOpd9p4c18EYexn8QYyDRlx+686mtaw7j4TGezlGC+R1pzVtw2LVvPcYbeEU1px7u9j5zvFB96Od71eSLAaOr17rTX7LEc985vtEbvxbhTiSJ5j6NXnDKSsnNzcLUFScVSziRbpk3cf3AHoaJvjfGb54Uf58lZ5cSStlO6A3Ur0hUNOiN5P3bB+h75dq2QhZIT9e+pdjYBGuf0rZ6/R9DekM8miNaH51teC9dX7F43MHoo3W2+H/NTBfw4j7rWLNkorE7AK6Gl/mcro0291Zg24G6B4hupk+dCOZLpbploPuUVqvnC3D8qOpAM1OIPRj/SDrvi/NPtDspjGw7KhBc9ztm6bjoKkSNOFl21yR0bb4WF8SryPI1KlnQox9Z060y5rnvg71yO/ON9cXftvBYxfVC9aTxW5c/tbxYx8/9EA4ppzq68T4MVFdtwsX5UGGfXD1umxi8PWaaVV1yJxrXkU0+ahpOs21VsPzogSjrNvZeE9zKeb9nti630MEy2drv7+6hf0dyTrRN2Ta+GduQvnyTuavA/npqrVX6zHhMHVzrf5YLEwIOv1lvvzGLp6IdWZPnTgP2fY8cPmX2PJgzI1zyU+sKv0Ir04dwLWkV9ZZrZWa5xX29FoXgAH5/qc6+F7hy3fsC8A0AN+T+THaUpYXvATmejGO2/MB5djQVe07lzLT/yHR50OLTZh6jOf0S79yTfUZfZupaJPsj9taGHi+H+bPoq21aGHt28htL5lg+jYfnpA90rTP8xl3jybadXhPEH3TJBt/8LAgPzcHWno9OaWmvvpxib76rUWgV5LfaBWfOFw5F/pLCPrJRFz85oHyMIbzsJY3icbB6Kwj8CZRV2vJQ3Ge90hMqCc38lIV4923yLGspx+mMHprPdV6fzgOneu91HOTYNR7+j5CiyTNxbqiDsgwEs0+PKegoOhioyPIKZyv1PUGf7LuHEN+xWbZZ258i2phWxNzu0I9EjwP/rymisY05om1HnE+k6y6VxTptupiyk42dSpQPbsAeKOof5OpnKiA8BioFHGVGG+jWhFPPTnFmNlbzxE6k5+25t7EdrInKssI4XMZcXjID84/zb0=
*/