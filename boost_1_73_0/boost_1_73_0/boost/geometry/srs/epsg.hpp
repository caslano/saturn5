// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_EPSG_HPP
#define BOOST_GEOMETRY_SRS_EPSG_HPP


#include <boost/geometry/srs/projection.hpp>
#include <boost/geometry/srs/projections/epsg.hpp>
#include <boost/geometry/srs/projections/epsg_params.hpp>
#include <boost/geometry/srs/projections/epsg_traits.hpp>


namespace boost { namespace geometry
{
    
namespace projections
{

template <>
struct dynamic_parameters<srs::epsg>
{
    static const bool is_specialized = true;
    static inline srs::dpar::parameters<> apply(srs::epsg const& params)
    {
        return projections::detail::epsg_to_parameters(params.code);
    }
};

template <int Code, typename CT>
class proj_wrapper<srs::static_epsg<Code>, CT>
    : public proj_wrapper
        <
            typename projections::detail::epsg_traits<Code>::parameters_type,
            CT
        >
{
    typedef projections::detail::epsg_traits<Code> epsg_traits;

    typedef proj_wrapper
        <
            typename epsg_traits::parameters_type,
            CT
        > base_t;

public:
    proj_wrapper()
        : base_t(epsg_traits::parameters())
    {}

    explicit proj_wrapper(srs::static_epsg<Code> const&)
        : base_t(epsg_traits::parameters())
    {}
};

} // namespace projections


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_EPSG_HPP

/* epsg.hpp
6Xm3OMk3mnDNtyqzXfWsDVNl79o6T0Nl51eIJHc1pRauqn22+ne3FNc0SY2ZafL1cCyjmp7Bd1wkMsqTetaYc9oshtQ5xKTLtL3zmYFYXPheIdWAGu4QuHYtUm+OjgRdFIBLUMIERLcXMlwEggiShWLYijI8DqMw00W2s6kyz7xLNEH1asfApQoDHBKRM9wi6KMr2TKegIQLyI8dDZFY5JQ0pgZqysV2RQea2kWcpIRkMCVuP60WRIP2hajqiOHLSi+V2ElAKV4D12Hvl26lzhpNzJ0+7sT5DF01YQByXciRK3NVXIBVhsn4XFuTPHXNevgVDJlRjpkAI3HETNHOSmRjA9TMOCYwVj+TgNop8XCCCE2lx1K0IC1ACbp7zQiGrgi73UnYIsWiOpuF0fM7C4ONjWJVYQwb2fxqs5j1eIUzM+BiaLJTgaQhh6rGrTVj6eHDuRHcLrqdSnTqIrqCunXnB5QdYM0Z13KVVS1UbCnZRxFfMyq8Y4nM1yqivHHPrpW4uRH2+vFz2MvnXuPwkLDU7q42iCbn1bD0/GMLA8xqyXG5TGyhGmYWJ3Y9TAtizcipSAfQCoAsKnWZ8AgyWkMiPnbrJt8IFisslFC1RCGowKzAjILp75L/3yj5KxBc2+p6bLbrEuqjVLFB
*/