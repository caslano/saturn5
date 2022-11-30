/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_SPAN_HPP
#define BOOST_CORE_SPAN_HPP

#include <array>
#include <iterator>
#include <type_traits>
#include <cstddef>

namespace boost {

constexpr std::size_t dynamic_extent = static_cast<std::size_t>(-1);

template<class T, std::size_t E = dynamic_extent>
class span;

namespace detail {

template<class U, class T>
struct span_convertible {
    static constexpr bool value = std::is_convertible<U(*)[], T(*)[]>::value;
};

template<std::size_t E, std::size_t N>
struct span_capacity {
    static constexpr bool value = E == boost::dynamic_extent || E == N;
};

template<class T, std::size_t E, class U, std::size_t N>
struct span_compatible {
    static constexpr bool value = span_capacity<E, N>::value &&
        span_convertible<U, T>::value;
};

template<class T>
struct span_uncvref {
    typedef typename std::remove_cv<typename
        std::remove_reference<T>::type>::type type;
};

template<class>
struct span_is_span {
    static constexpr bool value = false;
};

template<class T, std::size_t E>
struct span_is_span<boost::span<T, E> > {
    static constexpr bool value = true;
};

template<class T>
struct span_is_array {
    static constexpr bool value = false;
};

template<class T, std::size_t N>
struct span_is_array<std::array<T, N> > {
    static constexpr bool value = true;
};

template<class, class = void>
struct span_data { };

template<class T>
struct span_data<T,
    typename std::enable_if<std::is_pointer<decltype(std::declval<T
        &>().data())>::value>::type> {
    typedef typename std::remove_pointer<decltype(std::declval<T
        &>().data())>::type type;
};

template<class, class, class = void>
struct span_has_data {
    static constexpr bool value = false;
};

template<class R, class T>
struct span_has_data<R, T, typename std::enable_if<span_convertible<typename
    span_data<R>::type, T>::value>::type> {
    static constexpr bool value = true;
};

template<class, class = void>
struct span_has_size {
    static constexpr bool value = false;
};

template<class R>
struct span_has_size<R, typename
    std::enable_if<std::is_convertible<decltype(std::declval<R&>().size()),
        std::size_t>::value>::type> {
    static constexpr bool value = true;
};

template<class R, class T>
struct span_is_range {
    static constexpr bool value = (std::is_const<T>::value ||
        std::is_lvalue_reference<R>::value) &&
        !span_is_span<typename span_uncvref<R>::type>::value &&
        !span_is_array<typename span_uncvref<R>::type>::value &&
        !std::is_array<typename span_uncvref<R>::type>::value &&
        span_has_data<R, T>::value &&
        span_has_size<R>::value;
};

template<std::size_t E, std::size_t N>
struct span_implicit {
    static constexpr bool value = E == boost::dynamic_extent ||
        N != boost::dynamic_extent;
};

template<class T, std::size_t E, class U, std::size_t N>
struct span_copyable {
    static constexpr bool value = (N == boost::dynamic_extent ||
        span_capacity<E, N>::value) && span_convertible<U, T>::value;
};

template<std::size_t E, std::size_t O>
struct span_sub {
    static constexpr std::size_t value = E == boost::dynamic_extent ?
        boost::dynamic_extent : E - O;
};

template<class T, std::size_t E>
struct span_store {
    constexpr span_store(T* p_, std::size_t) noexcept
        : p(p_) { }
    static constexpr std::size_t n = E;
    T* p;
};

template<class T>
struct span_store<T, boost::dynamic_extent> {
    constexpr span_store(T* p_, std::size_t n_) noexcept
        : p(p_)
        , n(n_) { }
    T* p;
    std::size_t n;
};

template<class T, std::size_t E>
struct span_bytes {
    static constexpr std::size_t value = sizeof(T) * E;
};

template<class T>
struct span_bytes<T, boost::dynamic_extent> {
    static constexpr std::size_t value = boost::dynamic_extent;
};

} /* detail */

template<class T, std::size_t E>
class span {
public:
    typedef T element_type;
    typedef typename std::remove_cv<T>::type value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<T*> reverse_iterator;
    typedef std::reverse_iterator<const T*> const_reverse_iterator;

    static constexpr std::size_t extent = E;

    template<std::size_t N = E,
        typename std::enable_if<N == dynamic_extent || N == 0, int>::type = 0>
    constexpr span() noexcept
        : s_(0, 0) { }

    template<class I,
        typename std::enable_if<E == dynamic_extent &&
            detail::span_convertible<I, T>::value, int>::type = 0>
    constexpr span(I* f, size_type c)
        : s_(f, c) { }

    template<class I,
        typename std::enable_if<E != dynamic_extent &&
            detail::span_convertible<I, T>::value, int>::type = 0>
    explicit constexpr span(I* f, size_type c)
        : s_(f, c) { }

    template<class I, class L,
        typename std::enable_if<E == dynamic_extent &&
            detail::span_convertible<I, T>::value, int>::type = 0>
    constexpr span(I* f, L* l)
        : s_(f, l - f) { }

    template<class I, class L,
        typename std::enable_if<E != dynamic_extent &&
            detail::span_convertible<I, T>::value, int>::type = 0>
    explicit constexpr span(I* f, L* l)
        : s_(f, l - f) { }

    template<std::size_t N,
        typename std::enable_if<detail::span_capacity<E, N>::value,
            int>::type = 0>
    constexpr span(typename std::enable_if<true, T>::type (&a)[N]) noexcept
        : s_(a, N) { }

    template<class U, std::size_t N,
        typename std::enable_if<detail::span_compatible<T, E, U, N>::value,
            int>::type = 0>
    constexpr span(std::array<U, N>& a) noexcept
        : s_(a.data(), N) { }

