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