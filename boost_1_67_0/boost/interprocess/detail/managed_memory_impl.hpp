//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_MANAGED_MEMORY_IMPL_HPP
#define BOOST_INTERPROCESS_DETAIL_MANAGED_MEMORY_IMPL_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/segment_manager.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/detail/nothrow.hpp>
#include <boost/interprocess/detail/simple_swap.hpp>
//
#include <boost/core/no_exceptions_support.hpp>
//
#include <boost/intrusive/detail/minimal_pair_header.hpp>
#include <boost/assert.hpp>

//!\file
//!Describes a named shared memory allocation user class.
//!

namespace boost {
namespace interprocess {
namespace ipcdetail {

template<class BasicManagedMemoryImpl>
class create_open_func;

template<
         class CharType,
         class MemoryAlgorithm,
         template<class IndexConfig> class IndexType
        >
struct segment_manager_type
{
   typedef segment_manager<CharType, MemoryAlgorithm, IndexType> type;
};

//!This class is designed to be a base class to classes that manage
//!creation of objects in a fixed size memory buffer. Apart
//!from allocating raw memory, the user can construct named objects. To
//!achieve this, this class uses the reserved space provided by the allocation
//!algorithm to place a named_allocator_algo, who takes care of name mappings.
//!The class can be customized with the char type used for object names
//!and the memory allocation algorithm to be used.*/
template <  class CharType
         ,  class MemoryAlgorithm
         ,  template<class IndexConfig> class IndexType
         ,  std::size_t Offset = 0
         >
class basic_managed_memory_impl
{
   //Non-copyable
   basic_managed_memory_impl(const basic_managed_memory_impl &);
   basic_managed_memory_impl &operator=(const basic_managed_memory_impl &);

   template<class BasicManagedMemoryImpl>
   friend class create_open_func;

   public:
   typedef typename segment_manager_type
      <CharType, MemoryAlgorithm, IndexType>::type    segment_manager;
   typedef CharType                                   char_type;
   typedef MemoryAlgorithm                            memory_algorithm;
   typedef typename MemoryAlgorithm::mutex_family     mutex_family;
   typedef CharType                                   char_t;
   typedef typename MemoryAlgorithm::size_type        size_type;
   typedef typename MemoryAlgorithm::difference_type  difference_type;
   typedef difference_type                            handle_t;
   typedef typename segment_manager::
      const_named_iterator                            const_named_iterator;
   typedef typename segment_manager::
      const_unique_iterator                           const_unique_iterator;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   typedef typename
           segment_manager::char_ptr_holder_t         char_ptr_holder_t;
   //Experimental. Don't use.

   typedef typename segment_manager::multiallocation_chain  multiallocation_chain;

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   static const size_type PayloadPerAllocation = segment_manager::PayloadPerAllocation;

   private:
   typedef basic_managed_memory_impl
               <CharType, MemoryAlgorithm, IndexType, Offset> self_t;
   protected:
   template<class ManagedMemory>
   static bool grow(const char *filename, size_type extra_bytes)
   {
      typedef typename ManagedMemory::device_type device_type;
      //Increase file size
      try{
         offset_t old_size;
         {
            device_type f(open_or_create, filename, read_write);
            if(!f.get_size(old_size))
               return false;
            f.truncate(old_size + extra_bytes);
         }
         ManagedMemory managed_memory(open_only, filename);
         //Grow always works
         managed_memory.self_t::grow(extra_bytes);
      }
      catch(...){
         return false;
      }
      return true;
   }

   template<class ManagedMemory>
   static bool shrink_to_fit(const char *filename)
   {
      typedef typename ManagedMemory::device_type device_type;
      size_type new_size;
      try{
         ManagedMemory managed_memory(open_only, filename);
         managed_memory.get_size();
         managed_memory.self_t::shrink_to_fit();
         new_size = managed_memory.get_size();
      }
      catch(...){
         return false;
      }

      //Decrease file size
      {
         device_type f(open_or_create, filename, read_write);
         f.truncate(new_size);
      }
      return true;
   }

   //!Constructor. Allocates basic resources. Never throws.
   basic_managed_memory_impl()
      : mp_header(0){}

   //!Destructor. Calls close. Never throws.
   ~basic_managed_memory_impl()
   {  this->close_impl(); }

