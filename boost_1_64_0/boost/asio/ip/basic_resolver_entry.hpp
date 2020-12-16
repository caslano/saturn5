//
// ip/basic_resolver_entry.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_BASIC_RESOLVER_ENTRY_HPP
#define BOOST_ASIO_IP_BASIC_RESOLVER_ENTRY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/asio/detail/string_view.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// An entry produced by a resolver.
/**
 * The boost::asio::ip::basic_resolver_entry class template describes an entry
 * as returned by a resolver.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename InternetProtocol>
class basic_resolver_entry
{
public:
  /// The protocol type associated with the endpoint entry.
  typedef InternetProtocol protocol_type;

  /// The endpoint type associated with the endpoint entry.
  typedef typename InternetProtocol::endpoint endpoint_type;

  /// Default constructor.
  basic_resolver_entry()
  {
  }

  /// Construct with specified endpoint, host name and service name.
  basic_resolver_entry(const endpoint_type& ep,
      BOOST_ASIO_STRING_VIEW_PARAM host, BOOST_ASIO_STRING_VIEW_PARAM service)
    : endpoint_(ep),
      host_name_(static_cast<std::string>(host)),
      service_name_(static_cast<std::string>(service))
  {
  }

  /// Get the endpoint associated with the entry.
  endpoint_type endpoint() const
  {
    return endpoint_;
  }

  /// Convert to the endpoint associated with the entry.
  operator endpoint_type() const
  {
    return endpoint_;
  }

  /// Get the host name associated with the entry.
  std::string host_name() const
  {
    return host_name_;
  }

  /// Get the host name associated with the entry.
  template <class Allocator>
  std::basic_string<char, std::char_traits<char>, Allocator> host_name(
      const Allocator& alloc = Allocator()) const
  {
    return std::basic_string<char, std::char_traits<char>, Allocator>(
        host_name_.c_str(), alloc);
  }

  /// Get the service name associated with the entry.
  std::string service_name() const
  {
    return service_name_;
  }

  /// Get the service name associated with the entry.
  template <class Allocator>
  std::basic_string<char, std::char_traits<char>, Allocator> service_name(
      const Allocator& alloc = Allocator()) const
  {
    return std::basic_string<char, std::char_traits<char>, Allocator>(
        service_name_.c_str(), alloc);
  }

private:
  endpoint_type endpoint_;
  std::string host_name_;
  std::string service_name_;
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_BASIC_RESOLVER_ENTRY_HPP

/* basic_resolver_entry.hpp
K5FGdJ5EivGrxP2yKnu4C/cO4jche3C/CJth1gx+wwJ4nLhHr4FI/F7KXIVfS54I24bcS7nl497D78NIuooDTxMvn9/lhB0iTuA84vM7MBMd2II9w/Br5ncxXItsQXYg+5HjSg/mEf9FWEhab8AC3GuRk/yOP5/jIVtw58K8evKHnCbtbXAKfrsI24fsx70c9xuwhLTq+H0Y/z63+o1T+J3g97DraGO4U2ZhK+Hj4HKkDjlNHkoIu1e50X8SNhJnB7+b4CHkGH4nkZTZ6F2H3fgN43cRYoyl7uAuZBvpHIDp+G0hXi6cgjTuRQf/E0iJCkN2IPuRw8RrhukXkwd+HyBu1vXoIXn4FcNCeJQ4LchJJGkcx7/Qb9QTVknYDqQJyX2KvgyzCD8Bp8D5SCViXIIdxN/J72bYB/dxOBEGPoguUsLvBqSQ342wEj5J/JeR48gB/JrwO8Xvw/AY7hMwZQt+/M6HB1Q5X8C4geQjhVuIi18BvyeqcQ4bq/E7ST7TCyk3fpcQVo00bqM97aNP4jeFsGNwJaxDGggP3EB85SaNJrgb7sR/Fv7FpygPZA9yFDmFZL3rNyYiy5F65F7kSaQFSfqr38hDliP1yD7kReQ0kvs3vzEfqUMakSPIaSTntN+YhZQj25Em5EXkNJL7Ht8WQ7Yg+5EXkdNI7vukhdQje5DDSCuS8nf6F1KMbEH2IEeR00ges95ipB5pRA4hJ5B0X7xRgFQiu5CDyDEkni+J5SKzkLXIdmQ/cgRpRbL88cYUpATZhuxDjiCtSHo8YUgJsg3ZgxxCWhAjId7o+PsHe+cCH8VRx/G9vAjkgFxIQhIIBAhvQhIKFGhLD0ogvAOlLUUsCSSQSJqEPFpaq6YWam3VorbYlzVV+kZNtVarWGMfWrVq1FpbrYqValVsUanSWqvfnfvf3O7t7uUIUF+3fP78Mjvz3/nPf/4z+5+5mdnElbgSV+JKXIkrcSWuxJW4Etd/y5UCNRm+0J65eRubW+qa2po7WrfUhf5sayzZ3NHQWFtSPr18etnWkkvaZpSVn67jds6eWdJWz67s2pLWOs4rbKsLp9jSellLe/NGc+OQ+o9j+9qnswMsNH97ZsBcjN5rDGMd01dqDI0rG7a0Nrc1b20vmrR2ctHqlvaGixsub2jaVnQOm78bGjmmLM1YEZg81YicLSd7pvKhwVAmNN88i2eR2uenDxDhKzjlyMBuvxm1JHF8+2iZL8yTadmr29RQG9mrK/H5lnMDZe+v7O2TeAv/ltaG9hB/QyTecR5fllERWE38JJ2HT+2vQ0V6v1tvcWh/5BxHDdrPBgqC8r0g/X0yRCBMWSLfp5PzB5X86t56nU7JrO5VO8/00+c5T0qWb0uK3ougoLkA36l3U+2u+iatPnfrPBVXt9OI7IclPnrvNKcpSXx9JF7r6IfFfZ9DJHtILTqS7+CoMPlH9riJPsw87WePHU02HGePLaTs3VFlr6VJtNep4ruVX9IHXMs3DCTeds7S0ydQPktZbPV4IMVZlkWUpTeqLJwUqOuxK6ocvbHLQby9HM8eRzm6vMthP4s91VmOxZTjiGs51JdOVy1dZLiVR3gCnv3AESlPVqS8NW3tHFJnsc0jUWX+6QmXOSRDrt02JV+7Lp5Oc+qiEl1kVnjqgrMM3HUBj9ZFfoA4y3fMl6v4vnVBGpsunj8BXSADYWTw1IX9nMdDA9ztosxbF2YH2LClptFNH8IXcOnj5du3ceijLEofvzgBfUT67PhsozPdqY+l6KPKQx9bmjuaeJ6bLoQnoMtxsB/lsParDw50yrYc2Vo8ZKud0eAmF+ljtl+JLwjFp9nrsMrniLed2bFG4q3190w=
*/