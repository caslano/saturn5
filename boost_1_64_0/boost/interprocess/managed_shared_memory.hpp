//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MANAGED_SHARED_MEMORY_HPP
#define BOOST_INTERPROCESS_MANAGED_SHARED_MEMORY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/detail/managed_memory_impl.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/permissions.hpp>
//These includes needed to fulfill default template parameters of
//predeclarations in interprocess_fwd.hpp
#include <boost/interprocess/mem_algo/rbtree_best_fit.hpp>
#include <boost/interprocess/sync/mutex_family.hpp>

namespace boost {
namespace interprocess {

namespace ipcdetail {

template<class AllocationAlgorithm>
struct shmem_open_or_create
{
   typedef  ipcdetail::managed_open_or_create_impl
      < shared_memory_object, AllocationAlgorithm::Alignment, true, false> type;
};

}  //namespace ipcdetail {

//!A basic shared memory named object creation class. Initializes the
//!shared memory segment. Inherits all basic functionality from
//!basic_managed_memory_impl<CharType, AllocationAlgorithm, IndexType>*/
template
      <
         class CharType,
         class AllocationAlgorithm,
         template<class IndexConfig> class IndexType
      >
class basic_managed_shared_memory
   : public ipcdetail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType
      ,ipcdetail::shmem_open_or_create<AllocationAlgorithm>::type::ManagedOpenOrCreateUserOffset>
   , private ipcdetail::shmem_open_or_create<AllocationAlgorithm>::type
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef ipcdetail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType,
      ipcdetail::shmem_open_or_create<AllocationAlgorithm>::type::ManagedOpenOrCreateUserOffset>   base_t;
   typedef typename ipcdetail::shmem_open_or_create<AllocationAlgorithm>::type                     base2_t;

   typedef ipcdetail::create_open_func<base_t>        create_open_func_t;

   basic_managed_shared_memory *get_this_pointer()
   {  return this;   }

   public:
   typedef shared_memory_object                    device_type;
   typedef typename base_t::size_type              size_type;

   private:
   typedef typename base_t::char_ptr_holder_t   char_ptr_holder_t;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(basic_managed_shared_memory)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public: //functions

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~basic_managed_shared_memory()
   {}

   //!Default constructor. Does nothing.
   //!Useful in combination with move semantics
   basic_managed_shared_memory()
   {}

   //!Creates shared memory and creates and places the segment manager.
   //!This can throw.
   basic_managed_shared_memory(create_only_t, const char *name,
                             size_type size, const void *addr = 0, const permissions& perm = permissions())
      : base_t()
      , base2_t(create_only, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(), ipcdetail::DoCreate), perm)
   {}

