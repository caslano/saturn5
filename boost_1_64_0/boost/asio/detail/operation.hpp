//
// detail/operation.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_OPERATION_HPP
#define BOOST_ASIO_DETAIL_OPERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_operation.hpp>
#else
# include <boost/asio/detail/scheduler_operation.hpp>
#endif

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_IOCP)
typedef win_iocp_operation operation;
#else
typedef scheduler_operation operation;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_OPERATION_HPP

/* operation.hpp
fwsYpI8dICB7tPjmT2BgKTVBVW4mklJqDZIKiHTtoIwo6zb6wMBpvkUIvAT5GO2fxtni29ceeekAsLfZoUjWWhHhShJZazTwP9RAZBeUfwYMRJlAwxJMiQzisLn+mISJdGxqmMDoP2UR1CkqD4hjwlPMKW6xMcWIP4NaUZyg68lDwU+t0qQavRo+u8nR8Qj6E+Fb3rhqOs2rlDK/pK2nkqYurWyk2cDx6NIG5oX7tRcPFHwkMpH5F26z0E4eE77q8uHyVa7nJmxTNCvdmVjvugJHeAXF7xwvyyzlnRhyBnUmW8SKCPN78gLWiVz+IHoaunbxbxxSARKSLdOUXKVhJmfQoEdSRwh9rBXo+v3w3A4nvu0w/wBZviKOWvXztVR18F+9kl3YxooYTG0d8jZBUK9wwMBS5eQ5qnm0/oA5JDhowvGMiQcsc3Nlt/shk0W0v7zsDOtM31JZaDWitx7HZ41rGe8rII9NSiM/vv54SxFfh8M65W6p2rQARruFgIunM+jfa3FidYHnAhP2m1OY97ZNQxtd+aW6y8xEqhxWSAFQtQ+5+v9fs3M3CQ==
*/