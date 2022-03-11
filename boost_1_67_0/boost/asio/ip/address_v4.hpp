//
// ip/address_v4.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_ADDRESS_V4_HPP
#define BOOST_ASIO_IP_ADDRESS_V4_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/asio/detail/array.hpp>
#include <boost/asio/detail/cstdint.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/string_view.hpp>
#include <boost/asio/detail/winsock_init.hpp>
#include <boost/system/error_code.hpp>

#if !defined(BOOST_ASIO_NO_IOSTREAM)
# include <iosfwd>
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Implements IP version 4 style addresses.
/**
 * The boost::asio::ip::address_v4 class provides the ability to use and
 * manipulate IP version 4 addresses.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
class address_v4
{
public:
  /// The type used to represent an address as an unsigned integer.
  typedef uint_least32_t uint_type;

  /// The type used to represent an address as an array of bytes.
  /**
   * @note This type is defined in terms of the C++0x template @c std::array
   * when it is available. Otherwise, it uses @c boost:array.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef array<unsigned char, 4> bytes_type;
#else
  typedef boost::asio::detail::array<unsigned char, 4> bytes_type;
#endif

  /// Default constructor.
  address_v4() BOOST_ASIO_NOEXCEPT
  {
    addr_.s_addr = 0;
  }

  /// Construct an address from raw bytes.
  BOOST_ASIO_DECL explicit address_v4(const bytes_type& bytes);

  /// Construct an address from an unsigned integer in host byte order.
  BOOST_ASIO_DECL explicit address_v4(uint_type addr);

  /// Copy constructor.
  address_v4(const address_v4& other) BOOST_ASIO_NOEXCEPT
    : addr_(other.addr_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move constructor.
  address_v4(address_v4&& other) BOOST_ASIO_NOEXCEPT
    : addr_(other.addr_)
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Assign from another address.
  address_v4& operator=(const address_v4& other) BOOST_ASIO_NOEXCEPT
  {
    addr_ = other.addr_;
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move-assign from another address.
  address_v4& operator=(address_v4&& other) BOOST_ASIO_NOEXCEPT
  {
    addr_ = other.addr_;
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Get the address in bytes, in network byte order.
  BOOST_ASIO_DECL bytes_type to_bytes() const BOOST_ASIO_NOEXCEPT;

  /// Get the address as an unsigned integer in host byte order
  BOOST_ASIO_DECL uint_type to_uint() const BOOST_ASIO_NOEXCEPT;

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// Get the address as an unsigned long in host byte order
  BOOST_ASIO_DECL unsigned long to_ulong() const;
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Get the address as a string in dotted decimal format.
  BOOST_ASIO_DECL std::string to_string() const;

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use other overload.) Get the address as a string in dotted
  /// decimal format.
  BOOST_ASIO_DECL std::string to_string(boost::system::error_code& ec) const;

  /// (Deprecated: Use make_address_v4().) Create an address from an IP address
  /// string in dotted decimal form.
  static address_v4 from_string(const char* str);

  /// (Deprecated: Use make_address_v4().) Create an address from an IP address
  /// string in dotted decimal form.
  static address_v4 from_string(
      const char* str, boost::system::error_code& ec);

  /// (Deprecated: Use make_address_v4().) Create an address from an IP address
  /// string in dotted decimal form.
  static address_v4 from_string(const std::string& str);

  /// (Deprecated: Use make_address_v4().) Create an address from an IP address
  /// string in dotted decimal form.
  static address_v4 from_string(
      const std::string& str, boost::system::error_code& ec);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Determine whether the address is a loopback address.
  BOOST_ASIO_DECL bool is_loopback() const BOOST_ASIO_NOEXCEPT;

  /// Determine whether the address is unspecified.
  BOOST_ASIO_DECL bool is_unspecified() const BOOST_ASIO_NOEXCEPT;

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use network_v4 class.) Determine whether the address is a
  /// class A address.
  BOOST_ASIO_DECL bool is_class_a() const;

  /// (Deprecated: Use network_v4 class.) Determine whether the address is a
  /// class B address.
  BOOST_ASIO_DECL bool is_class_b() const;

  /// (Deprecated: Use network_v4 class.) Determine whether the address is a
  /// class C address.
  BOOST_ASIO_DECL bool is_class_c() const;
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Determine whether the address is a multicast address.
  BOOST_ASIO_DECL bool is_multicast() const BOOST_ASIO_NOEXCEPT;

  /// Compare two addresses for equality.
  friend bool operator==(const address_v4& a1,
      const address_v4& a2) BOOST_ASIO_NOEXCEPT
  {
    return a1.addr_.s_addr == a2.addr_.s_addr;
  }

  /// Compare two addresses for inequality.
  friend bool operator!=(const address_v4& a1,
      const address_v4& a2) BOOST_ASIO_NOEXCEPT
  {
    return a1.addr_.s_addr != a2.addr_.s_addr;
  }

  /// Compare addresses for ordering.
  friend bool operator<(const address_v4& a1,
      const address_v4& a2) BOOST_ASIO_NOEXCEPT
  {
    return a1.to_uint() < a2.to_uint();
  }

  /// Compare addresses for ordering.
  friend bool operator>(const address_v4& a1,
      const address_v4& a2) BOOST_ASIO_NOEXCEPT
  {
    return a1.to_uint() > a2.to_uint();
  }

  /// Compare addresses for ordering.
  friend bool operator<=(const address_v4& a1,
      const address_v4& a2) BOOST_ASIO_NOEXCEPT
  {
    return a1.to_uint() <= a2.to_uint();
  }

  /// Compare addresses for ordering.
  friend bool operator>=(const address_v4& a1,
      const address_v4& a2) BOOST_ASIO_NOEXCEPT
  {
    return a1.to_uint() >= a2.to_uint();
  }

  /// Obtain an address object that represents any address.
  static address_v4 any() BOOST_ASIO_NOEXCEPT
  {
    return address_v4();
  }

  /// Obtain an address object that represents the loopback address.
  static address_v4 loopback() BOOST_ASIO_NOEXCEPT
  {
    return address_v4(0x7F000001);
  }

  /// Obtain an address object that represents the broadcast address.
  static address_v4 broadcast() BOOST_ASIO_NOEXCEPT
  {
    return address_v4(0xFFFFFFFF);
  }

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use network_v4 class.) Obtain an address object that
  /// represents the broadcast address that corresponds to the specified
  /// address and netmask.
  BOOST_ASIO_DECL static address_v4 broadcast(
      const address_v4& addr, const address_v4& mask);

  /// (Deprecated: Use network_v4 class.) Obtain the netmask that corresponds
  /// to the address, based on its address class.
  BOOST_ASIO_DECL static address_v4 netmask(const address_v4& addr);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

private:
  // The underlying IPv4 address.
  boost::asio::detail::in4_addr_type addr_;
};

/// Create an IPv4 address from raw bytes in network order.
/**
 * @relates address_v4
 */
