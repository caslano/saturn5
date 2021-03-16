//
// detail/noncopyable.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NONCOPYABLE_HPP
#define BOOST_ASIO_DETAIL_NONCOPYABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class noncopyable
{
protected:
  noncopyable() {}
  ~noncopyable() {}
private:
  noncopyable(const noncopyable&);
  const noncopyable& operator=(const noncopyable&);
};

} // namespace detail

using boost::asio::detail::noncopyable;

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_NONCOPYABLE_HPP

/* noncopyable.hpp
ZAdmAccC+wDPA54BvABYCBwPnAG8FFgFnAa8E1gKfAI4HbgVOBP4GnAu8BNgBfAX4NXAdAyvFgH7Aa8DFgAXAycAl5L/wBpgOfAm4GIg2kQ4AqwDLgPeDKwH3g18HPgHShdwNfAL4L1Ammg/QOEC0ZbCpAbyMLAV8BEgrQU96lbyOOQwmhRkSpaHcyluBnPzmVvA3Arm7mRuLXMPMbeZuVeY28PcO8x9wtwB5tyW4ZIsw7Vj7iTmejLXh7nzmZs=
*/