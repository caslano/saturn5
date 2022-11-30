//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_SYNC_UTILS_HPP
#define BOOST_INTERPROCESS_DETAIL_SYNC_UTILS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/win32_api.hpp>
#include <boost/interprocess/sync/spin/mutex.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/windows/winapi_semaphore_wrapper.hpp>
#include <boost/interprocess/sync/windows/winapi_mutex_wrapper.hpp>

//Shield against external warnings
#include <boost/interprocess/detail/config_external_begin.hpp>
#include <boost/unordered/unordered_map.hpp>
#include <boost/interprocess/detail/config_external_end.hpp>
#include <boost/container/flat_map.hpp>

#include <cstddef>

namespace boost {
namespace interprocess {
namespace ipcdetail {

inline bool bytes_to_str(const void *mem, const std::size_t mem_length, char *out_str, std::size_t &out_length)
{
   const std::size_t need_mem = mem_length*2+1;
   if(out_length < need_mem){
      out_length = need_mem;
      return false;
   }

   const char Characters [] =
      { '0', '1', '2', '3', '4', '5', '6', '7'
      , '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

   std::size_t char_counter = 0;
   const char *buf = (const char *)mem;
   for(std::size_t i = 0; i != mem_length; ++i){
      out_str[char_counter++] = Characters[(buf[i]&0xF0)>>4];
      out_str[char_counter++] = Characters[(buf[i]&0x0F)];
   }
   out_str[char_counter] = 0;
   return true;
}

inline bool bytes_to_str(const void *mem, const std::size_t mem_length, wchar_t *out_str, std::size_t &out_length)
{
   const std::size_t need_mem = mem_length*2+1;
   if(out_length < need_mem){
      out_length = need_mem;
      return false;
   }

   const wchar_t Characters [] =
      { L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7'
      , L'8', L'9', L'A', L'B', L'C', L'D', L'E', L'F' };

   std::size_t char_counter = 0;
   const char *buf = (const char *)mem;
   for(std::size_t i = 0; i != mem_length; ++i){
      out_str[char_counter++] = Characters[(buf[i]&0xF0)>>4];
      out_str[char_counter++] = Characters[(buf[i]&0x0F)];
   }
   out_str[char_counter] = 0;
   return true;
}

class sync_id
{
   public:
   typedef __int64 internal_type;
   sync_id()
   {  winapi::query_performance_counter(&rand_);  }

   explicit sync_id(internal_type val)
   {  rand_ = val;  }

   const internal_type &internal_pod() const
   {  return rand_;  }

   internal_type &internal_pod()
   {  return rand_;  }

   friend std::size_t hash_value(const sync_id &m)
   {  return boost::hash_value(m.rand_);  }

   friend bool operator==(const sync_id &l, const sync_id &r)
   {  return l.rand_ == r.rand_;  }

   private:
   internal_type rand_;
};

class sync_handles
{
   public:
   enum type { MUTEX, SEMAPHORE };

   private:

   //key: id -> mapped: HANDLE. Hash map to allow efficient sync operations
   typedef boost::unordered_map<sync_id, void*> umap_type;
   //key: ordered address of the sync type -> iterator from umap_type. Ordered map to allow closing handles when unmapping
   typedef boost::container::flat_map<const void*, umap_type::iterator> map_type;
   static const std::size_t LengthOfGlobal = sizeof("Global\\boost.ipc")-1;
   static const std::size_t StrSize        = LengthOfGlobal + (sizeof(sync_id)*2+1);
   typedef char NameBuf[StrSize];

   void fill_name(NameBuf &name, const sync_id &id)
   {
      const char *n = "Global\\boost.ipc";
      std::size_t i = 0;
      do{
         name[i] = n[i];
         ++i;
      } while(n[i]);
      std::size_t len = sizeof(NameBuf) - LengthOfGlobal;
      bytes_to_str(&id.internal_pod(), sizeof(id.internal_pod()), &name[LengthOfGlobal], len);
   }

   void throw_if_error(void *hnd_val)
   {
      if(!hnd_val){
         error_info err(static_cast<int>(winapi::get_last_error()));
         throw interprocess_exception(err);
      }
   }

   void* open_or_create_semaphore(const sync_id &id, unsigned int initial_count)
   {
      NameBuf name;
      fill_name(name, id);
      permissions unrestricted_security;
      unrestricted_security.set_unrestricted();
      winapi_semaphore_wrapper sem_wrapper;
      bool created;
      sem_wrapper.open_or_create
         (name, (long)initial_count, winapi_semaphore_wrapper::MaxCount, unrestricted_security, created);
      throw_if_error(sem_wrapper.handle());
      return sem_wrapper.release();
   }

   void* open_or_create_mutex(const sync_id &id)
   {
      NameBuf name;
      fill_name(name, id);
      permissions unrestricted_security;
      unrestricted_security.set_unrestricted();
      winapi_mutex_wrapper mtx_wrapper;
      mtx_wrapper.open_or_create(name, unrestricted_security);
      throw_if_error(mtx_wrapper.handle());
      return mtx_wrapper.release();
   }

   public:
   sync_handles()
      : num_handles_()
   {}

   ~sync_handles()
   {
      BOOST_ASSERT(num_handles_ == 0); //Sanity check that handle we don't leak handles
   }

   void *obtain_mutex(const sync_id &id, const void *mapping_address, bool *popen_created = 0)
   {
      umap_type::value_type v(id, (void*)0);
      scoped_lock<spin_mutex> lock(mtx_);
      umap_type::iterator it = umap_.insert(v).first;
      void *&hnd_val = it->second;
      if(!hnd_val){
         BOOST_ASSERT(map_.find(mapping_address) == map_.end());
         map_[mapping_address] = it;
         hnd_val = open_or_create_mutex(id);
         if(popen_created) *popen_created = true;
         ++num_handles_;
      }
      else if(popen_created){
         BOOST_ASSERT(map_.find(mapping_address) != map_.end());
         *popen_created = false;
      }

      return hnd_val;
   }

   void *obtain_semaphore(const sync_id &id, const void *mapping_address, unsigned int initial_count, bool *popen_created = 0)
   {
      umap_type::value_type v(id, (void*)0);
      scoped_lock<spin_mutex> lock(mtx_);
      umap_type::iterator it = umap_.insert(v).first;
      void *&hnd_val = it->second;
      if(!hnd_val){
         BOOST_ASSERT(map_.find(mapping_address) == map_.end());
         map_[mapping_address] = it;
         hnd_val = open_or_create_semaphore(id, initial_count);
         if(popen_created) *popen_created = true;
         ++num_handles_;
      }
      else if(popen_created){
         BOOST_ASSERT(map_.find(mapping_address) != map_.end());
         *popen_created = false;
      }
      return hnd_val;
   }

   void destroy_handle(const sync_id &id, const void *mapping_address)
   {
      scoped_lock<spin_mutex> lock(mtx_);
      umap_type::iterator it = umap_.find(id);
      umap_type::iterator itend = umap_.end();

      if(it != itend){
         winapi::close_handle(it->second);
         --num_handles_;
         std::size_t i = map_.erase(mapping_address);
         (void)i;
         BOOST_ASSERT(i == 1);   //The entry should be there
         umap_.erase(it);
      }
   }

   void destroy_syncs_in_range(const void *addr, std::size_t size)
   {
      const void *low_id(addr);
      const void *hig_id(static_cast<const char*>(addr)+size);
      scoped_lock<spin_mutex> lock(mtx_);
      map_type::iterator itlow(map_.lower_bound(low_id)),
                         ithig(map_.lower_bound(hig_id)),
                         it(itlow);
      for (; it != ithig; ++it){
         umap_type::iterator uit = it->second; 
         void * const hnd = uit->second;
         umap_.erase(uit);
         int ret = winapi::close_handle(hnd);
         --num_handles_;
         BOOST_ASSERT(ret != 0); (void)ret;  //Sanity check that handle was ok
      }

      map_.erase(itlow, ithig);
   }

   private:
   spin_mutex mtx_;
   umap_type umap_;
   map_type map_;
   std::size_t num_handles_;
};


}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_SYNC_UTILS_HPP

/* sync_utils.hpp
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
*/