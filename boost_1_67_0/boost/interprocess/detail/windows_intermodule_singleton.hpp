//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2009-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_WINDOWS_INTERMODULE_SINGLETON_HPP
#define BOOST_INTERPROCESS_WINDOWS_INTERMODULE_SINGLETON_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/container/string.hpp>

#if !defined(BOOST_INTERPROCESS_WINDOWS)
   #error "This header can't be included from non-windows operating systems"
#endif

#include <boost/assert.hpp>
#include <boost/interprocess/detail/intermodule_singleton_common.hpp>
#include <boost/interprocess/sync/windows/winapi_semaphore_wrapper.hpp>
#include <boost/interprocess/sync/windows/winapi_mutex_wrapper.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/cstdint.hpp>
#include <string>
#include <boost/container/map.hpp>

namespace boost{
namespace interprocess{
namespace ipcdetail{

namespace intermodule_singleton_helpers {

//This global map will be implemented using 3 sync primitives:
//
//1)  A named mutex that will implement global mutual exclusion between
//    threads from different modules/dlls
//
//2)  A semaphore that will act as a global counter for modules attached to the global map
//    so that the global map can be destroyed when the last module is detached.
//
//3)  A semaphore that will be hacked to hold the address of a heap-allocated map in the
//    max and current semaphore count.
class windows_semaphore_based_map
{
   typedef boost::container::map<boost::container::string, ref_count_ptr> map_type;

   public:
   windows_semaphore_based_map()
   {
      map_type *m = new map_type;
      boost::uint32_t initial_count = 0;
      boost::uint32_t max_count = 0;

      //Windows user address space sizes:
      //32 bit windows: [32 bit processes] 2GB or 3GB (31/32 bits)
      //64 bit windows: [32 bit processes] 2GB or 4GB (31/32 bits)
      //                [64 bit processes] 2GB or 8TB (31/43 bits)
      //
      //Windows semaphores use 'long' parameters (32 bits in LLP64 data model) and
      //those values can't be negative, so we have 31 bits to store something
      //in max_count and initial count parameters.
      //Also, max count must be bigger than 0 and bigger or equal than initial count.
      if(sizeof(void*) == sizeof(boost::uint32_t)){
         //This means that for 32 bit processes, a semaphore count (31 usable bits) is
         //enough to store 4 byte aligned memory (4GB -> 32 bits - 2 bits = 30 bits).
         //The max count will hold the pointer value and current semaphore count
         //will be zero.
         //
         //Relying in UB with a cast through union, but all known windows compilers
         //accept this (C11 also accepts this).
         union caster_union
         {
            void *addr;
            boost::uint32_t addr_uint32;
         } caster;
         caster.addr = m;
         //memory is at least 4 byte aligned in windows
         BOOST_ASSERT((caster.addr_uint32 & boost::uint32_t(3)) == 0);
         max_count = caster.addr_uint32 >> 2;
      }
      else if(sizeof(void*) == sizeof(boost::uint64_t)){
         //Relying in UB with a cast through union, but all known windows compilers
         //accept this (C11 accepts this).
         union caster_union
         {
            void *addr;
            boost::uint64_t addr_uint64;
         } caster;
         caster.addr = m;
         //We'll encode the address using 30 bits in each 32 bit high and low parts.
         //High part will be the sem max count, low part will be the sem initial count.
         //(restrictions: max count > 0, initial count >= 0 and max count >= initial count):
         //
         // - Low part will be shifted two times (4 byte alignment) so that top
         //   two bits are cleared (the top one for sign, the next one to
         //   assure low part value is always less than the high part value.
         // - The top bit of the high part will be cleared and the next bit will be 1
         //   (so high part is always bigger than low part due to the quasi-top bit).
         //
         //   This means that the addresses we can store must be 4 byte aligned
         //   and less than 1 ExbiBytes ( 2^60 bytes, ~1 ExaByte). User-level address space in Windows 64
         //   is much less than this (8TB, 2^43 bytes): "1 EByte (or it was 640K?) ought to be enough for anybody" ;-).
         caster.addr = m;
         BOOST_ASSERT((caster.addr_uint64 & boost::uint64_t(3)) == 0);
         max_count = boost::uint32_t(caster.addr_uint64 >> 32);
         initial_count = boost::uint32_t(caster.addr_uint64);
         initial_count = initial_count/4;
         //Make sure top two bits are zero
         BOOST_ASSERT((max_count & boost::uint32_t(0xC0000000)) == 0);
         //Set quasi-top bit
         max_count |= boost::uint32_t(0x40000000);
      }
      bool created = false;
      const permissions & perm = permissions();
      std::string pid_creation_time, name;
      get_pid_creation_time_str(pid_creation_time);
      name = "bipc_gmap_sem_lock_";
      name += pid_creation_time;
      bool success = m_mtx_lock.open_or_create(name.c_str(), perm);
      name = "bipc_gmap_sem_count_";
      name += pid_creation_time;
      scoped_lock<winapi_mutex_wrapper> lck(m_mtx_lock);
      {
         success = success && m_sem_count.open_or_create
            ( name.c_str(), static_cast<long>(0), winapi_semaphore_wrapper::MaxCount, perm, created);
         name = "bipc_gmap_sem_map_";
         name += pid_creation_time;
         success = success && m_sem_map.open_or_create
            (name.c_str(), initial_count, max_count, perm, created);
         if(!success){
            delete m;
            //winapi_xxx wrappers do the cleanup...
            throw int(0);
         }
         if(!created){
            delete m;
         }
         else{
            BOOST_ASSERT(&get_map_unlocked() == m);
         }
         m_sem_count.post();
      }
   }

