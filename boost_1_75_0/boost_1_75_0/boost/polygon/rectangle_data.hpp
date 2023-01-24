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
WEA++no989IGpQZv6Q0/StP755r5yGqEUNPZrAYgOv5FrWIetyVuJr+OCFESVuYmj5PhmkSOrR79nfPwUHz+2GVHeKDzU5I2va9WPLvEALOy7Q9WCxypqLqpYULKTI9CPsudjVCy4dWc5P0K5A5AOoD8yR/kZmL8x8SjiIMT23546C7tj7lFEQyMRui2e3sbgHuM1YFv1PD4fRWB5MKz8fz8vOzCenX3tIF5oh+KlfH5bRcF6W3q8FkbMaRB5D56Unat5DMrOLxpoRlm/OYk8hizHdfnnQdtjeMfnZ421hkzvh2hhCxMHVZQMHNXVSvs7BWAupUYQFOlIgJ2Z2tCmFPf+4tDq7oX3Zz65icQmT+5EZcNX6vf+WM1EzVjNVM1oyyhrWE4MAmjeSFxdKuZkNRQ2Ly8waVZlfELagvy++oXJJhLtYTugZT9gaQGvAN0R7qQzEXff4n94vZFQLfpn1cX3hT5gX+YuZFQv9LiIt9x7yQu8Hz1HsjVPAuJCP9qaoL6Hjsa2Xzi0pUJEHRXp/ZgyhRIeKHIFJDx+mhrW+3hzRbqD1T+P+zcGCovWhOhGP0stFjn91NIxS9mfZ3eNgaxc6OMIUNfADIlMMRe+k/Qrw5EZCwMzvOxOC4pWGnqKehoDu7crdUT839a9mAs1MXQBDd60vP9+LOYG694KMZjRz6bYTsp/jgsDZzJ+W73sJMkbrJaHMhob7/Q
*/