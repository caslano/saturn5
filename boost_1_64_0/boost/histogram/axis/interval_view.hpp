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
3L/n5zYJ/f/nQPNdjp3svz/dEXf/ezaCcFN5Af2syCu2823wJfhxh37LodDXr+KHom086+ECG7oOGaMCVvVPcw6MiRK36LiOhv7TT8repzP/dqseGbN9AYyMXu/KkXGuYsNk/hkawZTSk4Lm5dWRbWEubRA4lvyNRsBIXKCKInMoueOaNyxUGCB3MSEvZMgbt0jI4CB0wkoseJbqUijrov1QGL2Qi63l+G7Z6cvV7a7uPtvFIppl1x9Otv324QPIPnfukcaJuhQjH/OgWPUUb9rQbZXN+Fp8GS5x1T+4iPAIJ8ZQf56q7TzCkarYJX4HiYA4TUhym1LmNixqe8SvX2ZRJdKbNipGR1flVaDUUW7aQv1gvQTkES+9oZ3dHBVKU24fbvxab1V04At/qUIGVdkl7OBL6M1Cu7SdeV7xyHM+24HL56n3Dy4U/Qs/LXNWJ+63jtyW+J73eeL7zNcS3/8kEt69oukT6vcrdu2Ikydrja/vYHlyOgjl9rcT5MksKU9+/T53U6H+evWDOGeLlCtPYa1dwYHlSq8YwuX/8F2s/BwjB32kq2CgCjltVuFSWYXStr5e/SA+WymrczvPMSXJibnmZ009j/+P4sf/Ejnil+GHxgkel9Pgx3Nh0Va83UwsIPRw3v0yQQmCfo9HD224Fe3E2yq8ESN4OJbgaTzSfa40c+oZagPSq1+n+mX/VpCqC7DnWe4Vm/5EuKtZqcdsAblq9orP5OqCGcrpEpXMUC4BKl/fLIc93Vjts7C14pi8fJkde33zjzX6mzkO4xy3yxwoNbsliFxGORLAqySnwcLlrzv0FbYoboiZuZwz/0IVd44U1osBpdgVV2poI3FHEkF2IifWABfyHiTGvc/KA5Qc9oeBQDaAvfAPO6KRjPAyfh0VfS0kSKLYtvBow2WWO5PL/fxNWe4bkm86AWKFhbGdH0lD31AXSN8/vbGv6fCu/8bRxZ43yi3q7yMDyLuf5uzBXc7aI43xGrZRcBd42kermKd5xUIkckkZqOXPpmkC+VRjq5mxLp+VjIZK8DymyiU27kJyr7jkFUqaSxyc+kZVrL8IdFYMac7j3J3IWRD6R+xCbS9Y7mFPt8FyDVk9zXLLZfUU3Gb5w4y3o2SCLNR4ReNayTCRkKwsUME83iV3SlPN1avVwqwQlsDjOI9sk8ULQ65HteXRIOWuI9vtcleJQTt0ON/Oxv5HbU2w/JrLEZnKpM1pq5SzYqQLXBz1RYG6osTNVYWISirwdYk7NtA+Oo0MKWaev50w6itziQpQPnWAD3RYimckLxPnNyFwSd79gKEweiyijCUaTcQV3OLOZmb765GAmZRi++6PiO3X/6ex/X/bZ00pn3/bGr/eLyHLqhAEYT7i4CraSlf1I0x6ppmItzw2UcO/bGKKIdCNfinBi0EvecSuRrk24L/ibXnqN59F8G9WalKaxcYPHvE6mJ9ysncN9e33FtWhHrEUw8/4Qb+zXf08CtodF1QspiFIy++l5r8KIrQx4qqVSpgPLBfHvBOT4QN0AvQu9i50KTOFTLZg0PfM92a7ydImll14h+tUnPgir7FcVR4feaSgIJGGVw8w3DvpG902OKhiTUlhQwmvZ6wYbLaGgGWt1cLcsKuRaTVbeXcTl28cpoN4WXQNQpn7IrFDx3jFPBlM/n1CTYq4576/4999AT7Jr3Tat0/om3h5ss/2/tBUOUbin2c0myM1nMDuXenokLvKK4L38ooMUh1Zujy1GW0ksyE4/wrtIPJzf/fBqB47q4Kf2bGcqvxC4TdQHtoQdlmXppct2YRCnoPU7erfvKDSY+TdSV0a7fbwCvKSYsc0BkHbTfILHQvoxADogs4=
*/