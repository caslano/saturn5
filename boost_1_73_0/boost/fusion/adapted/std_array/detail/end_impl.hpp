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
PQXyXMI9J3gOMYzRO6YCSI6Gmzieb8PGsBq8GDaGzWBL2Bx2gq1gD9gW9oXdYC7sAefBXvAM7A29tpwxI+9vGDyXF3q1fHqQ4HzwRZQ3h5dquetizsSlLlHzUUhLNd85Bv/CLrAq7ArbwR5wCOwJpX02Z9NSV6s75ZBCdedCG3/CZjAJNoctYUvYBbaCE2BbOBW2gwvhpXAJ7AjXwE7wr7AzfBZ2hTthd6j1k54TyzOX+ukb
*/