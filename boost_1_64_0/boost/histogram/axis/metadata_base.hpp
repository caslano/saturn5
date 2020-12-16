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
BBQKe4Wr22y3MvVaQZeIhAcdSG9Z4tVNsSZcO4DcPExsxkoNWglEIJhs0g86vmjiRlCpJdLTsNpiGPziR948ym7AQiIkwFicRNWhOXYMN70ekfTQZ3ti0+ucVtmss4m4zdAfiIBSKThxeCKKtg9pzHnELx7gAZeFttNS2DUKWumz2c6ctG5HG/lmDafxgD2xUSqwzkdtSVutEJmFbGPBTdWdL8bJyBbZoHQq+aRTcSzpQQ2swbryTd4NK9GQQ4NxexsiSjAiR/NTGYDiAcqdhnQxDKp/o59O7OZNYOMs/V4ljsM7bttZy2xf7oluxo6X0dOs+fSW5QgQwSd3/H+L6j/kg/n/BZ7/P4qf/wfFzf+zaf5/ts35v7mt+b/rKjX/P5/U/J/NHiswbOmkj9ZkiyAUSjT3IyA3zcJa3vPouZx9UpvyoyXXYmF2/e3jsiriLGwoGVelxKnyfJejAbtZ463Og5JRLSxkqMUzyM+GndWokl+o8U2ScZ/tvk486bpFyfXqtoVOgcUeuMXJl+/9mx11l5GniFQMa0rn1OlSHXXM2SvB8b8Pe62Q/nma/qEuWlvghRr5s+skhA2OugKCYFVOwV5BOEPAycuuiDCmJTRWbKHJQyCFNIlxLPmM+D3mr6L1pAAlJT2KmPuUBcowsh9YHKWn0FeOkS3gDiVV0g6GcMbouug5c2/+HgCS3mb83UcRJ3KLclRGefXu3+ioC1IKFNJnjxUcyvY8FcgF4ST6r2mHm/3Xk04hr0r8LYy86DHJjbNdEuJXy2WzkdBRVwR4WPDczah7CzHc8I6Ouu6I8NBs6RbPcjBj2r43DtP3IlxjOrIHeKrZlyg+fIxEl/w/ckXy0UyaaIgA2u0l69/3Uef/MdL4AF2omU/DhV5N1qCm4xR9WcRTq7BkCG1IMqOj7g6y3tlIeZqTzOO/4alP25Ne+vM2KA/muvtMx6AnkpYCngtE1qOmc+9uCAtWT4VlTSc8xRr1bXsaFTjb+JYL+8u9ZmFP26TVRqbHJe5+xCzvHgS7idUVbe03ttRxY5M49iGKtOPq0ilUMKx80dJk7cUCxU+5ftOOmjqWDAW1w76sHehEGU/f2q4yPtqDMpbd2r4y/O0rowZlyHo1Ez9KMh/Kcd7RrnKy9hwCvtpZxmM/Ulvaia9V7cNXJZVhv6v9+GpnOZ/uPoS2LKvPak8Zi1DGGqrX0s5npSPHJuQ433pWBeVoZpO8TYkl9F1DJSx1mKlHqtQbWqdm+LmAD2vbQ/e+8f9P6w/7S6Up3MlnikM9cJVBbVboFaz5Xw/taWxJ2fFQ6IXgx7YdD4ZLzyjaCVmjr2O1zcVSJOsFq/sOCb1St2m+Ldhoff37cNaJoVe+e3148GNr48cpb3yUngKPMq9gOiYfFw3Z6syvUWDKmxdDd91RVK461PPYbt5jdPK9Ijx+tL0mXRqGPaXJpsZkR3i4tX9jjTqi3+cV26uhRuw3ZZ/VHbS3FbQ31nrWeKZtvh1gayKlbjp7Ub/cQFOfV+GPpLEdVVT+3yBPq42/TIi16RZ86D3uOZe+PovcLBDbGb05KNhOXrZC9jyWw2n3g2CwDgQWE7lqUQxfhscaj93FJhoXA58/Ps749PXiQMop5mG+lftn7XLbtc95NZIQjGMGWJzYfkzmfNunlP7mMqT3J5U+Bv/wVcmkj8H/5Inkzs9xCQ/kIsfrT+5zXsHLCTPFR1hAxC5nWEPLkE/v4vXRAuD3tysT1kd5rb++KIMpwNYj5ApaHZ22JpnVUaz8qQcsP+cA5TOAfF0+dGlc/so/Jlf+vviSGJ7J599WJXMeJIbfK5cldX6GsKVrL3qgwpyn7c8+eXnsxOXfat0=
*/