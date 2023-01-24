// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ACCUMULATORS_THREAD_SAFE_HPP
#define BOOST_HISTOGRAM_ACCUMULATORS_THREAD_SAFE_HPP

#include <atomic>
#include <boost/core/nvp.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>

namespace boost {
namespace histogram {
namespace accumulators {

/** Thread-safe adaptor for builtin integral and floating point numbers.

  This adaptor uses std::atomic to make concurrent increments and additions safe for the
  stored value.

  On common computing platforms, the adapted integer has the same size and
  alignment as underlying type. The atomicity is implemented with a special CPU
  instruction. On exotic platforms the size of the adapted number may be larger and/or the
  type may have different alignment, which means it cannot be tightly packed into arrays.

  @tparam T type to adapt, must be supported by std::atomic.
 */
template <class T>
class thread_safe : public std::atomic<T> {
public:
  using value_type = T;
  using super_t = std::atomic<T>;

  thread_safe() noexcept : super_t(static_cast<T>(0)) {}
  // non-atomic copy and assign is allowed, because storage is locked in this case
  thread_safe(const thread_safe& o) noexcept : super_t(o.load()) {}
  thread_safe& operator=(const thread_safe& o) noexcept {
    super_t::store(o.load());
    return *this;
  }

  thread_safe(value_type arg) : super_t(arg) {}
  thread_safe& operator=(value_type arg) {
    super_t::store(arg);
    return *this;
  }

  thread_safe& operator+=(const thread_safe& arg) {
    operator+=(arg.load());
    return *this;
  }
  thread_safe& operator+=(value_type arg) {
    super_t::fetch_add(arg, std::memory_order_relaxed);
    return *this;
  }
  thread_safe& operator++() {
    operator+=(static_cast<value_type>(1));
    return *this;
  }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    auto value = super_t::load();
    ar& make_nvp("value", value);
    super_t::store(value);
  }
};

} // namespace accumulators
} // namespace histogram
} // namespace boost

#endif

/* thread_safe.hpp
+bh4Z1IxZgC5GVkobmqeskqK1hdxAYHQN73fE2E8yDMvjLWKqi+T06Gx4m2PPughuJtHvY1RHH9zCToaFjkQRJgfiQdW7uVcxUGjewoOUjegkgEsR2Dg+XKy0Dh0fGYK/MTSi+gWGddN8pxSIeU/tNETMzCCRxy5XIJLnztn2kQJTYRk/+19U7PD4Rnds9n1vdNB84d2ZRPYQDPkLVHsxW0hvnvlKQpqv22dBzgRezgGVk045N+2I+/fvU5U99jwrNWuP3d/bsmYf93phzb1uAnl7BIFEAVmBmQG6gSgwzUnZMCvBaD+XowiaRH8YPvh8mvOmlh7IDr8E8wTXGYAOAAcOCHEPQ1vCwv6w6Wjw60FhAZccF2hraPDx2Jc2YXFwPIF6gmxTH+8X2sUBk+KOhE/p70D8B6DitGfTZFWS5Td0TxJPWGfybdhrimmYdBmoesZXrP4rOCov6WtZIf9NikWtO7HEvUzKSxmwZSN7X83p8+KitGeEetgGNc0oCANdy6mScfnTFxcVrWYEqNcdByOQkPV0UtJjkIrZmJfsNBvCio2Kko87Ckz7ZeT2BPdtFyXinkgquNoiY2i3jVfJzyWQSuSjIsXe9ndi/ddJJPPMGKIJybyXCc+Y600KjWkwmYtOg1453DEghM1t533nzw7mV976jGrTcJbENgX1bBeyp16EK9KO2lElkikG/O6zkyNcmWEHrPvGrGb
*/