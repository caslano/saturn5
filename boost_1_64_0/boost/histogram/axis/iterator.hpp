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
wCj9BGns4l4xt1HSu8B9emlZXbpvEDLeD33tzyDL6S+Fkl8V7d7UO36p3mYn8qBu9adR87WNcwolsLgv0uVAEiH17t1cfzkPNG916fZXcV/VKo3Z7/RD/sfBMDVBdrgG6HSTarp9F2dxEhGgivJud1r/7GrMoQVdtU4ZGrFqxPLRkH/8Yu8HscZStPMUFWZ6/SEpqz97ySj6FcDb492eNADVeHDhCxPC3rwLcEKRB4E2n9H1foHt+Pqqf1nPycn8ZMwTFMG52WezcnkdpMIDQfyaieizoNddeHfDEP6r06onuAKv9NeCRRS7ybnJDlCs5EecVhoLrN2DoGuZiA/6xxOeQTZPTPiJSltJHV3TzktrH6zNHoaru7fY90GS3VAG10UsOuI6mbbCZUB8d+5zzN8gSZANKt7nIUEusiFq6lgfNLSq7b+YrQHYCT7IiISfGE77/WOwBZ/QgO+r85kX6ZS/28KsT2xbp6GeNgteA882I33lw5hhtn9/17PzzuTzB0eTqmogSm8DtBog55datF11Oxu5/fg1Rv29CU2h28KUjNdtO/jzeLrEVA==
*/