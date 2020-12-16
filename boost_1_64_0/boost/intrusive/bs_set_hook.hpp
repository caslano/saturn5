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
aLw+n2B3tNc2R5/PZYsXjlCWhWdMW6IOKaAqqabGiuxzk9C7o88DTRfF5/eIYuLthvw0e5gPd2tTdxDin7teJqRt1HUUGhZP66PAzTTSWru5lhe6MigDSUwv0+B4cam0uYq7tnFThXmcIr7WL5Mvn6KF5XPHd5Vnrpan3kY1w+PL3aM7UjWXu7F+fXJlRnzNFnfbNl6JG5F9tKM99fJm63eDmZ9e1uXF8WX9Ctq42FhWUWeVFD8Wb09el1Xx9nPXZfVwt7PrsprKsu4fEV/WZ9Rc7Jb18pIZCxcvnl+6eMmiOQtnQVZRVVuq5pq4uwXmeVfj6Wkyl6q4iXlaxw9kRvUB8xwbU0992mHLF7TH9QFFY65GI89bMP/pfSN6TJg/Mr4O94PfShLUoX7Hc9tZ+kdJTPnOtIMPtmk8r7f5MQO9P0ZdlCWi1x3i2z/GO3VUOyo+z9fVfitRnjLMJ8djtR0Y55G2sY5qRsfTew/qM5SIXgz17WnXUBSfn32sD3VgrN9mGOvb4udVF8eX/Umk0Zyw7Bjukyw30tDXrW3b9O7AeL/NMN4jP4730W09e0x8eT+vzozc8sZvjWm1ne8l2iwz0knOZnvL9nO32X53YXI22yeOjS/rAcQ93EZZ11ZvwklJcmVFOtp9nbbbl7iRe03t4Gm3vLH3bpifzs9nDGX+LOIfa6PMGPKkbx6RMlTgiRte0iW6oxRTjllJlCOP5TgiNDP92H3yuHi6v6rOEtqgG8Om1P3Bs7TTiQ6MmQdjxsyZDr3j4+n9IXBPJabXHTaT5a9T2rh5XRJr5FMdGDfvNqwProtZI+t9685LzH2rta3yY+hMtuyt7ehbrR0YO5PpW06Z906IL/MDiG9dm7jMVACbFJ9a1ya/ZrauPfc188HCs6+Zh7HM/SdG61DOgZuKXDJZ5oa68AK5c0ReaN7vxdB7f+bZ5b4ZpJcytyi6jhro8gOvOEKXdLXOnHsT0VUcQ9f+dtCFdElXRC6yZ1K8XORn6mwhTBelzBG5yLTEchHGsYmXUC4CvLPKRebqdE+LkYtMM8hFmibHl+M2pN4SU47SqYtnXLZo2uzSaQtKSmcuFN7tlillKk24RiC9Edw1xI0pm4Yr93JQtxNB13B5H2kFemYGUnpbycniHd5X+eWSNvI+/YSGqDpouZT6Znmv5Am+Z2sN10H4OTku5K/dTvHttVV1m9t4z/ZniXfEPN6xnHko516UceillEWmzw2kdI0/e3DwlgDvsOB1CaSMi8ejLJFyxLO+kWvzbcgZNZeeR53Q89Yr/5XrPv2dzPuW/nLHn1e9d0Ph8ufaryt6Toby/+Z3l//2izU9Tn/w8ZbpP+736J8gg+2q/A+/taLPp8se6HyD/7id95cvPJFIV/H50zl932bl/+tbq7q/3vSTTj860ZA3YdLXXvy/zunzrXP6fOqWzqdtRCW3L8HvO1Qf0n4P035jvHR/j9N/Z8MOG2A36gDgb/TPyO+HtN8Pa7/VG/EipHOdBajlpd7SlQFOgOul/e6m/S7QfnfXfg/Rfudrv/syryfgBvD3Mbjh/D3QA8ffQ/CbOlOp+0HueiNM15kqeK7u2FbiFRNP1x1bjoFTha0B9ANWAOYAVgLmA14D2B1wHeBwfqt0tzk6BgBvZboBwBqmOwr5KzgGsBPgWMAeqk0AewPOAOyjyg+o6JoIOAZwEuAswMmA5YCXAm4FnAp4C+O5usSZfzfmr+uu/SToVPBTgHmAd5Duce6ba/RzxtN1N1/IeEMBuwBeBJit+I3xp6g4jN+H8Wl739UNblM3eCfqBO9KneBFmk7w2XAlTGcQ09F1KJew/hax/hYDKnqXAgYBlwAO5Lc=
*/