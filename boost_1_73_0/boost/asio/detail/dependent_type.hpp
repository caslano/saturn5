//
// detail/dependent_type.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_DEPENDENT_TYPE_HPP
#define BOOST_ASIO_DETAIL_DEPENDENT_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename DependsOn, typename T>
struct dependent_type
{
  typedef T type;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_DEPENDENT_TYPE_HPP

/* dependent_type.hpp
5ubXVXrFNBtQ70WXMWM8y43nFOM5zXhO51M/8a5hRZVkLpxPPddBZF/+a/gmuC1yP9bXshsOmTmSF26YEK6dL0Qg5VgBnoeJDsLCIarXVfoX95yiIZcJSCl+q2lO+wIMaqn90beyoi8fPPqW9kJwr+0CIOie8oJYOJu+YRoE/r6CmsA8l+ZdCDb42tdkp5rC8Vea5x82KdjpKH224e/9pJEIKDSHNr1tFj4KSvvczUxwpMvq
*/