   map_type &get_map_unlocked()
   {
      if(sizeof(void*) == sizeof(boost::uint32_t)){
         union caster_union
         {
            void *addr;
            boost::uint32_t addr_uint32;
         } caster;
         caster.addr = 0;
         caster.addr_uint32 = m_sem_map.limit();
         caster.addr_uint32 = caster.addr_uint32 << 2;
         return *static_cast<map_type*>(caster.addr);
      }
      else{
         union caster_union
         {
            void *addr;
            boost::uint64_t addr_uint64;
         } caster;
         boost::uint32_t max_count(m_sem_map.limit()), initial_count(m_sem_map.value());
         //Clear quasi-top bit
         max_count &= boost::uint32_t(0xBFFFFFFF);
         caster.addr_uint64 = max_count;
         caster.addr_uint64 =  caster.addr_uint64 << 32;
         caster.addr_uint64 |= boost::uint64_t(initial_count) << 2;
         return *static_cast<map_type*>(caster.addr);
      }
   }

   ref_count_ptr *find(const char *name)
   {
      scoped_lock<winapi_mutex_wrapper> lck(m_mtx_lock);
      map_type &map = this->get_map_unlocked();
      map_type::iterator it = map.find(boost::container::string(name));
      if(it != map.end()){
         return &it->second;
      }
      else{
         return 0;
      }
   }

   ref_count_ptr * insert(const char *name, const ref_count_ptr &ref)
   {
      scoped_lock<winapi_mutex_wrapper> lck(m_mtx_lock);
      map_type &map = this->get_map_unlocked();
      map_type::iterator it = map.insert(map_type::value_type(boost::container::string(name), ref)).first;
      return &it->second;
   }

   bool erase(const char *name)
   {
      scoped_lock<winapi_mutex_wrapper> lck(m_mtx_lock);
      map_type &map = this->get_map_unlocked();
      return map.erase(boost::container::string(name)) != 0;
   }

   template<class F>
   void atomic_func(F &f)
   {
      scoped_lock<winapi_mutex_wrapper> lck(m_mtx_lock);
      f();
   }

   ~windows_semaphore_based_map()
   {
      scoped_lock<winapi_mutex_wrapper> lck(m_mtx_lock);
      m_sem_count.wait();
      if(0 == m_sem_count.value()){
         map_type &map = this->get_map_unlocked();
         BOOST_ASSERT(map.empty());
         delete &map;
      }
      //First close sems to protect this with the external mutex
      m_sem_map.close();
      m_sem_count.close();
      //Once scoped_lock unlocks the mutex, the destructor will close the handle...
   }

   private:
   winapi_mutex_wrapper     m_mtx_lock;
   winapi_semaphore_wrapper m_sem_map;
   winapi_semaphore_wrapper m_sem_count;
};

template<>
struct thread_safe_global_map_dependant<windows_semaphore_based_map>
{
   static void apply_gmem_erase_logic(const char *, const char *){}

   static bool remove_old_gmem()
   { return true; }

   struct lock_file_logic
   {
      lock_file_logic(windows_semaphore_based_map &)
         : retry_with_new_map(false)
      {}

      void operator()(void){}
      bool retry() const { return retry_with_new_map; }
      private:
      const bool retry_with_new_map;
   };

   static void construct_map(void *addr)
   {
      ::new (addr)windows_semaphore_based_map;
   }

   struct unlink_map_logic
   {
      unlink_map_logic(windows_semaphore_based_map &)
      {}
      void operator()(){}
   };

   static ref_count_ptr *find(windows_semaphore_based_map &map, const char *name)
   {
      return map.find(name);
   }

   static ref_count_ptr * insert(windows_semaphore_based_map &map, const char *name, const ref_count_ptr &ref)
   {
      return map.insert(name, ref);
   }

   static bool erase(windows_semaphore_based_map &map, const char *name)
   {
      return map.erase(name);
   }

   template<class F>
   static void atomic_func(windows_semaphore_based_map &map, F &f)
   {
      map.atomic_func(f);
   }
};

}  //namespace intermodule_singleton_helpers {

template<typename C, bool LazyInit = true, bool Phoenix = false>
class windows_intermodule_singleton
   : public intermodule_singleton_impl
      < C
      , LazyInit
      , Phoenix
      , intermodule_singleton_helpers::windows_semaphore_based_map
      >
{};

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_WINDOWS_INTERMODULE_SINGLETON_HPP

/* windows_intermodule_singleton.hpp
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
*/