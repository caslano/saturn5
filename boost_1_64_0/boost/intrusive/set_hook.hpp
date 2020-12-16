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
   set_base_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   set_base_hook(const set_base_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   set_base_hook& operator=(const set_base_hook& );

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
   void swap_nodes(set_base_hook &other);

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
   set_member_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   set_member_hook(const set_member_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   set_member_hook& operator=(const set_member_hook& );

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
   void swap_nodes(set_member_hook &other);

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

#endif //BOOST_INTRUSIVE_SET_HOOK_HPP

/* set_hook.hpp
9vWD8G3H+eYYKEPbt3E0sa8f+L9w/Ril3fia9eM6rQ9weGN2NaHa1A/CtakfUmdTtd0VjqgK6sfMuu6z2s6p90whlasfuOW5yNUnR13wHMKLqROWZxz7OlFmzHBI6oTuNuTcyGNk4H7bOjFu2vSp2dY+2MyLA9p9NZvyl7DkfhSIYX6o5FO1ajq9F9s3Ws8gLVSFZT2DVMY8xXUtZ8NaHklk+CNj2guc4WypH3IGqU39tLqT8clFnI1LHMwyrFH6/NFS6UyuWz6d96mznz2lU58A7ahUOkvqXvrZ4tb4W+ObF1Y+vverm32Yh/imTc3iUL9KxZcwrGPIis9xDrM7R9b+/i5u3c8OF3FmtyUfyozdiZuYBdqcLdtb8sunXvn8epo8DPKUX+ap7I6LPpfdVUa7yl5T2n6Ex2tOn2IzVrB/Rgi79POGCdu2Tm0OLxNfGXdHeYqvPm+4cvGNCqv8ecNRYZd+3vD8Ohc+b/gMLPK6+DPd7M+M83xWoP1Zchd/hqD9mYCeznTzfMbcdzOV+et3t72hw9S1p5s/vfGpjut2FHs6M+6/d8bfxZ6ZaH/G35931qH9WX5/3pl99mcaXvyZj2dlLyP+9BxOCXzTYYwFMghrhBpHWH7z/kV+63c/5u9gi/lui/kuCVOVz075/TKi91CS+UV5JtJ21j2U7pBv8O+Sx/sVsLascWoja5zayZqZKLgS9of5cDBcBePhvTBB3Ln2mMqV6+6Q61r3mFqPtZesQQiSNQj1ZQ1CJ9lrtKtKP+wGt8AkuBVmwu1wmaw1UGEWytqsHXCd+LtP9jJ9UOUR3C7hFmp7WYPpmrOR+JVY12DKmgPFL2St1JfQH/5d4v21JZxcCae6TTgfSTgfQz9Z21ANFsNA0V3h5Ek4gTbhvCfhvC/hHJdwPoABorvW6hdIOM0kHOta/RclnJcknAOSroMSzsuwIXwFNhVzV7hFEm4Lm3APS7ivS7hvSLjvSLhvwghZ+9FczGUNq7zDJq0SrnUN69NST/dKvu+TvWiflfCeg+3h81JPn5F6hG7uZR8n4T8o4Vv3sh8r5TtBwp8I68Fc/l0uaw3byFpDFb+FskZmEbwSpsuet1OginMmHC578CaIfoPoSXC6Q9aKQ8RxC1wi11sF50g9vhXeD+fCB/T1ZI2P652ivI8rKbPG53rJr9FSjomwFbwJtoY3wLaim2uGKghvmIQXJ+GNkPDiJbxrJbx4S3gFEl4jm/Auk3oSIfW/seR7Exiq66yxx05TCW+pvNfQaZLwrGssW0r8IqU9tJW9i7tB5a4dDIcdZI1oR6knnaSfiYb9xHwo7KrKT/yPgJ3hKNElPvIczXsFm/j0kPjESHx6SXxiJT69JT59JT79JD79pV4NgEPEfCQcLNePlXo0ECaL7toTer/EJ1jiY90TOlTyu460y3oSrzDr2jvx74tklFnbNsLirqSS7hxhlXMXVEl3EZV0F3UBd6xH1+ugYpCK1krtysW+4nVRFayJsl0PVem1UH90HZSHNVB/6vqnU9DDeqf/2jqnS1njdDFrmyq7rknWNJVdz2RdyyTrmPQapj+0funPWLd0sWuWZL2SrFX64+uU/sw1SmXWJ/1PrE1iTZJlPdKF1yGtR1zrj86w5iSCTVRikRykADmEnEEasKlKHyQFWYhsRg4hp5GwL1gXg6Qgy5FdSDHi8+Vfa1j++vvr76+/v/7+H/58kKn/ie//s3Oy2xnTsn94DcDeEPXsI9/3yPeZZ7zc3MhDZVxN97d3M1Iz08Yzc8tcShIfFk3LTMrKziRU17cT+nwycqGL05i3i9d+S7xC1bfRSGOkBdIW6YR0R3oifZHByLXI9ciNyDg=
*/