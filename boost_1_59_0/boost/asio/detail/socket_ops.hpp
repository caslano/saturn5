//
// detail/socket_ops.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

BOOST_ASIO_DECL signed_size_type recv1(socket_type s,
    void* data, size_t size, int flags, boost::system::error_code& ec);

BOOST_ASIO_DECL size_t sync_recv(socket_type s, state_type state, buf* bufs,
    size_t count, int flags, bool all_empty, boost::system::error_code& ec);

BOOST_ASIO_DECL size_t sync_recv1(socket_type s, state_type state,
    void* data, size_t size, int flags, boost::system::error_code& ec);

#if defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL void complete_iocp_recv(state_type state,
    const weak_cancel_token_type& cancel_token, bool all_empty,
    boost::system::error_code& ec, size_t bytes_transferred);

#else // defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL bool non_blocking_recv(socket_type s,
    buf* bufs, size_t count, int flags, bool is_stream,
    boost::system::error_code& ec, size_t& bytes_transferred);

BOOST_ASIO_DECL bool non_blocking_recv1(socket_type s,
    void* data, size_t size, int flags, bool is_stream,
    boost::system::error_code& ec, size_t& bytes_transferred);

#endif // defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL signed_size_type recvfrom(socket_type s, buf* bufs,
    size_t count, int flags, socket_addr_type* addr,
    std::size_t* addrlen, boost::system::error_code& ec);

BOOST_ASIO_DECL signed_size_type recvfrom1(socket_type s, void* data,
    size_t size, int flags, socket_addr_type* addr,
    std::size_t* addrlen, boost::system::error_code& ec);

BOOST_ASIO_DECL size_t sync_recvfrom(socket_type s, state_type state,
    buf* bufs, size_t count, int flags, socket_addr_type* addr,
    std::size_t* addrlen, boost::system::error_code& ec);

BOOST_ASIO_DECL size_t sync_recvfrom1(socket_type s, state_type state,
    void* data, size_t size, int flags, socket_addr_type* addr,
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

BOOST_ASIO_DECL bool non_blocking_recvfrom1(socket_type s,
    void* data, size_t size, int flags,
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

BOOST_ASIO_DECL signed_size_type send1(socket_type s,
    const void* data, size_t size, int flags, boost::system::error_code& ec);

BOOST_ASIO_DECL size_t sync_send(socket_type s, state_type state,
    const buf* bufs, size_t count, int flags,
    bool all_empty, boost::system::error_code& ec);

BOOST_ASIO_DECL size_t sync_send1(socket_type s, state_type state,
    const void* data, size_t size, int flags, boost::system::error_code& ec);

#if defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL void complete_iocp_send(
    const weak_cancel_token_type& cancel_token,
    boost::system::error_code& ec);

#else // defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL bool non_blocking_send(socket_type s,
    const buf* bufs, size_t count, int flags,
    boost::system::error_code& ec, size_t& bytes_transferred);

BOOST_ASIO_DECL bool non_blocking_send1(socket_type s,
    const void* data, size_t size, int flags,
    boost::system::error_code& ec, size_t& bytes_transferred);

#endif // defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL signed_size_type sendto(socket_type s, const buf* bufs,
    size_t count, int flags, const socket_addr_type* addr,
    std::size_t addrlen, boost::system::error_code& ec);

BOOST_ASIO_DECL signed_size_type sendto1(socket_type s, const void* data,
    size_t size, int flags, const socket_addr_type* addr,
    std::size_t addrlen, boost::system::error_code& ec);

BOOST_ASIO_DECL size_t sync_sendto(socket_type s, state_type state,
    const buf* bufs, size_t count, int flags, const socket_addr_type* addr,
    std::size_t addrlen, boost::system::error_code& ec);

BOOST_ASIO_DECL size_t sync_sendto1(socket_type s, state_type state,
    const void* data, size_t size, int flags, const socket_addr_type* addr,
    std::size_t addrlen, boost::system::error_code& ec);

#if !defined(BOOST_ASIO_HAS_IOCP)

BOOST_ASIO_DECL bool non_blocking_sendto(socket_type s,
    const buf* bufs, size_t count, int flags,
    const socket_addr_type* addr, std::size_t addrlen,
    boost::system::error_code& ec, size_t& bytes_transferred);

BOOST_ASIO_DECL bool non_blocking_sendto1(socket_type s,
    const void* data, size_t size, int flags,
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