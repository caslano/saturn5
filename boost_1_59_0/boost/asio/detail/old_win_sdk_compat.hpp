//
// detail/old_win_sdk_compat.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_OLD_WIN_SDK_COMPAT_HPP
#define BOOST_ASIO_DETAIL_OLD_WIN_SDK_COMPAT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

// Guess whether we are building against on old Platform SDK.
#if !defined(IN6ADDR_ANY_INIT)
#define BOOST_ASIO_HAS_OLD_WIN_SDK 1
#endif // !defined(IN6ADDR_ANY_INIT)

#if defined(BOOST_ASIO_HAS_OLD_WIN_SDK)

// Emulation of types that are missing from old Platform SDKs.
//
// N.B. this emulation is also used if building for a Windows 2000 target with
// a recent (i.e. Vista or later) SDK, as the SDK does not provide IPv6 support
// in that case.

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

enum
{
  sockaddr_storage_maxsize = 128, // Maximum size.
  sockaddr_storage_alignsize = (sizeof(__int64)), // Desired alignment.
  sockaddr_storage_pad1size = (sockaddr_storage_alignsize - sizeof(short)),
  sockaddr_storage_pad2size = (sockaddr_storage_maxsize -
      (sizeof(short) + sockaddr_storage_pad1size + sockaddr_storage_alignsize))
};

struct sockaddr_storage_emulation
{
  short ss_family;
  char __ss_pad1[sockaddr_storage_pad1size];
  __int64 __ss_align;
  char __ss_pad2[sockaddr_storage_pad2size];
};

struct in6_addr_emulation
{
  union
  {
    u_char Byte[16];
    u_short Word[8];
  } u;
};

#if !defined(s6_addr)
# define _S6_un u
# define _S6_u8 Byte
# define s6_addr _S6_un._S6_u8
#endif // !defined(s6_addr)

struct sockaddr_in6_emulation
{
  short sin6_family;
  u_short sin6_port;
  u_long sin6_flowinfo;
  in6_addr_emulation sin6_addr;
  u_long sin6_scope_id;
};

struct ipv6_mreq_emulation
{
  in6_addr_emulation ipv6mr_multiaddr;
  unsigned int ipv6mr_interface;
};

struct addrinfo_emulation
{
  int ai_flags;
  int ai_family;
  int ai_socktype;
  int ai_protocol;
  size_t ai_addrlen;
  char* ai_canonname;
  sockaddr* ai_addr;
  addrinfo_emulation* ai_next;
};

#if !defined(AI_PASSIVE)
# define AI_PASSIVE 0x1
#endif

#if !defined(AI_CANONNAME)
# define AI_CANONNAME 0x2
#endif

#if !defined(AI_NUMERICHOST)
# define AI_NUMERICHOST 0x4
#endif

#if !defined(EAI_AGAIN)
# define EAI_AGAIN WSATRY_AGAIN
#endif

#if !defined(EAI_BADFLAGS)
# define EAI_BADFLAGS WSAEINVAL
#endif

#if !defined(EAI_FAIL)
# define EAI_FAIL WSANO_RECOVERY
#endif

#if !defined(EAI_FAMILY)
# define EAI_FAMILY WSAEAFNOSUPPORT
#endif

#if !defined(EAI_MEMORY)
# define EAI_MEMORY WSA_NOT_ENOUGH_MEMORY
#endif

#if !defined(EAI_NODATA)
# define EAI_NODATA WSANO_DATA
#endif

#if !defined(EAI_NONAME)
# define EAI_NONAME WSAHOST_NOT_FOUND
#endif

#if !defined(EAI_SERVICE)
# define EAI_SERVICE WSATYPE_NOT_FOUND
#endif

#if !defined(EAI_SOCKTYPE)
# define EAI_SOCKTYPE WSAESOCKTNOSUPPORT
#endif

#if !defined(NI_NOFQDN)
# define NI_NOFQDN 0x01
#endif

#if !defined(NI_NUMERICHOST)
# define NI_NUMERICHOST 0x02
#endif

#if !defined(NI_NAMEREQD)
# define NI_NAMEREQD 0x04
#endif

#if !defined(NI_NUMERICSERV)
# define NI_NUMERICSERV 0x08
#endif

#if !defined(NI_DGRAM)
# define NI_DGRAM 0x10
#endif

#if !defined(IPPROTO_IPV6)
# define IPPROTO_IPV6 41
#endif

#if !defined(IPV6_UNICAST_HOPS)
# define IPV6_UNICAST_HOPS 4
#endif

#if !defined(IPV6_MULTICAST_IF)
# define IPV6_MULTICAST_IF 9
#endif

#if !defined(IPV6_MULTICAST_HOPS)
# define IPV6_MULTICAST_HOPS 10
#endif

#if !defined(IPV6_MULTICAST_LOOP)
# define IPV6_MULTICAST_LOOP 11
#endif

#if !defined(IPV6_JOIN_GROUP)
# define IPV6_JOIN_GROUP 12
#endif

#if !defined(IPV6_LEAVE_GROUP)
# define IPV6_LEAVE_GROUP 13
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_OLD_WIN_SDK)

// Even newer Platform SDKs that support IPv6 may not define IPV6_V6ONLY.
#if !defined(IPV6_V6ONLY)
# define IPV6_V6ONLY 27
#endif

// Some SDKs (e.g. Windows CE) don't define IPPROTO_ICMPV6.
#if !defined(IPPROTO_ICMPV6)
# define IPPROTO_ICMPV6 58
#endif

#endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

#endif // BOOST_ASIO_DETAIL_OLD_WIN_SDK_COMPAT_HPP

/* old_win_sdk_compat.hpp
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
*/