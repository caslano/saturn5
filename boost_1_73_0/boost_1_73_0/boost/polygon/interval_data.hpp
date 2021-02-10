// Boost.Polygon library interval_data.hpp header file

// Copyright (c) Intel Corporation 2008.
// Copyright (c) 2008-2012 Simonson Lucanus.
// Copyright (c) 2012-2012 Andrii Sydorchuk.

// See http://www.boost.org for updates, documentation, and revision history.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_POLYGON_INTERVAL_DATA_HPP
#define BOOST_POLYGON_INTERVAL_DATA_HPP

#include "isotropy.hpp"
#include "interval_concept.hpp"

namespace boost {
namespace polygon {

template <typename T>
class interval_data {
 public:
  typedef T coordinate_type;

  interval_data()
#ifndef BOOST_POLYGON_MSVC
    : coords_()
#endif
  {}

  interval_data(coordinate_type low, coordinate_type high) {
    coords_[LOW] = low;
    coords_[HIGH] = high;
  }

  interval_data(const interval_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
  }

  interval_data& operator=(const interval_data& that) {
    coords_[0] = that.coords_[0];
    coords_[1] = that.coords_[1];
    return *this;
  }

  template <typename IntervalType>
  interval_data& operator=(const IntervalType& that) {
    assign(*this, that);
    return *this;
  }

  coordinate_type get(direction_1d dir) const {
    return coords_[dir.to_int()];
  }

  void set(direction_1d dir, coordinate_type value) {
    coords_[dir.to_int()] = value;
  }

  coordinate_type low() const {
    return coords_[0];
  }

  interval_data& low(coordinate_type value) {
    coords_[LOW] = value;
    return *this;
  }

  coordinate_type high() const {
    return coords_[1];
  }

  interval_data& high(coordinate_type value) {
    coords_[HIGH] = value;
    return *this;
  }

  bool operator==(const interval_data& that) const {
    return low() == that.low() && high() == that.high();
  }

  bool operator!=(const interval_data& that) const {
    return low() != that.low() || high() != that.high();
  }

  bool operator<(const interval_data& that) const {
    if (coords_[0] != that.coords_[0]) {
      return coords_[0] < that.coords_[0];
    }
    return coords_[1] < that.coords_[1];
  }

  bool operator<=(const interval_data& that) const {
    return !(that < *this);
  }

  bool operator>(const interval_data& that) const {
    return that < *this;
  }

  bool operator>=(const interval_data& that) const {
    return !((*this) < that);
  }

 private:
  coordinate_type coords_[2];
};

template <typename CType>
struct geometry_concept< interval_data<CType> > {
  typedef interval_concept type;
};
}  // polygon
}  // boost

#endif  // BOOST_POLYGON_INTERVAL_DATA_HPP

/* interval_data.hpp
lyvbcM/aODs571Fm9je6F+s67+WKrxronnbOdNgO/IlxrmMgk9ZZhNXS/8nr0qpoemqVQjQhE3F15m8an1rxLcDlYu/T+1T5D1BLAwQKAAAACAAtZ0pS9Ara998EAABpIAAAIQAJAGN1cmwtbWFzdGVyL3Rlc3RzL3VuaXQvdW5pdDEzMDQuY1VUBQABtkgkYO1Za0/bSBT9nl9x45XaBHnjwLLVdimrjSjdotIEkaAKlcpy7Jt4tvaM5Rnz0NL/vnfGdl7kwUaUpSJGYHvmvu85M5PgbD3cVYEtWHm55teli+5G4yQVf6Ov5ku77i3kP6R1QfdVThwYq9y6dVitcgs1o+IWXt7oZ9dd5ehCx6b/OFrzwtWPNEJqWvNAJDcpG4YKagd12H79+jf4GXaaO00b3nqcYQRdhbyP6dCGN4EZ+TP0rq8bEv+wARV4UaMw1QuZBCkG6spLEeg5Yj5yiQF4EgKUfsr69MI4qBBhwCKEg87J+VH7LxuuQuaH2siNyECGIosCCL1LhBR9ZJe5jcRLFYgBqZPxgElFBjPFBG+QbwSFaSy1De3ei6QA79JjkdcnR56CUKlE/u44fpZGFL0TCF86fpl+I1TxKJNzCiL2bkAkCpSATKINWtKGWARsoO9UEBpMsn7EZGiP
*/