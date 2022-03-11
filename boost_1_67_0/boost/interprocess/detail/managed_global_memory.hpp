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

   basic_managed_global_memory (open_or_create_t open_or_create,
                              const char *name, size_type size,
                              const void *addr = 0, const permissions& perm = permissions())
      : base_t()
      , base2_t(open_or_create, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(),
                DoOpenOrCreate), perm)
   {}

   basic_managed_global_memory (open_only_t open_only, const char* name,
                                const void *addr = 0)
      : base_t()
      , base2_t(open_only, name, read_write, addr,
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