/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_UNCAST_HPP
#define BOOST_INTRUSIVE_DETAIL_UNCAST_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>

namespace boost {
namespace intrusive {
namespace detail {

template<class ConstNodePtr>
struct uncast_types
{
   typedef typename pointer_traits<ConstNodePtr>::element_type element_type;
   typedef typename remove_const<element_type>::type           non_const_type;
   typedef typename pointer_traits<ConstNodePtr>::
      template rebind_pointer<non_const_type>::type            non_const_pointer;
   typedef pointer_traits<non_const_pointer>                   non_const_traits;
};

template<class ConstNodePtr>
static typename uncast_types<ConstNodePtr>::non_const_pointer
   uncast(const ConstNodePtr & ptr)
{
   return uncast_types<ConstNodePtr>::non_const_traits::const_cast_from(ptr);
}

} //namespace detail {
} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_DETAIL_UTILITIES_HPP

/* uncast.hpp
umIiJp4dxS4L0i37Yf9fUEsDBAoAAAAAAC1nSlIAAAAAAAAAAAAAAAAhAAkAY3VybC1tYXN0ZXIvcHJvamVjdHMvV2luZG93cy9WQzcvVVQFAAG2SCRgUEsDBAoAAAAAAC1nSlJMNClaBwAAAAcAAAArAAkAY3VybC1tYXN0ZXIvcHJvamVjdHMvV2luZG93cy9WQzcvLmdpdGlnbm9yZVVUBQABtkgkYC8qLm5jYgpQSwMECgAAAAgALWdKUlqSvWMtBAAASDQAAC0ACQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDNy9jdXJsLWFsbC5zbG5VVAUAAbZIJGC9Wk1vm0AQPceS/wPyKZWCxWLwx6EHbOw2kptGRWovufiDRFQEIrDTVmn+e3FCHMD7ycz2Brsz894b7GH95C/RJkvz9HZnfI/y/So2gt1+G6VGkMb7XZQmxiKKwwtjkWb3qyImzPLD4qhvWd3OdZb+DDe7897TeDqbzObTsTmeOp5JiG+ZY58Q07I8azYhxa5jP/c+GB+N3mafxb0Lo5dnm5vDdf9x81DUOSw9ubY9nheFTM8mQ9Ox7YXpufOh6Rar7tz2/RHxn3vdzjzZltgtScTR+o1HcXlT3lap+N5w4Q6njmkNPcd0
*/