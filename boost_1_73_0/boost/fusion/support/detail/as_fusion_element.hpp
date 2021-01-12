/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AS_FUSION_ELEMENT_05052005_0338)
#define FUSION_AS_FUSION_ELEMENT_05052005_0338

#include <boost/fusion/support/config.hpp>
#include <boost/ref.hpp>

#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL
#include <functional>
#endif

namespace boost { namespace fusion { namespace detail
{
    template <typename T>
    struct as_fusion_element
    {
        typedef T type;
    };

    template <typename T>
    struct as_fusion_element<reference_wrapper<T> >
    {
        typedef T& type;
    };

#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL
    template <typename T>
    struct as_fusion_element<std::reference_wrapper<T> >
    {
        typedef T& type;
    };
#endif

    template <typename T, int N>
    struct as_fusion_element<T[N]>
    {
        typedef const T(&type)[N];
    };

    template <typename T, int N>
    struct as_fusion_element<volatile T[N]>
    {
        typedef const volatile T(&type)[N];
    };

    template <typename T, int N>
    struct as_fusion_element<const volatile T[N]>
    {
        typedef const volatile T(&type)[N];
    };

}}}

#endif

/* as_fusion_element.hpp
Rd/jl/iQeGcizomdCy6VNFspehlvwT7NbZavJUapR6YnI0FqfteZatK/kzownuTcyIi7zLa5lfV3Y0NnkzTNxj50wrKf/2vkfMxaDvl8bpfux6hZZxkzqLO0+1MvkbLT2k2rrl1iSGySmy+xSMvzBrNtpc/qcfE7vZ1kNEziXoaMnLj4q9TVvCnTFWj2NqI3oro5GNDm3Sfpa10Oqu5yPOSWn8jSBjtFdvvtPux8sn7vkiey
*/