/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2007-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_FWD_HPP
#define BOOST_INTRUSIVE_FWD_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#ifndef BOOST_CSTDINT_HPP
#  include <boost/cstdint.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//! \file
//! This header file forward declares most Intrusive classes.
//!
//! It forward declares the following containers and hooks:
//!   - boost::intrusive::slist / boost::intrusive::slist_base_hook / boost::intrusive::slist_member_hook
//!   - boost::intrusive::list / boost::intrusive::list_base_hook / boost::intrusive::list_member_hook
//!   - boost::intrusive::bstree / boost::intrusive::bs_set / boost::intrusive::bs_multiset /
//!      boost::intrusive::bs_set_base_hook / boost::intrusive::bs_set_member_hook
//!   - boost::intrusive::rbtree / boost::intrusive::set / boost::intrusive::multiset /
//!      boost::intrusive::set_base_hook / boost::intrusive::set_member_hook
//!   - boost::intrusive::avltree / boost::intrusive::avl_set / boost::intrusive::avl_multiset /
//!      boost::intrusive::avl_set_base_hook / boost::intrusive::avl_set_member_hook
//!   - boost::intrusive::splaytree / boost::intrusive::splay_set / boost::intrusive::splay_multiset
//!   - boost::intrusive::sgtree / boost::intrusive::sg_set / boost::intrusive::sg_multiset
//!   - boost::intrusive::treap / boost::intrusive::treap_set / boost::intrusive::treap_multiset
//!   - boost::intrusive::hashtable / boost::intrusive::unordered_set / boost::intrusive::unordered_multiset /
//!      boost::intrusive::unordered_set_base_hook / boost::intrusive::unordered_set_member_hook /
//!   - boost::intrusive::any_base_hook / boost::intrusive::any_member_hook
//!
//! It forward declares the following container or hook options:
//!   - boost::intrusive::constant_time_size / boost::intrusive::size_type / boost::intrusive::compare / boost::intrusive::equal
//!   - boost::intrusive::floating_point / boost::intrusive::priority / boost::intrusive::hash
//!   - boost::intrusive::value_traits / boost::intrusive::member_hook / boost::intrusive::function_hook / boost::intrusive::base_hook
//!   - boost::intrusive::void_pointer / boost::intrusive::tag / boost::intrusive::link_mode
//!   - boost::intrusive::optimize_size / boost::intrusive::linear / boost::intrusive::cache_last
//!   - boost::intrusive::bucket_traits / boost::intrusive::store_hash / boost::intrusive::optimize_multikey
//!   - boost::intrusive::power_2_buckets / boost::intrusive::cache_begin / boost::intrusive::compare_hash / boost::intrusive::incremental
//!
//! It forward declares the following value traits utilities:
//!   - boost::intrusive::value_traits / boost::intrusive::derivation_value_traits /
//!      boost::intrusive::trivial_value_traits
//!
//! Finally it forward declares the following general purpose utilities:
//!   - boost::intrusive::pointer_plus_bits / boost::intrusive::priority_compare.

#if !defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

#include <cstddef>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/detail/workaround.hpp>

