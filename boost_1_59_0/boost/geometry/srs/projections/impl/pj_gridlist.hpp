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

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_PJ_GRIDLIST_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_PJ_GRIDLIST_HPP


#include <boost/geometry/srs/projections/exception.hpp>
#include <boost/geometry/srs/projections/grids.hpp>
#include <boost/geometry/srs/projections/impl/pj_gridinfo.hpp>
#include <boost/geometry/srs/projections/impl/pj_strerrno.hpp>
#include <boost/geometry/srs/projections/par_data.hpp>


namespace boost { namespace geometry { namespace projections
{

namespace detail
{

/************************************************************************/
/*                       pj_gridlist_merge_grid()                       */
/*                                                                      */
/*      Find/load the named gridfile and merge it into the              */
/*      last_nadgrids_list.                                             */
/************************************************************************/

// Originally one function, here divided into several functions
// with overloads for various types of grids and stream policies

inline bool pj_gridlist_find_all(std::string const& gridname,
                                 pj_gridinfo const& grids,
                                 std::vector<std::size_t> & gridindexes)
{
    bool result = false;
    for (std::size_t i = 0 ; i < grids.size() ; ++i)
    {
        if (grids[i].gridname == gridname)
        {
            result = true;
            gridindexes.push_back(i);
        }
    }
    return result;
}

// Fill container with sequentially increasing numbers
inline void pj_gridlist_add_seq_inc(std::vector<std::size_t> & gridindexes,
                                    std::size_t first, std::size_t last)
{
    gridindexes.reserve(gridindexes.size() + (last - first));
    for ( ; first < last ; ++first)
    {
        gridindexes.push_back(first);
    }
}

// Generic stream policy and standard grids
template <typename StreamPolicy, typename Grids>
inline bool pj_gridlist_merge_gridfile(std::string const& gridname,
                                       StreamPolicy const& stream_policy,
                                       Grids & grids,
                                       std::vector<std::size_t> & gridindexes,
                                       grids_tag)
{
    // Try to find in the existing list of loaded grids.  Add all
    // matching grids as with NTv2 we can get many grids from one
    // file (one shared gridname).    
    if (pj_gridlist_find_all(gridname, grids.gridinfo, gridindexes))
        return true;

    std::size_t orig_size = grids.gridinfo.size();

    // Try to load the named grid.
    typename StreamPolicy::stream_type is;
    stream_policy.open(is, gridname);

    if (! pj_gridinfo_init(gridname, is, grids.gridinfo))
    {
        return false;
    }

    // Add the grid now that it is loaded.
    pj_gridlist_add_seq_inc(gridindexes, orig_size, grids.gridinfo.size());
    
    return true;
}

// Generic stream policy and shared grids
template <typename StreamPolicy, typename SharedGrids>
inline bool pj_gridlist_merge_gridfile(std::string const& gridname,
                                       StreamPolicy const& stream_policy,
                                       SharedGrids & grids,
                                       std::vector<std::size_t> & gridindexes,
                                       shared_grids_tag)
{
    // Try to find in the existing list of loaded grids.  Add all
    // matching grids as with NTv2 we can get many grids from one
    // file (one shared gridname).    
    {
        typename SharedGrids::read_locked lck_grids(grids);
        
        if (pj_gridlist_find_all(gridname, lck_grids.gridinfo, gridindexes))
            return true;
    }

    // Try to load the named grid.
    typename StreamPolicy::stream_type is;
    stream_policy.open(is, gridname);

    pj_gridinfo new_grids;
    
    if (! pj_gridinfo_init(gridname, is, new_grids))
    {
        return false;
    }

    // Add the grid now that it is loaded.

    std::size_t orig_size = 0;
    std::size_t new_size = 0;

    {
        typename SharedGrids::write_locked lck_grids(grids);

        // Try to find in the existing list of loaded grids again
        // in case other thread already added it.
        if (pj_gridlist_find_all(gridname, lck_grids.gridinfo, gridindexes))
            return true;

        orig_size = lck_grids.gridinfo.size();
        new_size = orig_size + new_grids.size();

        lck_grids.gridinfo.resize(new_size);
        for (std::size_t i = 0 ; i < new_grids.size() ; ++ i)
            new_grids[i].swap(lck_grids.gridinfo[i + orig_size]);
    }
    
    pj_gridlist_add_seq_inc(gridindexes, orig_size, new_size);
    
    return true;
}


/************************************************************************/
/*                     pj_gridlist_from_nadgrids()                      */
/*                                                                      */
/*      This functions loads the list of grids corresponding to a       */
/*      particular nadgrids string into a list, and returns it. The     */
/*      list is kept around till a request is made with a different     */
/*      string in order to cut down on the string parsing cost, and     */
/*      the cost of building the list of tables each time.              */
/************************************************************************/

template <typename StreamPolicy, typename Grids>
inline void pj_gridlist_from_nadgrids(srs::detail::nadgrids const& nadgrids,
                                      StreamPolicy const& stream_policy,
                                      Grids & grids,
                                      std::vector<std::size_t> & gridindexes)

{
    // Loop processing names out of nadgrids one at a time.
    for (srs::detail::nadgrids::const_iterator it = nadgrids.begin() ;
            it != nadgrids.end() ; ++it)
    {
        bool required = (*it)[0] != '@';
        
        std::string name(it->begin() + (required ? 0 : 1), it->end());

        if ( ! pj_gridlist_merge_gridfile(name, stream_policy, grids, gridindexes,
                                          typename Grids::tag())
          && required )
        {
            BOOST_THROW_EXCEPTION( projection_exception(error_failed_to_load_grid) );
        }
    }
}

template <typename Par, typename ProjectionGrids>
inline void pj_gridlist_from_nadgrids(Par const& defn, ProjectionGrids & proj_grids)
{
    pj_gridlist_from_nadgrids(defn.nadgrids,
                              proj_grids.grids_storage().stream_policy,
                              proj_grids.grids_storage().hgrids,
                              proj_grids.hindexes);
}


} // namespace detail

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_PJ_GRIDLIST_HPP

/* pj_gridlist.hpp
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
*/