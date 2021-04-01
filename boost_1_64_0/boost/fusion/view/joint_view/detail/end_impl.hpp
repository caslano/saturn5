/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07162005_0128)
#define FUSION_END_IMPL_07162005_0128

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct joint_view_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<joint_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::concat_last_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return s.concat_last();
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
gStr/B0EwNu0kmM8Z2xyXMZvSKARrtu6ksFTFKIwHNQ9B1TzxtYnAgfgFyTReiLz2vjwa2WV6weRLPsGW/JEUTEg7Imd1HjGkLxE+A3Ho/l/f31PgUQPK//apIwV9i1H4bnrCnAiPlTVFAPVGdonCtmDV5th6/UGVRQSqKJ3rJ7/6DcP9U5SpVySGQLv/tK3/cBRb5HJO2SjIDHoBIXU7gpDkQXo4uLZCBwZu+i5s+KzpYXhzAaR4e0ysp+UPkNL/1d1/wYt0kKjUfwIlSsau364SlyMoFXBDQGHYsz9hFoYNvBIM6g+XFMgnftw4JYHI2bWjmDsh/H9MgaaUF7yK3wcvqr3PaBykfEpW+OaSXYT87Vxug4gFYOr9z6qEszJSDIURZbWLPKfozhaQrs0SxO8F65OJw5GtKzpJbsClw7GtwQxCb+UQOSYyZoEvpKJz2Oafg0dxsNGUinSuziNzbcRhCBx3vZW2tkJn+YSj069FBk+rjC0ZwdIEjRCp9zKpCpo697iHrlflwKz28CaLshwS5vOejzH5rklvMJNOyMxK4VJtqD5I6wBBg==
*/