inline address_v4 make_address_v4(const address_v4::bytes_type& bytes)
{
  return address_v4(bytes);
}

/// Create an IPv4 address from an unsigned integer in host byte order.
/**
 * @relates address_v4
 */
inline address_v4 make_address_v4(address_v4::uint_type addr)
{
  return address_v4(addr);
}

/// Create an IPv4 address from an IP address string in dotted decimal form.
/**
 * @relates address_v4
 */
BOOST_ASIO_DECL address_v4 make_address_v4(const char* str);

/// Create an IPv4 address from an IP address string in dotted decimal form.
/**
 * @relates address_v4
 */
BOOST_ASIO_DECL address_v4 make_address_v4(const char* str,
    boost::system::error_code& ec) BOOST_ASIO_NOEXCEPT;

/// Create an IPv4 address from an IP address string in dotted decimal form.
/**
 * @relates address_v4
 */
BOOST_ASIO_DECL address_v4 make_address_v4(const std::string& str);

/// Create an IPv4 address from an IP address string in dotted decimal form.
/**
 * @relates address_v4
 */
BOOST_ASIO_DECL address_v4 make_address_v4(const std::string& str,
    boost::system::error_code& ec) BOOST_ASIO_NOEXCEPT;

#if defined(BOOST_ASIO_HAS_STRING_VIEW) \
  || defined(GENERATING_DOCUMENTATION)

