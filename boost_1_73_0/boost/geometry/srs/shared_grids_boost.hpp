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
c/h98PnmfBT4Nxy+/ILYflCE3+Xwl8Lj/TOJ4H2e9Y2b4S+AS/+2zfvj/udV8Oc5/MVwU/9eDX+uw38MN/XvNfDnOHzjFaJ9zkkEA579Hyn4UyR37dfwmmrBHf35Hvh9k9Nn9edPwu+dIn21Zn0R/vXJ6bP68zfgn/ek786jEsF5nvHlHvhyz/enPgk/xzO+BLWJoODZ/1sFH/Xs/62G++z3Bfh+z/frr4V3weeL9O94etz+
*/