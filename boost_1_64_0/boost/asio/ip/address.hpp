//
// ip/address.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_ADDRESS_HPP
#define BOOST_ASIO_IP_ADDRESS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/asio/detail/throw_exception.hpp>
#include <boost/asio/detail/string_view.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/address_v6.hpp>
#include <boost/asio/ip/bad_address_cast.hpp>

#if !defined(BOOST_ASIO_NO_IOSTREAM)
# include <iosfwd>
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Implements version-independent IP addresses.
/**
 * The boost::asio::ip::address class provides the ability to use either IP
 * version 4 or version 6 addresses.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
class address
{
public:
  /// Default constructor.
  BOOST_ASIO_DECL address() BOOST_ASIO_NOEXCEPT;

  /// Construct an address from an IPv4 address.
  BOOST_ASIO_DECL address(
      const boost::asio::ip::address_v4& ipv4_address) BOOST_ASIO_NOEXCEPT;

  /// Construct an address from an IPv6 address.
  BOOST_ASIO_DECL address(
      const boost::asio::ip::address_v6& ipv6_address) BOOST_ASIO_NOEXCEPT;

  /// Copy constructor.
  BOOST_ASIO_DECL address(const address& other) BOOST_ASIO_NOEXCEPT;

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move constructor.
  BOOST_ASIO_DECL address(address&& other) BOOST_ASIO_NOEXCEPT;
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Assign from another address.
  BOOST_ASIO_DECL address& operator=(const address& other) BOOST_ASIO_NOEXCEPT;

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move-assign from another address.
  BOOST_ASIO_DECL address& operator=(address&& other) BOOST_ASIO_NOEXCEPT;
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Assign from an IPv4 address.
  BOOST_ASIO_DECL address& operator=(
      const boost::asio::ip::address_v4& ipv4_address) BOOST_ASIO_NOEXCEPT;

  /// Assign from an IPv6 address.
  BOOST_ASIO_DECL address& operator=(
      const boost::asio::ip::address_v6& ipv6_address) BOOST_ASIO_NOEXCEPT;

  /// Get whether the address is an IP version 4 address.
  bool is_v4() const BOOST_ASIO_NOEXCEPT
  {
    return type_ == ipv4;
  }

  /// Get whether the address is an IP version 6 address.
  bool is_v6() const BOOST_ASIO_NOEXCEPT
  {
    return type_ == ipv6;
  }

  /// Get the address as an IP version 4 address.
  BOOST_ASIO_DECL boost::asio::ip::address_v4 to_v4() const;

  /// Get the address as an IP version 6 address.
  BOOST_ASIO_DECL boost::asio::ip::address_v6 to_v6() const;

  /// Get the address as a string.
  BOOST_ASIO_DECL std::string to_string() const;

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use other overload.) Get the address as a string.
  BOOST_ASIO_DECL std::string to_string(boost::system::error_code& ec) const;

  /// (Deprecated: Use make_address().) Create an address from an IPv4 address
  /// string in dotted decimal form, or from an IPv6 address in hexadecimal
  /// notation.
  static address from_string(const char* str);

  /// (Deprecated: Use make_address().) Create an address from an IPv4 address
  /// string in dotted decimal form, or from an IPv6 address in hexadecimal
  /// notation.
  static address from_string(const char* str, boost::system::error_code& ec);

  /// (Deprecated: Use make_address().) Create an address from an IPv4 address
  /// string in dotted decimal form, or from an IPv6 address in hexadecimal
  /// notation.
  static address from_string(const std::string& str);

  /// (Deprecated: Use make_address().) Create an address from an IPv4 address
  /// string in dotted decimal form, or from an IPv6 address in hexadecimal
  /// notation.
  static address from_string(
      const std::string& str, boost::system::error_code& ec);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Determine whether the address is a loopback address.
  BOOST_ASIO_DECL bool is_loopback() const BOOST_ASIO_NOEXCEPT;

  /// Determine whether the address is unspecified.
  BOOST_ASIO_DECL bool is_unspecified() const BOOST_ASIO_NOEXCEPT;

  /// Determine whether the address is a multicast address.
  BOOST_ASIO_DECL bool is_multicast() const BOOST_ASIO_NOEXCEPT;

  /// Compare two addresses for equality.
  BOOST_ASIO_DECL friend bool operator==(const address& a1,
      const address& a2) BOOST_ASIO_NOEXCEPT;

  /// Compare two addresses for inequality.
  friend bool operator!=(const address& a1,
      const address& a2) BOOST_ASIO_NOEXCEPT
  {
    return !(a1 == a2);
  }

  /// Compare addresses for ordering.
  BOOST_ASIO_DECL friend bool operator<(const address& a1,
      const address& a2) BOOST_ASIO_NOEXCEPT;

  /// Compare addresses for ordering.
  friend bool operator>(const address& a1,
      const address& a2) BOOST_ASIO_NOEXCEPT
  {
    return a2 < a1;
  }

  /// Compare addresses for ordering.
  friend bool operator<=(const address& a1,
      const address& a2) BOOST_ASIO_NOEXCEPT
  {
    return !(a2 < a1);
  }

  /// Compare addresses for ordering.
  friend bool operator>=(const address& a1,
      const address& a2) BOOST_ASIO_NOEXCEPT
  {
    return !(a1 < a2);
  }

private:
  // The type of the address.
  enum { ipv4, ipv6 } type_;

  // The underlying IPv4 address.
  boost::asio::ip::address_v4 ipv4_address_;

  // The underlying IPv6 address.
  boost::asio::ip::address_v6 ipv6_address_;
};

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
BOOST_ASIO_DECL address make_address(const char* str);

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
BOOST_ASIO_DECL address make_address(const char* str,
    boost::system::error_code& ec) BOOST_ASIO_NOEXCEPT;

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
BOOST_ASIO_DECL address make_address(const std::string& str);

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
BOOST_ASIO_DECL address make_address(const std::string& str,
    boost::system::error_code& ec) BOOST_ASIO_NOEXCEPT;

#if defined(BOOST_ASIO_HAS_STRING_VIEW) \
  || defined(GENERATING_DOCUMENTATION)

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
BOOST_ASIO_DECL address make_address(string_view str);

/// Create an address from an IPv4 address string in dotted decimal form,
/// or from an IPv6 address in hexadecimal notation.
/**
 * @relates address
 */
