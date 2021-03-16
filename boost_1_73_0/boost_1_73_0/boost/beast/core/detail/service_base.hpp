//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_SERVICE_BASE_HPP
#define BOOST_BEAST_DETAIL_SERVICE_BASE_HPP

#include <boost/asio/execution_context.hpp>

namespace boost {
namespace beast {
namespace detail {

template<class T>
struct service_base : net::execution_context::service
{
    static net::execution_context::id const id;

    explicit
    service_base(net::execution_context& ctx)
        : net::execution_context::service(ctx)
    {
    }
};

template<class T>
net::execution_context::id const service_base<T>::id;

} // detail
} // beast
} // boost

#endif

/* service_base.hpp
fXCHQlZXMu5WiR5+DerTaoUcrzHeP5ZC3NpahVxuZFwfiR6+92rZbIX0U7s/d5ToPQfrdxUwg+cz7iqJ3kLIX8U9CjndxLgYiR727t28QCEPLzHOH77tqmezQn5tYVwXiV4Y6O1fqpCDDzFOdvx8GpZL0SMK8TzBuESJXhac2N6wSiHVzzNumkTvUfj5zs0KufKi8fIbCstv5haFvNKqlyOYXjtwy7Yq5G/bGNdDojcJtpe9rysk+R3GDZfoXYI=
*/