   //!Places segment manager in the reserved space. This can throw.
   bool  create_impl   (void *addr, size_type size)
   {
      if(mp_header)  return false;

      //Check if there is enough space
      if(size < segment_manager::get_min_size())
         return false;

      //This function should not throw. The index construction can
      //throw if constructor allocates memory. So we must catch it.
      BOOST_TRY{
         //Let's construct the allocator in memory
         mp_header       = ::new(addr, boost_container_new_t()) segment_manager(size);
      }
      BOOST_CATCH(...){
         return false;
      }
      BOOST_CATCH_END
      return true;
   }

   //!Connects to a segment manager in the reserved buffer. Never throws.
   bool  open_impl     (void *addr, size_type)
   {
      if(mp_header)  return false;
      mp_header = static_cast<segment_manager*>(addr);
      return true;
   }

   //!Frees resources. Never throws.
   bool close_impl()
   {
      bool ret = mp_header != 0;
      mp_header = 0;
      return ret;
   }

   //!Frees resources and destroys common resources. Never throws.
   bool destroy_impl()
   {
      if(mp_header == 0)
         return false;
      mp_header->~segment_manager();
      this->close_impl();
         return true;
   }

   //!
   void grow(size_type extra_bytes)
   {  mp_header->grow(extra_bytes); }

   void shrink_to_fit()
   {  mp_header->shrink_to_fit(); }

   public:

   //!Returns segment manager. Never throws.
   segment_manager *get_segment_manager() const
   {   return mp_header; }

   //!Returns the base address of the memory in this process. Never throws.
   void *   get_address   () const
   {   return reinterpret_cast<char*>(mp_header) - Offset; }

   //!Returns the size of memory segment. Never throws.
   size_type   get_size   () const
   {   return mp_header->get_size() + Offset;  }

   //!Returns the number of free bytes of the memory
   //!segment
   size_type get_free_memory() const
   {  return mp_header->get_free_memory();  }

   //!Returns the result of "all_memory_deallocated()" function
   //!of the used memory algorithm
   bool all_memory_deallocated()
   {   return mp_header->all_memory_deallocated(); }

   //!Returns the result of "check_sanity()" function
   //!of the used memory algorithm
   bool check_sanity()
   {   return mp_header->check_sanity(); }

   //!Writes to zero free memory (memory not yet allocated) of
   //!the memory algorithm
   void zero_free_memory()
   {   mp_header->zero_free_memory(); }

   //!Transforms an absolute address into an offset from base address.
   //!The address must belong to the memory segment. Never throws.
   handle_t get_handle_from_address   (const void *ptr) const
   {
      return (handle_t)(reinterpret_cast<const char*>(ptr) -
             reinterpret_cast<const char*>(this->get_address()));
   }

   //!Returns true if the address belongs to the managed memory segment
   bool belongs_to_segment (const void *ptr) const
   {
      return ptr >= this->get_address() &&
             ptr <  (reinterpret_cast<const char*>(this->get_address()) + this->get_size());
   }

   //!Transforms previously obtained offset into an absolute address in the
   //!process space of the current process. Never throws.*/
   void *    get_address_from_handle (handle_t offset) const
   {  return reinterpret_cast<char*>(this->get_address()) + offset; }

   //!Searches for nbytes of free memory in the segment, marks the
   //!memory as used and return the pointer to the memory. If no
   //!memory is available throws a boost::interprocess::bad_alloc exception
   void* allocate             (size_type nbytes)
   {   return mp_header->allocate(nbytes);   }

   //!Searches for nbytes of free memory in the segment, marks the
   //!memory as used and return the pointer to the memory. If no memory
   //!is available returns 0. Never throws.
   void* allocate             (size_type nbytes, const std::nothrow_t &tag)
   {   return mp_header->allocate(nbytes, tag);  }

   //!Allocates nbytes bytes aligned to "alignment" bytes. "alignment"
   //!must be power of two. If no memory
   //!is available returns 0. Never throws.
   void * allocate_aligned (size_type nbytes, size_type alignment, const std::nothrow_t &tag)
   {   return mp_header->allocate_aligned(nbytes, alignment, tag);  }

   template<class T>
   T * allocation_command  (boost::interprocess::allocation_type command,   size_type limit_size,
                           size_type &prefer_in_recvd_out_size, T *&reuse)
   {  return mp_header->allocation_command(command, limit_size, prefer_in_recvd_out_size, reuse);  }

