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
PoN8XK4M/ufjwPAUj2uXBy+tiu5e93cpzd3fccQ+ShNyUwon4dEebTnWlzysEPQaxvTgnCmDEwe+GN+1EWX2sN5k+s854TmeMDlT/IRcr0THcAZYbe8Q+wEwtzT5OKQVoGzA8QC9AMf4g1kIHCB/wKz0iKxAK+KMbYAwdwkccDQ4Qr/BZIBuZFJzhT8F112E8DRf7et7/HT9Wvsi+E0jzUe1/U3i+RVR/Fsovk0Ufd7xRT+xcNiBwj6bSLdIZxSnXGciXTLRh+4ym41o+DrV3t05T7BcJ4EW6DN8ln12fswr2j9Fqf6lqvE+4046ryTaXjePuObz2Oh8o70tVyHfsa5EP0ojmFm+BHrPdX2tMHxoLVOyMvuWDew2P1G/nbTHWkX1WtZj68SkH+Xpk0/450f4023jPpV02Wt7yEtsNzLf4SG+p+MUBE3vPzWmK/IaLYvvvE+cHyyFKXXCV7FfbXfrrX69epl3vkh29sYSJ39NIc7FyUtvZNB7ecNtlJKOcicduCulv1Wuj9xPqn7GIltzsvunW1XtIcdDc1cedg25uLGtn1CRbWz8RZmY26E4jhPHzrkQ4rVqGc3kvNw2lfRO5fJeHy8q9NPjpDo/iS0y+/rrfDrPyJyX41ys6ypzeMBLdr9GEp8dn2n7NoSD80Ey2m9sxs/HHT4tGR3b3MM58ZC0m/eTNL7DFh6nfl7lKZky+pOk6d9pNsf6riZ27q94vkMeD+5gghO/N3Z+LImz9vkDf89BudAdRJxdu9N3Z4TjH0jcee+ANirt4KO+Psg3xcmprhmX7bq0zOK9HngwcJ14YKYbO1PQODPw88U5L6c1n5tLfMVpOfkxKpqjw0I6soOqbLZz/3py664cVOQq5fAoAWcr1SQs5FTfYZ8ZfJFw6CWEl5fJ9DEUyOlSVvbPKe8P6VW72UO0ZE41lKfeqEbr2HXQ5fHK7AltA4jJUwLupsHEdeDlx6xtYzH3RukswLwuFoupvBuVijeS9VgAZXZYFVhDI9pa86V3fEJO/W11+CXPq0r0JXaCq2DLqNFkdgLv+zv4DtfXrnYZvs+FS6l9jl/opxZT4cmbruzzXoagrQX2VbrSpO2k0KYxUw053sIC6Fl+yr33KOiZWmUTeQ6GbBaPv9khY+LkhWTntimNXFfVeq3pfZFmdzrfgAkgb/pMKXlxwrNEnAIVc1YZI2ZSve16SO6ScfedCk138BVh/TCbeXPxdnl9zjX3JePVWYYcvMTayBxPUan9eF3b8Rn+1PG8ZmGtpKUzT4F4EyMvwgrSWbXNaFSs41tDqcd2urZaPPAW9YGWgj8TXrHnIqN32pMxjVtwVX0AHxr+vLNNeHu1W3tSBMl79LyXjZx5slYuHl1sgX36hEjna5hG/355te6ZhNhKy5kmYRl/XntOTHVsUTlPJ7NlvWIXGePAdhmbTar4fJEmxha1NGWDxcLoI4hvRms7mT2Mti0Z2uCNNfZVT6jka461MFMfyf52E2GhMI+5288aAuuEz0bTn9O7R9xEshxKC1/l9Q2+rBXR74pFqxVjx2pZedup+FktyoMtieWAHQn12cuoV+7g7yNp40iQ5qPwg8gO1CKegNkWmwoEKTj4Jc9uIocOrqxAQuFLYrnaKenzcRMvmTLu8vp6OXz8eebL5aCsyVGV5g10lY8WBFqhP60Udsj7PrLZWUDnaB0ylpuMhUdLRk+lBm2UAEHDzOcvHhcqCLMzmbicuKY61SJF33eOejb1zYSdOMgs0fgTMiJz6vqpvZF67FXhHoquLIlimfd3xT0NuSUfx117VXHvz/pNxhThirJNW8iocy7BA0xnWOOl7iCwnRFsek1FCVP15xZO2TK+68igoj4UmYTvgeRcadjrieMjym+G7/9EjTnfsLmoNeUGZSL/8s4f3IjkRL/XKmE9eLFhyvfj/z0308e3OvKTd2EBzW6dw6VgTipRfucYuYntItmwqOCiIn2qA61OxYuCM31wkVVVkYftDx8qLFdM4FdFjS3b9xyRl8/uLeLCVS3UYmplnZD8G7dkQ7bAnmJ4DSJ56huKKGb8vkvRyY2JK1nWivhFzir2gIyJKzN4ZkGTN72PnlTWJMJSfiI+z9iMMLWRiBpmF6DaRVZEXLh0XiRsySIXRTTmHmHLUl9XOtvRDkT74ryJCT76qNKTfhVzTz7PuQZ4+pKrR5sbvhA5lIm8weHB/onpu0gcVnRnVjmpiYEMW9THNYVM+em3MmuPL/ozhgFzSsz/KILUkVvQm/wm/lichinZeBbwrUBrL44aIjKjbitRDN4sgm1NwEUlvFWIeTbKtPnvY+ubCmap5nWWjdOrssImLtBP09Su9d78DrqbHahxFtW3XIMEWR5yOOycDbemlwLSuoygshfpzRpldk3udj+CORePFxs/t+8HZ4CwCVjqjZrMlFmSC/XAHXVjDW9gNLOaydChK/17AmmkQ0YQQlkFrXnyJfPEyWWB53sChE2xvj1mhQz6cd5ew+p5IX3G/CD4VpfzsLM5i11sQUTvRuqlodxKZFJptAtEzEpI/qlhxh86TYBnsneKGXBN9R/cv7wiSLntQDuQM/+U476Y0jJemyAJ+CL9CMvAjgrNyUxD/AGtfzDuFFMZU7EO9M0bAzFNoYxjZHpVdTKdDNud80JUwS7JpGL/WHRk8Nmv0H2zNzgvE5V9OKbCQdSwl/a7CPrCzEJ2jkU7yCvYY8/XIutycc2QHawgyDHfnxU9giHf9SRxbngJvAuamoUYX8GUqcQQQh6xHymPtWCE9cT0G8JmCmf2xzo68YJPDs3tHq0rU3gj8k2fhEhkvTpgVsxd0N7by7hJP0Wqdv1LlAtvGtYzODu4UqAlwlGnjfqMQz6pQfc5bRkIdQW1fRgqTclXJUXiyDRis2V3J1HXx4DJLBW4NmJywyTnDGxg3dxANtLokbe9M+eQv7ofoSrZHa1CMHnFe1OKaAOGJ8IEJCo8KrmeqjdDm8+RU4wIt3l4tYxUmtpHTLCZvaAgM/rQT+9CYV29Eoloq+TLkBlRlCfjBYjnkWyYZda1lzCupG+ZQ/9Ob0ZmqDDWh7zFfAJEy8cfF53tWaSxCivyZOcMhK6dEYcU2K6Hd9ERcRbaTBvlBqfE1umdQ7qJCWFzc2z1qjSfaonlSixQ8xwaN6J3T/hD37xy/WyVR2co8wzJn5y6LRs1GGagHLR1KEefuEzKfEn+2ynYfLbpMdna4q6nHHjptVV8dQ3/QvKuw+NZKlK4Mqv6qWsrlkfidSVfzhtzfPcqDBQVYbWZawdjopGAtyXhcgef5rlGgJ6HAXYhW/swsBtCPAMb2CfrA9i34g90cQfUmDXrY4aM84UGKZ1B4O0EuejVRuGKP+h/iYQDFg+QHCJ12IQ+rE/wAtvj5bg2jaYyYK+DJ4WKH0gb3tWT5uHxRDbJE8JkA0xYEnKzyBjrTJYAHegDUAh+5w5X3gSEyYEZSKYQhh1I3ihIFuFaNIPdJ0ucjuZRMUB6XjFKyQUZcPzUC3fagoH73H7yTMG8A84DvdUG7Zp9CXrA4ZAPekAYWNidDPAG6MhEHFNYOUlww3q7MerIO8BOfJ2LWs95Zuh0qH43UEa+7IJrYLwV5LtCf3KAGw0MiNkAvCYlukbYB1s9ztQn3qL9WwSxIyOyzTdEK7q5JQHe6VYgQz733VxXgoaz5zjWFVTkxjwvrOYMz3GeYA+971DDHMtXTy/y+Eqs0VqUxwvQBaOyVTDrRADPA/8HPO2Jugn4FdEBigOcplO5gOSW4pbZYFsXqhpsJCA8IA8wXRTVChQOwB4oD0/hLywHQBeAB0uoHfgzwEKAu0KBdyA+sDo8pQt7HbYH3N8oShSQHjAZwB9gmhXUCQB5oBsA6jDUDnAOIJotKM5bcQIGIL1d090oDhuga/BtgJp27YLOgF4QP9DNDlhfNA9EjQwFCjge0C5gGqkBNQMojQQhXMAZgBugbZaBPvhA54AsxdOLPmuBKbfQFoDwQHhT1HUAHjAZYGhnqC+UNp5aBehb1V2KXUzRLYAXQHpg9TjKRehP1lvtfONwoR3gbaAaDHGMVWAZQHV5Av5d7T7GPud4odi+9EB8gF7gZT+8Z8AFgQW5UDyQbQC+Z9DQFsAfkE/2usdoqOGAGwB7wBU/yYLYPjsDpFfe2TrpAr/det39OGVU1WTw3Geid4Spsuh6q+4QupLJ3SL68Mr2oJri+HlVjWF9WfwyUIyIvADizjS0eVcX3qV5WI3KrYinZdlHyncWf/kz8zPnphC7ghIfdH3c44YjH/ofqY5YNUXg6lJWDeuaoieNzorDIrIqJmCUYrN1AVqUwo3y1PW/OVwWxKGWyNP/iBdFtzCkuhfFs+uVeoLf6726ogs1iBtxS4V98rYYfmok/1yX2qbkk/hPMAlvvC3U2oxuYVzlO2ble++CuM2jn0Y/kq6HOvfUzqpbsi8D65d5W8Jvie/0eXnSb8nD71Y54fNKwCe6GmNk29e1PD6Q66nc5dXGqNY/ydDaQLdWcaTT1ppHy7F77aViaw309KjVdgxjJ3Wk6R5V+E62O9dUWHfzFRj8MIiAlrjIIjy7hsMUAWnpKV/JfOJaom4o1riNlZr6ulXtV+kmYTzZ+ydM/MsXuE4RoECvSKR/jwl3Prmk3zLzL48INNdTV3u5ZktOX2GmharhUovUa8ftLz0shKzGRGtNwDzp8IOueDrqgM+TdxPzrq2i30GFAMsmLnfnrTJnGVR1/te/bxcxJXPMUKxhNNlWWWti8uqzVUg0hYjWXV3lprNWHDV0xLo+URrkyef3RVrWAENd3KekjB1Dvv/WlqtMbZZYo2PRec4LV0I5Ud+jpCd9Qs1ScAqJPmB+FdY4m7ZwAg170xHcWcPqvum8rHOHwSS177XrIKrvTtDEuN7UTo0RGRaco9hbW109fmKvOnkZsa2gTCk5tIJnB62HITqrH9hj6BuKc2mWqHX9iXVl8BC6SOmd1GzZnmOJmzJ5djGddX2sI2nwkdQyCVSXDVVQR79aoZX56n24yRz6bkbiyK4ZKjSPc8Je01ZurtZXVzvqCGEMUqtgy8nJ1RgVZTC+mLj4b+NdpL1SLlqzI2F9Vr9FJ+GeuxXZkxd9GdobUCchOq0pCaO70ibqWAmKRGaYqmGAYiB0Pub0SD24VkRZ55FOfedmsO+cugnshrEQbW3m3hLqwtDqkHV8zUSKfQnB1rTEkDXyM5bQ9DnWiadKfjPIxoT9ThPJ7aotyQnj3WghQDotTU2zevnkR/f0ZVk8vLi0IkslDZYJFdHJF3tP5FqIOtL+n2P1ztS/+qszSGtN2sxGjHQokwNjLzb1BuHBpyrImthEfkBZIOLgHWTKTvLtOH49rDsrUPRBrcc9FyjWBHjS5mov9Q5L4ZN7UzoKheS/p10tzZSLS9fQ4VxZ7C0gvoEG5JWH+eyXg/52OL05oEiOyA2bOEI84T1Agb529Obb0a9YvrxM3Rk2QlaIOfmO7JMPhS+rl7uH/1Q8iSuSBu4LG7qVLJCaxA3F06P9FukohQDTy8AJyynIrf/N012QmDi5lDxcxrFuOO8NPKqVT41WraYeqmkvvoLKshCyoWW+KEL7pL56zjZxNLa9PG8Wo3GnOmzSxUCuLVLfTUyzHqxzRmdlrnFnXy67/0uZnJ7mtGVGLGJ+6W7jNbezbb5Ab6DpNb5XNminn+W5QnWLFLuNtbwD2ZDb9epJALHxz610JqiJmU9nn6yLOrXU4RlxH/4L6s7ViYTyisY0FRq3ykLwAw3N/VSMJl8A0TKz1ekuu9mM9syY1p10He321234fqNbZOkqy4ssjAl9mbm8U1tXW8PGnO2auq4BuSgTgi6fCddjU70cWFIUlftCnGUrw9zl/r6n4p3cnE0t9GihBU0tzOegcbJSW2m0ZCZZK1V3q4Gys6PDdKHq8BztY8i0H7WDHxZN3SiID58fmqE33ZMQx4a6apKNOUWHLatATbNyrVmXNVu3udAN+WZMBdce4jlUveEJOQxA/yxKeiHxtPTawJ1h/foCutm9tZOmubUdUiSObyi08pD28t/+/CgnQ2oXQweQlfGT1nLlX+rdl0k3RicDYrN9oWmBDtjgaD2xs/NN7nVCusjbE4ek0OhAO/QMoW4iaLP25Qk8hj3V3e8Jbm2paJXQyX5ReLJ2fv1d+fE2F/nfzbgnaaVykmc3UO+YLFQNsdabh+ioK3RcQsuISqWqxZdfNLjJDEtRm6ONTiVp9Kxq9LNM4BrTWemp2o9gKcSj8gorPvMO4PnXk20Mvv98zXiUjbyxlx9y3jmZqtE916RYH3H70VF6+YOmOupA6IDr0OcK02nXvmp8st+m1XlbFsFP2vXSZy+RLdp97/aLiJnDv9ySczlZqQ/N1D4WojdOEVol1hwxUp+/uj+Ry+s/LASw5vFP9G7Nat5HKC285H/hKn76OtMrxKYm86aS4mMqmDdu3EyixrNY+7j/VVlWTnuhmi77LLBayLY2H4bx2qp54UNZ037EKKK1U4gWfRNFC+dwx1upj9PhmJ5//nNVU4utjWOv2WnRqgSup6J2Z5MrzB+4LeNIOt1C0cNTe7XZa3aDNe0rbdPkFNdof0T1KkKNM1r0xNtQIvzys5gn7jUDetnter8Fp8b5oKsH/jb82r9tuO4uUUAL5e2mOFS75MTJy5mR8RdXnkyp3TVarLF8qb0AkWbWuZXkQHjNhY73Ty9orn1zmjQdbqW2Svai0p0hrznPQpud4pbSTeFTum9bi5vtt/9G5/zfqnNXebPQCUbwmsJERLmUvz9feSe2ZnEpOM1KjdlZDwpZwhnLjKSNvz2O8AKRKDOpsDA8qevcv391sw5UzJOR/1KQYufjXjx3Ok7+fOz9cV3p0Pfkq/Mw7b68evgsNW989sPPZjE0Olwu/TmwJ+7thd/mNDwdTAaIVP72gP1B6uaFl2Ai+apPTBb8CYfPuX3B/36Iv5kIaBXLx+5W5bWUOayUxmMp2CBOxsflfaw/LJYkvvHgcBJOkcZjs/gXUjC+3fKDbv892r/xc1G08fxzoWP70ftTttds+8P/9ZjYi+F2vniVS+f78X039XPiCjIlytCKRYHYLJKjqM8CyRupJ3wxC/fISCXKc4rDgxEDrQd/H0zcH5lP1IahA/kNzD5qyzAC5P1JgBeFP4x8p9IFQj9aeZftAb0d1Xpw8OrtA6i+V9kG2R7aRBbBYCQp78TvGQFDWDSubIKWKY+WaGoCvyYfl3RwCPMWqyN+MR/WRAn7t9B9dvrRjislriT5FPnRsiODrqz9ETZLHn626BGGV55+LuySbDmrhGmgo3H7EpAtKNYUeY3nmcg7tNroYtX70tktwneq5sTVA5jOY8z71sWPH3+S/KHsFSd3WH8f+43bh/snwn+id2/nDv+N9BvbnsgO1RYUTeoR6WvYgFGHhygX0XmIqF6ni2w5+mVYrl4eB2UnQn9IVVGaLSH2qNqp7g8Fs2kgTaL4EaZnMlcR2Xm7V+p2/s5CmesfScacKZaHKk0juUwqYVuLznWejZHUtsHrJuuj1N7J+PuDT7Cf+p9F/Gd1n9g6wQyE0pArIeRnqNGQ5IFQQ702Th5UvRgfESEZtH/X8qdkKUHrxHETs5oq1Baodbt2GesJBHhl+3YeGNN9mq+on1zbAdC3hDyYXL1Bh0lPhwyWMuQLoY+uHYBeXn/85KlPZ5pIrUc5mKuIvUN4p78HmNZwngm5/8U1Ornlsu5OeVBvhxnzJcTvHryS8MX2/lO/8+nJRL8zmRNDIBSlEIvy3BetF6pCsY+4MnJv0hYfNnWsjkl+Mg2yIY5kaQi+JDoZI2WSt0sJdUr/VFpWvKNS3KpQSlHMWSRglYlVpV7EeipdL95WpHXlnmqew30yzDEgy848Bm1c7TJ6zgA+buK0pstMa8lZml2zc0vTNdFvbncL/prIbeDfoH72Gv3jvqUrvzJz1NZs1+i9cuWg3558Df6S3Lmf9abWk0O+/eayswL/KPxVxBBN69f5M3bzdPJJ+kOeIW60SiwD/xH+YIA2OQg/ID8wMyi812ooQqBsgOeqSLwIwypuqwi+iFpS5D0nbIGmFaIn2m4B/A6VI8RfRH3qlZEE3wHOG+zXH2XgWse4ioQCfhKcF5zVhmYXsWEUhnsdsXCr70CWi2+6FP7K/Un8DbtC4CiSGHeIN5/NI5GWlHMIYCm5MSvmg7HrxbwzER5Jup/QRnA+qej0ZxOku1uPlKJEqFnmSt31yXZWvKTxybkUhWtlVirbDL9RXnDmeDW0pWjSRXQ20/c6n/v8/NWrh/HRNAT/Av+F+tPqp3TncOeO9Nvaf139NTpgYahOdJVtqADqIzR4QHGvaO/wtt1BsI3Fh1QHFy10Y3Brjs4X99vvx4ALQ8p2EYBVtDV/Q4F8EfdJ6Gtu0ALEC8a0wCYlWK2odVZOBSjjG8oXuq0nyg7CDmY/2Kw/R9CLgQcDWQZuGeQieKpfvb+1f40AcCdG+4DbUX0TWr6f+VZJ4FPrk5IvID4I7SvAWIKmXB4rkYRIQqIjgcUJH1OcaczlHsYzsIrkYozsXr0hdrGs+5QjS9B8wfORtCO0R959Xv7UT0vOvzD9rJkmjdUgg3M5tKT+Y5WBDev1Dkd7SK3BpyX2yqTkEoN73OoW28N3V9J79g+3p/p2dPxh/P2oJ5l/HP2+/YOQwp/BT2u9afp7fU/gOYzHY0hGYRoU+sAekVcnBRzEsiH7vnQuJj22xCnSdMI6Utlt8rLJNSbpHgr9VO3DD6eyT5m0wP1PCv/E5qXYisgOYVdlf7WvJWGrYq2S5crqCo0rtZ1K6POGqLlmV2vcvkfu004XeV6Z+DnkpwWvtOl5zw4B9DPbd2RfsZ9i+gsM5Q0X5u5/wGb5mKal2W/HpsnGy5nuspmcRj2MO9mTpWm2phsaZjcNxpci3MPTTdSXVh+lWybRl+nPbdV16FeqG0Nb51qch9duLx3gWwbsI7LOD1tILw3aVy2duna1H+s5Dic6tjuzO4fJn1c94TcH4K+Cfk3+E/wX+rfRX9R+vT/zrfCYBDZSbWQ0MNKD9MRd0vGRnNiQln0dhhZMWeFowAtsBWr9wP3Q/d794f3buwD5h0YOtDXB2LsjbZhsimXrMTvDGwKI8fvKrzw1Q+mOjGuicYnJhzQ=
*/