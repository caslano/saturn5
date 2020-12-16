/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::value_at<
                    typename mpl::if_<
                        is_const<typename It::seq_type>
                      , typename It::seq_type::storage_type const
                      , typename It::seq_type::storage_type
                    >::type
                  , typename It::index
                >::type
            type;
        };
    };
}}}

#endif

/* value_of_impl.hpp
doXzYV/F8g6EXjgRLoapsAjmwmK4AfrgLbAEboFL4P1wKXwQlsKH4TJ4EK6Ab8CV8E24SrHAq6ERi34VPB2W8V+8Yn+7wTWwN1wLJ8Hr4HS4Ds6A18Mr4I3QAzfA9fAmWA5vNvTD2+DbcBN8H262xI7r/pG2Ml5CYsfbK/a9A4yFHTVuYhUD3wkOVwz75Yphz4ZxMNcSu94VBmLtD0vfdIdvyj4kfY/CnvAxOATuUqz644qRf0L10c+6F+Q4Vn3NYL7q26JY+7vhAHgvvAhuhxnwftn7E8WOPwBvhw/CJ+BO+DT8KayCP4PPwkpLjhfdx9EXhkvLnuOlozUXjNbrXst6VZb6KLb1xljWO6b1WtWyXkznutWXqPV6RlhP+0/XfZY57L9ztP/OhV1Dvqk7DLbS+aU15ME7GMOe9x/27gO+prMP4HgkQaiR2tSIir2SCGLHjlFSo4KQITcSMq4MpKioPWq0qKDVEa2iFTVeb41qjZqt4m1V1ahRm5aqGvX+zs0/N+fcnMtNX16fz/ue5+Px/Zybc+95zjnPmc+a6/ZE6rH/P4+3eqyKyyPrtz/tMVcvV3F5avXc/9vjrq68mP+Jj726/WL+pzr+6gyO47XEI8TbRI95rA8xijiDuJJ4gHiZWGi+Uf5sBCMYwQhGMIIRjGAEIxjhvxv+W+X/YTEx/3H5v1K2n6yq919GyvarSHlXRSnbv15WXbZvqfevrERSdJyUl+Zi/P4DzrkvY9EvS7FX9vL0ylj0y5SMspfHXfbypMtY3rWUscxOP9Xy3LGFzgM3vdKgXuee5oeXsfg5yXGCVaQfE1cpb1FCESljcZd3msTUivJu8x0XJ4f639gw0vL+yfLu6SQx6mXL+xfelfz9d5pP6n3mk+yb43DDvEb/HHbfW+Z8Z8n7yv9KnxyO9MfxON5LZvbDkfu2K3/3XaSn8W7RCEYwghGMYAQjPLXn/0H8GxkSa0qKehx9/yvP//15/qdupub5/xnpl7og0Y8HlHeKZrb7Z9Hh0UmJj2zjn9UXdeXMOqBDTSnaerULZDnusoyixGrM6+9uXc4gBn1n0PUwVtWUkOhAvwJFNMsMs0y7W6fDNXVQU6X+2mmpq3Kc2Jn5PJ7NXj6V7R2u953BhKynzRgB1NuV+czqcd+9pX6+etx3n8xxixeTgNHOmX2Hvq6kR1XX9VVLPduR1uX4KXktc9lmGWdas573ZD1DZNn9iB1Zz63Z+5Oa0o73x65ZT6lrO96aJm2/9Lelzv8e0lAZd+BE5vUvYV023wlhAz16PAJp35Bj+cq+6ZT5WVjM4Oy+/F2l/q92X5jpvD57X4yppt0/ftp1sewLJ9bhJrGD8huWdNv2629OSjGbcozBf0Dq6K+T8RgycDK/vbW0Zt3NCUqfGQ6OKe6PaZb1CremOcDmGCsl20nqz8dFmCy/b91WNYtrx9IO1dkOHtp8plmvtVL//lupJ7aP6K3kp0LW9WKdhjN8yCC6BHG83YTe8VM/c73YLLLNdfYjf6SGtyX9g5LkHOCv2v/a8RYShlu3mzbfyDpq++aPlHHrw7AhaTlQWLuOprjsdRz5iHVMxQY26zNFs+8kj0ubAz7j59mfsj6kXz5j1VX787K7rLt1vezvu+ZS776j1N1rQ6zN8kPdtetlyZRPKU+qzx/HJL3jJK+NlmuEuyqvJYcr14lHnz9kPBPNtSFIdW2QceBl24WTbslz8hnfybE9F8srAZOkL5RYkd+b/Yw6fXIo5KINkepYsLb/Kp+5PZMtKZP18VPnc+3xMZRcYt0/AXbyeUABaQsi+bwaVlG2b0F1+iWb5+IcLWkdat3HOvncS5vP5Vi2n3dvF9DPu1s=
*/