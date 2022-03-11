/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_UNORDERED_SET_HOOK_HPP
#define BOOST_INTRUSIVE_UNORDERED_SET_HOOK_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/slist_hook.hpp>
#include <boost/intrusive/options.hpp>
#include <boost/intrusive/detail/generic_hook.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

/// @cond

template<class VoidPointer, bool StoreHash, bool OptimizeMultiKey>
struct unordered_node
   :  public slist_node<VoidPointer>
{
   typedef typename pointer_traits
      <VoidPointer>::template rebind_pointer
         < unordered_node<VoidPointer, StoreHash, OptimizeMultiKey> >::type
      node_ptr;
   node_ptr    prev_in_group_;
   std::size_t hash_;
};

template<class VoidPointer>
struct unordered_node<VoidPointer, false, true>
   :  public slist_node<VoidPointer>
{
   typedef typename pointer_traits
      <VoidPointer>::template rebind_pointer
         < unordered_node<VoidPointer, false, true> >::type
      node_ptr;
   node_ptr    prev_in_group_;
};

template<class VoidPointer>
struct unordered_node<VoidPointer, true, false>
   :  public slist_node<VoidPointer>
{
   typedef typename pointer_traits
      <VoidPointer>::template rebind_pointer
         < unordered_node<VoidPointer, true, false> >::type
      node_ptr;
   std::size_t hash_;
};

