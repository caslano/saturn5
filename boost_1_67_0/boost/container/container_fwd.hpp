//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_CONTAINER_FWD_HPP
#define BOOST_CONTAINER_CONTAINER_FWD_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//! \file
//! This header file forward declares the following containers:
//!   - boost::container::vector
//!   - boost::container::stable_vector
//!   - boost::container::static_vector
//!   - boost::container::small_vector_base
//!   - boost::container::small_vector
//!   - boost::container::slist
//!   - boost::container::list
//!   - boost::container::set
//!   - boost::container::multiset
//!   - boost::container::map
//!   - boost::container::multimap
//!   - boost::container::flat_set
//!   - boost::container::flat_multiset
//!   - boost::container::flat_map
//!   - boost::container::flat_multimap
//!   - boost::container::basic_string
//!   - boost::container::string
//!   - boost::container::wstring
//!
//! Forward declares the following allocators:
//!   - boost::container::allocator
//!   - boost::container::node_allocator
//!   - boost::container::adaptive_pool
//!
//! Forward declares the following polymorphic resource classes:
//!   - boost::container::pmr::memory_resource
//!   - boost::container::pmr::polymorphic_allocator
//!   - boost::container::pmr::monotonic_buffer_resource
//!   - boost::container::pmr::pool_options
//!   - boost::container::pmr::unsynchronized_pool_resource
//!   - boost::container::pmr::synchronized_pool_resource
//!
//! And finally it defines the following types

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//Std forward declarations
#ifndef BOOST_CONTAINER_DETAIL_STD_FWD_HPP
   #include <boost/container/detail/std_fwd.hpp>
#endif

namespace boost{
namespace intrusive{
namespace detail{
   //Create namespace to avoid compilation errors
}}}

namespace boost{ namespace container{ namespace dtl{
   namespace bi = boost::intrusive;
   namespace bid = boost::intrusive::detail;
}}}

namespace boost{ namespace container{ namespace pmr{
   namespace bi = boost::intrusive;
   namespace bid = boost::intrusive::detail;
}}}

#include <cstddef>

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//////////////////////////////////////////////////////////////////////////////
//                             Containers
//////////////////////////////////////////////////////////////////////////////

namespace boost {
namespace container {

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

template<class T1, class T2>
struct pair;

template<class T>
class new_allocator;

template <class T
         ,class Allocator = void
         ,class Options   = void>
class vector;

template <class T
         ,class Allocator = void >
class stable_vector;

template < class T
         , std::size_t Capacity
         , class Options = void>
class static_vector;

template < class T
         , class Allocator = void
         , class Options   = void >
class small_vector_base;

template < class T
         , std::size_t N
         , class Allocator = void
         , class Options   = void  >
class small_vector;

template <class T
         ,class Allocator = void
         ,class Options   = void>
class deque;

template <class T
         ,class Allocator = void >
class list;

template <class T
         ,class Allocator = void >
class slist;

template <class Key
         ,class Compare  = std::less<Key>
         ,class Allocator = void
         ,class Options = void>
class set;

template <class Key
         ,class Compare  = std::less<Key>
         ,class Allocator = void
         ,class Options = void >
class multiset;

template <class Key
         ,class T
         ,class Compare  = std::less<Key>
         ,class Allocator = void
         ,class Options = void >
class map;

template <class Key
         ,class T
         ,class Compare  = std::less<Key>
         ,class Allocator = void
         ,class Options = void >
class multimap;

template <class Key
         ,class Compare  = std::less<Key>
         ,class Allocator = void >
class flat_set;

template <class Key
         ,class Compare  = std::less<Key>
         ,class Allocator = void >
class flat_multiset;

template <class Key
         ,class T
         ,class Compare  = std::less<Key>
         ,class Allocator = void >
class flat_map;

template <class Key
         ,class T
         ,class Compare  = std::less<Key>
         ,class Allocator = void >
class flat_multimap;

template <class CharT
         ,class Traits = std::char_traits<CharT>
         ,class Allocator  = void >
class basic_string;

typedef basic_string <char>   string;
typedef basic_string<wchar_t> wstring;

static const std::size_t ADP_nodes_per_block    = 256u;
static const std::size_t ADP_max_free_blocks    = 2u;
static const std::size_t ADP_overhead_percent   = 1u;
static const std::size_t ADP_only_alignment     = 0u;

template < class T
         , std::size_t NodesPerBlock   = ADP_nodes_per_block
         , std::size_t MaxFreeBlocks   = ADP_max_free_blocks
         , std::size_t OverheadPercent = ADP_overhead_percent
         , unsigned Version = 2
         >
class adaptive_pool;

template < class T
         , unsigned Version = 2
         , unsigned int AllocationDisableMask = 0>
class allocator;

static const std::size_t NodeAlloc_nodes_per_block = 256u;

template
   < class T
   , std::size_t NodesPerBlock = NodeAlloc_nodes_per_block
   , std::size_t Version = 2>
class node_allocator;

namespace pmr {

class memory_resource;

template<class T>
class polymorphic_allocator;

class monotonic_buffer_resource;

struct pool_options;

template <class Allocator>
class resource_adaptor_imp;

class unsynchronized_pool_resource;

class synchronized_pool_resource;

}  //namespace pmr {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//! Type used to tag that the input range is
//! guaranteed to be ordered
struct ordered_range_t
{};

//! Value used to tag that the input range is
//! guaranteed to be ordered
static const ordered_range_t ordered_range = ordered_range_t();

//! Type used to tag that the input range is
//! guaranteed to be ordered and unique
struct ordered_unique_range_t
   : public ordered_range_t
{};

//! Value used to tag that the input range is
//! guaranteed to be ordered and unique
static const ordered_unique_range_t ordered_unique_range = ordered_unique_range_t();

//! Type used to tag that the inserted values
//! should be default initialized
struct default_init_t
{};

//! Value used to tag that the inserted values
//! should be default initialized
static const default_init_t default_init = default_init_t();
#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//! Type used to tag that the inserted values
//! should be value initialized
struct value_init_t
{};

//! Value used to tag that the inserted values
//! should be value initialized
static const value_init_t value_init = value_init_t();

namespace container_detail_really_deep_namespace {

//Otherwise, gcc issues a warning of previously defined
//anonymous_instance and unique_instance
struct dummy
{
   dummy()
   {
      (void)ordered_range;
      (void)ordered_unique_range;
      (void)default_init;
   }
};

}  //detail_really_deep_namespace {


#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

}}  //namespace boost { namespace container {

#endif //#ifndef BOOST_CONTAINER_CONTAINER_FWD_HPP

/* container_fwd.hpp
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
*/