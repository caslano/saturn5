// Copyright 2015-2019 Hans Dembinski
// Copyright 2019 Glen Joseph Fernandes (glenjofe@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_UNLIMTED_STORAGE_HPP
#define BOOST_HISTOGRAM_UNLIMTED_STORAGE_HPP

#include <algorithm>
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
#include <cassert>
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
  assert(n > 0u);
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
  assert(p);
  assert(n > 0u);
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
      assert((ptr == nullptr) == (size == 0));
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
      assert(idx_ < bref_.size);
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
    // must be non-const to avoid msvc warning about if constexpr
    auto ti = buffer_type::template type_index<V>();
    auto nt = mp11::mp_size<typename buffer_type::types>::value;
    const std::size_t size = static_cast<std::size_t>(std::distance(s_begin, s_end));
    if (ti < nt)
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
        assert(tp == nullptr);
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
      assert(tp && i < b.size);
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