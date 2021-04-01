/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_IMPL_09232005_1058)
#define FUSION_SIZE_IMPL_09232005_1058

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct filter_view_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<filter_view_tag>
        {
            template <typename Sequence>
            struct apply
                : result_of::distance<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>
            {};
        };
    }
}}

#endif



/* size_impl.hpp
JKdlwN97y6RzUVyuvQmfh9RytORdvkDO18vOjyEmj86BMK0CTthE1BBYX8HFV+wh9q9JN5U19uD8LCTrmD0DuRR98LuUSddkVyS/VG5fACpjfDUd8x9YeYxs8du4elAkMNwkTBpAOzV9hRYEEaca4l7KafwDSe61xnFeNK/qaHsR/1GUCaXHv3qgZcmgxF7dtZF+jbXAdD3DoA39SQH/nDPEyRuOFuL4IQedYpmfcy1wbnZ3xwKJ9w2oKo7QC7pvzMX7jL8YGKgjmJLtly9YH+V4i0VcYrkofKv2eoY6Liw1pI+FQATYNgpacW2/3Uriz7DWy3dVP+IWSrmWWIB9qYhkOPubh+i4Ujz7ibjulP3ro7tNxj5U3PlyEBBZzKs/myW1tBaRPkxqWKHNcG+JlfjisagqIxZQF0HJN0+xm84pDQjpVNZl+Pvf9HlTrcI6/IXAWjvuxnwcJyEQVeRRZZDzMUKWaMFhu66MG1Dav4EC8SG4QgPgUn5kA/3NOXA5bjIAYQtO2bKdp28lehjMmS/sfxOfjvW0oa55bvUSquxbb61v/cgfXIbMQg==
*/