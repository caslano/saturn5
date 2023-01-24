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
9+LFB5BxEf/Jqn0u/8n4px/8bI5QFhQA27WDlvDRlfZ21XcFTACvwj2Iftkxc9oMrkLw0aOgpY3jZfWjYuS89igOlBce5T5VHiW7nocf5bbLfsOGXDpGjTnSV1yA2/EG2gUuGttg+0uHAYVcaaqSX/LBE/GP7iG9j0qcmbIk5w5Q3qu0kL4TgL5ksicIqnz4sQ3by9+jHN7M/hFFGiIUarheRUBbYabK4iEn6oI/CvvpeYNCSa2FGw7o7uG+YSmkitrFWyxMjLA8xtcyoVn2FJYU9e87+unerWrIndQATi0qBfhK6Em6NSVEOQw3VMZha3nhz8rhm9NV+f9Ye/OAqMrvf/wOi6AwXFRGzTSpqDBTKVsgtRiFmikwzFRKM0pTSissqCm1MKCgcQxts00tzWzVVnHH3DB3LfcSy/ISLS7lVjq/5yzPvc8Mi7y/n98fepl7n3uec5/nnPNs57zODmbN7xgjKoXY9N6/4VFi93BMbYveq9+UsSOojzNDp90Tgz+oItjFqq8ChbiOxPWSH8N4LXY2HyeAl8AJQrjTuwasr7i9Pw/mJCvh8ICrcg+NwWNKxwbzDb/5hrj9Cb6xVnmjrXgj3fsrgje4fPah0Q7BwMP5rNSYiFHYhTvD6PjTkZ8PI4Ao2BcL3i3oOZd2ghbtUpvWxXDT+X6Wc7kfZyzhB8fQho8LvRwc6T/EaeQDN/rhGHSxy06D81DG
*/