   //!Creates shared memory and creates and places the segment manager if
   //!segment was not created. If segment was created it connects to the
   //!segment.
   //!This can throw.
   basic_managed_shared_memory (open_or_create_t,
                              const char *name, size_type size,
                              const void *addr = 0, const permissions& perm = permissions())
      : base_t()
      , base2_t(open_or_create, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpenOrCreate), perm)
   {}

   //!Connects to a created shared memory and its segment manager.
   //!in copy_on_write mode.
   //!This can throw.
   basic_managed_shared_memory (open_copy_on_write_t, const char* name,
                                const void *addr = 0)
      : base_t()
      , base2_t(open_only, name, copy_on_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Connects to a created shared memory and its segment manager.
   //!in read-only mode.
   //!This can throw.
   basic_managed_shared_memory (open_read_only_t, const char* name,
                                const void *addr = 0)
      : base_t()
      , base2_t(open_only, name, read_only, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Connects to a created shared memory and its segment manager.
   //!This can throw.
   basic_managed_shared_memory (open_only_t, const char* name,
                                const void *addr = 0)
      : base_t()
      , base2_t(open_only, name, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   basic_managed_shared_memory(BOOST_RV_REF(basic_managed_shared_memory) moved)
   {
      basic_managed_shared_memory tmp;
      this->swap(moved);
      tmp.swap(moved);
   }

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   basic_managed_shared_memory &operator=(BOOST_RV_REF(basic_managed_shared_memory) moved)
   {
      basic_managed_shared_memory tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Swaps the ownership of the managed shared memories managed by *this and other.
   //!Never throws.
   void swap(basic_managed_shared_memory &other)
   {
      base_t::swap(other);
      base2_t::swap(other);
   }

   //!Tries to resize the managed shared memory object so that we have
   //!room for more objects.
   //!
   //!This function is not synchronized so no other thread or process should
   //!be reading or writing the file
   static bool grow(const char *shmname, size_type extra_bytes)
   {
      return base_t::template grow
         <basic_managed_shared_memory>(shmname, extra_bytes);
   }

   //!Tries to resize the managed shared memory to minimized the size of the file.
   //!
   //!This function is not synchronized so no other thread or process should
   //!be reading or writing the file
   static bool shrink_to_fit(const char *shmname)
   {
      return base_t::template shrink_to_fit
         <basic_managed_shared_memory>(shmname);
   }
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Tries to find a previous named allocation address. Returns a memory
   //!buffer and the object count. If not found returned pointer is 0.
   //!Never throws.
   template <class T>
   std::pair<T*, size_type> find  (char_ptr_holder_t name)
   {
      if(base2_t::get_mapped_region().get_mode() == read_only){
         return base_t::template find_no_lock<T>(name);
      }
      else{
         return base_t::template find<T>(name);
      }
   }

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Typedef for a default basic_managed_shared_memory
//!of narrow characters
typedef basic_managed_shared_memory
   <char
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
managed_shared_memory;

//!Typedef for a default basic_managed_shared_memory
//!of wide characters
typedef basic_managed_shared_memory
   <wchar_t
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
wmanaged_shared_memory;

//!Typedef for a default basic_managed_shared_memory
//!of narrow characters to be placed in a fixed address
typedef basic_managed_shared_memory
   <char
   ,rbtree_best_fit<mutex_family, void*>
   ,iset_index>
fixed_managed_shared_memory;

//!Typedef for a default basic_managed_shared_memory
//!of narrow characters to be placed in a fixed address
typedef basic_managed_shared_memory
   <wchar_t
   ,rbtree_best_fit<mutex_family, void*>
   ,iset_index>
wfixed_managed_shared_memory;


#endif   //#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_MANAGED_SHARED_MEMORY_HPP


/* managed_shared_memory.hpp
zkJ3Dyz/CF6ednHYPOsXJkLN7HkM7hxVR7dUJyuyXA5mdfuuvr2Hurq3uhgPPY313nUoSuENv+WFTaRyULNcR3MRzfLd0baJHcnxh0Q9OORTFCmJy7lDApFof99jlM9h1WyVyUWIIRPXS/lozQ5ARJgPOfja48Jo7zuzjRkh8wXrYYdEF52477J5pvlKkCf1HTHaAW4Jbx+A1pJzpDNFiyG6CPNq3FdKM+BGEKYd0IkFg1Ajv00iIGadkM3ZUIhhfiHJu7gJmZU9XWBFAY0mE5KximS8ax/hfCs+jjiJa7AYp1HMKUEI8Nl1aVbsYMR3gGKaFgnoMe7P0fKCb1BHesAqPSGiF/P9KwgAYfrJLm9fuYMXoYx6hMQUhUDhK/bmxo69CDOlmwbggfnV5npek5uQ5CYEua1AxRHDeGE0XnaPswQIM4UMs924obmKYKmhmFr6EY+Y79glpIshz/x4apPe6Am7fw1p3k1fzvxNgTnk8hQ4LosJK+/hRFHpbDwswUCx1+3d0QJ3NFMpCFynW29CmevEbupeqmsKaHBG/p55kgrKC0fAXKAghPsmQYDsrN3IPJnGq9QR3LnRTa7JsWCEpamjm5djPM8UNMuzvG1t+e5Cgpi8QkJ2brS9edMOuTb68MysqJJEPADXBjfP5aVommnT0DHVWbvJzROEHawEYb0uCJYQEXGTARSaDbSt6WDlzSd4Iae4GTNeSyFwSmX8zyYlTtqsQGnTAh3dvEQoFt9Wj7ZabLdqUcwg55T1m5gDSMEkQAtmARqZhvgs60IwCqG8RUTQXXMsrpzgXv4YTDPILUMYpYyBs3zbDEIiiDUIfYWUluLaOcsDBeGW7Ee4uZzFErbLGhTbyOAsY2MVnvQmkULYQwphDAUIjd4sgDGdmPL38/D97ISDFeVIMWrJxICLZgbeZmqJO8oZpcxazS7zSBmrWM7/NkHvlEpYUT/OSnOsTbqjrfUojycxytVrVVUmSs7g7vluf8jhNTOgOFKb7We+MWcVxUz6Qe4eBc77Q+YgBY77hbnaiDx3r7uzdu1mn9tiHHtdx26FC5DxmVg6+oacg/tt8BQkXQqFaZnYslLshyT72cM789KAw5biWQkSyO7LsKVzBWaCrcw79vQVysxmy6jM4mdU5jQZui8YpqlFB4LZ17p4CaqVoQuclmrBKdfJbv109wfl3Jj4liQz24VFRq4C+xmLA9Mnc1YO560WNj9N32GTaotu2WGlFsCRVNAodsh+1ehuYxu3lcd6rp3Hgi9kYmsBab74DUYtBG1UGtOiYmsTlvIPbWnJOLIIzJodvJ4naZeEbswhpQmMAyyqk8VZC4mmw9Dg0EvFyUOEcwzizDjCp6yxmlrS0o5BhRrp0XwKofAEivRM/Vh5DdjN9KVgAUFwykupljRFdxdcHkjxMTq9PCvMbgIhfoyyVe6JPXpxWDl2L0JtQy6mAUBFisWD5wIAFkWw+9uSbeeG17n2sSZ42cjbXTZzdkBm6d65Lq4yRzo7111zOVG3pgIJyXUyCWLf1RcUMKFwQaODycyDd+zvh3nfebUgKajNOWIwCVjb3d1uzuGwpRC6KRebXfsWAl5r8zruUDxCshhYiAWYjHBLoaQRiEQRkKRaPvbGE7wmZQ6TOgPjHG7KYeSNzHZQgpE2QSShu9ONawHtvW72sfE2dlNAK3PYmk6KZHxn16PjT2hz9MA2eMYh/wwrZuxt4/JNO2+Ys+wYGSYxyCcEtkXCDBYRdc4j4xxsyR0xSyibVQGcNm7OiIssNTNd2gzjw70me05imq8zC/uYZcftD8PhbK/PcZDNIJ1z9SG59brTjLOY29h+yBzuc8wboYziQrGK5nU=
*/