//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BUFFERS_ADAPTER_HPP
#define BOOST_BEAST_BUFFERS_ADAPTER_HPP

#include <boost/beast/core/detail/config.hpp>

#ifdef BOOST_BEAST_ALLOW_DEPRECATED

#include <boost/beast/core/buffers_adaptor.hpp>

namespace boost {
namespace beast {

template<class MutableBufferSequence>
using buffers_adapter = buffers_adaptor<MutableBufferSequence>;

} // beast
} // boost

#else

// The new filename is <boost/beast/core/buffers_adaptor.hpp>
#error The file <boost/beast/core/buffers_adapter.hpp> is deprecated, define BOOST_BEAST_ALLOW_DEPRECATED to disable this error

#endif

#endif

/* buffers_adapter.hpp
DuYxQ8qexftoATEz3Sflz9AHzxZy9ctSoVe/xFgCPdcSm85YDWP1jJmMrWPsAca2M/YEYzsZe5Oxdxg7wtgxxpIMjaUaGhvG2CjGqhlbythWxrYx9gJj+xg7ztgJxrJ9GsvxaexixsoYW8nY1Yzdx9gvGNvP2O8YO87YCcY6+DWW5tfYQMZyGXsIYiZhj6lYAi35IXnp7TSv4eTqlJvfEthd3KNWgE35j3U+DMMb12IQ8u9v/gi1X3Hlir0702k=
*/