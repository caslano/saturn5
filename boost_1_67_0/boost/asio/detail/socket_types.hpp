//
// detail/socket_types.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SOCKET_TYPES_HPP
#define BOOST_ASIO_DETAIL_SOCKET_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
// Empty.
#elif defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
# if defined(_WINSOCKAPI_) && !defined(_WINSOCK2API_)
#  error WinSock.h has already been included
# endif // defined(_WINSOCKAPI_) && !defined(_WINSOCK2API_)
# if defined(__BORLANDC__)
#  include <stdlib.h> // Needed for __errno
#  if !defined(_WSPIAPI_H_)
#   define _WSPIAPI_H_
#   define BOOST_ASIO_WSPIAPI_H_DEFINED
#  endif // !defined(_WSPIAPI_H_)
# endif // defined(__BORLANDC__)
# include <winsock2.h>
# include <ws2tcpip.h>
# if defined(WINAPI_FAMILY)
#  if ((WINAPI_FAMILY & WINAPI_PARTITION_DESKTOP) != 0)
#   include <windows.h>
#  endif // ((WINAPI_FAMILY & WINAPI_PARTITION_DESKTOP) != 0)
# endif // defined(WINAPI_FAMILY)
# if !defined(BOOST_ASIO_WINDOWS_APP)
#  include <mswsock.h>
# endif // !defined(BOOST_ASIO_WINDOWS_APP)
# if defined(BOOST_ASIO_WSPIAPI_H_DEFINED)
#  undef _WSPIAPI_H_
#  undef BOOST_ASIO_WSPIAPI_H_DEFINED
# endif // defined(BOOST_ASIO_WSPIAPI_H_DEFINED)
# if !defined(BOOST_ASIO_NO_DEFAULT_LINKED_LIBS)
#  if defined(UNDER_CE)
#   pragma comment(lib, "ws2.lib")
#  elif defined(_MSC_VER) || defined(__BORLANDC__)
#   pragma comment(lib, "ws2_32.lib")
#   if !defined(BOOST_ASIO_WINDOWS_APP)
#    pragma comment(lib, "mswsock.lib")
#   endif // !defined(BOOST_ASIO_WINDOWS_APP)
#  endif // defined(_MSC_VER) || defined(__BORLANDC__)
# endif // !defined(BOOST_ASIO_NO_DEFAULT_LINKED_LIBS)
# include <boost/asio/detail/old_win_sdk_compat.hpp>
#else
# include <sys/ioctl.h>
# if (defined(__MACH__) && defined(__APPLE__)) \
   || defined(__FreeBSD__) || defined(__NetBSD__) \
   || defined(__OpenBSD__) || defined(__linux__) \
   || defined(__EMSCRIPTEN__)
#  include <poll.h>
# elif !defined(__SYMBIAN32__)
#  include <sys/poll.h>
# endif
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# if defined(__hpux)
#  include <sys/time.h>
# endif
# if !defined(__hpux) || defined(__SELECT)
#  include <sys/select.h>
# endif
# include <sys/socket.h>
# include <sys/uio.h>
# include <sys/un.h>
# include <netinet/in.h>
# if !defined(__SYMBIAN32__)
#  include <netinet/tcp.h>
# endif
# include <arpa/inet.h>
# include <netdb.h>
# include <net/if.h>
# include <limits.h>
# if defined(__sun)
#  include <sys/filio.h>
#  include <sys/sockio.h>
# endif
#endif

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
const int max_addr_v4_str_len = 256;
const int max_addr_v6_str_len = 256;
typedef unsigned __int32 u_long_type;
typedef unsigned __int16 u_short_type;
struct in4_addr_type { u_long_type s_addr; };
struct in4_mreq_type { in4_addr_type imr_multiaddr, imr_interface; };
struct in6_addr_type { unsigned char s6_addr[16]; };
struct in6_mreq_type { in6_addr_type ipv6mr_multiaddr;
  unsigned long ipv6mr_interface; };
struct socket_addr_type { int sa_family; };
struct sockaddr_in4_type { int sin_family;
  in4_addr_type sin_addr; u_short_type sin_port; };
struct sockaddr_in6_type { int sin6_family;
  in6_addr_type sin6_addr; u_short_type sin6_port;
  u_long_type sin6_flowinfo; u_long_type sin6_scope_id; };
