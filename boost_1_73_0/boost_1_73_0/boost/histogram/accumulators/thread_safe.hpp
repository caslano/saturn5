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
+pHC7HYQ2vTyetIfTNvtWqCfDMf90fUZJP5x+iTKOvZuszQAkZcdYLPdWKc2a7KQzC7JhzrNPMt9Y9VTNxuTLEP+7uW1vbXz4fLsejTYaT+4nczqdgn7FgaC+peHuuxo87D1ybqjcWord4TO+8dCGxoSabLppWEo7tQ/BtTD7+8VMC2IhUQzJ/vtPF0PgE7JEjXiozVOMzXzhDlrrnBL0e7MhOPr8wA3eIfYSddbGR8geOBQNB5gTHDV3KEJqR/YHM5sONAlV5PBu+vhaPZ1HYPh1rduvn2ytCHKL7jf61+1W3+jWq83EXkdeRuFU0V7v13I6lmCUyUUJmD5SW9yiwXf2YfchNjG/nQPujI97MFnOoDWN4jq84qngCKJ74BTbWc/3mEwdwjH6e10NviQTC96k8HZ1wtb39+BX7NPq/kNgn4/4qGtmTH3UohIPzah0oHRlvxbjsXmWNL8BWA1Q+Jid7DE0LWSZlmf2gKkPU3dUtQngS1nPs8LT1Ey+DjoX89670aDduv/UEsDBAoAAAAAAC1nSlIAAAAAAAAAAAAAAAAZAAkAY3VybC1tYXN0ZXIvcGFja2FnZXMvRE9TL1VUBQABtkgkYFBLAwQKAAAACAAtZ0pS0StJmgUCAABvAwAAHwAJAGN1cmwt
*/