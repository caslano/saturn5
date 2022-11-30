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
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
*/