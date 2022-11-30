/*
Copyright 2020-2021 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_ALLOCATOR_ACCESS_HPP
#define BOOST_CORE_ALLOCATOR_ACCESS_HPP

#include <boost/config.hpp>
#include <boost/core/pointer_traits.hpp>
#include <limits>
#include <new>
#if !defined(BOOST_NO_CXX11_ALLOCATOR)
#include <type_traits>
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

#if defined(BOOST_GCC_VERSION) && (BOOST_GCC_VERSION >= 40300)
#define BOOST_DETAIL_ALLOC_EMPTY(T) __is_empty(T)
#elif defined(BOOST_INTEL) && defined(_MSC_VER) && (_MSC_VER >= 1500)
#define BOOST_DETAIL_ALLOC_EMPTY(T) __is_empty(T)
#elif defined(BOOST_MSVC) && (BOOST_MSVC >= 1400)
#define BOOST_DETAIL_ALLOC_EMPTY(T) __is_empty(T)
#elif defined(BOOST_CLANG) && !defined(__CUDACC__)
#if __has_feature(is_empty)
#define BOOST_DETAIL_ALLOC_EMPTY(T) __is_empty(T)
#endif
#elif defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x5130)
#define BOOST_DETAIL_ALLOC_EMPTY(T) __oracle_is_empty(T)
#elif defined(__ghs__) && (__GHS_VERSION_NUMBER >= 600)
#define BOOST_DETAIL_ALLOC_EMPTY(T) __is_empty(T)
#elif defined(BOOST_CODEGEARC)
#define BOOST_DETAIL_ALLOC_EMPTY(T) __is_empty(T)
#endif

#if defined(_LIBCPP_SUPPRESS_DEPRECATED_PUSH)
_LIBCPP_SUPPRESS_DEPRECATED_PUSH
#endif
#if defined(_STL_DISABLE_DEPRECATED_WARNING)
_STL_DISABLE_DEPRECATED_WARNING
#endif
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4996)
#endif

namespace boost {

template<class A>
struct allocator_value_type {
    typedef typename A::value_type type;
};

namespace detail {

template<class A, class = void>
struct alloc_ptr {
    typedef typename boost::allocator_value_type<A>::type* type;
};

template<class>
struct alloc_void {
    typedef void type;
};

template<class A>
struct alloc_ptr<A,
    typename alloc_void<typename A::pointer>::type> {
    typedef typename A::pointer type;
};

} /* detail */

template<class A>
struct allocator_pointer {
    typedef typename detail::alloc_ptr<A>::type type;
};

namespace detail {

template<class A, class = void>
struct alloc_const_ptr {
    typedef typename boost::pointer_traits<typename
        boost::allocator_pointer<A>::type>::template rebind_to<const typename
            boost::allocator_value_type<A>::type>::type type;
};

template<class A>
struct alloc_const_ptr<A,
    typename alloc_void<typename A::const_pointer>::type> {
    typedef typename A::const_pointer type;
};

} /* detail */

template<class A>
struct allocator_const_pointer {
    typedef typename detail::alloc_const_ptr<A>::type type;
};

namespace detail {

template<class, class>
struct alloc_to { };

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
template<template<class> class A, class T, class U>
struct alloc_to<A<U>, T> {
    typedef A<T> type;
};

template<template<class, class> class A, class T, class U, class V>
struct alloc_to<A<U, V>, T> {
    typedef A<T, V> type;
};

template<template<class, class, class> class A, class T, class U, class V1,
    class V2>
struct alloc_to<A<U, V1, V2>, T> {
    typedef A<T, V1, V2> type;
};
#else
template<template<class, class...> class A, class T, class U, class... V>
struct alloc_to<A<U, V...>, T> {
    typedef A<T, V...> type;
};
#endif

template<class A, class T, class = void>
struct alloc_rebind {
    typedef typename alloc_to<A, T>::type type;
};

template<class A, class T>
struct alloc_rebind<A, T,
    typename alloc_void<typename A::template rebind<T>::other>::type> {
    typedef typename A::template rebind<T>::other type;
};

} /* detail */

template<class A, class T>
struct allocator_rebind {
    typedef typename detail::alloc_rebind<A, T>::type type;
};

namespace detail {

template<class A, class = void>
struct alloc_void_ptr {
     typedef typename boost::pointer_traits<typename
        boost::allocator_pointer<A>::type>::template
            rebind_to<void>::type type;
};

template<class A>
struct alloc_void_ptr<A,
    typename alloc_void<typename A::void_pointer>::type> {
    typedef typename A::void_pointer type;
};

} /* detail */

