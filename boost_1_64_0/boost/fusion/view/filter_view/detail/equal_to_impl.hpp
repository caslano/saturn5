/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_EQUAL_TO_IMPL_02012005_2133)
#define BOOST_FUSION_EQUAL_TO_IMPL_02012005_2133

namespace boost { namespace fusion 
{
    struct filter_view_iterator_tag;

    namespace extension
    {
        template<typename I1, typename I2>
        struct equal_to;

        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<filter_view_iterator_tag>
        {
            template<typename I1, typename I2>
            struct apply
                : result_of::equal_to<typename I1::first_type, typename I2::first_type>
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
g6dOvfs2wiHi4FSo4wDYc0yvTVamnxTudHCtizykO7r0ls9VgjdkdNzrVRTyQf2PDaY8hbJQyw9LFhG93Z3ebkiHWT+4xcdbHjNMkQoZvYTI/KaEVeKTrQa+2EVPRHdi4OFnBkWHfSp7QXsWINZ0lt1O0WR91I8iKxO9XMekNv8ygnCHtgSZeOz6Zrn8txKsEO1MI93YUPU6WGf6d+TT6PYCE1AYpFStL5mrrtPCY7vBmQtkwJkbwqf564d6ax5PeyHjUhTiGVpJ5XVoWJUzTS4nDbgqsXMdAxdSI2v8IWhTKXUZnV5IkMUKUKvq3e7tHwv5IeO2XKvCOJG8/CA4zS7tkLCA/eYJXB/N6nX988vlEoGOrZTgQtfG7ZvJcu9S6RvlpreyQgID8tcGwjT+3SyLfrBvShne3GX0nxAK8rzZttcWtUwaEUdBfxK2fKDJhCtvjjxaMZZgtEKCJ4JC0Pxd8ML57H9bNwk+Y4bCXKuXswWW8rogq2EjrCDn4G5Jw7FFyVQ6JDEvOptICG0WRpiUPyvmjdtrPBpvrpqODfx4s3AHBX6O/vwrLg==
*/