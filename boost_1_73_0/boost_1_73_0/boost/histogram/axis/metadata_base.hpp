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
6j0XO4lKgq+isr+BVsFHDyMQ+JmT+K7P2kExapSwRhn52zAF9gs4tll6IK5v4XgsJPwVSwho7F9LKwAhSAdEAg8qKkmjUSk3rAinI4cTcKiJ8VH8U+9RxsAX+9yhJ0PhAqd1pTvW/cApSjfF2oR0jSnogbJmbDBW+7RyEDXzTMbAJhDBJgINSKrIS35OETp4uXWSXO62kYpDPRwOnUdQrCg+kftEqjBeHDO5O0iEHKAMGRLIjg79CQj/NKSEwDpqq3hOzciYwnxfaA6DcDRAjuDQW4RMjiaw6CdIvIx3AKxx0gwB5XS8oHIjTAqwgt0bEQT0iB7yzJAdRvqYatJydF8A3dmoLftPcNGUeVAU0nmKZJlF9KEH697ZmeOvIoHgz7KopUOeCpCTOg1ewExiecI4r62hlVJEf/7gfQYIo+X0FmDF0Ysyfs/zZk4zPkHU4M0AiaIcGvKnACwCDVDmgA8p1p9Qu17UiUK8k5GFoF7hccMICCgwn6heu4G9LJOhGLegDVBH3hT4JKmdBrZYblQM2CRpfyJ3fDAwS1JcPN01O0kwniPEyICPwbEJtYlU4C1FuyVJszPBeInHR3tHI791rsUdPaxBEcDHBElR2dCs2zOzEz/CuSHVYm/eS4/s1eJTX7TOYPyvgXiO
*/