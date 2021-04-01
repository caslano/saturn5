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
R+Pkzrvjk2fmU8so3wte2XVnE/mXEr2CdHkaO4d7x2Jl3qo65+uo+v332KuRycBOSGu0LP9RTkRXCbfmUmw58goAbSPxG7+Z7e8zOtadb4bX2EvesqEYNcWEPuWwGJbno7VbsoK/O1aDy8PJv5AivZ/69iELGEUiU9tt76S2Gwwe8qcKwCsskjvdnX13xiLRYzFeXNPZf6y3l2o6ovVDjqsGs5qObr52jOOigvNUfOt0u+1IjxWjVwAFj3MghKCx2IPXUQFpGisKPNp9olGndLbxbUTFC08PIz0NycjQS2HmRzrKDcAP0CJo48SG/tDCzAdEYRkK8aonbfO0t0eGN9aURkT/m/3a5S3yDFNtRkTR3LLy1YT/gAAFzCOrROdjZ5nviCWOzOQWOvHtTg31XtDOSGq7ajfEufpMvQDOuLxDl4dNo5Pr/tj25oNEuXb4bUwcKtK2l0T0u+YrbNPuL3h4dEEYGwOIHwqmvat8p+I9aJjF6VfbR0GQSunvGipQL+gaxNVKRQyQQ2cAdWmbcTO8ghRnmDbxwn77JatWOfaCxQT4RJ4I0apQJw==
*/