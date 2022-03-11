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