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
#include <boost/assert.hpp>
#include <boost/histogram/detail/non_member_container_access.hpp>
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
  constexpr span_base(T* b, std::size_t s) noexcept : begin_(b) { BOOST_ASSERT(N == s); }
  constexpr void set(T* b, std::size_t s) noexcept {
    begin_ = b;
    BOOST_ASSERT(N == s);
  }

private:
  T* begin_;
};

template <class T>
class span_base<T, dynamic_extent> {
public:
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

  template <std::size_t _ = extent,
            class = std::enable_if_t<(_ == 0 || _ == dynamic_extent)> >
  constexpr span() noexcept : base(nullptr, 0) {}

  constexpr span(pointer first, pointer last)
      : span(first, static_cast<std::size_t>(last - first)) {
    BOOST_ASSERT(extent == dynamic_extent ||
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
                                 decltype(dtl::size(std::declval<Container>()),
                                          dtl::data(std::declval<Container>())),
                                 pointer>::value> >
  constexpr span(const Container& cont) : span(dtl::data(cont), dtl::size(cont)) {}

  template <class Container, class = std::enable_if_t<std::is_convertible<
                                 decltype(dtl::size(std::declval<Container>()),
                                          dtl::data(std::declval<Container>())),
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

  constexpr reference front() { *base::data(); }
  constexpr reference back() { *(base::data() + base::size() - 1); }

  constexpr reference operator[](index_type idx) const { return base::data()[idx]; }

  constexpr std::size_t size_bytes() const noexcept {
    return base::size() * sizeof(element_type);
  }

  constexpr bool empty() const noexcept { return base::size() == 0; }

  template <std::size_t Count>
  constexpr span<element_type, Count> first() const {
    BOOST_ASSERT(Count <= base::size());
    return span<element_type, Count>(base::data(), Count);
  }

  constexpr span<element_type, dynamic_extent> first(std::size_t count) const {
    BOOST_ASSERT(count <= base::size());
    return span<element_type, dynamic_extent>(base::data(), count);
  }

  template <std::size_t Count>
  constexpr span<element_type, Count> last() const {
    BOOST_ASSERT(Count <= base::size());
    return span<element_type, Count>(base::data() + base::size() - Count, Count);
  }

  constexpr span<element_type, dynamic_extent> last(std::size_t count) const {
    BOOST_ASSERT(count <= base::size());
    return span<element_type, dynamic_extent>(base::data() + base::size() - count, count);
  }

  template <std::size_t Offset, std::size_t Count = dynamic_extent>
  constexpr span<element_type,
                 (Count != dynamic_extent
                      ? Count
                      : (extent != dynamic_extent ? extent - Offset : dynamic_extent))>
  subspan() const {
    BOOST_ASSERT(Offset <= base::size());
    constexpr std::size_t E =
        (Count != dynamic_extent
             ? Count
             : (extent != dynamic_extent ? extent - Offset : dynamic_extent));
    BOOST_ASSERT(E == dynamic_extent || E <= base::size());
    return span<element_type, E>(base::data() + Offset,
                                 Count == dynamic_extent ? base::size() - Offset : Count);
  }

  constexpr span<element_type, dynamic_extent> subspan(
      std::size_t offset, std::size_t count = dynamic_extent) const {
    BOOST_ASSERT(offset <= base::size());
    const std::size_t s = count == dynamic_extent ? base::size() - offset : count;
    BOOST_ASSERT(s <= base::size());
    return span<element_type, dynamic_extent>(base::data() + offset, s);
  }
};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

#include <boost/histogram/detail/non_member_container_access.hpp>
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