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
JblJvrEOvFdz1sRyX1XjOQR3FE7HR++7B7xKcFFO+rH36HnpA/fE56bfcA/k8Pt+4ItwUY768/g79XMR/qx8oJ6vHvg5k7O+9nOx/Fp78XwE7gTcObgxayEHZ+XdWrs2ltP+8FqT117l4cpcB93x3VhgAE7ltq/F8zY4K8d9A77bBDwOtHLdn14Xy3d/Tvi71853H8B3Y4FnnoQ8/g7BBfDcADwNuePAKA9+zvpYzq8x600+/DnrTU78Ovy9C07Hjf80vlf58c+vt/OEjUVZsvLkT4L8mA3QDQ6c+ZIvv26DySO2a4PJJRY8Gsud37whwp9/BngO3yffZ/LoF9yn59Ivuc/k099/tHVO/W2QPwEXQrhngCo/WeZGpEeECyTHvsFXFhC/zYa/je3Hs9+0sXWu/Xc2ts61X/h5k+tsOv5Oewp+gPvhcj4OWaAT/37L5zt54uBP2RTh4S8ApsyBDYBRPv5NCid/o3gGngDquPlz7ke8wELgcXw3G1gL984cxAm08vU34jty9sv7NE7eb3L3n8ffTRPNOzbyN0e42CYBVT7/GjyrnP6H8RxAu7kWbj/cMbjTcKlfBrc/3HS4hXCb4I7AvQ53Di5zP9pbuIVwG+Aa4I7DnYZLOYB6B1cENw9uLdx+uCa4FjjfI+DcgyuCmwe3Gm4v3BG41+GSD8I/3HS4INw2uKfhWuBSGsAnCFcCVwNXD3esoYM/ruPT8en4/Hc/yXBLLzj/X3lNzfJF8yUFYDtwAPbHC2emyb83fvbsWVMn3DS7mCx6kkPveG8fuTzk2qb8LOM77VLxt9gzuluu41oCqcDBsBqu43JtluevtXu9dlvvMC+vWV6zKuiw1k559VyuXDbWnltQZU8Z99Kb5y7y5O/lCBcnDyg3RcohTIVLaayUG+8rgMXkeS++P/5I7um/WeFO4D5+yoyGzPPyPFqhz3oeLZsy8yDzgpDp7k9NSlU59mL3+y/PwDog5F6CezCjdU6lnrjnfoFMt09ecp+hnhVmfnC/Ab+j3Y1zLzwXTPuq+8A3Jdl5KO4UexB05UG5c+GUM98X/CbOlXFKc+dCYbI9jWfwX5MujdwxyzQ67eWGX09cGR+xpNF250JDsp4ro0WXRo93LozNcuZ+zOxs58tYLvbV6uL1dueCTIMa15gu9jNkq0TbwfMfPENmxsey8innMwPw6/4cWdoe9+fI0vYkfo7sUwmcs4vaKFfDtf9phFe4Rz1zoNqo9bJauMf9uYPCPYmfOzjV6tmRyF6glBT7XqBPij2Le6J7gcaXzhhZNntuSXHMPu79ua3sVWTa2XY770+TsonvT0M6bPuAEB/3p5n7gI52cto/cuH3B+n39XjfH+R1H1DyUvH9wa6Pf2ztz576WtkjT3zqpW9e/6H//31AXvf76Pf1/Pf27+j3i8Xf18MjLnLcEpL3y0fGOWHuV3lB+VveuxodZ3F8GLbcuzqY950OA2YBrwX2AV4OHAxEEuX+kyuARVw3/RjXTW+i/M1cPy3neukdXEddyt+NeWemI0O3H0KRa4ojd4kpx35Yv54/QJELU65n3PDYvwD7tiJXSLnsuHJsz9iWhixyyLc6MUUy6dEkV3e5tuVeiLbczWq/l7V97mTdVdJ+d7Emcg9r/PtX3d296nzn6oW9b/VkEcIrSuyO1ci8r/e7VSNzvYnfqeplLvf1Ce7uu3B7l6qbe1QXoh5ugmuEOwF3Fi7nENak4AKHOuYyOz4dn45Px6fj0/Hp+HR8Oj4dn45Px6fj0/H5X/58MPf/lVe3x/1/Yl3/p8rdeKf9POtkztX6jolz9JvkmsyM4tmlE8djPaa0ZNrUshWLbl/Kdadn8+Q6rsE=
*/