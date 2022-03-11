//
// detail/socket_ops.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SOCKET_OPS_HPP
#define BOOST_ASIO_DETAIL_SOCKET_OPS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/system/error_code.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {
namespace socket_ops {

// Socket state bits.
enum
{
  // The user wants a non-blocking socket.
  user_set_non_blocking = 1,

  // The socket has been set non-blocking.
  internal_non_blocking = 2,

  // Helper "state" used to determine whether the socket is non-blocking.
  non_blocking = user_set_non_blocking | internal_non_blocking,

  // User wants connection_aborted errors, which are disabled by default.
  enable_connection_aborted = 4,

  // The user set the linger option. Needs to be checked when closing.
  user_set_linger = 8,

  // The socket is stream-oriented.
  stream_oriented = 16,

  // The socket is datagram-oriented.
  datagram_oriented = 32,

  // The socket may have been dup()-ed.
  possible_dup = 64
};

typedef unsigned char state_type;

struct noop_deleter { void operator()(void*) {} };
typedef shared_ptr<void> shared_cancel_token_type;
typedef weak_ptr<void> weak_cancel_token_type;

#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)

BOOST_ASIO_DECL socket_type accept(socket_type s, socket_addr_type* addr,
    std::size_t* addrlen, boost::system::error_code& ec);

BOOST_ASIO_DECL socket_type sync_accept(socket_type s,
    state_type state, socket_addr_type* addr,
    std::size_t* addrlen, boost::system::error_code& ec);

#if defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL void complete_iocp_accept(socket_type s,
    void* output_buffer, DWORD address_length,
    socket_addr_type* addr, std::size_t* addrlen,
    socket_type new_socket, boost::system::error_code& ec);

#else // defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL bool non_blocking_accept(socket_type s,
    state_type state, socket_addr_type* addr, std::size_t* addrlen,
    boost::system::error_code& ec, socket_type& new_socket);

#endif // defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL int bind(socket_type s, const socket_addr_type* addr,
    std::size_t addrlen, boost::system::error_code& ec);

BOOST_ASIO_DECL int close(socket_type s, state_type& state,
    bool destruction, boost::system::error_code& ec);

BOOST_ASIO_DECL bool set_user_non_blocking(socket_type s,
    state_type& state, bool value, boost::system::error_code& ec);

BOOST_ASIO_DECL bool set_internal_non_blocking(socket_type s,
    state_type& state, bool value, boost::system::error_code& ec);

BOOST_ASIO_DECL int shutdown(socket_type s,
    int what, boost::system::error_code& ec);

BOOST_ASIO_DECL int connect(socket_type s, const socket_addr_type* addr,
    std::size_t addrlen, boost::system::error_code& ec);

BOOST_ASIO_DECL void sync_connect(socket_type s, const socket_addr_type* addr,
    std::size_t addrlen, boost::system::error_code& ec);

#if defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL void complete_iocp_connect(socket_type s,
    boost::system::error_code& ec);

#endif // defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL bool non_blocking_connect(socket_type s,
    boost::system::error_code& ec);

BOOST_ASIO_DECL int socketpair(int af, int type, int protocol,
    socket_type sv[2], boost::system::error_code& ec);

BOOST_ASIO_DECL bool sockatmark(socket_type s, boost::system::error_code& ec);

BOOST_ASIO_DECL size_t available(socket_type s, boost::system::error_code& ec);

BOOST_ASIO_DECL int listen(socket_type s,
    int backlog, boost::system::error_code& ec);

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
typedef WSABUF buf;
#else // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
typedef iovec buf;
#endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

BOOST_ASIO_DECL void init_buf(buf& b, void* data, size_t size);

BOOST_ASIO_DECL void init_buf(buf& b, const void* data, size_t size);

BOOST_ASIO_DECL signed_size_type recv(socket_type s, buf* bufs,
    size_t count, int flags, boost::system::error_code& ec);

BOOST_ASIO_DECL size_t sync_recv(socket_type s, state_type state, buf* bufs,
    size_t count, int flags, bool all_empty, boost::system::error_code& ec);

#if defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL void complete_iocp_recv(state_type state,
    const weak_cancel_token_type& cancel_token, bool all_empty,
    boost::system::error_code& ec, size_t bytes_transferred);

#else // defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL bool non_blocking_recv(socket_type s,
    buf* bufs, size_t count, int flags, bool is_stream,
    boost::system::error_code& ec, size_t& bytes_transferred);

#endif // defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL signed_size_type recvfrom(socket_type s, buf* bufs,
    size_t count, int flags, socket_addr_type* addr,
    std::size_t* addrlen, boost::system::error_code& ec);

BOOST_ASIO_DECL size_t sync_recvfrom(socket_type s, state_type state,
    buf* bufs, size_t count, int flags, socket_addr_type* addr,
    std::size_t* addrlen, boost::system::error_code& ec);

#if defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL void complete_iocp_recvfrom(
    const weak_cancel_token_type& cancel_token,
    boost::system::error_code& ec);

#else // defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL bool non_blocking_recvfrom(socket_type s,
    buf* bufs, size_t count, int flags,
    socket_addr_type* addr, std::size_t* addrlen,
    boost::system::error_code& ec, size_t& bytes_transferred);

#endif // defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL signed_size_type recvmsg(socket_type s, buf* bufs,
    size_t count, int in_flags, int& out_flags,
    boost::system::error_code& ec);

BOOST_ASIO_DECL size_t sync_recvmsg(socket_type s, state_type state,
    buf* bufs, size_t count, int in_flags, int& out_flags,
    boost::system::error_code& ec);

