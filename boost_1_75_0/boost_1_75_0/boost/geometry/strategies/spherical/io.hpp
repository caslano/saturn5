// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_SPHERICAL_IO_HPP
#define BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_SPHERICAL_IO_HPP


#include <boost/geometry/strategies/io.hpp>

#include <boost/geometry/strategies/spherical/point_order.hpp>
#include <boost/geometry/strategies/spherical/point_in_poly_winding.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace io
{

template <typename CalculationType = void>
struct spherical
{
    typedef strategy::point_order::spherical<CalculationType> point_order_strategy_type;
    
    static inline point_order_strategy_type get_point_order_strategy()
    {
        return point_order_strategy_type();
    }

    template <typename Geometry1, typename Geometry2>
    struct point_in_geometry_strategy
    {
        typedef strategy::within::spherical_winding
            <
                typename point_type<Geometry1>::type,
                typename point_type<Geometry2>::type,
                CalculationType
            > type;
    };

    template <typename Geometry1, typename Geometry2>
    static inline typename point_in_geometry_strategy<Geometry1, Geometry2>::type
        get_point_in_geometry_strategy()
    {
        typedef typename point_in_geometry_strategy
            <
                Geometry1, Geometry2
            >::type strategy_type;
        return strategy_type();
    }
};

namespace services
{

template <>
struct default_strategy<spherical_equatorial_tag>
{
    typedef spherical<> type;
};

template <>
struct default_strategy<spherical_polar_tag>
{
    typedef spherical<> type;
};

} // namespace services

}} // namespace strategy::io

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_SPHERICAL_IO_HPP

/* io.hpp
AMy5loL8EyqeynnTO5K8kiq8mah+iB5dSYrvC4o84kzgioAgiQ83iYCxhA739zDZpNCkOTy+H2U/r2bFfISNP0WyvFbIkeImS/ZU1YIM+aaMEOR5lbmG2Vyx+PKkyDKcd0nGEK87VWkTWoh6b6nmxXfDxJCgPyn2Pb264h/ENph7/miNZB+s3sNytEEQ7qWp69ca+p88ONci3+C5xXjeTW2se9InWBSEMcLiYl/nJT86hwkanJl7UpcqNvOZXrFshHdiNKPZZ5aU6fkKAHMy2oMP+PhSSWLXUyvlDKWejB1hmnzn1xVttdVbSFn+h0ucSRI4XXaOLaklQ7lAJzD5SpY/5DLnlJblkHXiATQBCdJ6U9lSaLLV8l5RQcWH2CqSH1GpD9H1eKQrE4Evi3I4cCsab/hzq/S/KSasYdthegZWzidGeiZVFjNHY8yB5fjW66RWg8E8oxtJCHUvSuXRJ02v4BwTSnOyM2amS120y5GdVsKSlVD9suwvsgHdjDsTA15zmwAFqt57QEpyvU5mIpNbkH0xaOaGbx3zUemRX6MemR+2StGSd3C9pk34BPtTHVZftBPhcYgMCt1xujgTfVizBSHjlJQRSNzp4G3cqRBvxWR2Xb5LZEz606BAg8HDNJ6ZEhg1QSlsCwu5G4rwvQSl6SPjUGq1CMagjeJPQYCvguq5z/QLhlXVJvp6tc/XxQjy0TQkhq8UKtRu
*/