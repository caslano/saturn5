//
// detail/resolve_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_RESOLVE_OP_HPP
#define BOOST_ASIO_DETAIL_RESOLVE_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class resolve_op : public operation
{
public:
  // The error code to be passed to the completion handler.
  boost::system::error_code ec_;

protected:
  resolve_op(func_type complete_func)
    : operation(complete_func)
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_RESOLVE_OP_HPP

/* resolve_op.hpp
B1S9llBSbo8+vzlinzWBwQwpo99LZr9AvLPSsEa7l3prTbhEeQj565ifSB5lrcJVJaOomAENXYUE7lG/V67caG2ULVwJkhef6sUJQ5FsdnB+GhBNM41Z0/m1xXW0IkwuFuIm4pS01rZdt2zcU9rTGwoYcsWDJld/JuONykKiK2nF7b6QOGosHg3R3UO+vHaQiFc5ic0no1qnXd3L45Kwihy0YjZA7yB0o4UN3jQTtHpU5l89YEGRYdns8Z/Z1m++yA76DkPmvrWgJgX2pI4cRIkNEDziLpwxHPy0VzG8IL5UugeCttiCazceBb/uxTmfg+TVBe4jiTD+tdeBY+2SV6u5NHEWbodIfEj2JFpc2et1St6u5FAKPM5Ru9GbQG/EKJZ6VcHIexqlBMvrWvlpTDHhlGMFeOg2LBhvIigyPJeQabRhumTKCkadLrAf3ZvSgEZ/ETX+4tWHq8sIg//MFruuwmDaO3yalkfiXViw5LttUr+AQbMzsqhldL8T1gNiZCPkkpIi4aWHueKAcR0nWbqpsULKvQf3NYrakMVswp3o+avKY9+aI3urcMuktzyAkQAlYElVLBQ4cLdaTeLWg5JAlC6yaEhLbyOrEUiuvsjSguSovyXQJcFqMjuaXKjj8vcf3r1//ebHlwkW
*/