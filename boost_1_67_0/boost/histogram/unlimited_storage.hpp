// Copyright 2015-2019 Hans Dembinski
// Copyright 2019 Glen Joseph Fernandes (glenjofe@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_UNLIMTED_STORAGE_HPP
#define BOOST_HISTOGRAM_UNLIMTED_STORAGE_HPP

#include <algorithm>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/core/alloc_construct.hpp>
#include <boost/core/exchange.hpp>
#include <boost/core/nvp.hpp>
#include <boost/histogram/detail/array_wrapper.hpp>
#include <boost/histogram/detail/iterator_adaptor.hpp>
#include <boost/histogram/detail/large_int.hpp>
#include <boost/histogram/detail/operators.hpp>
#include <boost/histogram/detail/safe_comparison.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#include <cmath>
#include <cstdint>
#include <functional>
#include <iterator>
#include <memory>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
struct is_large_int : std::false_type {};

template <class A>
struct is_large_int<large_int<A>> : std::true_type {};

template <class T, class ReturnType>
using if_arithmetic_or_large_int =
    std::enable_if_t<(std::is_arithmetic<T>::value || is_large_int<T>::value),
                     ReturnType>;

template <class L, class T>
using next_type = mp11::mp_at_c<L, (mp11::mp_find<L, T>::value + 1)>;

template <class Allocator>
class construct_guard {
public:
  using pointer = typename std::allocator_traits<Allocator>::pointer;

  construct_guard(Allocator& a, pointer p, std::size_t n) noexcept
      : a_(a), p_(p), n_(n) {}

  ~construct_guard() {
    if (p_) { a_.deallocate(p_, n_); }
  }

  void release() { p_ = pointer(); }

  construct_guard(const construct_guard&) = delete;
  construct_guard& operator=(const construct_guard&) = delete;

private:
  Allocator& a_;
  pointer p_;
  std::size_t n_;
};

template <class Allocator>
void* buffer_create(Allocator& a, std::size_t n) {
  auto ptr = a.allocate(n); // may throw
  static_assert(std::is_trivially_copyable<decltype(ptr)>::value,
                "ptr must be trivially copyable");
  construct_guard<Allocator> guard(a, ptr, n);
  boost::alloc_construct_n(a, ptr, n);
  guard.release();
  return static_cast<void*>(ptr);
}

template <class Allocator, class Iterator>
auto buffer_create(Allocator& a, std::size_t n, Iterator iter) {
  BOOST_ASSERT(n > 0u);
  auto ptr = a.allocate(n); // may throw
  static_assert(std::is_trivially_copyable<decltype(ptr)>::value,
                "ptr must be trivially copyable");
  construct_guard<Allocator> guard(a, ptr, n);
  using T = typename std::allocator_traits<Allocator>::value_type;
  struct casting_iterator {
    void operator++() noexcept { ++iter_; }
    T operator*() noexcept {
      return static_cast<T>(*iter_);
    } // silence conversion warnings
    Iterator iter_;
  };
  boost::alloc_construct_n(a, ptr, n, casting_iterator{iter});
  guard.release();
  return ptr;
}

template <class Allocator>
void buffer_destroy(Allocator& a, typename std::allocator_traits<Allocator>::pointer p,
                    std::size_t n) {
  BOOST_ASSERT(p);
  BOOST_ASSERT(n > 0u);
  boost::alloc_destroy_n(a, p, n);
  a.deallocate(p, n);
}

} // namespace detail

/**
  Memory-efficient storage for integral counters which cannot overflow.

  This storage provides a no-overflow-guarantee if the counters are incremented with
  integer weights. It maintains a contiguous array of elemental counters, one for each
  cell. If an operation is requested which would overflow a counter, the array is
  replaced with another of a wider integral type, then the operation is executed. The
  storage uses integers of 8, 16, 32, 64 bits, and then switches to a multiprecision
  integral type, similar to those in
  [Boost.Multiprecision](https://www.boost.org/doc/libs/develop/libs/multiprecision/doc/html/index.html).

  A scaling operation or adding a floating point number triggers a conversion of the
  elemental counters into doubles, which voids the no-overflow-guarantee.
*/
template <class Allocator>
class unlimited_storage {
  static_assert(
      std::is_same<typename std::allocator_traits<Allocator>::pointer,
                   typename std::allocator_traits<Allocator>::value_type*>::value,
      "unlimited_storage requires allocator with trivial pointer type");
  using U8 = std::uint8_t;
  using U16 = std::uint16_t;
  using U32 = std::uint32_t;
  using U64 = std::uint64_t;

public:
  static constexpr bool has_threading_support = false;

