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
EcyiNkpRXikKNVL1ZdBMl7p4nEv7T6DIY/xVZAz5qGp1AwP9h/NEPyFXo05vAVr9BqgRwjW+2Pv52CIGRBYm23FxkqL1IvccF6k7mesIMvpBYjyDYiSoMB7Uvh/YRS5tP8DH+PaDfOS063yc3bhL9WZL0GJ2rbX9MKLC2clYqBYpGzBDeyKFvbD2PFPTYHhDEqjRJSly2V30ktWu9Y6odhilD+lLbR/SSj2t+nSVQ6h1gE35
*/