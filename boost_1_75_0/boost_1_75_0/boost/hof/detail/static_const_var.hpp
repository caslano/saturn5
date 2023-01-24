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
+WltwwG088DjZDX919XzOUhgSEBK1ma5K/UxCHOtzoOTvQbiB9AFPuypeRHrDkYG0oeEZWRGG7Rihx/dJbdHiEvJuRhrkP1OUHMS2W/ehsyNgBpDX4zenp+IPoYIYxm6+g7PPdTJkObewkjCazM5GbkH6+b60tGjiEDek8ZHIL+5Tx5ZgQM5PpN7i5zDBERPinurRHEJBPycAF9YljC8DpeRCsN/6ryOcjT7Hhgh6aBxf+suiEv72setc7C+bB0SNSSwpx5EhhodIxgYrS3h9i/1i3f7Di9pB+n+3sC/7jSfOy8MUDu+v9SHL91e9QWi0Grt1S1+15VsXUGZaRf0d927Ek9oRUeZBpcY9fLiDY8AghX8As9Tp4wWc2jSs/3Cn9IQ7cndoLOIf7GQH+PYfHAd9yVIJ5OWCI2Rb60iSjeVFIpVkjRvBrOAxgqlXeiiPcaZSvOB54Pqfmf8GnETNfnPz13f+z0SwGDO9DJhUmkH+iNRCY+TP+SDv44mHAnbmFp+fnEobGe6A+1O+T15pPsqWihICXQ5WRqFYzjdxlXpxpsHOZ36OngecXm0OeHergpUtpZAjy6r3Ets99i/kPOmP+qm+CoOmXzjIcQStbr1AvR1RQ2Ug/yQO47oavuRhf/xGShwYauW9XI2TG1oSj41XfNK80p667e/PlS7ovQ2TyY3Cq+mhEkVvKts1fdbZYtT42f3NIC1ek/G
*/