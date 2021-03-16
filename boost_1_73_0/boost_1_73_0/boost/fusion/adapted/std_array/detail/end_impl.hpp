/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_END_OF_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_END_OF_IMPL_01062013_1700

#include <boost/fusion/adapted/std_array/std_array_iterator.hpp>
#include <boost/fusion/adapted/std_array/detail/array_size.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<std_array_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef typename remove_const<Sequence>::type seq_type;
                static int const size = std_array_size<seq_type>::value;
                typedef std_array_iterator<Sequence, size> type;

                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
KWwQu8oJboKz5syeuZc7DucWXCqh8KaaA5PaEu5BLxz+g4D/od/zaWIdzEFtxf5tF4Mvnqal4JoxenhN3iuCms/HS2IXuMsvi0/KjvDT/uzB8P3tc7xJS8HY2LsqwGnoy5v+VTNjDhVr8LUi1uAuwRL/tnGBS3vCLUWZY0e8Wd/Nf10zr9LGttxxuHD1HXr40h7iyy4Urq4PhGPeQv+2w+GWgQfDq85HfSTOdzyejrcTgRKHTLUlFMFUc0/k3BI=
*/