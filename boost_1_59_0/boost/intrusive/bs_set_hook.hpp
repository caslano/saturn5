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

#ifndef BOOST_INTRUSIVE_BS_SET_HOOK_HPP
#define BOOST_INTRUSIVE_BS_SET_HOOK_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <boost/intrusive/detail/tree_node.hpp>
#include <boost/intrusive/bstree_algorithms.hpp>
#include <boost/intrusive/options.hpp>
#include <boost/intrusive/detail/generic_hook.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//! Helper metafunction to define a \c bs_set_base_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void>
#endif
struct make_bs_set_base_hook
{
   /// @cond
   typedef typename pack_options
   #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      < hook_defaults, O1, O2, O3>
   #else
      < hook_defaults, Options...>
   #endif
   ::type packed_options;

   typedef generic_hook
   < BsTreeAlgorithms
   , tree_node_traits<typename packed_options::void_pointer>
   , typename packed_options::tag
   , packed_options::link_mode
   , BsTreeBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Derive a class from bs_set_base_hook in order to store objects in
//! in a bs_set/bs_multiset. bs_set_base_hook holds the data necessary to maintain
//! the bs_set/bs_multiset and provides an appropriate value_traits class for bs_set/bs_multiset.
//!
//! The hook admits the following options: \c tag<>, \c void_pointer<>,
//! \c link_mode<>.
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
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3>
#endif
class bs_set_base_hook
   :  public make_bs_set_base_hook
   #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      <O1, O2, O3>
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
   bs_set_base_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   bs_set_base_hook(const bs_set_base_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   bs_set_base_hook& operator=(const bs_set_base_hook& );

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in a set an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~bs_set_base_hook();

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
   void swap_nodes(bs_set_base_hook &other);

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

//! Helper metafunction to define a \c bs_set_member_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void>
#endif
struct make_bs_set_member_hook
{
   /// @cond
   typedef typename pack_options
   #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      < hook_defaults, O1, O2, O3>
   #else
      < hook_defaults, Options...>
   #endif

   ::type packed_options;

   typedef generic_hook
   < BsTreeAlgorithms
   , tree_node_traits<typename packed_options::void_pointer>
   , member_tag
   , packed_options::link_mode
   , NoBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Put a public data member bs_set_member_hook in order to store objects of this class in
//! a bs_set/bs_multiset. bs_set_member_hook holds the data necessary for maintaining the
//! bs_set/bs_multiset and provides an appropriate value_traits class for bs_set/bs_multiset.
//!
//! The hook admits the following options: \c void_pointer<>, \c link_mode<>.
//!
//! \c void_pointer<> is the pointer type that will be used internally in the hook
//! and the container configured to use this hook.
//!
//! \c link_mode<> will specify the linking mode of the hook (\c normal_link,
//! \c auto_unlink or \c safe_link).
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3>
#endif
class bs_set_member_hook
   :  public make_bs_set_member_hook
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      <O1, O2, O3>
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
   bs_set_member_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   bs_set_member_hook(const bs_set_member_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   bs_set_member_hook& operator=(const bs_set_member_hook& );

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in a set an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~bs_set_member_hook();

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
   void swap_nodes(bs_set_member_hook &other);

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

#endif //BOOST_INTRUSIVE_BS_SET_HOOK_HPP

/* bs_set_hook.hpp
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
*/