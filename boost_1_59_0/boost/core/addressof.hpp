/*
Copyright (C) 2002 Brad King (brad.king@kitware.com)
                   Douglas Gregor (gregod@cs.rpi.edu)

Copyright (C) 2002, 2008, 2013 Peter Dimov

Copyright (C) 2017 Glen Joseph Fernandes (glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_CORE_ADDRESSOF_HPP
#define BOOST_CORE_ADDRESSOF_HPP

#include <boost/config.hpp>

#if defined(BOOST_MSVC_FULL_VER) && BOOST_MSVC_FULL_VER >= 190024215
#define BOOST_CORE_HAS_BUILTIN_ADDRESSOF
#elif defined(BOOST_GCC) && BOOST_GCC >= 70000
#define BOOST_CORE_HAS_BUILTIN_ADDRESSOF
#elif defined(__has_builtin)
#if __has_builtin(__builtin_addressof)
#define BOOST_CORE_HAS_BUILTIN_ADDRESSOF
#endif
#endif

#if defined(BOOST_CORE_HAS_BUILTIN_ADDRESSOF)
#if defined(BOOST_NO_CXX11_CONSTEXPR)
#define BOOST_CORE_NO_CONSTEXPR_ADDRESSOF
#endif

namespace boost {

template<class T>
BOOST_CONSTEXPR inline T*
addressof(T& o) BOOST_NOEXCEPT
{
    return __builtin_addressof(o);
}

} /* boost */
#else
#include <boost/config/workaround.hpp>
#include <cstddef>

namespace boost {
namespace detail {

template<class T>
class addrof_ref {
public:
    BOOST_FORCEINLINE addrof_ref(T& o) BOOST_NOEXCEPT
        : o_(o) { }
    BOOST_FORCEINLINE operator T&() const BOOST_NOEXCEPT {
        return o_;
    }
private:
    addrof_ref& operator=(const addrof_ref&);
    T& o_;
};

template<class T>
struct addrof {
    static BOOST_FORCEINLINE T* get(T& o, long) BOOST_NOEXCEPT {
        return reinterpret_cast<T*>(&
            const_cast<char&>(reinterpret_cast<const volatile char&>(o)));
    }
    static BOOST_FORCEINLINE T* get(T* p, int) BOOST_NOEXCEPT {
        return p;
    }
};

#if !defined(BOOST_NO_CXX11_NULLPTR)
#if !defined(BOOST_NO_CXX11_DECLTYPE) && \
    (defined(__INTEL_COMPILER) || \
        (defined(__clang__) && !defined(_LIBCPP_VERSION)))
typedef decltype(nullptr) addrof_null_t;
#else
typedef std::nullptr_t addrof_null_t;
#endif

template<>
struct addrof<addrof_null_t> {
    typedef addrof_null_t type;
    static BOOST_FORCEINLINE type* get(type& o, int) BOOST_NOEXCEPT {
        return &o;
    }
};

template<>
struct addrof<const addrof_null_t> {
    typedef const addrof_null_t type;
    static BOOST_FORCEINLINE type* get(type& o, int) BOOST_NOEXCEPT {
        return &o;
    }
};

template<>
struct addrof<volatile addrof_null_t> {
    typedef volatile addrof_null_t type;
    static BOOST_FORCEINLINE type* get(type& o, int) BOOST_NOEXCEPT {
        return &o;
    }
};

template<>
struct addrof<const volatile addrof_null_t> {
    typedef const volatile addrof_null_t type;
    static BOOST_FORCEINLINE type* get(type& o, int) BOOST_NOEXCEPT {
        return &o;
    }
};
#endif

} /* detail */

#if defined(BOOST_NO_CXX11_SFINAE_EXPR) || \
    defined(BOOST_NO_CXX11_CONSTEXPR) || \
    defined(BOOST_NO_CXX11_DECLTYPE)
#define BOOST_CORE_NO_CONSTEXPR_ADDRESSOF

template<class T>
BOOST_FORCEINLINE T*
addressof(T& o) BOOST_NOEXCEPT
{
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x610)) || \
    BOOST_WORKAROUND(__SUNPRO_CC, <= 0x5120)
    return boost::detail::addrof<T>::get(o, 0);
#else
    return boost::detail::addrof<T>::get(boost::detail::addrof_ref<T>(o), 0);
#endif
}

#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x590))
namespace detail {

template<class T>
struct addrof_result {
    typedef T* type;
};

} /* detail */

template<class T, std::size_t N>
BOOST_FORCEINLINE typename boost::detail::addrof_result<T[N]>::type
addressof(T (&o)[N]) BOOST_NOEXCEPT
{
    return &o;
}
#endif

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
template<class T, std::size_t N>
BOOST_FORCEINLINE
T (*addressof(T (&o)[N]) BOOST_NOEXCEPT)[N]
{
   return reinterpret_cast<T(*)[N]>(&o);
}

template<class T, std::size_t N>
BOOST_FORCEINLINE
const T (*addressof(const T (&o)[N]) BOOST_NOEXCEPT)[N]
{
   return reinterpret_cast<const T(*)[N]>(&o);
}
#endif
#else
namespace detail {

template<class T>
T addrof_declval() BOOST_NOEXCEPT;

template<class>
struct addrof_void {
    typedef void type;
};

template<class T, class E = void>
struct addrof_member_operator {
    static constexpr bool value = false;
};

template<class T>
struct addrof_member_operator<T, typename
    addrof_void<decltype(addrof_declval<T&>().operator&())>::type> {
    static constexpr bool value = true;
};

#if BOOST_WORKAROUND(BOOST_INTEL, < 1600)
struct addrof_addressable { };

addrof_addressable*
operator&(addrof_addressable&) BOOST_NOEXCEPT;
#endif

template<class T, class E = void>
struct addrof_non_member_operator {
    static constexpr bool value = false;
};

template<class T>
struct addrof_non_member_operator<T, typename
    addrof_void<decltype(operator&(addrof_declval<T&>()))>::type> {
    static constexpr bool value = true;
};

template<class T, class E = void>
struct addrof_expression {
    static constexpr bool value = false;
};

template<class T>
struct addrof_expression<T,
    typename addrof_void<decltype(&addrof_declval<T&>())>::type> {
    static constexpr bool value = true;
};

template<class T>
struct addrof_is_constexpr {
    static constexpr bool value = addrof_expression<T>::value &&
        !addrof_member_operator<T>::value &&
        !addrof_non_member_operator<T>::value;
};

template<bool E, class T>
struct addrof_if { };

template<class T>
struct addrof_if<true, T> {
    typedef T* type;
};

template<class T>
BOOST_FORCEINLINE
typename addrof_if<!addrof_is_constexpr<T>::value, T>::type
addressof(T& o) BOOST_NOEXCEPT
{
    return addrof<T>::get(addrof_ref<T>(o), 0);
}

template<class T>
constexpr BOOST_FORCEINLINE
typename addrof_if<addrof_is_constexpr<T>::value, T>::type
addressof(T& o) BOOST_NOEXCEPT
{
    return &o;
}

} /* detail */

template<class T>
constexpr BOOST_FORCEINLINE T*
addressof(T& o) BOOST_NOEXCEPT
{
    return boost::detail::addressof(o);
}
#endif

} /* boost */
#endif

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && \
    !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)
namespace boost {

template<class T>
const T* addressof(const T&&) = delete;

} /* boost */
#endif

#endif

/* addressof.hpp
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
*/