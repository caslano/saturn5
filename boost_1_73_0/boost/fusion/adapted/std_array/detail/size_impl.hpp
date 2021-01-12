/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_SIZE_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_SIZE_IMPL_01062013_1700

#include <boost/fusion/adapted/std_array/detail/array_size.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template<>
        struct size_impl<std_array_tag>
        {
            template<typename Sequence>
            struct apply
                : mpl::int_
                    <
                        std_array_size
                        <
                            typename remove_const<Sequence>::type
                        >::value
                    >
            {};
        };
    }
}}

#endif

/* size_impl.hpp
9YdwEYyyaT9hAlwKG8NlsClcATvClXA4vBWOhLfBXLgVzoTb4NXwTrgM3gXvh2vgg/Bu+Cy8B+6C98I9av8Dtf8xXAcPwgfgUbgenoQPwoATb7A83AhT4V9gPfgY7Ao3we5wM+wHn4Sj4NNwFtwC58Ct8CrIeyV9CLuePUdbqfV/LcSn6TOUcuuFV8JKcCSsD0fDC+GtsDUcCzvCLNgD5sABcDqcAGfA62EevBHOhCvU/u3w
*/