   //!Allocates nbytes bytes aligned to "alignment" bytes. "alignment"
   //!must be power of two. If no
   //!memory is available throws a boost::interprocess::bad_alloc exception
   void * allocate_aligned(size_type nbytes, size_type alignment)
   {   return mp_header->allocate_aligned(nbytes, alignment);  }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Experimental. Don't use.

   //!Allocates n_elements of elem_bytes bytes.
   //!Throws bad_alloc on failure. chain.size() is not increased on failure.
   void allocate_many(size_type elem_bytes, size_type n_elements, multiallocation_chain &chain)
   {  mp_header->allocate_many(elem_bytes, n_elements, chain); }

   //!Allocates n_elements, each one of element_lengths[i]*sizeof_element bytes.
   //!Throws bad_alloc on failure. chain.size() is not increased on failure.
   void allocate_many(const size_type *element_lengths, size_type n_elements, size_type sizeof_element, multiallocation_chain &chain)
   {  mp_header->allocate_many(element_lengths, n_elements, sizeof_element, chain); }

   //!Allocates n_elements of elem_bytes bytes.
   //!Non-throwing version. chain.size() is not increased on failure.
   void allocate_many(const std::nothrow_t &tag, size_type elem_bytes, size_type n_elements, multiallocation_chain &chain)
   {  mp_header->allocate_many(tag, elem_bytes, n_elements, chain); }

   //!Allocates n_elements, each one of
   //!element_lengths[i]*sizeof_element bytes.
   //!Non-throwing version. chain.size() is not increased on failure.
   void allocate_many(const std::nothrow_t &tag, const size_type *elem_sizes, size_type n_elements, size_type sizeof_element, multiallocation_chain &chain)
   {  mp_header->allocate_many(tag, elem_sizes, n_elements, sizeof_element, chain); }

   //!Deallocates all elements contained in chain.
   //!Never throws.
   void deallocate_many(multiallocation_chain &chain)
   {  mp_header->deallocate_many(chain); }

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   //!Marks previously allocated memory as free. Never throws.
   void  deallocate           (void *addr)
   {   if (mp_header) mp_header->deallocate(addr);  }

   //!Tries to find a previous named allocation address. Returns a memory
   //!buffer and the object count. If not found returned pointer is 0.
   //!Never throws.
   template <class T>
   std::pair<T*, size_type> find  (char_ptr_holder_t name)
   {   return mp_header->template find<T>(name); }

   //!Creates a named object or array in memory
   //!
   //!Allocates and constructs a T object or an array of T in memory,
   //!associates this with the given name and returns a pointer to the
   //!created object. If an array is being constructed all objects are
   //!created using the same parameters given to this function.
   //!
   //!-> If the name was previously used, returns 0.
   //!
   //!-> Throws boost::interprocess::bad_alloc if there is no available memory
   //!
   //!-> If T's constructor throws, the function throws that exception.
   //!
   //!Memory is freed automatically if T's constructor throws and if an
   //!array was being constructed, destructors of created objects are called
   //!before freeing the memory.
   template <class T>
   typename segment_manager::template construct_proxy<T>::type
      construct(char_ptr_holder_t name)
   {   return mp_header->template construct<T>(name);  }

   //!Finds or creates a named object or array in memory
   //!
   //!Tries to find an object with the given name in memory. If
   //!found, returns the pointer to this pointer. If the object is not found,
   //!allocates and constructs a T object or an array of T in memory,
   //!associates this with the given name and returns a pointer to the
   //!created object. If an array is being constructed all objects are
   //!created using the same parameters given to this function.
   //!
   //!-> Throws boost::interprocess::bad_alloc if there is no available memory
   //!
   //!-> If T's constructor throws, the function throws that exception.
   //!
   //!Memory is freed automatically if T's constructor throws and if an
   //!array was being constructed, destructors of created objects are called
   //!before freeing the memory.
   template <class T>
   typename segment_manager::template construct_proxy<T>::type
      find_or_construct(char_ptr_holder_t name)
   {   return mp_header->template find_or_construct<T>(name);  }

   //!Creates a named object or array in memory
   //!
   //!Allocates and constructs a T object or an array of T in memory,
   //!associates this with the given name and returns a pointer to the
   //!created object. If an array is being constructed all objects are
   //!created using the same parameters given to this function.
   //!
   //!-> If the name was previously used, returns 0.
   //!
   //!-> Returns 0 if there is no available memory
   //!
   //!-> If T's constructor throws, the function throws that exception.
   //!
   //!Memory is freed automatically if T's constructor throws and if an
   //!array was being constructed, destructors of created objects are called
   //!before freeing the memory.
   template <class T>
   typename segment_manager::template construct_proxy<T>::type
      construct(char_ptr_holder_t name, const std::nothrow_t &tag)
   {   return mp_header->template construct<T>(name, tag);  }

