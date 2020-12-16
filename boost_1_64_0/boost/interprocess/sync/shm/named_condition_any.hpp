//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SHM_NAMED_CONDITION_ANY_HPP
#define BOOST_INTERPROCESS_SHM_NAMED_CONDITION_ANY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/static_assert.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/shm/named_creation_functor.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/detail/condition_any_algorithm.hpp>

//!\file
//!Describes process-shared variables interprocess_condition class

namespace boost {
namespace interprocess {
namespace ipcdetail {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
class interprocess_tester;
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//! A global condition variable that can be created by name.
//! This condition variable is designed to work with named_mutex and
//! can't be placed in shared memory or memory mapped files.
class shm_named_condition_any
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   shm_named_condition_any();
   shm_named_condition_any(const shm_named_condition_any &);
   shm_named_condition_any &operator=(const shm_named_condition_any &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:
   //!Creates a global condition with a name.
   //!If the condition can't be created throws interprocess_exception
   shm_named_condition_any(create_only_t create_only, const char *name, const permissions &perm = permissions())
      :  m_shmem  (create_only
                  ,name
                  ,sizeof(internal_condition) +
                     open_create_impl_t::ManagedOpenOrCreateUserOffset
                  ,read_write
                  ,0
                  ,construct_func_t(DoCreate)
                  ,perm)
   {}

   //!Opens or creates a global condition with a name.
   //!If the condition is created, this call is equivalent to
   //!shm_named_condition_any(create_only_t, ... )
   //!If the condition is already created, this call is equivalent
   //!shm_named_condition_any(open_only_t, ... )
   //!Does not throw
   shm_named_condition_any(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions())
      :  m_shmem  (open_or_create
                  ,name
                  ,sizeof(internal_condition) +
                     open_create_impl_t::ManagedOpenOrCreateUserOffset
                  ,read_write
                  ,0
                  ,construct_func_t(DoOpenOrCreate)
                  ,perm)
   {}

   //!Opens a global condition with a name if that condition is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   shm_named_condition_any(open_only_t open_only, const char *name)
      :  m_shmem  (open_only
                  ,name
                  ,read_write
                  ,0
                  ,construct_func_t(DoOpen))
   {}

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~shm_named_condition_any()
   {}

   //!If there is a thread waiting on *this, change that
   //!thread's state to ready. Otherwise there is no effect.*/
   void notify_one()
   {  this->internal_cond().notify_one(); }

   //!Change the state of all threads waiting on *this to ready.
   //!If there are no waiting threads, notify_all() has no effect.
   void notify_all()
   {  this->internal_cond().notify_all(); }

   //!Releases the lock on the named_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), and then reacquires the lock.
   template <typename L>
   void wait(L& lock)
   {  this->internal_cond().wait(lock); }

   //!The same as:
   //!while (!pred()) wait(lock)
   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {  this->internal_cond().wait(lock, pred); }

   //!Releases the lock on the named_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), or until time abs_time is reached,
   //!and then reacquires the lock.
   //!Returns: false if time abs_time is reached, otherwise true.
   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {  return this->internal_cond().timed_wait(lock, abs_time); }

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
   {  return this->internal_cond().timed_wait(lock, abs_time, pred); }

   //!Erases a named condition from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name)
   {  return shared_memory_object::remove(name); }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:

   class internal_condition_members
   {
      public:
      typedef interprocess_mutex       mutex_type;
      typedef interprocess_condition   condvar_type;

      condvar_type&  get_condvar() {  return m_cond;  }
      mutex_type&    get_mutex()   {  return m_mtx; }

      private:
      mutex_type     m_mtx;
      condvar_type   m_cond;
   };

   typedef ipcdetail::condition_any_wrapper<internal_condition_members> internal_condition;

   internal_condition &internal_cond()
   {  return *static_cast<internal_condition*>(m_shmem.get_user_address()); }

   friend class boost::interprocess::ipcdetail::interprocess_tester;
   void dont_close_on_destruction()
   {  interprocess_tester::dont_close_on_destruction(m_shmem);  }

   typedef ipcdetail::managed_open_or_create_impl<shared_memory_object, 0, true, false> open_create_impl_t;
   open_create_impl_t m_shmem;

   template <class T, class Arg> friend class boost::interprocess::ipcdetail::named_creation_functor;
   typedef boost::interprocess::ipcdetail::named_creation_functor<internal_condition> construct_func_t;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_SHM_NAMED_CONDITION_ANY_HPP

/* named_condition_any.hpp
D+Gu4bjC/ihBqpEduLeA+8ECdKyrKQ+O6/BbijvnE6QJv8ngdLAQqedcJe4qjjcjjbi3455Jn1aGVCM7kf3ISSRnaaw1GVmKbER2IA3ICWRgaaw1HVmKbER2IgcR63rOIdORMqQaqUUOInHLYq08pAApQ2qQXUgjEldG34pMR8qQamQnsh85gfRlQnQsMg9Zh2xB6pBDSJBJ0mFIAbIW2YLsRo4hmeXkASlDNiHPIkeRNCZO8yvwr8Af2YUcQtJuiLXGI8VIFbIZ2YUcQjp/nb/OX9O62hVWQPe3WVBeUbKiaRPcpsNVZcOvW83edsNHjhg5Infx8DWrRuWOHOOcWzv2vOGrWJxdUjx8JRbHi1aVhDSKVt5UUVm+YK3ss7ugouimhZVwM4wov+56e95gfC/746iL7DP/1CLLwUtLi1aWrypfXJkz+PIhObMrKkuXl95cumJJzkUY+pWWlaxk/czMXr1TLYevv1hJ2ezxj57gOHCmze1wQGyXxECroryslAQULS0pWhay05ohe6lU2Ily7CO+L2FO8O75spnrQc7rnrxxEp7tMom7tFKv4dqqPCe65dblhFyCGPkg0Anbd7FkZeUqM8ex6qaj211s7jVX5aXFq0z8gmHxr7aEk6Ns0ZKm+NM8ummqa9gz0SmbC35hnz+X62c5tiE3id9c9lZOcmxlfil+CeJOc9xBiXei8MuuKC8uWaX6fAOqvn2+VDbEkVvi8BueJ+e/bY2iDO9DvqJleaKZrUvpCm4BCXZtff4k+ZlJNQsynxXvpO+wHR/udCc9i1ZDPNyUKC1H2xZC9rjHPTaWOG17jmDVEZf3Rm0+VGcBOhmpsq9YQvi+eyHu5kzOZyHZin2Qvshp4tZ9xFrkiYvvRVmqXUb5Si/fll2Xe2td7hey9YvDz18/1XZY9xrT+patXIN2verdvF6JfhoothRaf/CT8rfvV2/nfvWScpsoaXHL1LFd1/bKofzu1THFjchVhMn/pa+92hErA43l1I+AXM/dj3aKhLvL1F6J063TF8m9LlqNTYvDx71YzheH88VJfpfKuSJLeCaJbHI890i4KDOCseQk3LYnRfWWxmt9Sexp+eqL6mxEp7/ENS9iPDuc640J03H3gP8+8eaIPZAt0XMNuvetuU3uTr03Z2igAUguhXFMyoI9l+w76uEEek7sNG1Pl6vxuOj2MdwPjce1yyDNrdtlhNJsX6u3XsvLvVbYxW+j+60MyuVgstroTrpi1siFsy+cMeWiOR4OpkczWrbTJXy77YmJ28gTNzPRn9bvoJtrTKvYT0WVVsJHbVOMbrttih/NaN2mOGQDdNKQ16V2O3fyKk29YPbMiy+6euHkSXMmubbei/u0wtnQgXtD3EYb/BNd/ektRrcgYnodgixJ85SW00w8rn3zPVmt82Oh325+LNLi40vgmmH8WG7ej3bz5/16myMvct7V5j26+1XYhvpZ2IH6ubhP6/XT4UNL8ue5jPAVxjzPmj15SnNOnYmt5Jl4ouLUQa/dnDqkoSVOHZc/JejP6wrCVkXMq5AgRpXPKs+9fa4V/jN0282BONFwb5+LwH+2trs/v7MIXx0xv9KOo8ovcbSbA9HNQ1j7M6S3HN0tEdPbcc6jzT3817zc/m6KeE23fy5opYx2dKB/LohQRjU9/em9Dt26yOmlf47+vtZ5+ueRaa33z3Ud6J8nGvpnrhmRv3BDsrn91kfMu/A9RZXv+ja0X3TbzfcUTfsN3et1vfz5vYHwjZHzq8+j6OpnYxueR40deB4VRPE8Cr1756SY+XCOHUxuFx/OsQ60wUh8OImpZj4c69XkdvPhWK9Gfy+sV9t/L6Lhwwm9py9I0/U=
*/