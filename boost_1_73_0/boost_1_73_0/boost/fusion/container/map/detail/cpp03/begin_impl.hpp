/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct begin_impl;

    template <>
    struct begin_impl<map_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    map_iterator_tag
                  , typename Seq::category
                  , Seq
                  , 0
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* begin_impl.hpp
GFCz0GtS7QYfCx2AkRItnG8T+C/714gjC+lPKgr8G1GPSYnXrg8TzkTJkvQICguVYNmS+cRTB6L64qpxWW+A9WfgEdTlnOgm1T3pAJ5FC5JeYVznellkMi238pKQzGqMVJk5ly80/qAueLMjiHrx1q0UUBi6Ieik5Gou5qpjzqV4KrI/FAiB7z0wy+NhjMnsuGe4wSwSXbXqJ8reJW/XRH4Vb2DY06kCL6+kTXUjgn33d317koG3DdyZ6HEiDmyT9uhlhsbJ8VedM5Iev7YcoH3qAc+cVbYrVxRZ03lEx/zimJVlR4swId2jfWRglG7hOIICjcZqMFGAh2yeNCmrIecVayAIJ4OGQmeDblHhCZz4TYE3oRJEMZ9GjeRaAs1NcdtUDAM8+jDN9GwT8K71cSU+PiFGtZLkGFHqDEVJP1XQGm0oWI8tLEA34VkWD2ydWNkgkmGi/MpFGcjEIicVeBDNLsvDs6JymzyumHfikTTk91M8Ku9IajYlQ4uNKdIsGq93kgHm+SGi/NsQr8smqDTlCEXI+FHkWSm5VOb9r6pu8GPg7OdlRQgHM0EdRQLLmpGfOPzMc3HmKJ4qziur051D7eAwjfJdteomNnqCPe0J8+OebgPXedr7dHpIPz6Kn9Ho6cLeu4TtcoBF
*/