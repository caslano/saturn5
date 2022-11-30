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
#include <boost/interprocess/detail/timed_utils.hpp>
#include <boost/move/move.hpp>
#include <boost/cstdint.hpp>

namespace boost {
namespace interprocess {
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
   typedef bool_<FileBased> file_like_t;

   static const unsigned MaxCreateOrOpenTries = BOOST_INTERPROCESS_MANAGED_OPEN_OR_CREATE_INITIALIZE_MAX_TRIES;
   static const unsigned MaxInitializeTimeSec = BOOST_INTERPROCESS_MANAGED_OPEN_OR_CREATE_INITIALIZE_TIMEOUT_SEC;

   typedef managed_open_or_create_impl_device_holder<StoreDevice, DeviceAbstraction> DevHolder;
   enum
   {
      UninitializedSegment,
      InitializingSegment,
      InitializedSegment,
      CorruptedSegment
   };

   static const std::size_t RequiredAlignment =
      MemAlignment ? MemAlignment
                   : boost::container::dtl::alignment_of< boost::container::dtl::max_align_t >::value
                   ;

   public:
   static const std::size_t ManagedOpenOrCreateUserOffset =
      ct_rounded_size<sizeof(boost::uint32_t), RequiredAlignment>::value;

   managed_open_or_create_impl()
   {}

