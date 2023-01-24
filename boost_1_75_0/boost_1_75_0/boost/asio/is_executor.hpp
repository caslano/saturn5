//
// is_executor.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IS_EXECUTOR_HPP
#define BOOST_ASIO_IS_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/is_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// The is_executor trait detects whether a type T meets the Executor type
/// requirements.
/**
 * Class template @c is_executor is a UnaryTypeTrait that is derived from @c
 * true_type if the type @c T meets the syntactic requirements for Executor,
 * otherwise @c false_type.
 */
template <typename T>
struct is_executor
#if defined(GENERATING_DOCUMENTATION)
  : integral_constant<bool, automatically_determined>
#else // defined(GENERATING_DOCUMENTATION)
  : boost::asio::detail::is_executor<T>
#endif // defined(GENERATING_DOCUMENTATION)
{
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IS_EXECUTOR_HPP

/* is_executor.hpp
LPnTtXswvAgsE1jzV672rIdkXLgt2EeWJzGvbesXuO4v/mHisUFaznycE5ay+2wFAmQiPuYNfX0GckDirrxeYj6ZeWxF0z/W6iXUgO/ekQwnRyyGfvJIKBpPZh47quSmHzF14Qu6qGshmM8hLf7WOpkMjUZz/fZ+g+FZiQLPzENtfuuQkUzmqig7359zyag6XREVdnVeAw9vvdM0zUIvhkSeH1nI7PI2vTgu8EXv1n4LMPTVaMDZ1vq36EB/6hZJX2C0+WPKLu4/BfXXj8hh+4/3NrZsuQgtDHTFHD+VH915sXN65/H+1s8lPceI3t8mVAcyXjsE2iRYG88QbgaaeU1lyy/KziTE7VFGsihj6UVJy70oo1KNpfxy5ohYewlf9D5e/neyBExV6TxcoY3UF0irIrS+gfYBNk6UgmZj1wRqj0qpdeNZ7lFZixUB0NuN3KNQ9FE5GOfjXx1CMyosIDDVQu/RZrO1jRSjFmUC80mitGUsCiaG/wbSG6PK1L9WtBXz83dYLMJ711eqv4V6Lr1AZuP5vBiEH3YTXmr7xX7hHb9eNoHNZzBPzVG+F3U1nrWmkz8kfHmmYZDffOFEw3D2hCz6BWO0bgBdUX5IVZDukp+7yYSMyC9ltzcih2SW9D7/6CbigQpltqjmaFdPK66lapm9T9X1IuINvyNU2ecTMKQf5P9VJRsLrecNEt7C+qj173OZWq/O8dv4
*/