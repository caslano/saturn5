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
pZIOeLulJdAm2c3nYT89HE4mVizCTdSoylO04vuSW0JzkS2Q2ODYj9j+uu9rOdyC603VsXNVcnd//DDNqeW+/Ffqral9tE4LDJlNws5T8/pp3ImgLqcIXqxNId8qj7Z5Y9vhPVZD7QDtrgP5Vv1PSFXPI17TWfcN1mPh35jdNqSC8/FoNhtOZ2Q6G0xmgW/IrWeBAytWehHDRjCP3jK23wzHC+z/+OInvEoIa+AG7xWqxHtl7HuSygVe91xzKt+f/lzCpvTeICLLi5C6y2nH2eh04ckB5qmZik3S/axfzXw9DulcaUtKmeEVJnRCB62XLu/uKJJt0eBFE+OJR2rcqdVrV1xJWlebqyPUC6xEW0i8RqLkvh863o0bkWWQKrzqOs80T7jmkvHKPfDIRXNG+VGMMXFjOGrLNWopPIP9CNYH+4Z73hx6JfBKrr0zWOaqYrLuFvI7xgPBRd1TlOoG5hyvnXiPmS/uHw0N4dVCryaXP2pXKuX0LPgHUEsDBAoAAAAIAC1nSlJDvqFwUgsAAIk6AAAhAAkAY3VybC1tYXN0ZXIvdGVzdHMvdW5pdC91bml0MTMwNy5jVVQFAAG2SCRgxZt9e9q2FsD/51Oo3toB5S3t7pombRlNmzVbmvQWsq2NGRNGxFqNzWOL
*/