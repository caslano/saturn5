/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Brandon Kohn

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_HPP)
#define BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::at<typename Sequence::storage_type::types, N>::type type;
            };
        };
    }
}}

#endif //BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_HPP

/* value_at_impl.hpp
nVKhWy9f5DOlxxzdSm7yqy81b6l8xBVUk5p6tn7K+V1cwDv9PVxcX/8KH+Hy0+WnHhh+ylkCXsHSJcvvevAlVCt/xv7j47lgf/SAFeAn51tTJOYCRBYVD37OAJ8THrBUsBB8ASETQc6X+IOnUMQMIp4w0J3pwrKHPXiIeRBLI09ZCSLOyiSE2L9nkLOA8fuNjbWfF5BFqI7GQy4KNFgWPEvP0TeDguUrIW1I934iMvDvfZ74S3TkFxAXxVr81u8HZZ4g+36YBaIfvIR/Hher10gWSGLlP0G2LqDIoBSsBxLZg1UW8kjeMSG4uC6XCRdxb8cGXaVhP8tBsCSRtlCPM7GhzcDbpqcnYbBGxryQN5GlQrp6iLNVBYh5lFaiMk/REeYBQWGGae5BiVsqV2AV+YuLbU5VgltLs+MbQpYiGTjVPLC8U1j6gosefLPIyJkR+Ka5rmaTBTgD0OyFNPbVsg0sPUdnObDHdc4EOs+Br9YJZ+HW59td/RPc/fD7/78ATfUbm2UkKxHkfiRzEWRpxO82zRlhTBM/AMeD67rSxtIbcnLSF1/f1R5YlaKAvEy3jEosG1b+jqUs97HJZBPTjeg83tB9W06vExkZna784FQVwdis8UhxfPDTQrXcsuRJ8RE39spPSz+R+i/q
*/