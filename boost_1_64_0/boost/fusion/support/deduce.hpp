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
V4MaQiP7qXUnRtRxVI1kY7ziF9r9y50tnLlMNE3gdFK72V1U+1AJxBglS1BcFiGyPnffbfESQCMFZz7x1wX9dovn0r5eTmBobzbx5Wjg1morZvq1V4SIwa/f0nB02WKsK/E+sCq6hyb3vBzonfpnazHJsdvTg/26fyFjq+39w3NmHW1Ml9Lv92q8cwiqVvk8hwxhsT4KnmOhbxIdZLBMyihFc/XO5OB9KCNMzYaXRCouO0R6tOBWm+IodhVy30WUnvGDhY2p/X0eGQOOAlL9WP3DFw5CkAw8jYXybfeFEWlFQ9EEApNh+aIlSwt8eDoNTz8Fkl4DnJS+Vz67kf3shAWL8wq3x1YHsaND0IRJACHhihxRGTg5YOmkEpnvA2bXG7t+JYxK6AjeZ4L+/AFZvGHjkmqkwkOkRGZLmqe+0L9DqS4uts6ZZTgMLeiDKZIFIfqwM8jPez4BYg+ZsrHRgLF0AN+K+wx29oITS9B94rVENMvqhxJtmZiO/PVlOe/2aZq0v5rqpnNV3RUjN+59E6qYifa7iRmB/TlrZWv3Hs7Sejd1fQROdfKBxA==
*/