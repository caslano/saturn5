//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SHM_NAMED_RECURSIVE_MUTEX_HPP
#define BOOST_INTERPROCESS_SHM_NAMED_RECURSIVE_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/sync/interprocess_recursive_mutex.hpp>
#include <boost/interprocess/sync/shm/named_creation_functor.hpp>
#include <boost/interprocess/permissions.hpp>

//!\file
//!Describes a named shm_named_recursive_mutex class for inter-process synchronization

namespace boost {
namespace interprocess {
namespace ipcdetail {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
class interprocess_tester;
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

class shm_named_recursive_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   shm_named_recursive_mutex();
   shm_named_recursive_mutex(const shm_named_recursive_mutex &);
   shm_named_recursive_mutex &operator=(const shm_named_recursive_mutex &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   //!Creates a global recursive_mutex with a name.
   //!If the recursive_mutex can't be created throws interprocess_exception
   shm_named_recursive_mutex(create_only_t create_only, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global recursive_mutex with a name.
   //!If the recursive_mutex is created, this call is equivalent to
   //!shm_named_recursive_mutex(create_only_t, ... )
   //!If the recursive_mutex is already created, this call is equivalent
   //!shm_named_recursive_mutex(open_only_t, ... )
   //!Does not throw
   shm_named_recursive_mutex(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions());

   //!Opens a global recursive_mutex with a name if that recursive_mutex is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   shm_named_recursive_mutex(open_only_t open_only, const char *name);

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~shm_named_recursive_mutex();

   //!Unlocks a previously locked
   //!shm_named_recursive_mutex.
   void unlock();

   //!Locks shm_named_recursive_mutex, sleeps when shm_named_recursive_mutex is already locked.
   //!Throws interprocess_exception if a severe error is found.
   void lock();

   //!Tries to lock the shm_named_recursive_mutex, returns false when shm_named_recursive_mutex
   //!is already locked, returns true when success.
   //!Throws interprocess_exception if a severe error is found.
   bool try_lock();

   //!Tries to lock the shm_named_recursive_mutex until time abs_time,
   //!Returns false when timeout expires, returns true when locks.
   //!Throws interprocess_exception if a severe error is found
   bool timed_lock(const boost::posix_time::ptime &abs_time);

   //!Erases a named recursive mutex
   //!from the system
   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class interprocess_tester;
   void dont_close_on_destruction();

   interprocess_recursive_mutex *mutex() const
   {  return static_cast<interprocess_recursive_mutex*>(m_shmem.get_user_address()); }
   typedef ipcdetail::managed_open_or_create_impl<shared_memory_object, 0, true, false> open_create_impl_t;
   open_create_impl_t m_shmem;
   typedef named_creation_functor<interprocess_recursive_mutex> construct_func_t;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

inline shm_named_recursive_mutex::~shm_named_recursive_mutex()
{}

inline void shm_named_recursive_mutex::dont_close_on_destruction()
{  interprocess_tester::dont_close_on_destruction(m_shmem);  }

inline shm_named_recursive_mutex::shm_named_recursive_mutex(create_only_t, const char *name, const permissions &perm)
   :  m_shmem  (create_only
               ,name
               ,sizeof(interprocess_recursive_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(DoCreate)
               ,perm)
{}

inline shm_named_recursive_mutex::shm_named_recursive_mutex(open_or_create_t, const char *name, const permissions &perm)
   :  m_shmem  (open_or_create
               ,name
               ,sizeof(interprocess_recursive_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(DoOpenOrCreate)
               ,perm)
{}

inline shm_named_recursive_mutex::shm_named_recursive_mutex(open_only_t, const char *name)
   :  m_shmem  (open_only
               ,name
               ,read_write
               ,0
               ,construct_func_t(DoOpen))
{}

inline void shm_named_recursive_mutex::lock()
{  this->mutex()->lock();  }

inline void shm_named_recursive_mutex::unlock()
{  this->mutex()->unlock();  }

inline bool shm_named_recursive_mutex::try_lock()
{  return this->mutex()->try_lock();  }

inline bool shm_named_recursive_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
{  return this->mutex()->timed_lock(abs_time);  }

inline bool shm_named_recursive_mutex::remove(const char *name)
{  return shared_memory_object::remove(name); }

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_SHM_NAMED_RECURSIVE_MUTEX_HPP

/* named_recursive_mutex.hpp
eoTmzSTOMq1noXBzSe10y/Q+ZTsHiU7QKcsccX/Tmkk4+91iHfVlzyh9n6raHHqfSppsv0z1a9u71O1HjO9STr4/JedHGfMtdVjTc2yUvht17e9/f1KdnHNVJzBcxlYnRxqvVf3J54beWfJ97ULC6fvxuaFxtXY+P3zvI4b51uQWxuTGn9d0obe13v4VWU+cyb9z21PFytUrSkzr6rUdrRDdz5ieLRpPIKwNunWst5w/ZmxDGtZvD6JtaICcP2Dst4fJuZdowWnO99D14pfm70e17p4v52/gKTnKmWfME7+76R3OtuyZuKutITLOv4f7O3i09qlJab56E9KZOVr70W4D3XoQplOBzljRucSztrO5zibnWosjXqvWudaaiNc66FyrarPvWtr2GCtQad+Yr9TNsPrq7okQeY8A8x4Ekbn3zXscRObkN+990Pa9A4oXyl4G599Y8fCUb66btGVZ7rZ5pfdG2sug7Vz95r0SIu0l0fY9Bcx7HLR9z4UfT7X9B8Rtm/tM90NnzLh72fTVz897ONLeB6duzwvzngiR98Iw72FxavdEOIxYuvdBIah7HzjHj+j+CBkxPBc8x2N0r4Eg7v7usbT1XHAPOoM9x6d7jgd4jod4jtM9x2M9x/08x6Pda8k7cx34DnKuHg/j3Eg9vpjjQXr8RED3HQioHaDaU9rnTm/iv5ffbZibdwPXgz2VP3oyuAGcqfzRc8CN4DzwXuUP/wRYCtaCy8FPKW/XZ8AbwU3gbXr+DvBzYDX4RbBG9xP4ku4n8CC4BaxV/V3gg+BvwW+AR5T/+W1wO/hP8BHQztSjYAK4A0wFvwX2Ae14TgcfAwepeyj4OJgHPgGOU/8/2/kN2ZapHVud8rWv0/pyjfJ5LtJyKgZlHgYcqDzkg9U9VN254FLlQSvVcr1ey3E5WAKuANeA5eBG8AZNz9iQbRV4hqZH9k/W9MxFz8Z5mp6rwQHgfJc3VO2dzHxfGR693Cj18kXPzKMU9PKHRalXGKVehUcvNyx9ezzpq4pSrzpKvS1R6u2IUq8uSr36KPUao9Q75urRz0XmtbJebV1vXmitqq6lrfPyZSrfoXA/gunKc5ih/IdnK/9hrvqPBHeBU8Xt7g9QofEv0fi9+wMMRs/GoWAPcBiYCo4Eh4GjNf4x4GXgWHA+OA68FhyvvJLng4vV/WcwMUA56XXLtZ/sh5zU6+5FLwncB2aCB8Ac5X+8BvylxvsPsBg8CC4FXwWvB38FrlK+zw3g62A1+CZ4v/J+fhV8C3xA3Y8pD+gPlf/zXfXvFWiK5wzl5RwK/g3MU17PseAfwHzwj+AM8BhYAP4ZvEr15oPvgCXg38Fl6q/loWuKuLeG8ojV/SB6gH3Bntr/nKc8x73AYWAqWACm6b4QvcFl6n8z2EefC33Bz4Gngd8E+4GPgP3Bx8EzwRfAs8C94GCwARwK/gkcDv5NeSj/BZ4DxpLuUfpc6AMOBkeDI8DzwFFgOngemAFOUP8p4LngdHG7POiyTkTXo9SF8aBPRC9OeSsTwcn6fJgC5oBTwRHgDHAqOFvLpQC8UvWvBa8Al4BztJymgSvEre00Rtcx6PqMOvuaUr786T4R3bW9poPXgdnqPk3dF4FF4Ezlb79KeduLlKd9CbgMXA7+HlwJrgSrlI/9bnAN+FnwJvDren678vfuADeAT4EfB58H7wF/Dm4ED6neH8HPgO+C94E9lMc3RXl8+4NfBIeDXFPux1fBAvBBcCW4A/wM+C3wQfConQ7lbX4MrAafUPdT4E7wafA74LPg4+BhsBY8CT4JxsfQ7sAeoB0fZSvhM8Efgrng0+B48BnwQvDH4AxwNzgHfB68BvwpuBg=
*/