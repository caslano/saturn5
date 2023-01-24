//
// ip/impl/basic_endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_IMPL_BASIC_ENDPOINT_HPP
#define BOOST_ASIO_IP_IMPL_BASIC_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/detail/throw_error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

template <typename Elem, typename Traits, typename InternetProtocol>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os,
    const basic_endpoint<InternetProtocol>& endpoint)
{
  boost::asio::ip::detail::endpoint tmp_ep(endpoint.address(), endpoint.port());
  return os << tmp_ep.to_string().c_str();
}

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_IP_IMPL_BASIC_ENDPOINT_HPP

/* basic_endpoint.hpp
WWRux97LmT3oEgfE3oQpf6MZb0H7D83Lfv4+y+kmX8t+Yq8mr1qehhqsMfPhmvPdhJRiKcwYdQ8Ee3a7hasqHdQr8NCivV9JAoQINFvXC+WyPi8WfBVYtqHFAJbjiERPy1WN9ixqr0X7bGrfL6H0XFTD+S5NlQVMtg6FKFWI7yxYjqLlBFh2tVC1EPu8F6kaWzSUA9ezSQ3rfcy+g8WrCfhky32PH9q39qyP5hWAtwC2AuwE+AJgCsDXAP0BegKcB2Ags3YAnQHKynSL85n8vEVMTt48hBHDod2kFmblYrtKTcsj7S2VTSXuwicKWGJCMAahd5oui7TBjJy8vAKwLMhLz0A34AVc9FxVwh5yQc4+2vaUSmPu9QVeXRAvxFcLF+LJFTC8FR9nfvkArm2VlD85xHGLvy8+5k1v8avM/GFc/dFYn0iINR/fLyCzpmGUFi7wq7KV1iDzOJADvHgdruT2O5457pxwvgbfYOcJkgZAct+1ff56S2zNIclbE6psjXndAczSz/Hgd1ORrmCRpu5vo0iHv3BXJB/zjkNNRfpjX1tF8iFFypC7KdKOfe6K5ANF+uIL1yIlZjPZjPlJSEnfXbCPbsBL1jbzfPDK4Jd3VH/6FRDpKB0+Hk2WROntcH655nxv4W2TM/uF8k7D8vbG8oaQF7zPdyUl9jMfqCIlJm+MYhGAuK5IXs1lTP/1a/gQhzI2wfxLJeEG
*/