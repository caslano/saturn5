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