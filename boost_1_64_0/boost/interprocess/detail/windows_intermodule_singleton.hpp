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
DLdjzgjaUSE2pjDsS2xbIruS2JRqtie525KqsiFp29Ha0TXbjMhWFIadCDYi2Ia0XUjbhELtQeHZgtaBQm1AcdXZfsTu47T3aFvPetCe6u05YsvRNhyn/UbbbmC3cdpstK2G7DTaPmO3zVRtlyGbjNhjtC3G3Q7jtME47S/a9mK3uzhtLk57S812FrGxiH0lPNuK3a5Ss00lHFuKtqGw7WTx9nO2hnN/5/7O/Z37O/d37u/c37m/qub/hf+F+X9meVk+GQAM49+yAaj5e3LI/L2NfON9l+RnE2h0gpqz0fydp+181JU6lDqzFCf15RUVWucgmnwOovt5M4Y+b+buBoo3B3enzLXuiCoi/1txhozpcg6PDt/AOqs2e7Y6UNX1nE7N73rWYjn5rcCe2siQs2oKcIaQvg9hL/E0ge3DQ3HIPZnWGca3kf9Q8muhHIz51vmRN5FfqTETvuyGW6TJrQRvnBly5o7KgT77bi3x5CPtddnNCjfPqA9XdZYNfQenzu2ORT59UdFmHTr2sQDHPrred5QgYXbBo7kKU6dZtDfScJz9GHxuUYtzH1Wdx1Od6/ONVN3Gc91a58DRebO6vvR98byflP4OSz3/BTQZhZhihrY5HGMuRzzVs+4slPs5pb66EH8Tt7YncZkhYSUuCTvVrOIuDwqr293EBDqHckGZuujV0Gf23Uo8ndzaoQ6v6zx4VpXV9vsSz6vU9uvp9oQLNHTbuIx4XjNuMCJC2w8VQrBd9yaeAzhDIpLOEG3vpf38RktV79FLnHdsCc9B8LRSPP5Z+ry0SncW3xPDtEHOSdpoUc3tRZ2L/LLpOBdZ7jKkLEj7ETeuH6v9oNzhJuXO7YdlFu8Xp79mhsZM8Gd4XNtP5oyionywONqRs91wHPbzGrNKCztxFM62IvzubcXZNjS/1W8vilVUs+3TrfwSQs8X0+kMqwyP1+HIG8tLzpcyrKimDDMLZ4ZVhhW1LMOKWpah8Eu7/e+WX/C81CORHHmFvGQJKAv8m6oov7zCsrDKjsKLTPghlsoOQfUYtZn8443IKsbMTbUsS+J33Beg709q6FX+0TQOnUCbyUe+W6tzWWMCdel65gtxqlpkPMpssjU+tI1lebENJOer4m9GYVmBvvtwN713otGb06rPoyMJaFjybTvx5Rtpho9kk+43JIfCvlfVTe6o8o3n8g2rzyRGOc8lzAN/qte9zsuzodqFKXcoDtudKhSHs46Jt3Z1nOr9z/QXfUdJePI6ON4flnIbLPtyB4F+hzgybOWWXVQ4U58z2oLKQLnptjiB+Pu7y23Oo7RDahuaanGHWQvKG73XVvc9zmPmDz18hrX6jmwu8rzNlodZuWUuY04rXZ/WvVhPULh3PNd6zjPWgpx5ori1HPXVLEeFX9ob9TmbPvEk+a/2zPBcZOmazQPKbS5mEE1lTOK+e3sYfUuN8eMCzjG+lW4fWsb6bDLWJkun15MDh6V9DAUVqvG8jqNstSy1l6uVxwkUpo/R3f0MeMSpyyg/QctXZ3naebtTSvO4POU+gizy72m0MupYZdcOfLfXor2FlJXVv5AukUv2Mad3LEfwJ5O/D3wJOE+1QVs5FWeVlOZmUje0yZ78vEJX2SPhQ+Uw8eIiNwqfRnddHCGe35qih4quqs/A7BWh/HcbjbAavhmhaLyCS/1I5T4Y41VPnlPJOdVN4a/q+kd+t5kKLa4U4Vbjfofn6O43+MPnXorXGzIfm2fdx/cPCtvIaB68O5d4Z5lDkKs5KLlr4fcO6qar6QsJr8egHyj8tWaiye9rZKW3S+h5pmVZZbnWPM9D7ygzz5MwCVaYruDhea7B9Vkq81S6D1eXmxoG9Xg=
*/