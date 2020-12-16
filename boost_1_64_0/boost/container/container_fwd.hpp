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
xe1BazNjcCOy6EY7zBJWq3SPbGTBb+xQ1aTbn996e5G5NuMxmLCXX3z3EVksZIcbCbqtHvnbx2SBbTwPaHIeME+FRRQWU5hju7G5FOZRmM/QAAJonTXbi2YfsKcPmWOHHUAbs30mE4z4JkM5Ms9OO1wG3fKUXdKS9iHeXXYYqNl3+H8+0HvmCbJYnL1aPmgCmX+3HUoLe71tYogsHGfZbaViZLDHDneE/bfZhOpkzr14HiCMrwFBc6OVFZblyV9dOZc4KzP//DXOJc7OVrjaiwz22SFJGF/HguZAayPs6JypHbm/OOubNPQAjxlaDWHO3mtncA3f4XmcML6+HM2LZlS7H62gsCkXXI15v4T2RLP9OLdFmv/8lCy63w7HhC29eX0J2wE7VDPpVvWfIRYy30E7rBPmSTp8lMz/g7ZOqxmv06KF0ILCZuWrdYPjfsRjPmHPHGs7kkUU5vzJ2HwKC6PV0eyAKUH8FhjbPKTHhbHOYxUG5OP3H1pGzQ5qz7El86MVEXai5KsbZGFFXERhUYXFFAaHjc2hMKfCXApzK8yjMC/aWGElKkFuMjiSdjzzzD42nPs7ouhPYV60PML4/A//BeKMz/HwX1gRF1PEOY8ax3nQjOL8iriQIi6qiHMcM45zoxnF+RRxQUVcRBEHx43jXGhGcV5FXEARF0ZzCmufkjSf50/RpvOEcZsetPeF3R73XRLPX1wcn7/jv5DCogpznDQ2t8J8CgsqLKIw+NnYXArzxhmvM+C/gMLCCospzHnK2DwK8ysspLCowhwRY3MbGn6OofXR7Hv8rMq39uL3ZDG0CcLyl7/9G1nwtB26Cdtrm/yQzHkGz/uFFV/yfnOyKFonYd02vnKRec9qa/ea/bXa9zVZ+Bc+NkWTx6Z4DotGzzH6AeMDgQtryQIXtGMbzR5Nc48gC8UZ/04DLYJ2Q9iws2Mvk8X+x9d9RzlVNQEAn2QXWPpLYWFpG3qHgHQEQq9CLPSyQXoRIqwgwkIEBGkSQRApEkEUESWgSFXzCYigQFBBpQYQ6RA6SPvmHDPzZt857/7hOervzNyZ1/LefTfZPwtC/ly6NXMMm0YWOY1zxsm6jd7Q/h+OO18Q/MKun+85kSxwtSBss+jWZcaLN7nO6/jMBbrdO/haJpkWLwinhC3a/OEsMvcNnD8TdvPVc3YeD22YsFNNfzvEOW/i3L0w7fs6x8mCaDLn0+HBQmQxtC3Cmi09vIUseiu7bRp8mvdR5HZByJuk2/QrZz7k8e4nPqcT1u/Ak284J1pBsc1eOrt/Aff+b0FIF/be/nsnyEIPE3N5CeO5PLQ4Wjdhd8dsTSHzPcLnVJHz2/Pv8D4KPMFnX2H1NoeXcxxokAq6yWM3oLCQwiIKiykMLObmUphHYT6FBRQWUlhEYTFTw/+wapA/YbssSVDp57dnkGlohSy69bo/eSGZP0mDciJu73vpn5OF0GqJuBfaF25N5sqhwVERV2fDnm/I3Dmz2/XaR5LJPLk0GCusy1cntpDF0GYIa1d/dmWyYIoGPwt75c6hjWy5Negh6iy+McfzPF5eDbqKuLTJk7uQhdFkLZYWb1cl8+bTIF3kzOxxOEQWya+BV8Q12L5gFfdeQIP6wl7bO04jC6B9I6zzjy9ynL+gBquEzfn72wPcg6bB78LaVNzu5jptGu5fsY9m/Wglizs02CXizlzq247NiceSsGxzLIXMza0wr8L8CgsqLKywqMLipgagpWq8ln832uUpQ5qQBdHq6iaeUwFiaPOFlXlc+0OyUGE8BoWt+fv2Wv5cKaLBwcQ++tFigSIvHX9KFiqmQQOLbtN2Hr1F5i6hwXHQrcHRVpfIvCXxHBNx9+Y=
*/