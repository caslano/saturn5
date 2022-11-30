//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_FWD_HPP
#define BOOST_INTERPROCESS_FWD_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#ifndef BOOST_CSTDINT_HPP
#  include <boost/cstdint.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/std_fwd.hpp>

//! \file
//! This header file forward declares the basic interprocess types:
//!   - boost::interprocess::offset_ptr;
//!   - boost::interprocess::permissions;
//!   - boost::interprocess::mapped_region;
//!   - boost::interprocess::file_mapping;
//!   - boost::interprocess::shared_memory_object;
//!   - boost::interprocess::windows_shared_memory;
//!   - boost::interprocess::xsi_shared_memory;
//!
//! The following synchronization mechanisms and locks:
//!   - boost::interprocess::null_mutex;
//!   - boost::interprocess::interprocess_mutex;
//!   - boost::interprocess::interprocess_recursive_mutex;
//!   - boost::interprocess::interprocess_semaphore;
//!   - boost::interprocess::named_mutex;
//!   - boost::interprocess::named_recursive_mutex;
//!   - boost::interprocess::named_semaphore;
//!   - boost::interprocess::interprocess_sharable_mutex;
//!   - boost::interprocess::interprocess_condition;
//!   - boost::interprocess::scoped_lock;
//!   - boost::interprocess::sharable_lock;
//!   - boost::interprocess::upgradable_lock;
//!
//! The following mutex families:
//!   - boost::interprocess::mutex_family;
//!   - boost::interprocess::null_mutex_family;
//!
//! The following allocators:
//!   - boost::interprocess::allocator;
//!   - boost::interprocess::node_allocator;
//!   - boost::interprocess::private_node_allocator;
//!   - boost::interprocess::cached_node_allocator;
//!   - boost::interprocess::adaptive_pool;
//!   - boost::interprocess::private_adaptive_pool;
//!   - boost::interprocess::cached_adaptive_pool;
//!
//! The following allocation algorithms:
//!   - boost::interprocess::simple_seq_fit;
//!   - boost::interprocess::rbtree_best_fit;
//!
//! The following index types:
//!   - boost::interprocess::flat_map_index;
//!   - boost::interprocess::iset_index;
//!   - boost::interprocess::iunordered_set_index;
//!   - boost::interprocess::map_index;
//!   - boost::interprocess::null_index;
//!   - boost::interprocess::unordered_map_index;
//!
//! The following managed memory types:
//!   - boost::interprocess::segment_manager;
//!   - boost::interprocess::basic_managed_external_buffer
//!   - boost::interprocess::managed_external_buffer
//!   - boost::interprocess::wmanaged_external_buffer
//!   - boost::interprocess::basic_managed_shared_memory
//!   - boost::interprocess::managed_shared_memory
//!   - boost::interprocess::wmanaged_shared_memory
//!   - boost::interprocess::basic_managed_windows_shared_memory
//!   - boost::interprocess::managed_windows_shared_memory
//!   - boost::interprocess::wmanaged_windows_shared_memory
//!   - boost::interprocess::basic_managed_xsi_shared_memory
//!   - boost::interprocess::managed_xsi_shared_memory
//!   - boost::interprocess::wmanaged_xsi_shared_memory
//!   - boost::interprocess::fixed_managed_shared_memory
//!   - boost::interprocess::wfixed_managed_shared_memory
//!   - boost::interprocess::basic_managed_heap_memory
//!   - boost::interprocess::managed_heap_memory
//!   - boost::interprocess::wmanaged_heap_memory
//!   - boost::interprocess::basic_managed_mapped_file
//!   - boost::interprocess::managed_mapped_file
//!   - boost::interprocess::wmanaged_mapped_file
//!
//! The following exception types:
//!   - boost::interprocess::interprocess_exception
//!   - boost::interprocess::lock_exception
//!   - boost::interprocess::bad_alloc
//!
//! The following stream types:
//!   - boost::interprocess::basic_bufferbuf
//!   - boost::interprocess::basic_ibufferstream
//!   - boost::interprocess::basic_obufferstream
//!   - boost::interprocess::basic_bufferstream
//!   - boost::interprocess::basic_vectorbuf
//!   - boost::interprocess::basic_ivectorstream
//!   - boost::interprocess::basic_ovectorstream
//!   - boost::interprocess::basic_vectorstream
//!
//! The following smart pointer types:
//!   - boost::interprocess::scoped_ptr
//!   - boost::interprocess::intrusive_ptr
//!   - boost::interprocess::shared_ptr
//!   - boost::interprocess::weak_ptr
//!
//! The following interprocess communication types:
//!   - boost::interprocess::message_queue_t;
//!   - boost::interprocess::message_queue;

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#include <cstddef>

