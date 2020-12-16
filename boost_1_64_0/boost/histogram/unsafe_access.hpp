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
MoPTtFPaDlGE2us2WbRFm2wwXDp7E+XR8jahwY8fNMNrwEsS+GxcrLFuZTUtc0AHHJACTTnTaUOGalM2M/AbUaXWTDohmm2bVrTNrM3eJuGnA6nybRa8Exip1Mbb/XiBrUD/e7Cc44tN7aSdI1Au7GLT6srus6B12CcsM9HT4iuL9bkVJEiiYLKvzKx/vkr/HCc6Od6CJ8WPwJPiE3zueLFddPhmWWlOS8U347NNzz6Ss6PGPAQSfW6VbWitPn9OWnmApZv/UJaQ+xUPPgZ6xuwclEwEK+iUoxd9CYrleyrK895X+j0ipVus7MbN726s/bttkLyPd5hxqEk0PwLdCGpNSlEfP2MWSb+nXqaDOpDViHI6jSD67NRsN8DLQdUNZvQejHIhfuUNFm32DTba5H6KeIO6l9knMv9OitWO81K9I0KiqUSioFmdSg03yxdSK/rgcRQIRkintby2kw+0Z/eYtUU9Ni2vR6vrsYjtVIzoBrGCanWqHwEMMNHi+oRNkuwhNmucxIbF9jC1QjWVStsao5VvNeurnQyELXjn1uHdhvQp1FqIHr47jaCkV3wgMroUgdr/cQLFd4My5zFpzkWKOZIu7/wPW8uvT2X7Hz9h+svgHSvMPqWHNy3cVignG4UW+ZB3nJzCbRZAQK9w2byvEFozTuwhPYiGV/D5RQxQJrquTnqGMAptx6hLI25PSB3lpTEZI+FKGnO2mYIvT7Tu6DmgbfDPRke2agfkDj4PRJs5Y/DVierjIZM6Kt8lNva87n0Rt8NPkJH0VBCNqeFFqo+OujGgYfiBpdSWnj7rEdaYPkVXo72vMXhcFg1QJ/bx2eoB9fE3TNru4CsTG16jInoOqqNcqbB1TkVtAFuZrAf9RExNPb08xJ8iyMgaOEBPF1NTZYGUul0UpGPgn+r0F2QLXC9rp2FW6xQFmVoL6hlVAGtB011Yl4niJP/0HDUjKKbb71KX7jDfpd7XhiAenQjvtGlteO3wF1chd3EKbhtMd4vpODCZLYpRA2WxIEGrv3gBVi9aNyWYRQCDL4oXscrj9Pk8Snf7p9eKMqf4ZDZKaiFdMa2NtE3FvBz/jMVQMiitgyH4z+WJNpINWpNq/wL1i79kpb9ihaiwS6DaDSCbENaoWUmwBIlav7COEq+h29qMzFAENHZyVJYM6AFD4BtEQnuzyG5SFzeQmqc1aaf9Dd/mvAAdhUq5QW2kK12Bh+lTl7/hUXrms+IC6gz8hKMFtWURkjU8zp+dXEDDrwigJ/+Iv6xU+9Pf6dc//Q+t52zaDBdrCzdrpUX+B3nDZUaZf+1zeAEiSstRwYPtHOv2r/0zXiDSS6u0Zv+Dm6jktX/BX8jXGbNEk1Y62//gDk4737/2BT3tAu2exVqzNq/O/+B+mXb5Cm1GrX/tXxGiTIs0z0r/L/uptO8dpb9/OEl/Hwxx+X+jv18nL5VSWKX+J40Q/9zf+myWfz+I1n9wCrqTjzudbMUFcoOWP2XiDZAXb9yJeWXKEXFP+egWVhRoNtHGlndrTG5IXUsIXZKQu1ddu1fqk3dqxzFqiC3WbtFSf/U69fEmU4no6AkhEvcz6g7VeEKWq6UzXzrifeBuEwIJWTNqxVRz1oxFosCSVbpY4EbnlqzSOoenTMyonSpKF4WXW4IvmRW64Fdg1hJoY5c2zpBQK60TUy3ajMXUEnZYH5AfnW4RH94k98lsWaUr2PBE6Uo2PLGWGJDv6q4luYs2UXtA6er9N5OsqqPLJ2jVmkwKEQ6qWLHaTfqja75BmUtTocGRVVorSrHNsUiUZhDcpZmAOkAD6YvmSqVjpq7ckdIfF4NGoC1oR2tRinOVRlNJwMjXczA+ABQ=
*/