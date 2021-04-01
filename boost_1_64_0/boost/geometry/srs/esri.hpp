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
mxMmjVCQYJW9v7o+gFiaQALAg0V83iVK4g55fr7F09ZQMDAiXMWtJvPLdk4lcIvc7UncxY2LNZh/uB5Z/rhvWTb5JWexPGn8slYxHbfa2Z8oFo4fJYeIOarSviMmPiUHOgTHabZjzTRdnVfWCPvSMHt0E0QT7YlYziKU0G4nD+/6B76blrV/ZRrPORKguypOoKCrrG9BmTWK9qGm6qmmutEpp/GxWbtYBEp/Y8jC1uLrIvoF5Ys5LEfNIXSOw4D0mf1a818uzcOs050ImeVhxAz6JQoa2Qr9TXjlRmHH6wYPcdkaXFeQqprBaV2VsidvJQt/D/Oo5Dm6N6GHMTLmQ+1ygRU0DduHER37UYVkdyji5iAtBgoBCVrV9JpyJDLmTkjZAV0VqjzMKL8NO7YtrfAt/ojNHqrkI5aoZSVQdM1w73vUL+IgYOb1Cxz0LJgTOfgh2Gazd8tR3BjhrtG9P0+lvPuO0hPljve5eQKn/6mNKaGklaRfYQi5TQPSdA/9/X4kqNQNn0pZ36R0KS29RjuTrk3otXoFK3p0TWOp8xE2CzRLdv5icAz0wg==
*/