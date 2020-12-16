// Boost.Polygon library point_traits.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_POINT_TRAITS_HPP
#define BOOST_POLYGON_POINT_TRAITS_HPP

#include "isotropy.hpp"

namespace boost {
namespace polygon {

template <typename PointType>
struct point_traits {
  typedef PointType point_type;
  typedef typename point_type::coordinate_type coordinate_type;

  static coordinate_type get(
      const point_type& point, orientation_2d orient) {
    return point.get(orient);
  }
};

template <typename PointType>
struct point_mutable_traits {
  typedef PointType point_type;
  typedef typename point_type::coordinate_type coordinate_type;

  static void set(
      point_type& point, orientation_2d orient, coordinate_type value) {
    point.set(orient, value);
  }

  static point_type construct(coordinate_type x, coordinate_type y) {
    return point_type(x, y);
  }
};
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_POINT_TRAITS_HPP

/* point_traits.hpp
szHHhffYWe+9yv3WB3iPnc091D/w/rocdpQO77Bz4f11rr67ztV31i2k/iz3NheSDrlwH7Ow76fLIa0qxPvptrYp7tI76rTvpstlGuXe48U2xV2+/2h771F731HuN2rvNdq/j+5PfBed43voCvcOuj/6/jnLu+fuKHXXlvtkpDBSJmk96QjpKql0O+6/tSu6X1b0KfoUfYo+RZ+iT9Gn6FP0Kfr8GZ+/8P5/q9DEtBjz3f8/dv9fua9/zIN5WOI8ynWsZCyH8Xidv+fNsNyracUL19JSwo2RsaHhzMH4YDFjtfH4tPFhJ8i91FtyP9yUBTe6tHGQS3lK/FPuvWyiwEqRb3uYv7ecaf7OODbv1guTnzkzZLmmynJlz9QsV7ISozApJipU7ianpURFurke+1eWz+l7v3YpfyeiYVQqwzR1kGZZPsrfaZa5/PWqmL+Hy/dH5fsF+T6Y79p78l4lrLF+S5DOk7Yo99hmW5dPydu0zlx4FsNumdT7qNq4kdo4ndwbjLQswzJTnvx2lXfTDZsjy6S5P3a1uPP7Rfr3zZzfR9K/T1L4+2P6952c3V/66++n/Vn3nfTvsxX+PpL+fSFn980KHxOvsPfHnN3XWlzZtH5Pf3687c2PHrn2QaNXa6/cN7/w96/078cW/r6iuc+v7ENl3xpi1+d3jNw3GI9eGIb+GI6NMQJHYySGoQFTMArTMR6zMAE3YBJuw2S8gKn4LabhbTTiI9L3vBpOxtqYgY/jFIzFaRiP0+W68VU32WfiDFkOX9nfmLZ/WY5K6I1eWAu9sR76YBusikFYDeOxOqZiLVyEfrgRa+Nr6I8f4qN4HBvjWWwiy9UU72Az/BWby/IFoA+2wl7YFgdgO4zEQIzBDjgJO+JU7CTLS53KPpR9q1wnr4BzZHm7ynX57lgNe2AT7ImtsDe2xz7YDfvhcOyPyTgQZ+AgfA4H4+s4BN/DofgZjsTzGIJ3Sji99q69Pq/2kcokLSflOPSXsu8rpddHyq5v1H/punzPP3BtXu+6fMafeG3+UCGuz2v6HWn6HLnW38jcz+ivv17vyrV6o3q9vvD9hO7fR8i1/kHa6/Z9/8Rr92H61+/ZQf9nr+Hf0lzHVw50/qSgwKJr9UWfos//y+cv/f2fEBfxZ/z+V94V8Jqvch4j7+tvJT9+08zP/B/3cFPfmxcm1wYak8qR6pPOVWT/3N/0G1N+NFveQun6+4EOeWieFZbvEZrf0WnK31PkuoF8j0ixfcb0YjHHuPXNqnDM6G95r57p9fn9gvr2GmZ+oavr79RLt3t/YZq8v1Cbf1Bxx/j1s5X3bOrkX9h3+s2U9wpq88sr7ri8cxkvXyc/85sMC5/f/d5jOLaE/vtePQaQ+3/ofa+WdrlHymL/jtEApSwP+I5RmTexS5y8k5N5/6feybmjpJN3clKGv+KdnN0tyy7P59eWfGuRPmAmmZIvXSJSwtPSJvOaShY+OZHXTkRzCS3ClefK9d/pYfMuI/Wa5HkpR5jsd8aSXqMScgao17bUd7XQ2SM1oRD7Hvv8jaTIRIPaR2AL+USn2F6zpI+PTfk6yrPl30h/mK/wdV/a30BN+WKTk9MsFxalfD0LUT61HwPfIxPosqJef5P9U+okZivvL5R9JOVU36GojJOSGpdsGeeM5fpknHk+++Udh+EJMaHhdvveSMkrX+ZDVSdPdriOK/2YZD6J4TRLaV/nZZxkeV/xRe044XJ9VJM/o9m+b0/qV/mdXgKjcBbrJW+IWr/m9wI+QLvT5rNV3hu9ogzrUVxCPllD1XzMzUvyCbpvPu7md7eMYUrN99LyvSJXqA+MNv3bf+DgwNZuMizaOizAMuwRdVg=
*/