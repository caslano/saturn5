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
U/1lhST5DN0fKq7weoCpEdxpfU6O4SCtz3BktJLe1iu6T5IDzK3ISfo3IuVVQrd40mn2+hNZ7xrxqdBwNDmG8fPnP8EpPDl7cubAOasELyHSvFrz5pMDrzJz8kvBbm9dxV87wDWw0n0AGBdCgZK53rKGA96XIuWV4hkwBRlXaSPW+ENUoAsOuSg5TGbzq2D61oFtIdKix9nJFlQh2zKDgt1waHjKxU0HU7NGg8wRAfEzoTRitlrIykXzHDRvNqqHISdYqSSwGyZKtkZzTEOhda1ejEZp25QYySiTqRqlQyrcQm8eRXWF3mzYDmStQUtoFXeA5B3YyEzkdMUU4WHdrkuhCufOLTRYZSPZgOJl2cOhquCqC4FD1GfLIUmo0Xuh6aJkpcjatpCbB4KY1h4ob5sKzWFaUC6TmHgH2irjjZE3iRis9Fk2Kf9Kye58z0BW6BXYXgRBZMOaKaEc+BjEl7NlDB+9xcKbxlcwuwBvetXjvQum58gNgVYb4Ld1wxV60YDY1KXg2QPj37TTLTe+hMlyEc7mcbKchzPvHJ6CPX4Gv7YVsnr8ow12KdZUdnjmPn3mnuEB/Uo4U7tEcU0Fxi9ySSFcdAlT771vPcJcnQKvDJcyphm0dSlZZqSjq+lsHgWR9b2o0rLNOLwi
*/