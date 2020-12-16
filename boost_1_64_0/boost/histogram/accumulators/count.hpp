// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ACCUMULATORS_NUMBER_HPP
#define BOOST_HISTOGRAM_ACCUMULATORS_NUMBER_HPP

#include <boost/core/nvp.hpp>
#include <boost/histogram/fwd.hpp> // for count<>
#include <type_traits>             // for std::common_type

namespace boost {
namespace histogram {
namespace accumulators {

/**
  Uses a C++ builtin arithmetic type to accumulate a count.

  This wrapper class may be used as a base class by users who want to add custom metadata
  to each bin of a histogram. Otherwise, arithmetic types should be used directly as
  accumulators in storages for simplicity. In other words, prefer `dense_storage<double>`
  over `dense_storage<count<double>>`, both are functionally equivalent.

  When weighted data is accumulated and high precision is required, use
  `accumulators::sum` instead. If a local variance estimate for the weight distribution
  should be computed as well (generally needed for a detailed statistical analysis), use
  `accumulators::weighted_sum`.
*/
template <class ValueType>
class count {
public:
  using value_type = ValueType;
  using const_reference = const value_type&;

  count() = default;

  /// Initialize count to value and allow implicit conversion
  count(const_reference value) noexcept : value_(value) {}

  /// Allow implicit conversion from other count
  template <class T>
  count(const count<T>& c) noexcept : count(c.value()) {}

  /// Increment count by one
  count& operator++() noexcept {
    ++value_;
    return *this;
  }

  /// Increment count by value
  count& operator+=(const_reference value) noexcept {
    value_ += value;
    return *this;
  }

  /// Add another count
  count& operator+=(const count& s) noexcept {
    value_ += s.value_;
    return *this;
  }

  /// Scale by value
  count& operator*=(const_reference value) noexcept {
    value_ *= value;
    return *this;
  }

  bool operator==(const count& rhs) const noexcept { return value_ == rhs.value_; }

  bool operator!=(const count& rhs) const noexcept { return !operator==(rhs); }

  /// Return count
  const_reference value() const noexcept { return value_; }

  // conversion to value_type must be explicit
  explicit operator value_type() const noexcept { return value_; }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("value", value_);
  }

  // begin: extra operators to make count behave like a regular number

  count& operator*=(const count& rhs) noexcept {
    value_ *= rhs.value_;
    return *this;
  }

  count operator*(const count& rhs) const noexcept {
    count x = *this;
    x *= rhs;
    return x;
  }

  count& operator/=(const count& rhs) noexcept {
    value_ /= rhs.value_;
    return *this;
  }

  count operator/(const count& rhs) const noexcept {
    count x = *this;
    x /= rhs;
    return x;
  }

  bool operator<(const count& rhs) const noexcept { return value_ < rhs.value_; }

  bool operator>(const count& rhs) const noexcept { return value_ > rhs.value_; }

  bool operator<=(const count& rhs) const noexcept { return value_ <= rhs.value_; }

  bool operator>=(const count& rhs) const noexcept { return value_ >= rhs.value_; }

  // end: extra operators

private:
  value_type value_{};
};

} // namespace accumulators
} // namespace histogram
} // namespace boost

#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED
namespace std {
template <class T, class U>
struct common_type<boost::histogram::accumulators::count<T>,
                   boost::histogram::accumulators::count<U>> {
  using type = boost::histogram::accumulators::count<common_type_t<T, U>>;
};
} // namespace std
#endif

#endif

