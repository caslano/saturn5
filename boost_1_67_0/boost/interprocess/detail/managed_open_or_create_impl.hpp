//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MANAGED_OPEN_OR_CREATE_IMPL
#define BOOST_INTERPROCESS_MANAGED_OPEN_OR_CREATE_IMPL

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/os_thread_functions.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/interprocess/detail/interprocess_tester.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/detail/mpl.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/container/detail/type_traits.hpp>  //alignment_of, aligned_storage
#include <boost/interprocess/sync/spin/wait.hpp>
#include <boost/move/move.hpp>
#include <boost/cstdint.hpp>

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
namespace ipcdetail{ class interprocess_tester; }


template<class DeviceAbstraction>
struct managed_open_or_create_impl_device_id_t
{
   typedef const char *type;
};

#ifdef BOOST_INTERPROCESS_XSI_SHARED_MEMORY_OBJECTS

class xsi_shared_memory_file_wrapper;
class xsi_key;

template<>
struct managed_open_or_create_impl_device_id_t<xsi_shared_memory_file_wrapper>
{
   typedef xsi_key type;
};

#endif   //BOOST_INTERPROCESS_XSI_SHARED_MEMORY_OBJECTS

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

namespace ipcdetail {


template <bool StoreDevice, class DeviceAbstraction>
class managed_open_or_create_impl_device_holder
{
   public:
   DeviceAbstraction &get_device()
   {  static DeviceAbstraction dev; return dev; }

   const DeviceAbstraction &get_device() const
   {  static DeviceAbstraction dev; return dev; }
};

template <class DeviceAbstraction>
class managed_open_or_create_impl_device_holder<true, DeviceAbstraction>
{
   public:
   DeviceAbstraction &get_device()
   {  return dev; }

   const DeviceAbstraction &get_device() const
   {  return dev; }

