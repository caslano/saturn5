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
JI/aeWAWxx/DyB9/FNxeaT473brSm2rlpqZaZXAtcN+AexcuNy2Vb3CdtK/UeYd+Ou+EjY4N4Tot9SLhg7Qt1r98nlSftQDuo3APw52C86T5rEKuDV8epnA3ej8LbYPfsqdZXTyrsSt6UtokiJB3Lwq3yUCFj1+HBf8xbw/rKWuDPRI6krta/T0+6wbPU9b13j4cN9XfxvLtpZEDU5RH+uJkSe8nqbznhT+eN5GH8yTcH5NOeQ2WuJvKG6oknTNIZ6bgfS81Ugf19ZaqA6bTR8JnpqRaBZ7+nnuslzx9rD96Jli13pst23ef9UXfp625CtctYwHUOB7F2+aZ0FPaCzq/0+w3Ua5B3nTrmHeS1d03FDZCfFZ2Spq1Gu4zcM/AtcJlp6a57TVG0npLo4tnK+T5e6T+srmfY30ih+5QnLPb86q1yrtY3vSfRhnDdA1M7Yw32IM9I6PX1EzvBxL/DisXpdlt+dx900LxH4uaHGBlsK03DhcdAVYh875RvkdgpzcT+hpWWD/CHq0/3vwXcJ92g6TxW+900PYQaLvJuzgJPnhF+CCbZZii8MBVFdD2qsr1TlS5HlXlihvPRpLe94TPu6X9C3PP4/YGu8Tb29M1NcVaCXcX3FG438F1TUtx+ecWKdNSlCGWzmUe0Kbq190XvCG4Pmm71z/An+RXkMb9j+Ip2VxkcI//otCdaWWTvsYR4X1VmVVh9eWe/0eCc4cvE+PaaIx1rai7ld5XrVG+xQloego0TRcaToGEkRL/Vxr/SB9y54UvjwzrQUgh3ScRZ6HEeTk10mfQX/Q7vIybO4JnkOSR08Xy3SYvFgquHjbUUwUJAcMVDbLHvVJo+GYqbUaruqsqr6tYL/M2x6UdCgdj0lZw8ivglY/40mPHGXeesLR5okzo7uXu8X4r7TYdPdryOHNHq+B43LYtkXrKkb7UmoDnmI9qYpmjX6Ms4QTmnbenoxbVPOcZGUjHFsOv2ZD8izMnEjd9BuepThfE7fvyiFM8g3tOb34AQ4aL1xqDdyfw1qh8U0NvBrzpLt77aDC5C5br3qtw2/FaKdsCt63+Kd/1vkzU4XG05RjwX1fwn07z0RnOPL5zgE6LjnNqhrMe2HlZ7HqgkDjBmU65di4NpPsD3mEoXsDbybiXZpxxM7kW6bJze9xahDirZjp1urNWr1MdJwScdwVn94Q4u9vEOeDQl77zzbj1CnHKZmEWUuuVXT1T073eVE/Amxfpf5tVXbvjbbbw3kBvP+tezJfL7IHK3x1LbvfkYhwNYRx92YKuMXUjwZ5vLbH723mRMaV8i3avJo88/YH0r/HeqdYn7B8h3QLy8QxJt9DbH/w/A+PaPVaDRy/fnlmsp8AuT6J6OjjLaetdjyRq6+PAqVQ46buaHZyqYDROaySdNxOlE5ztrDN3+/W21et7ymz2rc67ewe8XVI7Bzxd9L6l49YAd63I9HZ/JuCDsEbrO92yo/Nunu3UxZ6tifrh47MdftgzL+DtbCUqx+tOObrueTgBj4oC43WKtrQ9Bx2c9TF1NmWOU9Y9P9DKGL0eJg88KmNYZhS96+c49N7Q3Ba9e+c4feGGm/S+oNfliTnhdXmqx3tTZ7Uux4JYxW+G//E5rLuUmzqb1tp9mcb0uW4aN76e6g14ff7BTCr23oA7Zx0dpco1ysoCD6tynUReU+YyP9+NrwdSAnHjpk53k5bnYxrds+G/By5M942PGfcITOM9puG9cS/6t8/rT5WEEtJcIzQXWxmkeS/in4nQfFsgJdVEs9sePeex3fw3Xqe3mU5T07xIuRb6R/v7sWw6TfracZjQFBB6ihB3DxzpWYhRt016Ds1z+u6NxYnoyZ8=
*/