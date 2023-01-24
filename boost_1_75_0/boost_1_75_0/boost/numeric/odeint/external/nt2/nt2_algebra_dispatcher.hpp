//==============================================================================
//         Copyright 2014          LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014          NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_ALGEBRA_DISPATCHER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_ALGEBRA_DISPATCHER_HPP_INCLUDED

#include <nt2/core/container/table/table.hpp>

#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>

namespace boost { namespace numeric { namespace odeint {
template<typename T, typename S>
struct algebra_dispatcher<nt2::container::table<T,S> >
{
  typedef vector_space_algebra algebra_type;
};
} } }

#endif

/* nt2_algebra_dispatcher.hpp
KuZq8MH6rD+69zK3NyOe+Z3ot8fjHbti+fF4McWO/2PFlHJxC3u+FHLqCZ4UvShg8bCaMy6dEUEoi+L5avBOm8HmlkkVQLAuHNxKr1araZ70xkwFv69bBJcnIu2XgJKjEuSfH61HRxjrQZDg1n0Day53LzskFyrUeyTfSbCw56TKjDjn8yG5vYhJWtKefX234GwifwbY0i5pjbWkOgJXQmQ8klGjmHcUYYOsYw9NrTlMjb2HRslrRQI3z+NU6z1OsZRIp1yolBe311R9aw3pW5FxTqCsC6si2B5ZpugpxGIQEQq0ltDt6cQT6PJYOSxc/wKX4LBcyDSDmARwnIHqtmg1XudPGw1kR28RvfYa09O0HyxioV8+wXfkYLyuJjEnGqb4KK8YLm+jNcGLCdVG2mbFNgs+K+Xt3scRjsdW4gH426MSC+rfSjHH48vk7oooMe37Wb7AM7iB314cRd+eHRX87Y/PNv+tLprGppSl7DK9apPK7SnHbNIe69Kah5xTp1uXnh4x9SGXTToo1aTssnqHGextq0yvWpeeuf+hqemeiAR7292QT4RUh2zZMy4h2pUpumNMD4I40qvmVsU0pKyVQXAmDslpFSY4ewyZiaCLcWPdJVibxc9JELcYBAPxWNH0WvnsDjbJeBYYrNVdZbB5iCf7IyHsODjoQmWbV7yYVrOgN+IKpdskXP1EqGWbSn9oPbuNvW05fPvf
*/