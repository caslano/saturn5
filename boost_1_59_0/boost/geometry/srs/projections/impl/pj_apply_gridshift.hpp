// Boost.Geometry
// This file is manually converted from PROJ4

// This file was modified by Oracle on 2018, 2019.
// Modifications copyright (c) 2018-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// This file was converted to Geometry Library by Adam Wulkiewicz

// Original copyright notice:
// Author:   Frank Warmerdam, warmerdam@pobox.com

// Copyright (c) 2000, Frank Warmerdam

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_PJ_APPLY_GRIDSHIFT_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_PJ_APPLY_GRIDSHIFT_HPP


#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/radian_access.hpp>

#include <boost/geometry/srs/projections/impl/adjlon.hpp>
#include <boost/geometry/srs/projections/impl/function_overloads.hpp>
#include <boost/geometry/srs/projections/impl/pj_gridlist.hpp>

#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry { namespace projections
{

namespace detail
{

// Originally implemented in nad_intr.c
template <typename CalcT>
inline void nad_intr(CalcT in_lon, CalcT in_lat,
                     CalcT & out_lon, CalcT & out_lat,
                     pj_ctable const& ct)
{
	pj_ctable::lp_t frct;
	pj_ctable::ilp_t indx;
	boost::int32_t in;

	indx.lam = int_floor(in_lon /= ct.del.lam);
	indx.phi = int_floor(in_lat /= ct.del.phi);
	frct.lam = in_lon - indx.lam;
	frct.phi = in_lat - indx.phi;
    // TODO: implement differently
	out_lon = out_lat = HUGE_VAL;
	if (indx.lam < 0) {
		if (indx.lam == -1 && frct.lam > 0.99999999999) {
			++indx.lam;
			frct.lam = 0.;
		} else
			return;
	} else if ((in = indx.lam + 1) >= ct.lim.lam) {
		if (in == ct.lim.lam && frct.lam < 1e-11) {
			--indx.lam;
			frct.lam = 1.;
		} else
			return;
	}
	if (indx.phi < 0) {
		if (indx.phi == -1 && frct.phi > 0.99999999999) {
			++indx.phi;
			frct.phi = 0.;
		} else
			return;
	} else if ((in = indx.phi + 1) >= ct.lim.phi) {
		if (in == ct.lim.phi && frct.phi < 1e-11) {
			--indx.phi;
			frct.phi = 1.;
		} else
			return;
	}
	boost::int32_t index = indx.phi * ct.lim.lam + indx.lam;
	pj_ctable::flp_t const& f00 = ct.cvs[index++];
	pj_ctable::flp_t const& f10 = ct.cvs[index];
	index += ct.lim.lam;
	pj_ctable::flp_t const& f11 = ct.cvs[index--];
	pj_ctable::flp_t const& f01 = ct.cvs[index];
    CalcT m00, m10, m01, m11;
	m11 = m10 = frct.lam;
	m00 = m01 = 1. - frct.lam;
	m11 *= frct.phi;
	m01 *= frct.phi;
	frct.phi = 1. - frct.phi;
	m00 *= frct.phi;
	m10 *= frct.phi;
	out_lon = m00 * f00.lam + m10 * f10.lam +
			  m01 * f01.lam + m11 * f11.lam;
	out_lat = m00 * f00.phi + m10 * f10.phi +
			  m01 * f01.phi + m11 * f11.phi;
}

// Originally implemented in nad_cvt.c
template <bool Inverse, typename CalcT>
inline void nad_cvt(CalcT const& in_lon, CalcT const& in_lat,
                    CalcT & out_lon, CalcT & out_lat,
                    pj_gi const& gi)
{
    static const int max_iterations = 10;
    static const CalcT tol = 1e-12;
    static const CalcT toltol = tol * tol;
    static const CalcT pi = math::pi<CalcT>();

    // horizontal grid expected
    BOOST_GEOMETRY_ASSERT_MSG(gi.format != pj_gi::gtx,
        "Vertical grid cannot be used in horizontal shift.");

    pj_ctable const& ct = gi.ct;

    // TODO: implement differently
    if (in_lon == HUGE_VAL)
    {
        out_lon = HUGE_VAL;
        out_lat = HUGE_VAL;
        return;
    }

    // normalize input to ll origin
    pj_ctable::lp_t tb;
    tb.lam = in_lon - ct.ll.lam;
    tb.phi = in_lat - ct.ll.phi;
    tb.lam = adjlon (tb.lam - pi) + pi;

    pj_ctable::lp_t t;
    nad_intr(tb.lam, tb.phi, t.lam, t.phi, ct);
    if (t.lam == HUGE_VAL)
    {
        out_lon = HUGE_VAL;
        out_lat = HUGE_VAL;
        return;
    }

    if (! Inverse)
    {
        out_lon = in_lon - t.lam;
        out_lat = in_lat - t.phi;
        return;
    }

    t.lam = tb.lam + t.lam;
    t.phi = tb.phi - t.phi;

    int i = max_iterations;
    pj_ctable::lp_t del, dif;
    do
    {
        nad_intr(t.lam, t.phi, del.lam, del.phi, ct);

        // This case used to return failure, but I have
        // changed it to return the first order approximation
        // of the inverse shift.  This avoids cases where the
        // grid shift *into* this grid came from another grid.
        // While we aren't returning optimally correct results
        // I feel a close result in this case is better than
        // no result.  NFW
        // To demonstrate use -112.5839956 49.4914451 against
        // the NTv2 grid shift file from Canada.
        if (del.lam == HUGE_VAL)
        {
            // Inverse grid shift iteration failed, presumably at grid edge. Using first approximation.
            break;
        }

        dif.lam = t.lam - del.lam - tb.lam;
        dif.phi = t.phi + del.phi - tb.phi;
        t.lam -= dif.lam;
        t.phi -= dif.phi;

    }
    while (--i && (dif.lam*dif.lam + dif.phi*dif.phi > toltol)); // prob. slightly faster than hypot()

    if (i==0)
    {
        // Inverse grid shift iterator failed to converge.
        out_lon = HUGE_VAL;
        out_lat = HUGE_VAL;
        return;
    }

    out_lon = adjlon (t.lam + ct.ll.lam);
    out_lat = t.phi + ct.ll.phi;
}


/************************************************************************/
/*                             find_grid()                              */
/*                                                                      */
/*    Determine which grid is the correct given an input coordinate.    */
/************************************************************************/

// Originally find_ctable()
// here divided into grid_disjoint(), find_grid() and load_grid()

template <typename T>
inline bool grid_disjoint(T const& lam, T const& phi,
                          pj_ctable const& ct)
{
    double epsilon = (fabs(ct.del.phi)+fabs(ct.del.lam))/10000.0;
    return ct.ll.phi - epsilon > phi
        || ct.ll.lam - epsilon > lam
        || (ct.ll.phi + (ct.lim.phi-1) * ct.del.phi + epsilon < phi)
        || (ct.ll.lam + (ct.lim.lam-1) * ct.del.lam + epsilon < lam);
}

template <typename T>
inline pj_gi * find_grid(T const& lam,
                         T const& phi,
                         std::vector<pj_gi>::iterator first,
                         std::vector<pj_gi>::iterator last)
{
    pj_gi * gip = NULL;

    for( ; first != last ; ++first )
    {
        // skip tables that don't match our point at all.
        if (! grid_disjoint(lam, phi, first->ct))
        {
            // skip vertical grids
            if (first->format != pj_gi::gtx)
            {
                gip = boost::addressof(*first);
                break;
            }
        }
    }

    // If we didn't find a child then nothing more to do
    if( gip == NULL )
        return gip;

    // Otherwise use the child, first checking it's children
    pj_gi * child = find_grid(lam, phi, first->children.begin(), first->children.end());
    if (child != NULL)
        gip = child;

    return gip;
}

template <typename T>
inline pj_gi * find_grid(T const& lam,
                         T const& phi,
                         pj_gridinfo & grids,
                         std::vector<std::size_t> const& gridindexes)
{
    pj_gi * gip = NULL;

    // keep trying till we find a table that works
    for (std::size_t i = 0 ; i < gridindexes.size() ; ++i)
    {
        pj_gi & gi = grids[gridindexes[i]];

        // skip tables that don't match our point at all.
        if (! grid_disjoint(lam, phi, gi.ct))
        {
            // skip vertical grids
            if (gi.format != pj_gi::gtx)
            {
                gip = boost::addressof(gi);
                break;
            }
        }
    }

    if (gip == NULL)
        return gip;

    // If we have child nodes, check to see if any of them apply.
    pj_gi * child = find_grid(lam, phi, gip->children.begin(), gip->children.end());
    if (child != NULL)
        gip = child;

    // if we get this far we have found a suitable grid
    return gip;
}


template <typename StreamPolicy>
inline bool load_grid(StreamPolicy const& stream_policy, pj_gi_load & gi)
{
    // load the grid shift info if we don't have it.
    if (gi.ct.cvs.empty())
    {
        typename StreamPolicy::stream_type is;
        stream_policy.open(is, gi.gridname);

        if (! pj_gridinfo_load(is, gi))
        {
            //pj_ctx_set_errno( ctx, PJD_ERR_FAILED_TO_LOAD_GRID );
            return false;
        }
    }

    return true;
}


/************************************************************************/
/*                        pj_apply_gridshift_3()                        */
/*                                                                      */
/*      This is the real workhorse, given a gridlist.                   */
/************************************************************************/

// Generic stream policy and standard grids
template <bool Inverse, typename CalcT, typename StreamPolicy, typename Range, typename Grids>
inline bool pj_apply_gridshift_3(StreamPolicy const& stream_policy,
                                 Range & range,
                                 Grids & grids,
                                 std::vector<std::size_t> const& gridindexes,
                                 grids_tag)
{
    typedef typename boost::range_size<Range>::type size_type;
    
    // If the grids are empty the indexes are as well
    if (gridindexes.empty())
    {
        //pj_ctx_set_errno(ctx, PJD_ERR_FAILED_TO_LOAD_GRID);
        //return PJD_ERR_FAILED_TO_LOAD_GRID;
        return false;
    }

    size_type point_count = boost::size(range);

    for (size_type i = 0 ; i < point_count ; ++i)
    {
        typename boost::range_reference<Range>::type
            point = range::at(range, i);

        CalcT in_lon = geometry::get_as_radian<0>(point);
        CalcT in_lat = geometry::get_as_radian<1>(point);
        
        pj_gi * gip = find_grid(in_lon, in_lat, grids.gridinfo, gridindexes);

        if ( gip != NULL )
        {
            // load the grid shift info if we don't have it.
            if (! gip->ct.cvs.empty() || load_grid(stream_policy, *gip))
            {
                // TODO: use set_invalid_point() or similar mechanism
                CalcT out_lon = HUGE_VAL;
                CalcT out_lat = HUGE_VAL;

                nad_cvt<Inverse>(in_lon, in_lat, out_lon, out_lat, *gip);
            
                // TODO: check differently
                if ( out_lon != HUGE_VAL )
                {
                    geometry::set_from_radian<0>(point, out_lon);
                    geometry::set_from_radian<1>(point, out_lat);
                }
            }
        }
    }

    return true;
}

// Generic stream policy and shared grids
template <bool Inverse, typename CalcT, typename StreamPolicy, typename Range, typename SharedGrids>
inline bool pj_apply_gridshift_3(StreamPolicy const& stream_policy,
                                 Range & range,
                                 SharedGrids & grids,
                                 std::vector<std::size_t> const& gridindexes,
                                 shared_grids_tag)
{
    typedef typename boost::range_size<Range>::type size_type;
    
    // If the grids are empty the indexes are as well
    if (gridindexes.empty())
    {
        //pj_ctx_set_errno(ctx, PJD_ERR_FAILED_TO_LOAD_GRID);
        //return PJD_ERR_FAILED_TO_LOAD_GRID;
        return false;
    }

    size_type point_count = boost::size(range);

    // local storage
    pj_gi_load local_gi;

    for (size_type i = 0 ; i < point_count ; )
    {
        bool load_needed = false;

        CalcT in_lon = 0;
        CalcT in_lat = 0;

        {
            typename SharedGrids::read_locked lck_grids(grids);

            for ( ; i < point_count ; ++i )
            {
                typename boost::range_reference<Range>::type
                    point = range::at(range, i);

                in_lon = geometry::get_as_radian<0>(point);
                in_lat = geometry::get_as_radian<1>(point);

                pj_gi * gip = find_grid(in_lon, in_lat, lck_grids.gridinfo, gridindexes);

                if (gip == NULL)
                {
                    // do nothing
                }
                else if (! gip->ct.cvs.empty())
                {
                    // TODO: use set_invalid_point() or similar mechanism
                    CalcT out_lon = HUGE_VAL;
                    CalcT out_lat = HUGE_VAL;

                    nad_cvt<Inverse>(in_lon, in_lat, out_lon, out_lat, *gip);

                    // TODO: check differently
                    if (out_lon != HUGE_VAL)
                    {
                        geometry::set_from_radian<0>(point, out_lon);
                        geometry::set_from_radian<1>(point, out_lat);
                    }
                }
                else
                {
                    // loading is needed
                    local_gi = *gip;
                    load_needed = true;
                    break;
                }
            }
        }

        if (load_needed)
        {
            if (load_grid(stream_policy, local_gi))
            {
                typename SharedGrids::write_locked lck_grids(grids);

                // check again in case other thread already loaded the grid.
                pj_gi * gip = find_grid(in_lon, in_lat, lck_grids.gridinfo, gridindexes);

                if (gip != NULL && gip->ct.cvs.empty())
                {
                    // swap loaded local storage with empty grid
                    local_gi.swap(*gip);
                }
            }
            else
            {
                ++i;
            }
        }
    }

    return true;
}


/************************************************************************/
/*                        pj_apply_gridshift_2()                        */
/*                                                                      */
/*      This implementation uses the gridlist from a coordinate         */
/*      system definition.  If the gridlist has not yet been            */
/*      populated in the coordinate system definition we set it up      */
/*      now.                                                            */
/************************************************************************/

template <bool Inverse, typename Par, typename Range, typename ProjGrids>
inline bool pj_apply_gridshift_2(Par const& /*defn*/, Range & range, ProjGrids const& proj_grids)
{
    /*if( defn->catalog_name != NULL )
        return pj_gc_apply_gridshift( defn, inverse, point_count, point_offset,
                                      x, y, z );*/

    /*std::vector<std::size_t> gridindexes;
    pj_gridlist_from_nadgrids(pj_get_param_s(defn.params, "nadgrids"),
                              grids.storage_ptr->stream_policy,
                              grids.storage_ptr->grids,
                              gridindexes);*/

    // At this point the grids should be initialized
    if (proj_grids.hindexes.empty())
        return false;

    return pj_apply_gridshift_3
            <
                Inverse, typename Par::type
            >(proj_grids.grids_storage().stream_policy,
              range,
              proj_grids.grids_storage().hgrids,
              proj_grids.hindexes,
              typename ProjGrids::grids_storage_type::grids_type::tag());
}

template <bool Inverse, typename Par, typename Range>
inline bool pj_apply_gridshift_2(Par const& , Range & , srs::detail::empty_projection_grids const& )
{
    return false;
}


} // namespace detail

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_PJ_APPLY_GRIDSHIFT_HPP

/* pj_apply_gridshift.hpp
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
*/