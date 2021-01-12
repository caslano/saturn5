/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CATEGORY_OF_IMPL_09272006_0726)
#define BOOST_FUSION_CATEGORY_OF_IMPL_09272006_0726

namespace boost { namespace fusion 
{ 
    struct boost_tuple_tag;
    struct forward_traversal_tag;

    namespace extension
    {
        template<typename T>
        struct category_of_impl;

        template<>
        struct category_of_impl<boost_tuple_tag>
        {
            template<typename T>
            struct apply
            {
                typedef forward_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
6Xw183B4FzBmFZMSJDbuznwMbXOWkOYrJR23By4NBExaLxPdYp3LrM8YfR2LWYPzMU9fa98X1il+d99zVdlsZzJfRZWJ62Rxs8k6j1TMU382iu4GPn0721qBX3/Frx74NQO/zBobk5/zqdDE2htPaX6ra0/RdLhH7NDvoPmmtZRBAZt+fL5lc3EsvBIHeO9qn909Rv1Xv/4mfiWRyj7T59NA7Ph8yfSW97MaMXo8lLXpx1vt
*/