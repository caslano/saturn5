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
0V3RcbtPKBzwUGwDv4tdru7yOi22cfB/aK0QboUc8XbBH5vZhAIu96IpfU9ja3SbzHK1Sqcqul8sNmruToVxOjzJSckX3V4nwx/eDCHvpi3hnI8o3EUkMHQ7LJAojAGosaL4xKgVTCKq340aXHEvEQFLlsIawic4LGsxGLxFgxgK+/LfzhfalmkRDEs6fghZkZ6FG703pPSqBGk+asR2LEWS8x5uQN8NJG+7voZXKjGfHEnzN++1K3mnuhrXVO86GI46sV2+IJmk4oyjXd7ZOoAWEslKcRtpJJP3N4yJEx/pL9RBX4TEwMrlnLTaDAYZXbaVtjGXOmueEHTjTs+5mank4vhVCSvCDKk4evqRrel5v46Mq8kBWj4et1GZRNNPXrd6pr0e86r31nOSfIBLzdmsRETrvDjzc5p3HG6ub/ilFDcdybzzsSG7RmiR3cjGjhgUxekvykRB8b3D0vHx/fS76J64U8kScKIh6YrpJH1hVIM81FrZG7Mnxo43bL3jN2lF5w69HjvqUVI1/aQ3vPhOWz8DAgMKCJ48WhDgCN3B8GCP3WU+v8T9Gtr4pxfGsadoRpgzmVDF3g0ygU+uqpCX9vNhQPnXjm+D9XQE0x2MuW7lT766g70tUSHTvz39lAfPCZX8S/2QaeHnqQKEqAE6Tsyc1aap2oqxi60meowl6hVqKfvGdATztpLCL0sbwO6Y5qjkwTVcu9Ym
*/