namespace boost {
namespace intrusive {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
#  ifdef BOOST_HAS_INTPTR_T
      using ::boost::uintptr_t;
#  else
      typedef std::size_t uintptr_t;
#  endif
#endif

////////////////////////////
//     Node algorithms
////////////////////////////

//Algorithms predeclarations
template<class NodeTraits>
class circular_list_algorithms;

template<class NodeTraits>
class circular_slist_algorithms;

template<class NodeTraits>
class linear_slist_algorithms;

template<class NodeTraits>
class bstree_algorithms;

template<class NodeTraits>
class rbtree_algorithms;

template<class NodeTraits>
class avltree_algorithms;

template<class NodeTraits>
class sgtree_algorithms;

template<class NodeTraits>
class splaytree_algorithms;

template<class NodeTraits>
class treap_algorithms;

////////////////////////////
//       Containers
////////////////////////////

//slist
#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   >
#else
template<class T, class ...Options>
#endif
class slist;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class O1  = void
   , class O2  = void
   , class O3  = void
   >
#else
template<class ...Options>
#endif
class slist_base_hook;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class O1  = void
   , class O2  = void
   , class O3  = void
   >
#else
template<class ...Options>
#endif
class slist_member_hook;

//list
#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   >
#else
template<class T, class ...Options>
#endif
class list;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class O1  = void
   , class O2  = void
   , class O3  = void
   >
#else
template<class ...Options>
#endif
class list_base_hook;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class O1  = void
   , class O2  = void
   , class O3  = void
   >
#else
template<class ...Options>
#endif
class list_member_hook;

//rbtree/set/multiset
#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   >
#else
template<class T, class ...Options>
#endif
class rbtree;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   >
#else
template<class T, class ...Options>
#endif
class set;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   >
#else
template<class T, class ...Options>
#endif
class multiset;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   >
#else
template<class ...Options>
#endif
class set_base_hook;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   >
#else
template<class ...Options>
#endif
class set_member_hook;

//splaytree/splay_set/splay_multiset
#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   >
#else
template<class T, class ...Options>
#endif
class splaytree;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   >
#else
template<class T, class ...Options>
#endif
class splay_set;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   >
#else
template<class T, class ...Options>
#endif
class splay_multiset;

//avltree/avl_set/avl_multiset
#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   >
#else
template<class T, class ...Options>
#endif
class avltree;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   >
#else
template<class T, class ...Options>
#endif
class avl_set;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   >
#else
template<class T, class ...Options>
#endif
class avl_multiset;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   >
#else
template<class ...Options>
#endif
class avl_set_base_hook;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   >
#else
template<class ...Options>
#endif
class avl_set_member_hook;


//treap/treap_set/treap_multiset
#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   , class O7  = void
   >
#else
template<class T, class ...Options>
#endif
class treap;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   , class O7  = void
   >
#else
template<class T, class ...Options>
#endif
class treap_set;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   , class O7  = void
   >
#else
template<class T, class ...Options>
#endif
class treap_multiset;

//sgtree/sg_set/sg_multiset
#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   >
#else
template<class T, class ...Options>
#endif
class sgtree;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   >
#else
template<class T, class ...Options>
#endif
class sg_set;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   >
#else
template<class T, class ...Options>
#endif
class sg_multiset;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   >
#else
template<class T, class ...Options>
#endif
class bstree;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   >
#else
template<class T, class ...Options>
#endif
class bs_set;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   >
#else
template<class T, class ...Options>
#endif
class bs_multiset;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class O1  = void
   , class O2  = void
   , class O3  = void
   >
#else
template<class ...Options>
#endif
class bs_set_base_hook;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class O1  = void
   , class O2  = void
   , class O3  = void
   >
#else
template<class ...Options>
#endif
class bs_set_member_hook;

//hashtable/unordered_set/unordered_multiset

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   , class O7  = void
   , class O8  = void
   , class O9  = void
   , class O10 = void
   >
#else
template<class T, class ...Options>
#endif
class hashtable;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   , class O7  = void
   , class O8  = void
   , class O9  = void
   , class O10 = void
   >
#else
template<class T, class ...Options>
#endif
class unordered_set;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class T
   , class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   , class O5  = void
   , class O6  = void
   , class O7  = void
   , class O8  = void
   , class O9  = void
   , class O10 = void
   >
#else
template<class T, class ...Options>
#endif
class unordered_multiset;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   >
#else
template<class ...Options>
#endif
class unordered_set_base_hook;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class O1  = void
   , class O2  = void
   , class O3  = void
   , class O4  = void
   >
#else
template<class ...Options>
#endif
class unordered_set_member_hook;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class O1  = void
   , class O2  = void
   , class O3  = void
   >
#else
template<class ...Options>
#endif
class any_base_hook;

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template
   < class O1  = void
   , class O2  = void
   , class O3  = void
   >
#else
template<class ...Options>
#endif
class any_member_hook;

//Options

template<bool Enabled>
struct constant_time_size;

template<typename SizeType>
struct size_type;

template<typename Compare>
struct compare;

template<bool Enabled>
struct floating_point;

template<typename Equal>
struct equal;

template<typename Priority>
struct priority;

template<typename Hash>
struct hash;

template<typename ValueTraits> struct value_traits;

template< typename Parent
        , typename MemberHook
        , MemberHook Parent::* PtrToMember>
struct member_hook;

template<typename Functor>
struct function_hook;

template<typename BaseHook>
struct base_hook;

template<typename VoidPointer>
struct void_pointer;

template<typename Tag>
struct tag;

template<link_mode_type LinkType>
struct link_mode;

template<bool Enabled> struct
optimize_size;

template<bool Enabled>
struct linear;

template<bool Enabled>
struct cache_last;

template<typename BucketTraits>
struct bucket_traits;

template<bool Enabled>
struct store_hash;

template<bool Enabled>
struct optimize_multikey;

template<bool Enabled>
struct power_2_buckets;

template<bool Enabled>
struct cache_begin;

template<bool Enabled>
struct compare_hash;

template<bool Enabled>
struct incremental;

//Value traits

template<typename ValueTraits>
struct value_traits;

template< typename Parent
        , typename MemberHook
        , MemberHook Parent::* PtrToMember>
struct member_hook;

template< typename Functor>
struct function_hook;

template<typename BaseHook>
struct base_hook;

template<class T, class NodeTraits, link_mode_type LinkMode = safe_link>
struct derivation_value_traits;

template<class NodeTraits, link_mode_type LinkMode = normal_link>
struct trivial_value_traits;

//Additional utilities

template<typename VoidPointer, std::size_t Alignment>
struct max_pointer_plus_bits;

template<std::size_t Alignment>
struct max_pointer_plus_bits<void *, Alignment>;

template<typename Pointer, std::size_t NumBits>
struct pointer_plus_bits;

template<typename T, std::size_t NumBits>
struct pointer_plus_bits<T *, NumBits>;

template<typename Ptr>
struct pointer_traits;

template<typename T>
struct pointer_traits<T *>;

}  //namespace intrusive {
}  //namespace boost {

