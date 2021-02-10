//
// detail/handler_invoke_helpers.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_HANDLER_INVOKE_HELPERS_HPP
#define BOOST_ASIO_DETAIL_HANDLER_INVOKE_HELPERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/handler_invoke_hook.hpp>

#include <boost/asio/detail/push_options.hpp>

// Calls to asio_handler_invoke must be made from a namespace that does not
// contain overloads of this function. The boost_asio_handler_invoke_helpers
// namespace is defined here for that purpose.
namespace boost_asio_handler_invoke_helpers {

template <typename Function, typename Context>
inline void invoke(Function& function, Context& context)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  Function tmp(function);
  tmp();
#else
  using boost::asio::asio_handler_invoke;
  asio_handler_invoke(function, boost::asio::detail::addressof(context));
#endif
}

template <typename Function, typename Context>
inline void invoke(const Function& function, Context& context)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  Function tmp(function);
  tmp();
#else
  using boost::asio::asio_handler_invoke;
  asio_handler_invoke(function, boost::asio::detail::addressof(context));
#endif
}

} // namespace boost_asio_handler_invoke_helpers

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_HANDLER_INVOKE_HELPERS_HPP

/* handler_invoke_helpers.hpp
JCqVwSDiUVxwvXzVgCe6kj6TbBmCWOfWPjkeC65KPGiGu7LS0VylwdMMmxsxrcDxnDkmevJztaY2a61QIZjFM7g7uODpkkpQy1hM7jA9eewlOcysvoI4e/8OUGzQK9R3L78KvOeiW6SZXmF6NHv/vQR55mrLdHK6diH7jZzc0wTiShaEkexIWZxL8k9BP7kQHvMrMT/EiQhwFg+5BSw5O+usUjzpO4Mw4E4f1Z5t+daDhp5LCtgBQncuDyvkdJRwVtpcFtIunGytldcghhr3cAVawF0Mqx0ObK26lBPgC+gZeFV9JsocJqzseFQ70C0XKQObadUxB49goRqYbiAPe3FdtxammB+5FQb2SY01/X/LXW5w5OKxyhDzBNY33cHXlqcWgFmuwpatO8v9esAGAn5leSADgE1uRlyKg+68tLCJMivQM4YgG9Aiok8ERtPha/jyvkdhD+Xx6ik0qmeNKp10Zzk3Ac65LWGuPU8ceIVj36wtw09zzWVv2MZ4P56GknIhIDWl7mHIKOTxxtzf4uQUCEFjKjahZjzkOpBznqImH2sQuFDFIVAxCXQePq0Q1vqOCB4t51AHw3p2D7kWNcBwyPMhlANQG90zuhMjexxO0OjgOISfeti9huxqlg/ybI649j0dY5BHLPZT
*/