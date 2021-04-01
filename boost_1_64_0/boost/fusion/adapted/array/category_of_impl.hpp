/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_CATEGORY_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_CATEGORY_OF_IMPL_HPP

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename>
        struct category_of_impl;

        template<>
        struct category_of_impl<po_array_tag>
        {
            template<typename Seq>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
jWmoRr3GjdSjkrfeQbp58O5dV/KksX+Z4qxw08FyvpAy722BT9ytYJAwvFagfSLxYh454qnXFmWwjYPWK1wazFk1hKl/PAQAFLKNb3mRgLdccYfEHaFcXBbEtuFuk2DuZ5Hv0UFacETv93k/91D8w+Dg1disVTmW85K08/QiUyak0eaQY9Hey/yTBT3GKngYT4hrorpseLN3T7Z3T31ZcbiKEkRrJfQKaEs6jn3F3d4635I5MxVl3K5DzrTpiQosfICsgyyPTG8rPtXf2t82M28jzM+Ij66+p+Nkfrne5Sk6NErjf0ZHeMS/IkA6k9XO9KsDKgF9YEz5z8PPqW9xjO84Gc7sJFJ8MngduHq6j+1H6pBYiudPm+eF+giXU0/8Bs8bBK5srv7aw/6lNXPz79hi+GPmgG5xvGToG8omT0C3Ok4flURXhaNVelfX5Wb/D8WBpMLaJveaGSoBItx+oU8MPN0shiTdpH73eOdmLofDslL4ylaBDw+MKjOeAjO5xL7UN3oBsUciJJXwNGVwFikLPtYDfbNjPeBBwX4v81jf5WGEjtEwgvP8/w==
*/