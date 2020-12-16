// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_OR_AREAL_TO_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_OR_AREAL_TO_AREAL_HPP

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/strategies/distance.hpp>

#include <boost/geometry/algorithms/intersects.hpp>

#include <boost/geometry/algorithms/detail/distance/linear_to_linear.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template <typename Linear, typename Areal, typename Strategy>
struct linear_to_areal
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Linear>::type,
            typename point_type<Areal>::type
        >::type return_type;

    static inline return_type apply(Linear const& linear,
                                    Areal const& areal,
                                    Strategy const& strategy)
    {
        if ( geometry::intersects(linear, areal,
                                  strategy.get_relate_segment_segment_strategy()) )
        {
            return 0;
        }

        return linear_to_linear
            <
                Linear, Areal, Strategy
            >::apply(linear, areal, strategy, false);
    }


    static inline return_type apply(Areal const& areal,
                                    Linear const& linear,
                                    Strategy const& strategy)
    {
        return apply(linear, areal, strategy);
    }
};

template <typename Areal1, typename Areal2, typename Strategy>
struct areal_to_areal
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Areal1>::type,
            typename point_type<Areal2>::type
        >::type return_type;

    static inline return_type apply(Areal1 const& areal1,
                                    Areal2 const& areal2,
                                    Strategy const& strategy)
    {
        if ( geometry::intersects(areal1, areal2,
                                  strategy.get_relate_segment_segment_strategy()) )
        {
            return 0;
        }

        return linear_to_linear
            <
                Areal1, Areal2, Strategy
            >::apply(areal1, areal2, strategy, false);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Linear, typename Areal, typename Strategy>
struct distance
    <
        Linear, Areal, Strategy,
        linear_tag, areal_tag, 
        strategy_tag_distance_point_segment, false
    >
    : detail::distance::linear_to_areal
        <
            Linear, Areal, Strategy
        >
{};

template <typename Areal, typename Linear, typename Strategy>
struct distance
    <
        Areal, Linear, Strategy,
        areal_tag, linear_tag, 
        strategy_tag_distance_point_segment, false
    >
    : detail::distance::linear_to_areal
        <
            Linear, Areal, Strategy
        >
{};


template <typename Areal1, typename Areal2, typename Strategy>
struct distance
    <
        Areal1, Areal2, Strategy,
        areal_tag, areal_tag, 
        strategy_tag_distance_point_segment, false
    >
    : detail::distance::areal_to_areal
        <
            Areal1, Areal2, Strategy
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_OR_AREAL_TO_AREAL_HPP

/* linear_or_areal_to_areal.hpp
xNMSi2H2WET+rqnH014TnEJPrsffMWfSYt37+L8/6xgvmdjrhRwfy9cU60wkdqf1m/33FPuG+vnSMbF37SWLcOkBdWAN9XB3h4Fw4aV9tjffrsQ7I2lgdXh3BVzGFcflfHIt9fMBn7amOq/pe7fNy8XhqDltFj4ebZ2RvWFKLzPYBvNVETnL7HVwsgG8iZwmXsvM5idhsRpdusZsAWtXqu+ZQfYnJtXb6gE9t0msa5vlfw/HP9+qOzH6qA7vyro+VUNj4tBl4tuqv/fPNIvTCnFozDQVArxrM24J5+o/wYLuzq0NuR/S2Ivy0ac0W8Uh6hMeXS8Bq6ro0c56S94m3qKR7W/6c/5abTGoZN5dTBvt5FOExdSOer8Ac7byS8zeQyvClYJm9N7wAaa6VaCDHM2HEX2z0gct+cnpaJOO8lnNzKM+/xjEazhsLnpvFsrlNRXp7HCx+gIO1IfxZ/XJHrWi93iu/g42HZmIJ6PPo8wrV7bgEP54LHnJWhEu6L8CKcx0J7z2lBkIpkzuoN7G8LPU8A7PJfv7yfxq8ZoXUCfO8syBN+7oy/HyktpZp3hk62r+hf399HWWKtaPq5ZYx6P6tKr1B5kprnaFgZ4VbVKWf/wHDvzdc2+V6LxOMELPbDGLHJsDP+1nVWF7WEdrlDaTwJKOEQFzKu9gGN2cXN71wqQX1q5WH9NXw9RxC/2f/pIagSFFw3kdD2CZun/tHgNTiPdCuqo+XJoIe0Lg/Q/uDw+zw908tEvnHvpHT/wFGzbA9zLlzdJj9Yl7H/bxQXUzO8/tcS+Yv4e+X6wPa8AUc2g4DXZzKQ+fxtzwD38eP91vogdy4KTUOGaAWu/AY3kAv49bH5zJ+mdMbujvx7AsHp6t5nzyES1lb5d4TOV+59G+1Ft6Z8oM5x1f8VJxTAhd8iJHMG9X7FLKHQ748qwz/mXmc2cL5c/Q4uXlJw5cvxTi7NtMPcesyHNaFR/XpTEbn4AFz/DhfrHPEWRekJ8x1jKPlmhI9zhfGEdzN1oJDxvhptYwNNyaP/McuLVcq0Y34bNtvj8IViaKQ0cs4TdM0zMwdskDmHSB5o3p3yS0ZmJnQDHnYg/lsK05ymv7wfDioermrFlBTNI+gvcNYBAsncS7vN2H7ipFS8fTB5tgR254zIeuMB/udoeDqdXxX7C3OKy01/0P1d5k86H1pp0Lr3HIPn36aqre1QNlravFffl5CgMHwsQpevIGP8ec1aWeeJohktLss/kWl2cYSU7LtzjFykQ38yK+fSy+cGUtbyFsAl2SG+dr2lspzY9079Wh6r+g3Ilvp0j+YRD/iP7oRT9GljWrZBOTuvA0L88NTzX9ynMTQ+go51t1VrgOril6BFa51zO+cl7e0251kSw7baqG/5Pa/nryRunfiFIB8bHWrV5/SA/yRcLMhYvw5LnWsKIOX6KdOrSHv37Djea/0Np8ONx2MWBevaN2+db1+InBTXnnsG9EUpqFHxk/n7PrffhkEU+Yjk6dkz7Bpb3VZ83l8j3M/FCAj0//FMzp//Y0ED7Ptv8pasxZX2DATrP3BLmqL9fqtcpf4gs70qjbLfpysDPE5uExMTVfDzPXe+9H4TH6Ww/ExgVP9IR73TYP3rinf7vTgMEw6KW++D7g5yDUezXx/p2vDkfyw/bP8+BmmHdPP/Sugv9fwp4LuHsA3UQLZvuADp4Ja9XDiCXmSq+/DA+Py+fVBNZxWuzovrjw7rw4xntpbwtxIdw96iOd9d874WMzr+EiHK1F34rXzh/sfTI+9Dx09Hwa5XMaTO33Gm2e6xbwt0+8vh/9PBpO0OLH9cYL1+31F94/6FzamnryvG4Fm7npugzmzMs=
*/