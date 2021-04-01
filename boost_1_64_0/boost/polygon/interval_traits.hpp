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
Bsmr4kVb+TlA6JVxkfjmDdjPTtCwYllh774vGnm1sShkwM/Kyap9u85xha6i3DimSZvUMLEDOwFtJa1vVoJJ6JaBFMuVlQSeRxiyIZyI2rjzCS0Njqud3IyvPYJ042XurqvLIG3YN5/gELJNXF5RqxHO5bx5z3o5treziPXbZj0yzlzZWzcc38KnqNbXe6m1xsnD6JovjCkXMfwQNcJjkDY4L/H/fztq8UzVHMTfcNe6cNNGDliY3GCcp5hYMkqex2+dmyo/RMwNPw50LLeczYUTRvTlgCeIDma+2fWT+BsjfPa4akXTf6yNX5eboBBuN3XKOozLVe4yHP2CHS9Qptrgqs7h8PxI61C7GebsqMo/pyWimjEFbx6cunq8JzBFnH2ssmBbafvweqKz0TJAG4rcRkDYLlGsiRbXt63/Xi14TbhtS3v/F2amQXtnHRebmvoA69xDXCTsDrC+HTA0QeatRwA6IWNBuGbddEUCbVjoDU9it9xJX7q8+I3/SHY+nkVz47Xa07pb5rWT5M2KpbQEdqQRmNNzDNlJ3TNO4d2UQZIBEKmXOGevMg==
*/