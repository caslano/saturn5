// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_POINT_ORDER_HPP
#define BOOST_GEOMETRY_STRATEGIES_POINT_ORDER_HPP


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace point_order
{

struct area_tag {};
struct azimuth_tag {};

namespace services
{

template <typename CSTag>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_CS
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::point_order

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_POINT_ORDER_HPP

/* point_order.hpp
DODL7o0kcgsM05dsdSdGYy9kKyQIYK2ZlwbKPAuvPgkuhvMNshtBrjVlvm0J/LrZU4deILMVESDOzmo+r+THDVqPA1dgLUguN3ebXS+2LPidQasWM15cteLCtxAeC8FnElQTnOjdzWA277PxRxUDoDKkQv5Z9J3RTBNbIPBx5vDbZeKki5S2skJk+HTO4tDY4ewQkCyhuyb1kT12jVKYRIg4i9In/9v7QyrG3aknvg6Ui30ATVo7vKHrD2RbSleRspeCRjg7mjGyIdpPAl+iS3v1p14C9a7u17YoaahkoYtINa+MMRxRqj+AVz9XhCyi6qD+DXqzQk88geI/JXvuerS30Lekt+hMyVwbipmHjAiTU+JLPrLr86H4MXgjbaL/xGzVaFmNeZjYhflWFK8v5HZOCWbX+rQFZXyl8Kr8utrt4jsc2/pj3JTTvsRf2IbhrHVk0jhYes0ypy9DGCxkGXC0vbrhVjGXRhmxqowQa+cC3Wf3ZTSCVmyoFHyWtQV3l4X5AoKaITRPfcqz198eDH689qcid0/y5lyfO7qzQU9I+Bx8FSsiSuYF6OA78+8T5lvuC6i8RfosG+As8WOloNvfO8xsTfn1kYvJpHpn8NC5WNo1/kjh7HnubPnqhG9nbdiiS4lW99UfsoXzTy9rIvSgWoUXLwFjJiNYxIpMpWIvIlp3xFgo7/cDkdxZS+fb9LPGxJf3FZsbR4Wz
*/