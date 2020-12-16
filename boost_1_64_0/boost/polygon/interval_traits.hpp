// Boost.Polygon library interval_traits.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_INTERVAL_TRAITS_HPP
#define BOOST_POLYGON_INTERVAL_TRAITS_HPP

#include "isotropy.hpp"

namespace boost {
namespace polygon {

template <typename Interval>
struct interval_traits {
  typedef Interval interval_type;
  typedef typename interval_type::coordinate_type coordinate_type;

  static coordinate_type get(const interval_type& interval, direction_1d dir) {
    return interval.get(dir);
  }
};

template <typename Interval>
struct interval_mutable_traits {
  typedef Interval interval_type;
  typedef typename interval_type::coordinate_type coordinate_type;

  static void set(
      interval_type& interval, direction_1d dir, coordinate_type value) {
    interval.set(dir, value);
  }

  static interval_type construct(coordinate_type low, coordinate_type high) {
    return interval_type(low, high);
  }
};
}  // polygon
}  // boost

#endif  // BOOST_POLICY_INTERVAL_TRAITS_HPP

/* interval_traits.hpp
rOSlX3c2cbrWS1DZhFKMizGYrJT1FduycjHJIcZjSb1rZ69Zt6WK2jIrla4pD8PkeoPjcuSxDNmUawgzOrZJcy1RliNV9sm3dJarraVdSFz9hbJvm4esAx7gtVkuOXd3fb/2q/N3z6l1Ok/yviTr/wIpxZeUY5s3J4ouXZfQ1pe27Rt9JW6L5HOI9Dj1lvWGbT5pUeYA04RCjEoqxLVA7bK66++z1XW2sKr5XQIBSntX8ke9dSTjUh/m63Pu2zVxfO3G1W5TgdXMBfxclvUsKZV5ZG23X1ZjgOz6C4xJWt7Ffb39fl29bmtfF/rLoS7DRVmGSbIMqbIMOW86LIPsq1y/blWYZbBcy1KGGWSgtpwp1e1i90lbC9rhUE7ZkUW4vD+1b1MRfGdydX9agoUNT42xaecBNaS/otRbKGmSsi07KY/5cOh63WmP0e4YyXeZheZ4b9sGvNB87T5arc+TSruWCbX1eU/Kv1nKv4GUoWy7Ox3KLxup68dU+/qsSEpOcd4u5TzetB22plx3SM0YlmYqi1uB+9XcmhIfWNpGJ9ITyvm3ZlmMGSwKCxJnnOJyu5B7iNrfGyyHbf1LGF+b+k+Sd5D5SNtJNirhMc33kXx2ScwQD9v9c2Ytx2WYpuy7dlmWofDll/sRf2r5Y+3K31vO20/Kj5lrcmz7GuMZJ9Ox/Lx5PDo8PYF2FZ6QEGG6XeXK/Qf9ZdKuIw+7ZfTSWUYfu2Wsbr+MDPOTYVEZEufUGj/bNCtf9mTTlev6zakDy1Dzy+xlu9PEv5Zj0RzWbx4zflpZt7tt27Xmvaa2MZhrS0wceb/LGZxBvvl71DrlRSNx0VNsflq6Epe/lOfefeZzoiSD0/219roCy8RHU9dX1d8Ijud9vprfAlJA2QNZ79Gd5m9cTAtPlHZVzFwet7Wettc9O9aROB2yn+ol98+y9ksd6D4AUfB+Vtt2N9XRf2divuRxv4csXLknb3P9p67jtZExyu9F8/v5M0zX07lg6cp8LeutFV/CUXtvIMIu33l1Ha+LhJBvgOSr3n97gHw1+agdPqpKPlVIn/KXIG0+XIVhEV3O55Sn7fLxXV2+W+hTwlls3cLHgtWPxes8lqp+TFbnsWD1Y/c6j32rHzvWeUxc/di9zmMA68dwdR7rVz8mrvNYwvoxgJ3HoNWPDew8trF+rFznMZh93JXhB0+EfLc5odrV35dm9zxb982b3F8zDc/5alTt58NeLTO37NFi3j+/std5DGb9WLnOYyHrx9B1FsPYeUziCV7K8B3zQ/afGemXfvXF5VmlveescB6TWI2NtbiYGqvtql3fLD/pm1Ubq2IdtEwXJtOV15nulsRE+gnd8WdUYwzeJ78fZLp8rIr/1EyXc5/pqkk5q0s5a0g580gXZbrlxczTVZHfnm4SG8UHD2Ad/Ds2wYM4DN/HqXgEn8cPcR0ewyN4HC/gCfwSP8Ff8CTexVOoZP4plsUz2AA/w654FsfgORyHn2MMXsIU/BJn4GWci1dkuXyKWZ4jol3Jcvnxb3d5hm+GxJSZiV44C6vhbFnOp7AtzsM+uAAH4TMYiwsxERfjXMzCBbgMX8LluB5X4F5cifvwOfwQV2EePo8ncDV+jWvwFq7F0pR1HXrhi+iNf8Nq+DL64Xqsg69gQ9yMbfBV7IZbcChuxWB8TY0lI88W4QHSVbtYMieLSWxGrIxnsRqew7Z4Hjvg5zgOv8ApeBGX4SVcj19iDn6FO/AK7sKvcS9+o8YElGeJMELKo40J+Iu0+1/RHe9iHbyHLfE3KdfvGIhuEhuoGA7FEhiGpVCNcbnCGsPkql1fdubJ8vMdO2Ab7IJtsSe2Q1O5mUGYzCdX2lk=
*/