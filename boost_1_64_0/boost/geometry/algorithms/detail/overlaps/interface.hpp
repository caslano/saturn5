// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014, 2015, 2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAPS_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAPS_INTERFACE_HPP


#include <cstddef>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/detail/relate/relate_impl.hpp>

#include <boost/geometry/strategies/relate.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry1,
    typename Geometry2,
    typename Tag1 = typename tag<Geometry1>::type,
    typename Tag2 = typename tag<Geometry2>::type
>
struct overlaps
    : detail::relate::relate_impl
        <
            detail::de9im::static_mask_overlaps_type,
            Geometry1,
            Geometry2
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief \brief_check2{overlap}
\ingroup overlaps
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Strategy \tparam_strategy{Overlaps}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param strategy \param_strategy{overlaps}
\return \return_check2{overlap}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/overlaps.qbk]}
*/
template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool overlaps(Geometry1 const& geometry1,
                     Geometry2 const& geometry2,
                     Strategy const& strategy)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();

    return dispatch::overlaps
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, strategy);
}

/*!
\brief \brief_check2{overlap}
\ingroup overlaps
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\return \return_check2{overlap}

\qbk{[include reference/algorithms/overlaps.qbk]}
\qbk{
[heading Examples]
[overlaps]
[overlaps_output]
}
*/
template <typename Geometry1, typename Geometry2>
inline bool overlaps(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();

    typedef typename strategy::relate::services::default_strategy
            <
                Geometry1,
                Geometry2
            >::type strategy_type;

    return dispatch::overlaps
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, strategy_type());
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAPS_INTERFACE_HPP

/* interface.hpp
izlv28chru0VF1b94thP1UvnW+tSeKm4P5a/Z17Bf/DXtweyv5z21On7lH7c73TRfCoMO85Hi3oua6Z8hs1XxV8bbhGje+PieMoPE/5698LqI2yA7io9zfeDfvU2fvaie7XXU/k1+eyS2FEObsibcnUV8/Xo72plXsleCfwq0w1XtKei4rHk8biBPKel3/fbA1zkPRxyjnjWAednd4vg3HcN5MqT9YzH2XfzkJ7nCXWtP/SSB/P7dmLsTP6XU+2qKF99wZzqWRf8ptsh+SCfuB02Nxisdmaet1m3rDhmqS76bZ0YWrJeKnZv/4qtd5PH9se3Sqi/icvD8KHeHR0/3B57a34M2GarhUezgzfGw6A35U30neGiZ9Bd6/Fp5vAWm4VPyy/wX/2kDvcm9yfjOovZnbwhSz35OuxvjZNtXC2O6VNMcI/clcTV93EF10++yfGgOFd4qD1MPeH6epg8XU6zwf1zqA24xkE6KZdXf+JhWPogPgbrs/tuD56UD5/LY06JAvDLZykvqHfJGxpXxysyia+95Gl5HOe7IS3xm0/4qLhXwP8LZdD/GKzeIE/6MY2aUbvEv/Ym76oAb9R0ltJnnevFilf5XXXj+FmP6z4135FstSgcEbuKlGIzaiMdXKdXM72ZvWzPtXt59nPkcbzlaXEhBzwlt5LM1rz2vXwsu3mIW6+ww3Xb5TO9xFw4fCmL1HWl2Mi3Z1vDm6fAR/u6WtrPcod9Pqnmm+EKnGyo5zSOby8TQ9p4xnGo+qEeb8WD7Dqt/HAz/ckRKha0d1APtDCsbWEdPqiP1+3Epfrzn+SesXLyC3x5tZzh7Fh9qhdcg/52/YRfLsGtn4NFa2M1DuPVk2v8GnvpYH9QH7XKXHyzDi7hmKz79YQm8Y1X1JIbwLYBcGaSGhWzyzNfb+VlvPRSMudja/LhPCfEa/XwkfRbmN7Wj9ArGWqPQ2dxo6Ta1UJ2/pXzh4V/9TJL29c5yHxG9pcbHGZn+pCtRshHF1g7XLPIEfGUXzSai0fBlJz2Zn1X39zbi/8peM0imPEZ7p1fLiuG3DwPl91Kr4XVzQrbP5Tbmm/nS+PVDeD3sLb80fc72cV6tvUFvx17HbxO9jSH4LtXkn7Gt+lhF5ttus4zJe3Y6+18oqB6Ct090wgWboJ/sK4cXrvdWo9d9dde5utXOzb5klQ42YLNVFmYxFh1xxzWHgdK/yMcgFOPpYEZ9+rT5hEDghqNNazCVwfIvY4Ok0cY67dizG1qADVegVH+v0ePOt0MdXjH5XKN1Qv4oj5End/p6mvYrsbZz8J8+Tp+PUpure/fE3a3LmQ9P+Y3xvHoBP4p5ve8Ygzs4XQ6eDVf3bIAPMT9+i/kK8n3FHyH7+XAV8n0s3jpHfwvdp1kXj8YN6+qRyEOTrN2O+nhuHHkuwIX9rmnOHJ/pP/UlC3AuUyfifHVcC7x+2V6+wduF7+OKzVjq9+7lnrBEPW08eytgzV+lA/t3cVvMuDfg2BfTmukdl+Hvby7VWhvKg/B++pnMh94PbF98vUG4mAd+YxjU/lX1ZH2J/XEb9hvN1hcjW4G3yk3x7FXzjVvazhIba9aWTXRu8TwpeJ5DvHmNbb5nbzDeCe8LSfCHdp3+mtfSeuifPQeuTNOMXCIOZXH4+jwH9b863Owors9lA/IL16Ux1QWq42lHTnp2svxk/rsO/mc0L5FeGN5cf5T2N4Jhs5kwx30/hryeePun02Nr6W9iOPU+4bgOGLlfSPxFLy86XH+wd7H2Qs5cgOdwPCoqufMuqkdlMX/2GqmZjixNa0/C77eKqduzJflq2Uy4sOenzwqr/h5h/gEMyfLhz7GqfoaV8HVyecSPTc=
*/