   //!Finds or creates a named object or array in memory
   //!
   //!Tries to find an object with the given name in memory. If
   //!found, returns the pointer to this pointer. If the object is not found,
   //!allocates and constructs a T object or an array of T in memory,
   //!associates this with the given name and returns a pointer to the
   //!created object. If an array is being constructed all objects are
   //!created using the same parameters given to this function.
   //!
   //!-> Returns 0 if there is no available memory
   //!
   //!-> If T's constructor throws, the function throws that exception.
   //!
   //!Memory is freed automatically if T's constructor throws and if an
   //!array was being constructed, destructors of created objects are called
   //!before freeing the memory.
   template <class T>
   typename segment_manager::template construct_proxy<T>::type
      find_or_construct(char_ptr_holder_t name, const std::nothrow_t &tag)
   {   return mp_header->template find_or_construct<T>(name, tag);  }

   //!Creates a named array from iterators in memory
   //!
   //!Allocates and constructs an array of T in memory,
   //!associates this with the given name and returns a pointer to the
   //!created object. Each element in the array is created using the
   //!objects returned when dereferencing iterators as parameters
   //!and incrementing all iterators for each element.
   //!
   //!-> If the name was previously used, returns 0.
   //!
   //!-> Throws boost::interprocess::bad_alloc if there is no available memory
   //!
   //!-> If T's constructor throws, the function throws that exception.
   //!
   //!Memory is freed automatically if T's constructor throws and
   //!destructors of created objects are called before freeing the memory.
   template <class T>
   typename segment_manager::template construct_iter_proxy<T>::type
      construct_it(char_ptr_holder_t name)
   {   return mp_header->template construct_it<T>(name);  }

   //!Finds or creates a named array from iterators in memory
   //!
   //!Tries to find an object with the given name in memory. If
   //!found, returns the pointer to this pointer. If the object is not found,
   //!allocates and constructs an array of T in memory,
   //!associates this with the given name and returns a pointer to the
   //!created object. Each element in the array is created using the
   //!objects returned when dereferencing iterators as parameters
   //!and incrementing all iterators for each element.
   //!
   //!-> If the name was previously used, returns 0.
   //!
   //!-> Throws boost::interprocess::bad_alloc if there is no available memory
   //!
   //!-> If T's constructor throws, the function throws that exception.
   //!
   //!Memory is freed automatically if T's constructor throws and
   //!destructors of created objects are called before freeing the memory.
   template <class T>
   typename segment_manager::template construct_iter_proxy<T>::type
      find_or_construct_it(char_ptr_holder_t name)
   {   return mp_header->template find_or_construct_it<T>(name);  }

   //!Creates a named array from iterators in memory
   //!
   //!Allocates and constructs an array of T in memory,
   //!associates this with the given name and returns a pointer to the
   //!created object. Each element in the array is created using the
   //!objects returned when dereferencing iterators as parameters
   //!and incrementing all iterators for each element.
   //!
   //!-> If the name was previously used, returns 0.
   //!
   //!-> If there is no available memory, returns 0.
   //!
   //!-> If T's constructor throws, the function throws that exception.
   //!
   //!Memory is freed automatically if T's constructor throws and
   //!destructors of created objects are called before freeing the memory.*/
   template <class T>
   typename segment_manager::template construct_iter_proxy<T>::type
      construct_it(char_ptr_holder_t name, const std::nothrow_t &tag)
   {   return mp_header->template construct_it<T>(name, tag);  }

   //!Finds or creates a named array from iterators in memory
   //!
   //!Tries to find an object with the given name in memory. If
   //!found, returns the pointer to this pointer. If the object is not found,
   //!allocates and constructs an array of T in memory,
   //!associates this with the given name and returns a pointer to the
   //!created object. Each element in the array is created using the
   //!objects returned when dereferencing iterators as parameters
   //!and incrementing all iterators for each element.
   //!
   //!-> If the name was previously used, returns 0.
   //!
   //!-> If there is no available memory, returns 0.
   //!
   //!-> If T's constructor throws, the function throws that exception.
   //!
   //!Memory is freed automatically if T's constructor throws and
   //!destructors of created objects are called before freeing the memory.*/
   template <class T>
   typename segment_manager::template construct_iter_proxy<T>::type
      find_or_construct_it(char_ptr_holder_t name, const std::nothrow_t &tag)
   {   return mp_header->template find_or_construct_it<T>(name, tag);  }

