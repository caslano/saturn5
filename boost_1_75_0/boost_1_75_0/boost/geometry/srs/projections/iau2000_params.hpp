// Boost.Geometry

// Copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_IAU2000_PARAMS_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_IAU2000_PARAMS_HPP


#include <string>

#include <boost/geometry/srs/spheroid.hpp>


namespace boost { namespace geometry
{
    
namespace srs
{


struct iau2000
{
    explicit iau2000(int c)
        : code(c)
    {}

    int code;
};


template <int Code>
struct static_iau2000
{
    static const int code = Code;
};


} // namespace srs


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_IAU2000_PARAMS_HPP

/* iau2000_params.hpp
2u/XEif3N5c76Pyrno7obQhCF0ZnXiI5FAUB+9lsB8KAJW52OchRf90gFANSNH2dn1tvS/gGjVUBwdO/Nh2B5jFtzr4h2yO9+EmJKcrr4IqfF7Qtqh0WYF+9Mr46RRmh+GO04/SSQigOmMWxiTNYoeoixi7Q8+s+X8eIjVAHwcOrUFRfyMdmvcar6g52XmC03KIdD68Aj3DmKq8wQ3QSjZBw+Mf1L+m0wEAw2wcUFYr6d4x3D/mTwfn/muT/twGO678YL25jaW7H+h+O33IjGXMpEPLHIJdG/PI59jvdNzhVCvqYL1ewn0yiPzkb80UbYyR9kk1ZcnFp+6TFtxnq5/fps968KA3zFJ6YKhcu7SEjj2bZvYkxr7t9RmVRu8GhMEWgbIdaOgK16SS66l4jWa4r0/mCIHtXG89fpEkmfVTSy8/butgXFwUXFxebvJr6XsYUycGPeVHQdM3SsOqQAC1Hy5latuSdirDPUeNBWiwZl3t3BQvHDGCY3QGfDcrjBsRrjmNiDOZoLQniItJdSXuJzah24/a/bISvMW147oFhXj/KH15lxrJCLFgjJHXxrmlyqtDgOBe1Vg6qfe7C7EiNjCDsqqRu95C9zTFw3ywYm0PtiFV1ZRiLCViWolHrh+PngulncYcVd/qSW1MYhH/PFMNrd3r/Za9eWgB9DEQgl3SBfJlU5zMu/z3DJ3gFviai5awvfm3AHiwe
*/