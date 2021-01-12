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
bbW8a3lbmF3LVTXd7zatJ5s0f7S8rpyu11FPz0vzJbK11t/d9jOHrp/2qZa/6+rp+v1wu/0Tu16p3lqv9+j18xsUrvn0tdexdpmm+2n7GaDpUmOf2HKUnfpqXnq8hdrPFNBy2quFti+ndHtl71V5M+2n2mm+JdipW1re59r1Xk218XU0fp+Wpwf3xJ6/bjeuldj9XLfLhz+3n7cS6K3ty8pLWu7eIBNq/oFa33dovrXRfvCu
*/