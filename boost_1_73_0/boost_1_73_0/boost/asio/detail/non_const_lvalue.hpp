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
4Sma7ptcRIc6t004ElLTih6UrLr/R/ahuss4ydT4iMgts3lDui/8Vf7it4exCNnQspv4QjSriVBeoSeyXAB2AXXeZAVdyxFVUqri0koWJfgqer8iZE2k//tr4T2A0J/en//Aj0Tbuy8p5N+bGCwKKGEhixpWIlDrlwIA4IDJE4DqjqeL94LmFMYhNxAaiVMkaB0opTf9W7/sO1nulRwLEZcbZwx5AfYnUuSLYEhohNK2gMpoIw9iSMROLewIFBLo+6pp61orkb5m+UzYAyVf/U6kLDm1E1FQG5hGFkneeEjK+cxFnl4BaB/bn1bLroykD/blAUVaJ0WJpCiCtL48UDtOWYj4LbpKA0jK9xB0+P6wNZUQwIQ2ZwrYiyZAFpul1C2J493LWHdJVEcdVhBEhC2aZfI6nheydCERQp602UuhszPs739sYxsC7UlXJJolzqAOXQf67sOW/XbE1el1VfvVVgNZIeR95YfDMl3q812KwbT0lKnnp5D6MrUniVpjRgDqGPxojxLK1OgNYCgkNJuI/pkU9RhkmiaLGGL0JPNYoR/vC0/XkwxmmEM5yotfTOel+G0HGyfRNQHdEEHw9TyfpPwpqy7H47zhHxAhSfqvzk55aj6cnn+4jIfQrsaJTJOtdkWbgtAMPevH
*/