template<class A>
struct allocator_void_pointer {
    typedef typename detail::alloc_void_ptr<A>::type type;
};

namespace detail {

template<class A, class = void>
struct alloc_const_void_ptr {
     typedef typename boost::pointer_traits<typename
        boost::allocator_pointer<A>::type>::template
            rebind_to<const void>::type type;
};

template<class A>
struct alloc_const_void_ptr<A,
    typename alloc_void<typename A::const_void_pointer>::type> {
    typedef typename A::const_void_pointer type;
};

} /* detail */

template<class A>
struct allocator_const_void_pointer {
    typedef typename detail::alloc_const_void_ptr<A>::type type;
};

namespace detail {

template<class A, class = void>
struct alloc_diff_type {
    typedef typename boost::pointer_traits<typename
        boost::allocator_pointer<A>::type>::difference_type type;
};

template<class A>
struct alloc_diff_type<A,
    typename alloc_void<typename A::difference_type>::type> {
    typedef typename A::difference_type type;
};

} /* detail */

template<class A>
struct allocator_difference_type {
    typedef typename detail::alloc_diff_type<A>::type type;
};

namespace detail {

#if defined(BOOST_NO_CXX11_ALLOCATOR)
template<class A, class = void>
struct alloc_size_type {
    typedef std::size_t type;
};
#else
template<class A, class = void>
struct alloc_size_type {
    typedef typename std::make_unsigned<typename
        boost::allocator_difference_type<A>::type>::type type;
};
#endif

template<class A>
struct alloc_size_type<A,
    typename alloc_void<typename A::size_type>::type> {
    typedef typename A::size_type type;
};

} /* detail */

template<class A>
struct allocator_size_type {
    typedef typename detail::alloc_size_type<A>::type type;
};

namespace detail {

#if defined(BOOST_NO_CXX11_ALLOCATOR)
template<bool V>
struct alloc_bool {
    typedef bool value_type;
    typedef alloc_bool type;

    static const bool value = V;

    operator bool() const BOOST_NOEXCEPT {
        return V;
    }

    bool operator()() const BOOST_NOEXCEPT {
        return V;
    }
};

template<bool V>
const bool alloc_bool<V>::value;

typedef alloc_bool<false> alloc_false;
#else
typedef std::false_type alloc_false;
#endif

template<class A, class = void>
struct alloc_pocca {
    typedef alloc_false type;
};

template<class A>
struct alloc_pocca<A,
    typename alloc_void<typename
        A::propagate_on_container_copy_assignment>::type> {
    typedef typename A::propagate_on_container_copy_assignment type;
};

} /* detail */

template<class A, class = void>
struct allocator_propagate_on_container_copy_assignment {
    typedef typename detail::alloc_pocca<A>::type type;
};

namespace detail {

template<class A, class = void>
struct alloc_pocma {
    typedef alloc_false type;
};

template<class A>
struct alloc_pocma<A,
    typename alloc_void<typename
        A::propagate_on_container_move_assignment>::type> {
    typedef typename A::propagate_on_container_move_assignment type;
};

} /* detail */

template<class A>
struct allocator_propagate_on_container_move_assignment {
    typedef typename detail::alloc_pocma<A>::type type;
};

namespace detail {

template<class A, class = void>
struct alloc_pocs {
    typedef alloc_false type;
};

template<class A>
struct alloc_pocs<A,
    typename alloc_void<typename A::propagate_on_container_swap>::type> {
    typedef typename A::propagate_on_container_swap type;
};

} /* detail */

template<class A>
struct allocator_propagate_on_container_swap {
    typedef typename detail::alloc_pocs<A>::type type;
};

namespace detail {

#if !defined(BOOST_NO_CXX11_ALLOCATOR)
template<class A, class = void>
struct alloc_equal {
    typedef typename std::is_empty<A>::type type;
};
#elif defined(BOOST_DETAIL_ALLOC_EMPTY)
template<class A, class = void>
struct alloc_equal {
    typedef alloc_bool<BOOST_DETAIL_ALLOC_EMPTY(A)> type;
};
#else
template<class A, class = void>
struct alloc_equal {
    typedef alloc_false type;
};
#endif

template<class A>
struct alloc_equal<A,
    typename alloc_void<typename A::is_always_equal>::type> {
    typedef typename A::is_always_equal type;
};

} /* detail */

template<class A>
struct allocator_is_always_equal {
    typedef typename detail::alloc_equal<A>::type type;
};

template<class A>
inline typename allocator_pointer<A>::type
allocator_allocate(A& a, typename allocator_size_type<A>::type n)
{
    return a.allocate(n);
}

