/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_SUPPORT_DEDUCE_HPP_INCLUDED)
#define BOOST_FUSION_SUPPORT_DEDUCE_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/ref.hpp>

#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL
#include <functional>
#endif

namespace boost { namespace fusion { namespace traits
{
    template <typename T> struct deduce;

    //----- ---- --- -- - -  -   -

    // Non-references pass unchanged

    template <typename T>
    struct deduce
    {
        typedef T type; 
    };

    template <typename T>
    struct deduce<T const>
    {
        typedef T type;
    };

    template <typename T>
    struct deduce<T volatile>
    {
        typedef T type;
    };

    template <typename T>
    struct deduce<T const volatile>
    {
        typedef T type;
    };

    // Keep references on mutable LValues

    template <typename T>
    struct deduce<T &>
    {
        typedef T & type;
    };

    template <typename T>
    struct deduce<T volatile&>
    {
        typedef T volatile& type;
    };

    // Store away potential RValues

    template <typename T>
    struct deduce<T const&>
    {
        typedef T type;
    };

    template <typename T>
    struct deduce<T const volatile&>
    {
        typedef T type;
    };

    // Unwrap Boost.RefS (referencee cv is deduced)

    template <typename T>
    struct deduce<reference_wrapper<T> & >
    {
        typedef T& type;
    };

    template <typename T>
    struct deduce<reference_wrapper<T> const & >
    {
        typedef T& type;
    };

    // Also unwrap C++11 std::ref if available (referencee cv is deduced)
#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL
    template <typename T>
    struct deduce<std::reference_wrapper<T> &>
    {
        typedef T& type;
    };

    template <typename T>
    struct deduce<std::reference_wrapper<T> const &>
    {
        typedef T& type;
    };
#endif

    // Keep references on arrays, even if const

    template <typename T, int N>
    struct deduce<T(&)[N]>
    {
        typedef T(&type)[N];
    };

    template <typename T, int N>
    struct deduce<volatile T(&)[N]>
    {
        typedef volatile T(&type)[N]; 
    };

    template <typename T, int N>
    struct deduce<const T(&)[N]>
    {
        typedef const T(&type)[N];
    };

    template <typename T, int N>
    struct deduce<const volatile T(&)[N]>
    {
        typedef const volatile T(&type)[N];
    };

}}}

#endif


/* deduce.hpp
x7Kyh4H4qs/nzHoQJhytCetBjy8pS2FCvTVqO8qLz+rZUebIBoRGZEAI6VLKIqz7SW97Iz+WZtgovb4qVqNcs5uVxSixTrd8ynp1Nnp1NFVrWlelWlcr1Tq7ASuL7QxSpHeE0p+xjp3NOnb73dSxWUi11ax+89T12xT1u8hZ4Z1/mUnZFTQjTJEGeOHTkWItswBUdPXzxhWt1louG0vu774sVsFFfSH35ok7lc6whUptQhfXvXN967Mie6M+esKlT3lPKP8F7wk3VrKS2qouqeYoqQV6++dYN4gSloxQd4P8LN3SwSrwFLqmRCobx/SVOluUYswOdut3Gyh6mNdFhignI8LIzU7T7bYrB8a22l01H0WlzTJmppJ7ZvgQyTbxTI3MLXKqy9TPZMH2wQ5Wl3FSgR9jX/n23NBJ6QFblR7wtpVV51YrbIllaIkjrsin82fchvjsCjblCzMt1VYkUqtntti9w9WV2uC7pzd5zQ50o2nLb58Xc9qSyGsizbgm5ruP3Glyodl2Z3QYprn7aPm2OzYbWK4xNkYU88BA5mdm54kxai3ZxJ0jk9zH/LRiMTJj1nAfrV1X44wxVdoZuwxaCJkK2WpTxkXFdLh7XWGREpbgCCknh/FJXXuNF5MKtaqpvVg1ltF4sUnd/apqLybAftV4sR1yA05qbGJkgXsrxtgm9tfppxuuorjhih2raxKht5nmqXt2Alky
*/