//////////////////////////////////////////////////////////////////////////////
//                        Standard predeclarations
//////////////////////////////////////////////////////////////////////////////

namespace boost{  namespace intrusive{ }  }
namespace boost{  namespace interprocess{ namespace bi = boost::intrusive; }  }

namespace boost { namespace interprocess {

//////////////////////////////////////////////////////////////////////////////
//                            permissions
//////////////////////////////////////////////////////////////////////////////

class permissions;

//////////////////////////////////////////////////////////////////////////////
//                            shared_memory
//////////////////////////////////////////////////////////////////////////////

class shared_memory_object;

#if defined (BOOST_INTERPROCESS_WINDOWS)
class windows_shared_memory;
#endif   //#if defined (BOOST_INTERPROCESS_WINDOWS)

#if defined(BOOST_INTERPROCESS_XSI_SHARED_MEMORY_OBJECTS)
class xsi_shared_memory;
#endif   //#if defined (BOOST_INTERPROCESS_WINDOWS)

//////////////////////////////////////////////////////////////////////////////
//              file mapping / mapped region
//////////////////////////////////////////////////////////////////////////////

class file_mapping;
class mapped_region;

//////////////////////////////////////////////////////////////////////////////
//                               Mutexes
//////////////////////////////////////////////////////////////////////////////

class null_mutex;

class interprocess_mutex;
class interprocess_recursive_mutex;

class named_mutex;
class named_recursive_mutex;

class interprocess_semaphore;
class named_semaphore;

//////////////////////////////////////////////////////////////////////////////
//                         Mutex families
//////////////////////////////////////////////////////////////////////////////

struct mutex_family;
struct null_mutex_family;

//////////////////////////////////////////////////////////////////////////////
//                   Other synchronization classes
//////////////////////////////////////////////////////////////////////////////

class interprocess_sharable_mutex;
class interprocess_condition;

//////////////////////////////////////////////////////////////////////////////
//                              Locks
//////////////////////////////////////////////////////////////////////////////

template <class Mutex>
class scoped_lock;

template <class SharableMutex>
class sharable_lock;

template <class UpgradableMutex>
class upgradable_lock;

//////////////////////////////////////////////////////////////////////////////
//                      STL compatible allocators
//////////////////////////////////////////////////////////////////////////////

template<class T, class SegmentManager>
class allocator;

template<class T, class SegmentManager, std::size_t NodesPerBlock = 64>
class node_allocator;

template<class T, class SegmentManager, std::size_t NodesPerBlock = 64>
class private_node_allocator;

template<class T, class SegmentManager, std::size_t NodesPerBlock = 64>
class cached_node_allocator;

template< class T, class SegmentManager, std::size_t NodesPerBlock = 64
        , std::size_t MaxFreeBlocks = 2, unsigned char OverheadPercent = 5 >
class adaptive_pool;

template< class T, class SegmentManager, std::size_t NodesPerBlock = 64
        , std::size_t MaxFreeBlocks = 2, unsigned char OverheadPercent = 5 >
class private_adaptive_pool;

template< class T, class SegmentManager, std::size_t NodesPerBlock = 64
        , std::size_t MaxFreeBlocks = 2, unsigned char OverheadPercent = 5 >
class cached_adaptive_pool;


//////////////////////////////////////////////////////////////////////////////
//                            offset_ptr
//////////////////////////////////////////////////////////////////////////////

static const std::size_t offset_type_alignment = 0;

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
#  ifdef BOOST_HAS_INTPTR_T
      using ::boost::uintptr_t;
#  else
      typedef std::size_t uintptr_t;
#  endif
#endif

template < class T, class DifferenceType = std::ptrdiff_t
         , class OffsetType = uintptr_t, std::size_t Alignment = offset_type_alignment>
class offset_ptr;

//////////////////////////////////////////////////////////////////////////////
//                    Memory allocation algorithms
//////////////////////////////////////////////////////////////////////////////

//Single segment memory allocation algorithms
template<class MutexFamily, class VoidMutex = offset_ptr<void> >
class simple_seq_fit;

template<class MutexFamily, class VoidMutex = offset_ptr<void>, std::size_t MemAlignment = 0>
class rbtree_best_fit;

//////////////////////////////////////////////////////////////////////////////
//                         Index Types
//////////////////////////////////////////////////////////////////////////////

template<class IndexConfig> class flat_map_index;
template<class IndexConfig> class iset_index;
template<class IndexConfig> class iunordered_set_index;
template<class IndexConfig> class map_index;
template<class IndexConfig> class null_index;
template<class IndexConfig> class unordered_map_index;

//////////////////////////////////////////////////////////////////////////////
//                         Segment manager
//////////////////////////////////////////////////////////////////////////////

template <class CharType
         ,class MemoryAlgorithm
         ,template<class IndexConfig> class IndexType>
class segment_manager;

//////////////////////////////////////////////////////////////////////////////
//                  External buffer managed memory classes
//////////////////////////////////////////////////////////////////////////////

template <class CharType
         ,class MemoryAlgorithm
         ,template<class IndexConfig> class IndexType>
class basic_managed_external_buffer;

typedef basic_managed_external_buffer
   <char
   ,rbtree_best_fit<null_mutex_family>
   ,iset_index>
managed_external_buffer;

typedef basic_managed_external_buffer
   <wchar_t
   ,rbtree_best_fit<null_mutex_family>
   ,iset_index>
wmanaged_external_buffer;

//////////////////////////////////////////////////////////////////////////////
//                      managed memory classes
//////////////////////////////////////////////////////////////////////////////

template <class CharType
         ,class MemoryAlgorithm
         ,template<class IndexConfig> class IndexType>
class basic_managed_shared_memory;

typedef basic_managed_shared_memory
   <char
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
managed_shared_memory;

typedef basic_managed_shared_memory
   <wchar_t
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
wmanaged_shared_memory;


//////////////////////////////////////////////////////////////////////////////
//                      Windows shared memory managed memory classes
//////////////////////////////////////////////////////////////////////////////

#if defined (BOOST_INTERPROCESS_WINDOWS)

template <class CharType
         ,class MemoryAlgorithm
         ,template<class IndexConfig> class IndexType>
class basic_managed_windows_shared_memory;

typedef basic_managed_windows_shared_memory
   <char
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
managed_windows_shared_memory;

typedef basic_managed_windows_shared_memory
   <wchar_t
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
wmanaged_windows_shared_memory;

#endif   //#if defined (BOOST_INTERPROCESS_WINDOWS)

#if defined(BOOST_INTERPROCESS_XSI_SHARED_MEMORY_OBJECTS)

template <class CharType
         ,class MemoryAlgorithm
         ,template<class IndexConfig> class IndexType>
class basic_managed_xsi_shared_memory;

typedef basic_managed_xsi_shared_memory
   <char
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
managed_xsi_shared_memory;

typedef basic_managed_xsi_shared_memory
   <wchar_t
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
wmanaged_xsi_shared_memory;

#endif //#if defined(BOOST_INTERPROCESS_XSI_SHARED_MEMORY_OBJECTS)

//////////////////////////////////////////////////////////////////////////////
//                      Fixed address shared memory
//////////////////////////////////////////////////////////////////////////////

typedef basic_managed_shared_memory
   <char
   ,rbtree_best_fit<mutex_family, void*>
   ,iset_index>
fixed_managed_shared_memory;

typedef basic_managed_shared_memory
   <wchar_t
   ,rbtree_best_fit<mutex_family, void*>
   ,iset_index>
wfixed_managed_shared_memory;

//////////////////////////////////////////////////////////////////////////////
//                      Heap memory managed memory classes
//////////////////////////////////////////////////////////////////////////////

template
   <class CharType
   ,class MemoryAlgorithm
   ,template<class IndexConfig> class IndexType>
class basic_managed_heap_memory;

typedef basic_managed_heap_memory
   <char
   ,rbtree_best_fit<null_mutex_family>
   ,iset_index>
managed_heap_memory;

typedef basic_managed_heap_memory
   <wchar_t
   ,rbtree_best_fit<null_mutex_family>
   ,iset_index>
wmanaged_heap_memory;

//////////////////////////////////////////////////////////////////////////////
//                         Mapped file managed memory classes
//////////////////////////////////////////////////////////////////////////////

template
   <class CharType
   ,class MemoryAlgorithm
   ,template<class IndexConfig> class IndexType>
class basic_managed_mapped_file;

typedef basic_managed_mapped_file
   <char
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
managed_mapped_file;

typedef basic_managed_mapped_file
   <wchar_t
   ,rbtree_best_fit<mutex_family>
   ,iset_index>
wmanaged_mapped_file;

//////////////////////////////////////////////////////////////////////////////
//                            Exceptions
//////////////////////////////////////////////////////////////////////////////

class interprocess_exception;
class lock_exception;
class bad_alloc;

//////////////////////////////////////////////////////////////////////////////
//                            Bufferstream
//////////////////////////////////////////////////////////////////////////////

//bufferstream
template <class CharT
         ,class CharTraits = std::char_traits<CharT> >
class basic_bufferbuf;

template <class CharT
         ,class CharTraits = std::char_traits<CharT> >
class basic_ibufferstream;

template <class CharT
         ,class CharTraits = std::char_traits<CharT> >
class basic_obufferstream;

template <class CharT
         ,class CharTraits = std::char_traits<CharT> >
class basic_bufferstream;

//////////////////////////////////////////////////////////////////////////////
//                            Vectorstream
//////////////////////////////////////////////////////////////////////////////

template <class CharVector
         ,class CharTraits = std::char_traits<typename CharVector::value_type> >
class basic_vectorbuf;

template <class CharVector
         ,class CharTraits = std::char_traits<typename CharVector::value_type> >
class basic_ivectorstream;

template <class CharVector
         ,class CharTraits = std::char_traits<typename CharVector::value_type> >
class basic_ovectorstream;

template <class CharVector
         ,class CharTraits = std::char_traits<typename CharVector::value_type> >
class basic_vectorstream;

//////////////////////////////////////////////////////////////////////////////
//                             Smart pointers
//////////////////////////////////////////////////////////////////////////////

template<class T, class Deleter>
class scoped_ptr;

template<class T, class VoidPointer>
class intrusive_ptr;

template<class T, class VoidAllocator, class Deleter>
class shared_ptr;

template<class T, class VoidAllocator, class Deleter>
class weak_ptr;

//////////////////////////////////////////////////////////////////////////////
//                                  IPC
//////////////////////////////////////////////////////////////////////////////

template<class VoidPointer>
class message_queue_t;

typedef message_queue_t<offset_ptr<void> > message_queue;

}}  //namespace boost { namespace interprocess {

#endif   //#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#include <boost/interprocess/detail/config_end.hpp>

#endif //#ifndef BOOST_INTERPROCESS_FWD_HPP

/* interprocess_fwd.hpp
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
*/