template<class A>
inline void
allocator_deallocate(A& a, typename allocator_pointer<A>::type p,
    typename allocator_size_type<A>::type n)
{
    a.deallocate(p, n);
}

#if defined(BOOST_NO_CXX11_ALLOCATOR)
template<class A>
inline typename allocator_pointer<A>::type
allocator_allocate(A& a, typename allocator_size_type<A>::type n,
    typename allocator_const_void_pointer<A>::type h)
{
    return a.allocate(n, h);
}
#else
namespace detail {

template<class>
struct alloc_no {
    char x, y;
};

template<class A>
class alloc_has_allocate {
    template<class O>
    static auto check(int)
    -> alloc_no<decltype(std::declval<O&>().allocate(std::declval<typename
        boost::allocator_size_type<A>::type>(), std::declval<typename
            boost::allocator_const_void_pointer<A>::type>()))>;

    template<class>
    static char check(long);

public:
    BOOST_STATIC_CONSTEXPR bool value = sizeof(check<A>(0)) > 1;
};

} /* detail */

template<class A>
inline typename std::enable_if<detail::alloc_has_allocate<A>::value,
    typename allocator_pointer<A>::type>::type
allocator_allocate(A& a, typename allocator_size_type<A>::type n,
    typename allocator_const_void_pointer<A>::type h)
{
    return a.allocate(n, h);
}

template<class A>
inline typename std::enable_if<!detail::alloc_has_allocate<A>::value,
    typename allocator_pointer<A>::type>::type
allocator_allocate(A& a, typename allocator_size_type<A>::type n,
    typename allocator_const_void_pointer<A>::type)
{
    return a.allocate(n);
}
#endif

#if defined(BOOST_NO_CXX11_ALLOCATOR)
template<class A, class T>
inline void
allocator_construct(A&, T* p)
{
    ::new((void*)p) T();
}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
template<class A, class T, class V, class... Args>
inline void
allocator_construct(A&, T* p, V&& v, Args&&... args)
{
    ::new((void*)p) T(std::forward<V>(v), std::forward<Args>(args)...);
}
#else
template<class A, class T, class V>
inline void
allocator_construct(A&, T* p, V&& v)
{
    ::new((void*)p) T(std::forward<V>(v));
}
#endif
#else
template<class A, class T, class V>
inline void
allocator_construct(A&, T* p, const V& v)
{
    ::new((void*)p) T(v);
}

template<class A, class T, class V>
inline void
allocator_construct(A&, T* p, V& v)
{
    ::new((void*)p) T(v);
}
#endif
#else
namespace detail {

template<class A, class T, class... Args>
class alloc_has_construct {
    template<class O>
    static auto check(int)
    -> alloc_no<decltype(std::declval<O&>().construct(std::declval<T*>(),
        std::declval<Args&&>()...))>;

    template<class>
    static char check(long);

public:
    BOOST_STATIC_CONSTEXPR bool value = sizeof(check<A>(0)) > 1;
};

} /* detail */

template<class A, class T, class... Args>
inline typename std::enable_if<detail::alloc_has_construct<A, T,
    Args...>::value>::type
allocator_construct(A& a, T* p, Args&&... args)
{
    a.construct(p, std::forward<Args>(args)...);
}

template<class A, class T, class... Args>
inline typename std::enable_if<!detail::alloc_has_construct<A, T,
    Args...>::value>::type
allocator_construct(A&, T* p, Args&&... args)
{
    ::new((void*)p) T(std::forward<Args>(args)...);
}
#endif

#if defined(BOOST_NO_CXX11_ALLOCATOR)
template<class A, class T>
inline void
allocator_destroy(A&, T* p)
{
    p->~T();
    (void)p;
}
#else
namespace detail {

template<class A, class T>
class alloc_has_destroy {
    template<class O>
    static auto check(int)
    -> alloc_no<decltype(std::declval<O&>().destroy(std::declval<T*>()))>;

    template<class>
    static char check(long);

public:
    BOOST_STATIC_CONSTEXPR bool value = sizeof(check<A>(0)) > 1;
};

} /* detail */

template<class A, class T>
inline typename std::enable_if<detail::alloc_has_destroy<A, T>::value>::type
allocator_destroy(A& a, T* p)
{
    a.destroy(p);
}

template<class A, class T>
inline typename std::enable_if<!detail::alloc_has_destroy<A, T>::value>::type
allocator_destroy(A&, T* p)
{
    p->~T();
    (void)p;
}
#endif

namespace detail {

#if defined(BOOST_NO_CXX11_ALLOCATOR)
template<class T, T>
struct alloc_no {
    char x, y;
};

template<class A>
class alloc_has_max_size {
    template<class O>
    static alloc_no<typename boost::allocator_size_type<O>::type(O::*)(),
        &O::max_size> check(int);