/// Create an IPv4 address from an IP address string in dotted decimal form.
/**
 * @relates address_v4
 */
BOOST_ASIO_DECL address_v4 make_address_v4(string_view str);

/// Create an IPv4 address from an IP address string in dotted decimal form.
/**
 * @relates address_v4
 */
BOOST_ASIO_DECL address_v4 make_address_v4(string_view str,
    boost::system::error_code& ec) BOOST_ASIO_NOEXCEPT;

#endif // defined(BOOST_ASIO_HAS_STRING_VIEW)
       //  || defined(GENERATING_DOCUMENTATION)

#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Output an address as a string.
/**
 * Used to output a human-readable string for a specified address.
 *
 * @param os The output stream to which the string will be written.
 *
 * @param addr The address to be written.
 *
 * @return The output stream.
 *
 * @relates boost::asio::ip::address_v4
 */
template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const address_v4& addr);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/ip/impl/address_v4.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ip/impl/address_v4.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_IP_ADDRESS_V4_HPP

/* address_v4.hpp
Zpuw3jRfu0udIs5TTWUJMoSayf0guKcvNwf5QXu+XVEOZOXwwW3JcpT1mvje8U/r4HFv9DaSu995oDxOHuCu7tBxm/Uce9/5oPhNdm4G2McMzyGNacaBupC79oafH6YulGD9Mj1t1CeaTmZp+LVijFgzVHxZ3Ws1FcAnXNySlgVawdDuVMmFrGI0wL/YJ4ctknw9aHyFuoPryLCuVCxB49qy7ik/hNzM7DHAhsL1SXYBzBAwyvzalJgx0ptxBMIt0RCG5uo56KdhiTd+Zb1LZfv+Ruad0Nt//KMSndE7hHFWy04XJnvtrVLPWja7T2IjoGdfRzeUkLlmoREziXi/Z2zjeAor2I4OnfzPdETmnlwzp/1AX9PngUopBU6JledZNppqBFNZjGq2fqmAELdoshITVAxt1n8pgLCnhuoNk/+xTSagWTRd5eyzPDZZpiBTuISrMkWEOemSKBbiwuf3zePxYcIHVSy7dGnELuxDFlWmaetTs+UnijdMVPy4vilwxIIUzIu5toVvK+itEzHF4MTuBPz+mahy3Mxwev/0c5FvUhVzRvm6Sc+x4735ydIHRLViFuWaeTW0BYb2XF1lZWb69nC5tBWG5hxXhXAGJH1o9vXe2zqzoRr2DuNoXqYOJ3d9I6yPpAv65W2+8pJNq23OY4J397BiSCuDj7k7zkPCB/2F4an8UGWd7fD8LKYM/47vIwbmUzOyONSFqGUU7MV5iP28mS7byK/WeGWZIY1dqqHail97L63wUlVK2z714HIFzvfT+/FOtLJJQVNu0cGCeXY+ftNBk/lkPq7L6HWIFqbYSGgPCvGHDOonNAz6VpFLEP6qIY7bcTjCX/VU8xH9wQo3d04cG3d1hSePaKWpLsbji5htpTbHw9t41ahWbgtzoe80p7fD9IFEFj9Rx8TZN2XHzLkwnzSxVdElaCop3v7kYFapFehWWrUVym9xNZvF50uwCvyx+BKv5tnJs+9Kcwfz0OWAV8bK+iNuP0+rzGyV/TU+99/Gdv9yQBad21nr3MZ3f0sw88VluxeV3Anbb+Pz+WLPZZRjZ2n5sWzVTKGVpttJa/uxbRVtmdEs9oyXlFxxa3Bjnhq5G7v861fcuAngNDROjYUqtbhZ4er6zbrKvW1Bd7hIzFEnmotDt8551tCYKLvrK11cvK6CTc5GlslYJbvpDYduhc1u6mqN7IUtxzZnD9KGZ2obRGyCLYKWUTdXjizadkJur7vP6bY4P2bvQHea9z8/yYeLdq6WTodON6sYd8tXzVNeiT7AnSq+A54SPh8vzVcuj3bwuxeinCOIBMWAQJIiCYllFPGUMXFWTHHUz6KGEQTHGehCsp0sJOYx0ojf8RH5eJrwrDd9SUVk9tNDVGHHpKByAsmKTqkLBL9M4bJ8zXiegg4pZ8RLqp3EqaJ+pxn0OLR3iQFw2o+uQPn6YLHassBVB4ZoDGW6vkAUFWt72R4kWI0uKjZGoew+OewkADYT9ebwYl3ZEYwsCWZkP6QQZ2f3QW6JkezABjUjaW4hspiXeelAZYVQJBVOKFBFiWb+QjZSttF2ac2UcHPiCscKaaZr6hRz8hFLFMWqEb7/ipEWRSeGJ4bHSWBE4EbgRMakMCRsI2wkrCPsJAwjDSRhjoKPrKNdYgau828orhiu1m76r8Wv5K/Tb/SzjjbS1so22tY+N8w2x9bUVKRYoPzydYo1vdvE28SbxTvEW8W7xBvFdZBcMJzS/fEj8KPwe7K0mEcNFhRnbj92VMZVLGIHiTJFmIR4hBRVpVWFeMuMpR2svaMdqi2nba+sYXxpjKUdrfWjPavNp62jTcYMwA3EPMNcxwzB54rPu594rruft055mjTtYxeCngg2FBZoyYnU2MTY3DjMONDTgadppyinWiYtMKuwnbC6sA7XA7YRtwl3GTcGthS2DbYdNgQ3ErYBM5vXHx3k90TE/Dwlnk1EAFTy1QBK7I+Yt6229TMV+Mia16spjDKL++s0Ikad8YEOmw6iLU6BrJoUYwJa80yuE+6DpdokOIXaRUOu59FDskVB5+Y1g6tFRVb3NydD3nQhPrthqOBhpndLe2E9tU2A73tEH1EThaDJRAeuiMgCIQk/0uOeZ/lBjo3g0DLEIc6MGNE83Mar4jT0xIcYjTr/E5ikDNYL2nFe3/znR5h4lgwkMQrG7L8ErnAVjN0bbxfar3JHCaqkMl7yHwpU2HERt3e0pxxxENG6Rv2k8eI4WboQZzDVOmtXpJXSJFkWULHwKAybOmntf//lK0AmX03rmNRblKP/l08jogLLeJlcT1mRNg+gSdQERu7284ahRq8drYDOs+tRH2mepEbfIeAV7og63T1ptHgyPSYSEOd533DE+64MMVh5I5HflMip6Vi2P4FuBktXyMLyLJuSpH4Kr01icTYkqKVzVzVIPj9rOTOseWYiiFYFR/4zGzljLIUhFgBelUluMbtxE8xjnp3DRK7AbBxLOLebD9Gp6ug3FlSBC3GlqMPKDZlVYCuiB8d1ccB535PaR/48bA69dNOo6cIF2a7aTd4FE6A5o08cYxpOhbFUllQdzSIfpaga5ZAek2ya1kxiHFOzgdCwbAWhKd/oPZaZvyPVVWBotYLQmm8ooZumX/Y7Vbdo/VxWC79eSguBr8g5wgJrX1e2DoR9gfYvDAmPakJ/lZkFAnhlyqGo0aYFewG92cP4DjLB0OBTANbRed6qFZUyoR448DKj7InuWRvoLRlxvhDY8xK1zJpuRvvLAqVxHhHyCDjyErSsTjbDNlgba7uoA+S8MPqjagUVq3jBPKyo9YNdtkNbkzXcP2EJW5ku4yYFq3mxh7W1YsZQk+V8uJ9inWMdYz14f3x/bf8s2LcooGan5qemtwZwWnf6J+A5/jlmsVapHXsJOwQ7FHsTux07ArsSexHbOk37FelV+RXNTe/V+hXjtdI0QtWAdsOk8thtynnq31TylPFU8xTJ1JKJghijGCRIAkgDyLwXNmsZDh3tzFfuLW8IT0oqRXWhBjjRBxGYsZfJ5/KqlCyq3JgcplyV7LXsnOy+nLAsqRy4bIVclOyMrIYtji2CbbGduR2N7Z125o3U7eKN1q3PDXMWaBpFj3hcYQ7Y1goxm/GqCXvoahi7/2V/TONzY0yfn9dT8inYi+hT6NfoGdij6HPo8+g52LnoC9jZwsnsmLAgAi4wed4vbo0yjbqsnrquhPp8r5RspPQCSZBEBZPsPyF6dnPpiSPqpAtwqA0OVMimrXpG1KRuSxWt5ifGn5wvl8qlNcKIZsb9HCGvEVHLmzUWSH3b7XTzvAsf+5uoNZiQ6LmG4/IHDaSNjnOjjSsmO2Zd6gH5QMdjClRVUqrCY/1yUCPmz3PYC0yQHbRgqnD5yxHVpyZMFuY78hMpyuCq3iLVaNozv+W5ZkLj/8yxZwjEKe3EVVCr4qlT1Jko+iRa5udM/quMlyAWQxUzibfQqpBnElQgTtCkLFXNThQhpi+iKaIo4iJhL2YpRpAz+dcj0iDSItIhEiMRIMGKgI3UNb+7DN8W0FlQP1Bv0AXYRtgg2GLQGWATb6VlmGW5aXhplWWDbaSlQjlPUK3aKN9+51LgTOhUoE/oVmBM6FVQrv4jfy+PqgenB6lnwF5bmjeUX5K4e9wTFR+1YN3bAQTtAmIC0kITQpPiaS3RZ/jrzm/kp9Kn86vB7+0n3mf8K8Dv4qfQp8E/FToENhj6BHYdOgKWK7hocW6xYXFZMWdhWrJnHeA12xtI3KJl/S/butoah0P50L+hv71xrZGjai31p9O37KfKNxd2DXYe9gG2CHYadhl2BbYMthh2HTZfMIsW34uvVoglxVuwT7HiX0F2QGN3Y2PhUHE2S1OxCFiU4nJxeIWuzH/ZiSNqaCrP3hsSqEpNmfWcqFHdmircJU+cP0FfM4NLEYSLzZz7QUJiI6VENxEsSvoy29ln8Mthg9rpEdHwmD/Ix2sP66UbrOdOG1tM7pjhkvWg+VicmiGsi5EknGuFvwN1pwuT2KiqMhRL4iWpMBN2qLZXjpzNvuPFSUW5xY7jzjVf8kwpekaZGxSlGtmpIuT0VTRVFFVcNOzVLNXx8ubKzSl9Ku0q9SrBGXEaHAyITA0Nmy3QbgGeBfYD9gZegG6EDoIuBp4B1/GXmgeZFxsHF5eZ11iHmssU80TVGo3K7U8uFc6UThX6lG4VxpReFeXKP+L34ikCsQIRAgZ2jaZpQwUlCbuHPWHxYQuGvSVAVgr/BP8lWPdaF3z8m6g9uHmjO7Rdrt2+Waf7sh2vPbrpp3u2na9dp5sKGQIdDHkCvQ4ZAc0VXrQ5t9mwuayZszEt2jMMMJstCFRK2Pw3XHwVfHV0N3xHYg/EocGmwGbBOt+o1XbZ7NUy5QToRegp6GvgHOBR4Dngue8c4EzoBehs7nR8ODumFj6AN3NrSoUqhzWfhqeSiNf2y0gkQm2ROsCjoEH8IFhHYi45cUX9+ARutIGVAm9KaqBEZerButgqfa705fWOXVqxLIy/UBr8CoU7ij3TXrXIByB1UfoPvPQ2ybGgilmZ6atyilG0ic88rVjOwmlyz5hAuj/dX/KofEyVX3k4rj8dUvV3ym4qk1IVfbon04gLodHcOdoUsRiPlaWmUpUiQZLunbHTopNxzGS+MlGCW0hF2CThXL1CkclC+5GwRVW6h4M1ylXZVNFU29TT3Njc0JxmZ2ncesr9bz4aT8EsYiw653MVexrVWsHdADwL7Pvv978A3Agc+F/0PwFsEq02DDMuN4zMrzJuMo42VKoWSqj3GDfY318anhueGA4Y3hhOGL4YKkyc7b/ts/xA/ID8rNnKzOCEiUjR9m16sROyl7x7RzGiNUEkQTBrGGkoPV8kco503HOOdlRydnU0cb51xHNOdARwXnQUcjZxpgKHAQcDnwNvAEcB80SVTi38De8Vqbypac2Bd6C47CBGMea2i3Csdcv1zP2LfSx91vrS6s7q0cpOk1rbWYsby9hTgBeBJ/+v/jOAR4Fn/+f+c4BzgRcA8/mT8bGMOHa0GUZNBmM9qnUOw3zOymrOm3oOohlayF7ovPJOBIdlK0hNxcaPSa6aXhmvggPLFaTWYsMUNXYbs7zeYb/kvpYsT76jzFYSb+Uzlp3mMZ/cEyjrCi0k3Fxf8+kQ3rn/JiE46MfwZ1yXbSX0Fk5SCMcFMv23AVvGAcdWtKkXRPVfQeaYB9jvnnmAQEARjQq9PE9R26zxZni+zt8bjRAXj7wiT0Hb6mwz8IJ5sHiLPEACikS7VE6haBXPSYeKtLqw27TxajQz+hEvoKnipOckaxLPr7FWl1QZrw+eaPbKr4qv2q+e7iA4nsaQXGNeWlvbXNtcW18Y2hjdwGeFZ9ltu2z38eTxUfAw8Kzx9/BI8MrxpPHrB1afSXMrcmlze3PXcxlzVWqQbAY3SKdCpvTSpNKY06BTndKkUpvSoiZF40bjSiFFIcggRl/oLG05eTQ133t2vCA9KGlPtWIabkSu/l1N2E7dVOalbVHtxO4y7ahub2znbg/uhm5J7sBtKe6ibWduN/Jw8BDwiPP/x6fOs+fBwpvKV8rbyvfBY9oKRYfufowTw3ndkSOmPZ47pQuTB68HMBeAbnJqgq56Stvm0ibbptbGA18PXwh/BC8Knw5fCV8NLwsvDt8ILxDHJse34x3YgIEh/9O2mmr48/QRSEAqKPoJ50mZCGiES1Y6yYCI2HOVPw9pJEy2Aq/ebEBFZLpuUKQ0Krpc3Vq3KNZng11nVBYKF1Ec42qTtcHMdmAfVhoB0HQp6uWpkee3QMAirHvqZM4JRSH1j5vbxznDBkLqlBV5Wkv+BQJ0qFJcBIUXJlbf3JS9R5f3jDtVgiIIIlbXXIQ9S5f5bBPdiDLUfsWNI7IAdLuuM2Ml+AnLplAQF4VA+KpSPuRqgB4tKF/mKsaWrkfVQwfLs5KBqkc6S9IjCrIaK2Epcuf1hBLfQoBpmimaqVr4SVhaGOZ+TZRDS11rTcuuzZ6hgaEBXEhYiL2zq3N/RX4VZQVjxXp1b4VkpXxFerX+2dFG0lrRRtPa26bRxtC6kurjsmtHiyadDoNOne6MLp0Gg0ad5ow2HTUIDhNe4/78PuMO03XIspPzSZOql3OOw41Lbhoji7l+7193TH/CSOKIKjztueoV3q3pVe1F6yXfZegt3HnqFd5Z6Q3dBdulqYaTurB6km6RTpP60KIVFyWvBLcF7z3nRPVZOqPD6q7ZW1TeEgQtdBOUzXntpetF78WJRpAOss8PbQDrNOsy6wprGWsx6zprvm6WDHcWI53wE7e8YF5yybCaJ7BIfCNR0RBHD8uhfwcctNIyPKJwT2X+OqSTMJrqM30zvzLMTOWgadl0jKXGdfGCWd81th1ZCRwcZumM63UWFxMbqRN8KSZQ1YWpF5gGfi9WP4xp+fkbfGqQ2ZJ8F5WPa4YVhBp4AiQbojKr0FC9qXqCOHwWDUd6h4Sd2twP7ipJtiCLhl29YdJMbca3VmQDjDAItUfjgf7ASZVMKTNhl2ia+QscVryC4nK+0LJ+5AiCObWFUdJUrYpMWmzuB3iKTqlUSebIUhrW0FKoLuxjc5wzgYaphqjGisGHQalBaDBJ0VENvZaEVoTWRLoeQxIYmDAYO1sX2/6s/BzKLMas9dzeLMls+az0XP21o46ktqKOpra3TqOOoXYl1kdWFwtNqnQaTBpNmnOadCpMKk3qU+q0pKBYtFg1yBOINAiMF78lG+eVJlZvx1y7W6ccDYYWUz2ZGIkoyZRvgowiPs268hbOrvFW9UbzJs9m8C7MevIWzlrxDs0Gy6YxpxOHMEcSXxFvE8dQk1UnZY9El0XPfceE9Zk6w/0Sv7G9pCt29BshN8Wnkbv9G7g9wluRdf1V2LL+lOl26eLJMtkc5lXGGeZ7xjzmScYF5mXGIuZCxhXmf7UzJTlTGHmEojEsw/WBZDHTBOGh36/4SeWV1cMrZnhX+EwxOcbUSGqY9GzKnwrPgn2m/7HYJhaJa5r0rilc50+2LujA1iUO2Q/9V+DHTkpnkFg9Ll1S+yYf07WwfFfox+6SmJ3pRrDdD9D5kITVrGna0AJF6bJAYqXw0VqaWfnFPh2RlXXb2g2yJcsHVWmZasn+j3VEQ+Omc4HOQBKrMrNDvJk0pDliWmQkhcq9W2RkeUZDQ8i5YjJzEkpksllZpCRicjLz1h9FoC+u9SQUrkkDBjbnC2mklGkSrOmmo9gXe3VkvisEaZb5i80jvEP9zqEzowo5KsV87QFGpKRFscQwgwI0yL7+gGRnXbJTxd0hJjMCaB2qQ9m9Ybo2NRObcr4r5r8zYzhWy0mpBm1ndG84e4PErcoKIKvIiOlwmKOgEPxJZvEJ/cpSQ6IJp8AyzuHiyPNJRXHX15lSLom10vvejnQ0XaqD43EuCPSyW1G/Zl+TmAdTZl+mHwxjdgKaneeeAJqqTo4q1fCF1waAvYlugzBELx70mXlLm/PCxijsFvHkKXEdnQrzchwpJd3/8pbOzBg6Cng8PnqQuPVCO/Obn4JCeaSSImV8i/SK7OYFwzQFH45lmLCcVAqMKvzSQFqchRIzD9RUjs8LMrsSs29f9rGRG64K8QpSGL2+0x0kGyaFle2uIl1lPqnfw8uh2I3CKqAeoqDJ4Xs3USUVMwzZauF9EXwCuXmFFeBhFNIj2j1ItH3eG9Yl25btwO9QL6B1PtG+fPRHDsn7xbBsOO1a56wL1NnPhCh4x9OHmcwESZyJKA35E+QSwnN/rFyqZ1RTTLiO4Xw2t2Vw1N5Inz+NZ9IWEv+5hMDfKkaicKT2zWQYyZgxUJ/aKKEZdlGhJP8HiIx6efYdKZCJj9RXpGZTbiOtqvCslvcCzewbFZeTLbyZXVzg75MvqRwKWXuWwidrmWzvkB2SLHxmBSv9YLUqrphqpoJTXBLaP75NEERfnAgT5Ko/W8YosGfIZDq8DxGDbVqcOCyfkS2vUCLDqCSXxkAV+3svgTJ38iF9f/ie480MMXPtgh6qD8q17lGQJ6g9QOoCypIhi6OizYIldeerE8Dlo7TCl7mTfANOAJ4WqyAcK1RuLWTbISpZ0gd4oA6BVHdg6twGpwjAzVdIryi0oflUKru+WczqQCNYGyVoSykhOOROKtGVNyxO2myC0swI7M5Z12V5+LwE3DvrI16ljYBTIj5ODQ5LtcPqptxEP122HZ5oS0U6TFk1TDUyBs8czoVPydk3YQuXGP8dXMH1tEgwS+fqbBo86e2lJVEPocb/FS32CdCzqsE2Gg3NpADOZwZV1MacaqcGyMT4nw+7YzsybQ9j6q0O2m4tjkFcVsWLr2nuI5uGP+S/mippDN/lVD1r/P9Es6VJj7kzAImixpsVrb1Cv10NxFomxUhu9yaVlrDNPuiJW3SSX25KnS0pleFuyOgs4ezA005UM8aNR+ZZVZkjjV6Y7m4lN1iRpMknHOnVCD6TDVWQo2HTrZjkz8XSs8Mwt9x702Vg31skY5jcbvOgsqZRP8XlY5ocffBdvcVoLvP0FNW118gHNqh7gR0PG5CrDI1kTfxUlOaQ1ILlif6L21yYdUrYMid1imUjhSoWjy3IHB+DJXsbnQvNIr47BrHJke8cFXcIsWejOyLH5DHtdpMOiS2YoMZpwUuYiOyF5dDi7fnJ+gA7jpuJ5mVCAY1MiO4neS7IjVgzFrTVzl7Gf8H3v3qtBZNaXEq00aRrQ5dQcmd/Z0zm5/P7wPAFIE1lR1fFVlKaEueIQvEmZpatIdBRrU5D3wywZn4tMpcqodeG7w8sngX93XeR9TVJC6BeJ+mxC9oQzRauvEh2tGgY8SYa2EOVoGWiYaKBIiMkQiSS4DDgcOBAzIkfPfWkwTbkF+Hyn/3INa869SvBW+erxY/gM8xeEWl9316s1UL0GNgtf6WD/kqBNMzxv+VX+LoEEfqNCLypAd7SR6ATrq3y6hoS0xTMXnho+Zl3h0eviGmdznSOdPvQT5Stvhqpm3pMeCXuhu0HWwczfN6SbUMuUepdpGcA6QAHTfpXWkpxeAwLNs903/lh9spqtnNHXS9pFcMBsWKlmUNpUlUC90sKfZFtYVIFGooffLZdM9vsq70K1wMf8QCUAySC1+W5WW/LIJH7Yxq8lbRi4aEyfeF0Lxswu5M0an9s25qYN3RHRUg=
*/