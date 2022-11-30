//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2009-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_BASIC_GLOBAL_MEMORY_HPP
#define BOOST_INTERPROCESS_BASIC_GLOBAL_MEMORY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/sync/spin/mutex.hpp>
#include <boost/interprocess/sync/spin/recursive_mutex.hpp>
#include <boost/interprocess/detail/managed_memory_impl.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/mem_algo/rbtree_best_fit.hpp>
#include <boost/interprocess/indexes/iset_index.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/permissions.hpp>

namespace boost{
namespace interprocess{
namespace ipcdetail{

struct intermodule_singleton_mutex_family
{
   typedef boost::interprocess::ipcdetail::spin_mutex              mutex_type;
   typedef boost::interprocess::ipcdetail::spin_recursive_mutex    recursive_mutex_type;
};

struct intermodule_types
{
   //We must use offset_ptr since a loaded DLL can map the singleton holder shared memory
   //at a different address than other DLLs or the main executable
   typedef rbtree_best_fit<intermodule_singleton_mutex_family, offset_ptr<void> > mem_algo;
   template<class Device, bool FileBased>
   struct open_or_create
   {
      typedef managed_open_or_create_impl
            <Device, mem_algo::Alignment, FileBased, false> type;
   };
};

//we must implement our own managed shared memory to avoid circular dependencies
template<class Device, bool FileBased>
class basic_managed_global_memory
   : public basic_managed_memory_impl
      < char
      , intermodule_types::mem_algo
      , iset_index
      , intermodule_types::open_or_create<Device, FileBased>::type::ManagedOpenOrCreateUserOffset
      >
   , private intermodule_types::open_or_create<Device, FileBased>::type
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef typename intermodule_types::template open_or_create<Device, FileBased>::type base2_t;

   typedef basic_managed_memory_impl
      < char
      , intermodule_types::mem_algo
      , iset_index
      , base2_t::ManagedOpenOrCreateUserOffset
      > base_t;

   typedef create_open_func<base_t>        create_open_func_t;

   basic_managed_global_memory *get_this_pointer()
   {  return this;   }

   public:
   typedef typename base_t::size_type              size_type;

   private:
   typedef typename base_t::char_ptr_holder_t   char_ptr_holder_t;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(basic_managed_global_memory)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public: //functions

   basic_managed_global_memory (open_or_create_t,
                              const char *name, size_type size,
                              const void *addr = 0, const permissions& perm = permissions())
      : base_t()
      , base2_t(open_or_create_t(), name, size, read_write, addr,
                create_open_func_t(get_this_pointer(),
                DoOpenOrCreate), perm)
   {}

   basic_managed_global_memory (open_only_t , const char* name,
                                const void *addr = 0)
      : base_t()
      , base2_t(open_only_t(), name, read_write, addr,
                create_open_func_t(get_this_pointer(),
                DoOpen))
   {}
};


}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_BASIC_GLOBAL_MEMORY_HPP

/* managed_global_memory.hpp
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
*/