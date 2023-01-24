/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_CATEGORY_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_CATEGORY_OF_IMPL_HPP

namespace boost { namespace fusion
{
    namespace extension
    {
        template<typename>
        struct category_of_impl;

        template<>
        struct category_of_impl<struct_tag>
        {
            template<typename Seq>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };

        template<>
        struct category_of_impl<assoc_struct_tag>
        {
            template<typename Seq>
            struct apply
            {
                typedef assoc_struct_category type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
Komf6aPr8lOp8lPZCD9nQ4gfikbF+uUrcK2SFm810kCnC7wnoa5RMr4JoS0tfBKY82C7mbRhh3T+Nu59GjY8TLnyhpjLLKFQxizxUwYKjyH41Sr5NX7Hk9t0hbFg36fAPESC7fsx6RDD1NYMhl9gn+gEK8L6ms3K14Q0/DXf1/M1L00I+Jr1No58p6/5LAy/BvJHdPX7/cImQIRwqouAMtBNB6e60mMGD1sh9qBMfHuN/ywCrevFRzjfncnweoXhe2wNMryzHoZ/Gh/AcKJNRk4jw2OaIcOCqZrxnFZvCze/LpVdWXnmqY5i6SUHPS3hBEuapO1beK+pQiVRYZGggOlU9WgrMGba4DXpla/SmvSw1ijI7qDfpX3PMP/q8ztZ+uvh6vRuNH44wn98J/9Yf4SKtP0dR8ZYujSnSwhd/q3Fy9+11ngRacWy0jjx0S1WLKvGiCN7/I5JG83Dpter2psomvEnaBy4/zEcB5Y9huOAv2ccH3bav6UlXLLf0WejLo9yOn1Gh01mqJ5x3kQ7uvXwNlBMAEBqlvQZgRKFgSVwrCrX2DX/EAeoJqv+/7nG6DZCIPRYM3TbFWuGj0zqJeE6XhCjaGNx2zSI+x2LNunsnozHj37Hik3k0P6oWbl3DdV7flSD9eb3lPW2amK9fYLrdXO9Nt7NiQ+sXMzTG6p8cIqs/JWTDVa+S6189cagyjdsJHd6WmVbMWO6
*/