#if defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL void complete_iocp_recvmsg(
    const weak_cancel_token_type& cancel_token,
    boost::system::error_code& ec);

#else // defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL bool non_blocking_recvmsg(socket_type s,
    buf* bufs, size_t count, int in_flags, int& out_flags,
    boost::system::error_code& ec, size_t& bytes_transferred);

#endif // defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL signed_size_type send(socket_type s, const buf* bufs,
    size_t count, int flags, boost::system::error_code& ec);

BOOST_ASIO_DECL size_t sync_send(socket_type s, state_type state,
    const buf* bufs, size_t count, int flags,
    bool all_empty, boost::system::error_code& ec);

#if defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL void complete_iocp_send(
    const weak_cancel_token_type& cancel_token,
    boost::system::error_code& ec);

#else // defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL bool non_blocking_send(socket_type s,
    const buf* bufs, size_t count, int flags,
    boost::system::error_code& ec, size_t& bytes_transferred);

#endif // defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL signed_size_type sendto(socket_type s, const buf* bufs,
    size_t count, int flags, const socket_addr_type* addr,
    std::size_t addrlen, boost::system::error_code& ec);

BOOST_ASIO_DECL size_t sync_sendto(socket_type s, state_type state,
    const buf* bufs, size_t count, int flags, const socket_addr_type* addr,
    std::size_t addrlen, boost::system::error_code& ec);

#if !defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL bool non_blocking_sendto(socket_type s,
    const buf* bufs, size_t count, int flags,
    const socket_addr_type* addr, std::size_t addrlen,
    boost::system::error_code& ec, size_t& bytes_transferred);

#endif // !defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL socket_type socket(int af, int type, int protocol,
    boost::system::error_code& ec);

BOOST_ASIO_DECL int setsockopt(socket_type s, state_type& state,
    int level, int optname, const void* optval,
    std::size_t optlen, boost::system::error_code& ec);

BOOST_ASIO_DECL int getsockopt(socket_type s, state_type state,
    int level, int optname, void* optval,
    size_t* optlen, boost::system::error_code& ec);

BOOST_ASIO_DECL int getpeername(socket_type s, socket_addr_type* addr,
    std::size_t* addrlen, bool cached, boost::system::error_code& ec);

BOOST_ASIO_DECL int getsockname(socket_type s, socket_addr_type* addr,
    std::size_t* addrlen, boost::system::error_code& ec);

BOOST_ASIO_DECL int ioctl(socket_type s, state_type& state,
    int cmd, ioctl_arg_type* arg, boost::system::error_code& ec);

BOOST_ASIO_DECL int select(int nfds, fd_set* readfds, fd_set* writefds,
    fd_set* exceptfds, timeval* timeout, boost::system::error_code& ec);

BOOST_ASIO_DECL int poll_read(socket_type s,
    state_type state, int msec, boost::system::error_code& ec);

BOOST_ASIO_DECL int poll_write(socket_type s,
    state_type state, int msec, boost::system::error_code& ec);

BOOST_ASIO_DECL int poll_error(socket_type s,
    state_type state, int msec, boost::system::error_code& ec);

BOOST_ASIO_DECL int poll_connect(socket_type s,
    int msec, boost::system::error_code& ec);

#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)

BOOST_ASIO_DECL const char* inet_ntop(int af, const void* src, char* dest,
    size_t length, unsigned long scope_id, boost::system::error_code& ec);

BOOST_ASIO_DECL int inet_pton(int af, const char* src, void* dest,
    unsigned long* scope_id, boost::system::error_code& ec);

BOOST_ASIO_DECL int gethostname(char* name,
    int namelen, boost::system::error_code& ec);

#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)

BOOST_ASIO_DECL boost::system::error_code getaddrinfo(const char* host,
    const char* service, const addrinfo_type& hints,
    addrinfo_type** result, boost::system::error_code& ec);

BOOST_ASIO_DECL boost::system::error_code background_getaddrinfo(
    const weak_cancel_token_type& cancel_token, const char* host,
    const char* service, const addrinfo_type& hints,
    addrinfo_type** result, boost::system::error_code& ec);

BOOST_ASIO_DECL void freeaddrinfo(addrinfo_type* ai);

BOOST_ASIO_DECL boost::system::error_code getnameinfo(
    const socket_addr_type* addr, std::size_t addrlen,
    char* host, std::size_t hostlen, char* serv,
    std::size_t servlen, int flags, boost::system::error_code& ec);

BOOST_ASIO_DECL boost::system::error_code sync_getnameinfo(
    const socket_addr_type* addr, std::size_t addrlen,
    char* host, std::size_t hostlen, char* serv,
    std::size_t servlen, int sock_type, boost::system::error_code& ec);

BOOST_ASIO_DECL boost::system::error_code background_getnameinfo(
    const weak_cancel_token_type& cancel_token,
    const socket_addr_type* addr, std::size_t addrlen,
    char* host, std::size_t hostlen, char* serv,
    std::size_t servlen, int sock_type, boost::system::error_code& ec);

#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)

BOOST_ASIO_DECL u_long_type network_to_host_long(u_long_type value);

BOOST_ASIO_DECL u_long_type host_to_network_long(u_long_type value);

BOOST_ASIO_DECL u_short_type network_to_host_short(u_short_type value);

BOOST_ASIO_DECL u_short_type host_to_network_short(u_short_type value);

} // namespace socket_ops
} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/socket_ops.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_SOCKET_OPS_HPP

/* socket_ops.hpp
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
*/