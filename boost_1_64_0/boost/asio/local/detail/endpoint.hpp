//
// local/detail/endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Derived from a public domain implementation written by Daniel Casimiro.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_LOCAL_DETAIL_ENDPOINT_HPP
#define BOOST_ASIO_LOCAL_DETAIL_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)

#include <cstddef>
#include <string>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/string_view.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace local {
namespace detail {

// Helper class for implementing a UNIX domain endpoint.
class endpoint
{
public:
  // Default constructor.
  BOOST_ASIO_DECL endpoint();

  // Construct an endpoint using the specified path name.
  BOOST_ASIO_DECL endpoint(const char* path_name);

  // Construct an endpoint using the specified path name.
  BOOST_ASIO_DECL endpoint(const std::string& path_name);

  #if defined(BOOST_ASIO_HAS_STRING_VIEW)
  // Construct an endpoint using the specified path name.
  BOOST_ASIO_DECL endpoint(string_view path_name);
  #endif // defined(BOOST_ASIO_HAS_STRING_VIEW)

  // Copy constructor.
  endpoint(const endpoint& other)
    : data_(other.data_),
      path_length_(other.path_length_)
  {
  }

  // Assign from another endpoint.
  endpoint& operator=(const endpoint& other)
  {
    data_ = other.data_;
    path_length_ = other.path_length_;
    return *this;
  }

  // Get the underlying endpoint in the native type.
  boost::asio::detail::socket_addr_type* data()
  {
    return &data_.base;
  }

  // Get the underlying endpoint in the native type.
  const boost::asio::detail::socket_addr_type* data() const
  {
    return &data_.base;
  }

  // Get the underlying size of the endpoint in the native type.
  std::size_t size() const
  {
    return path_length_
      + offsetof(boost::asio::detail::sockaddr_un_type, sun_path);
  }

  // Set the underlying size of the endpoint in the native type.
  BOOST_ASIO_DECL void resize(std::size_t size);

  // Get the capacity of the endpoint in the native type.
  std::size_t capacity() const
  {
    return sizeof(boost::asio::detail::sockaddr_un_type);
  }

  // Get the path associated with the endpoint.
  BOOST_ASIO_DECL std::string path() const;

  // Set the path associated with the endpoint.
  BOOST_ASIO_DECL void path(const char* p);

  // Set the path associated with the endpoint.
  BOOST_ASIO_DECL void path(const std::string& p);

  // Compare two endpoints for equality.
  BOOST_ASIO_DECL friend bool operator==(
      const endpoint& e1, const endpoint& e2);

  // Compare endpoints for ordering.
  BOOST_ASIO_DECL friend bool operator<(
      const endpoint& e1, const endpoint& e2);

private:
  // The underlying UNIX socket address.
  union data_union
  {
    boost::asio::detail::socket_addr_type base;
    boost::asio::detail::sockaddr_un_type local;
  } data_;

  // The length of the path associated with the endpoint.
  std::size_t path_length_;

  // Initialise with a specified path.
  BOOST_ASIO_DECL void init(const char* path, std::size_t path_length);
};

} // namespace detail
} // namespace local
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/local/detail/impl/endpoint.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)

#endif // BOOST_ASIO_LOCAL_DETAIL_ENDPOINT_HPP

/* endpoint.hpp
4H5exBc3SY97L6xU/tHx/V7wBPizUdg3OvKdDGcrV9RGaS80zy8X+e7aPgTDD3Lk5YrK81X+ZOPf37Qv68Se43P1tZqvj4vf88xv2m75xY3z/MVtMz398cy3yne2FaYd6r8psN9bhu7dcJWEyfDNsu42bdF+1T0Nubvt/WlENuj+VtBd7tlT3K/MFL1naXMj7llQZjwyw0WmbnfEWm2VKTJ66u730rM2Rfvd9LpbIvpdldmMzAiRWdM+KHN/zGUosW3eJrO/X2B/KdwuDbl5lzNTpriv2h9t2Wj6I7F/EWZftil6fzVNz9Z/KZ45OMr1yGRvdpRB2Vw1UP5+nB7Yr8BRt1R2gjyzFbjOuWPlr6njKufYs22m2K/2iZ37PuRO275Yy3mojmfoc+oskb8tfnZ8nGMPAfZpUZkyZO76WaDlac9/fnHzWbvELdXX3mpD23aNI+zCkhIN64e/vwM5Zkyf4lul5djEyRFGFr9LmKU+ypbE6ab4k+MTovaZS+TaiWZviA5yjdc1vuz9Ifa+xJXnLdP/cY6w1tX7JHx36s2tDv8qUz+vFf8TfBdIunAz+Zgscb5C7nJggX+G7utUJHG+Nn5iPPXTxLly8eJqslvlOsK3JW4ZcSdrfnQ0+XEudtPHVzn327hF4jPVd6W1SvuEYBoT4+5lJtJPffOkPuen8hzciu9rgbPHrgzfgyFLZea31vPGL8xJ7Rk4bzzFa5+A+XLt0Jnzs8TelXxr4bk32wyR6RTo1/Waa1trGxJ/4R/SUiLP5AzGf3Nr7ddTLuoc3q9Pwt4G+3Li+QMysxAGTTVmRAZ/a/9dpnSashj2KbPbC+6Hs72Q+kcdlX0fgu3FXNMvSX101f96Pft/te4Buxzebff9dznrv+z366j/HGEUyneVHaTvbNH7qZONXGexn4Y99W7s9H7Ik6eOPp3kVcF24j+Pfkn99Tm3wm4LxC9e/dx9z0zxO2KF/CpM/Vsmfqc665pJxx7xG23Kz26xT7QScFN5156MT4n/TOwmfnaem3fKIvHfx1y8xaZ+nCJunzD/qtK8Z47fIu2O6jV2h96aSvLFPHf7A2nwhdVv87zcTfxP9oXVUdPfV4v/48F3Z43nu1Y73KTeUXDRq++ovAp2TYtPjfKO6lfZ7W312TW1Ki0+3Yp4Du6pcjkZWpfrbrDrcVxqYmo/qdAN7K24VuI2Qu2USLEneNbny8U/S64bPLN+uda5mxz1Kq+RenXaFne9KjL1Ssq+uJVFPlObfU/y20XfV3L3ltj3lUS2wX0lX9xydPaV7NI+cu+F+lH2y6PEtaKscGbBCTNmz84PbsBQwviZtgelUs/dz9qEM++B88W/xLQBxs88L8W+90Kp5LVeS5+D5gfy35WeXVHScyvpyfZIj76Oe6YnOyzOP/2KcXbGcX2HyDjeTBzzPOKorwGecSSc893bmefGzzzHfsX4B/Mc/SbPJ2l6SvzRy1CRV3po6leUl57XUL4XeZcj42ee379mmqKVo/EdI9O0gTTV3aN7kpg0FQQLEm/HgfQUR44paDi/PjtF7LVi/M14WhP2JeF67n1JzH2qiqjv+6OkayPpqvdOFxXEO131YfHOy/hq8XaWpzmZkXG8kzju8oqj2dWo6XsaBfPlcJRrXkL89ntfk+cpzzEkwn31vY3QF3Vvo92dopdJa2vUOOoOQJ73jnANlkn8v/r+P00pk5uzItN1KeGzPdMl4yleeU+4BvcAwv+r7wF08YivvwdQ9D1lmr4XTPT5mF576HjN02z63kPR9zDy2kvo6M27fE3mh/5l1Rsdp1adPXX4GdN7P3LVHRMZt+hhu6++4oyqW0e8WX73Pe+cfOeGb80=
*/