// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2017 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_AZIMUTH_HPP
#define BOOST_GEOMETRY_STRATEGIES_AZIMUTH_HPP

#include <boost/mpl/assert.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace azimuth { namespace services
{

/*!
\brief Traits class binding a default azimuth strategy to a coordinate system
\ingroup util
\tparam CSTag tag of coordinate system
\tparam CalculationType \tparam_calculation
*/
template <typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<CSTag>)
        );
};

}}} // namespace strategy::azimuth::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_AZIMUTH_HPP

/* azimuth.hpp
P1INVlYtDVYhHKyOYORoxNoq015uDJxDuOif1GPRp5lF3zcNip4NRXcBTonDQ3igkg100UJHdQYavfyLRziufoQdGpzopRn4Hppj5jXxOFlg5+ukquq1VPXaDo4qg1f/MtzeJDdarQQ17Rqz0QDsLQx2jgI7h8DOEVSaU3+ooujDFxBF5yBFyzgnzUdhMR89C9037Aq7Y2ldZ4NSGn/1yg+ZgnQOY25MujTizfQNLumPUqKOYcmdZSmFtrdhn+mho/ra4vHeRkGWc4/Xr2kfx8zxg8scdkLL4HgpdqIaIlXz/+2SXXHpiaea859G+f9o5j8e8xfz5H/xd+Nxvi1aYogMGWL5+WJ0pS3HbCkyLP2ucPwXsvYdmu777fvt+/3X/rTz3RCpsF6kpPGs5wyjrJPN4ykd8CdtEB9IFqKUpnt1dOprcd7+3Q0JMKWQWCxVRlYra1maZyw9P8tk+ddsJSxZaMu/vgJLgm9apPJNLr24pHdm4aBv2viw+Nbn6QSm0gRTjWBy8ejOq1CrwKsIiVU47w1RBdz6dL3h4sRkes4p+WubRfLHMPlqmXyxi5IPT0z+jZ+J5K0498xnPAIoikpISf5raet3TuxUTpbrlOyxn4tkX42N10k6hGlx/EVIi26TFpWwr41l8PQ3FzVw4+F8exZkuGXn7NKZgENR6kn7u+EEPe3D77ghgvZBEEXKtkcCnY18m5sw3KUAD5mFlhO+gGeFf88v8SrocxcqVZ1Svu+49RwSD47EoBAHPclBfv6afj57JKaFyuxsvv9Uq1h+kX3/aRK0z9F8kS+t0y0MsSnN70HfpiYfSAk2NW2jdhxKX+w2oA2DIh7l+rQuevu5SPQvcuuvCm1HVzopLa29gCjBei/Xfxs+Eu/albAJP7qPoXuS42OxI11sN+BC1WsLFSVunki6Pu/Qyfbazz1oh3OyefVtLp/enjaZrmTUKp8Sxez3ihTbc6XNbu0Ox3DO8FVpDpzyiPscKLKqWGs5ZYtOEuqqIAmx78QXI/E5l9sp16MyV7bI1ci5+HSql4xXyIyvimV2m4bq8t7zTpN5fyjyrtDyruw9r8V5YfQhf2laxjW9Z+ycKDKOBqbFfkCycqmHKCNJDmqp8GUQjuPPf5ICVB8/dldA/H8e8T86MW73FrWUFzX6vzuGDKF6i0JwTyu0Kw4Ko1bp2jQ4cWp+LJLmAidT8e3A1mmQKpKF88ZnLnjLJ/Mr+DYY3/6Mb0Pw7bf4dhC+vYpvpOyxBd+Q7F3P4NuhGPY4vo3Ft/vxbRy+3Y5vh+HbD/FtPFkCxjeyqtKCbyU0FUUm4qMhMgkfl0Qm4+PCSDk+aiJHk/mFyDH4OClSjY/jImfgozIyCx/TIpfgY2rkUnxMiNThozhyGT5GRC7Hx/4R9p8dOY0GJtJDj6VRHaDdC567YPntT6a5VsPfo/C3Hv42wd82+HsL/t6Bvw/gbyf8uYGG2fA3BP4C8Hco/E2Ev1L4Owr+joa/4+HvFPg7E/5uhr9z4e878FcHf/PgbyH8tcLfUvi7Hv5uh7/V8OcKyJ+l3twer3hLU2HpGb7MrAHZOQP9uYNkWJ6K3S9fvg2m/0Pgb6iKLVBvw/Y/oPDAg/Bt+Iv/2T/NPBEpVtbIexoDpql7Gsst81bGGsO0dY28hp0cVUtRPPYmxLLjcIhb5Qi0UQBtxFFcqoX5F3/bbSduiXjJWlpxImSXf12ULZXYB7rtVmyMQ7odyensVOYiuVQe0IzgFFgFH6LRaUkY7c0YEBuekGD7bjOBKqElkmuRy0Gp4h07Npo9jt0XrDbIslQM1W2YwXaqkdH1diZaI7ITUoLoz8daOk0hjKdnFZZWYMkT8Ko=
*/