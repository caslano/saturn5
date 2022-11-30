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

#ifndef BOOST_INTRUSIVE_SLIST_HOOK_HPP
#define BOOST_INTRUSIVE_SLIST_HOOK_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <boost/intrusive/detail/slist_node.hpp>
#include <boost/intrusive/circular_slist_algorithms.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/options.hpp>
#include <boost/intrusive/detail/generic_hook.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//! Helper metafunction to define a \c slist_base_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void>
#endif
struct make_slist_base_hook
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
   < CircularSListAlgorithms
   , slist_node_traits<typename packed_options::void_pointer>
   , typename packed_options::tag
   , packed_options::link_mode
   , SlistBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Derive a class from slist_base_hook in order to store objects in
//! in an list. slist_base_hook holds the data necessary to maintain the
//! list and provides an appropriate value_traits class for list.
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
class slist_base_hook
   :  public make_slist_base_hook<
         #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
         O1, O2, O3
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
   slist_base_hook() BOOST_NOEXCEPT;

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   slist_base_hook(const slist_base_hook& ) BOOST_NOEXCEPT;

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   slist_base_hook& operator=(const slist_base_hook& ) BOOST_NOEXCEPT;

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in an slist an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~slist_base_hook();

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
   void swap_nodes(slist_base_hook &other) BOOST_NOEXCEPT;

   //! <b>Precondition</b>: link_mode must be \c safe_link or \c auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c slist::iterator_to
   //!   will return a valid iterator.
   //!
   //! <b>Throws</b>: Nothing.
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

//! Helper metafunction to define a \c slist_member_hook that yields to the same
//! type when the same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void>
#endif
struct make_slist_member_hook
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
   < CircularSListAlgorithms
   , slist_node_traits<typename packed_options::void_pointer>
   , member_tag
   , packed_options::link_mode
   , NoBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

//! Put a public data member slist_member_hook in order to store objects of this class in
//! an list. slist_member_hook holds the data necessary for maintaining the list and
//! provides an appropriate value_traits class for list.
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
class slist_member_hook
   :  public make_slist_member_hook<
         #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
         O1, O2, O3
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
   slist_member_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   slist_member_hook(const slist_member_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   slist_member_hook& operator=(const slist_member_hook& );

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in an slist an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~slist_member_hook();

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
   void swap_nodes(slist_member_hook &other);

   //! <b>Precondition</b>: link_mode must be \c safe_link or \c auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c slist::iterator_to
   //!   will return a valid iterator.
   //!
   //! <b>Note</b>: If this member is called when the value is inserted in a
   //!   slist with the option linear<true>, this function will return "false"
   //!   for the last element, as it is not linked to anything (the next element is null),
   //!   so use with care.
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

#endif //BOOST_INTRUSIVE_SLIST_HOOK_HPP

/* slist_hook.hpp
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
*/