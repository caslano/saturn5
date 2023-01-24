//
// ip/resolver_query_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_RESOLVER_QUERY_BASE_HPP
#define BOOST_ASIO_IP_RESOLVER_QUERY_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/ip/resolver_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// The resolver_query_base class is used as a base for the
/// basic_resolver_query class templates to provide a common place to define
/// the flag constants.
class resolver_query_base : public resolver_base
{
protected:
  /// Protected destructor to prevent deletion through this type.
  ~resolver_query_base()
  {
  }
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_RESOLVER_QUERY_BASE_HPP

/* resolver_query_base.hpp
nnCOehUHChR/aQLG4LM0AWNQKk3AGBRLEzAGKmkCxuCxNAFjkCNNwBgokcjrRMCaWC0hhaKmw0GQftqWr4BXNrxy4ZUPLw28tPAqh9cAWPdweI2F18/wmgKvmfCKgdeSM3jhMgm9MwdXhrwrNtLcGBv06oG18r3lqKl5b+F875YnrmMLg9zyfPIQJX+/fxY2ZitNya00JbfSlNxKU3IrTcmtNCW30pTcylDSLVOsZ4va8K6MZvHOPrPMtdzaSLpZbpk+mYhwyR9QXYlNCZdIEy6RJlwiTbhEmnCJNOESacIlfkc4pjZWS6jcY/JZwBqaw6sVvNrDqzO8usOrH7yGwmshvFbDS4wwgdd2eO2F11F4nTyLyff/xoic8/81RmSLWjdlOsiOkHgzm/Cd5/n/Nt/BOiDtrCjaDTtnyx8Dr4nwioDXL/D6FV6L4bUSXqfhdR1eGfC6C68n8HoBrxJ4vT9H0w5qyNLvh7VRGlwyIw0umZMsh8xLlkNmYB0yB2ufeVj7zMDa92+wQrjSsa5wFk6Dev9s/NZoR98WvOQI/BY3ZxJ6OTCctx69NxpjI35k8K6eKtaHLR0q1g/hre2L8uuHLoNznG+pBkEfFtzjjjAuUBgTKPw5UGQvXuVoscwW/lovmzVkiqPIUrI4GFcHs/GSoB5HBKLcvwTykt8g1RBl5+HsS2B2XjIyJ8EiksWTS28j8MMd4cCT864k
*/