   template <class DeviceId>
   managed_open_or_create_impl(create_only_t,
                 const DeviceId & id,
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

   template <class DeviceId>
   managed_open_or_create_impl(open_only_t,
                 const DeviceId & id,
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

   template <class DeviceId>
   managed_open_or_create_impl(open_or_create_t,
                 const DeviceId & id,
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

   template <class DeviceId, class ConstructFunc>
   managed_open_or_create_impl(create_only_t,
                 const DeviceId & id,
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

   template <class DeviceId, class ConstructFunc>
   managed_open_or_create_impl(open_only_t,
                 const DeviceId & id,
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

   template <class DeviceId, class ConstructFunc>
   managed_open_or_create_impl(open_or_create_t,
                 const DeviceId & id,
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
   template<bool dummy, class DeviceId>
   static void create_device(DeviceAbstraction &dev, const DeviceId & id, std::size_t size, const permissions &perm, false_ /*file_like*/)
   {
      DeviceAbstraction tmp(create_only, id, read_write, size, perm);
      tmp.swap(dev);
   }

   template<bool dummy, class DeviceId>
   static void create_device(DeviceAbstraction &dev, const DeviceId & id, std::size_t, const permissions &perm, true_ /*file_like*/)
   {
      DeviceAbstraction tmp(create_only, id, read_write, perm);
      tmp.swap(dev);
   }

   template <class DeviceId>
   static bool do_create_else_open(DeviceAbstraction &dev, const DeviceId & id, std::size_t size, const permissions &perm)
   {
      //This loop is very ugly, but brute force is sometimes better
      //than diplomacy. In POSIX file-based resources we can' know if we
      //effectively created the file or not (there is no ERROR_ALREADY_EXISTS equivalent),
      //so we try to create exclusively and fallback to open if already exists, with
      //some retries if opening also fails because the file does not exist
      //(there is a race, the creator just removed the file after creating it).
      //
      //We'll put a maximum retry limit just to avoid possible deadlocks, we don't
      //want to support pathological use cases.
      spin_wait swait;
      unsigned tries = 0;
      while(1){
         BOOST_TRY{
            create_device<FileBased>(dev, id, size, perm, file_like_t());
            return true;
         }
         BOOST_CATCH(interprocess_exception &ex){
            #ifndef BOOST_NO_EXCEPTIONS
            if(ex.get_error_code() != already_exists_error){
               BOOST_RETHROW
            }
            else if (++tries == MaxCreateOrOpenTries) {
               //File existing when trying to create, but non-existing when
               //trying to open, and tried MaxCreateOrOpenTries times. Something fishy
               //is happening here and we can't solve it
               throw interprocess_exception(error_info(corrupted_error));
            }
            else{
               BOOST_TRY{
                  DeviceAbstraction tmp(open_only, id, read_write);
                  dev.swap(tmp);
                  return false;
               }
               BOOST_CATCH(interprocess_exception &e){
                  if(e.get_error_code() != not_found_error){
                     BOOST_RETHROW
                  }
               }
               BOOST_CATCH(...){
                  BOOST_RETHROW
               } BOOST_CATCH_END
            }
            #endif   //#ifndef BOOST_NO_EXCEPTIONS
         }
         BOOST_CATCH(...){
            BOOST_RETHROW
         } BOOST_CATCH_END
         swait.yield();
      }
      return false;
   }

   template <class ConstructFunc>
   static void do_map_after_create
      (DeviceAbstraction &dev, mapped_region &final_region,
       std::size_t size, const void *addr, ConstructFunc construct_func)
   {
      BOOST_TRY{
         //If this throws, we are lost
         truncate_device<FileBased>(dev, static_cast<offset_t>(size), file_like_t());

         //If the following throws, we will truncate the file to 1
         mapped_region region(dev, read_write, 0, 0, addr);
         boost::uint32_t *patomic_word = 0;  //avoid gcc warning
         patomic_word = static_cast<boost::uint32_t*>(region.get_address());
         boost::uint32_t previous = atomic_cas32(patomic_word, InitializingSegment, UninitializedSegment);

         if(previous == UninitializedSegment){
            BOOST_TRY{
               construct_func( static_cast<char*>(region.get_address()) + ManagedOpenOrCreateUserOffset
                              , size - ManagedOpenOrCreateUserOffset, true);
               //All ok, just move resources to the external mapped region
               final_region.swap(region);
            }
            BOOST_CATCH(...){
               atomic_write32(patomic_word, CorruptedSegment);
               BOOST_RETHROW
            } BOOST_CATCH_END
            atomic_write32(patomic_word, InitializedSegment);
         }
         else{
            atomic_write32(patomic_word, CorruptedSegment);
            throw interprocess_exception(error_info(corrupted_error));
         }
      }
      BOOST_CATCH(...){
         BOOST_TRY{
            truncate_device<FileBased>(dev, 1u, file_like_t());
         }
         BOOST_CATCH(...){
         }
         BOOST_CATCH_END
         BOOST_RETHROW
      }
      BOOST_CATCH_END
   }

   template <class ConstructFunc>
   static void do_map_after_open
      ( DeviceAbstraction &dev, mapped_region &final_region
      , const void *addr, ConstructFunc construct_func
      , bool ronly, bool cow)
   {
      const usduration TimeoutSec(usduration_seconds(MaxInitializeTimeSec));

      if(FileBased){
         offset_t filesize = 0;
         spin_wait swait;

         //If a file device was used, the creator might be truncating the device, so wait
         //until the file size is enough to map the initial word
         ustime ustime_start = microsec_clock<ustime>::universal_time();

         while(1){
            if(!get_file_size(file_handle_from_mapping_handle(dev.get_mapping_handle()), filesize)){
               error_info err = system_error_code();
               throw interprocess_exception(err);
            }
            if (filesize != 0)
               break;
            else {
               //More than MaxZeroTruncateTimeSec seconds waiting to the creator
               //to minimally increase the size of the file: something bad has happened
               const usduration elapsed(microsec_clock<ustime>::universal_time() - ustime_start);
               if (elapsed > TimeoutSec){
                  throw interprocess_exception(error_info(corrupted_error));
               }
               swait.yield();
            }
         }
         //The creator detected an error creating the file and signalled it with size 1
         if(filesize == 1){
            throw interprocess_exception(error_info(corrupted_error));
         }
      }

      mapped_region  region(dev, ronly ? read_only : (cow ? copy_on_write : read_write), 0, 0, addr);

      boost::uint32_t *patomic_word = static_cast<boost::uint32_t*>(region.get_address());
      boost::uint32_t value = atomic_read32(patomic_word);

      if (value != InitializedSegment){
         ustime ustime_start = microsec_clock<ustime>::universal_time();
         spin_wait swait;
         while ((value = atomic_read32(patomic_word)) != InitializedSegment){
            if(value == CorruptedSegment){
               throw interprocess_exception(error_info(corrupted_error));
            }
            //More than MaxZeroTruncateTimeSec seconds waiting to the creator
            //to minimally increase the size of the file: something bad has happened
            const usduration elapsed(microsec_clock<ustime>::universal_time() - ustime_start);
            if (elapsed > TimeoutSec){
               throw interprocess_exception(error_info(corrupted_error));
            }
            swait.yield();
         }
         //The size of the file might have grown while Uninitialized -> Initializing, so remap
         {
            mapped_region null_map;
            region.swap(null_map);
         }
         mapped_region  final_size_map(dev, ronly ? read_only : (cow ? copy_on_write : read_write), 0, 0, addr);
         final_size_map.swap(region);
      }
      construct_func( static_cast<char*>(region.get_address()) + ManagedOpenOrCreateUserOffset
                     , region.get_size() - ManagedOpenOrCreateUserOffset
                     , false);
      //All ok, just move resources to the external mapped region
      final_region.swap(region);
   }

   template <class DeviceId, class ConstructFunc> inline
   void priv_open_or_create
      (create_enum_t type,
       const DeviceId & id,
       std::size_t size,
       mode_t mode, const void *addr,
       const permissions &perm,
       ConstructFunc construct_func)
   {
      if(type != DoOpen){
         //Check if the requested size is enough to build the managed metadata
         const std::size_t func_min_size = construct_func.get_min_size();
         if( (std::size_t(-1) - ManagedOpenOrCreateUserOffset) < func_min_size ||
             size < (func_min_size + ManagedOpenOrCreateUserOffset) ){
            throw interprocess_exception(error_info(size_error));
         }
         //Check size can be represented by offset_t (used by truncate)
         if (!check_offset_t_size<FileBased>(size, file_like_t())){
           throw interprocess_exception(error_info(size_error));
         }
      }

      //Now create the device (file, shm file, etc.)
      DeviceAbstraction dev;
      (void)mode;
      bool created = false;
      bool ronly   = false;
      bool cow     = false;
      if(type == DoOpen){
         DeviceAbstraction tmp(open_only, id, mode == read_write ? read_write : read_only);
         tmp.swap(dev);
         ronly = mode == read_only;
         cow = mode == copy_on_write;
      }
      else if(type == DoCreate){
         create_device<FileBased>(dev, id, size, perm, file_like_t());
         created = true;
      }
      else { //DoOpenOrCreate
         created = this->do_create_else_open(dev, id, size, perm);
      }

      if(created){
         this->do_map_after_create(dev, m_mapped_region, size, addr, construct_func);
      }
      else{
         this->do_map_after_open(dev, m_mapped_region, addr, construct_func, ronly, cow);
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