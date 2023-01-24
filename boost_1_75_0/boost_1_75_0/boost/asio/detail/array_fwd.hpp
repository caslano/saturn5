//
// detail/array_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ARRAY_FWD_HPP
#define BOOST_ASIO_DETAIL_ARRAY_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

namespace boost {

template<class T, std::size_t N>
class array;

} // namespace boost

// Standard library components can't be forward declared, so we'll have to
// include the array header. Fortunately, it's fairly lightweight and doesn't
// add significantly to the compile time.
#if defined(BOOST_ASIO_HAS_STD_ARRAY)
# include <array>
#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

#endif // BOOST_ASIO_DETAIL_ARRAY_FWD_HPP

/* array_fwd.hpp
Sjopyy/qpBKfUbL6iwa5jYGp8K3potWfdnT1Huw135iSE+DHeW0GKJD26ctEwehu16+OLLcaMW9hWpYx31TUD1pOwaa+unLrWVw1xI/RBfHopwT02Oz0+MlZlw4TFtP9tTg/dZExJh0QKkSrkQSm0tPjeL2dkcQUoydzljsQxs+RrsXD26DgDUQneDW7yAZvlaIPZ7GnHOILx/mMxFdHfXoppxp4YOCoVOqLIbc9pCxsmMqFi+ZXltrJ8s8CNB8mC4CKI9c9pM753Bvl7GfA1vgfaQZn/nhBKscfc3HeLNNsG0G0q3k75hrhpecw9HH6wWD8j9rHROyDXmV5HPs7Jum8N+JJr+bAOK/VZJtDMB+qJgkIhWZrsKfyGV1Bw2BpCMPMHpqTc3HEFWwtzugKDmh9ASj/DLsQlIHBziZ1BorUw3OY/xq7P+LiAJ5wzXDwpKiUY8TMlDVCPDn8gNrVqelsXf0dMFmQxvHfM9BqkZfxR7H/Qw7XArCrwVB3jbWDruesl/m6cAfQyL2uiXZSvhdWCN2NFJx2UvhKS8D7kB63rtocuKuCLCfA0k3l3X4s3OJwkqQtKodLxSwg8Grpd63Kq+Gohq0I80Vhgpq0suXoOR7jIN98z7FD7SNdnJOc+o559s2eE8gj6ekfJ/GzUUuNDZiizEmaX8bUEuGwYDHH2RKEp5GyB6NyXPYDrBcQ2hzkxVdUoN6gjT+B
*/