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
wzE6Vap5RXuIjOy8R0ry7vcRaLOA+xp7J/zPgvrkbv5bX+7eB8/hX45V+h6uRYrZ7kIgCvAy7Z1CIomO512ru16a4QFl5WldOdfharfNoGgfkqjNjXLGO2etkJu66gFThU/O8nwTTDaSj1ibsNuOskza+9VhUI7xUOwuPT3wlBFwir6OF7NpuCAzef9HxPKEQVx3Ip5opDoQ7QLFJZVVIT3ZjeTgNnDf5Ff1ehBUn9qP6WVlbYm9km8QSGJWWeKNsm/q/yCnMygUxNKPA2LMorei0FJRiCyD28R7GDQmgHra1Lst75fVm18DimTPNvjF/RXhcovkMSocKR6y/oy4gaYxjHD7J/Kl65wOr/H1AqiZYykqGjxIX6gI2j1DX2Nz4BVtKR1ePJ1hNgmBFTjvj5lqZt/lF3GnXI1ZEiESfrjXFC6pLml+jy17XQb/A/Xa+AhXrshoCja7iJ3dzTIeygOiBieIslz4eV4FP05JNoczx207nbuBVjZyqzolPjM9ek6/fdxnxX+CO2Ype2blJ+UybknaUQoMaDJTUp8L5+pU8rEffj1Lmx09mw==
*/