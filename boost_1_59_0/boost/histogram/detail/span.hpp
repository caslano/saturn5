// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_SPAN_HPP
#define BOOST_HISTOGRAM_DETAIL_SPAN_HPP

#ifdef __has_include
#if __has_include(<version>)
#include <version>
#ifdef __cpp_lib_span
#if __cpp_lib_span >= 201902
#define BOOST_HISTOGRAM_DETAIL_HAS_STD_SPAN
#endif
#endif
#endif
#endif

#ifdef BOOST_HISTOGRAM_DETAIL_HAS_STD_SPAN

#include <span>

namespace boost {
namespace histogram {
namespace detail {
using std::span;
} // namespace detail
} // namespace histogram
} // namespace boost

#else // C++17 span not available, so we use our implementation

// to be replaced by boost::span

#include <array>
#include <boost/histogram/detail/nonmember_container_access.hpp>
#include <cassert>
#include <initializer_list>
#include <iterator>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

namespace dtl = ::boost::histogram::detail;

static constexpr std::size_t dynamic_extent = ~static_cast<std::size_t>(0);

template <class T, std::size_t N>
class span_base {
public:
  constexpr T* data() noexcept { return begin_; }
  constexpr const T* data() const noexcept { return begin_; }
  constexpr std::size_t size() const noexcept { return N; }

protected:
  constexpr span_base(T* b, std::size_t s) noexcept : begin_(b) {
    (void)s;
    assert(N == s);
  }
  constexpr void set(T* b, std::size_t s) noexcept {
    (void)s;
    begin_ = b;
    assert(N == s);
  }

private:
  T* begin_;
};

template <class T>
class span_base<T, dynamic_extent> {
public:
  constexpr span_base() noexcept : begin_(nullptr), size_(0) {}

  constexpr T* data() noexcept { return begin_; }
  constexpr const T* data() const noexcept { return begin_; }
  constexpr std::size_t size() const noexcept { return size_; }

protected:
  constexpr span_base(T* b, std::size_t s) noexcept : begin_(b), size_(s) {}
  constexpr void set(T* b, std::size_t s) noexcept {
    begin_ = b;
    size_ = s;
  }

private:
  T* begin_;
  std::size_t size_;
};

template <class T, std::size_t Extent = dynamic_extent>
class span : public span_base<T, Extent> {
  using base = span_base<T, Extent>;

public:
  using element_type = T;
  using value_type = std::remove_cv_t<T>;
  using index_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  static constexpr std::size_t extent = Extent;

  using base::base;

  constexpr span(pointer first, pointer last)
      : span(first, static_cast<std::size_t>(last - first)) {
    assert(extent == dynamic_extent ||
           static_cast<difference_type>(extent) == (last - first));
  }

  constexpr span(pointer ptr, index_type count) : base(ptr, count) {}

  template <std::size_t N>
  constexpr span(element_type (&arr)[N]) noexcept : span(dtl::data(arr), N) {
    static_assert(extent == dynamic_extent || extent == N, "static sizes do not match");
  }

  template <std::size_t N,
            class = std::enable_if_t<(extent == dynamic_extent || extent == N)> >
  constexpr span(std::array<value_type, N>& arr) noexcept : span(dtl::data(arr), N) {}

  template <std::size_t N,
            class = std::enable_if_t<(extent == dynamic_extent || extent == N)> >
  constexpr span(const std::array<value_type, N>& arr) noexcept
      : span(dtl::data(arr), N) {}

  template <class Container, class = std::enable_if_t<std::is_convertible<
                                 decltype(dtl::size(std::declval<const Container&>()),
                                          dtl::data(std::declval<const Container&>())),
                                 pointer>::value> >
  constexpr span(const Container& cont) : span(dtl::data(cont), dtl::size(cont)) {}

  template <class Container, class = std::enable_if_t<std::is_convertible<
                                 decltype(dtl::size(std::declval<Container&>()),
                                          dtl::data(std::declval<Container&>())),
                                 pointer>::value> >
  constexpr span(Container& cont) : span(dtl::data(cont), dtl::size(cont)) {}

