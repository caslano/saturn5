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
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
*/