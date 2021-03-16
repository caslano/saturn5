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
l2/ZN53CXaBwFyjcBQpLdj/Yg2BHwU6AuVH9DZvq6zQeJJRa9XapVW9YGJkfrVpY7y6zejq1Jm7SzNoWJa+BktcINcrBqsA2g20Fc6Pa6zbVeKToP6ZRzZdStbqqaN38qsZWS/jITnvESufjhrigXwfaLGhHM7PuEaCy7d6gGxTuJpSbC1YJtgzMADsKdgLMjerrbaq/q6VXPSOuev2CyISiyaWRSaHJpWOLI7WLa+N+ddatomG7IEF1bvVGxEo=
*/