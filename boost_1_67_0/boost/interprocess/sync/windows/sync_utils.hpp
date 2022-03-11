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


#include <boost/container/map.hpp>
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

class sync_id
{
   public:
   typedef __int64 internal_type;
   sync_id(const void *map_addr)
      : map_addr_(map_addr)
   {  winapi::query_performance_counter(&rand_);  }

   explicit sync_id(internal_type val, const void *map_addr)
      : map_addr_(map_addr)
   {  rand_ = val;  }

   const internal_type &internal_pod() const
   {  return rand_;  }

   internal_type &internal_pod()
   {  return rand_;  }

   const void *map_address() const
   {  return map_addr_;  }

   friend std::size_t hash_value(const sync_id &m)
   {  return boost::hash_value(m.rand_);  }

   friend bool operator==(const sync_id &l, const sync_id &r)
   {  return l.rand_ == r.rand_ && l.map_addr_ == r.map_addr_;  }

   private:
   internal_type rand_;
   const void * const map_addr_;
};

class sync_handles
{
   public:
   enum type { MUTEX, SEMAPHORE };

   private:
   struct address_less
   {
      bool operator()(sync_id const * const l, sync_id const * const r) const
      {  return l->map_address() <  r->map_address(); }
   };

   typedef boost::unordered_map<sync_id, void*> umap_type;
   typedef boost::container::map<const sync_id*, umap_type::iterator, address_less> map_type;
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
         error_info err(winapi::get_last_error());
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
   void *obtain_mutex(const sync_id &id, bool *popen_created = 0)
   {
      umap_type::value_type v(id, (void*)0);
      scoped_lock<spin_mutex> lock(mtx_);
      umap_type::iterator it = umap_.insert(v).first;
      void *&hnd_val = it->second;
      if(!hnd_val){
         map_[&it->first] = it;
         hnd_val = open_or_create_mutex(id);
         if(popen_created) *popen_created = true;
      }
      else if(popen_created){
         *popen_created = false;
      }
      return hnd_val;
   }

   void *obtain_semaphore(const sync_id &id, unsigned int initial_count, bool *popen_created = 0)
   {
      umap_type::value_type v(id, (void*)0);
      scoped_lock<spin_mutex> lock(mtx_);
      umap_type::iterator it = umap_.insert(v).first;
      void *&hnd_val = it->second;
      if(!hnd_val){
         map_[&it->first] = it;
         hnd_val = open_or_create_semaphore(id, initial_count);
         if(popen_created) *popen_created = true;
      }
      else if(popen_created){
         *popen_created = false;
      }
      return hnd_val;
   }

   void destroy_handle(const sync_id &id)
   {
      scoped_lock<spin_mutex> lock(mtx_);
      umap_type::iterator it = umap_.find(id);
      umap_type::iterator itend = umap_.end();

      if(it != itend){
         winapi::close_handle(it->second);
         const map_type::key_type &k = &it->first;
         map_.erase(k);
         umap_.erase(it);
      }
   }

   void destroy_syncs_in_range(const void *addr, std::size_t size)
   {
      const sync_id low_id(addr);
      const sync_id hig_id(static_cast<const char*>(addr)+size);
      scoped_lock<spin_mutex> lock(mtx_);
      map_type::iterator itlow(map_.lower_bound(&low_id)),
                         ithig(map_.lower_bound(&hig_id));
      while(itlow != ithig){
         void * const hnd = umap_[*itlow->first];
         winapi::close_handle(hnd);
         umap_.erase(*itlow->first);
         itlow = map_.erase(itlow);
      }
   }

   private:
   spin_mutex mtx_;
   umap_type umap_;
   map_type map_;
};


}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_SYNC_UTILS_HPP

/* sync_utils.hpp
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
*/