   //!Calls a functor and guarantees that no new construction, search or
   //!destruction will be executed by any process while executing the object
   //!function call. If the functor throws, this function throws.
   template <class Func>
   void atomic_func(Func &f)
   {   mp_header->atomic_func(f);  }

   //!Tries to call a functor guaranteeing that no new construction, search or
   //!destruction will be executed by any process while executing the object
   //!function call. If the atomic function can't be immediatelly executed
   //!because the internal mutex is already locked, returns false.
   //!If the functor throws, this function throws.
   template <class Func>
   bool try_atomic_func(Func &f)
   {   return mp_header->try_atomic_func(f); }

   //!Destroys a named memory object or array.
   //!
   //!Finds the object with the given name, calls its destructors,
   //!frees used memory and returns true.
   //!
   //!-> If the object is not found, it returns false.
   //!
   //!Exception Handling:
   //!
   //!When deleting a dynamically object or array, the Standard
   //!does not guarantee that dynamically allocated memory, will be released.
   //!Also, when deleting arrays, the Standard doesn't require calling
   //!destructors for the rest of the objects if for one of them the destructor
   //!terminated with an exception.
   //!
   //!Destroying an object:
   //!
   //!If the destructor throws, the memory will be freed and that exception
   //!will be thrown.
   //!
   //!Destroying an array:
   //!
   //!When destroying an array, if a destructor throws, the rest of
   //!destructors are called. If any of these throws, the exceptions are
   //!ignored. The name association will be erased, memory will be freed and
   //!the first exception will be thrown. This guarantees the unlocking of
   //!mutexes and other resources.
   //!
   //!For all theses reasons, classes with throwing destructors are not
   //!recommended.
   template <class T>
   bool destroy(const CharType *name)
   {   return mp_header->template destroy<T>(name); }

   //!Destroys the unique instance of type T
   //!
   //!Calls the destructor, frees used memory and returns true.
   //!
   //!Exception Handling:
   //!
   //!When deleting a dynamically object, the Standard does not
   //!guarantee that dynamically allocated memory will be released.
   //!
   //!Destroying an object:
   //!
   //!If the destructor throws, the memory will be freed and that exception
   //!will be thrown.
   //!
   //!For all theses reasons, classes with throwing destructors are not
   //!recommended for  memory.
   template <class T>
   bool destroy(const unique_instance_t *const )
   {   return mp_header->template destroy<T>(unique_instance);  }

   //!Destroys the object (named, unique, or anonymous)
   //!
   //!Calls the destructor, frees used memory and returns true.
   //!
   //!Exception Handling:
   //!
   //!When deleting a dynamically object, the Standard does not
   //!guarantee that dynamically allocated memory will be released.
   //!
   //!Destroying an object:
   //!
   //!If the destructor throws, the memory will be freed and that exception
   //!will be thrown.
   //!
   //!For all theses reasons, classes with throwing destructors are not
   //!recommended for  memory.
   template <class T>
   void destroy_ptr(const T *ptr)
   {  mp_header->template destroy_ptr<T>(ptr); }

   //!Returns the name of an object created with construct/find_or_construct
   //!functions. If ptr points to an unique instance typeid(T).name() is returned.
   template<class T>
   static const char_type *get_instance_name(const T *ptr)
   {  return segment_manager::get_instance_name(ptr);   }

   //!Returns is the type an object created with construct/find_or_construct
   //!functions. Does not throw.
   template<class T>
   static instance_type get_instance_type(const T *ptr)
   {  return segment_manager::get_instance_type(ptr); }

   //!Returns the length of an object created with construct/find_or_construct
   //!functions (1 if is a single element, >=1 if it's an array). Does not throw.
   template<class T>
   static size_type get_instance_length(const T *ptr)
   {  return segment_manager::get_instance_length(ptr); }

   //!Preallocates needed index resources to optimize the
   //!creation of "num" named objects in the  memory segment.
   //!Can throw boost::interprocess::bad_alloc if there is no enough memory.
   void reserve_named_objects(size_type num)
   {  mp_header->reserve_named_objects(num);  }

