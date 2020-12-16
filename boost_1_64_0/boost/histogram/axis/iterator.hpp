// Copyright 2015-2017 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_ITERATOR_HPP
#define BOOST_HISTOGRAM_AXIS_ITERATOR_HPP

#include <boost/histogram/axis/interval_view.hpp>
#include <boost/histogram/detail/iterator_adaptor.hpp>
#include <iterator>

namespace boost {
namespace histogram {
namespace axis {

template <class Axis>
class iterator : public detail::iterator_adaptor<iterator<Axis>, index_type,
                                                 decltype(std::declval<Axis>().bin(0))> {
public:
  /// Make iterator from axis and index.
  iterator(const Axis& axis, index_type idx)
      : iterator::iterator_adaptor_(idx), axis_(axis) {}

  /// Return current bin object.
  decltype(auto) operator*() const { return axis_.bin(this->base()); }

private:
  const Axis& axis_;
};

/// Uses CRTP to inject iterator logic into Derived.
template <class Derived>
class iterator_mixin {
public:
  using const_iterator = iterator<Derived>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  /// Bin iterator to beginning of the axis (read-only).
  const_iterator begin() const noexcept {
    return const_iterator(*static_cast<const Derived*>(this), 0);
  }

  /// Bin iterator to the end of the axis (read-only).
  const_iterator end() const noexcept {
    return const_iterator(*static_cast<const Derived*>(this),
                          static_cast<const Derived*>(this)->size());
  }

  /// Reverse bin iterator to the last entry of the axis (read-only).
  const_reverse_iterator rbegin() const noexcept {
    return std::make_reverse_iterator(end());
  }

  /// Reverse bin iterator to the end (read-only).
  const_reverse_iterator rend() const noexcept {
    return std::make_reverse_iterator(begin());
  }
};

} // namespace axis
} // namespace histogram
} // namespace boost

#endif

/* iterator.hpp
db4yRijMN6dhWrkBAig870L8OZ6ql0umyJOSveugrY+bDaiYTxl3o05e4X8VhIt3npu94iL9atind0V0Fd5DGyAEo104D6+aRlZCfZ4LZ45d/D2lXXBe0Rt1W2sHyiNI4eISOPOAyRxfDJ55UnhuSmOL3bG6YQ0aVn/+XsezmScNDn7sMEOi/d+seXsy7uB3Td9gL8mwTDl0e501JKGLde/Ey09D5fpprFw/TZQLJ7yy1MS/WD/JaBvfC4q189HagAgZKT+o+f73iFUTfBp9rtE+xe5xnC5N9LsHkkJK9HVpmNXXuNOUDwyfDx35wotMIjSU40BWxUBiCoe70NE+Kw3aqbj0BgdLUzFBuqDxvbfZJA+vCD9KkitJMHT9Bx2wZYtZyFZnYLLfTDohosWd5lSZVeUCQS/5KBZzXGgoYmiVaLM9Pwpz80TUXt+sm06RVlsk23jGbMNF3IZU2QYkB2OiyVlNd30f5NdcmiGPf5DThJrRyDGIVZxgxrvc0H/9NKfs/99iXwzS0ZS0ZycE5qdIn3KOJcfgqTTDseSIFCKG011wmefLMFYQZ4u+LQWJY4wPTXz8En8dxc5NapUweQqORoROHopcwQ0ZRvVdlO0tG52yWjSo2FFHfqDhqA6uAUoLHHUP4U2n8XW07TJ+r4vJornGT9Luho5GjUyh1DSTKdOSOMBL00aUZvh7Gt+YlZrFlbpAV2oS1crX0Xg4rhFIv9tMfwmnPy0hvRslx+pv1NNT6Ltotwo0bWlOmm2XB26hxNVES2BdMiVNrA2p9T2jb4WwUKDK5dAROUwQuUbnFF3a5Vxa00ZV2gRZnHhopVZPnrbUMYLyLfq+wN/b6Koz8kkdzvurxLzgtvmLBhUEehtHmGmv0mkntC5nCMpxqcECEe+irjS3O6Uxq0xjfGFixscwjpQwJk3GMlB7jzzkcxn/qg+fcvEGd2UE0tZNA3+P5AR3HYPnWfTshJOEdTV4eqoe/8gtuV/PBSsQ4BEGiIHfIf5M1M/ajpkJJe8gW05e8dc3aI14q4hfX1+TEltfzwBqn25ua8vosFekJib+CydN98v19EjWxeQfZD29pthK/P/1eP5faOX1c6mV12M5eCyTj7l4HGrl6UDH5iOokh4xwRFhi7P/qhYD6Q2QKPGlZW6hcVdKbN15Ka3/ntcER7odK3P3eZuJ6VGFmmiSH3oLoQQkniP60ePXtDMlTqFHQdyI/JnRPhM5oCTnc6y03iuVR2VYrgwkCnTB3f7L5tqvDiGhAcStqg+X/rMW1dhLcxd2CArr/G+bh9oHZGCjYoAFOR3BzXYMjk4ILGOIxjIMXpfWfp8Q9ueNiC3++tCSp9yXams2fhuXzD/TrBAqcstL2i59sfGEiY8ZjI/3/iznAbbGQou33Ia+pYdX8VAlNuG/R7zP+8vOovXAGbpETxaD3jTxRiJYeHhHFPYYcuhbEZ+LIT9yXXj4DzSoz3XRfW9NR8MQfAiuMDCozc1DU3+gc5X5HjGbs2fxecSXYtlbRpKqcbidm1WfzQ3jnY1nXjRnRMc1KxFZ3UXht5jx+yXjtxj4bU5ZvFcieI6NiiwuRaI88ObqcOkx4REdXdzs7b81Ne63EZPqyF1wN+O2G3WgxO88D1chRLRZZsdSVmzPSWWnf1xDCmtutmdbWAtAi4zQh+JwVdVsVPXaKrRHUkTRTh69VaZDsMt0FQKnGpE4FFTu1Vl4YRzZaLwfF3sKxQ6zNzNt1lGnkJs9WsygRkyP178Qh6pjrUBV5oGwdB6AU4OCe8sxLyqMOYY1+jrS8NNo0SQHfJFxPRI7rqVNI75scX1HW7MLPsNiOA0hSqIOdbWRPCTW9ADisCw=
*/