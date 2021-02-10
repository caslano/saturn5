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
    detail::axis_index_is_valid(hist.axes_, I);
    return detail::axis_get<I>(hist.axes_);
  }

  /**
    Get mutable axis reference with run-time number.
    @param hist histogram.
    @param i axis index.
  */
  template <class Histogram>
  static decltype(auto) axis(Histogram& hist, unsigned i) {
    detail::axis_index_is_valid(hist.axes_, i);
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
k/VWiC8pidw4gkd5rxks0B0VGW3JK6zUZFMxYYb+tIoS4uJUWe69nW7DpvPR+Zod4oa0APsZzADghGDDJ0iUbj496nkFue9XudhSKnuDzwfY1pj8UHnYknGdqff4sLqtUIz94MoAeR6aDD7I0pMgVmdBVqHB//rKoI0x0jeii+Dup276WS3cZCKEiTPv2fj1qh2A9+HF7jVc4OTEB4epQi2VM0vTnTP631MLqBWzlUq0vXreoY9X2zQPJ0U+l3F5lmYF8GPRWjoDGlFiciVnOK55qOaofnjrwxWxgZnRP6u0VB3JwwpHn04Oz2uaDi9Wecn4/MxUp+y6N6QQf22HHMiRT+CDeo4gmivpSNGxIF/VE9dSFpd9Bp2/wlmNwhUFxlcp31XKoJ7DlMygZaJedwbYqH3OTOYqU0XIpzbRO1PncgAMsyuyOdZw9HXNWVLNVaLS3I++gW1e11ox/9HT/bqNbRQWsc8iT8dIM7UDy+a9tQkgyF03eq3d8bP9I9fh70IpYOl5aOitvRjO4FUo6XmZ8SKTGn5kjsMyMUh6eFGRYZvISvK2Njc3cQxZmRbUtiOYqLHrk5aX9JvfwCBjQJ4DQhSWJh1IaR2HyLVh4c8vqflytoJHt951sGR+OZSK47U48Ot9nSHf1bSb
*/