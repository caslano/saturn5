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
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
*/