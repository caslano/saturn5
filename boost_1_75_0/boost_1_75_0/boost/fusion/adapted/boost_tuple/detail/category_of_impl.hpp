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
5Yl0GG06j8hKEnbBSTpjj7OLMLsRlijCEo0wK+fcm6w655KfUE91XtOIvhbLNn8fwCZTLBySUSl36tpzi8L55olD3HD4V3IMPPpPK9sQ3FMg0L3X/Y4Lr3jNVn0Uyo6bdAzslA+hqBl1BuTUNVuhbbBSz4RnzIYT7AtY+rNvfEcBlLUxW1kGGzKnb0GYU6n5KMLKEpD/3kyWgMXCro2tHGjYIL/h55fhjwY0verVB4y4CN/ICecjtsiVPXAXYdN+s8IwK2ntDUTswk//+MtqEduxy9kmxzGsTip5PYr/uAX2g+l1UmkxfFJTMgjA7sFp6S2EuwWbftZSsMSHMpOIvHX9rGgew+r1FxAW9VtzP4SeQ5ziyj9xB0rAZGrFMDjKe5wDLDGCjt/ez5Kd9i5szaSS78JMkJhkec9R33yErKzZvv3dail3ed/mgGjL+BWojuJHArcbVvmhQfoFKUETAkI1ZAOWZIS0cjEeY7yNZ6yI1IHoizpStLsHDOExrMxKGMJN62yUvFHkq+Pr7TR2pgPNWFTxRnJS/G226RpDUJiIhj3AdJu5po1HrLgCOwNnbQLtQpmNK5JUSKvE7T/aj1SfhwNlSgJ4WZcsBGUmwz8ZCGrmYv8kg5ZZEiAqtfDDGTstTLOULx1aj8CDFEL5xNxXI9zJZYyiplfhPjq9pigGqPi0l6mdAWRK9IyObSJq04N9i6/Q803DIv5P
*/