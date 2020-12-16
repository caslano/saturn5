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
5Wz6tJwHnESfyv/iPdKngX30DVbP7+YZTsY7KPrMJH0RCnwDcAZwDXAmcDWwm8+hcA4zHLcmnBUM52qGcw3DWQmczWfTtynDydD4uqpTfDanA68mXy8gQL795PMC9pHvA8w/c4BFWPPoi28+88WVwCtEngUW9lpEOy0G3kCfireT7sPAS4G30Kfvdvr03U2fit2k+yRwBfDjfN/D988CzwV+ns/0pc39WAhb40t7MuWfwvz4PuAhwDOAJ9JH8PnAFzL/TwVeBDwd+BLxnvG0JXGPEPdh9dH/dAM33Xye+ewLPBv7RWA3fcEOBn6R95y/xPz3JeBhfB7B51H0PUqf97J8vgx8IfDXeMfS14HLgQ8yv34DeAF9yV5BX7JXA38LeCV94l1Pn3g19InXAvx94A30CdtGn7Bb6RP2Xvpq/TTwUd7J9HPgfXzupc+7I/R9+1P6vv0V9f0N8DHg4/RZF6DPuj/x+SSf/0EfdslJwWcXsHj2AP8OuDBJhEf7G9w3AfwM01nYtwEgfveLcICRl2S6fhy4DPgR4Ml8fyfwg8B38ftH+P0e4IeARb57mHp+AriH35nPuC6MNXlNPutg/Dt4R9dHaO97gBuAu3gH1keBbybdfcB3A9/P9/SdyTU4rHVqfGfuAV0S8OPAw4H3Mt88RZ/2TwBfAPwk8BzgfcwfTzF8pB/Xh4AZ/lDAEYZfxfB9DO9G4PHAa1hf1gOX8Xkany8Cvgl4rnhmfGuBFwM3Al8K7Od9/E3ANwI3A68H/rCwB59b+HwrcDv+B0ifftv43MHne4HvAH4QeDPv718N/AifWa9yDQL1maZeLTPooxY4Q74PltupwPl85t1jnLcHj8Z3/AraqxJ4JPC1LLfXMR+upN2uU8I7zPBGasJ7H+W6ENgNfBGwR3wHLjDCvvrfD8z2mHOoiEPTHs9leAupJ+KX7caVwILuEuA84KXAE4AvBZ4CfBl93i8DXsT3FcBXAC8n/wrgCuBr+Wz62qc8wzX6eSnPEOpXRP2G0u7DgL3AxYp+PQzvsRj9wnfnnc38Pob5bxLvohtNvxFjmd/G8Q668fT/MIH1wSTelXcO8C7gc5mvJgI/Kr5TnlKDY3fmJ/TdmMeCv8UKXZdDum6HdD390PUN4B0MifsXEvcv/C/fv/B27l7owp0LLwKOA7wvwJ8oYA2gE/Ac4Cgg5QvwCQi4DtAB6AEcAbwJGP1F+BkEtAG6AQcBAUDRi4m7HBK/xO+98nu3zv/XDuD9fx5v+P7/So5d1fOBW8Q5qw+F1yvnXbFULFeWVWG5EnLjYrVmOR+8Qp7/qW1qMLRzxwgjvjOCIrwChqfuWTqlkXErZAzoZBTLa1f5sYjocyRjYIBk7E7Wy2hs1Mi43tcWj4zGxoGR8aSL/WUyya0m+Mejk7G5/sb1NS2tTT4jWka5NpgPXCT5hmhkZphcNzgwTK4LIcTwHhGv/J6rXUdQeV8O8tY0KLxj5Pcs7bqR523YKrTuIOQtoLyhtSIhRwHlUPed7UyJTfdrh2PsGWtT3Ku4YtklC+ZLvR7MtU/z8jj1QHjUI+r8b2qsfJeLu/818tU3N7eiinCUJyvilM8qT76qka8DebI6Vj61aDuyYXWcMiI8rYwb0/Qy+jUyomjHJaP/bcpo7tfjmXoGIu9s3y7WtGNlDBftKrHPxVl6I5yItb1ZDu7otEr7C6PuARhMphzAXeKsmUZm3ujpSNbuKFlvehuyhvLAESZ+AZkyAZ2QtS9KVjTTk9WMmsU8EHFX7kab+wqUuu9vkq8FS8sWd+VG6ZnrYO9TjpKP1PtiRVwFjEvV+1CmXu+jGr2Z+S31Pmaj99E49D76Luh9ICtW7y4=
*/