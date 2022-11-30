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
//!   - boost::container::devector
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
class devector;

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

#ifndef BOOST_NO_CXX11_TEMPLATE_ALIASES

//! Alias templates for small_flat_[multi]{set|map} using small_vector as container

template < class Key
         , std::size_t N
         , class Compare  = std::less<Key>
         , class SmallVectorAllocator = void
         , class SmallVectorOptions   = void  >
using small_flat_set = flat_set<Key, Compare, small_vector<Key, N, SmallVectorAllocator, SmallVectorOptions>>;

template < class Key
         , std::size_t N
         , class Compare  = std::less<Key>
         , class SmallVectorAllocator = void
         , class SmallVectorOptions   = void  >
using small_flat_multiset = flat_multiset<Key, Compare, small_vector<Key, N, SmallVectorAllocator, SmallVectorOptions>>;

template < class Key
         , class T
         , std::size_t N
         , class Compare  = std::less<Key>
         , class SmallVectorAllocator = void
         , class SmallVectorOptions   = void  >
using small_flat_map = flat_map<Key, T, Compare, small_vector<std::pair<Key, T>, N, SmallVectorAllocator, SmallVectorOptions>>;

template < class Key
         , class T
         , std::size_t N
         , class Compare  = std::less<Key>
         , class SmallVectorAllocator = void
         , class SmallVectorOptions   = void  >
using small_flat_multimap = flat_multimap<Key, T, Compare, small_vector<std::pair<Key, T>, N, SmallVectorAllocator, SmallVectorOptions>>;

#endif // #ifndef BOOST_NO_CXX11_TEMPLATE_ALIASES


//! A portable metafunction to obtain a small_flat_set
template < class Key
         , std::size_t N
         , class Compare  = std::less<Key>
         , class SmallVectorAllocator = void
         , class SmallVectorOptions   = void  >
struct small_flat_set_of
{
   typedef flat_set<Key, Compare, small_vector<Key, N, SmallVectorAllocator, SmallVectorOptions> > type;
};

//! A portable metafunction to obtain a small_flat_multiset
template < class Key
         , std::size_t N
         , class Compare  = std::less<Key>
         , class SmallVectorAllocator = void
         , class SmallVectorOptions   = void  >
struct small_flat_multiset_of
{
   typedef flat_multiset<Key, Compare, small_vector<Key, N, SmallVectorAllocator, SmallVectorOptions> > type;
};

//! A portable metafunction to obtain a small_flat_map
template < class Key
         , class T
         , std::size_t N
         , class Compare  = std::less<Key>
         , class SmallVectorAllocator = void
         , class SmallVectorOptions   = void  >
struct small_flat_map_of
{
   typedef flat_map<Key, T, Compare, small_vector<std::pair<Key, T>, N, SmallVectorAllocator, SmallVectorOptions> > type;
};

//! A portable metafunction to obtain a small_flat_multimap
template < class Key
         , class T
         , std::size_t N
         , class Compare  = std::less<Key>
         , class SmallVectorAllocator = void
         , class SmallVectorOptions   = void  >
struct small_flat_multimap_of
{
   typedef flat_multimap<Key, T, Compare, small_vector<std::pair<Key, T>, N, SmallVectorAllocator, SmallVectorOptions> > type;
};

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

typedef const std::piecewise_construct_t & piecewise_construct_t;

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

}}  //namespace boost { namespace container {

#endif //#ifndef BOOST_CONTAINER_CONTAINER_FWD_HPP

/* container_fwd.hpp
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
*/