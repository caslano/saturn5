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
WMd7mWZjJsjL/xGtH51/pPlmevyJo/hYKa0QuWvp7xcbmnyjik/T1JEW8Vh2RIyHu57/kevAqI+oKnBHdxH363si4TlU10LbL479fIdkzIn9f1rMOPe7r4Murtgk3F8cnD6vi8tzc5W/ue3UhmuWv/H+h8RwS2Nl/jvAjRmZ/9VzNNpuQbePG2u/BrkfZ35TqGMHPnS/ha32dhuGNyOgod8efNAgbF30NH2OhiMHCxvVMPidhY2nML7/Y35zgd8XN/Qjml6Vf40OZ6YwU8Mw8MO7FR8L73Z00w8glVIVLW6Ucd5e4wOpXoTrZM7uT79nj5zrdUd9+6ijtD/ZG/i2v58RnH82dc8MPji61cfdvVvj6L6iwd2jm2QdSr/wSzbhnF3e0o+wEKzu17m6D1+3JgLfaRoEcDQI4U+N0gPeit4K8OCmgXOe1kSPQQ7HsfBRgYPcrRcbeluLXhTg3G+jRwzc9fNRA3dlnGng4Rw4zeoFfQO9AGe9fFxcL8ChVygfcCW/s2/+9mMhqUxF5sXJjv8cReOydbveRDhjJUC/74q56rnfPwX370iOZHD0zrmriHmf/dBVrqko3DFREP8s8kyBwyKd/cbT/lZ3GQaiceKePK/p3tG9u/Wdm3+ApqM3cPerFzxj98GGovLvm8kfG97sx5wjGKdWUo5vHm7WmZMWx/Wjo6mNv+9e1E1rKPCMO47XSeA69M8W9zFGyB5097DbvY8xMOjXPHy8m0csCdq7edpSDz8c3D338F49Z5nf3jv/Wi52dHWw/B8cwQ9T+5Xa1i3bPyyCH+7MP3F4G/PPp0b98xGZz+BALrwTbXHsZ4+kNr6fPYr9DHjG9UnfGKfm4mrAf44zi/vcV93v07C1gD3y3l2IYRZ2MmDvx17g8Qss7NGATYHuVKJ7PGD/Bs3Gwy1so8CuIrot0raXYNsA2w26d+6wsCeL3PJhFvYUaftQaXtqW+NzoFLYpZ5V1f9UR5/hHmWPM06POxS+tWpS3h/zgVniLfeOpB/LIeNJh9qPfeVKmN/UovP/1PSN4TNGMK0TfABdy34nrpv2YptLjcFmvY43gjaVJ0p1UxuYga5a4GR5oq6/n8eDyUkt3yhMg47eXRA67MHyM+ZXMMx9IMMHgVWd/Dn7OMHpdybwJqbuH8UI8A9pMl/eK/bcALotbc9b8NJ/RuLo2VE7Qgex40S60azlm0mJ8M/sNncytJ20LLOXP6fb36/CFtpeoPFliAVzjWn1aTTXkJ9nxwTBA55XnUkPQ+sVMKJ6zfO7hZe2uR7e3O7qBOl8rkOzL1/Wg2Pw5xm86pEow/t44HG/QJM8afuG2NuEL/Jp1HUi4nEB8FUMEYvQw2zzueebPkN/bw80yTjvXPSlgc0TY/Nuf37oEVVcjP9flPE2tlG3hLKniu35+cXGTkpxbeVlvn5oikHVEqB/ODfA3lv7ns/zRg+1ahzxyWaFvJL6xrx5j8VzqlhSpmcfe7VvN+OP2nbLAl/EUXDjQKohz9vXBmNfrTH+dR7eroe+/qmGRr83BPoBnw3swXa/NzAxQF73Dd5KX9jG+77Q3LzO27Fc5VVhHH9TVO6bjY+dNoAqMA7Rs3qEfVProoDG/VbtrS7eXBaYmQGXxL73/rY4Hb4FrkyViorWzrHLorSgIT9+R0DjfvP2zhCfZAEJjNI4fxVo3ow4v0Lti9qM8xOT+F+uMIn3tiLje3k0zr9P1Wg26UaoGSpOzh7umhRvMHeualuPUiF8P/PKaI54rZaBBkaOJx+T1oP/GhwAr9bUO0FJR3pF7mVeHdXrw2KbiYLo1eY+UsupthiHD0TH4Totq0rj0PY+XstLsG2N5WTXRutAH9c=
*/