   //!Preallocates needed index resources to optimize the
   //!creation of "num" unique objects in the  memory segment.
   //!Can throw boost::interprocess::bad_alloc if there is no enough memory.
   void reserve_unique_objects(size_type num)
   {  mp_header->reserve_unique_objects(num);  }

   //!Calls shrink_to_fit in both named and unique object indexes
   //to try to free unused memory from those indexes.
   void shrink_to_fit_indexes()
   {  mp_header->shrink_to_fit_indexes();  }

   //!Returns the number of named objects stored
   //!in the managed segment.
   size_type get_num_named_objects()
   {  return mp_header->get_num_named_objects();  }

   //!Returns the number of unique objects stored
   //!in the managed segment.
   size_type get_num_unique_objects()
   {  return mp_header->get_num_unique_objects();  }

   //!Returns a constant iterator to the index storing the
   //!named allocations. NOT thread-safe. Never throws.
   const_named_iterator named_begin() const
   {  return mp_header->named_begin(); }

   //!Returns a constant iterator to the end of the index
   //!storing the named allocations. NOT thread-safe. Never throws.
   const_named_iterator named_end() const
   {  return mp_header->named_end(); }

   //!Returns a constant iterator to the index storing the
   //!unique allocations. NOT thread-safe. Never throws.
   const_unique_iterator unique_begin() const
   {  return mp_header->unique_begin(); }

   //!Returns a constant iterator to the end of the index
   //!storing the unique allocations. NOT thread-safe. Never throws.
   const_unique_iterator unique_end() const
   {  return mp_header->unique_end(); }

   //!This is the default allocator to allocate types T
   //!from this managed segment
   template<class T>
   struct allocator
   {
      typedef typename segment_manager::template allocator<T>::type type;
   };

   //!Returns an instance of the default allocator for type T
   //!initialized that allocates memory from this segment manager.
   template<class T>
   typename allocator<T>::type
      get_allocator()
   {   return mp_header->template get_allocator<T>(); }

   //!This is the default deleter to delete types T
   //!from this managed segment.
   template<class T>
   struct deleter
   {
      typedef typename segment_manager::template deleter<T>::type type;
   };

   //!Returns an instance of the default allocator for type T
   //!initialized that allocates memory from this segment manager.
   template<class T>
   typename deleter<T>::type
      get_deleter()
   {   return mp_header->template get_deleter<T>(); }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //!Tries to find a previous named allocation address. Returns a memory
   //!buffer and the object count. If not found returned pointer is 0.
   //!Never throws.
   template <class T>
   std::pair<T*, size_type> find_no_lock  (char_ptr_holder_t name)
   {   return mp_header->template find_no_lock<T>(name); }
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   protected:
   //!Swaps the segment manager's managed by this managed memory segment.
   //!NOT thread-safe. Never throws.
   void swap(basic_managed_memory_impl &other)
   {  (simple_swap)(mp_header, other.mp_header); }

   private:
   segment_manager *mp_header;
};

template<class BasicManagedMemoryImpl>
class create_open_func
{
   typedef typename BasicManagedMemoryImpl::size_type size_type;

   public:

   create_open_func(BasicManagedMemoryImpl * const frontend, create_enum_t type)
      : m_frontend(frontend), m_type(type){}

   bool operator()(void *addr, std::size_t size, bool created) const
   {
      if( ((m_type == DoOpen)   &&  created) ||
          ((m_type == DoCreate) && !created) ||
          //Check for overflow
          size_type(-1) < size ){
         return false;
      }
      else if(created){
         return m_frontend->create_impl(addr, static_cast<size_type>(size));
      }
      else{
         return m_frontend->open_impl  (addr, static_cast<size_type>(size));
      }
   }

   static std::size_t get_min_size()
   {
      const size_type sz = BasicManagedMemoryImpl::segment_manager::get_min_size();
      if(sz > std::size_t(-1)){
         //The minimum size is not representable by std::size_t
         BOOST_ASSERT(false);
         return std::size_t(-1);
      }
      else{
         return static_cast<std::size_t>(sz);
      }
   }

   private:
   BasicManagedMemoryImpl *m_frontend;
   create_enum_t           m_type;
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_MANAGED_MEMORY_IMPL_HPP


/* managed_memory_impl.hpp
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
*/