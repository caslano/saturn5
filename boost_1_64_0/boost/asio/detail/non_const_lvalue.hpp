//
// detail/non_const_lvalue.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NON_CONST_LVALUE_HPP
#define BOOST_ASIO_DETAIL_NON_CONST_LVALUE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
struct non_const_lvalue
{
#if defined(BOOST_ASIO_HAS_MOVE)
  explicit non_const_lvalue(T& t)
    : value(static_cast<typename conditional<
        is_same<T, typename decay<T>::type>::value,
          typename decay<T>::type&, T&&>::type>(t))
  {
  }

  typename conditional<is_same<T, typename decay<T>::type>::value,
      typename decay<T>::type&, typename decay<T>::type>::type value;
#else // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  explicit non_const_lvalue(const typename decay<T>::type& t)
    : value(t)
  {
  }

  typename decay<T>::type value;
#endif // defined(BOOST_ASIO_HAS_MOVE)
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_NON_CONST_LVALUE_HPP

/* non_const_lvalue.hpp
B4ZZauJcs//my8KCoN0+LsUqScyt7QlwJ94pkzAunJVh905tV0Yocq2FJpD4vUkvMQFMp4xNXM8XIu1dLoNM1vdBKepBIWv84HW48IgumMq57mo4OJ6bFm6EGrA4ygD2ZMIOot4qAQId+X34JbaSGL2TKU2cA2N0nrxVmGvWUPAWgZGggPZr+KJ5GAJArj488auiV3k99nZY4VB/+Eh1i33mOIAQPBskkuc7yQhJ8BDpv8ul6KlN3nZwWtNW55JZynWriG9/zzbcHr568wT48YI2zy8IojmjZt6w57vRx33YAOLs+z3rBK+EgHmDRZRRgWpfG1G2fa3UYInz+3VCxfJ0ByWcz++HZH820Av4Oxmg4aGcTAVaROG1a2mdA2SCTqcK/1HqfYT3H7ER20qIRG2nDxZRX3YYRD2oIeVHGZBl1la86/+N4HnhoW0cdj9ivyUiERR0wMk9zJJS0EqkDLuIQBu8Du/ubr4tnE40zxXqcWphATrYZ1NSibht3Hj91SR5m2OXqOUf7hmbti0jTKsHJmxtT6raXdWmXNDfMNguQYGTMXHcwOfZ/w==
*/