  using allocator_type = Allocator;
  using value_type = double;
  using large_int = detail::large_int<
      typename std::allocator_traits<allocator_type>::template rebind_alloc<U64>>;

  struct buffer_type {
    // cannot be moved outside of scope of unlimited_storage, large_int is dependent type
    using types = mp11::mp_list<U8, U16, U32, U64, large_int, double>;

    template <class T>
    static constexpr unsigned type_index() noexcept {
      return static_cast<unsigned>(mp11::mp_find<types, T>::value);
    }

    template <class F, class... Ts>
    decltype(auto) visit(F&& f, Ts&&... ts) const {
      // this is intentionally not a switch, the if-chain is faster in benchmarks
      if (type == type_index<U8>())
        return f(static_cast<U8*>(ptr), std::forward<Ts>(ts)...);
      if (type == type_index<U16>())
        return f(static_cast<U16*>(ptr), std::forward<Ts>(ts)...);
      if (type == type_index<U32>())
        return f(static_cast<U32*>(ptr), std::forward<Ts>(ts)...);
      if (type == type_index<U64>())
        return f(static_cast<U64*>(ptr), std::forward<Ts>(ts)...);
      if (type == type_index<large_int>())
        return f(static_cast<large_int*>(ptr), std::forward<Ts>(ts)...);
      return f(static_cast<double*>(ptr), std::forward<Ts>(ts)...);
    }

    buffer_type(const allocator_type& a = {}) : alloc(a) {}

    buffer_type(buffer_type&& o) noexcept
        : alloc(std::move(o.alloc))
        , size(boost::exchange(o.size, 0))
        , type(boost::exchange(o.type, 0))
        , ptr(boost::exchange(o.ptr, nullptr)) {}

    buffer_type& operator=(buffer_type&& o) noexcept {
      using std::swap;
      swap(alloc, o.alloc);
      swap(size, o.size);
      swap(type, o.type);
      swap(ptr, o.ptr);
      return *this;
    }

    buffer_type(const buffer_type& x) : alloc(x.alloc) {
      x.visit([this, n = x.size](const auto* xp) {
        using T = std::decay_t<decltype(*xp)>;
        this->template make<T>(n, xp);
      });
    }

    buffer_type& operator=(const buffer_type& o) {
      *this = buffer_type(o);
      return *this;
    }

    ~buffer_type() noexcept { destroy(); }

    void destroy() noexcept {
      BOOST_ASSERT((ptr == nullptr) == (size == 0));
      if (ptr == nullptr) return;
      visit([this](auto* p) {
        using T = std::decay_t<decltype(*p)>;
        using alloc_type =
            typename std::allocator_traits<allocator_type>::template rebind_alloc<T>;
        alloc_type a(alloc); // rebind allocator
        detail::buffer_destroy(a, p, this->size);
      });
      size = 0;
      type = 0;
      ptr = nullptr;
    }

    template <class T>
    void make(std::size_t n) {
      // note: order of commands is to not leave buffer in invalid state upon throw
      destroy();
      if (n > 0) {
        // rebind allocator
        using alloc_type =
            typename std::allocator_traits<allocator_type>::template rebind_alloc<T>;
        alloc_type a(alloc);
        ptr = detail::buffer_create(a, n); // may throw
      }
      size = n;
      type = type_index<T>();
    }

    template <class T, class U>
    void make(std::size_t n, U iter) {
      // note: iter may be current ptr, so create new buffer before deleting old buffer
      void* new_ptr = nullptr;
      const auto new_type = type_index<T>();
      if (n > 0) {
        // rebind allocator
        using alloc_type =
            typename std::allocator_traits<allocator_type>::template rebind_alloc<T>;
        alloc_type a(alloc);
        new_ptr = detail::buffer_create(a, n, iter); // may throw
      }
      destroy();
      size = n;
      type = new_type;
      ptr = new_ptr;
    }

    allocator_type alloc;
    std::size_t size = 0;
    unsigned type = 0;
    mutable void* ptr = nullptr;
  };

  class reference; // forward declare to make friend of const_reference

