/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_ARRAY_SIZE_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_ARRAY_SIZE_01062013_1700

#include <cstddef>
#include <boost/type_traits/integral_constant.hpp>

namespace boost { namespace fusion
{
    namespace extension
    {
        template<class T>
        struct std_array_size;

        template<template<typename, std::size_t> class Array, typename T, std::size_t N>
        struct std_array_size<Array<T, N> > : boost::integral_constant<std::size_t, N> {};
    }
}}

#endif

/* array_size.hpp
zGukQ8vPOpfKo3OVJX3nYE15R26CbRHesQRsGhhfDedq2c/9lmCco94TS59hD24WyXFiPEBSMn6gIFk+2M260xcX6jynlt0X8/N3bjKOJNs+7osryxdViRfQqxbxrInCp+aHRKCfGB50waCxLuL3TXo2bfimeNxMu2UwW1i5uK4SvckRsd0RbTndMW/TfYDcpqqxFv55stjmU6qWczXu3Q50ltvAIz4uNrhG7MD9yYb4PZrW98ZXlV/pJP/aU2Q=
*/