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
oVeT9Lz+RW7GffL72hGSjvz8mTVdrDObPbs6fXAT24xJzG42vz0ptFslPuwRqOdnZg8tU4E1pzF4zr0vK3v7m9R27O0RIMqmWkvZ+d3R4KhLt9C3A78Tt0Dta9dR69U4Htt3Z1r1i5ZxtjoBM70U7UTxU37J51ZEffn7KT//6uP8uBjRVJFp5IAFIZOtsg/ZYKnohL61KWE7hOOM8iksPxstQa/dTqVzdBXmVEEyt7tf/oT3eyYJvNdq5rN+Ao45hOzAbsQWDE/4132buSALpFUmEa947e6BiG6xczFf1KPPr8Ss/mi4AWMfmvVhQXTL9kEx0tv2CMI9fp8FaAzDFJA9jeDeaFG7iT9eMQRwFv5QzhlTceegyeArzsKbiMUVQy4Un9nleLfuMO+qs9NyVdtd1ihMunE7IT1eS7NA7rLSMy2Rp53qezq2qzXiOjyVeB78rGwQzDJXlbeFNpVOk0OWH01b9QvnKo8PZ0vv3qcx0r3iNXbXpg3TTmfGB+cVCiDpj7p7CyggxCqffoo9HrrHfnV4pTMHa8ZByIum95p3EAj9YBRLaTxm/eT4ZKQjWhNxnDzk+DIi2vcuf3P+CKn/db63+J2q0skmaK5qRG3Ws5jZkmZ9RLnLspcQ3kB3UccE17HAv4VqMSGOKl3HOMG60Vb6uouJdTP0fAY1PGlY4FLiUgFLW3l3r99IqYcGZpZFVgtJp5+edfOP
*/