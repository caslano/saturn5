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
KIrN7WxIRCdxklEWbe8oaEN5NNa0MEYSMyKthEdBdKrDj0lz82H/U4mn1PTE52ZdMQ8Kfyzk4uMZXduHcg4ZQq5JnZ4ZCDeGXNit719v55wXpNH5lKtvDo1xB70hTkOszsR/qm3FgC3wmbUP5HzuQeIGqbK6Nkuz+429UNnWUhtrb6+MaltLT9CcfTHCfT/W3d+dp/I74jWNnc0HV2urorJDzx9t2hSXf5yTXZUubrwrY5aL28Plm+PiJri4unXqGpObGLPPaV+j+2ZP883dhncczXISeVf115ivbGnvsH0t5bqEqpZOPCpO3sf76vVi9+3oRPzfKfOGZHyu1A+3e9UUBlpK64xdTjXeFwIn93vr2uVV3bfFu63fNYa+ykq+BXReir1WaO42cH4J9H9tND6lScT1UJPjLXNtpPBh9FTW3STiNlEVmG1K6GHsify6ujYokaKLjV2RSPDjvzb4M3aOmZP0gl7fCHo99wPmJGnvWv+BtppZk1yfXePaV1peUmEKkxHONlJDknMkPQYhL+knyzF+xuIpzLjjMcs7o03cjJQ4jzLgqGh7frypoXl+jJFx9ntYp9l/Gd14XyThv8ww3xU0dVhbpp/FR8vBTYlJlplj0emePcib0Y17/vexZfc0ZXcqWy7fmobH6rS1awtPnsV2nXLnrzcRfeqzEfMnjX3w5vbzXiqxL/2fdTEnVzKS8dKuMnPvXsm0qlit9d9ZuZWZTEsAW6dZP1m5uSDFiVGb1pt+ZSe/K23WW8iivo92H7t+tano++kb4T+QumNOQLcs7pPqz1y9SUo6taaGHw98n034XUvLPrQvqIueNz4lK0+Lmxc2tbWYAS2It9QebGm2Od81BvTSFsS92idVL21J3NIBNfH26niLwaad8y4dmKp/Msm33MWNS+qTrRNxJXhM406m9yX/HJsm9c/SramreHFrtFkLb7/S4XbO10+MxfKtIzUJ+V2j5bfwdYTF7x5h3zfh5EU3fBOa1gOH+LT2oPU5ltYDiAvOsbcycQaq4g0i5qowFiMQb2lQTj57vryvqNeIb1fO5xL2fSnOBPP9Li4+xc+8teZ966PRxST2mG1C8YMEfXp2Qx7Wp/BjAdVL3nH82FzndIjwgds2aKZJJAfTtCebb5zfcrCUIz+Cryf9vVxmHSS/ppBXp1JMwTTxVq9sZ3XCd2Iu7tYUKmuV06dpfASZAR9Bcm5b3K5ftW9q55EWf4FJzHFruNgs1lHaauKMP3FEYj5rJZuO/0DPB1RZtLmhk2qtChIyb4KycZrQNv5FPWdQUwASbqYa89a+G7Mpqrq2pTVWyrNCi+VYluGjicdzDD03U6g3MU6VG0nPdL7SLMqTvtLsIW4dkTx++puBvWc7DHH7gQzN5BrzMNJmhxJrdboZZfkH6NvWSidHqgvzy8tKy4sjiOFi7ZMH9dWVxYX+U2l27W6D3+Aon6w3LZfOdOeDN/hNKSSoKssv1Od5N/6byIxKXumikWVFJaVV1TWJMsIbU0ZZxf7pylBLv99QISUV5s0+ysKMnyneiBs+ZIMU9hciN5BJ78ve1I1ZJFJanR/Jn5lfWmas5VkTxruxCaaxdTzXnkFOlzY2Vxk6BdP4NcvtSw+mFZeXsGIz2ab3SPetrVOtm1Y1vbxGpW9rebF7zzBtmv54/FizrgqNe1saj4DGIm9pWWnNAT5Rg7H+um4XdnXxTASjsb4iRcXVhVWllVjjhlXTJzmbeKSVf80p8k9PH4W89/2vLtzH2Q5K7Deu0e9DufDmAbskuBY61dpYuwp5k/kD+3Fkylp3acp6rxfQ2b6NUNgYbW6OxYkT86/YwlhczL3s0q8uy60J17C6Kuc=
*/