    template<class O>
    static alloc_no<typename boost::allocator_size_type<O>::type(O::*)() const,
        &O::max_size> check(int);

    template<class O>
    static alloc_no<typename boost::allocator_size_type<O>::type(*)(),
        &O::max_size> check(int);

    template<class>
    static char check(long);

public:
    BOOST_STATIC_CONSTEXPR bool value = sizeof(check<A>(0)) > 1;
};
#else
template<class A>
class alloc_has_max_size {
    template<class O>
    static auto check(int)
    -> alloc_no<decltype(std::declval<const O&>().max_size())>;

    template<class>
    static char check(long);

public:
    BOOST_STATIC_CONSTEXPR bool value = sizeof(check<A>(0)) > 1;
};
#endif

template<bool, class>
struct alloc_if { };

template<class T>
struct alloc_if<true, T> {
    typedef T type;
};

} /* detail */

template<class A>
inline typename detail::alloc_if<detail::alloc_has_max_size<A>::value,
    typename allocator_size_type<A>::type>::type
allocator_max_size(const A& a) BOOST_NOEXCEPT
{
    return a.max_size();
}

template<class A>
inline typename detail::alloc_if<!detail::alloc_has_max_size<A>::value,
    typename allocator_size_type<A>::type>::type
allocator_max_size(const A&) BOOST_NOEXCEPT
{
    return (std::numeric_limits<typename
        allocator_size_type<A>::type>::max)() /
            sizeof(typename allocator_value_type<A>::type);
}

namespace detail {

#if defined(BOOST_NO_CXX11_ALLOCATOR)
template<class A>
class alloc_has_soccc {
    template<class O>
    static alloc_no<O(O::*)(), &O::select_on_container_copy_construction>
    check(int);

    template<class O>
    static alloc_no<O(O::*)() const, &O::select_on_container_copy_construction>
    check(int);

    template<class O>
    static alloc_no<O(*)(), &O::select_on_container_copy_construction>
    check(int);

    template<class>
    static char check(long);

public:
    BOOST_STATIC_CONSTEXPR bool value = sizeof(check<A>(0)) > 1;
};
#else
template<class A>
class alloc_has_soccc {
    template<class O>
    static auto check(int) -> alloc_no<decltype(std::declval<const
        O&>().select_on_container_copy_construction())>;

    template<class>
    static char check(long);

public:
    BOOST_STATIC_CONSTEXPR bool value = sizeof(check<A>(0)) > 1;
};
#endif

} /* detail */

template<class A>
inline typename detail::alloc_if<detail::alloc_has_soccc<A>::value, A>::type
allocator_select_on_container_copy_construction(const A& a)
{
    return a.select_on_container_copy_construction();
}

template<class A>
inline typename detail::alloc_if<!detail::alloc_has_soccc<A>::value, A>::type
allocator_select_on_container_copy_construction(const A& a)
{
    return a;
}

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
template<class A>
using allocator_value_type_t = typename allocator_value_type<A>::type;

template<class A>
using allocator_pointer_t = typename allocator_pointer<A>::type;

template<class A>
using allocator_const_pointer_t = typename allocator_const_pointer<A>::type;

template<class A>
using allocator_void_pointer_t = typename allocator_void_pointer<A>::type;

template<class A>
using allocator_const_void_pointer_t =
    typename allocator_const_void_pointer<A>::type;

template<class A>
using allocator_difference_type_t =
    typename allocator_difference_type<A>::type;

template<class A>
using allocator_size_type_t = typename allocator_size_type<A>::type;

template<class A>
using allocator_propagate_on_container_copy_assignment_t =
    typename allocator_propagate_on_container_copy_assignment<A>::type;

template<class A>
using allocator_propagate_on_container_move_assignment_t =
    typename allocator_propagate_on_container_move_assignment<A>::type;

template<class A>
using allocator_propagate_on_container_swap_t =
    typename allocator_propagate_on_container_swap<A>::type;

template<class A>
using allocator_is_always_equal_t =
    typename allocator_is_always_equal<A>::type;

template<class A, class T>
using allocator_rebind_t = typename allocator_rebind<A, T>::type;
#endif

} /* boost */

#if defined(_LIBCPP_SUPPRESS_DEPRECATED_POP)
_LIBCPP_SUPPRESS_DEPRECATED_POP
#endif
#if defined(_STL_RESTORE_DEPRECATED_WARNING)
_STL_RESTORE_DEPRECATED_WARNING
#endif
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#endif

/* allocator_access.hpp
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
*/