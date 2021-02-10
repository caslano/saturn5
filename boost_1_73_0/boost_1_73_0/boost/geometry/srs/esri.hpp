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
mMN15EYwWUHZt5gpKasVCUeLKMVljMch2yxKygRUtVgdpVfsZR9stxaJvoOtLNn/GS4qQvSPjfL3b5G6r8P87tl2RomJ9hPGkos2TMLFw4ttmeFmCl6beSGQBCXkHV2ExCTyLpTuobPaFsO7YUc3p8jZL/LMoefsyDq3F0OxIB6ONnR4OEU70nh4T4iT1Gz5BomfU773CJc83WGuTnwtskVi93bnXurNJBp56ENJH9nZ4UIq+Sqh/VhfzjP+BS2gA4thxESbG7RF0xKdTESSOrYklto00DVO4sf0WG9NexjY3mERS1s6zGXMRXMp5ZmSRnDRbizqufTYIYG7QIvyP70ulilIpCKLcfmw/IwVMVpOGQFoC+Uu0d5IViXkwCSYJCOAljjN/csQKFKb2sh2KOLJEi6tjAsbXIppsmA5M5rkOKTFQGagWemtcL1ELTFMHMwre6C0YibEyFjQS5KewIk6tIxHGH9jp2dMJh6JA2cFmBT1e3d3Xf3+sSR4qruEtRJ0STcilkv6jxWS24RQmTci6mX+x+KxYS8qbaW/vnXaooSUFTxYoLmaOE4LFNAGCuimhPYKC+ApDGaUBijxYulVm6wg5xZ5G5KFMjubJI37BU9QAbL7neQ/9oyINs8wBp+p0NFRguZDHypo
*/