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
   slist_base_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   slist_base_hook(const slist_base_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   slist_base_hook& operator=(const slist_base_hook& );

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
   void swap_nodes(slist_base_hook &other);

   //! <b>Precondition</b>: link_mode must be \c safe_link or \c auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c slist::iterator_to
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
sjey0fuBInCvOj8k4h5quD8a94ZYeSmQvJjvkfINpP/gXpDu2sMxbKUVXz991Bm/vOULe5ffevjovc8+VpTYw9HdezjMe3G6d2+HVG41rtwl42FZiyrvt6T9QPZaVNn7YOFaMBW8CQzK9Y8hd7nILRe5FbYcFEPuMpFrFLkmTa48hty3Re47IrdJW1s6U+T6iZy+tvQbIvdN0Ad+C8wB14O9wFvAvuAGTY/mGHpcJ+ldL3qsEbkh0FqRKxY5j7YH8Ssid412nVbh72m4Tq3wLwWzwtYWt8fQr1nkrhT9rtLkOmLIfV7kVoncF7TyPSRy5SIXvhfCHbYXwgdeBPYAZ4PnSljS43koenpTJb1pkt4nJb0Zkt50SY+wvTZ5raRXIOnpa5NPk3yVgWngxyXdEZp8q1HevAfmEpGfq63Zbhf5wSKvr9k+WeQHiXypyJ8C5oNDwRPBU8FBcl70omCi63WGpHumpDtK0j1b5JvtsRFlKvI9IL/I50k554tcgZRzfynnQtGvSNpHMTgA7AUOFb5TwT5gGVgCfgLsB06R82JvGc9gC4O950k+Fkg5LARPBmvketXgMAkH97bskvROl/T0vS3nSHrlYDY4FuwDjgP7geeBp4DjRf+J4EhwEtjqVWvLu1xPvm5HrO8vha8Z797vMD2/47/7W0yyPtv4TaaRbc6+yzSvLfa3mda0fTDfZ9rZ5uwbTaFrqI/tW01H2mJ/ryn7wY/WN5tkrbOsc4797aaFrDteDW2F2qHDUD6921nQPKgZ2gztgQ5C2fjTHgnNglZAG6Gd0PNQ4kgcicP58aHN/zdWXdYd8/+Wj//d3LhrlY9/JvUr8H9XUVvT5A/4+PeToRX6uaaAj/+famsG9rltPyDq6A09RZr93+9pv7O5YMKnLA//wysq/f5Gea/xnPKnREaMvnlEXt5F/Cbg5wbhKO+p4NXf0T3t4L1N8J2EpUeB6BF8J2Fdr0Cu5+GK4ySvq72R73Sftuavo+XV8kc9ffJ4l8M8k06Yjw7KHDTk2cCr5lON89M67+t5yhfQSn9Vk+FbBaZ0a6vqQNO3CmaGlfteIp36IzeUu7wzI88R/jlV3mx/8uSBOJWHUH/yoqtus9HJkTZ7xhpIx7IZXvac2qxZK68Zqp7SMKP5nIvDZs1x2Kw5Dps1h9nsZ8fZVsgzceS5G232bkqkzZ7FZq2xbOZf4XdqM9Kx34OjnPQt0ecAWuOwW2scdmuNw26tYXb7+THaTd7DyzcZgvk+ftsF53BekTUChQGAh3etPNh2RNpOW0bmzG4dWnkdLrB4SaHJbLOOsPJ65hjLK1jPresVyPX0urpZ/NEr3wFQNfTrflamY+XXupk6y7PrqPM8w2u4fxjrqc2ba8+DkK5lTs3/7UDFU8A8nEel2T9J+CTNI/h5tvzEHsTmJZRDez5pFw/3eU7gyzDwdN4XxE+szCP9gnBzTqfftiR9DHWMNpH6G34PUTqid4AvrJ9ZJ/Pw7VC64H7mpNeG2k58kzc01lxe6a+qYKpX5U1sp8/HS3kZ5+OlvDPs+ekltv/j+9S5e1xDGWndCplsK/L2/DYjsyVqvCVzM5vU+cfIXw/XGP7eC3X6Na5fon9Pab3i3eM6n787IMuGWyiADirwL9XaCT6XlDkA7+I9koI2XJ4n3xshnEL4WfguI+6wUHM2YcPcqC9ivswHMHagB3TL92beVvq4BkybfqYKv2aHz1DhF+3w6Sr8tB0eSVivH9giZF5+ibbuQl7CaT4l8qDfWn5N0UW390KG3xja6hwdtVHkw/vx+gVRxgDCa7eNfcfZL0k/zPVC++E14esP5Lspu8LyavdJgS5J+gPJbzBO1l4=
*/