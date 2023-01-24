// Boost.Geometry

// Copyright (c) 2018-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_SHARED_GRIDS_BOOST_HPP
#define BOOST_GEOMETRY_SRS_SHARED_GRIDS_BOOST_HPP


#include <boost/geometry/srs/projections/grids.hpp>


#include <boost/thread.hpp>


namespace boost { namespace geometry
{
    
namespace srs
{

class shared_grids_boost
{
public:
    std::size_t size() const
    {
        boost::shared_lock<boost::shared_mutex> lock(mutex);
        return gridinfo.size();
    }

    bool empty() const
    {
        boost::shared_lock<boost::shared_mutex> lock(mutex);
        return gridinfo.empty();
    }

    typedef projections::detail::shared_grids_tag tag;

    struct read_locked
    {
        read_locked(shared_grids_boost & g)
            : gridinfo(g.gridinfo)
            , lock(g.mutex)
        {}

        // should be const&
        projections::detail::pj_gridinfo & gridinfo;

    private:
        boost::shared_lock<boost::shared_mutex> lock;
    };

    struct write_locked
    {
        write_locked(shared_grids_boost & g)
            : gridinfo(g.gridinfo)
            , lock(g.mutex)
        {}

        projections::detail::pj_gridinfo & gridinfo;

    private:
        boost::unique_lock<boost::shared_mutex> lock;
    };

private:
    projections::detail::pj_gridinfo gridinfo;
    mutable boost::shared_mutex mutex;
};


} // namespace srs


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_SHARED_GRIDS_BOOST_HPP

/* shared_grids_boost.hpp
kOZ97BwrnhrDgFaV4bNsdKuMUdVev7t4fusDP/DOsc/klgCbqWgOIa3glXJ4BT8/FP+wrCASMrfayDB9aby7hSeWl+TDR1WQzUt11ynX1QbxbdGfpP2Xe3Et+hllQRAjHQsd/UK7DpLCux9Zn+zcf5JtszphRg436bBBQ8sJnTF/1zGCouwYb8x7pi6/BkSZ0jIcnTplhjfx/YkPcqkumLyMEVjm2BLsIZNPcyK3tNhiRZhI6kA7dVC7ajhoVkjwOOmYT/KITy4cuV5+VjQTEg2gve8mvIPHjNacMydJ/KEpy20qAmh767cya+dWSmnQVSQthkGid503n1uo+FLHVvyRfb1xvC/FO14/dpyPKDqEUNhG4FWLvG9/74Y1gLpuKXBW02u7NAped2qqEauszaouJeXaEjjBtsTuxFMWJ4W4KjFB3OaGT/5i/hPIK0YvXAycDZiZZmfrfhvL+zncn60P6703Yv2aDKwyYODr3jRPCfTzvhTrpeJL/ZQtYIxxPY5//pdTSQ5xtYe5y+qrALjFaQJIPihrnv15p5i8RwQqrTmWokz74Fr0qi0Zxa4uLDxUHHP5m1IxIDVQLMP6MmuVo1w8RQsr0jxSRhnd/7yXrQZZQOSZjXSrWCVVxg7MSftLOew3wdu1o5Zy3YnQxGU0Qc9J2vGB98qM5d8bm+6JiUrlrhCKncma9tWNi38nrPwyXXPrKfuz8wWb
*/