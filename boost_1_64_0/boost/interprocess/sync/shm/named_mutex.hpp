//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SHM_NAMED_MUTEX_HPP
#define BOOST_INTERPROCESS_SHM_NAMED_MUTEX_HPP

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
#include <boost/interprocess/detail/interprocess_tester.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/sync/shm/named_creation_functor.hpp>

//!\file
//!Describes a named mutex class for inter-process synchronization

namespace boost {
namespace interprocess {
namespace ipcdetail {

class named_condition;

//!A mutex with a global name, so it can be found from different
//!processes. This mutex can't be placed in shared memory, and
//!each process should have it's own named mutex.
class shm_named_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   shm_named_mutex();
   shm_named_mutex(const shm_named_mutex &);
   shm_named_mutex &operator=(const shm_named_mutex &);
   friend class named_condition;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Creates a global interprocess_mutex with a name.
   //!Throws interprocess_exception on error.
   shm_named_mutex(create_only_t create_only, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global mutex with a name.
   //!If the mutex is created, this call is equivalent to
   //!shm_named_mutex(create_only_t, ... )
   //!If the mutex is already created, this call is equivalent
   //!shm_named_mutex(open_only_t, ... )
   //!Does not throw
   shm_named_mutex(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions());

   //!Opens a global mutex with a name if that mutex is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   shm_named_mutex(open_only_t open_only, const char *name);

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~shm_named_mutex();

   //!Unlocks a previously locked
   //!interprocess_mutex.
   void unlock();

   //!Locks interprocess_mutex, sleeps when interprocess_mutex is already locked.
   //!Throws interprocess_exception if a severe error is found
   void lock();

   //!Tries to lock the interprocess_mutex, returns false when interprocess_mutex
   //!is already locked, returns true when success.
   //!Throws interprocess_exception if a severe error is found
   bool try_lock();

   //!Tries to lock the interprocess_mutex until time abs_time,
   //!Returns false when timeout expires, returns true when locks.
   //!Throws interprocess_exception if a severe error is found
   bool timed_lock(const boost::posix_time::ptime &abs_time);

   //!Erases a named mutex from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef interprocess_mutex internal_mutex_type;
   interprocess_mutex &internal_mutex()
   {  return *static_cast<interprocess_mutex*>(m_shmem.get_user_address()); }

   private:
   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction();
   typedef ipcdetail::managed_open_or_create_impl<shared_memory_object, 0, true, false> open_create_impl_t;
   open_create_impl_t m_shmem;
   typedef ipcdetail::named_creation_functor<interprocess_mutex> construct_func_t;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline void shm_named_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_shmem);  }

inline shm_named_mutex::~shm_named_mutex()
{}

inline shm_named_mutex::shm_named_mutex(create_only_t, const char *name, const permissions &perm)
   :  m_shmem  (create_only
               ,name
               ,sizeof(interprocess_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoCreate)
               ,perm)
{}

inline shm_named_mutex::shm_named_mutex(open_or_create_t, const char *name, const permissions &perm)
   :  m_shmem  (open_or_create
               ,name
               ,sizeof(interprocess_mutex) +
                  open_create_impl_t::ManagedOpenOrCreateUserOffset
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpenOrCreate)
               ,perm)
{}

inline shm_named_mutex::shm_named_mutex(open_only_t, const char *name)
   :  m_shmem  (open_only
               ,name
               ,read_write
               ,0
               ,construct_func_t(ipcdetail::DoOpen))
{}

inline void shm_named_mutex::lock()
{  this->internal_mutex().lock();  }

inline void shm_named_mutex::unlock()
{  this->internal_mutex().unlock();  }

inline bool shm_named_mutex::try_lock()
{  return this->internal_mutex().try_lock();  }

inline bool shm_named_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
{  return this->internal_mutex().timed_lock(abs_time);   }

inline bool shm_named_mutex::remove(const char *name)
{  return shared_memory_object::remove(name); }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_SHM_NAMED_MUTEX_HPP

/* named_mutex.hpp
nBtDafR13snmi9/HZb8x33ePts29onORNdzdw1vjOkCpv6j7FuozZ+GqZaUVbrs8U9J8plMHCuVeXeG8M+eI+xli/rTk+zBpmiphvhTjttuykjUlZU6cO+Xayc5cdJrEEYu7qZx+IOcHBsLarFMHfi/xX+DMR18m4cutdK0TO+T8vEAq9eErdn3Q56ym1ZPf5YsqNL/9tD84TcI+FTPeSuRuxlt3BhKtN8BsJ0z40gD33SNTwj4ZyKfnuCOQgJ2dPKu1vN06XtQ02u6k/zYJN0DrXahOf4r8VwXC9e3DZ+Q891K/UZry+w/sMZdK3lZrOhc2NV8rXetKqFy+aU1F+0pjWoZJGZ1piMdtw6NFZwp9WbLM84/NIdyZwnXG+2r3YGx3y/esT1G9AvT+ZOt1C+cLdXUqXZ3nI+nUODp35IbrXIi7J+63k5v67XMQGx9MRnTOf2VK82//LI9ervbvmS327/G9/ir31LpuUbGsuTCuK9HxAe+6EfELhq0N8T6TBw7lT+wruQ74KfAOe17jt+6zoax0xbKFNFfLN97jvtftEP3bAtcHEqUNkDaNo4/7jBA/01iQ+5wpfiNZ9jjN4J6vMu9bSRymcRrze7TqNn9ma/3bKedKAmdbcQ4X9dA3bb8YJw9Pic5a//usxvGanL80EEdLDI/Dfj+cw7P38KDQd2BaMLFLMPb2QXwNRng//JCG2XQ28w2EiZ2QkBKbmXRG0sikgXwQ9kqIiU1NGpI0O6FrMGVmQkZsGl+IExL4crvDbQejCGdaL5MiZbtBv4UYOZC0LwpciF9BgG9g+d7Rfke+otx+/R3R/QrtcKH2QRqeZ9NpWK//1hrCt1mq0/81nSsKhH2bOP3wUElLpvOMuEjc03CPtM6iDI5SZhuGYHdql8HtVkK32PiExNgMctsvLiEm2BXOI9O4WsRxwwck/h5hzy03Pd+R80NayFu3pndqTduOIaF3/qvhL7b83xuq1+joldvfBnGVwa7xpvs+QPXLzm7Kc0JsbNUXkgZqvk8j3wPiNJzm15xXtyxTIub1Sjk/0in7O8X9IO2zJtTvSVqqz3a+Ue4I7/dET+tq7dk6fhDM9X0jhdxnRrE/b1vHPN333eZjBoXDmyLdqZxv30Y22n3am2F9mgxjs3RVP1dMfVuaRRlIuE+z5mqumdP3zeZjwQEpb7dv/KmcX2/dZBn3VdXw5j7qaTm30bqd57znHWfRqkq3bdaKzn28YXbzvm/oGL2bjy6H5dlPGuKc97yX7LDyTF7ktN068dsUcTyx8c2m+jPIs4Z0psSdIH3eYJ4pB4eF+ryUYHwy2+IHY6cy+mX+JtYw1vDQONSoiHvo50ndb7U+tTqGbt+n3nqfvM/DtblNEQS4eBr4LlJF+OrDzeuOVpmwOuOOM/1A9J+ijOYyppFjqjfEGf28CLr+8SCtX1+Tc4covnutV9AI3cdt4v+W4V1d9/2V8w8T6jS5b8WU/6YRvHPJmG33YFJSMK7q4WBS9wjPqlEaJpEyO0/u9flJq5OWJo1Iuth+TNFnJaUldI/tmZASjEtOSqTb7tXFcB+N9f4XkravWh+xTg+r924/9rToPKluWthbUkYttoE+b7ltIPQcfEPi+bq0gU9aPZ1vuqb4X4zYDo4f9reDmyX+BBkDr6EsG88JtYPzWW4ajL2ERmBsA6oflxtqA1dZxj5Xy3wYemMitJVox3da62e9c4O7z22K4IjWx7eQO9FtfKt5u3AnBw1tQ+vdGxKmkXvbxfokkiLvWqG4jjBiOcFtJ+IffTtB1zAH6O53cVTO77dupD+9CzG8MxKH8f3SOGeour73rQz7/BH73BznW2uluK+gXGcb37U=
*/