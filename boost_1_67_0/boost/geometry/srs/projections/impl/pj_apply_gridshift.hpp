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