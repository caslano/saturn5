// Copyright 2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_UNSAFE_ACCESS_HPP
#define BOOST_HISTOGRAM_UNSAFE_ACCESS_HPP

#include <boost/histogram/detail/axes.hpp>
#include <type_traits>

namespace boost {
namespace histogram {

/** Unsafe read/write access to private data that potentially breaks consistency.

  This struct enables access to private data of some classes. It is intended for library
  developers who need this to implement algorithms efficiently, for example,
  serialization. Users should not use this. If you are a user who absolutely needs this to
  get a specific effect, please submit an issue on Github. Perhaps the public
  interface is insufficient and should be extended for your use case.

  Unlike the normal interface, the unsafe_access interface may change between versions.
  If your code relies on unsafe_access, it may or may not break when you update Boost.
  This is another reason to not use it unless you are ok with these conditions.
*/
struct unsafe_access {
  /**
    Get axes.
    @param hist histogram.
  */
  template <class Histogram>
  static auto& axes(Histogram& hist) {
    return hist.axes_;
  }

  /// @copydoc axes()
  template <class Histogram>
  static const auto& axes(const Histogram& hist) {
    return hist.axes_;
  }

  /**
    Get mutable axis reference with compile-time number.
    @param hist histogram.
    @tparam I axis index (optional, default: 0).
  */
  template <class Histogram, unsigned I = 0>
  static decltype(auto) axis(Histogram& hist, std::integral_constant<unsigned, I> = {}) {
    assert(I < hist.rank());
    return detail::axis_get<I>(hist.axes_);
  }

  /**
    Get mutable axis reference with run-time number.
    @param hist histogram.
    @param i axis index.
  */
  template <class Histogram>
  static decltype(auto) axis(Histogram& hist, unsigned i) {
    assert(i < hist.rank());
    return detail::axis_get(hist.axes_, i);
  }

  /**
    Get storage.
    @param hist histogram.
  */
  template <class Histogram>
  static auto& storage(Histogram& hist) {
    return hist.storage_;
  }

  /// @copydoc storage()
  template <class Histogram>
  static const auto& storage(const Histogram& hist) {
    return hist.storage_;
  }

  /**
    Get index offset.
    @param hist histogram
    */
  template <class Histogram>
  static auto& offset(Histogram& hist) {
    return hist.offset_;
  }

  /// @copydoc offset()
  template <class Histogram>
  static const auto& offset(const Histogram& hist) {
    return hist.offset_;
  }

  /**
    Get buffer of unlimited_storage.
    @param storage instance of unlimited_storage.
  */
  template <class Allocator>
  static constexpr auto& unlimited_storage_buffer(unlimited_storage<Allocator>& storage) {
    return storage.buffer_;
  }

  /**
    Get implementation of storage_adaptor.
    @param storage instance of storage_adaptor.
  */
  template <class T>
  static constexpr auto& storage_adaptor_impl(storage_adaptor<T>& storage) {
    return static_cast<typename storage_adaptor<T>::impl_type&>(storage);
  }
};

} // namespace histogram
} // namespace boost

#endif

/* unsafe_access.hpp
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
*/