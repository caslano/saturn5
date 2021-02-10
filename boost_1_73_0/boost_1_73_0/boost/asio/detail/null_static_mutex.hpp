//
// detail/null_static_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_STATIC_MUTEX_HPP
#define BOOST_ASIO_DETAIL_NULL_STATIC_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)

#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct null_static_mutex
{
  typedef boost::asio::detail::scoped_lock<null_static_mutex> scoped_lock;

  // Initialise the mutex.
  void init()
  {
  }

  // Lock the mutex.
  void lock()
  {
  }

  // Unlock the mutex.
  void unlock()
  {
  }

  int unused_;
};

#define BOOST_ASIO_NULL_STATIC_MUTEX_INIT { 0 }

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)

#endif // BOOST_ASIO_DETAIL_NULL_STATIC_MUTEX_HPP

/* null_static_mutex.hpp
ZkNAFMsQ392NL1as0wiYkEFckJ8Zqc2o6MJw7gGzLHVfVc7B2mOHN482gZWAU8cQIxF/i/nse+4bF4xwhKMoPWNPpG2rFut4zGRYe/ho8KxGtt9crXcAZvjm8uJ0A1ahSptuIpTUN/SCbJsNkSjp2QoMR17YRdxsh/kPHYwHmzqCbBUhbmWDYWrzfjH6okSpae4FIZP6k4Lxa5lJ3pdrFg6RimEFAZpa3B+ynHpAtqemRdH9kay6PRk+kFHfhJMcLJ9xLmhzoaGmOMPg7WGUSUS5t9aDFThQ+V2CnNTJpKO6pkhIDNRsOQnULv9VGTP8ej7zhj9a9ILgH7WR+Fl4gmJdmMGcmhl3jYwGmqnnKzQbyWwEmnJWBNZJkUFtsYgZU8I81QC3jHQpTnMzTcmQHNYf0JmxHNyU5+E5CWfqS10jGtwINSlSLZBFODmkRoSqvPN9DzP45sCEQSUjrM/3biE6KyMar2bcrIkvC/U6MvVZM9EmSwBSetOJYRKBdo/+UjUKMNyQdgcfyOlDSDjhjbQSFafeiEjclsxSVl6wQtfAgcy6BttpMrEIHJie7BvkAxcZRUIL7sGZSFNnqLqnjQL+7fqTx69k5DgEtshF2ql1HwEMuilCAKBxCnBggVJD4zAzx1yg9cto2zY2
*/