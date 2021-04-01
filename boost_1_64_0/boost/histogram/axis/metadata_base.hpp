// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_METADATA_BASE_HPP
#define BOOST_HISTOGRAM_AXIS_METADATA_BASE_HPP

#include <boost/core/empty_value.hpp>
#include <boost/histogram/detail/relaxed_equal.hpp>
#include <boost/histogram/detail/replace_type.hpp>
#include <string>
#include <type_traits>

namespace boost {
namespace histogram {
namespace axis {

/// Meta data holder with space optimization for empty meta data types.
template <class Metadata,
          class DetailMetadata = detail::replace_default<Metadata, std::string>>
class metadata_base : empty_value<DetailMetadata> {
  using base_t = empty_value<DetailMetadata>;

protected:
  using metadata_type = DetailMetadata;

  // std::string explicitly guarantees nothrow only in C++17
  static_assert(std::is_same<metadata_type, std::string>::value ||
                    std::is_nothrow_move_constructible<metadata_type>::value,
                "metadata must be nothrow move constructible");

  metadata_base() = default;
  metadata_base(const metadata_base&) = default;
  metadata_base& operator=(const metadata_base&) = default;

  // make noexcept because std::string is nothrow move constructible only in C++17
  metadata_base(metadata_base&& o) noexcept : base_t(std::move(o)) {}
  metadata_base(metadata_type&& o) noexcept : base_t(empty_init_t{}, std::move(o)) {}
  // make noexcept because std::string is nothrow move constructible only in C++17
  metadata_base& operator=(metadata_base&& o) noexcept {
    base_t::operator=(o);
    return *this;
  }

public:
  /// Returns reference to metadata.
  metadata_type& metadata() noexcept { return base_t::get(); }

  /// Returns reference to const metadata.
  const metadata_type& metadata() const noexcept { return base_t::get(); }

  bool operator==(const metadata_base& o) const noexcept {
    return detail::relaxed_equal(metadata(), o.metadata());
  }

  bool operator!=(const metadata_base& o) const noexcept {
    return operator==(o.metadata());
  }
};

} // namespace axis
} // namespace histogram
} // namespace boost

#endif

/* metadata_base.hpp
6OAzsNcvqxsimKFi3D+D+n4+8E6bCLbcKlqEZwgCfbsqLtnWsuv5HK9TzGT4KTc7XgnXgnfehXxCB9kHJkRsP0CopfsV6oc2R7bCOhsaXVTi4HAg7kRHuH6CE7zxpBeEBmo+saAAZsVdBU1LBhUYofEl56IEWgtDu2krHcu89nws370Y7mHDwgQFnEHIxkFavrVFONwTXdaKFgKvgD67UEbGO2KNqqPTSD4MjMiMCMAz3iMIudV6cdr4yOQelL//6fHQue6c3wyLZ/OadJo+XSm44pCy/jO+wRClB0FhFdY/nH8GROdqqPlagDicwB49osUnl9AA/jNkU/EraGrEal+DC1Zh+Tt2f3YI3XqRJ6S5vDkXdLp2Lp52qpQjAbp+z9Uu4AvSnsWBl6LCxRNg9/1VYQgilq+NxuaP/mRDjdq+s+u2DAMwQRQQq92ZW4xM9EZHcUaFsIYD2/38QZMsHLg1lxPJrogLsJCR0j8u91gOG/arYub/ZnLh4jr/YMxQ0MQ3Sy27wcfGMZgJmdLNijfKwsF16b/UeECIf8wcR5idnuko1Z8KB7oQbA==
*/