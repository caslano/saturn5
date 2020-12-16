// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_SAFE_COMPARISON_HPP
#define BOOST_HISTOGRAM_DETAIL_SAFE_COMPARISON_HPP

#include <boost/mp11/utility.hpp>
#include <boost/type.hpp>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
auto make_unsigned(const T& t) noexcept {
  static_assert(std::is_integral<T>::value, "");
  return static_cast<std::make_unsigned_t<T>>(t);
}

template <class T>
using number_category =
    mp11::mp_if<std::is_integral<T>,
                mp11::mp_if<std::is_signed<T>, type<int>, type<unsigned>>, type<void>>;

// version of std::equal_to<> which handles signed and unsigned integers correctly
struct safe_equal {
  template <class T, class U>
  bool operator()(const T& t, const U& u) const noexcept {
    return impl(number_category<T>{}, number_category<U>{}, t, u);
  }

  template <class C1, class C2, class T, class U>
  bool impl(C1, C2, const T& t, const U& u) const noexcept {
    return t == u;
  }

  template <class T, class U>
  bool impl(type<int>, type<unsigned>, const T& t, const U& u) const noexcept {
    return t >= 0 && make_unsigned(t) == u;
  }

  template <class T, class U>
  bool impl(type<unsigned>, type<int>, const T& t, const U& u) const noexcept {
    return impl(type<int>{}, type<unsigned>{}, u, t);
  }
};

// version of std::less<> which handles signed and unsigned integers correctly
struct safe_less {
  template <class T, class U>
  bool operator()(const T& t, const U& u) const noexcept {
    return impl(number_category<T>{}, number_category<U>{}, t, u);
  }

  template <class C1, class C2, class T, class U>
  bool impl(C1, C2, const T& t, const U& u) const noexcept {
    return t < u;
  }

  template <class T, class U>
  bool impl(type<int>, type<unsigned>, const T& t, const U& u) const noexcept {
    return t < 0 || make_unsigned(t) < u;
  }

  template <class T, class U>
  bool impl(type<unsigned>, type<int>, const T& t, const U& u) const noexcept {
    return 0 < u && t < make_unsigned(u);
  }
};

// version of std::greater<> which handles signed and unsigned integers correctly
struct safe_greater {
  template <class T, class U>
  bool operator()(const T& t, const U& u) const noexcept {
    return safe_less()(u, t);
  }
};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* safe_comparison.hpp
/JnifHJPqZSMvstg9OD+kl/DyZJ/mzVo+QsLbSI6BpQHUypv6TDTpJphIJ1a++i4mXs1qadNvePCHhbQT7aPI240Inj/a7mgvTE4jPbbkLaztDvBfQSUTiH0yqiUdD0q+LUIVrHX7jPfauxvK0x5SjVsnLm2wYxwjPfH3glOXGEap1R/sjb2brBgRYFpXKGpejiap2D2ioLkcYXJ1YNqUS0+uaJAGVeoBEdVLpbKE2BmmPoxM4zK2GmhJzKDvAUPpyzXKo90ccXSzDQBejfXato2G0n1FcnTuf8w9yNvD8/2Jf2dY4Ol/2RZOe/aAF3w48HxN/3kWistSDLL8RLtN+g68cJRTasyuhLSl2xk5YWBIpLc3MrbILkSxZhXlB6ZFZUfL+T4Mu2FId1ba46q/KTMVcC5hhi5ZunZUH4m2Rgffzxrn0HxlSbyHMXPC0Nyc7K+w/jtZjXW2Z/WE4VNlRfLknA8Fz7wAIbOqTsbjqG6/xO6vGXyuN8KY79vNabNgE0jryeab92CLfWulIQtqFwIwnKS49OswMPSUF5ZrHPjWXu36RxcWapzo4NPHjRVlPOWEppjZHxmjwYqiBvOcBVPGGrX7+gyHKmCt1GfNddWPY08lcQCC03EDTnJLNzYxFk4T+Is3NDEWbiBRCbvZXx+pV9iGGCyvmjS1/P+BCPblTMkSeWaG718qn6ImgmC/2O+SnL93BVWeb5mBpbUAlE+09qQCzw/oD5WbPIHe8XO7Zm9f+wRLU8Uo6a63I8P2ursWixw9gQvRDu4kMxzLYmjms4/SYrrtcxD21D9zUO8oancDPr5+FRXXlij0cpUUhXkoalE3vRqL9alkvuKlgpdQQ97KCbwF3LV4SKssojOj1eayngxrV+7M9ZlzPYtHUyr0Y3uYNhSOZfz4jvqN28x11GUHcidheMBjrsEWkbeHz9L3x/fGds92eiW9d78Stt2gdzw6iTyy+T1jwO5Y5RDSm0c6UGWSFsAglCkhT6yTHJvSVqPUJkpuVXN81Vg2HZ0e1km2EwFox5DLzQmk1Irx8qkwc6Ncm9PtmbWfgkagr35SFy66cvH3YO7N4ywiNnj48OHtfwXgQn0xIKm+EHus5k9jFJ2WO4ciJLPArOlPf7qAN2+5FQYO5sR0olqre1zsLHJkcbGzau6JKkLAvfp+3+8q3PFOGEgEDYSYXc4a7f35ZCAMCJgeGqk4fGze7728DDdHwX+sItI1WvfvdW2/BXu5HqCgwMPx3MGOscTYzCvlWmzpyCp3XDitw3BV1EJ9jstgA9aunRey25KknWGFnx6gtP4QJLuqmbQYJI0ELTAHiNFOWvX3zCWG+g0whA0xa89ijC5iUm6rAF2mrfJEK3PpCPh9feif5JcPQz9EzKGe2EJE9Hs/H7gV93UdCyiAat3Z9uWf5eJPc+2nHBadoXZtjxED7eb7LblS2XniarDhaAxuSfZSZJQklgHLUIhWu3BgfKr3oYAmguM+JOfIdlS/5Txc70Hfh1H0e8L/DUBxU3HGGZWUhAfs1O2dGGkpmub/iEOqa6LJ63ueBRJMY7TL74aPq/xNkdgQ5zp36AC7kQisXPMFmVXp5XWqZJNpbS+svIEi1byDlJBE/SVIdchU95e2/IlsufuwH44h/rg/zE5seUpSmx5Lk1seS7SuXs+L1gv82mTpvD+S17yPciKs2YXTbW+2M0aQ3+iR1l/Ov727kd8ZWrfruP9+52Bx3jcBn9m7Y/oKB/n35+a4N+f1Nl1Sv/+F/foaZZemuDf39RfwdVUbKabdPYvtiTVNg7AKbPXnjV/f0IannED8T17hSTsq5W30v7Hh7vibu/w6M+FztqW/04/G30=
*/