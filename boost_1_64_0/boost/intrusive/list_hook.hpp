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
bwv+Lrw18Jr4CunF73Pce9QStsPaapb9IW7b9g7yAN8QnCa8bfYY9zZIw3yWwXn8+xJ+p/Uxo60Dxtf1fUTfBTTZEHfj6G90SzdvcHn7xxJ+kazJdqC/z76ea7Iq52o373/BfzpcmJdqjGsyh0/3Iv5f2qEfKJn9RZv2DliPBWKHmn563ZA/Vy4w89+zu8NEfQWBfsBHOM61CH4o1hBgwjPRhwX/s3YmeOhOrMV4T5DpfMmussbbGj/C37CmY7v8XMIq7aHQ8uHeJxW/DfjW5/+I/rHvL3D0cKTTD9JE8VNvNIttZx30S/HbbIvMH23ac6czLw6Km3vriDMUdfRRxRdLUtMCHp8/xV/jX+ev90/Dv37Qa9TFi7tGWfDChzcbv7vBpfv7+4f71+P/of7puIekXuANwEiViTCf/4LUDG9q6lUBf0FqPl5WLvQG4eULpHVq466zcX2buVCVZ5I9LLK+Zbnn2z2tYXai++azEI/3zd0zyevE7zty3/ywVeSO+X8Xfy/Xw0768+zFiL0eI1c3uyjhvfO/C+7vsLJaZlXz3nlrG/fONy+MukfOvMrts90/H8V4znrRiSfrFrRxYLdzprQkkJKrTosM50rEHQxc3kFf6dxBV67wHO9mzlgYfWd8K79L+X1bzHcLv9fw+4mY77TLzX354A3UvcQx93bumU9crvVlvElqj6zhxOXJyxqIq59tVutnwb+Q8MnopT6XtxaXyHpaO0eEoqA11Q31mmz/rxJvLeJ4Y2UU7vz3T8GpVO9XNJyNlaAg8i5T8uoc9faholsYT1+7Txa8LnE0On3zzzkY4+Gas3F2Bz65jftwXzvXDYZ9uPsWQcZx0q+vS/ffHE50GxjAC7jVpj7lkkgbUz1uQt1Hdwhutf1xy4u+m2qtxi6Y/Y3p9NV5gH763Btte66A9faQ4E3G3deukBbNw1rgqyY+YXrmt2FBwC9IeAtkQfPoh3Wn+M1FnFHuXuzL4nel/TkLmpTsvOg7K+Sdn4bLY89DSU5YaVh/Z+jjqHsP+A+Cl2+PQlrPqpHETjflHa/TieNwS0l4vLkFrdUV95GX2vqbtI3bdD0QJVdIXvwGdfLd2Zkz+f1L+FxoxegXcev6ZcnvXdR0EShbDI2mE3gH2aF3ACiYjBosEXnzoxgl/ozxXnQ/YZzo2aTd3+2E/033d4k7pcm5p3tF/Nk5cSpdnNChRDhNTa4ui8mxeTl0HW9yzpveiXpftxf+L8BxPf9ubB56Pq1N1EXQeWd/XQeBfr+oBuF74ZoF8kw/qXVbStYOaR9szCB7AP+L30thP3aJZGxbRfUhGdfvu8I8ri/5aJiAmQhU8WcANvZW7+ykz6sba+UbcCYlnT9+j+D2hV2CX2zPQtoBrNFy7S7GMR/pmu/fk9e3LAr386XALsA9/n62X8aPdDdunpse/dz9w+1BlR4lXmade8TneOMTfFXG+goYxNPXMJ9arPCw79Te2DzB/A17CL1clFlVbMK449J+I+vHdE4yXvLaBg1fue45ySPi50Fu+j3b+DcGByXdLvZA/P9ruH/AaXf6YTggso7eK7gB6AZOwX2+FbF5SV9owRxw8lanvw0x3tEHDhJz+nie3NFP1ft4DG6xi1sqenRmJDprIf6SvU5frI3Lv5A4TW6aoWflAId7+rbSPeSmG/q+UTcr7560ZIVlTVZW7O9k+nD77ggqns3VeLbA2X/54B/FmzF7q9vCmb7As5/n4baqOytL3H4LV1nLjqvvzV3eGSC4hyw/+loQbr/5fgTSNPRZTW6UK+HfQB44N4YbBPdwovstS2L3+24Rjf1Vx28M91euzyP7s8sE5w6UocHYN5mG8YxyroQ=
*/