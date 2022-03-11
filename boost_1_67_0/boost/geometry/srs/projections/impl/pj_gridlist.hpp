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