#endif   //#if !defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

#endif   //#ifndef BOOST_INTRUSIVE_FWD_HPP

/* intrusive_fwd.hpp
ZnMzFqqFhzuOmKH2aKh7r1XpejJxX+7andGRPBMT5rGKAX5O6OI+2YvvnMHYk3XARaydJzK8qCp62dpA5zMjnb5heiRS6IoGX2TrQcEcn+aoIV9fwjhbBpOdhOxCpp3tcMoajjGkHGFcb0bP4PpZRiYNkC5JpOWGWaMPpuVAZPyf4oo3cOFmSz0+bFm+32aLuUYQH5Do5CT+1ImuBX0ghhoLFdgu3y1G/ECLz2SHL7k9CP5gba6Hc5dooFm2g/Em1K3Y0KXK/KaKMLfROk93VhszuLmx3TLAFJtFDtINXHigBPHEfe2tO/Y5jYyIbPG3NXEJhnuFzDdqjq3wzGriRAS37F/aw/CyNSobaFWgtRqIUQYqbRY8Hfg/4QMuItFlnIBqpN3F2PMyclf0r74SEl4YJc+ft2KQnGcgycahfbkYVAr3Ufc8HQ8L88nDRrRiw+kKFGjEhnDElTgut88i9IBzaeTiTdtt/tjKlLbwS4nidAtQXEtdtMI9PgBCtkNXfcag0pyqbOkb7ed8LAuRtgDry3dwiGGrfa7IrCDtDWzNwFagutoDWgh5c8W81IVWXjYj0FTppZSnBfBSMKxU4nhp/0SDcnWmx6W4N0tVdCXnNdpWPD+ErnW3ICcgOZ/pcyJWFfiXAT85CsndcFtjTYqa9rdW+OmjB7A7ZhcSPjCCr4GLHUlWxAdxCj8c1SmtA+7QTdrvcF8URrDRPwAFaWAQFAAAAAiA0ChtEa2Yd1oGtv9GVgAAHAAkAF5MgkzMrCLsorQMzKwctCwMJky0QqyMgrQiokxMYhxirMKsDCI+9ComRubKNhbO5nRyJs50xtbWUAAEAP97AAEwAPy9j3WWWeYA/d/CGv9nEey1IFb+szfe0N7KqovvHexzpRabJD6CWhJaeCFspBdBrd3S0DYBSudRYQKSS1tsLDO07JTNBJtqgggKDx35EorOouqiougIxwfAwy4hqhr3A0MmI/IoouioLgf8Trc9kprzLn17bX13bz++fwKnuRlOs9PZnMxOp8UW0mZ7oijBCKTddbqkxuCIekfjfb4u/VvzfmkB1vAe3A7gzCc3w5NiaWuLRPewgUUbh87uPN1zSlMawWpxIycNKKmq/zI/uOh4aWTYBQ4ZbYAIlTFAMb9MVkgy7iwGyUKZNM8BRKgXcy2A9BOCC13XTUV7ICF5JvgSemMY6msdpiAj8v+A5f+CeqkC7mAsGMdSBHFXCLigcneCzw8cvAEJH/oGyH7TRuq4fCwA6eEGl3y0s+Bzt8ilrzKJLneiRr6dB6g5IoqxzyWW73M3nbY53vPo7G13KS8juZR1U9aisfe0Zroyh80YcwqJgBsFyg6Cg5+x2GeIMn71um2nu09CbpIiT1lsuzxf15egB73VxXs9erfe7vN2PZzmei+K8Kj6LHRiX1vx73a9TOe+qFF83nTcSe8UjGQ3Y2+n4uS3uK8ivnppPY1stvbGYLoqap9nBZFva3sZjw9eRgMs9Faufv8p7R1wWuSmV3G03bhb9s3D2zaEBqfB7bJZqWz2DsVN3z1l2A41zLm9GaWFBrHDhJiB8InXK07F95diQC7A1twGNEaaOM+7Z1QqlKbbrxNl5MswRh2JyOD0Du9VFQ55ueBDH6JB7kQ2k6gRMgQ33+8rcFXIQwgLsSCdV+tw8Ijh0MWiqQ+OEcXEoqUNvwnCGviIOeQcDo7WQ2moSuGjNKP14Y3iGV60iwI2iGlEMv6LhBQfAErNIGnKNAGywTHt8UnQoKGbxA6b4VvufShkYiw0sGeqQirjedoqU+BMSNT/wAyZ27heNFdhBjyF+HGQ/SEJSeBJTreBYkL5RoSxiF6NWG72rY6HEg6RAaBkkKSNTtXsZGETKwuF5LBrx+Abzeo/c3ncFhwAgtbPJCJFzFSxLieTLTpIsm+eNnp+cf/nlxMmWLR8PyGBQdBU2B25D8m5eY6LMUx9hu4OK6RbIdYSih9NQTVSBjB/LwygOVexIMbYaGNEkjUqNcdnOD1fJjQBL5plGk6RFzluXxEnLwzzYmQuhXRDs3WvqZktK6qrtsAD2zyusNBQjThovI0A58+Oy0GHeMEjo3ql4azlopn+Hh17PJBvqfiB6Af8OwjMQEsjwe20Z+6kfSljpGe0DdbENIyD34Z2PZqOHA25MPouHg3JKEbav/5btNZvD5bpM7whRqojD0WiwKrw9YpPAi+BCfbMYKQ9LeOUzTi7/ganLtbGRjICplKHK1oZXZkMY96saSBUnjonEmR2UMpD8aW2eycYlWxtvrOMjm4T3V0I9mpJz5FZCyyZnJsIXA7/Gik5EaJ2K5RO+o2XcVyQ71vqO4g3LJZf2r5m2uJGwscyQHaOb9Na3Ir9hU2LPa1ZpPausDrINVeO2AsyXY7WK3pIsYzyrcIOwUVnFKZGYejptq+AmRBdUjKKlEECNqrZL4ZWNLL+B7e2jl2n23OJG/QZLFI3M8w7L5opLMpfRPVgtMCgN0D3m6lmIiPQbs+EAVm+klWhQV9Juf4vP79ULUdxbuigzKlE7OVWemKMMhEZEvlHGWXhtwHZK5YVY6gYFfNFbCjQ3JdHVdJuWRR76B0oMhgihUZnkUdNV4lwFlb2Btpn0dHrDVM4Gss3EB+ePXTvgOny1n6GJRQIwUQMY6goBnFhPYUJUaxgHsIjXwIStnC+Irn6R10u0xSdl0XudZ6lL4woYtHLo1zMXGQJZeHUwxpt6ZTUOlWfOTMvGF567KeP+Nt4k/OfIPpefjw6P+jEaDi3NvS7UmZZ6eFljMSFnltQCE7gOqVwIuWmdSybeKkcS2b9EgYntQnWYlG0qdGyDLNMQIg4VtH7hXtseMcQDZ9RjKKVfgfMDAHDKMsSDiT8fuLDt2TPQnopI9aHY/prQmidAHeMiJE4dtFTLhB8DNsYRTXlqHkvEu1qcfz2AI5VtCwzllHIGUojLCojAwuZjkW0ZNWb2kE63ygfQwPW0ggMCLPDRJOCoFGeSXq/BmOcF+FcedrBAhmePQ8JuouMaXewyfy0eFZGO72CZmXa8LnSkEaElxRN7NqLTAaj4SQPJt+51J7gIJ7CklV/BHkJzeycmKj59z27PjMX6Cx0yybWSpI8fsKcePx4Bg3PGhhV1q3S5UjkHeEJo2AJhvwSb7OWqmc4YGjIa4eWintyIqI1TC6JJZsJHB4W2AhB+ZBh6siRYVEq6fvcb4G8bhxUmUr3P0SScFERfp6i4Cv4kWGZuRkODva2fuRYnKJC9ZR85SUoAVwOK2HWZqRwyYyoBvxBMeXdCpNEhIiBt0iAIAUTeDBPtSwmeGpMFTFakZdrWCPh8lVyI3BISCkP9MAtYcwLxwZP1gX54tbgV+DgTaTZE/cLb7n43J9hJ01dF7razk5wqJIriOJdEmUPCN2W9ZL9p3rZrwCNRm1YEult8PFgQKQBKuRqJEIdsmLpYMH368Tg5KI784I0pRAqbVPY3FsG+3sXcLheV/1JF/BSbW779OopBsk0wvduYAjh4ffBsHlIZaXTo1gO+7xQCSObR+MsEQwqXuUSs0weghk9dTrkOgOxA759zKOaEryC/i10DiS9sAj96NCwTDH0obWiYbBnhIRFdgFGSiWsC8WlPnmM9jmK7Yz4ZMZ2ysnyaYh1canLPfHiiXYlkQYyEJ3KYi906mzhLGMDNMEq8KMgrwPK5nvXAszQxVMg61KwEEUUU23J0MTqd/hxBTEz8xS07+EBPgWFinwwGPD8Yo3MxLXkA8alYM4lWWjh9jIJqZGBixyqlbRCmYrgOLxJz6wHgNBo9BruCvF8wf5RmJHtlMAqCHLCBhFVuTJh7oDyyGNXJEXBXKND/ZmI+XmCv+SEcz+8Y3wqGnDcHh5V8ChAl37OmoJBvSCusdfbaCVwLmhPVyyNBEy81stkoUyKn+kSstGqtpBcKyNgHSMvZw90JXGYQ3rWH2J3QAAFcoIV6Y4UQ32N5W54ZG1MCsrEVQFHsxFDYwpcdsyy5kVLZla4y2TR5Y2eqIWmFW9sNQxv7lR8LF9Irhdx++rBGggFz+pGSn1jl+L+gODkknSkle+Ye4iDNMVX0saEGhciJEqalLDMAZPS/PcshIXSUQFAT+aCkrbEO4EMql5kfE3FZwuEGtAFTcVmCojQQhIXmD1RUDBXVs32JLosJVtB7l0q2yUJy4EF8+4TCjkblSqPcNAdyRwu2Mxk7lGJX5SHIzRmd8TOdQmxTxyxbuDELsCxuS7dS1E/uF2c+ULABUlnHuoqILMTDFHN8vSk961w976WKcgJOpNymIx4QkQmE6HSZ0hAXm3QvwcGYRnipvsCqQ5BHlClyoeMAU91Q9aD+HhVX5HOKCHM8DwrzJ62oibKZRpatY+VZVwly5KE4PXwHON4mUTRxgO+HGFHSTyHeM1DEpdg4pd+aVCOn+yJ8UHWe9x14APhFm/Ya/wGNHp94Dhjg40OMJMGt3ZDM2VL82a+Fv4qHfTShdFZtbBnl90mRC1G5hXCnyGr243ymIyKtcH7aHjW3ZZgXeWKWwRfc7PwC+5h4e1qwAJGgPMMgOBfCQk4omIig38IhOCQxEEQoBIUUETJhAVEAhib0q85hwwo0qjxZwX/Kv1lBBpUADP8DSuAmABHlECNgSJLoEAmVv1vICFLOh7BzqU6oN+ccV+zxlPMyVNHMM4ZC21YF35qsFm/dwQiduMd4TPtvEeKH6L/JSr86SQn2ErPtZ4YHyNoGgj6kn1NB5MI+5cK9qwD3h1D5e0/srg7DOMTUJwKM8nWVhJ4Zr1/WDkqqkK6w0WAf7vZp5PFuT21BKzrm1p7GktAgE3EyZBFoEETfeMsg9zRRGO7z6HwoxPmkwRQRY5iENeiOrEHCAN2K3zjpCbsQl1EdBHyrRjjJI2VT4BATVFUg5UTxy2wTf3i6pOE9JmxN4IhVc1TLB/bjhj6hwFeSgQ+QjWvVfJa4nKW/xZpyrJZdDVbLqqXrVRE5AxWoLAptwcOyqLcFt77QA0J0QPIFNv/o1CKpLSGPhHqMZalsPxyPA8qsHwkDEkTfsIAllwp4mM/b+hB2QR7ZCkhCfkRriPGRJGDxkYtJYYHUkmSH7K/hQCutc0EVOfaUzCZRwwY9AKsnEDcxEaKtf/n7tieiaLEkaOEg8IWZme8Uhy1eFeSDE4pEy6Q2wpxrCZzIOMPtoj2wBzdxw9k805hwy++1VVQQyx+kZ6U7MsH9GEeDWFEIVNmH43ISc88y3w5TouyK3rwg8IneFAFsHLMy/WLzPUbiegmYjb4qrCEbxDnKCtByXKwO1OWTCbVMbZssJggm/yIFrKnmG4wurtgur2EidKa7rByl64YSYd0s0GeuAlC8PCFIQY7tC8PFyqUPb5uHllBao00IkRiDTby7G8T+vHyzDxtD6lFZECTLIFoDKtP6E9J8QoxEu1sCrIB/Q9jODLCMIwCTb5aZTDsGEjiHF4x2IcfGE0skVRmjoAtPrr4H0vQ03VxpjMTojHDSKMErM7GDcJd+MqS8h2Ifo4Mm76lC+2/jk4jQGSw+pBBVyg7IIq33UkYkHakfBmNKRjAdwCBjMaEBqBrsPH4NMzo1SGZXvxYI3RAa9M0YO9QH5z9r+soAGWUOgBvbUaEfT3UPOBm6j9I1w1stDIGpCZCuYF4uxRej0mkIRW40k7ixMF//jAVSgU08P0XuFnmX8GWtPNzyuUKxDgls+QRxkGfvmQJOMr8YMlTltncckFHZ+YKkQJbVZTfYk5wnsTN63Lg5qa9zH70P8cXsCtqo3QfcIZbGQf+uA0ErUJdeZiwXT7ZhnbmeyZQgNy0ryO5hpGAX5NxsoAyKRRGSxGJIl8NGfteGr7WeMdjUJE7UP94jedUUbyCYIyvDOLcSMCOQ5J8IgA9Do4VDAV0OTjxSOgDvZGGkRtdlfzNSC7SSGrLk3WAJnzig2dM7MCs04NpTdQTMBKJDazWuQGw00ik29OGkerwvTAuE2UXx3Ouk0gCeAgNwDdsivE3yAz8zNyAWoUHHVHAAbzEl2mKww3HRviYhB0Q6sONEbOK3KHrpSCPUMQJfDtJrXsOMa7/2ohKd0o5QKV/JAdfKWaBSnEIDP9K3tGIZOkNilJgkmSIKF2pMwpVgFNpDJqSPcNhs4JpFXpBGTckGtjT5UoSMEUuzTNeKJvUNGTAkOlHdIFpQjFlRhcSrsa/6xlEoSqSGUYRSiWIo8LAXufEVj8bkEbFXN8bLuzP8cr+kXPWZc8aJ9BWFK7yU5oJZP8Rsu4nbBh3BReEGSftVADmjZPZfTCyvj9i8o8ydgRLIp+RlkMVcMEk1BNWUvpnkNBgf4rF9yKxAf5njCG3oHyIJalGuFq48+1IJhI/4SrFkhSNk5fdRFoSMUXJJHzwq1YDdkuQXNVGAE8T6qPm2UNpEuvxC+xgPAQGny9dpv81Sg4aruDof5FY+3fGRxOHkUyX5gKtK0Jiw/t8HAcHy4b2ej/KQ1YF9z6ImKAygj/HkINBfvV4EisLFJJeK78s+b8kMaSckvaDSf4rPjXpt1ZzGEtk/TIgd9UC/mJI+LdoYs2vLNKqfO2bWMs5nhw/blBIHreMMmThnMa7r5E0TubV30SWYHaTqMPiypTxrTiosvk0bdwoP2jYEmIMxUliMLFJ6Y+bUs9zTk1KTlIN8Sk1Qf7qLy5HmvfVEDWtUjiB4DJQzZETbBauyW5VJxAakVZP6p+S1AyzMJW3SrUOtUj2cjN/uU71mBHcA0ZcJalTGo4Lbg3GSWvgBw5zJRn6XT4CpYIZeIPAbxyR0ErbjLtYVRPvCa40OW+1ufb48d9ZCzKkLT5R/i3qonhMW/MbT3QTRK5fFT/vJ8SgtCqF89+aSHphPOrhhfJnaeG+Wj1nUbJDr4hrL0QSuJfhNx4Dbvo+Z6L+vO03JZ/R+XWRm9jNR9bmfJFzPepUPoEnO7aiG094bP6GDuIHEhQtCZ7o+7txZLPlgBBboIZcUWjLH5hCtSm944RwU27DM4R6JLXGKbkHDjIDEK9HAagzpUF68g4RsCBhypXZQ4W8KPiFXLnVuyJV+UFTuPtuSib68gfZw1eVNeGgvBbUB0fP942EMiQ9i2sQK1fxw80XzZGLjZb9Bd8M0ayhJyKcykF1vYjvs4xqEE7r/pCyJXgAn4ol9p37hb4y/gjuf6P3ZAL+evL2P+ULQ664cgVh4npookCAU4Yq5ODKJBHCbuaECsW3g+0LnUIKpxLhj8YpNDOTwxyhQGcwh1JGyo2i6ALW271rGaeYA+4zSzdEYuLy6TXEKj0TNAgmyFcO8UbOyAi3A9y03o8ApIXsVbvHauD6ZhXCX2DrSrgyZQ2tUWlPKx+UD8n5052yQsUFjzHAnRq/S/nnLe3iD7FT4ETzGWJ7JElGrhe7J2GCMOTBxLjLJEgw3HGmKyLKU8cy3Yajo/yJsnJObkMd0Qt9STpi7svl9yE2yB8Q2Inm50Igb0Aj0mTPqhOzTBJatysqHDeYJ3m7JjKCna+MEheDUDhMIr3SGTUuDvAZ80iYNnBHC6fQvXbvlmqPH95am+4ynVIcXfTCIPQEfsz/q7k2XjitopAnRrbjGq8uu1FN7sXc1z4xZVPbAUCQz5+p5g40OJTsmCiSIbY7t1PjEx+zM/Wr61XNEHXz4I/q+ib7ar6wTX9hXxI7oZDCFzBDXdSwazw4Rc8PF/w0ZdvAGcrn4065omhjpsmlNFtPyOzJZ9486Pu3/EEUkkZpTc6ewa8cSrFI5AfEnW2oUklorHKMWv4qDXja9ERslOyDImRcPTlOE3FdJiSPUb4oZGIZ3IZXKUSrkuwAQBwBqs9TokXBG9K6ZM4d1epk0RXUaldyk8KwJnBLKivD9ZBo6sKlIYUGKEPaVrVYcDgDZk42AnAUDq3PdAAoV3pDpgROLJ44l58j2QmohkCtkG0cypVhY1go2QtUIBwsFZyDMqtOeJ1vzxzyRckjTFgk5p4pVChoXmCPE/JEeZ1fnzXoY6glvYWiKXTuDoX5ScqEzDnhO9oYGQQV5Bj9CHuiPqmgWjwJlRq8BM6UD+foQbH8bKAvCxwNFyaVES+zCsyQhvp9z2fCoy3ERo0MWGsCBsgjogTIV9QMuC16gD1p7X9HIQ7AU0MzbGddfsrA21GjRtgdNjjGAtFmUf8mOpOnfwwH9abwznXjkzXYp/BecEoxD18pD8BT9gGin/LK1M+pee0CZGwgCsVTdcA3FZhmDpB5LrsJEw+qBxniihLSUG+KxkQy2PsMhwv+OxBIngFINkgBRvVCYU4+xBsU0n4FPA9XtP8NQt1Q//bzABLaQDNRwAA/yvQvDggHFJULWjfwbZZRIaHJfkqcIxVmYItKgKNtYA+j/A4BbdAmmxQURY5gyJ8pYdAwfiKRKLCtX5IgKcQ71p5peZFGRYlTIA8qUaM8G0FtqesTxp8mA5IJkwmaQNo0yDh0G+Be9ZW6VUSj1Fp5t9Zb5SPZ0RTMN7D0GoEfmljku5oos0fA0xcwgZDNE/FGcqoL7sYsMrM/9x5LdXKtpbODsTjRiU2Npcs75kKZU88zZ0t2krOurv/AVf7fsId3z2fDHH9+Y0+IcHHIm3sHnkTI3IHVSyISTsbeYSXS9hKIb0JVLLII1mzu4eMnB7yC8aBI2BRvwcxEy7t2d1iyOxrndi3XdXIHGNcJJUm7FpLmrSNbKlBV4ima7j0nj1ztGdY38OPVJcgstVz6PAzIZM38gdN7iqhQCrxnZo+crn2XpaQot/mODJm7JuD7C2WVTj+nT3HxPGilO26Lbaz/a422LCzmHGs7T7G/na2DE18sgReTIIJ7AEoA3ZJ7c5mRQ4j8Ps6M8SlLWF1CMitiM2gFkraIEiiNROkjn7oPd4XDowuOxb43K+h6uUUoKweWiFTFspzbp4B/uZWnR9XYmeXpIjXHACiZzmE+1Vu/FM8LD6KLvQcWlDv8zyY1BQVdNJVsyQSQpWZQKwopuF1DG7ousOnrRxu2eBo4cncPZOIuqUmiVH+/HSHXehzrc7+CXD35eKIACiz10ydn+LCvaRN3eQZdZm8wXykXWgfWOd3qO1aHY+ws3XEOk3jk0bc+zpd0d72bfqvltrf18Zd3YFXrylgEiqQu4J1rkMbA/e4zkXbjlKT9y9PN70T4oNqUolibllj3gERBFJMjxM0Ts0Q=
*/