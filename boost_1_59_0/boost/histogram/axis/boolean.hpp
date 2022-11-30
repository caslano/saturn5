// Copyright Hans Dembinski 2020
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_BOOLEAN_HPP
#define BOOST_HISTOGRAM_AXIS_BOOLEAN_HPP

#include <boost/core/nvp.hpp>
#include <boost/histogram/axis/iterator.hpp>
#include <boost/histogram/axis/metadata_base.hpp>
#include <boost/histogram/axis/option.hpp>
#include <boost/histogram/detail/relaxed_equal.hpp>
#include <boost/histogram/detail/replace_type.hpp>
#include <boost/histogram/fwd.hpp>
#include <string>

namespace boost {
namespace histogram {
namespace axis {

/**
  Discrete axis for boolean data.

  Binning is a pass-though operation with zero cost, making this the
  fastest possible axis. The axis has no internal state apart from the
  optional metadata state. The axis has no under- and overflow bins.
  It cannot grow and cannot be reduced.

  @tparam MetaData type to store meta data.
 */
template <class MetaData>
class boolean : public iterator_mixin<boolean<MetaData>>,
                public metadata_base_t<MetaData> {
  using value_type = bool;
  using metadata_base = metadata_base_t<MetaData>;
  using metadata_type = typename metadata_base::metadata_type;

public:
  /** Construct a boolean axis.
   *
   * @param meta description of the axis.
   */
  explicit boolean(metadata_type meta = {}) : metadata_base(std::move(meta)) {}

  /// Return index for value argument.
  index_type index(value_type x) const noexcept { return static_cast<index_type>(x); }

  /// Return value for index argument.
  value_type value(index_type i) const noexcept { return static_cast<value_type>(i); }

  /// Return bin for index argument.
  value_type bin(index_type i) const noexcept { return value(i); }

  /// Returns the number of bins, without over- or underflow.
  index_type size() const noexcept { return 2; }

  /// Whether the axis is inclusive (see axis::traits::is_inclusive).
  static constexpr bool inclusive() noexcept { return true; }

  /// Returns the options.
  static constexpr unsigned options() noexcept { return option::none_t::value; }

  template <class M>
  bool operator==(const boolean<M>& o) const noexcept {
    return detail::relaxed_equal{}(this->metadata(), o.metadata());
  }

  template <class M>
  bool operator!=(const boolean<M>& o) const noexcept {
    return !operator==(o);
  }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("meta", this->metadata());
  }

private:
  template <class M>
  friend class boolean;
};

#if __cpp_deduction_guides >= 201606

boolean()->boolean<null_type>;

template <class M>
boolean(M) -> boolean<detail::replace_type<std::decay_t<M>, const char*, std::string>>;

#endif

} // namespace axis
} // namespace histogram
} // namespace boost

#endif // BOOST_HISTOGRAM_AXIS_BOOLEAN_HPP

/* boolean.hpp
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
*/