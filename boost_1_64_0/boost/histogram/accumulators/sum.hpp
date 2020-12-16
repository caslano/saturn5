// Copyright 2018 Hans Dembinski
//
// Distributed under the Boost Software License, version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ACCUMULATORS_SUM_HPP
#define BOOST_HISTOGRAM_ACCUMULATORS_SUM_HPP

#include <boost/core/nvp.hpp>
#include <boost/histogram/fwd.hpp> // for sum<>
#include <cmath>                   // std::abs
#include <type_traits>             // std::is_floating_point, std::common_type

namespace boost {
namespace histogram {
namespace accumulators {

/**
  Uses Neumaier algorithm to compute accurate sums of floats.

  The algorithm is an improved Kahan algorithm
  (https://en.wikipedia.org/wiki/Kahan_summation_algorithm). The algorithm uses memory for
  two numbers and is three to five times slower compared to using a single number to
  accumulate a sum, but the relative error of the sum is at the level of the machine
  precision, independent of the number of samples.

  A. Neumaier, Zeitschrift fuer Angewandte Mathematik und Mechanik 54 (1974) 39-51.
*/
template <class ValueType>
class sum {
  static_assert(std::is_floating_point<ValueType>::value,
                "ValueType must be a floating point type");

public:
  using value_type = ValueType;
  using const_reference = const value_type&;

  sum() = default;

  /// Initialize sum to value and allow implicit conversion
  sum(const_reference value) noexcept : sum(value, 0) {}

  /// Allow implicit conversion from sum<T>
  template <class T>
  sum(const sum<T>& s) noexcept : sum(s.large(), s.small()) {}

  /// Initialize sum explicitly with large and small parts
  sum(const_reference large, const_reference small) noexcept
      : large_(large), small_(small) {}

  /// Increment sum by one
  sum& operator++() noexcept { return operator+=(1); }

  /// Increment sum by value
  sum& operator+=(const_reference value) noexcept {
    // prevent compiler optimization from destroying the algorithm
    // when -ffast-math is enabled
    volatile value_type l;
    value_type s;
    if (std::abs(large_) >= std::abs(value)) {
      l = large_;
      s = value;
    } else {
      l = value;
      s = large_;
    }
    large_ += value;
    l -= large_;
    l += s;
    small_ += l;
    return *this;
  }

  /// Add another sum
  sum& operator+=(const sum& s) noexcept {
    operator+=(s.large_);
    small_ += s.small_;
    return *this;
  }

  /// Scale by value
  sum& operator*=(const_reference value) noexcept {
    large_ *= value;
    small_ *= value;
    return *this;
  }

  bool operator==(const sum& rhs) const noexcept {
    return large_ + small_ == rhs.large_ + rhs.small_;
  }

  bool operator!=(const sum& rhs) const noexcept { return !operator==(rhs); }

  /// Return value of the sum.
  value_type value() const noexcept { return large_ + small_; }

  /// Return large part of the sum.
  const_reference large() const noexcept { return large_; }

  /// Return small part of the sum.
  const_reference small() const noexcept { return small_; }

  // lossy conversion to value type must be explicit
  explicit operator value_type() const noexcept { return value(); }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("large", large_);
    ar& make_nvp("small", small_);
  }

  // begin: extra operators to make sum behave like a regular number

  sum& operator*=(const sum& rhs) noexcept {
    const auto scale = static_cast<value_type>(rhs);
    large_ *= scale;
    small_ *= scale;
    return *this;
  }

  sum operator*(const sum& rhs) const noexcept {
    sum s = *this;
    s *= rhs;
    return s;
  }

  sum& operator/=(const sum& rhs) noexcept {
    const auto scale = 1.0 / static_cast<value_type>(rhs);
    large_ *= scale;
    small_ *= scale;
    return *this;
  }

  sum operator/(const sum& rhs) const noexcept {
    sum s = *this;
    s /= rhs;
    return s;
  }

  bool operator<(const sum& rhs) const noexcept {
    return operator value_type() < rhs.operator value_type();
  }

  bool operator>(const sum& rhs) const noexcept {
    return operator value_type() > rhs.operator value_type();
  }

  bool operator<=(const sum& rhs) const noexcept {
    return operator value_type() <= rhs.operator value_type();
  }

  bool operator>=(const sum& rhs) const noexcept {
    return operator value_type() >= rhs.operator value_type();
  }

  // end: extra operators

private:
  value_type large_{};
  value_type small_{};
};

} // namespace accumulators
} // namespace histogram
} // namespace boost

