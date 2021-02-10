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
UuO0fDMUH2rBt5bx6DfLeTpNJstosYriubcg2A7SH2lpjuPL8BYFJw+C35SR8d+UCxiiWLOdpuoISuEmy6Xm9anh876UAUQahXJJ1d5itGLpCOpD7ouhK1ThlmqjZaXs+HoGl9NrjUd3DtRYlCb5pZluPI315Ub4JdJwnNiGmop3rbLCMbEZm9dKoUUuahxUM4L0keGvui01osJTDeE5hYxyWjK7R3DBmArcBHknu8DzrEDw92OnUP6SEu32EMGt9HdHlfaBC210IiRqL7DrIifcGDMK245IwjV1aZJcd6SudzYhk+EW1xq3zbJU9CtzY8izHa7PknS1huc/wyWrhe2JW3kNuWZN19yZNSQRV24zZLZQBuUYF9WWHHoyft8TvubpjZ8fkHpewkwR9/IZB+ODudiDIZ+ByolbJE8K2phGoU4EMLeV3Cx7TPFH2oyKa6OD8d2C78GuWF1DX9FbVGLeQGZZ2yE/C9ezlWfKc2Iti2W8iifxLPFCs3vRMv0zfLeYTb2Al55Tk03h9wOtYUH0EHXDyqExHsG/HnwpRWM4kOBy5sNAlbrFtwq9JrjpaJCLZlQKEWSMDxAPUUb4QlKXN9LA+u4zuT98+6wfjx5A/qX+x8dP8TNzrBIbeJhgrwKXnT1x+yyvKeFd
*/