    template<class U, std::size_t N,
        typename std::enable_if<detail::span_compatible<T, E, const U,
            N>::value, int>::type = 0>
    constexpr span(const std::array<U, N>& a) noexcept
        : s_(a.data(), N) { }

    template<class R,
        typename std::enable_if<E == dynamic_extent &&
            detail::span_is_range<R, T>::value, int>::type = 0>
    constexpr span(R&& r) noexcept(noexcept(r.data()) && noexcept(r.size()))
        : s_(r.data(), r.size()) { }

    template<class R,
        typename std::enable_if<E != dynamic_extent &&
            detail::span_is_range<R, T>::value, int>::type = 0>
    explicit constexpr span(R&& r) noexcept(noexcept(r.data()) &&
        noexcept(r.size()))
        : s_(r.data(), r.size()) { }

    template<class U, std::size_t N,
        typename std::enable_if<detail::span_implicit<E, N>::value &&
            detail::span_copyable<T, E, U, N>::value, int>::type = 0>
    constexpr span(const span<U, N>& s) noexcept
        : s_(s.data(), s.size()) { }

    template<class U, std::size_t N,
        typename std::enable_if<!detail::span_implicit<E, N>::value &&
            detail::span_copyable<T, E, U, N>::value, int>::type = 0>
    explicit constexpr span(const span<U, N>& s) noexcept
        : s_(s.data(), s.size()) { }

    template<std::size_t C>
    constexpr span<T, C> first() const {
        static_assert(C <= E, "Count <= Extent");
        return span<T, C>(s_.p, C);
    }

    template<std::size_t C>
    constexpr span<T, C> last() const {
        static_assert(C <= E, "Count <= Extent");
        return span<T, C>(s_.p + (s_.n - C), C);
    }

    template<std::size_t O, std::size_t C = dynamic_extent>
    constexpr typename std::enable_if<C == dynamic_extent,
        span<T, detail::span_sub<E, O>::value> >::type subspan() const {
        static_assert(O <= E, "Offset <= Extent");
        return span<T, detail::span_sub<E, O>::value>(s_.p + O, s_.n - O);
    }

    template<std::size_t O, std::size_t C = dynamic_extent>
    constexpr typename std::enable_if<C != dynamic_extent,
        span<T, C> >::type subspan() const {
        static_assert(O <= E && C <= E - O,
            "Offset <= Extent && Count <= Extent - Offset");
        return span<T, C>(s_.p + O, C);
    }

    constexpr span<T, dynamic_extent> first(size_type c) const {
        return span<T, dynamic_extent>(s_.p, c);
    }

    constexpr span<T, dynamic_extent> last(size_type c) const {
        return span<T, dynamic_extent>(s_.p + (s_.n - c), c);
    }

    constexpr span<T, dynamic_extent> subspan(size_type o,
        size_type c = dynamic_extent) const {
        return span<T, dynamic_extent>(s_.p + o,
            c == dynamic_extent ? s_.n - o : c);
    }

    constexpr size_type size() const noexcept {
        return s_.n;
    }

    constexpr size_type size_bytes() const noexcept {
        return s_.n * sizeof(T);
    }

    constexpr bool empty() const noexcept {
        return s_.n == 0;
    }

    constexpr reference operator[](size_type i) const {
        return s_.p[i];
    }

    constexpr reference front() const {
        return *s_.p;
    }

    constexpr reference back() const {
        return s_.p[s_.n - 1];
    }

    constexpr pointer data() const noexcept {
        return s_.p;
    }

    constexpr iterator begin() const noexcept {
        return s_.p;
    }

    constexpr iterator end() const noexcept {
        return s_.p + s_.n;
    }

    constexpr reverse_iterator rbegin() const noexcept {
        return reverse_iterator(s_.p + s_.n);
    }

    constexpr reverse_iterator rend() const noexcept {
        return reverse_iterator(s_.p);
    }

    constexpr const_iterator cbegin() const noexcept {
        return s_.p;
    }

    constexpr const_iterator cend() const noexcept {
        return s_.p + s_.n;
    }

    constexpr const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(s_.p + s_.n);
    }

    constexpr const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(s_.p);
    }

    friend constexpr iterator begin(span s) noexcept {
        return s.begin();
    }

    friend constexpr iterator end(span s) noexcept {
        return s.end();
    }

private:
    detail::span_store<T, E> s_;
};

template<class T, std::size_t E>
constexpr std::size_t span<T, E>::extent;

#ifdef __cpp_deduction_guides
template<class I, class L>
span(I*, L) -> span<I>;

template<class T, std::size_t N>
span(T(&)[N]) -> span<T, N>;

template<class T, std::size_t N>
span(std::array<T, N>&) -> span<T, N>;

template<class T, std::size_t N>
span(const std::array<T, N>&) -> span<const T, N>;

template<class R>
span(R&&) -> span<typename detail::span_data<R>::type>;

template<class T, std::size_t E>
span(span<T, E>) -> span<T, E>;
#endif

#ifdef __cpp_lib_byte
template<class T, std::size_t E>
inline span<const std::byte, detail::span_bytes<T, E>::value>
as_bytes(span<T, E> s) noexcept
{
    return span<const std::byte, detail::span_bytes<T,
        E>::value>(reinterpret_cast<const std::byte*>(s.data()),
            s.size_bytes());
}

template<class T, std::size_t E>
inline typename std::enable_if<!std::is_const<T>::value,
    span<std::byte, detail::span_bytes<T, E>::value> >::type
as_writable_bytes(span<T, E> s) noexcept
{
    return span<std::byte, detail::span_bytes<T,
        E>::value>(reinterpret_cast<std::byte*>(s.data()), s.size_bytes());
}
#endif

} /* boost */

#endif

/* span.hpp
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
*/