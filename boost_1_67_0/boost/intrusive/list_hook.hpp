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
   list_base_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   list_base_hook(const list_base_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   list_base_hook& operator=(const list_base_hook& );

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
   void swap_nodes(list_base_hook &other);

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
   void unlink();
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
   list_member_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   list_member_hook(const list_member_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   list_member_hook& operator=(const list_member_hook& );

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
   void swap_nodes(list_member_hook &other);

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
   void unlink();
   #endif
};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_LIST_HOOK_HPP

/* list_hook.hpp
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
*/