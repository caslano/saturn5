// Boost.Polygon library segment_traits.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_SEGMENT_TRAITS_HPP
#define BOOST_POLYGON_SEGMENT_TRAITS_HPP

#include "isotropy.hpp"

namespace boost {
namespace polygon {

template <typename Segment>
struct segment_traits {
  typedef Segment segment_type;
  typedef typename segment_type::point_type point_type;
  typedef typename segment_type::coordinate_type coordinate_type;

  static point_type get(
      const segment_type& segment, direction_1d dir) {
    return segment.get(dir);
  }
};

template <typename Segment>
struct segment_mutable_traits {
  typedef Segment segment_type;
  typedef typename segment_type::point_type point_type;
  typedef typename segment_type::coordinate_type coordinate_type;

  static void set(
      segment_type& segment, direction_1d dir, const point_type& point) {
    segment.set(dir, point);
  }

  static segment_type construct(const point_type& low, const point_type& high) {
    return segment_type(low, high);
  }
};
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_SEGMENT_TRAITS_HPP

/* segment_traits.hpp
pLeqVClyEof4GmIUO4Xqet/9xiYFWqDJrdaIOhn8/814xg91Wj+vGdCCyubrr48Ne62Y5fxvGsrjo33/GTYfVN1jX+XEgZ3k2W9CteQZGlril14+qWffr3J0r2JTfxylvPfVI1pQppQjvnzK2TyR0Bg1odPvX8Iv0G132xZ8JhmjKbiSZgHN5xZ8irTl94Ss17agv1lAJZDULlFewgQIHssVySngc8pCmgkaAREQURHmLMAXloFMKMQspTCazu7Gk68WrBIWJgryxAsQCS/SCBLySCGnIWWPG8aS5BJ4jHKER0xIBBaS8cxG3xQkzRdCMZR7kgoO5JGwlAToiEhIpFyKgeOERZ5i9E7EQ+GEL9O3E7nYzuQOg1iQJ+BLCZJDIagFaqQFCx6xWPWYEDQuiyBlIrF20aCrLHJ4DoKmqWKhjlGxCZuCW6bHUsNgiREzqTrBM6FcrRK+eDUQ86gocZFn6AjzgIMijmm2oMgimuvBeuYvLsqc6gSfLM0u3gh4hsGAOXRh7JoQEMGEBd/H3p/TWw++D29uhhPvDqZfYDi5U7Dr8eQzlp6hsxzoeplTgc5zYItlymhU+vx5zTE+sCxMi4iCqYoXJjR8sBPT2LMnXMgXOziYr7zMY8oCnGwOSDGEJJKFMLq9+RZy
*/