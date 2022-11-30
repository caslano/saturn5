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

#ifndef BOOST_INTRUSIVE_SET_HOOK_HPP
#define BOOST_INTRUSIVE_SET_HOOK_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <boost/intrusive/detail/rbtree_node.hpp>
#include <boost/intrusive/rbtree_algorithms.hpp>
#include <boost/intrusive/options.hpp>
#include <boost/intrusive/detail/generic_hook.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//! Helper metafunction to define a \c set_base_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct make_set_base_hook
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
   < RbTreeAlgorithms
   , rbtree_node_traits<typename packed_options::void_pointer, packed_options::optimize_size>
   , typename packed_options::tag
   , packed_options::link_mode
   , RbTreeBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Derive a class from set_base_hook in order to store objects in
//! in a set/multiset. set_base_hook holds the data necessary to maintain
//! the set/multiset and provides an appropriate value_traits class for set/multiset.
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
class set_base_hook
   :  public make_set_base_hook<
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
   set_base_hook() BOOST_NOEXCEPT;

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   set_base_hook(const set_base_hook& ) BOOST_NOEXCEPT;

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   set_base_hook& operator=(const set_base_hook& ) BOOST_NOEXCEPT;

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in a set an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~set_base_hook();

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
   void swap_nodes(set_base_hook &other) BOOST_NOEXCEPT;

   //! <b>Precondition</b>: link_mode must be \c safe_link or \c auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c set::iterator_to
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

//! Helper metafunction to define a \c set_member_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct make_set_member_hook
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
   < RbTreeAlgorithms
   , rbtree_node_traits<typename packed_options::void_pointer, packed_options::optimize_size>
   , member_tag
   , packed_options::link_mode
   , NoBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Put a public data member set_member_hook in order to store objects of this class in
//! a set/multiset. set_member_hook holds the data necessary for maintaining the
//! set/multiset and provides an appropriate value_traits class for set/multiset.
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
class set_member_hook
   :  public make_set_member_hook<
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
   set_member_hook() BOOST_NOEXCEPT;

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   set_member_hook(const set_member_hook& ) BOOST_NOEXCEPT;

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   set_member_hook& operator=(const set_member_hook& ) BOOST_NOEXCEPT;

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in a set an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~set_member_hook();

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
   void swap_nodes(set_member_hook &other) BOOST_NOEXCEPT;

   //! <b>Precondition</b>: link_mode must be \c safe_link or \c auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c set::iterator_to
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

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_SET_HOOK_HPP

/* set_hook.hpp
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
*/