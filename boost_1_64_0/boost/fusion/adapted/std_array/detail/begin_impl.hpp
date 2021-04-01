/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_BEGIN_OF_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_BEGIN_OF_IMPL_01062013_1700

#include <boost/fusion/adapted/std_array/std_array_iterator.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<std_array_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef std_array_iterator<Sequence, 0> type;
           
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

/* begin_impl.hpp
C1XHpN+1KEG0rMyNzc0TplQu+ZqhlX5nzAkNi/JvfLPdBcH/yzJSj+8nH4GRf0X39VDykip16IpkIwOuW0fdt7cAVwh9suOIbQpI8z8tnmaOg+7hrF8xACOV1TdHZrWwzZTjM2j1KNyOyYCE9mduvUeEULV7D6Xal42o4uM+FFe/RZndko3pIuNh7kQ6LG2Y4K/tqqaS7zloIhZK51uFpybfPBM33fiPgsllzWpIeX+KdV6TCw9B7cZNxKF1YV4xFtQkjQpNv31L/hLG3VwdVyUaR5usnkyaFii3fddlwET7f0JN16tiihI7KGDxV82JRaMaMUWhEP5bpRXKNe49EbJxAL8xa8NvSv2f+6kxg4nFIKcArT4boDOEjpZpplV+bwfatjLoVZYsx+I9RwLJTxClXOya0cEITe1W8+aQjTy7gFOGAJp9tqKjH10yd6tPsDjAhF581lfF1oYzdAcZ00gdr1kQHGYwe59EhOXGOljOQ9VBnJ4VKydtiadaogi4HhhzpeXQCiekwKfLsRAoGzMhLXbOQtclPT80yKBJdlEylhExm5zh7Rydqg==
*/