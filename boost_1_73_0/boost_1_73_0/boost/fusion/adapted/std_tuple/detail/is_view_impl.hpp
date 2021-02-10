/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_09242011_1744)
#define BOOST_FUSION_IS_VIEW_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<std_tuple_tag>
        {
            template<typename T>
            struct apply : mpl::false_ {};
        };
    }
}}

#endif

/* is_view_impl.hpp
p/EKPp0FtJOoCuTwu5NeLcalC82NQiAgaHv6i3e18KfrtY2Ji4u//Ni/dxO9dQCsYtnB2QMAhhqeLqNo0UdmaAz/vWJOyLRVpRGnrTnDCehbYh8JC+AtGlviHOUJ3O7QtA+TY/0wqnU2G8rwIvD94NoPzjwutvHLk3W2mNDQaLZ2vqKhc7yOAUU1KKjlHy34tR2+0saoDbKJWZLJGhAo14aZGWzsVFGgF2OLkWXaTT6mxTloPqrsKGXwMGtt9LD3pcnrXf7GbVlA6c5eLKv5chpGy9lZND2PvVV02YXDcwGt6GSCSUEqewSW6aLguix0RxrH42iriM69ajrwpW4G7L1cj/smdGuk240j/JccTCJThwmqwRpYEUmiUnxBEPuxFlLciVuMNQc6208MJ2svhuZQyUfpRjvMdWrlwOecrtU8tTg7xPaM+8FPs3kc2AYbPnnAgabWBc2uPIhgESxe2nIKr6CbfrJwUf0rC117NfbawoRx008lT4TUEs+8ys8N3tEOrYPjAaWO7U97vQIIIGxOO1q+LnT5KALw2mFwCVQd5B2jhGddH0jXFUUzsZO7n1aqGS5uONQHISpM9Z7BVEtjcdsrG9DdSVl1LccGhrg0rickMgwYllMzoHJ6VP3guvBWfuTMV75vFxbL
*/