#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED
namespace std {
template <class T, class U>
struct common_type<boost::histogram::accumulators::sum<T>,
                   boost::histogram::accumulators::sum<U>> {
  using type = boost::histogram::accumulators::sum<common_type_t<T, U>>;
};
} // namespace std
#endif

#endif

/* sum.hpp
vVd3aJDlvWuffXRCggk8QARiJ/dajoLNuXb7Aw7Mwuv/fPKPJ5ssLz0xCAXrTqdo/6hrHmT5x7X1BO/Wadi+te+k7f0sH4Tsj2P0mOdr4Bmj7rRNB9m1O+/A/h49iYAW9hYMqenH2qiTRyITDYaH1lMLmyI2JgRzQ4U7r9u+hMFgeXGR5fmFQVsnJ/QTPoFJc6+l9/kv81rEAdqOTO8kO9UH8CXev/l42JvwIKWLBiTxEhvfhcKOe2qx6Mz1bvVZ2r1qaEtziqd8EdMkfwJPmo3IN26ia3Wei0wbgJoHwuvDYXf4MqoE0l4aX7B7sMguNhdKxs4G7nX2lnlIxorNgjB/DeIdoKR5dZVppeHLKEV8ZzX27dX28DhI4mA+RFauKerrRk88ov9XpR2djimyObGWZUwK6j2oHjAyu8XhK3WTqM4zfZ/is2WuHEolM/IeV/CyBdSXc1cDtibZMa1FvFMKyO96O9mpd/X+1czLYJVcpsd8sAQ5HuEcDIIDa7jXjTwdbKPXZZ7+C+Pw6KVCqBcw/RQj0/3/gJHmrUHJ0OSVL4XXHmY0pGS4VNdbka7OWXxexYfUH1WgPn3W+R1MgEL8ajRGlI8ZAqbzVLjEN1jXwv7saXfbLHc3pRHN8utv6ALtcdHtk9II6em7ECMaKlDlBvzyKmHEh1kJuAv0LOcEbhSPR6uVF/GVSaLJ2YZ8N8UTHvNI+OUiACoPpGLd+xXz1RlmHT/4bbbnPfI48gUoeOR+NvsGad+QCo4GXlBt0JLLJ5a60ZjANDjEJvfxMPDmHRlFZMKjtdDN4YtoCW18l5YTAYq3xVLhuY1nGiVGBdYoJt+lOCCNLAqcS1o/UMu3k9KOM+qTNszI7d9dYbSNbJ/BtEenHz5DQmIR96sxVOSnq1qpyAY1noq0aUvrNk9CIBNVuZBfdF/DFTDWT0aEzIHeI5MFTOqW94f0dxKZF/me0gcpIGp98miq5A2g8C1XoS5FRTUVklTZxTdXUKVYeYeukSstLJkpr6Ux8bUck7OxWFn8gwuc4kUke/Ql9+xXucxR8QSXcUJeNnmqbGHdD8v1TGdQsXSdZGOuwabzD5ZgiULx8idWpPYs7gR5r0eH+ATj9drEnsVo4AadhnnKjbPAIsp4VXTG3yzWjzpfvPcUiZ8PX4dR6Lho8FY6IeBNmHEQxAHEwA3kW1QgCT8JtkujiHfuSsR3jyPef78JxHuVPTyWiPcqnXiHW+nxorm82CTtpobBAHQeK4m3Zx4/Ic/st4dvskHRPwdtdHSYkpsUypi0ruiQNt22qccEp79v1W7fBZtKzRNcZn+3QF1CoDaharf/baBb/9rAdnP9+dq3SRsoa16C344LEri3EBxTEy5Q2iXCTYOnHA9Hhx+4KTb84Vdjw4+tjw3vXRQbfqgiNpxzeWy498rYcMbI2HD3QGz4ihkxYXVBFGW0i0fnxNnvAJ60w/bXui1g7Fmj5Nn83cLZ4eU2MQNdjZ8IhhUbkWrWrET/UgN7RsCgaHkr9gwwsOf+G2nrJ8TR8hWaVyc2N+igoAxjes6z1z9q9hyts8esJM9f5zdE7g93Ep0a6RJXR3VqoNEpKzpFPTJRh+zads2aU7eoHjHi1FeY55BRnWm0aVDc/By/MTYslseGL3HHhm++ISpsnCffvCZaP+0MTFpCRBvG2RiZNLhW/GPUxS0g2o+cSga3sZz0KA9SLt4mHPfUgRBcAPiROR/0dS94mQLV4wn5b3gl56YQDT1G6/gJ+krf0McJUvVzzsgbEG3pT9IRar3d5Ls4UIldI119KirvukheG+W9g/JONvnS1GeiMnkimewkjw6sVyjHtqgcl0VyECLNhDeMab8=
*/