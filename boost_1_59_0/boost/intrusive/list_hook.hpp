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

#ifndef BOOST_INTRUSIVE_LIST_HOOK_HPP
#define BOOST_INTRUSIVE_LIST_HOOK_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <boost/intrusive/detail/list_node.hpp>
#include <boost/intrusive/circular_list_algorithms.hpp>
#include <boost/intrusive/options.hpp>
#include <boost/intrusive/detail/generic_hook.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif


namespace boost {
namespace intrusive {

//! Helper metafunction to define a \c \c list_base_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void>
#endif
struct make_list_base_hook
{
   /// @cond
   typedef typename pack_options
      < hook_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3
      #else
      Options...
      #endif
      >::type packed_options;

   typedef generic_hook
   < CircularListAlgorithms
   , list_node_traits<typename packed_options::void_pointer>
   , typename packed_options::tag
   , packed_options::link_mode
   , ListBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Derive a class from this hook in order to store objects of that class
//! in an list.
//!
//! The hook admits the following options: \c tag<>, \c void_pointer<> and
//! \c link_mode<>.
//!
//! \c tag<> defines a tag to identify the node.
//! The same tag value can be used in different classes, but if a class is
//! derived from more than one \c list_base_hook, then each \c list_base_hook needs its
//! unique tag.
//!
//! \c link_mode<> will specify the linking mode of the hook (\c normal_link,
//! \c auto_unlink or \c safe_link).
//!
//! \c void_pointer<> is the pointer type that will be used internally in the hook
//! and the container configured to use this hook.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3>
#endif
class list_base_hook
   :  public make_list_base_hook
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
   list_base_hook() BOOST_NOEXCEPT;

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   list_base_hook(const list_base_hook& ) BOOST_NOEXCEPT;

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   list_base_hook& operator=(const list_base_hook& ) BOOST_NOEXCEPT;

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in an list an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~list_base_hook();

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
   void swap_nodes(list_base_hook &other) BOOST_NOEXCEPT;

   //! <b>Precondition</b>: link_mode must be \c safe_link or \c auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c list::iterator_to
   //!   will return a valid iterator.
   //!
   //! <b>Complexity</b>: Constant
   bool is_linked() const;

   //! <b>Effects</b>: Removes the node if it's inserted in a container.
   //!   This function is only allowed if link_mode is \c auto_unlink.
   //!
   //! <b>Throws</b>: Nothing.
   void unlink() BOOST_NOEXCEPT;
   #endif
};

//! Helper metafunction to define a \c \c list_member_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void>
#endif
struct make_list_member_hook
{
   /// @cond
   typedef typename pack_options
      < hook_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3
      #else
      Options...
      #endif
      >::type packed_options;

   typedef generic_hook
   < CircularListAlgorithms
   , list_node_traits<typename packed_options::void_pointer>
   , member_tag
   , packed_options::link_mode
   , NoBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Store this hook in a class to be inserted
//! in an list.
//!
//! The hook admits the following options: \c void_pointer<> and
//! \c link_mode<>.
//!
//! \c link_mode<> will specify the linking mode of the hook (\c normal_link,
//! \c auto_unlink or \c safe_link).
//!
//! \c void_pointer<> is the pointer type that will be used internally in the hook
//! and the container configured to use this hook.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3>
#endif
class list_member_hook
   :  public make_list_member_hook
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
   list_member_hook() BOOST_NOEXCEPT;

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   list_member_hook(const list_member_hook& ) BOOST_NOEXCEPT;

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   list_member_hook& operator=(const list_member_hook& ) BOOST_NOEXCEPT;

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in an list an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~list_member_hook();

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
   void swap_nodes(list_member_hook &other) BOOST_NOEXCEPT;

   //! <b>Precondition</b>: link_mode must be \c safe_link or \c auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c list::iterator_to
   //!   will return a valid iterator.
   //!
   //! <b>Complexity</b>: Constant
   bool is_linked() const;

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

#endif //BOOST_INTRUSIVE_LIST_HOOK_HPP

/* list_hook.hpp
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
*/