BOOST_ASIO_DECL address make_address(string_view str,
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
 * @relates boost::asio::ip::address
 */
template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const address& addr);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/ip/impl/address.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ip/impl/address.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_IP_ADDRESS_HPP

/* address.hpp
vv9oLynPGEk3Vsqzj6TbG7YTvaPo9nRLa0jX+h5G0r1c0r1Cp+v6PUxH0a3vbCRd7oPd9lXuJOl2kXT/xd65wFdV1wH83N1tDHaBbWxjjNeA8R4wBXmJMF463gOHIGJswGCTMeY2dBraUFQyKjI0TKtZKKhYU7GoLJdhUlKhmalhLTOjwlpJhoXW9/+/v3vuOfecc3cZ9N4+/Pje/+P3P7//8/zPOf/zP0Ml3TxJd5ikOxwOFP8hcAQcCUfCfPGXfDAn9M6H+bxZjjdRjjdZjjcJ9hX3AHHLd0tlHqb7uOO7pT2kv6WLfob0gxw4AmbC0bAnHA97wQIJnwd7w8WwD/wA7A/XSPhGcYfa01GxY4ZLeyqR/IW+z7tWjlsBQ9/nvUjcsj5G5iiqDeIZsT7mInnOPk3KpwD2g9PhcDhD0p8p+ZoFJ8FL4FRYCA/7Y/tu6MQHou+rbH8OfW73V97ywP/GHsvyzNdtr2We8ca233L83uh7Lufv/efuu1yyN7a9l2N5LvtijHswN+5tex/mA3v/M/Ziluenlmen0fdkTv8Dz0GRlUgDsgc5hBxHUlr9Rj5SjNQj9yLNyBtI/B/5/iUyH6lEtv+x45lox1/HX8ffP//vX/b8v6bs6nPx/F/t8fftCVxb6z3+eKi/infuV1VW1NbpPf70/jO7rWG1wT3+Gi1rBp702Z9D9keeIc38jeH7a0tmL1Y7/J23qrSurkbuU23KMAgnI+H7VKKTosMLgu/7oSD3pczwDPN+W2FW2/fbQveYOB73kzie5R4Tx8BPH0PfY5oheSqQU8YoydMw5Fn1PMwrT2r/qoVzZhneeRPdDMv7UZRn+H6phPezhOvntfK+lD08PkW/73hdXVmt7D/opl9ZVgXD+w1KHNlDkCZjluNIuW85sY17dQUu5Vho3rvU+YnYC0DnQfstx43d+Gm7I/bFUrba6+BQvLMOvksdNEarA97Qj1YHjZY66JVKuGUPinkSHq0OGtuog8YY6qDRow7mZUkdxLAXg1sdkB/8yM85rIOiRGcdPKeebUarA75NGq0OWqQO0sx9NJWi/flISxv10NJGPbTEUA8tHvWwoJ31kCn1QJ7wC+Xp7Osi9HxqmDyj7yN10QP5PnWRU+WoC8vyLK96ED3ZJ+hYlgpHq1bqIBxulssDZ/D+qttYyzHwU8ewt7FTstfd3fLMbRvyQ/JVFDVf6mTkmTfRHaXdC3HfoN2lzrzK84vrdfgqyXtIf4TrWN0T1ujwq6U9SnyeuqdJfEOlr6swvH/NHRInkdyrdHMSJZ5Od4ZuD9fqODV6f5s86ruasvk85R7InhvwDwnEd7aN2bLnizxH20u8j1jeGc8/w/Yr44i1nqTtOsf35RD7g/Eixow6eQ7eimQhv0Kepz5TNtnqU/Ygq66puKa0rmwVj6F13qQ+w8/fRG+E+Z78DO1OJG7oGfkGqbdQ3L7mc65R2v0Cbh2Xv/rgvgSyr9k4Hf4U9gfMuqZUVBzzveV1Ok5c0M2vN7U7XdfRaeonnfw+SNn7++rtZwPxljqaLnWUjTsB94cH8u5gmha9v90DaW3XVTdbXdVrd6H5/H6DbT1FoTy7z5YxQnn+SD3zrbaX/VqmlxS6GqS8+pDopFrH0E1rrM93q+3PPhed5VxMxj2OYR/3xslz+VC6Q2Uf0RJ7nsJjQ3BokL4o+RI/2b9LdId57jVVocLJTZZ+w/1SPQ/eO5WARHMebLa59Tpu5zbXX6nzQ5KZT9MmW/296LIG4cR45gz2vOo1lbKQxKv+0LHvP9CjneO3tS5e7Opc7/k29h11s89ceBgcp98c77ARPcfaTrSkbCPCB/TS4aWVEl6kw2Nb+5k=
*/