  /// implementation detail
  class const_reference
      : detail::partially_ordered<const_reference, const_reference, void> {
  public:
    const_reference(buffer_type& b, std::size_t i) noexcept : bref_(b), idx_(i) {
      BOOST_ASSERT(idx_ < bref_.size);
    }

    const_reference(const const_reference&) noexcept = default;

    // no assignment for const_references
    const_reference& operator=(const const_reference&) = delete;
    const_reference& operator=(const_reference&&) = delete;

    operator double() const noexcept {
      return bref_.visit(
          [this](const auto* p) { return static_cast<double>(p[this->idx_]); });
    }

    bool operator<(const const_reference& o) const noexcept {
      return apply_binary<detail::safe_less>(o);
    }

    bool operator==(const const_reference& o) const noexcept {
      return apply_binary<detail::safe_equal>(o);
    }

    template <class U>
    detail::if_arithmetic_or_large_int<U, bool> operator<(const U& o) const noexcept {
      return apply_binary<detail::safe_less>(o);
    }

    template <class U>
    detail::if_arithmetic_or_large_int<U, bool> operator>(const U& o) const noexcept {
      return apply_binary<detail::safe_greater>(o);
    }

    template <class U>
    detail::if_arithmetic_or_large_int<U, bool> operator==(const U& o) const noexcept {
      return apply_binary<detail::safe_equal>(o);
    }

  private:
    template <class Binary>
    bool apply_binary(const const_reference& x) const noexcept {
      return x.bref_.visit([this, ix = x.idx_](const auto* xp) {
        return this->apply_binary<Binary>(xp[ix]);
      });
    }

    template <class Binary, class U>
    bool apply_binary(const U& x) const noexcept {
      return bref_.visit([i = idx_, &x](const auto* p) { return Binary()(p[i], x); });
    }

  protected:
    buffer_type& bref_;
    std::size_t idx_;
    friend class reference;
  };

  /// implementation detail
  class reference : public const_reference,
                    public detail::partially_ordered<reference, reference, void> {
  public:
    reference(buffer_type& b, std::size_t i) noexcept : const_reference(b, i) {}

    // references do copy-construct
    reference(const reference& x) noexcept = default;

    // references do not rebind, assign through
    reference& operator=(const reference& x) {
      return operator=(static_cast<const_reference>(x));
    }

    // references do not rebind, assign through
    reference& operator=(const const_reference& x) {
      // safe for self-assignment, assigning matching type doesn't invalide buffer
      x.bref_.visit([this, ix = x.idx_](const auto* xp) { this->operator=(xp[ix]); });
      return *this;
    }

    template <class U>
    detail::if_arithmetic_or_large_int<U, reference&> operator=(const U& x) {
      this->bref_.visit([this, &x](auto* p) {
        // gcc-8 optimizes the expression `p[this->idx_] = 0` away even at -O0,
        // so we merge it into the next line which is properly counted
        adder()((p[this->idx_] = 0, p), this->bref_, this->idx_, x);
      });
      return *this;
    }

    bool operator<(const reference& o) const noexcept {
      return const_reference::operator<(o);
    }

    bool operator==(const reference& o) const noexcept {
      return const_reference::operator==(o);
    }

    template <class U>
    detail::if_arithmetic_or_large_int<U, bool> operator<(const U& o) const noexcept {
      return const_reference::operator<(o);
    }

    template <class U>
    detail::if_arithmetic_or_large_int<U, bool> operator>(const U& o) const noexcept {
      return const_reference::operator>(o);
    }

    template <class U>
    detail::if_arithmetic_or_large_int<U, bool> operator==(const U& o) const noexcept {
      return const_reference::operator==(o);
    }

    reference& operator+=(const const_reference& x) {
      x.bref_.visit([this, ix = x.idx_](const auto* xp) { this->operator+=(xp[ix]); });
      return *this;
    }

    template <class U>
    detail::if_arithmetic_or_large_int<U, reference&> operator+=(const U& x) {
      this->bref_.visit(adder(), this->bref_, this->idx_, x);
      return *this;
    }

    reference& operator-=(const double x) { return operator+=(-x); }

    reference& operator*=(const double x) {
      this->bref_.visit(multiplier(), this->bref_, this->idx_, x);
      return *this;
    }

    reference& operator/=(const double x) { return operator*=(1.0 / x); }

    reference& operator++() {
      this->bref_.visit(incrementor(), this->bref_, this->idx_);
      return *this;
    }
  };

private:
  template <class Value, class Reference>
  class iterator_impl : public detail::iterator_adaptor<iterator_impl<Value, Reference>,
                                                        std::size_t, Reference, Value> {
  public:
    iterator_impl() = default;
    template <class V, class R>
    iterator_impl(const iterator_impl<V, R>& it)
        : iterator_impl::iterator_adaptor_(it.base()), buffer_(it.buffer_) {}
    iterator_impl(buffer_type* b, std::size_t i) noexcept
        : iterator_impl::iterator_adaptor_(i), buffer_(b) {}

    Reference operator*() const noexcept { return {*buffer_, this->base()}; }

    template <class V, class R>
    friend class iterator_impl;

  private:
    mutable buffer_type* buffer_ = nullptr;
  };

public:
  using const_iterator = iterator_impl<const value_type, const_reference>;
  using iterator = iterator_impl<value_type, reference>;

