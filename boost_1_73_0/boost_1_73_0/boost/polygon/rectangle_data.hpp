/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_RECTANGLE_DATA_HPP
#define BOOST_POLYGON_RECTANGLE_DATA_HPP

#include "isotropy.hpp"
//interval
#include "interval_data.hpp"

namespace boost { namespace polygon{

template <typename T>
class rectangle_data {
public:
  typedef T coordinate_type;
  typedef interval_data<T> interval_type;
  inline rectangle_data():ranges_() {}
  inline rectangle_data(T xl, T yl, T xh, T yh):ranges_() {
    if(xl > xh) std::swap(xl, xh);
    if(yl > yh) std::swap(yl, yh);
    ranges_[HORIZONTAL] = interval_data<T>(xl, xh);
    ranges_[VERTICAL] = interval_data<T>(yl, yh);
  }
  template <typename interval_type_1, typename interval_type_2>
  inline rectangle_data(const interval_type_1& hrange,
                        const interval_type_2& vrange):ranges_() {
    set(HORIZONTAL, hrange); set(VERTICAL, vrange); }

  inline rectangle_data(const rectangle_data& that):ranges_() { (*this) = that; }
  inline rectangle_data& operator=(const rectangle_data& that) {
    ranges_[0] = that.ranges_[0]; ranges_[1] = that.ranges_[1]; return *this;
  }
  template <typename T2>
  inline rectangle_data& operator=(const T2& rvalue);

  template <typename T2>
  inline bool operator==(const T2& rvalue) const;
  template <typename T2>
  inline bool operator!=(const T2& rvalue) const { return !((*this) == rvalue); }

  inline interval_data<coordinate_type> get(orientation_2d orient) const {
    return ranges_[orient.to_int()]; }
  inline coordinate_type get(direction_2d dir) const {
    return ranges_[orientation_2d(dir).to_int()].get(direction_1d(dir));
  }
  inline void set(direction_2d dir, coordinate_type value) {
    return ranges_[orientation_2d(dir).to_int()].set(direction_1d(dir), value);
  }
  template <typename interval_type_1>
  inline void set(orientation_2d orient, const interval_type_1& interval);
private:
  interval_data<coordinate_type> ranges_[2];
};


}
}
#endif

/* rectangle_data.hpp
Z9cw+QuG42tydnY6/oRHL5BMAb8vFNdIrkBkRSp4VHP+uMt3fhJ5mJYRhw4dXpjw8F8v6TgNeSQNfreEGc8iPi8XVqwNMyKE0dXleShRW+bCBJqbsujeSRH1nO8O4NNmMNEW9DmYnPWdp7UhgWojIzc2FUKV2BeqGID8hHicBsKEKdgTeVGa/pZQlsZKn/qOczU+nc0+T2fBdDa8nDmILHMtFrmtFQOCbGkS48OsYQAHG2dt5oIJpb/eIoRiAPgOHZ/5cz/0Pd+z30XHtbJFB57cFSYTEdZBjmVuBr8R6j2hSPq+CfMTfKIl6TMprR8am4BDUh5a1eG2YiV/rvGsYltao5+5eQFOzEdWc7Qj5hagErVghmvjU1chwGaxC0F+crlcA2neiqXKD97jOkttSQNaHUkzmbuUJ9gocmlo9cAeVtAtaTOAo19PkGiAW/55ztSAIFUcuxRtRnSMw8kyYcaaVLPm9p4lnwQthLfis5OGZr3VrcfGe0nh7zjqXcdfRf1MXolakoaACg8glqorbEmBgGPQ4j8u466to57fXH09uO0hZn+/V9fWuozReoRNKYh4VYX4eqhNxK1na7/XtxZsLpUJyjzFdtklwzcDGF+dn2NMVdvBeqf1m07PxoZFH3exwMOsILgLa69V
*/