struct sockaddr_storage_type { int ss_family;
  unsigned char ss_bytes[128 - sizeof(int)]; };
struct addrinfo_type { int ai_flags;
  int ai_family, ai_socktype, ai_protocol;
  int ai_addrlen; const void* ai_addr;
  const char* ai_canonname; addrinfo_type* ai_next; };
struct linger_type { u_short_type l_onoff, l_linger; };
typedef u_long_type ioctl_arg_type;
typedef int signed_size_type;
# define BOOST_ASIO_OS_DEF(c) BOOST_ASIO_OS_DEF_##c
# define BOOST_ASIO_OS_DEF_AF_UNSPEC 0
# define BOOST_ASIO_OS_DEF_AF_INET 2
# define BOOST_ASIO_OS_DEF_AF_INET6 23
# define BOOST_ASIO_OS_DEF_SOCK_STREAM 1
# define BOOST_ASIO_OS_DEF_SOCK_DGRAM 2
# define BOOST_ASIO_OS_DEF_SOCK_RAW 3
# define BOOST_ASIO_OS_DEF_SOCK_SEQPACKET 5
# define BOOST_ASIO_OS_DEF_IPPROTO_IP 0
# define BOOST_ASIO_OS_DEF_IPPROTO_IPV6 41
# define BOOST_ASIO_OS_DEF_IPPROTO_TCP 6
# define BOOST_ASIO_OS_DEF_IPPROTO_UDP 17
# define BOOST_ASIO_OS_DEF_IPPROTO_ICMP 1
# define BOOST_ASIO_OS_DEF_IPPROTO_ICMPV6 58
# define BOOST_ASIO_OS_DEF_FIONBIO 1
# define BOOST_ASIO_OS_DEF_FIONREAD 2
# define BOOST_ASIO_OS_DEF_INADDR_ANY 0
# define BOOST_ASIO_OS_DEF_MSG_OOB 0x1
# define BOOST_ASIO_OS_DEF_MSG_PEEK 0x2
# define BOOST_ASIO_OS_DEF_MSG_DONTROUTE 0x4
# define BOOST_ASIO_OS_DEF_MSG_EOR 0 // Not supported.
# define BOOST_ASIO_OS_DEF_SHUT_RD 0x0
# define BOOST_ASIO_OS_DEF_SHUT_WR 0x1
# define BOOST_ASIO_OS_DEF_SHUT_RDWR 0x2
# define BOOST_ASIO_OS_DEF_SOMAXCONN 0x7fffffff
# define BOOST_ASIO_OS_DEF_SOL_SOCKET 0xffff
# define BOOST_ASIO_OS_DEF_SO_BROADCAST 0x20
# define BOOST_ASIO_OS_DEF_SO_DEBUG 0x1
# define BOOST_ASIO_OS_DEF_SO_DONTROUTE 0x10
# define BOOST_ASIO_OS_DEF_SO_KEEPALIVE 0x8
# define BOOST_ASIO_OS_DEF_SO_LINGER 0x80
# define BOOST_ASIO_OS_DEF_SO_OOBINLINE 0x100
# define BOOST_ASIO_OS_DEF_SO_SNDBUF 0x1001
# define BOOST_ASIO_OS_DEF_SO_RCVBUF 0x1002
# define BOOST_ASIO_OS_DEF_SO_SNDLOWAT 0x1003
# define BOOST_ASIO_OS_DEF_SO_RCVLOWAT 0x1004
# define BOOST_ASIO_OS_DEF_SO_REUSEADDR 0x4
# define BOOST_ASIO_OS_DEF_TCP_NODELAY 0x1
# define BOOST_ASIO_OS_DEF_IP_MULTICAST_IF 2
# define BOOST_ASIO_OS_DEF_IP_MULTICAST_TTL 3
# define BOOST_ASIO_OS_DEF_IP_MULTICAST_LOOP 4
# define BOOST_ASIO_OS_DEF_IP_ADD_MEMBERSHIP 5
# define BOOST_ASIO_OS_DEF_IP_DROP_MEMBERSHIP 6
# define BOOST_ASIO_OS_DEF_IP_TTL 7
# define BOOST_ASIO_OS_DEF_IPV6_UNICAST_HOPS 4
# define BOOST_ASIO_OS_DEF_IPV6_MULTICAST_IF 9
# define BOOST_ASIO_OS_DEF_IPV6_MULTICAST_HOPS 10
# define BOOST_ASIO_OS_DEF_IPV6_MULTICAST_LOOP 11
# define BOOST_ASIO_OS_DEF_IPV6_JOIN_GROUP 12
# define BOOST_ASIO_OS_DEF_IPV6_LEAVE_GROUP 13
# define BOOST_ASIO_OS_DEF_AI_CANONNAME 0x2
# define BOOST_ASIO_OS_DEF_AI_PASSIVE 0x1
# define BOOST_ASIO_OS_DEF_AI_NUMERICHOST 0x4
# define BOOST_ASIO_OS_DEF_AI_NUMERICSERV 0x8
# define BOOST_ASIO_OS_DEF_AI_V4MAPPED 0x800
# define BOOST_ASIO_OS_DEF_AI_ALL 0x100
# define BOOST_ASIO_OS_DEF_AI_ADDRCONFIG 0x400
#elif defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
typedef SOCKET socket_type;
const SOCKET invalid_socket = INVALID_SOCKET;
const int socket_error_retval = SOCKET_ERROR;
const int max_addr_v4_str_len = 256;
const int max_addr_v6_str_len = 256;
typedef sockaddr socket_addr_type;
typedef in_addr in4_addr_type;
typedef ip_mreq in4_mreq_type;
typedef sockaddr_in sockaddr_in4_type;
# if defined(BOOST_ASIO_HAS_OLD_WIN_SDK)
typedef in6_addr_emulation in6_addr_type;
typedef ipv6_mreq_emulation in6_mreq_type;
typedef sockaddr_in6_emulation sockaddr_in6_type;
typedef sockaddr_storage_emulation sockaddr_storage_type;
typedef addrinfo_emulation addrinfo_type;
# else
typedef in6_addr in6_addr_type;
typedef ipv6_mreq in6_mreq_type;
typedef sockaddr_in6 sockaddr_in6_type;
typedef sockaddr_storage sockaddr_storage_type;
typedef addrinfo addrinfo_type;
# endif
typedef ::linger linger_type;
typedef unsigned long ioctl_arg_type;
typedef u_long u_long_type;
typedef u_short u_short_type;
typedef int signed_size_type;
# define BOOST_ASIO_OS_DEF(c) BOOST_ASIO_OS_DEF_##c
# define BOOST_ASIO_OS_DEF_AF_UNSPEC AF_UNSPEC
# define BOOST_ASIO_OS_DEF_AF_INET AF_INET
# define BOOST_ASIO_OS_DEF_AF_INET6 AF_INET6
# define BOOST_ASIO_OS_DEF_SOCK_STREAM SOCK_STREAM
# define BOOST_ASIO_OS_DEF_SOCK_DGRAM SOCK_DGRAM
# define BOOST_ASIO_OS_DEF_SOCK_RAW SOCK_RAW
# define BOOST_ASIO_OS_DEF_SOCK_SEQPACKET SOCK_SEQPACKET
# define BOOST_ASIO_OS_DEF_IPPROTO_IP IPPROTO_IP
# define BOOST_ASIO_OS_DEF_IPPROTO_IPV6 IPPROTO_IPV6
# define BOOST_ASIO_OS_DEF_IPPROTO_TCP IPPROTO_TCP
# define BOOST_ASIO_OS_DEF_IPPROTO_UDP IPPROTO_UDP
# define BOOST_ASIO_OS_DEF_IPPROTO_ICMP IPPROTO_ICMP
# define BOOST_ASIO_OS_DEF_IPPROTO_ICMPV6 IPPROTO_ICMPV6
# define BOOST_ASIO_OS_DEF_FIONBIO FIONBIO
# define BOOST_ASIO_OS_DEF_FIONREAD FIONREAD
# define BOOST_ASIO_OS_DEF_INADDR_ANY INADDR_ANY
# define BOOST_ASIO_OS_DEF_MSG_OOB MSG_OOB
# define BOOST_ASIO_OS_DEF_MSG_PEEK MSG_PEEK
# define BOOST_ASIO_OS_DEF_MSG_DONTROUTE MSG_DONTROUTE
# define BOOST_ASIO_OS_DEF_MSG_EOR 0 // Not supported on Windows.
# define BOOST_ASIO_OS_DEF_SHUT_RD SD_RECEIVE
# define BOOST_ASIO_OS_DEF_SHUT_WR SD_SEND
# define BOOST_ASIO_OS_DEF_SHUT_RDWR SD_BOTH
# define BOOST_ASIO_OS_DEF_SOMAXCONN SOMAXCONN
# define BOOST_ASIO_OS_DEF_SOL_SOCKET SOL_SOCKET
# define BOOST_ASIO_OS_DEF_SO_BROADCAST SO_BROADCAST
# define BOOST_ASIO_OS_DEF_SO_DEBUG SO_DEBUG
# define BOOST_ASIO_OS_DEF_SO_DONTROUTE SO_DONTROUTE
# define BOOST_ASIO_OS_DEF_SO_KEEPALIVE SO_KEEPALIVE
# define BOOST_ASIO_OS_DEF_SO_LINGER SO_LINGER
# define BOOST_ASIO_OS_DEF_SO_OOBINLINE SO_OOBINLINE
# define BOOST_ASIO_OS_DEF_SO_SNDBUF SO_SNDBUF
# define BOOST_ASIO_OS_DEF_SO_RCVBUF SO_RCVBUF
# define BOOST_ASIO_OS_DEF_SO_SNDLOWAT SO_SNDLOWAT
# define BOOST_ASIO_OS_DEF_SO_RCVLOWAT SO_RCVLOWAT
# define BOOST_ASIO_OS_DEF_SO_REUSEADDR SO_REUSEADDR
# define BOOST_ASIO_OS_DEF_TCP_NODELAY TCP_NODELAY
# define BOOST_ASIO_OS_DEF_IP_MULTICAST_IF IP_MULTICAST_IF
# define BOOST_ASIO_OS_DEF_IP_MULTICAST_TTL IP_MULTICAST_TTL
# define BOOST_ASIO_OS_DEF_IP_MULTICAST_LOOP IP_MULTICAST_LOOP
# define BOOST_ASIO_OS_DEF_IP_ADD_MEMBERSHIP IP_ADD_MEMBERSHIP
# define BOOST_ASIO_OS_DEF_IP_DROP_MEMBERSHIP IP_DROP_MEMBERSHIP
# define BOOST_ASIO_OS_DEF_IP_TTL IP_TTL
# define BOOST_ASIO_OS_DEF_IPV6_UNICAST_HOPS IPV6_UNICAST_HOPS
# define BOOST_ASIO_OS_DEF_IPV6_MULTICAST_IF IPV6_MULTICAST_IF
# define BOOST_ASIO_OS_DEF_IPV6_MULTICAST_HOPS IPV6_MULTICAST_HOPS
# define BOOST_ASIO_OS_DEF_IPV6_MULTICAST_LOOP IPV6_MULTICAST_LOOP
# define BOOST_ASIO_OS_DEF_IPV6_JOIN_GROUP IPV6_JOIN_GROUP
# define BOOST_ASIO_OS_DEF_IPV6_LEAVE_GROUP IPV6_LEAVE_GROUP
# define BOOST_ASIO_OS_DEF_AI_CANONNAME AI_CANONNAME
# define BOOST_ASIO_OS_DEF_AI_PASSIVE AI_PASSIVE
# define BOOST_ASIO_OS_DEF_AI_NUMERICHOST AI_NUMERICHOST
# if defined(AI_NUMERICSERV)
#  define BOOST_ASIO_OS_DEF_AI_NUMERICSERV AI_NUMERICSERV
# else
#  define BOOST_ASIO_OS_DEF_AI_NUMERICSERV 0
# endif
# if defined(AI_V4MAPPED)
#  define BOOST_ASIO_OS_DEF_AI_V4MAPPED AI_V4MAPPED
# else
#  define BOOST_ASIO_OS_DEF_AI_V4MAPPED 0
# endif
# if defined(AI_ALL)
#  define BOOST_ASIO_OS_DEF_AI_ALL AI_ALL
# else
#  define BOOST_ASIO_OS_DEF_AI_ALL 0
# endif
# if defined(AI_ADDRCONFIG)
#  define BOOST_ASIO_OS_DEF_AI_ADDRCONFIG AI_ADDRCONFIG
# else
#  define BOOST_ASIO_OS_DEF_AI_ADDRCONFIG 0
# endif
# if defined (_WIN32_WINNT)
const int max_iov_len = 64;
# else
const int max_iov_len = 16;
# endif
#else
typedef int socket_type;
const int invalid_socket = -1;
const int socket_error_retval = -1;
const int max_addr_v4_str_len = INET_ADDRSTRLEN;
#if defined(INET6_ADDRSTRLEN)
const int max_addr_v6_str_len = INET6_ADDRSTRLEN + 1 + IF_NAMESIZE;
#else // defined(INET6_ADDRSTRLEN)
const int max_addr_v6_str_len = 256;
#endif // defined(INET6_ADDRSTRLEN)
typedef sockaddr socket_addr_type;
typedef in_addr in4_addr_type;
# if defined(__hpux)
// HP-UX doesn't provide ip_mreq when _XOPEN_SOURCE_EXTENDED is defined.
struct in4_mreq_type
{
  struct in_addr imr_multiaddr;
  struct in_addr imr_interface;
};
# else
typedef ip_mreq in4_mreq_type;
# endif
typedef sockaddr_in sockaddr_in4_type;
typedef in6_addr in6_addr_type;
typedef ipv6_mreq in6_mreq_type;
typedef sockaddr_in6 sockaddr_in6_type;
typedef sockaddr_storage sockaddr_storage_type;
typedef sockaddr_un sockaddr_un_type;
typedef addrinfo addrinfo_type;
typedef ::linger linger_type;
typedef int ioctl_arg_type;
typedef uint32_t u_long_type;
typedef uint16_t u_short_type;
#if defined(BOOST_ASIO_HAS_SSIZE_T)
typedef ssize_t signed_size_type;
#else // defined(BOOST_ASIO_HAS_SSIZE_T)
typedef int signed_size_type;
#endif // defined(BOOST_ASIO_HAS_SSIZE_T)
# define BOOST_ASIO_OS_DEF(c) BOOST_ASIO_OS_DEF_##c
# define BOOST_ASIO_OS_DEF_AF_UNSPEC AF_UNSPEC
# define BOOST_ASIO_OS_DEF_AF_INET AF_INET
# define BOOST_ASIO_OS_DEF_AF_INET6 AF_INET6
# define BOOST_ASIO_OS_DEF_SOCK_STREAM SOCK_STREAM
# define BOOST_ASIO_OS_DEF_SOCK_DGRAM SOCK_DGRAM
# define BOOST_ASIO_OS_DEF_SOCK_RAW SOCK_RAW
# define BOOST_ASIO_OS_DEF_SOCK_SEQPACKET SOCK_SEQPACKET
# define BOOST_ASIO_OS_DEF_IPPROTO_IP IPPROTO_IP
# define BOOST_ASIO_OS_DEF_IPPROTO_IPV6 IPPROTO_IPV6
# define BOOST_ASIO_OS_DEF_IPPROTO_TCP IPPROTO_TCP
# define BOOST_ASIO_OS_DEF_IPPROTO_UDP IPPROTO_UDP
# define BOOST_ASIO_OS_DEF_IPPROTO_ICMP IPPROTO_ICMP
# define BOOST_ASIO_OS_DEF_IPPROTO_ICMPV6 IPPROTO_ICMPV6
# define BOOST_ASIO_OS_DEF_FIONBIO FIONBIO
# define BOOST_ASIO_OS_DEF_FIONREAD FIONREAD
# define BOOST_ASIO_OS_DEF_INADDR_ANY INADDR_ANY
# define BOOST_ASIO_OS_DEF_MSG_OOB MSG_OOB
# define BOOST_ASIO_OS_DEF_MSG_PEEK MSG_PEEK
# define BOOST_ASIO_OS_DEF_MSG_DONTROUTE MSG_DONTROUTE
# define BOOST_ASIO_OS_DEF_MSG_EOR MSG_EOR
# define BOOST_ASIO_OS_DEF_SHUT_RD SHUT_RD
# define BOOST_ASIO_OS_DEF_SHUT_WR SHUT_WR
# define BOOST_ASIO_OS_DEF_SHUT_RDWR SHUT_RDWR
# define BOOST_ASIO_OS_DEF_SOMAXCONN SOMAXCONN
# define BOOST_ASIO_OS_DEF_SOL_SOCKET SOL_SOCKET
# define BOOST_ASIO_OS_DEF_SO_BROADCAST SO_BROADCAST
# define BOOST_ASIO_OS_DEF_SO_DEBUG SO_DEBUG
# define BOOST_ASIO_OS_DEF_SO_DONTROUTE SO_DONTROUTE
# define BOOST_ASIO_OS_DEF_SO_KEEPALIVE SO_KEEPALIVE
# define BOOST_ASIO_OS_DEF_SO_LINGER SO_LINGER
# define BOOST_ASIO_OS_DEF_SO_OOBINLINE SO_OOBINLINE
# define BOOST_ASIO_OS_DEF_SO_SNDBUF SO_SNDBUF
# define BOOST_ASIO_OS_DEF_SO_RCVBUF SO_RCVBUF
# define BOOST_ASIO_OS_DEF_SO_SNDLOWAT SO_SNDLOWAT
# define BOOST_ASIO_OS_DEF_SO_RCVLOWAT SO_RCVLOWAT
# define BOOST_ASIO_OS_DEF_SO_REUSEADDR SO_REUSEADDR
# define BOOST_ASIO_OS_DEF_TCP_NODELAY TCP_NODELAY
# define BOOST_ASIO_OS_DEF_IP_MULTICAST_IF IP_MULTICAST_IF
# define BOOST_ASIO_OS_DEF_IP_MULTICAST_TTL IP_MULTICAST_TTL
# define BOOST_ASIO_OS_DEF_IP_MULTICAST_LOOP IP_MULTICAST_LOOP
# define BOOST_ASIO_OS_DEF_IP_ADD_MEMBERSHIP IP_ADD_MEMBERSHIP
# define BOOST_ASIO_OS_DEF_IP_DROP_MEMBERSHIP IP_DROP_MEMBERSHIP
# define BOOST_ASIO_OS_DEF_IP_TTL IP_TTL
# define BOOST_ASIO_OS_DEF_IPV6_UNICAST_HOPS IPV6_UNICAST_HOPS
# define BOOST_ASIO_OS_DEF_IPV6_MULTICAST_IF IPV6_MULTICAST_IF
# define BOOST_ASIO_OS_DEF_IPV6_MULTICAST_HOPS IPV6_MULTICAST_HOPS
# define BOOST_ASIO_OS_DEF_IPV6_MULTICAST_LOOP IPV6_MULTICAST_LOOP
# define BOOST_ASIO_OS_DEF_IPV6_JOIN_GROUP IPV6_JOIN_GROUP
# define BOOST_ASIO_OS_DEF_IPV6_LEAVE_GROUP IPV6_LEAVE_GROUP
# define BOOST_ASIO_OS_DEF_AI_CANONNAME AI_CANONNAME
# define BOOST_ASIO_OS_DEF_AI_PASSIVE AI_PASSIVE
# define BOOST_ASIO_OS_DEF_AI_NUMERICHOST AI_NUMERICHOST
# if defined(AI_NUMERICSERV)
#  define BOOST_ASIO_OS_DEF_AI_NUMERICSERV AI_NUMERICSERV
# else
#  define BOOST_ASIO_OS_DEF_AI_NUMERICSERV 0
# endif
// Note: QNX Neutrino 6.3 defines AI_V4MAPPED, AI_ALL and AI_ADDRCONFIG but
// does not implement them. Therefore they are specifically excluded here.
# if defined(AI_V4MAPPED) && !defined(__QNXNTO__)
#  define BOOST_ASIO_OS_DEF_AI_V4MAPPED AI_V4MAPPED
# else
#  define BOOST_ASIO_OS_DEF_AI_V4MAPPED 0
# endif
# if defined(AI_ALL) && !defined(__QNXNTO__)
#  define BOOST_ASIO_OS_DEF_AI_ALL AI_ALL
# else
#  define BOOST_ASIO_OS_DEF_AI_ALL 0
# endif
# if defined(AI_ADDRCONFIG) && !defined(__QNXNTO__)
#  define BOOST_ASIO_OS_DEF_AI_ADDRCONFIG AI_ADDRCONFIG
# else
#  define BOOST_ASIO_OS_DEF_AI_ADDRCONFIG 0
# endif
# if defined(IOV_MAX)
const int max_iov_len = IOV_MAX;
# else
// POSIX platforms are not required to define IOV_MAX.
const int max_iov_len = 16;
# endif
#endif
const int custom_socket_option_level = 0xA5100000;
const int enable_connection_aborted_option = 1;
const int always_fail_option = 2;

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_SOCKET_TYPES_HPP

/* socket_types.hpp
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
*/