template<class VoidPointer, bool StoreHash, bool OptimizeMultiKey>
struct unordered_node_traits
   :  public slist_node_traits<VoidPointer>
{
   typedef slist_node_traits<VoidPointer> reduced_slist_node_traits;
   typedef unordered_node<VoidPointer, StoreHash, OptimizeMultiKey> node;

   typedef typename pointer_traits
      <VoidPointer>::template rebind_pointer
         < node >::type node_ptr;
   typedef typename pointer_traits
      <VoidPointer>::template rebind_pointer
         < const node >::type const_node_ptr;

   static const bool store_hash        = StoreHash;
   static const bool optimize_multikey = OptimizeMultiKey;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_next(const const_node_ptr & n)
   {  return pointer_traits<node_ptr>::static_cast_from(n->next_);  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_next(node_ptr n, node_ptr next)
   {  n->next_ = next;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_prev_in_group(const const_node_ptr & n)
   {  return n->prev_in_group_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_prev_in_group(node_ptr n, node_ptr prev)
   {  n->prev_in_group_ = prev;  }

   BOOST_INTRUSIVE_FORCEINLINE static std::size_t get_hash(const const_node_ptr & n)
   {  return n->hash_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_hash(const node_ptr & n, std::size_t h)
   {  n->hash_ = h;  }
};

template<class NodeTraits>
struct unordered_group_adapter
{
   typedef typename NodeTraits::node            node;
   typedef typename NodeTraits::node_ptr        node_ptr;
   typedef typename NodeTraits::const_node_ptr  const_node_ptr;

   static node_ptr get_next(const const_node_ptr & n)
   {  return NodeTraits::get_prev_in_group(n);  }

   static void set_next(node_ptr n, node_ptr next)
   {  NodeTraits::set_prev_in_group(n, next);   }
};

template<class NodeTraits>
struct unordered_algorithms
   : public circular_slist_algorithms<NodeTraits>
{
   typedef circular_slist_algorithms<NodeTraits>   base_type;
   typedef unordered_group_adapter<NodeTraits>     group_traits;
   typedef circular_slist_algorithms<group_traits> group_algorithms;
   typedef NodeTraits                              node_traits;
   typedef typename NodeTraits::node               node;
   typedef typename NodeTraits::node_ptr           node_ptr;
   typedef typename NodeTraits::const_node_ptr     const_node_ptr;

   BOOST_INTRUSIVE_FORCEINLINE static void init(typename base_type::node_ptr n)
   {
      base_type::init(n);
      group_algorithms::init(n);
   }

   BOOST_INTRUSIVE_FORCEINLINE static void init_header(typename base_type::node_ptr n)
   {
      base_type::init_header(n);
      group_algorithms::init_header(n);
   }

   BOOST_INTRUSIVE_FORCEINLINE static void unlink(typename base_type::node_ptr n)
   {
      base_type::unlink(n);
      group_algorithms::unlink(n);
   }
};

//Class to avoid defining the same algo as a circular list, as hooks would be ambiguous between them
template<class Algo>
struct uset_algo_wrapper : public Algo
{};

template<class VoidPointer, bool StoreHash, bool OptimizeMultiKey>
struct get_uset_node_traits
{
   typedef typename detail::if_c
      < (StoreHash || OptimizeMultiKey)
      , unordered_node_traits<VoidPointer, StoreHash, OptimizeMultiKey>
      , slist_node_traits<VoidPointer>
      >::type type;
};

template<bool OptimizeMultiKey>
struct get_uset_algo_type
{
   static const algo_types value = OptimizeMultiKey ? UnorderedAlgorithms : UnorderedCircularSlistAlgorithms;
};

template<class NodeTraits>
struct get_algo<UnorderedAlgorithms, NodeTraits>
{
   typedef unordered_algorithms<NodeTraits> type;
};

template<class NodeTraits>
struct get_algo<UnorderedCircularSlistAlgorithms, NodeTraits>
{
   typedef uset_algo_wrapper< circular_slist_algorithms<NodeTraits> > type;
};

/// @endcond

//! Helper metafunction to define a \c unordered_set_base_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct make_unordered_set_base_hook
{
   /// @cond
   typedef typename pack_options
      < hook_defaults,
         #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
         O1, O2, O3, O4
         #else
         Options...
         #endif
      >::type packed_options;

   typedef generic_hook
   < get_uset_algo_type <packed_options::optimize_multikey>::value
   , typename get_uset_node_traits < typename packed_options::void_pointer
                                   , packed_options::store_hash
                                   , packed_options::optimize_multikey
                                   >::type
   , typename packed_options::tag
   , packed_options::link_mode
   , HashBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Derive a class from unordered_set_base_hook in order to store objects in
//! in an unordered_set/unordered_multi_set. unordered_set_base_hook holds the data necessary to maintain
//! the unordered_set/unordered_multi_set and provides an appropriate value_traits class for unordered_set/unordered_multi_set.
//!
//! The hook admits the following options: \c tag<>, \c void_pointer<>,
//! \c link_mode<>, \c store_hash<> and \c optimize_multikey<>.
//!
//! \c tag<> defines a tag to identify the node.
//! The same tag value can be used in different classes, but if a class is
//! derived from more than one \c list_base_hook, then each \c list_base_hook needs its
//! unique tag.
//!
//! \c void_pointer<> is the pointer type that will be used internally in the hook
//! and the container configured to use this hook.
//!
//! \c link_mode<> will specify the linking mode of the hook (\c normal_link,
//! \c auto_unlink or \c safe_link).
//!
//! \c store_hash<> will tell the hook to store the hash of the value
//! to speed up rehashings.
//!
//! \c optimize_multikey<> will tell the hook to store a link to form a group
//! with other value with the same value to speed up searches and insertions
//! in unordered_multisets with a great number of with equivalent keys.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3, class O4>
#endif
class unordered_set_base_hook
   :  public make_unordered_set_base_hook<
         #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
         O1, O2, O3, O4
         #else
         Options...
         #endif
      >::type
{
   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   public:
   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state.
   //!
   //! <b>Throws</b>: Nothing.
   unordered_set_base_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   unordered_set_base_hook(const unordered_set_base_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   unordered_set_base_hook& operator=(const unordered_set_base_hook& );

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in an unordered_set an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~unordered_set_base_hook();

   //! <b>Effects</b>: Swapping two nodes swaps the position of the elements
   //!   related to those nodes in one or two containers. That is, if the node
   //!   this is part of the element e1, the node x is part of the element e2
   //!   and both elements are included in the containers s1 and s2, then after
   //!   the swap-operation e1 is in s2 at the position of e2 and e2 is in s1
   //!   at the position of e1. If one element is not in a container, then
   //!   after the swap-operation the other element is not in a container.
   //!   Iterators to e1 and e2 related to those nodes are invalidated.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   void swap_nodes(unordered_set_base_hook &other);

   //! <b>Precondition</b>: link_mode must be \c safe_link or \c auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c unordered_set::iterator_to
   //!   will return a valid iterator.
   //!
   //! <b>Complexity</b>: Constant
   bool is_linked() const;

   //! <b>Effects</b>: Removes the node if it's inserted in a container.
   //!   This function is only allowed if link_mode is \c auto_unlink.
   //!
   //! <b>Throws</b>: Nothing.
   void unlink();
   #endif
};


//! Helper metafunction to define a \c unordered_set_member_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct make_unordered_set_member_hook
{
   /// @cond
   typedef typename pack_options
      < hook_defaults,
         #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
         O1, O2, O3, O4
         #else
         Options...
         #endif
      >::type packed_options;

   typedef generic_hook
   < get_uset_algo_type <packed_options::optimize_multikey>::value
   , typename get_uset_node_traits < typename packed_options::void_pointer
                                   , packed_options::store_hash
                                   , packed_options::optimize_multikey
                                   >::type
   , member_tag
   , packed_options::link_mode
   , NoBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Put a public data member unordered_set_member_hook in order to store objects of this class in
//! an unordered_set/unordered_multi_set. unordered_set_member_hook holds the data necessary for maintaining the
//! unordered_set/unordered_multi_set and provides an appropriate value_traits class for unordered_set/unordered_multi_set.
//!
//! The hook admits the following options: \c void_pointer<>,
//! \c link_mode<> and \c store_hash<>.
//!
//! \c void_pointer<> is the pointer type that will be used internally in the hook
//! and the container configured to use this hook.
//!
//! \c link_mode<> will specify the linking mode of the hook (\c normal_link,
//! \c auto_unlink or \c safe_link).
//!
//! \c store_hash<> will tell the hook to store the hash of the value
//! to speed up rehashings.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3, class O4>
#endif
class unordered_set_member_hook
   :  public make_unordered_set_member_hook<
         #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
         O1, O2, O3, O4
         #else
         Options...
         #endif
   >::type
{
   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   public:
   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state.
   //!
   //! <b>Throws</b>: Nothing.
   unordered_set_member_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   unordered_set_member_hook(const unordered_set_member_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   unordered_set_member_hook& operator=(const unordered_set_member_hook& );

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in an unordered_set an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~unordered_set_member_hook();

   //! <b>Effects</b>: Swapping two nodes swaps the position of the elements
   //!   related to those nodes in one or two containers. That is, if the node
   //!   this is part of the element e1, the node x is part of the element e2
   //!   and both elements are included in the containers s1 and s2, then after
   //!   the swap-operation e1 is in s2 at the position of e2 and e2 is in s1
   //!   at the position of e1. If one element is not in a container, then
   //!   after the swap-operation the other element is not in a container.
   //!   Iterators to e1 and e2 related to those nodes are invalidated.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   void swap_nodes(unordered_set_member_hook &other);

   //! <b>Precondition</b>: link_mode must be \c safe_link or \c auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c unordered_set::iterator_to
   //!   will return a valid iterator.
   //!
   //! <b>Complexity</b>: Constant
   bool is_linked() const;

   //! <b>Effects</b>: Removes the node if it's inserted in a container.
   //!   This function is only allowed if link_mode is \c auto_unlink.
   //!
   //! <b>Throws</b>: Nothing.
   void unlink();
   #endif
};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_UNORDERED_SET_HOOK_HPP

/* unordered_set_hook.hpp
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
*/