/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_CATEGORY_OF_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_CATEGORY_OF_IMPL_01062013_1700

#include <boost/config/no_tr1/utility.hpp>

namespace boost { namespace fusion { 

    struct std_array_tag;
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename T>
        struct category_of_impl;

        template<>
        struct category_of_impl<std_array_tag>
        {
            template<typename T>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
GlsjghNKnA2teGZZgIfpq2PKSOFB2MX0Q+UvfxY0mCe0S7ldOiMwZbWzeUleIc6bDjZr7+9jFlyspD/SBx2I/kESGfG34WyX1z/hx15uB6croR8t0zzjraOSOMpkcMkB3p86OXwLigdMW2tL1hET8DG0dIzoB2QjoGWLAPmzfhW3WuVITQqXTz0Apk7RoHX1wWJVxyn10gtljusQZmQlfN+qXUx9+8zbeQfkal+yktBPaIX7kQnnEUbXjprm+QTws77Igy0j/yIsxZIBJ2CkWwdO8jru84Ze7cF70aTvrJNENzNA1Iw47ZfZGkj4h9De7u4+zo8FZH5wkTTWRBRZo36zYB7mutqMgNnp1ZwbMW6l94BWIM+9K/tAoHw5zomW/ngkKLqmBmPH69sADWIb/jpodlAT8aIjM11fZwgB2InqaTZHdjrEvv00ZOmAXLzLjd2jWv6mAeTJ5hli83cuqeOcrNH36omfa57xUFo6RqgZ/nnh3M0wWtvCVFIsHPDjTZlqHwHlRIhdDfI/t9l4gaW4B3t7y2vOO4nFauZdlLNuLQNI6kBg+kFxHA==
*/