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
   template<class ManagedMemory, class CharT>
   static bool grow(const CharT *filename, size_type extra_bytes)
   {
      typedef typename ManagedMemory::device_type device_type;
      //Increase file size
      BOOST_TRY{
         offset_t old_size;
         {
            device_type f(open_or_create, filename, read_write);
            if(!f.get_size(old_size))
               return false;
            f.truncate(old_size + static_cast<offset_t>(extra_bytes));
         }
         ManagedMemory managed_memory(open_only, filename);
         //Grow always works
         managed_memory.self_t::grow(extra_bytes);
      }
      BOOST_CATCH(...){
         return false;
      } BOOST_CATCH_END
      return true;
   }

   template<class ManagedMemory, class CharT>
   static bool shrink_to_fit(const CharT *filename)
   {
      typedef typename ManagedMemory::device_type device_type;
      size_type new_size;
      BOOST_TRY{
         ManagedMemory managed_memory(open_only, filename);
         managed_memory.get_size();
         managed_memory.self_t::shrink_to_fit();
         new_size = managed_memory.get_size();
      }
      BOOST_CATCH(...){
         return false;
      } BOOST_CATCH_END

      //Decrease file size
      {
         device_type f(open_or_create, filename, read_write);
         f.truncate(static_cast<offset_t>(new_size));
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
         BOOST_ASSERT((0 == (std::size_t)addr % boost::move_detail::alignment_of<segment_manager>::value));
         mp_header       = ::new(addr, boost_container_new_t()) segment_manager(size);
      }
      BOOST_CATCH(...){
         return false;
      } BOOST_CATCH_END
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