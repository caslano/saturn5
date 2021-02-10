/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    static_const_var.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_STATIC_CONST_H
#define BOOST_HOF_GUARD_STATIC_CONST_H

#include <boost/hof/detail/intrinsics.hpp>

namespace boost { namespace hof { namespace detail {

template<class T>
struct static_const_storage
{
    static constexpr T value = T();
};

template<class T>
constexpr T static_const_storage<T>::value;

struct static_const_var_factory
{
    constexpr static_const_var_factory()
    {}

    template<class T>
    constexpr const T& operator=(const T&) const
    {
        static_assert(BOOST_HOF_IS_DEFAULT_CONSTRUCTIBLE(T), "Static const variable must be default constructible");
        return static_const_storage<T>::value;
    }
};
}

template<class T>
constexpr const T& static_const_var()
{
    return detail::static_const_storage<T>::value;
}


}} // namespace boost::hof

#if BOOST_HOF_HAS_RELAXED_CONSTEXPR || defined(_MSC_VER)
#define BOOST_HOF_STATIC_CONSTEXPR const constexpr
#else
#define BOOST_HOF_STATIC_CONSTEXPR static constexpr
#endif

#if defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7
#define BOOST_HOF_STATIC_AUTO_REF extern __attribute__((weak)) constexpr auto
#else
#define BOOST_HOF_STATIC_AUTO_REF static constexpr auto&
#endif

// On gcc 4.6 use weak variables
#if defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7
#define BOOST_HOF_STATIC_CONST_VAR(name) extern __attribute__((weak)) constexpr auto name
#else
#define BOOST_HOF_STATIC_CONST_VAR(name) static constexpr auto& name = boost::hof::detail::static_const_var_factory()
#endif

#define BOOST_HOF_DECLARE_STATIC_VAR(name, ...) BOOST_HOF_STATIC_CONST_VAR(name) = __VA_ARGS__{}

#endif

/* static_const_var.hpp
GL87F8/x1TsTQjXtfq8QqP+k3PV5kpp0WVM9JnS5b2fd77V8d6q9mu0Dix9k+0W6Wes40/RKrjtztp1LHztzs9/ZAPZZmufab1BLAwQKAAAACAAtZ0pS479EQf0GAABoEgAANQAJAGN1cmwtbWFzdGVyL3BhY2thZ2VzL3Ztcy9idWlsZF9jdXJsLWNvbmZpZ19zY3JpcHQuY29tVVQFAAG2SCRgvVdhb6NGE/7c91fMUUtJdMa55E79UCnSEZsktBhcwHdvVVUIw2KvgoEu6yTuq/e/d2YBG2ynyklVfReDd2eeeXZ25xkYvIPFhmdJGG9EpsdFnvJlWMWCl3IUF+v/DN7hfwhWvIIly5mIJKtArhh07EdQO0AqivXRJM8h5RkbNVDjotwKvlxJuP5w9WkIPxWrHKZRtl4wsWxsZkyseVXxIgdZwKZiQ4jRbQjrIuEpXqM8uSwEJLySgi82kmFUZFgVqXyOBIMUJ6N8S1jlRpRFxeCZyxXgMF2LDXJlDNBlxQRbbGEpolyyZAilKJ54whIEjKRaS7QonhghxTvmeSF5zIhFHbfc822nypJFAnDtUZaRJ2dVm4HgwQTfvQu+Gp4Jlg8zz/1iTcwJaIaPvzUwnIkyMubBg+vBxPLHtmFNfTBsG9DLM5zA
*/