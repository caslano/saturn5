//
// detail/socket_types.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
struct sockaddr_un_type { u_short sun_family; char sun_path[108]; };
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