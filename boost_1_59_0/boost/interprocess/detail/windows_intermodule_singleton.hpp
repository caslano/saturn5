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
            (name.c_str(), (long)initial_count, (long)max_count, perm, created);
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
         caster.addr_uint32 = boost::uint32_t(m_sem_map.limit());
         caster.addr_uint32 = caster.addr_uint32 << 2u;
         return *static_cast<map_type*>(caster.addr);
      }
      else{
         union caster_union
         {
            void *addr;
            boost::uint64_t addr_uint64;
         } caster;
         boost::uint32_t max_count(boost::uint32_t(m_sem_map.limit()))
                       , initial_count(boost::uint32_t(m_sem_map.value()));
         //Clear quasi-top bit
         max_count &= boost::uint32_t(0xBFFFFFFF);
         caster.addr_uint64 = max_count;
         caster.addr_uint64 =  caster.addr_uint64 << 32u;
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