  explicit unlimited_storage(const allocator_type& a = {}) : buffer_(a) {}
  unlimited_storage(const unlimited_storage&) = default;
  unlimited_storage& operator=(const unlimited_storage&) = default;
  unlimited_storage(unlimited_storage&&) = default;
  unlimited_storage& operator=(unlimited_storage&&) = default;

  // TODO
  // template <class Allocator>
  // unlimited_storage(const unlimited_storage<Allocator>& s)

  template <class Iterable, class = detail::requires_iterable<Iterable>>
  explicit unlimited_storage(const Iterable& s) {
    using std::begin;
    using std::end;
    auto s_begin = begin(s);
    auto s_end = end(s);
    using V = typename std::iterator_traits<decltype(begin(s))>::value_type;
    constexpr auto ti = buffer_type::template type_index<V>();
    constexpr auto nt = mp11::mp_size<typename buffer_type::types>::value;
    const std::size_t size = static_cast<std::size_t>(std::distance(s_begin, s_end));
#ifdef BOOST_NO_CXX17_IF_CONSTEXPR
    if
#else
    if constexpr
#endif
        (ti < nt)
      buffer_.template make<V>(size, s_begin);
    else
      buffer_.template make<double>(size, s_begin);
  }

  template <class Iterable, class = detail::requires_iterable<Iterable>>
  unlimited_storage& operator=(const Iterable& s) {
    *this = unlimited_storage(s);
    return *this;
  }

  allocator_type get_allocator() const { return buffer_.alloc; }

  void reset(std::size_t n) { buffer_.template make<U8>(n); }

  std::size_t size() const noexcept { return buffer_.size; }

  reference operator[](std::size_t i) noexcept { return {buffer_, i}; }
  const_reference operator[](std::size_t i) const noexcept { return {buffer_, i}; }

  bool operator==(const unlimited_storage& x) const noexcept {
    if (size() != x.size()) return false;
    return buffer_.visit([&x](const auto* p) {
      return x.buffer_.visit([p, n = x.size()](const auto* xp) {
        return std::equal(p, p + n, xp, detail::safe_equal{});
      });
    });
  }

  template <class Iterable>
  bool operator==(const Iterable& iterable) const {
    if (size() != iterable.size()) return false;
    return buffer_.visit([&iterable](const auto* p) {
      return std::equal(p, p + iterable.size(), std::begin(iterable),
                        detail::safe_equal{});
    });
  }

  unlimited_storage& operator*=(const double x) {
    buffer_.visit(multiplier(), buffer_, x);
    return *this;
  }

  iterator begin() noexcept { return {&buffer_, 0}; }
  iterator end() noexcept { return {&buffer_, size()}; }
  const_iterator begin() const noexcept { return {&buffer_, 0}; }
  const_iterator end() const noexcept { return {&buffer_, size()}; }

  /// implementation detail; used by unit tests, not part of generic storage interface
  template <class T>
  unlimited_storage(std::size_t s, const T* p, const allocator_type& a = {})
      : buffer_(std::move(a)) {
    buffer_.template make<T>(s, p);
  }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    if (Archive::is_loading::value) {
      buffer_type tmp(buffer_.alloc);
      std::size_t size;
      ar& make_nvp("type", tmp.type);
      ar& make_nvp("size", size);
      tmp.visit([this, size](auto* tp) {
        BOOST_ASSERT(tp == nullptr);
        using T = std::decay_t<decltype(*tp)>;
        buffer_.template make<T>(size);
      });
    } else {
      ar& make_nvp("type", buffer_.type);
      ar& make_nvp("size", buffer_.size);
    }
    buffer_.visit([this, &ar](auto* tp) {
      auto w = detail::make_array_wrapper(tp, this->buffer_.size);
      ar& make_nvp("buffer", w);
    });
  }

