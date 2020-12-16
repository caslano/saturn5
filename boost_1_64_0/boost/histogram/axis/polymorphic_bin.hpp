// Copyright 2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_POLYMORPHIC_BIN_HPP
#define BOOST_HISTOGRAM_AXIS_POLYMORPHIC_BIN_HPP

#include <boost/histogram/detail/detect.hpp>
#include <type_traits>

namespace boost {
namespace histogram {
namespace axis {

/**
  Holds the bin data of an axis::variant.

  The interface is a superset of the axis::interval_view
  class. In addition, the object is implicitly convertible to the value type,
  returning the equivalent of a call to lower(). For discrete axes, lower() ==
  upper(), and width() returns zero.

  This is not a view like axis::interval_view for two reasons.
  - Sequential calls to lower() and upper() would have to each loop through
    the variant types. This is likely to be slower than filling all the data in
    one loop.
  - polymorphic_bin may be created from a temporary instance of axis::variant,
    like in the call histogram::axis(0). Storing a reference to the axis would
    result in a dangling reference. Rather than specialing the code to handle
    this, it seems easier to just use a value instead of a view.
*/
template <class RealType>
class polymorphic_bin {
  using value_type = RealType;

public:
  polymorphic_bin(value_type lower, value_type upper)
      : lower_or_value_(lower), upper_(upper) {}

  /// Implicitly convert to bin value (for axis with discrete values).
  operator const value_type&() const noexcept { return lower_or_value_; }

  /// Return lower edge of bin.
  value_type lower() const noexcept { return lower_or_value_; }
  /// Return upper edge of bin.
  value_type upper() const noexcept { return upper_; }
  /// Return center of bin.
  value_type center() const noexcept { return 0.5 * (lower() + upper()); }
  /// Return width of bin.
  value_type width() const noexcept { return upper() - lower(); }

  template <class BinType>
  bool operator==(const BinType& rhs) const noexcept {
    return equal_impl(detail::has_method_lower<BinType>(), rhs);
  }

  template <class BinType>
  bool operator!=(const BinType& rhs) const noexcept {
    return !operator==(rhs);
  }

  /// Return true if bin is discrete.
  bool is_discrete() const noexcept { return lower_or_value_ == upper_; }

private:
  bool equal_impl(std::true_type, const polymorphic_bin& rhs) const noexcept {
    return lower_or_value_ == rhs.lower_or_value_ && upper_ == rhs.upper_;
  }

  template <class BinType>
  bool equal_impl(std::true_type, const BinType& rhs) const noexcept {
    return lower() == rhs.lower() && upper() == rhs.upper();
  }

  template <class BinType>
  bool equal_impl(std::false_type, const BinType& rhs) const noexcept {
    return is_discrete() && static_cast<value_type>(*this) == rhs;
  }

  const value_type lower_or_value_, upper_;
};

} // namespace axis
} // namespace histogram
} // namespace boost

#endif

/* polymorphic_bin.hpp
d3lbcaVcsU/ajMvlAxXNbcU5rskki73uKbE+DMo+vJW7PetfPpOBlQfn0+KO12PQL+GYpxgO5o590b1/0NP+AO1l2CNWPqID8zUXxcXVZmBXFgAhO1/4sAoKpBRh8o6wpGxPxoVfIv0V2kn/8dt4/WWB1FgWS/1lqVJc6p3HLIRV4BFSId4y8ebCm7eBb9GkeD3Y+TjSqQEazDRbFqFTqInE9L3xKrwKrcKrcInBEOa1U4xc4x6zHw3jV7If31gujxXs4Y1M8haJNLhsmZO5xLiY1hCnBR+MrSh0/utVfjqLihWRPCDiqiI9AKaw8+WFLHxzBxVgP8X2j4Y0utyxOR2XqlKBwV3pc3KNJ03ICzTkEgX5QvYusis8kz2S0LzJoxn4yRUnTEHHu0XXWzipdqGh1Z4eF0y3C+4x446yKmGVUGZ7HhntPtMA9Ec5OiHCvtsFBYKj0fB2LHkK4QPA0PD4CFWMEhXQUREXnIRMR98MoMDpjreH5vXDmZQhFnH9ZK5U7c1mwcQbueKAfs9lpmoohysYultpoP01iZW7+BJNpBfKipXFVcxfxJXyFxgvm6i7SKNuzzVSx9FHF1p4GUtFdHyTcO7TuxG/Q14pFeW6xfFQvxlbNDSvGAYzA7UrTks3pNHnv24jzWjhf5lmtO0PT9w8UWSGzvSfgFdn1pz5xuQ4eqyXSL0/bHK8JkqWPSfNuBDJIu84Vg+3hs+HdHpEeDbE0fROrzlWl1shovJDCgTUTs8NOGb7k4/5cw3DBOzXgEfGAQaojmFPumN1hmP15QxrY+Nn2Y7Vg1MI3EY8dKDA7Y7V59j5NVWHp1ExjeFz0rHGhKAYvsTeYEPpqFUXXaUUx+qzbVytxo/5zq9OLzSkw0HAcqtlXkHINsACAX1eb/DU48EFexnzzarO11W9e5nUW0xgn6cNp7I936QJ7eSR7flI+7lrf82Cq5PvdQ9ZtK7FxfuHPGq07J7nxR6bjSg2m41q1lp0I64wlshGfBjS+GbTujHgQV/x5k5m+PyYoNcNTinSw5lnBxsLIseGM1nMi2QjsAMut4o4wsNJysPGCwl6mRX9v5/T21hvlnWlLmuOLmsyF8agqaqjPS5/Z/HhV1Ea4TJOLP5GvbXLQO9g+Csg/I28KV5/lR8CdyYnIx68ZBbt9DmJGzTwKTQxdKxSXTn9Jxuvx7WoTul/luoW0fk8cIPTmPkWaM2VPaa5MhUD/Eo+eWqtqmdq17H+LKtKzcnZ4oZvo9Jt1OLdRJBz+xrv6cJZ9aTLP1aXP2mCrsGjN8saeI33dRa3uB2BeuY62vjQbEi5BrSlQTLJKreXBCDWfY3wSt1Xk/9o49N9236PytKLeHSVpLl+yAujmKwvo7R7/czXUal4Nr60mIz0xwWsdhjK5pfkHgR13v1rrvPP1s/JfogCnWz0G+o6x06WsEtTvKWpgRy+enyQJdDJN1W2el7kdHnZfOSY0rRAiYy3In66jK+OdJMXai+6wpqCS+1nyuCAcbVEVnW9vNuOygB/6giWlc4MDS8Zmmt1Ulwrk680yiGulXoQrpVLXIuU8vJCy1Aqz4fzjvePoYfT/IcNoCVK4OgNVoqnJv0CTFw1qVzOmr2x323yYV3hDb/St0nSpZZNMj81uRenUK3WqW/5laJDTjy5oY/khT/BNUpSH2l/sBDSNw+gXE+V1syY54hnSXVZcJc/kEvqL7nJUSUu9XG4S9Rvj0b/ZOmFnu2N81SBPvGJ7pupEj3xDSW6mxS6DWCR0qNQhryokHb8w+cSr1z8A8EJdKvb2Raz3KmZ5ZAEZklcPC/Y6CSnlBidGbSmamSgoTQ+vP+EXjOOEltWaLG805RY4WQ=
*/