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
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) || \
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

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
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