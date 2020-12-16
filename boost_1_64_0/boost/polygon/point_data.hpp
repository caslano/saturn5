// Boost.Polygon library point_data.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_POINT_DATA_HPP
#define BOOST_POLYGON_POINT_DATA_HPP

#include "isotropy.hpp"
#include "point_concept.hpp"

namespace boost {
namespace polygon {

template <typename T>
class point_data {
 public:
  typedef T coordinate_type;

  point_data()
#ifndef BOOST_POLYGON_MSVC
    : coords_()
#endif
  {}

  point_data(coordinate_type x, coordinate_type y) {
    coords_[HORIZONTAL] = x;
    coords_[VERTICAL] = y;
  }

  explicit point_data(const point_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
  }

  point_data& operator=(const point_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
    return *this;
  }

#if defined(__GNUC__) && __GNUC__ < 6
  // "explicit" to work around a bug in GCC < 6: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=63356
  template <typename PointType>
  explicit point_data(const PointType& that) {
    *this = that;
  }
#else // __GNUC__ < 6
  template <typename PointType>
  point_data(const PointType& that) {
    *this = that;
  }
#endif // __GNUC__ < 6

  template <typename PointType>
  point_data& operator=(const PointType& that) {
    assign(*this, that);
    return *this;
  }

  // TODO(asydorchuk): Deprecated.
  template <typename CT>
  point_data(const point_data<CT>& that) {
    coords_[HORIZONTAL] = (coordinate_type)that.x();
    coords_[VERTICAL] = (coordinate_type)that.y();
  }

  coordinate_type get(orientation_2d orient) const {
    return coords_[orient.to_int()];
  }

  void set(orientation_2d orient, coordinate_type value) {
    coords_[orient.to_int()] = value;
  }

  coordinate_type x() const {
    return coords_[HORIZONTAL];
  }

  point_data& x(coordinate_type value) {
    coords_[HORIZONTAL] = value;
    return *this;
  }

  coordinate_type y() const {
    return coords_[VERTICAL];
  }

  point_data& y(coordinate_type value) {
    coords_[VERTICAL] = value;
    return *this;
  }

  bool operator==(const point_data& that) const {
    return (coords_[0] == that.coords_[0]) &&
      (coords_[1] == that.coords_[1]);
  }

  bool operator!=(const point_data& that) const {
    return !(*this == that);
  }

  bool operator<(const point_data& that) const {
    return (coords_[0] < that.coords_[0]) ||
      ((coords_[0] == that.coords_[0]) &&
       (coords_[1] < that.coords_[1]));
  }

  bool operator<=(const point_data& that) const {
    return !(that < *this);
  }

  bool operator>(const point_data& that) const {
    return that < *this;
  }

  bool operator>=(const point_data& that) const {
    return !(*this < that);
  }

 private:
  coordinate_type coords_[2];
};

template <typename CType>
struct geometry_concept< point_data<CType> > {
  typedef point_concept type;
};
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_POINT_DATA_HPP

/* point_data.hpp
XEo4ouG9hg/vN2RwaLfhg1vQJ2JiqJH7FKY4fR95uKn9oPvKtQFtXIct/MjM5mIO/3OYUZyx4Oe2vSnLEspyvalSloRk+l8wnW0Mr45yeO8s/Zk74CqmyTHna2gZF6rJ25xndca7X1+Dt+Y59mX+zlv7TDdS8hS1bwqSiOYWY4y19i/w97CNB1WO70yi9k9YTTnD09zU/gnKPOIMzEv6IKfz3ZiYkmAfz+SoLHMtqesapLW+ygUUx2WW+i6wri3L+YKv43LGJaHtctqsg+XSccEo/T5S8EXmE2AuT1xLg+M6cC9WcFn8JW9LWfZ5muvcm+/+1E8wfycyQlQGXevj6JbjLfX+LMMj41LoIGMKUmaqz54yflqcwdRxvCbDvGRYCs/3xxnoMaZ09omNo+eYeR3MMf9d5mXuJ3LrN5lPakpoOiGh6B9gEzuM8qvxDQwyfWJ4mpGyxEdNMc/XaJkvGx0Zm6ZdzrBnpD0o+bS2Xb7Y5DSjkpVpvsGWZYlKS4tLTmIW5ml+5+Pnps7XvPBu5r+V1FlW+3blVcoxNtnfKFPQIst6fPB2ZWrrqF2XyelGm/z3S/5DJf8hpJeZLnORtU+WLHJiVGJkyhS3gvchlvz9aKOGNKPaPzGd7ykMoC2rbXufab1Gavtise4yGMW2ngwSl6+BlLMeaSPlzHcsZ7LS88aVvjEVpZzrmY8hioJq64opk9NkXyPLIutW7QeXLtultpz3pJztpJxtSJuU7fJZh3Km/RXlTJFy2rezTIn5Fyvliia9qqxnnXIZU5PoNu96uSK8lfXqWC7Wq6kMjaQMt6QMFaUMHqS9VdAcS5QDY8HxdCx57ma60GBlCnPfsCrybP/+KmqfHzJx3odEv6+I8z5C+n1InPfl0O+r47wvjX7fG2d9SwrfJ0S/74ezvknO+640q6wML5/nPi+67qXOP+5rvbNyYr9Y531X9Pv2OO/Do99HyHmfK/2+Us77OOn3iXLeF0i/T1fh+4w566MVaarPi4caDjo9/2T623NevXsg/0pE4ftWOetLpj6rOsf6bG623b2KcXKvIqO4nMPJuZ0y3kBlH4du8oxDOfwJK+PPWB1vY138BQPxLnbGe9gDf8Oh+DuOQjLgHiGgAYtjNJbAJHwIJ+HDuARL40osh+9geTyPFfASVsTr6IW3sbLco/LGKlgVh2B1HIs1MBZr4TNYG7OwLubgo7gT6+Pb2BBPYCP8Cpvgz9gMyyj3T7EatsAG2Ao7YGvsh21wOLbDSdgep2JHXICd8RXsgluxO36APfBj7InfYS/Mx774O/bD0rS3/uiLA7AxDsRAHIQdcDD2waEYhMNwDA7HSRiMU3EEPo8j8QUMwU04Dg/heDyM4XgKI/EbjMKfMBr/hTFYivYTi2UwHqtjAjbBRAzEJOyAySjtVM6nWTc67ZQ2I+/RlvNcOf/NtnuP9hRpp0uxMS7DlrgCu+Nz2A9XSbtcjePwBYzHtfgErsPl+CJuxr/h33E9/gM34Ke4EfPxVfSkDK9hS8zB4fgmRuIOTMOdOAN34zO4FzfhPtyB+/Ec/h2/wVy8g+9iZZb1ELbE93EIfohheBRT8GNt34JF0ofEaX3Ksxoy3lAZT/usxmX+XAKv4CP4NVbEb7Aqfot18RrWx++wK17H/vg9DsEbkl9fUr7k10Dy0z47GSP5xaI7xqEXTsCaGI/1MAGlj5OcX7GNkbLt+jhNlPmlSvnTsAmmYxucpK0HmU+sTj2ckvmcxmr4KfrjGWyEn2ELPIuP4zlpV+cxHC9gNH6uvTcs5y0VSSF292q95V5tFfRAHzxZ4v73affwt5Ok1m24Jj/X/t6s3JfVeY/dWMa33I+dxr8=
*/