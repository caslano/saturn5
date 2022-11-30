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

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_next(const_node_ptr n) BOOST_NOEXCEPT
   {  return pointer_traits<node_ptr>::static_cast_from(n->next_);  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_next(node_ptr n, node_ptr next) BOOST_NOEXCEPT
   {  n->next_ = next;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_prev_in_group(const_node_ptr n) BOOST_NOEXCEPT
   {  return n->prev_in_group_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_prev_in_group(node_ptr n, node_ptr prev) BOOST_NOEXCEPT
   {  n->prev_in_group_ = prev;  }

   BOOST_INTRUSIVE_FORCEINLINE static std::size_t get_hash(const_node_ptr n) BOOST_NOEXCEPT
   {  return n->hash_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_hash(node_ptr n, std::size_t h) BOOST_NOEXCEPT
   {  n->hash_ = h;  }
};

template<class NodeTraits>
struct unordered_group_adapter
{
   typedef typename NodeTraits::node            node;
   typedef typename NodeTraits::node_ptr        node_ptr;
   typedef typename NodeTraits::const_node_ptr  const_node_ptr;

   static node_ptr get_next(const_node_ptr n)
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

   BOOST_INTRUSIVE_FORCEINLINE static void init(typename base_type::node_ptr n) BOOST_NOEXCEPT
   {
      base_type::init(n);
      group_algorithms::init(n);
   }

   BOOST_INTRUSIVE_FORCEINLINE static void init_header(typename base_type::node_ptr n) BOOST_NOEXCEPT
   {
      base_type::init_header(n);
      group_algorithms::init_header(n);
   }

   BOOST_INTRUSIVE_FORCEINLINE static void unlink(typename base_type::node_ptr n) BOOST_NOEXCEPT
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
   unordered_set_base_hook() BOOST_NOEXCEPT;

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   unordered_set_base_hook(const unordered_set_base_hook& ) BOOST_NOEXCEPT;

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   unordered_set_base_hook& operator=(const unordered_set_base_hook& ) BOOST_NOEXCEPT;

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
   void swap_nodes(unordered_set_base_hook &other) BOOST_NOEXCEPT;

   //! <b>Precondition</b>: link_mode must be \c safe_link or \c auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c unordered_set::iterator_to
   //!   will return a valid iterator.
   //!
   //! <b>Complexity</b>: Constant
   bool is_linked() const BOOST_NOEXCEPT;

   //! <b>Effects</b>: Removes the node if it's inserted in a container.
   //!   This function is only allowed if link_mode is \c auto_unlink.
   //!
   //! <b>Throws</b>: Nothing.
   void unlink() BOOST_NOEXCEPT;
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