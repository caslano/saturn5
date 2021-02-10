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
NhR+1684TYBODuTr9tAuWTHXdhajmRPITo2sKQRaoiIukiiIVGy36X/fOZRsR62NYEAdWJTP9eO5kTkWYRrwEC5G/eHI9QY37qU3HV2OBjPvwjpGjkj5fmb75Od9LDiBFz+e+Xr4wdVoXOfyX+7r/dKe9wTlH2rd4fqSkzbsVJ68Brys8gS2UfEqL2f07nkvObojbPRok+adR69IQTXSHMhsnYv7SIM9aED37ds30IRep9d1YMhSwWOYap4ueH7vwFlgKH9GbLVqKf7OAa6Bxa3K1CwSCpQM9ZLlHPA9Fj5PFQ+AKQi48nOxwB8iBR1xCEXMYXB1fTue/OXAMhJ+REbWsgAVySIOIGKPHHLuc/FY2shYrkGGqI7GA6E0Giy0kGkLfXPQPE8U2SD3LFYS2CMTMVugI6Yh0jpTv7fbfpHHiL4dSF+1/c32W5FOtju5RRAJW4PMNGgJheIOkKQDiQxESCsGBIlZsYiFipwdGnSVBm2Zg+JxTLZQT3BVwuYwrcLjkBhkiFhoWpRMFblaRjKpCWIcyUpY5Ck6wjigUCAxzA4U2Eq5ETY737ioYmoCfDA1O7wByBTBwFF/CuPpESyYEsqB+Xh2cXUzg3nfdfuT2S1cnUN/ckvGPownQ0y9QGc58FWWc4XOcxBJ
*/