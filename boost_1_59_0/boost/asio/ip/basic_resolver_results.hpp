//
// ip/basic_resolver_results.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_BASIC_RESOLVER_RESULTS_HPP
#define BOOST_ASIO_IP_BASIC_RESOLVER_RESULTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <cstring>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
# include <boost/asio/detail/winrt_utils.hpp>
#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// A range of entries produced by a resolver.
/**
 * The boost::asio::ip::basic_resolver_results class template is used to define
 * a range over the results returned by a resolver.
 *
 * The iterator's value_type, obtained when a results iterator is dereferenced,
 * is: @code const basic_resolver_entry<InternetProtocol> @endcode
 *
 * @note For backward compatibility, basic_resolver_results is derived from
 * basic_resolver_iterator. This derivation is deprecated.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename InternetProtocol>
class basic_resolver_results
#if !defined(BOOST_ASIO_NO_DEPRECATED)
  : public basic_resolver_iterator<InternetProtocol>
#else // !defined(BOOST_ASIO_NO_DEPRECATED)
  : private basic_resolver_iterator<InternetProtocol>
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)
{
public:
  /// The protocol type associated with the results.
  typedef InternetProtocol protocol_type;

  /// The endpoint type associated with the results.
  typedef typename protocol_type::endpoint endpoint_type;

  /// The type of a value in the results range.
  typedef basic_resolver_entry<protocol_type> value_type;

  /// The type of a const reference to a value in the range.
  typedef const value_type& const_reference;

  /// The type of a non-const reference to a value in the range.
  typedef value_type& reference;

  /// The type of an iterator into the range.
  typedef basic_resolver_iterator<protocol_type> const_iterator;

  /// The type of an iterator into the range.
  typedef const_iterator iterator;

  /// Type used to represent the distance between two iterators in the range.
  typedef std::ptrdiff_t difference_type;

  /// Type used to represent a count of the elements in the range.
  typedef std::size_t size_type;

  /// Default constructor creates an empty range.
  basic_resolver_results()
  {
  }

  /// Copy constructor.
  basic_resolver_results(const basic_resolver_results& other)
    : basic_resolver_iterator<InternetProtocol>(other)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move constructor.
  basic_resolver_results(basic_resolver_results&& other)
    : basic_resolver_iterator<InternetProtocol>(
        BOOST_ASIO_MOVE_CAST(basic_resolver_results)(other))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Assignment operator.
  basic_resolver_results& operator=(const basic_resolver_results& other)
  {
    basic_resolver_iterator<InternetProtocol>::operator=(other);
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-assignment operator.
  basic_resolver_results& operator=(basic_resolver_results&& other)
  {
    basic_resolver_iterator<InternetProtocol>::operator=(
        BOOST_ASIO_MOVE_CAST(basic_resolver_results)(other));
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

#if !defined(GENERATING_DOCUMENTATION)
  // Create results from an addrinfo list returned by getaddrinfo.
  static basic_resolver_results create(
      boost::asio::detail::addrinfo_type* address_info,
      const std::string& host_name, const std::string& service_name)
  {
    basic_resolver_results results;
    if (!address_info)
      return results;

    std::string actual_host_name = host_name;
    if (address_info->ai_canonname)
      actual_host_name = address_info->ai_canonname;

    results.values_.reset(new values_type);

    while (address_info)
    {
      if (address_info->ai_family == BOOST_ASIO_OS_DEF(AF_INET)
          || address_info->ai_family == BOOST_ASIO_OS_DEF(AF_INET6))
      {
        using namespace std; // For memcpy.
        typename InternetProtocol::endpoint endpoint;
        endpoint.resize(static_cast<std::size_t>(address_info->ai_addrlen));
        memcpy(endpoint.data(), address_info->ai_addr,
            address_info->ai_addrlen);
        results.values_->push_back(
            basic_resolver_entry<InternetProtocol>(endpoint,
              actual_host_name, service_name));
      }
      address_info = address_info->ai_next;
    }

    return results;
  }

  // Create results from an endpoint, host name and service name.
  static basic_resolver_results create(const endpoint_type& endpoint,
      const std::string& host_name, const std::string& service_name)
  {
    basic_resolver_results results;
    results.values_.reset(new values_type);
    results.values_->push_back(
        basic_resolver_entry<InternetProtocol>(
          endpoint, host_name, service_name));
    return results;
  }

  // Create results from a sequence of endpoints, host and service name.
  template <typename EndpointIterator>
  static basic_resolver_results create(
      EndpointIterator begin, EndpointIterator end,
      const std::string& host_name, const std::string& service_name)
  {
    basic_resolver_results results;
    if (begin != end)
    {
      results.values_.reset(new values_type);
      for (EndpointIterator ep_iter = begin; ep_iter != end; ++ep_iter)
      {
        results.values_->push_back(
            basic_resolver_entry<InternetProtocol>(
              *ep_iter, host_name, service_name));
      }
    }
    return results;
  }

# if defined(BOOST_ASIO_WINDOWS_RUNTIME)
  // Create results from a Windows Runtime list of EndpointPair objects.
  static basic_resolver_results create(
      Windows::Foundation::Collections::IVectorView<
        Windows::Networking::EndpointPair^>^ endpoints,
      const boost::asio::detail::addrinfo_type& hints,
      const std::string& host_name, const std::string& service_name)
  {
    basic_resolver_results results;
    if (endpoints->Size)
    {
      results.values_.reset(new values_type);
      for (unsigned int i = 0; i < endpoints->Size; ++i)
      {
        auto pair = endpoints->GetAt(i);

        if (hints.ai_family == BOOST_ASIO_OS_DEF(AF_INET)
            && pair->RemoteHostName->Type
              != Windows::Networking::HostNameType::Ipv4)
          continue;

        if (hints.ai_family == BOOST_ASIO_OS_DEF(AF_INET6)
            && pair->RemoteHostName->Type
              != Windows::Networking::HostNameType::Ipv6)
          continue;

        results.values_->push_back(
            basic_resolver_entry<InternetProtocol>(
              typename InternetProtocol::endpoint(
                ip::make_address(
                  boost::asio::detail::winrt_utils::string(
                    pair->RemoteHostName->CanonicalName)),
                boost::asio::detail::winrt_utils::integer(
                  pair->RemoteServiceName)),
              host_name, service_name));
      }
    }
    return results;
  }
# endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)
#endif // !defined(GENERATING_DOCUMENTATION)

  /// Get the number of entries in the results range.
  size_type size() const BOOST_ASIO_NOEXCEPT
  {
    return this->values_ ? this->values_->size() : 0;
  }

  /// Get the maximum number of entries permitted in a results range.
  size_type max_size() const BOOST_ASIO_NOEXCEPT
  {
    return this->values_ ? this->values_->max_size() : values_type().max_size();
  }

  /// Determine whether the results range is empty.
  bool empty() const BOOST_ASIO_NOEXCEPT
  {
    return this->values_ ? this->values_->empty() : true;
  }

  /// Obtain a begin iterator for the results range.
  const_iterator begin() const
  {
    basic_resolver_results tmp(*this);
    tmp.index_ = 0;
    return BOOST_ASIO_MOVE_CAST(basic_resolver_results)(tmp);
  }

  /// Obtain an end iterator for the results range.
  const_iterator end() const
  {
    return const_iterator();
  }

  /// Obtain a begin iterator for the results range.
  const_iterator cbegin() const
  {
    return begin();
  }

  /// Obtain an end iterator for the results range.
  const_iterator cend() const
  {
    return end();
  }

  /// Swap the results range with another.
  void swap(basic_resolver_results& that) BOOST_ASIO_NOEXCEPT
  {
    if (this != &that)
    {
      this->values_.swap(that.values_);
      std::size_t index = this->index_;
      this->index_ = that.index_;
      that.index_ = index;
    }
  }

  /// Test two iterators for equality.
  friend bool operator==(const basic_resolver_results& a,
      const basic_resolver_results& b)
  {
    return a.equal(b);
  }

  /// Test two iterators for inequality.
  friend bool operator!=(const basic_resolver_results& a,
      const basic_resolver_results& b)
  {
    return !a.equal(b);
  }

private:
  typedef std::vector<basic_resolver_entry<InternetProtocol> > values_type;
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_BASIC_RESOLVER_RESULTS_HPP

/* basic_resolver_results.hpp
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
*/