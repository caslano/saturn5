/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_TRIVIAL_VALUE_TRAITS_HPP
#define BOOST_INTRUSIVE_TRIVIAL_VALUE_TRAITS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/pointer_traits.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//!This value traits template is used to create value traits
//!from user defined node traits where value_traits::value_type and
//!node_traits::node should be equal
template<class NodeTraits, link_mode_type LinkMode
   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   = safe_link
   #endif
>
struct trivial_value_traits
{
   typedef NodeTraits                                          node_traits;
   typedef typename node_traits::node_ptr                      node_ptr;
   typedef typename node_traits::const_node_ptr                const_node_ptr;
   typedef typename node_traits::node                          value_type;
   typedef node_ptr                                            pointer;
   typedef const_node_ptr                                      const_pointer;
   static const link_mode_type link_mode = LinkMode;
   BOOST_INTRUSIVE_FORCEINLINE static node_ptr       to_node_ptr (value_type &value)
      {  return pointer_traits<node_ptr>::pointer_to(value);  }
   BOOST_INTRUSIVE_FORCEINLINE static const_node_ptr to_node_ptr (const value_type &value)
      {  return pointer_traits<const_node_ptr>::pointer_to(value);  }
   BOOST_INTRUSIVE_FORCEINLINE static const pointer  &      to_value_ptr(const node_ptr &n)        {  return n; }
   BOOST_INTRUSIVE_FORCEINLINE static const const_pointer  &to_value_ptr(const const_node_ptr &n)  {  return n; }
};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_TRIVIAL_VALUE_TRAITS_HPP

/* trivial_value_traits.hpp
lvRXytIPNFvm/UYi8a/f5uUm7YAeF4WePiA1Iw6oquw3wdrHErL1d73gPg/sfqEKnvLMncDljhgth/s2bz+CpJFmTgX4w8mKPPnR5ybs5gZB1IP/BIkJP1BedhX1Qi4gmcENePjyZOZIB0Y6R5IHJMQ7YibF5nwhNUiDaA54Dg/mhBcTfK4SC5NpamTDMD1KQtbZxQX/QlGRX5NtfKOG04VhrJSJD7l5/EXoot3KnEoErY8algQryxzSd8BOSLIWpwm25pcqfmVfBv87Z9KYY98BYzmnpwEyyd1lJOxsWAC/Kp9qZFDtvUnnZxUcBq6JvM9OVgrQBr4LNZafYSzgZlw26ISFgW5EQepkiBq8wWBR4xayzYhbyvFO+jzf9ZEOzMsa/LJuTzQ5q1Ex7ZH2fNi814228A8SDU3C+Y/Vyl4do+M31+HF/dwdqZ1UVKD2YNJRU4wsRob7SUS2VsjcvEgGv4a7LpnTWONfMTzsvjRtRPYvPaIlL9sGU2+0kjLdpqR7yDcQSCkQHL/+SU9fYpToTTKBOKpD+BmQlz7pDvyAtSxzLbsgg0rCng==
*/