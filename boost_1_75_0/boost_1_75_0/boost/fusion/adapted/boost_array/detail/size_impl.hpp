/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_27122005_1251)
#define BOOST_FUSION_SIZE_IMPL_27122005_1251

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template<>
        struct size_impl<boost_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::int_<Sequence::static_size> {};
        };
    }
}}

#endif

/* size_impl.hpp
JzDomhz6J4/0Pf0nMMU2xeufjD8j5CdS6SK8FsyJoWFQ8SeIBM8G0JKxuK8TS6AcZDn2Tx6sgJ65kJY5GXxo1KmPd6EFUK0eI85HO1gAycpS0iO1NrO+vTrJxXqUzeBwkxnGCI1N4DeZ1fpNZtEEWRllXVR8hqVoAPsV0xwnp+dY3XEwkSsZMRhxiL0098OQmEVzz7CA74MvUC7WYvwRUWx6vdsL/8yCGthpCkydBnqgcCdO7+fPxHda3SpW1XqFLji3/B4vxOl69hPHr/oB/yWrb/JfGeoK9qs5Qc9kkl39PJ1/alc9kEvT1WGiq9b0Dt278WxSyYjJ9yIEfPNm+mi9LfRHPVjhKyzUxWo2K7zZRx++2iv0hwmitDeBoSajBILvLhge+jurQ9qQEeNd+jZ8NkD/7NzTFCc+A3nYdOCUpjkkK0cEYb9kq8ADeZgb7yAICNu5IZbUOU3/BYVXtsGgDQVieZz/lSSwGribgR4X+eM0e6oT1VMt0FfjrOpf9CNG/RV+COdje1tQzi0++CLbRBdd6DkYVjTUczCqaBD8Ggj/xHiOhxdFpFRtkioWQ1Pltzb0q2qt9zSGb0K8/U2stKTFx+GKwt0737P2TRxZsVlKvTqTha0Oaw6/uIoVlrTJT57qHgxLvX7wNsrvfkdHr8eHOjq6zrdk+t+gpRd9b+7aVTBxvVx993julIF9fWN8Z06T9u8ynSbl
*/