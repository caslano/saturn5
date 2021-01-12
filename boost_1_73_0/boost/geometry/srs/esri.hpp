// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_ESRI_HPP
#define BOOST_GEOMETRY_SRS_ESRI_HPP


#include <boost/geometry/srs/projection.hpp>
#include <boost/geometry/srs/projections/esri.hpp>
#include <boost/geometry/srs/projections/esri_params.hpp>
#include <boost/geometry/srs/projections/esri_traits.hpp>


namespace boost { namespace geometry
{
    
namespace projections
{

template <>
struct dynamic_parameters<srs::esri>
{
    static const bool is_specialized = true;
    static inline srs::dpar::parameters<> apply(srs::esri const& params)
    {
        return projections::detail::esri_to_parameters(params.code);
    }
};


template <int Code, typename CT>
class proj_wrapper<srs::static_esri<Code>, CT>
    : public proj_wrapper
        <
            typename projections::detail::esri_traits<Code>::parameters_type,
            CT
        >
{
    typedef projections::detail::esri_traits<Code> esri_traits;

    typedef proj_wrapper
        <
            typename esri_traits::parameters_type,
            CT
        > base_t;

public:
    proj_wrapper()
        : base_t(esri_traits::parameters())
    {}

    explicit proj_wrapper(srs::static_esri<Code> const&)
        : base_t(esri_traits::parameters())
    {}
};


} // namespace projections


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_ESRI_HPP

/* esri.hpp
h+Du9zH/Cr/E419w8DvKfuLZ/ws/xzN/OQz3nX/8ZfgFHvth7XeJ37TJ+bNE33EavI0f26pi3vm8eP/4E+DrHH4d/AjjvwZf6/D74Wb/5mr4uQ5f/3zh33I//p1B5e//jsMfDFz9K24/RfjPHX4YHpj5O/wehzO+2Kub4bd7znfZ8UPmx5747YQ/1Xl+7u44fv3w/Q5fek0cv6vhfQ7fBzdXL4B3Ofw7cDt+w2+rqdx/Hfop
*/