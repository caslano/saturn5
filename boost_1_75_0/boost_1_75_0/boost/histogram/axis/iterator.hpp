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
jOlpQrP9fhWRR2P7959xc7ZJj9evvPoGoTcrAP9u0l9Nr4B3em5ld87MLYkiOmsD6NDlysYMqNXF5o+udIjs1Pan4kWNTmc5CNtxv3fsaJPQ2sv/jtIAeDvf0G4AsBgfogOfQFwyJdBiAU6PP42epiddDAha355tSrRZOnwhG/kp+dkpeu0eFzx3qycXinZrTT5TOapVJTpT3Qxhonyh2pOrH2b8i+98WRzI6Scht/FjCYzqe/DyDDzJMTqi+h5/HfNHST89gzzf2wLdVJt471an8Vq8k3Fi6HXyfAIi2yO+JOI5fEakeN/b0vEJanN1u7FOa5tb9inWkKSf025i+oaz5T02TbIekIwDKm+/xyArdvNREtxGFRNRSS7Tlt3T1LCtqLddJkV6GMWd7Vt75f/47uxnWKkDANeqR8UICQZkszT6i3q9VCPN86/d/6zf+VV+eOvM6NlF+f2dghv/WUYFhc/VFtO/pNtHlwxxTCsf0S32vDZTc1jPuaM1c8wo7xbJ1HXoJDHdimlc7SM7gf7mYrDd3NCA7gRfy529XcM1YWRpK8UZTpFCaAl4hJH0yTLMh6Ofm6dAjgJRZstVLiNCrTO9RkhMOb3IF9MqmhrxRe44Mbir4Q9AL1ICGBj7oFCkExO2K6G686XjpZxZMrrVclzrs9gaQHxM9HdqaFfkzaSdWoTGy3QNvlphJ89BQUjzURr8nxKLONkW
*/