/* count.hpp
iCvS47pE5SvW46xR+Ur0uMSofNMdPUAIOBMkJzbEXEGdGl0XODgZgRlyj9bewPkvse6whXYuS0OZS3Qz0xWJMa5HbcOft9Oa3r1/8C5Gqd3v2e6licMFOH3nn3evpNwIupgWIG7avf9has5+iELFTMcyWfcplUW/u+Z4GKbK81zkSEwsOMDqIfkaSUU99b4j/Evl+693ReNfShnbgj9mGw4R34YXw5ue3+ogCB0Mgf642TgvaycJwuFfprq2stumlNxNzw/es/u9mrlKTwRCY3KJfu7+Z03KKPTTZ9eQd5P90tE74Bw7IMxrdyAiQ6etH97Di6ezEJX389d/G4uSDhbPEYf0ujw+Rl3STw+c1h2bwfQ/HLohbNlmeS/vKJiKZkfgVt2V4DbWjx5ZuVbbFrrBqb0Kx2ZZLwdpwyDpdr22ByGSIrxKl7Sz9vDFi7lMfEeQtEzax0OfGqhLh0o1dD1pVa26VnVm4n6Esva36lS/sj8PYokVO3WHRBkaYLsQ90XTs86ElL5Zx7JekvcP7LlQBY8ugQ+O7DDf769Y9EVevCf/WKQzx4S0pclHoA6SxBYq0vPd7wvfGXO/j+/0Ec5MdJNTF82fQqKYD5ATAtq8v6+4nPyrkxPy/WfxqM7NwcLUVimBPx/Xslm/jz3uAuCEfqfvH3fJy3PY/PKOOQJbWGwIVnMPJDWWD/XrPU7i+z3aLXhPELgpsTJN+/umxJDHicFp79FmUktjyzrCRtPg/xiXgbZJAHVtU2LNTCWLcNaem7A7NGZYTW/C2MRN9mRga3dC1r/pvF0GaTGzSxx8C6tO9zqP3/4N/BwjMK8i6E8hgTOu+VsW5sNlVD0heI+7vvhbgHHyF63BkxMO7DcnN/p7UfegoTUXa3teagr80xzYgTOF1ohXLM6zni6543g41tfFGF7m2ljyt4AqcfmG/F10nw1/F0Xs7+Kg9HcxMRCGSapmaI2lH32n7l4IL+Oe1+NFSrPSjr+hIdq0Vm9MDeyNyZ5pOL2wRJxeTIx2x8QWfY8ZLi/Q2VHRroTwbz4ql24urJaTsU4ujqC+L81vkLTv3BmKXi82EgfqQkqnJFxMtEC7JdNbWuaaI1aABSTGIxVTkFkd3qpMBIdocxQ2upgvFqfvJLyiN10G4vmSWV+jkM24PWsD4n1XZqD9K0VrkFdSqxD3qQwA5f7giOl/Cp3YyLwAv9ndBI0hmwMwsbAQ+owoITRgHDpRn+io7mEmV5JHJx0Jh+G4yIJQuTYy99t4saXUzc6KcS/Vn8l3+mE0jNqtbApcxMgTKrJ5bS7Olxq6rqV5CF+CoXOI200wy0SkIE0c0iHjria/lfxkGF0MS1TtAFyz2QO72Dt0iPmXotfgXFtgquV4/C9kqzUtYzAC8tcQ/kWMdsj+rIl9FLXg3ZlL806tHpl1BC90l6vT8AqLS6yOVNhrIS0xgnwKoDzwDrmnlbnF4xU8LzBXbk0O3y6T+cxRKyem+fZPtQ1+5o88z03WYs5zRLRIuE6qPMNZwwiaxlwSnJyowwS2MBiOTjrKE/geQrjsG2iw8UsEc9xEh8O9aELJpQzD5AkgLL8wY+YmptBSL2ECbJXHQSf5u4F54bLQ2jCe9yrm/S924lFQejFNz16QkYNqN54Jo/Cq/tKD/rSMi6VLfbC49CM1mxYWyk8NWvlUVKSgi7TAf06NI4qfKAFVp+b9AdZ9o42K+cEEwulFOEGGptgW6odBTyhyGMwkx7vE/4W+sJPg+dbbj4LtrjdeZ+VMYElkel0ifkLD3MIrDjS3nsLsOIecKpOibuMZerrAEajFP/AeZdMu49WQoI3V6sntI1lIAQAMRfy4UN5Ow2KAn+w=
*/