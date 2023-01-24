// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_INTERVAL_VIEW_HPP
#define BOOST_HISTOGRAM_AXIS_INTERVAL_VIEW_HPP

#include <boost/histogram/fwd.hpp>

namespace boost {
namespace histogram {
namespace axis {

/**
  Lightweight bin view.

  Represents the current bin interval.
*/
template <class Axis>
class interval_view {
public:
  interval_view(const Axis& axis, index_type idx) : axis_(axis), idx_(idx) {}
  // avoid viewing a temporary that goes out of scope
  interval_view(Axis&& axis, index_type idx) = delete;

  /// Return lower edge of bin.
  decltype(auto) lower() const noexcept { return axis_.value(idx_); }
  /// Return upper edge of bin.
  decltype(auto) upper() const noexcept { return axis_.value(idx_ + 1); }
  /// Return center of bin.
  decltype(auto) center() const noexcept { return axis_.value(idx_ + 0.5); }
  /// Return width of bin.
  decltype(auto) width() const noexcept { return upper() - lower(); }

  template <class BinType>
  bool operator==(const BinType& rhs) const noexcept {
    return lower() == rhs.lower() && upper() == rhs.upper();
  }

  template <class BinType>
  bool operator!=(const BinType& rhs) const noexcept {
    return !operator==(rhs);
  }

private:
  const Axis& axis_;
  const index_type idx_;
};

} // namespace axis
} // namespace histogram
} // namespace boost

#endif

/* interval_view.hpp
b3/etcks/eyJfW2+LWPI6YhTi6hV8dq420qoha4Lr4tsC8MFtwTrAMtFt1nm2B5ugT3qS88F74Bgr+ymc7OO2KHXCfwwRdIDkn6F2kmtAfy82y1yFbcIj2OeXUOX9pDvG9Hvzx4DWGaPPI7zq/OaBc9Rn3XaPe3Rn9s7O2r58Y+Xfu4E8l219a2RXLqdbeZsOtp8J76/jPz1oNTuT3s+y78jpXTVwb9c9bETQpq5dIWE5urpi3m/uUR2fQZxtLCppZkNDTKUSeT2KIlEc1C6+vwxCD67+QR+jX9HvxQDDdFXZUHhYbEVFW6jrcags+SB43RhzgtGL0IO5LGm/GXV7bfsxWatIvdqa8fflJY9nY7B/JgGrwuXNx4n9WNVORB/DnkioWh+/gilUFIU4WwmUqBi/1yhw01IL6iH3OpBmfmlayU/hx8iNA3gt9sk7T72CC1ZI6oV790J2NpBfQAD4I0pjH6CrgMUPbzaXBUs70gPsQk+fS6fIEKLBkB3A+c8BN5yyJe7t9awkbxbipLChruUloliHEdjeoQ1/1o+woSX2EJTXC6U+8u8jnKeqQpfe+HY2s6xUqcBNLfYAupq2Dwov9K1cFtwb7NdDHE7s63QXOKsrNJRHxPWlqefspBPAXm2uwKlUIzwfCv4ZnEOKZf3op4BuuFnZ6fWRNU1FVV2pTUO1ugS94ev1KlDeLOZNmsUkNhTiN7Ebbr9
*/