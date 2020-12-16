//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MANAGED_MAPPED_FILE_HPP
#define BOOST_INTERPROCESS_MANAGED_MAPPED_FILE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/managed_open_or_create_impl.hpp>
#include <boost/interprocess/detail/managed_memory_impl.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/detail/file_wrapper.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/permissions.hpp>
//These includes needed to fulfill default template parameters of
//predeclarations in interprocess_fwd.hpp
#include <boost/interprocess/mem_algo/rbtree_best_fit.hpp>
#include <boost/interprocess/sync/mutex_family.hpp>
#include <boost/interprocess/indexes/iset_index.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

template<class AllocationAlgorithm>
struct mfile_open_or_create
{
   typedef  ipcdetail::managed_open_or_create_impl
      < file_wrapper, AllocationAlgorithm::Alignment, true, false> type;
};

}  //namespace ipcdetail {

//!A basic mapped file named object creation class. Initializes the
//!mapped file. Inherits all basic functionality from
//!basic_managed_memory_impl<CharType, AllocationAlgorithm, IndexType>
template
      <
         class CharType,
         class AllocationAlgorithm,
         template<class IndexConfig> class IndexType
      >
class basic_managed_mapped_file
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   : public ipcdetail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType
      ,ipcdetail::mfile_open_or_create<AllocationAlgorithm>::type::ManagedOpenOrCreateUserOffset>
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   public:
   typedef ipcdetail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType,
      ipcdetail::mfile_open_or_create<AllocationAlgorithm>::type::ManagedOpenOrCreateUserOffset>   base_t;
   typedef ipcdetail::file_wrapper device_type;

   private:

   typedef ipcdetail::create_open_func<base_t>        create_open_func_t;

   basic_managed_mapped_file *get_this_pointer()
   {  return this;   }

   private:
   typedef typename base_t::char_ptr_holder_t   char_ptr_holder_t;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(basic_managed_mapped_file)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public: //functions

   //!Unsigned integral type enough to represent
   //!the size of a basic_managed_mapped_file.
   typedef typename BOOST_INTERPROCESS_IMPDEF(base_t::size_type) size_type;

   //!Creates mapped file and creates and places the segment manager.
   //!This can throw.
   basic_managed_mapped_file()
   {}

   //!Creates mapped file and creates and places the segment manager.
   //!This can throw.
   basic_managed_mapped_file(create_only_t, const char *name,
                             size_type size, const void *addr = 0, const permissions &perm = permissions())
      : m_mfile(create_only, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(), ipcdetail::DoCreate), perm)
   {}

   //!Creates mapped file and creates and places the segment manager if
   //!segment was not created. If segment was created it connects to the
   //!segment.
   //!This can throw.
   basic_managed_mapped_file (open_or_create_t,
                              const char *name, size_type size,
                              const void *addr = 0, const permissions &perm = permissions())
      : m_mfile(open_or_create, name, size, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpenOrCreate), perm)
   {}

   //!Connects to a created mapped file and its segment manager.
   //!This can throw.
   basic_managed_mapped_file (open_only_t, const char* name,
                              const void *addr = 0)
      : m_mfile(open_only, name, read_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Connects to a created mapped file and its segment manager
   //!in copy_on_write mode.
   //!This can throw.
   basic_managed_mapped_file (open_copy_on_write_t, const char* name,
                              const void *addr = 0)
      : m_mfile(open_only, name, copy_on_write, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Connects to a created mapped file and its segment manager
   //!in read-only mode.
   //!This can throw.
   basic_managed_mapped_file (open_read_only_t, const char* name,
                              const void *addr = 0)
      : m_mfile(open_only, name, read_only, addr,
                create_open_func_t(get_this_pointer(),
                ipcdetail::DoOpen))
   {}

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   basic_managed_mapped_file(BOOST_RV_REF(basic_managed_mapped_file) moved)
   {
      this->swap(moved);
   }

   //!Moves the ownership of "moved"'s managed memory to *this.
   //!Does not throw
   basic_managed_mapped_file &operator=(BOOST_RV_REF(basic_managed_mapped_file) moved)
   {
      basic_managed_mapped_file tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~basic_managed_mapped_file()
   {}

   //!Swaps the ownership of the managed mapped memories managed by *this and other.
   //!Never throws.
   void swap(basic_managed_mapped_file &other)
   {
      base_t::swap(other);
      m_mfile.swap(other.m_mfile);
   }

   //!Flushes cached data to file.
   //!Never throws
   bool flush()
   {  return m_mfile.flush();  }

   //!Tries to resize mapped file so that we have room for
   //!more objects.
   //!
   //!This function is not synchronized so no other thread or process should
   //!be reading or writing the file
   static bool grow(const char *filename, size_type extra_bytes)
   {
      return base_t::template grow
         <basic_managed_mapped_file>(filename, extra_bytes);
   }

   //!Tries to resize mapped file to minimized the size of the file.
   //!
   //!This function is not synchronized so no other thread or process should
   //!be reading or writing the file
   static bool shrink_to_fit(const char *filename)
   {
      return base_t::template shrink_to_fit
         <basic_managed_mapped_file>(filename);
   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Tries to find a previous named allocation address. Returns a memory
   //!buffer and the object count. If not found returned pointer is 0.
   //!Never throws.
   template <class T>
   std::pair<T*, size_type> find  (char_ptr_holder_t name)
   {
      if(m_mfile.get_mapped_region().get_mode() == read_only){
         return base_t::template find_no_lock<T>(name);
      }
      else{
         return base_t::template find<T>(name);
      }
   }

   private:
   typename ipcdetail::mfile_open_or_create<AllocationAlgorithm>::type m_mfile;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Typedef for a default basic_managed_mapped_file
//!of narrow characters
typedef basic_managed_mapped_file
   <char
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
managed_mapped_file;

//!Typedef for a default basic_managed_mapped_file
//!of wide characters
typedef basic_managed_mapped_file
   <wchar_t
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
wmanaged_mapped_file;

#endif   //#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_MANAGED_MAPPED_FILE_HPP

/* managed_mapped_file.hpp
mQGvXHvzRjvMcugbPrSUdIWPsvGNkhssbwqx39hIoGEah9wiZLnXEgP9RQzk2doXlOfY6hZGmfOaG3djPJUkF2RKYyZxtC9nnJWj83J2bnLN3e2NRuAMpPwMQoSV6/K9D/6E3xW5bvhdEaGoGEbpaZ9aDoMaMjkKuq58cOS67oMjEuLYCsJ/faQJm/n45rU21sLLwBrAdKkYwoojICYmWQJ3F5chZIXarCIFJImAW7uXXkWBKwTIjQCvA5mvU5tr/htNpWApHjoT7NrNx7ObtClI2hSK0x43kw/YZyipMyxOXkqcJw0S8sjU8omn9CKeHCeDEkomKzc4Dgz2Da91mRX+W6sg1JhCE9jlCRzdvJkJZY2C4GVX+O/jX9bFv2wU/7ISf321+eNSELRJCLlYTSeSz7rbu+xa4M76Vs5BA3k2VDDHqP3KFsC1Ozfb3Lr0qgm7TTmo8A7ykNyfQvlbyCVoThi2kovHO0TJ7h7fSi8f35Jrvbfie72F9AUbyTd2d9bXbkSVeN6Nx+ZufBMO042XaeGhhBZOnOHOja5Pf/cZCUYGCZIl3OzQs9Fhj7EgZ9B/c0ZWEhCasU+rx4xUgs1cAOOxE0y35adZyceQ20zYOm53EyVt2GYWEhGEoPgV9nuN82dZ7wh/mOgBeybu6fiMXGCqLgSbEULJvcAO8i+QQFM684W9O2BhnqR2Q5P1nuahhd7tOyGBmzc0g+0Kv+5rHBK0+ekG6tvKsHtsc0Z+xpIE27ubh+VzBytQ9okiExyvjo1kTaVcmN/V0dgHKd2HtYGBViF9mMO1FcKm7KalDCn5EyMKk2qleQT6mms7m+vbG4RQ1TGUwUbmar/AW7IS2B3P5JxGhhRDD6aA/uqwwFuyWmB70HAEl3q1c2lH7vTlGvdyFHvAlzKHKWLMHKhxG+YR4JC2lRaALEIyTr+zu7Z7E+OoU5B0GSRpt28QFwUtJUGFBR23Rf+8cdS0KWOJh5ht1BR2JQqQN6cw0tRJQ7axaMWUlTeh8LP2E84wIkUhEJtb1zYXWEUIKSI6TMLwwGQhVGLGWTIi0Koxw13JgkSKzDhZBokqW3noMuflypQIuTaFNYzpXDkMN0Ga5Tzb6Ov2gy5HKREj1oA8ssGN2MuhPubcfj6fxgjaj4ExiXLEKlPQSGZ/DzNDx50sSg+/JldCmi6ZYCggRchOoGut7ZpbFGOIZDEQp/L9WABShCTHK/Pe7UMkzYFaNE3KoF6CWZsF+TPta+ZGCUShCUAhMRI38E2Pu/7GtXw/ytFhHlOy5N2GmzJvuMFxZnaVgiTOIEnL2w24Q3vJeYKRMkUkIXP+G2xk41yJueSluPTmnCWSCGiPjbP8k76eM7MS8lHwKDad/ii29Ps8jnT9jDvMIFFst9cbsBRlSTZl4TrQAYfJ1ZDzOe6TmOzve7y5tKsnn4RLQfOB7RRlhcBH93QAm0mr0HbG2iBNxqh/WagANg9+ZgE4n7h2MsspV74AbGQM+xwmWoxtiCjObBT2Skj7WpIvx3610YXlkQKH2MvgJRKfLcAvRUZkPxq0mNnGm9nPeaIcG0dAUW4Oe9EFp3j7ZbEIdlKITQhH5IsYcr9oApN7hISN1dhOVAp0M5dOSGcDHg0FgJTPAKRxUFCC4M84l+wNmL0HpSZfeGwY3rTNaiAFSXHMGGDCEGEFTC0QfY37qMSNewKMU8RbmH1B7a4+U7uisEyW0SOkoh6hBNgNa6w793g21WR0o40t7hpjF2S7Q/4RTS0F2NzaNFOWGCGPCEAo/90xnkfEAiTBDa5rvGeMTFj1ZQA+4yAA7Zt+AsSSQFNPUt5lbPYMhEH30thBiCByRLICbzSky+iySTI=
*/