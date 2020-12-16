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
arZwvFgCdlbIJnFcP6cYx/XzivlxPVtzE1c6f1yzVjWlY4rLvEbri6EPKhTWiS8pJl8J6Dkn7qFXAq3nj3ro2UfPhC/7HjUDED4eUl05z/ManfLjK1IP9u46P8KwetKYvOTQK4Z3ErCvKcbvmwsUg3cKsAsVg4oNeXKRYvqdcXHU45/hcUnUA/ED/vUIp/cGrtePcv+c98viHnrAoOfyqMffC/6KuIfX7Ee5K0jwXCU9euM7PL876uF1/Vd35tlXEvBcE/XQ2n+qs9fGPXzaZN38L/UTr5vIK77NXK99pg+AcbpBszSsDzdGPVwfbopyrg/fjPCwPnwr4gnrw80RT1gfvh31cH24JcLD+vCdiCesD9+Nerg+fK8j5/pwa8QT1ofbop54fbg97uX6QL7v+75KmprRVq/bQed6S5/4/XJnqBfMW0nsN/EDyV220Z4CUcZnsd0lOU7IQVeK1/9IcddZBH635tRRxDz/scdT2D8n3EvmHunxu5A47h9w+e79qWL87r3XZ+rde5/i/O69X7H4u/eB0AcfLPD+D0YZ/FSB8n5IcrEn3MOhjuWF+6NLJr6pPiJ1uA+G9ajU3axeZD+XzDUD2ic9wmRf8zHJVfPAPHx8Ao/cc/yX1pdPilXxfekJqfex/1dWd6M/dPa31b3RG2S/IUa/RMfk2uEnBaOBX9CfknqZx7uednqSFuDErZGSfd8/E2HQi8xOepmE+fLsRB7cKx/u81vlK41b9lzA4NgWYs9HmPkH2AsRNpWue1ExU1OJvRSypDRi2cshG+N4vhKyOl/3O8VGHXtVMHcoKtXN1xSjA1Pp2t+HfAn/Fn3dY/t1QdkRe0MxTsebinF+/0Exzu8/Ksb5/ZZinN9/CpjM77cDJvP7nYDJ/P6zYpzf7wZM5vdfAhbm93uSm/or28P7iun28IHyxNvDX5WP0/03xbh8/q4Yl88/FOPy+adiXD7/Cpgsn38HTJbPfwImy+dDxbh8llvVZ7J8lg9YWD4rhHwJn52yomUjo1m2w3NvJdbwBCDyrsx6llzQVmEtiy5cv6rTqmZ7iq6RKZO6QF/N11MTFYj/6lYv0RlN/FAFvkaMQyFiHVszyqmQKYy1OnmmIl87zltNO74d5SYXiK8b5fVRy9dTnB4+xNePck7jBh05p3HDqIfTuFGUcxo3jnJO4yZRzmncVHFqzMQ3i3JO4+YdOadxi6iH07hllHMat4pyTuPWMY5phDq8DfO0NQUSB21sW0+nZkPXfMRn5maob+fp5iakb+/0hUXzX9deFLcdQr3QqFeXTpq81xS8bkfLy0mKMUN9J6FDdpK+s9AxxqjvEuhTyf9RoUMqSP+Yp5cTq+8a6Pbsst1CHSKLbPeQQYSR7REyjDSwPWNsKl738ZBB5JHtpVh91LJJIYMHK7KugMl+xOSAYTSR7R0w+d6YErL6qMvjfQST+r5CXwKRQH0q6bCpWq1dtWPd+5EuJoiPLIVFmsj3F5z6vMgpjgdI3jjB/OKrj9uz6g60rFJOiiIuB0kdMwP0T0gdMwL0g6UOicX3zyFWHy+b3EStm7UpNk+mCQ26GaT3sI5ZQmH0sl7qIm/Oas1SV2Hvvdy7cbrU99nb6TOELtveTKHLNtYndNmWDhU6JJ3iOIt1l/bZQjNxhPKZIzToQ2HGAOt3LCmWTeHRQhUo94E4K4xXahCvQccrjWS8nJ0EBvphpOP2utyOh6TunuF4TV4yUe7DUhftcK7TZZ3DPJhHDMsZtcOFZo4lA20+adSlBG2B0CZPRd8RQrP9liOtdsLCSrPaqNdpnvpRoM8fzvX35nphB7+5+e4ZOW+vzqM7eOyYyjFxnn3lgfgUMj69bzA=
*/