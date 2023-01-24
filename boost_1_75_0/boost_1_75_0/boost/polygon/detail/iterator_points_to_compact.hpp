/*
  Copyright 2008 Intel Corporation
 
  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_ITERATOR_POINTS_TO_COMPACT_HPP
#define BOOST_POLYGON_ITERATOR_POINTS_TO_COMPACT_HPP
namespace boost { namespace polygon{
template <typename iT, typename point_type>
class iterator_points_to_compact {
private:
  iT iter_, iterEnd_;
  orientation_2d orient_;
  mutable typename point_traits<point_type>::coordinate_type coord_;
public:
  typedef typename point_traits<point_type>::coordinate_type coordinate_type;
  typedef std::forward_iterator_tag iterator_category;
  typedef coordinate_type value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const coordinate_type* pointer; //immutable
  typedef const coordinate_type& reference; //immutable

  inline iterator_points_to_compact() : iter_(), iterEnd_(), orient_(), coord_() {}
  inline iterator_points_to_compact(iT iter, iT iterEnd) : 
    iter_(iter), iterEnd_(iterEnd), orient_(HORIZONTAL), coord_() {}
  inline iterator_points_to_compact(const iterator_points_to_compact& that) : 
    iter_(that.iter_), iterEnd_(that.iterEnd_), orient_(that.orient_), coord_(that.coord_) {}
  //use bitwise copy and assign provided by the compiler
  inline iterator_points_to_compact& operator++() {
    //iT tmp = iter_;
    ++iter_;
    //iT tmp2 = iter_;
    orient_.turn_90();
    //while(tmp2 != iterEnd_ && get(*tmp2, orient_) == get(*tmp, orient_)) {
    //  iter_ = tmp2;
    //  ++tmp2;
    //}
    return *this;
  }
  inline const iterator_points_to_compact operator++(int) {
    iT tmp(*this);
    ++(*this);
    return tmp;
  }
  inline bool operator==(const iterator_points_to_compact& that) const {
    return (iter_ == that.iter_);
  }
  inline bool operator!=(const iterator_points_to_compact& that) const {
    return (iter_ != that.iter_);
  }
  inline reference operator*() const { coord_ = get(*iter_, orient_); 
    return coord_;
  }
};
}
}
#endif


/* iterator_points_to_compact.hpp
9bG82j49K95q1cPwmKzQm1e2woZXZnd0h3iXn2wZYPR4ZOpWtcV+yPK8wsrKJeqxS5f03wkGLcLs40hb0usFh0qoOJJq9maAKsqHWj+4jUpsJzPa+S2+tJiTOaoJJzXBbMcfVT4mUW1mK8/JVO8rZu0WtbrMkcSMtJdOkxY+PMpM8FaIJVNOTgzW7tUPVoYYRtikMJ4MGJqyp+IzTp6cYg714oFqQAYxA1LbPRHkpDQ3t1hx4U8Bh5BAkMUXrKsH71tcDILZQrBsnMpuInHMfnua1qmdqTdQLE+/ERobvj19njf1a7YH7oZ6OpoHSe1DJG3Q9MurT4F4ExkA4g0gWnaCZxtGLj11i2rUFsmJU+MMCXVkoMKHOEO8n2Zv3kcHBQyTLlnr/NSOtgv9BSaFn7wGERUMg4dK4mfYDVd8GKQ4UOZ4TeK4KCnH1QtjCmdtV5GrXJdklfesu0sZ81gxtKnyXljbjA68tIvC/PGe16f7LEKTCoWdpGSBuCThPS8odwgP6j1Wb5DV1fjeLfwDTeSRe4yx5y62PQHw4bDF3Twy/oI+8qI/KWeQilH8AOf4lEwe2Gf5ZUJ5tnSmvRz++BxEYGW0cUYTYXuQ1dlVsqUkN9Ft2HdikP9NVJrL8+eigMV8cnmBtF2RNL9cQ/WWz/yDdtNzRyGo2h5NW6cK+ynoeyDMef7irJv36UXTM+0BTuuegufu4dRZ9X7J
*/