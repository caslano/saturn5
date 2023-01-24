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
DZPt0tJu4XCFt7SUjmiAVEAGzlSWQipYD2aIpUa9A4YWrL7eWEiGQZuA/5+ChEwGZbAlDmZaLZW+CWeBh2A0vImbg5PZEZry/WjFdSpGs/VjZcmz96RCU3tL0u3ob4jl5mAfjVYyT8WwXhytXHsqlg0oFg/MpX2m2TIXWGmMp1ezL6WS31jOYyE5Eak8TjkhsWz/zkl80cIzTWMUuvNY+1mxq7aqgyJhEBedm74KKiA9MAX1F1nt7i7B60zWfwvgR01TV1wDs4Bj82FB8AKUo/wlK4xJxkJa37RU2fNbmPtQ82BMtjMgmd0vGZYSh6XUNb1i4Zk/F/DVQY9f5lczuRSQZrN/mnM127UsTemhov7+6Z73S4fGWYoHjx440Weyz5oP4M8e7GdTHuqUsLfI+VZi52keulzkk0Z/Jy2pc2hJPTvZ7zLVT3+UVJ5gTRN9nI9YZ1vKUZcv+0/wyCzTrc03mb4x4ZrNtQB6ruhGz4I/w93T8tPcLe7JmBJSQRK0fpvcotnOppQjMOVF+Z4FLWHu84InbZ2PSWMxaRepwtnSHIGTUnYb1CUnUyx/hEnTDNOZglTxLWonMuIq7hNDuqivVAFnrWp/2n3IYOSWgW21yW9Np9ugzQbLX7HDhMY43qaLr9QUTdqwMcs7rjLbN67yrPmDLnH5oi5j3Ud756ass+ZV+abGa7Zf5tHiIglnv2HImds1W/R8vvW7
*/