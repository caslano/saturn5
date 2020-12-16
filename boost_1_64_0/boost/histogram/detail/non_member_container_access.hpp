// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_NON_MEMBER_CONTAINER_ACCESS_HPP
#define BOOST_HISTOGRAM_DETAIL_NON_MEMBER_CONTAINER_ACCESS_HPP

#if __cpp_lib_nonmember_container_access >= 201411

#include <iterator>

namespace boost {
namespace histogram {
namespace detail {

using std::data;
using std::size;

} // namespace detail
} // namespace histogram
} // namespace boost

#else

#include <initializer_list>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class C>
constexpr auto data(C& c) -> decltype(c.data()) {
  return c.data();
}

template <class C>
constexpr auto data(const C& c) -> decltype(c.data()) {
  return c.data();
}

template <class T, std::size_t N>
constexpr T* data(T (&array)[N]) noexcept {
  return array;
}

template <class E>
constexpr const E* data(std::initializer_list<E> il) noexcept {
  return il.begin();
}

template <class C>
constexpr auto size(const C& c) -> decltype(c.size()) {
  return c.size();
}

template <class T, std::size_t N>
constexpr std::size_t size(const T (&)[N]) noexcept {
  return N;
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

#endif // BOOST_HISTOGRAM_DETAIL_NON_MEMBER_CONTAINER_ACCESS_HPP

/* non_member_container_access.hpp
x4fffy3dJlWWuA+LAtziu1hQDNwv78P68uIPvA+LnblWousroes1o3iLH6b/LX2A25lYYv3/drWe4Dqg7l+OtDuWFwZLAl96GU3snsAqNdIXywUcqHNj1EVUfCM47CoPXqduvHyZdGRRt4TK5M7h+E9uIsUt+lO++Jjx5B5uKBzfQCSsIT9cuFkTe94vfIe8rWsQo0g9rpFxCE8VLeKzSrGYdOf6bArdfiuF8lbCXA51UuiVjMupTuTQHAp9hHFzWHHj0FwKjXJoLoVewqH5FLqIQ/Mp1MahBRQ6m0MLKPR4CoUWUWgNh/Jaw+8RSqpUfLFTvKOMlbCnKH3lFfvlJpA3vjhHfGaZsQny3RTlH1vc40MLBJj1nHcWG4paBCgepErhrPp8fJyhYc2TRJ0i7eNKbEbw8kQKrFdh/RlHQevJlAM1mQmzYiK8piUXMAAsfjHjYwbdDASSO0b2h2nEpYWK+OJcsfleIw9/hDQiiBI9MFa1rd3i+17OTy7n5/JEfn5p7pSfz4818vOQWc/PiJuNZuClzGy6ieOPB9KahRg9Wu4AZtBMLH9HglhxTXAyTXGyNFObkqNV56L6cTG7R4Ljix1id6VBNhfxxKnp3NU5qQ68IhQ2Uk0h6KuA0oIw5cgvfAnon2gN0u9lXXR5IskdfMl6pdpafpYbEZAQObOOexmUwOJs0Z97oxw/xfkckHT92SrmGHE/zXGB7Bd75tB2HeJiMiY+x9Ryqfv2UKEhuADBn+JgJ3Xf2G+7Vabm0FMLlVJK2OH+LKXk59IoEp//mGIi5BBbZBSeH7de4RdPyPcAZUH2CRa9TxCXcDzsCtXNRq+LgdUyjHE9Yuwoo4v4V2x+/Rd8uP/GLlDb7ksrSzsXWGJ/SrdSWDydd9IaqkuC2NT4xmyWO9oKNtnvI/1Iq8ZIQKKR6ovvRkXEF2eK/dg0bqgudvuC6WIBlhqRiHgAzZgawxvz6dfJmhGJ5av8CzWBf3PFNv7NF5v5t0A8xb9F4hf8O1kUFNIvdqXwG+Dl/RcgKfHFtWItj6O1ga+rQJ8Ic1DmOZkRf+AHZxBtVGa426qHVpkfTUFApnwp4BeHfCmKpnRDR9kPshaiyh9efZHe84g1NidqRkCmfMmNmhvPQt+RTN+ZTD/7A+g/+ibOVLBJyLcwd/0WvXXAi4C/4pbDmC8k82szcNDS75qTNFXzBWu5eIMzxNfnSWOzTLoKPDhJBlcGg2ix833cYmkm1VxdwgYXb82gMWw6WLkieGMybgVwgx69zmITubOhiAnOW6p0zqMkbvm0rpZ5eRzbA5izoa8Z7hfLClU/nhecJRO/ghN/3cuM+MSxWsYgxakxWp/ZahO3FRNDmVo16ZlOt/i67IBAg61db239lcbkFCUl06cmK+X0B4xAuls2iz8biwfvlvSrW+4lt5MXeI3mOX+ovoJx0vDfuVGfEH0PBfqBRhoenhbyZqJfg/qBrEKLzSH1g8xN8XYglEVqB80GwxnYs0mThlaNQMNWeNZcWUp35hMitdH36mTInALUBUKKxBt6SH2RMsE8d1WV92J5kR7soWgVQ7nsCjjcEwyl1s1hfg4QP/WKeo6knivmK+q5dXPOTrwDPUeCnvMD6GUpeg5Jzynem6PTcyKGzkW2+IsKzT4XLjrWp2qlifbpw5SjY/+djt7b6K+764ZvrOLprAOvcHTJl5GztCawzum8jewPSvNAslG9N5DWv2B6ZFPJNNwLJ6J+XR1ZQfedujZhfLCa7Y90bwngC14VMO1F+ygVb801+o/QVOoXg9cyyA6v0L1T7Y5KXK9e7cBvLn5zT9jrK4tvs++tLoZRk/0T3AajqcgN31QbdHFUn1g=
*/