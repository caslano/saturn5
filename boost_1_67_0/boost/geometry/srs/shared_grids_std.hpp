// Boost.Geometry

// Copyright (c) 2018-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_SHARED_GRIDS_STD_HPP
#define BOOST_GEOMETRY_SRS_SHARED_GRIDS_STD_HPP


#include <boost/config.hpp>

#ifdef BOOST_NO_CXX14_HDR_SHARED_MUTEX
#error "C++14 <shared_mutex> header required."
#endif

#include <boost/geometry/srs/projections/grids.hpp>

#include <mutex>
#include <shared_mutex>


namespace boost { namespace geometry
{
    
namespace srs
{

class shared_grids_std
{

// VS 2015 Update 2
#if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 190023918)
    typedef std::shared_mutex mutex_type;
// Other C++17
#elif !defined(BOOST_NO_CXX14_HDR_SHARED_MUTEX) && (__cplusplus > 201402L)
    typedef std::shared_mutex mutex_type;
#else
    typedef std::shared_timed_mutex mutex_type;
#endif

public:
    std::size_t size() const
    {
        std::shared_lock<mutex_type> lock(mutex);
        return gridinfo.size();
    }

    bool empty() const
    {
        std::shared_lock<mutex_type> lock(mutex);
        return gridinfo.empty();
    }

    typedef projections::detail::shared_grids_tag tag;

    struct read_locked
    {
        read_locked(shared_grids_std & g)
            : gridinfo(g.gridinfo)
            , lock(g.mutex)
        {}

        // should be const&
        projections::detail::pj_gridinfo & gridinfo;

    private:
        std::shared_lock<mutex_type> lock;
    };

    struct write_locked
    {
        write_locked(shared_grids_std & g)
            : gridinfo(g.gridinfo)
            , lock(g.mutex)
        {}

        projections::detail::pj_gridinfo & gridinfo;

    private:
        std::unique_lock<mutex_type> lock;
    };

private:
    projections::detail::pj_gridinfo gridinfo;
    mutable mutex_type mutex;
};


} // namespace srs


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_SHARED_GRIDS_STD_HPP

/* shared_grids_std.hpp
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
*/