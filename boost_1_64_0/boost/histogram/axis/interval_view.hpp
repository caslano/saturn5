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
LyYMbZ8bC3bIkSH2cAAncotzXjnZ0KsgkQ7UGpfRRtHgv7iPclSIZ+U/ZYMgc2Dtiro6whS653PC77GCkP5D79yWhTqKFqiqztt9de20MuJg1ZM7g1rHQ/4lySuZ36URdfB0ArCuTCd83UPca9GRXFEAsumEAYnLHBFDgZLBdDZRkIaTtd5sYuUn7sZAn3nlho2btALqGqjKciefAf+kSKvC/e39IKaA8Nl7e8PfJVm1WuzpIxn2erNiqg/tGuelf1Rbikb269T+SI5ee1JGrvNPhDhoR33ZXBBS/PwwjBTHWW60JpD/kNOPwjAgVH06gxJ24StjeUArAIiSiU5qCEfq8XrUBocnIbAgoEvQF+1mfqZULNYGqzvscPvLA4JtpkRLnK0OthdvzNhCCy1cPoCmtdI9oxQf6TKz2YUz0tMeH0Eq1vcQj1fYIQCas8q5UGsZw8YkKcy/Daq8ascrTA8N7cYn5opGPMjFl8O6bOR+1hpu2Yr/T8eViXB+CsB+Q2d70tUsVAnHU2bG9YBgmSmotNyN5lJyw4c+EfyuQ/gKlp/K62O7RHjwXg==
*/