   private:
   DeviceAbstraction dev;
};

template<class DeviceAbstraction, std::size_t MemAlignment, bool FileBased, bool StoreDevice>
class managed_open_or_create_impl
   : public managed_open_or_create_impl_device_holder<StoreDevice, DeviceAbstraction>
{
   //Non-copyable
   BOOST_MOVABLE_BUT_NOT_COPYABLE(managed_open_or_create_impl)

   typedef typename managed_open_or_create_impl_device_id_t<DeviceAbstraction>::type device_id_t;
   typedef managed_open_or_create_impl_device_holder<StoreDevice, DeviceAbstraction> DevHolder;
   enum
   {
      UninitializedSegment,
      InitializingSegment,
      InitializedSegment,
      CorruptedSegment
   };

   public:
   static const std::size_t
      ManagedOpenOrCreateUserOffset =
         ct_rounded_size
            < sizeof(boost::uint32_t)
            , MemAlignment ? (MemAlignment) :
               (::boost::container::dtl::alignment_of
                  < ::boost::container::dtl::max_align_t >::value)
            >::value;

   managed_open_or_create_impl()
   {}

   managed_open_or_create_impl(create_only_t,
                 const device_id_t & id,
                 std::size_t size,
                 mode_t mode,
                 const void *addr,
                 const permissions &perm)
   {
      priv_open_or_create
         ( DoCreate
         , id
         , size
         , mode
         , addr
         , perm
         , null_mapped_region_function());
   }

   managed_open_or_create_impl(open_only_t,
                 const device_id_t & id,
                 mode_t mode,
                 const void *addr)
   {
      priv_open_or_create
         ( DoOpen
         , id
         , 0
         , mode
         , addr
         , permissions()
         , null_mapped_region_function());
   }


   managed_open_or_create_impl(open_or_create_t,
                 const device_id_t & id,
                 std::size_t size,
                 mode_t mode,
                 const void *addr,
                 const permissions &perm)
   {
      priv_open_or_create
         ( DoOpenOrCreate
         , id
         , size
         , mode
         , addr
         , perm
         , null_mapped_region_function());
   }

   template <class ConstructFunc>
   managed_open_or_create_impl(create_only_t,
                 const device_id_t & id,
                 std::size_t size,
                 mode_t mode,
                 const void *addr,
                 const ConstructFunc &construct_func,
                 const permissions &perm)
   {
      priv_open_or_create
         (DoCreate
         , id
         , size
         , mode
         , addr
         , perm
         , construct_func);
   }

   template <class ConstructFunc>
   managed_open_or_create_impl(open_only_t,
                 const device_id_t & id,
                 mode_t mode,
                 const void *addr,
                 const ConstructFunc &construct_func)
   {
      priv_open_or_create
         ( DoOpen
         , id
         , 0
         , mode
         , addr
         , permissions()
         , construct_func);
   }

   template <class ConstructFunc>
   managed_open_or_create_impl(open_or_create_t,
                 const device_id_t & id,
                 std::size_t size,
                 mode_t mode,
                 const void *addr,
                 const ConstructFunc &construct_func,
                 const permissions &perm)
   {
      priv_open_or_create
         ( DoOpenOrCreate
         , id
         , size
         , mode
         , addr
         , perm
         , construct_func);
   }

   managed_open_or_create_impl(BOOST_RV_REF(managed_open_or_create_impl) moved)
   {  this->swap(moved);   }

   managed_open_or_create_impl &operator=(BOOST_RV_REF(managed_open_or_create_impl) moved)
   {
      managed_open_or_create_impl tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   ~managed_open_or_create_impl()
   {}

   std::size_t get_user_size()  const
   {  return m_mapped_region.get_size() - ManagedOpenOrCreateUserOffset; }

   void *get_user_address()  const
   {  return static_cast<char*>(m_mapped_region.get_address()) + ManagedOpenOrCreateUserOffset;  }

   std::size_t get_real_size()  const
   {  return m_mapped_region.get_size(); }

   void *get_real_address()  const
   {  return m_mapped_region.get_address();  }

   void swap(managed_open_or_create_impl &other)
   {
      this->m_mapped_region.swap(other.m_mapped_region);
   }

   bool flush()
   {  return m_mapped_region.flush();  }

   const mapped_region &get_mapped_region() const
   {  return m_mapped_region;  }


   DeviceAbstraction &get_device()
   {  return this->DevHolder::get_device(); }

   const DeviceAbstraction &get_device() const
   {  return this->DevHolder::get_device(); }

   private:

   //These are templatized to allow explicit instantiations
   template<bool dummy>
   static void truncate_device(DeviceAbstraction &, offset_t, false_)
   {} //Empty

   template<bool dummy>
   static void truncate_device(DeviceAbstraction &dev, offset_t size, true_)
   {  dev.truncate(size);  }


   template<bool dummy>
   static bool check_offset_t_size(std::size_t , false_)
   { return true; } //Empty

   template<bool dummy>
   static bool check_offset_t_size(std::size_t size, true_)
   { return size == std::size_t(offset_t(size)); }

   //These are templatized to allow explicit instantiations
   template<bool dummy>
   static void create_device(DeviceAbstraction &dev, const device_id_t & id, std::size_t size, const permissions &perm, false_ file_like)
   {
      (void)file_like;
      DeviceAbstraction tmp(create_only, id, read_write, size, perm);
      tmp.swap(dev);
   }

   template<bool dummy>
   static void create_device(DeviceAbstraction &dev, const device_id_t & id, std::size_t, const permissions &perm, true_ file_like)
   {
      (void)file_like;
      DeviceAbstraction tmp(create_only, id, read_write, perm);
      tmp.swap(dev);
   }

   template <class ConstructFunc> inline
   void priv_open_or_create
      (create_enum_t type,
       const device_id_t & id,
       std::size_t size,
       mode_t mode, const void *addr,
       const permissions &perm,
       ConstructFunc construct_func)
   {
      typedef bool_<FileBased> file_like_t;
      (void)mode;
      bool created = false;
      bool ronly   = false;
      bool cow     = false;
      DeviceAbstraction dev;

      if(type != DoOpen){
         //Check if the requested size is enough to build the managed metadata
         const std::size_t func_min_size = construct_func.get_min_size();
         if( (std::size_t(-1) - ManagedOpenOrCreateUserOffset) < func_min_size ||
             size < (func_min_size + ManagedOpenOrCreateUserOffset) ){
            throw interprocess_exception(error_info(size_error));
         }
      }
      //Check size can be represented by offset_t (used by truncate)
      if(type != DoOpen && !check_offset_t_size<FileBased>(size, file_like_t())){
         throw interprocess_exception(error_info(size_error));
      }
      if(type == DoOpen && mode == read_write){
         DeviceAbstraction tmp(open_only, id, read_write);
         tmp.swap(dev);
         created = false;
      }
      else if(type == DoOpen && mode == read_only){
         DeviceAbstraction tmp(open_only, id, read_only);
         tmp.swap(dev);
         created = false;
         ronly   = true;
      }
      else if(type == DoOpen && mode == copy_on_write){
         DeviceAbstraction tmp(open_only, id, read_only);
         tmp.swap(dev);
         created = false;
         cow     = true;
      }
      else if(type == DoCreate){
         create_device<FileBased>(dev, id, size, perm, file_like_t());
         created = true;
      }
      else if(type == DoOpenOrCreate){
         //This loop is very ugly, but brute force is sometimes better
         //than diplomacy. If someone knows how to open or create a
         //file and know if we have really created it or just open it
         //drop me a e-mail!
         bool completed = false;
         spin_wait swait;
         while(!completed){
            try{
               create_device<FileBased>(dev, id, size, perm, file_like_t());
               created     = true;
               completed   = true;
            }
            catch(interprocess_exception &ex){
               if(ex.get_error_code() != already_exists_error){
                  throw;
               }
               else{
                  try{
                     DeviceAbstraction tmp(open_only, id, read_write);
                     dev.swap(tmp);
                     created     = false;
                     completed   = true;
                  }
                  catch(interprocess_exception &e){
                     if(e.get_error_code() != not_found_error){
                        throw;
                     }
                  }
                  catch(...){
                     throw;
                  }
               }
            }
            catch(...){
               throw;
            }
            swait.yield();
         }
      }

      if(created){
         try{
            //If this throws, we are lost
            truncate_device<FileBased>(dev, size, file_like_t());

            //If the following throws, we will truncate the file to 1
            mapped_region        region(dev, read_write, 0, 0, addr);
            boost::uint32_t *patomic_word = 0;  //avoid gcc warning
            patomic_word = static_cast<boost::uint32_t*>(region.get_address());
            boost::uint32_t previous = atomic_cas32(patomic_word, InitializingSegment, UninitializedSegment);

            if(previous == UninitializedSegment){
               try{
                  construct_func( static_cast<char*>(region.get_address()) + ManagedOpenOrCreateUserOffset
                                , size - ManagedOpenOrCreateUserOffset, true);
                  //All ok, just move resources to the external mapped region
                  m_mapped_region.swap(region);
               }
               catch(...){
                  atomic_write32(patomic_word, CorruptedSegment);
                  throw;
               }
               atomic_write32(patomic_word, InitializedSegment);
            }
            else if(previous == InitializingSegment || previous == InitializedSegment){
               throw interprocess_exception(error_info(already_exists_error));
            }
            else{
               throw interprocess_exception(error_info(corrupted_error));
            }
         }
         catch(...){
            try{
               truncate_device<FileBased>(dev, 1u, file_like_t());
            }
            catch(...){
            }
            throw;
         }
      }
      else{
         if(FileBased){
            offset_t filesize = 0;
            spin_wait swait;
            while(filesize == 0){
               if(!get_file_size(file_handle_from_mapping_handle(dev.get_mapping_handle()), filesize)){
                  error_info err = system_error_code();
                  throw interprocess_exception(err);
               }
               swait.yield();
            }
            if(filesize == 1){
               throw interprocess_exception(error_info(corrupted_error));
            }
         }

         mapped_region  region(dev, ronly ? read_only : (cow ? copy_on_write : read_write), 0, 0, addr);

         boost::uint32_t *patomic_word = static_cast<boost::uint32_t*>(region.get_address());
         boost::uint32_t value = atomic_read32(patomic_word);

         spin_wait swait;
         while(value == InitializingSegment || value == UninitializedSegment){
            swait.yield();
            value = atomic_read32(patomic_word);
         }

         if(value != InitializedSegment)
            throw interprocess_exception(error_info(corrupted_error));

         construct_func( static_cast<char*>(region.get_address()) + ManagedOpenOrCreateUserOffset
                        , region.get_size() - ManagedOpenOrCreateUserOffset
                        , false);
         //All ok, just move resources to the external mapped region
         m_mapped_region.swap(region);
      }
      if(StoreDevice){
         this->DevHolder::get_device() = boost::move(dev);
      }
   }

   friend void swap(managed_open_or_create_impl &left, managed_open_or_create_impl &right)
   {
      left.swap(right);
   }

   private:
   friend class interprocess_tester;
   void dont_close_on_destruction()
   {  interprocess_tester::dont_close_on_destruction(m_mapped_region);  }

   mapped_region     m_mapped_region;
};

}  //namespace ipcdetail {

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_MANAGED_OPEN_OR_CREATE_IMPL

/* managed_open_or_create_impl.hpp
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
*/