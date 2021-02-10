//
// detail/handler_cont_helpers.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_HANDLER_CONT_HELPERS_HPP
#define BOOST_ASIO_DETAIL_HANDLER_CONT_HELPERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/handler_continuation_hook.hpp>

#include <boost/asio/detail/push_options.hpp>

// Calls to asio_handler_is_continuation must be made from a namespace that
// does not contain overloads of this function. This namespace is defined here
// for that purpose.
namespace boost_asio_handler_cont_helpers {

template <typename Context>
inline bool is_continuation(Context& context)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  return false;
#else
  using boost::asio::asio_handler_is_continuation;
  return asio_handler_is_continuation(
      boost::asio::detail::addressof(context));
#endif
}

} // namespace boost_asio_handler_cont_helpers

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_HANDLER_CONT_HELPERS_HPP

/* handler_cont_helpers.hpp
yFM8aI8/aZ4yL4fbthHwPDf6xQGFw6p23Fqg80S+5dCtcT1pWajGXydJpmLqEvR5SgTdmtKTbphVW6rPQsqqdBtJ2fDXdMC9/z6Le/MDZyy1aeRALwn9dpfebRVPdevLl12S9UYxWSBiru/3BU15Ep8+gljJgOr+ssefjK2kvwT4xJhjxoYN0PBw8tB4jaSjFnvV03Br2v4X3xOlYrwmorbYSygw4mebdtV9UTxOP9LcUFZHIMv2kfQ90eX+CeZyLRwkHt7BjZTQjhmP0BQ6fGpAyCfDqKCQL7Ztas4sfnzhsoj5wIKuUNIukMzGCNTU1PDk+OJET5onDsMA8+koJK8mcqhWB8YQz2EVODJ4IkzKrz1E/MSvROiw4zpmvyZhXTyu4XXMV6WzSnq9y5GFkcJd1D3GYN/A8lJ9VXZMQKWxfcQvKiwbxKTa8IfpfDAaI+BJKyIGAoSs6K/7WMmgEnD2cc+MQjmElgrxyVi0JhxGGEVwAyKe2HJpwzixPL1QkqwMlB/s71YOp4KvJYefPPE4rmdOjoyxvycuVIuqxCAkqrlUBBUKUkz5pz2q6LhqnquQ8/zkDrps6x/+TL0FkRN98h2I01NOd7AHzI4f2hiqFCh5zW1zbwo67mvD7cs/++lPhwuYv/Jqw72G
*/