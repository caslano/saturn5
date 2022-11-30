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
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
*/