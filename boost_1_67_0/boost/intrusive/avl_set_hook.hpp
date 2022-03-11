/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_AVL_SET_HOOK_HPP
#define BOOST_INTRUSIVE_AVL_SET_HOOK_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <boost/intrusive/detail/avltree_node.hpp>
#include <boost/intrusive/avltree_algorithms.hpp>
#include <boost/intrusive/options.hpp>
#include <boost/intrusive/detail/generic_hook.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//! Helper metafunction to define a \c avl_set_base_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct make_avl_set_base_hook
{
   /// @cond
   typedef typename pack_options
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      <hook_defaults, O1, O2, O3, O4>
      #else
      <hook_defaults, Options...>
      #endif
      ::type packed_options;

   typedef generic_hook
   < AvlTreeAlgorithms
   , avltree_node_traits<typename packed_options::void_pointer, packed_options::optimize_size>
   , typename packed_options::tag
   , packed_options::link_mode
   , AvlTreeBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Derive a class from avl_set_base_hook in order to store objects in
//! in an avl_set/avl_multiset. avl_set_base_hook holds the data necessary to maintain
//! the avl_set/avl_multiset and provides an appropriate value_traits class for avl_set/avl_multiset.
//!
//! The hook admits the following options: \c tag<>, \c void_pointer<>,
//! \c link_mode<> and \c optimize_size<>.
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
//! \c optimize_size<> will tell the hook to optimize the hook for size instead
//! of speed.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3, class O4>
#endif
class avl_set_base_hook
   :  public make_avl_set_base_hook
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      <O1, O2, O3, O4>
      #else
      <Options...>
      #endif
      ::type
{
   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   public:
   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state.
   //!
   //! <b>Throws</b>: Nothing.
   avl_set_base_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   avl_set_base_hook(const avl_set_base_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   avl_set_base_hook& operator=(const avl_set_base_hook& );

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in a set an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~avl_set_base_hook();

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
   void swap_nodes(avl_set_base_hook &other);

   //! <b>Precondition</b>: link_mode must be \c safe_link or \c auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c set::iterator_to
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

//! Helper metafunction to define a \c avl_set_member_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct make_avl_set_member_hook
{
   /// @cond
   typedef typename pack_options
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      <hook_defaults, O1, O2, O3, O4>
      #else
      <hook_defaults, Options...>
      #endif
      ::type packed_options;

   typedef generic_hook
   < AvlTreeAlgorithms
   , avltree_node_traits<typename packed_options::void_pointer, packed_options::optimize_size>
   , member_tag
   , packed_options::link_mode
   , NoBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Put a public data member avl_set_member_hook in order to store objects of this class in
//! an avl_set/avl_multiset. avl_set_member_hook holds the data necessary for maintaining the
//! avl_set/avl_multiset and provides an appropriate value_traits class for avl_set/avl_multiset.
//!
//! The hook admits the following options: \c void_pointer<>,
//! \c link_mode<> and \c optimize_size<>.
//!
//! \c void_pointer<> is the pointer type that will be used internally in the hook
//! and the container configured to use this hook.
//!
//! \c link_mode<> will specify the linking mode of the hook (\c normal_link,
//! \c auto_unlink or \c safe_link).
//!
//! \c optimize_size<> will tell the hook to optimize the hook for size instead
//! of speed.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3, class O4>
#endif
class avl_set_member_hook
   :  public make_avl_set_member_hook
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      <O1, O2, O3, O4>
      #else
      <Options...>
      #endif
      ::type
{
   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   public:
   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state.
   //!
   //! <b>Throws</b>: Nothing.
   avl_set_member_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   avl_set_member_hook(const avl_set_member_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   avl_set_member_hook& operator=(const avl_set_member_hook& );

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in a set an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~avl_set_member_hook();

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
   void swap_nodes(avl_set_member_hook &other);

   //! <b>Precondition</b>: link_mode must be \c safe_link or \c auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c set::iterator_to
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

#endif //BOOST_INTRUSIVE_AVL_SET_HOOK_HPP

/* avl_set_hook.hpp
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
*/