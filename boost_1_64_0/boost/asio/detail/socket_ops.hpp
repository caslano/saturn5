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
7Bxc5YLwHITsdHfP4Pu51W8PvhNI8szbXVxeVqz5CNdOF/du0lVW//vgW8QofGYnt1rPC4/d/8TKPB/8KHxfmNzppPMdQ3ac89taaRz9aivzYrA7KbTPnNEXbG/tl7j20WP/BbuRnKh55ivSPzHm/YMluvuP8sEfo/SeMf6rrBu7OHMwwc7p55F/PZJC55GOTeuU1tOeRhpzFqnmFbZY+63d+5Rfs/oyYpXEWTzHxp5Hqng9YuXaOWPt8jcXf5+w4/HVN3rKRlhG49Nbrczi+8LvSKTMKmQec2RujSfzMDJPGpn0xSXR4/rtJdM/OZQOi/uaREg2l/TXcDbrbTbNj5E+GHjK6pPipsNaa94+Imx5+PtrJ/wto9OhPXrzDk/XfMNTvZ3fKY1gLe/FMfMOn+Cv5h3cO/94P6g/nPdDZ4FqTtkp/zoLVPfmOOW7ecSdf6HyG7kGaL3m1BdpbU4J6o/4tf/T2PeVq+nivauSb+2+U2kHjT6PMxRSlB8x76rsdIl9L/WONLFuTA2cGH4vZaeD33upuSzct/ZyGX9P0/sYstfOM39YYgMTmoPLlF+47N4J/bny7fFDnzfpztfmxOaT7jKKzKdcn3zK882ncL06U/PVN2qv0OWoP+HXioOx+TS/tLyM8cR4eSU7vdw74x61+nlWvr1N01IbWM1fS767eyfcQ1ZfHpNvDVTnbrbm5yrPQva7+uRZ+PzQ++Wm8kt2jovOL/e80KeUX7qD153je1zv3G9q8a4dKs/a27yw6XDYeeZ+3+vGfm9fwa+Zf/fkmc70r6fvhKe9gdyRtzdwS+2NcBlaneYIXmLCJL5uypA3PNwaHvltVrj0/VLYZCcrvG7N6s9mz3sw3rdZdjq43+Z7rT6POYo03/V1m635JOqQjNhvpOqZF6zMQGqeFu68++P22UmBRjw1380D5EObNMqEqbeTOqQnp6QnHcf/fnPUzSU/HPnfGvm0vumJDWLXwYX0d2fUvP6tcUSekI56NjCiDo+sl3ekOw5coDsIz0e9jf3sf0Tmlerl6Hxy1y+MtPKn426K8i7kRvN49bLM28bWlcrrXGs+NdCH/8My5YXec/SvsTL1dR+x6lL7TTy8d9NNM//6NKJ8d2zgOPBzfcuuRP0V+zt80kx1ZLzyLTtt3XL2ntUvYD4uJV49KTut3PL7jtVXsfozM25afmxl5gcGHyItW37mpKXWNKiuC6Xl4dd3bpr613cR9zCsaODfR9nh6aPQ0ah1/yR7ePz+yYEGsfXly4R1zWdhv5zeyeH3T0Ln369p6Bi0kUBr1AeNiY/jBwdTm4q8Xx8ex2tHSrZN3PP8n7fmLcNpcog1XqluebZ+RKTHqozY9HhviHmZbFiLWM9l0ySg78fOiO+H5PQeVzWKvgs20rxxIPLs/jky935/ymtx74O+P/qmFoTXrDWKuX8Vmmex380VjWLjvd/UfeF4q6/qxPv9qHhn1xDv7Brinf0V4v3+V4j3lMax8f7QtBc+1zr5IuV3vPaCJ14LG0XeFTxW5t54/eAw4vVCVLxwX3fsRsYhs0lsHA6YNoYnDso73zGWFTXEYcVXiAN++ccham3opib+a1e3fN7ssNeuYudrX7u6vKn/2tU9nzc77LWr2Dnk2lXMv5W1q12axcbpTVPXfaE4hYqNEtyE989DYuKD/JGnN+4pvJFhO+gTtteQzYoJm11ybsP2u5iwSV5pvdLnnkvMj3jNOf5Fp7XKO35ExWdb89j4vGXGAaPjo8Ljn9aSj192MD/ysvPnITWXndA3Pa+l48K7qBao11GfmDEMp41iR6LzS/qaZPC971nxkXwru5Y5N07bcKwr18HtPzf5yOiftvI=
*/