private:
  struct incrementor {
    template <class T>
    void operator()(T* tp, buffer_type& b, std::size_t i) {
      BOOST_ASSERT(tp && i < b.size);
      if (!detail::safe_increment(tp[i])) {
        using U = detail::next_type<typename buffer_type::types, T>;
        b.template make<U>(b.size, tp);
        ++static_cast<U*>(b.ptr)[i];
      }
    }

    void operator()(large_int* tp, buffer_type&, std::size_t i) { ++tp[i]; }

    void operator()(double* tp, buffer_type&, std::size_t i) { ++tp[i]; }
  };

  struct adder {
    template <class U>
    void operator()(double* tp, buffer_type&, std::size_t i, const U& x) {
      tp[i] += static_cast<double>(x);
    }

    void operator()(large_int* tp, buffer_type&, std::size_t i, const large_int& x) {
      tp[i] += x; // potentially adding large_int to itself is safe
    }

    template <class T, class U>
    void operator()(T* tp, buffer_type& b, std::size_t i, const U& x) {
      is_x_integral(std::is_integral<U>{}, tp, b, i, x);
    }

    template <class T, class U>
    void is_x_integral(std::false_type, T* tp, buffer_type& b, std::size_t i,
                       const U& x) {
      // x could be reference to buffer we manipulate, make copy before changing buffer
      const auto v = static_cast<double>(x);
      b.template make<double>(b.size, tp);
      operator()(static_cast<double*>(b.ptr), b, i, v);
    }

    template <class T>
    void is_x_integral(std::false_type, T* tp, buffer_type& b, std::size_t i,
                       const large_int& x) {
      // x could be reference to buffer we manipulate, make copy before changing buffer
      const auto v = static_cast<large_int>(x);
      b.template make<large_int>(b.size, tp);
      operator()(static_cast<large_int*>(b.ptr), b, i, v);
    }

    template <class T, class U>
    void is_x_integral(std::true_type, T* tp, buffer_type& b, std::size_t i, const U& x) {
      is_x_unsigned(std::is_unsigned<U>{}, tp, b, i, x);
    }

    template <class T, class U>
    void is_x_unsigned(std::false_type, T* tp, buffer_type& b, std::size_t i,
                       const U& x) {
      if (x >= 0)
        is_x_unsigned(std::true_type{}, tp, b, i, detail::make_unsigned(x));
      else
        is_x_integral(std::false_type{}, tp, b, i, static_cast<double>(x));
    }

    template <class T, class U>
    void is_x_unsigned(std::true_type, T* tp, buffer_type& b, std::size_t i, const U& x) {
      if (detail::safe_radd(tp[i], x)) return;
      // x could be reference to buffer we manipulate, need to convert to value
      const auto y = x;
      using TN = detail::next_type<typename buffer_type::types, T>;
      b.template make<TN>(b.size, tp);
      is_x_unsigned(std::true_type{}, static_cast<TN*>(b.ptr), b, i, y);
    }

    template <class U>
    void is_x_unsigned(std::true_type, large_int* tp, buffer_type&, std::size_t i,
                       const U& x) {
      tp[i] += x;
    }
  };

  struct multiplier {
    template <class T>
    void operator()(T* tp, buffer_type& b, const double x) {
      // potential lossy conversion that cannot be avoided
      b.template make<double>(b.size, tp);
      operator()(static_cast<double*>(b.ptr), b, x);
    }

    void operator()(double* tp, buffer_type& b, const double x) {
      for (auto end = tp + b.size; tp != end; ++tp) *tp *= x;
    }

    template <class T>
    void operator()(T* tp, buffer_type& b, std::size_t i, const double x) {
      b.template make<double>(b.size, tp);
      operator()(static_cast<double*>(b.ptr), b, i, x);
    }

    void operator()(double* tp, buffer_type&, std::size_t i, const double x) {
      tp[i] *= static_cast<double>(x);
    }
  };

  mutable buffer_type buffer_;
  friend struct unsafe_access;
};

} // namespace histogram
} // namespace boost

#endif

/* unlimited_storage.hpp
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
*/