  template <class U, std::size_t N,
            class = std::enable_if_t<((extent == dynamic_extent || extent == N) &&
                                      std::is_convertible<U, element_type>::value)> >
  constexpr span(const span<U, N>& s) noexcept : span(s.data(), s.size()) {}

  template <class U, std::size_t N,
            class = std::enable_if_t<((extent == dynamic_extent || extent == N) &&
                                      std::is_convertible<U, element_type>::value)> >
  constexpr span(span<U, N>& s) noexcept : span(s.data(), s.size()) {}

  constexpr span(const span& other) noexcept = default;

  constexpr iterator begin() { return base::data(); }
  constexpr const_iterator begin() const { return base::data(); }
  constexpr const_iterator cbegin() const { return base::data(); }

  constexpr iterator end() { return base::data() + base::size(); }
  constexpr const_iterator end() const { return base::data() + base::size(); }
  constexpr const_iterator cend() const { return base::data() + base::size(); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
  const_reverse_iterator crbegin() { return reverse_iterator(end()); }

  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { return reverse_iterator(begin()); }
  const_reverse_iterator crend() { return reverse_iterator(begin()); }

  constexpr reference front() { return *base::data(); }
  constexpr reference back() { return *(base::data() + base::size() - 1); }

  constexpr reference operator[](index_type idx) const { return base::data()[idx]; }

  constexpr std::size_t size_bytes() const noexcept {
    return base::size() * sizeof(element_type);
  }

  constexpr bool empty() const noexcept { return base::size() == 0; }

  template <std::size_t Count>
  constexpr span<element_type, Count> first() const {
    assert(Count <= base::size());
    return span<element_type, Count>(base::data(), Count);
  }

  constexpr span<element_type, dynamic_extent> first(std::size_t count) const {
    assert(count <= base::size());
    return span<element_type, dynamic_extent>(base::data(), count);
  }

  template <std::size_t Count>
  constexpr span<element_type, Count> last() const {
    assert(Count <= base::size());
    return span<element_type, Count>(base::data() + base::size() - Count, Count);
  }

  constexpr span<element_type, dynamic_extent> last(std::size_t count) const {
    assert(count <= base::size());
    return span<element_type, dynamic_extent>(base::data() + base::size() - count, count);
  }

  template <std::size_t Offset, std::size_t Count = dynamic_extent>
  constexpr span<element_type,
                 (Count != dynamic_extent
                      ? Count
                      : (extent != dynamic_extent ? extent - Offset : dynamic_extent))>
  subspan() const {
    assert(Offset <= base::size());
    constexpr std::size_t E =
        (Count != dynamic_extent
             ? Count
             : (extent != dynamic_extent ? extent - Offset : dynamic_extent));
    assert(E == dynamic_extent || E <= base::size());
    return span<element_type, E>(base::data() + Offset,
                                 Count == dynamic_extent ? base::size() - Offset : Count);
  }

  constexpr span<element_type, dynamic_extent> subspan(
      std::size_t offset, std::size_t count = dynamic_extent) const {
    assert(offset <= base::size());
    const std::size_t s = count == dynamic_extent ? base::size() - offset : count;
    assert(s <= base::size());
    return span<element_type, dynamic_extent>(base::data() + offset, s);
  }
};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

#include <boost/histogram/detail/nonmember_container_access.hpp>
#include <utility>

namespace boost {
namespace histogram {
namespace detail {

namespace dtl = ::boost::histogram::detail;

template <class T>
auto make_span(T* begin, T* end) {
  return dtl::span<T>{begin, end};
}

template <class T>
auto make_span(T* begin, std::size_t size) {
  return dtl::span<T>{begin, size};
}

template <class Container, class = decltype(dtl::size(std::declval<Container>()),
                                            dtl::data(std::declval<Container>()))>
auto make_span(const Container& cont) {
  return make_span(dtl::data(cont), dtl::size(cont));
}

template <class T, std::size_t N>
auto make_span(T (&arr)[N]) {
  return dtl::span<T, N>(arr, N);
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* span.hpp
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
*/