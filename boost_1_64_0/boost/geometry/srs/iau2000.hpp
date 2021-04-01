// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_IAU2000_HPP
#define BOOST_GEOMETRY_SRS_IAU2000_HPP


#include <boost/geometry/srs/projection.hpp>
#include <boost/geometry/srs/projections/iau2000.hpp>
#include <boost/geometry/srs/projections/iau2000_params.hpp>
#include <boost/geometry/srs/projections/iau2000_traits.hpp>


namespace boost { namespace geometry
{
    
namespace projections
{

template <>
struct dynamic_parameters<srs::iau2000>
{
    static const bool is_specialized = true;
    static inline srs::dpar::parameters<> apply(srs::iau2000 const& params)
    {
        return projections::detail::iau2000_to_parameters(params.code);
    }
};

template <int Code, typename CT>
class proj_wrapper<srs::static_iau2000<Code>, CT>
    : public proj_wrapper
        <
            typename projections::detail::iau2000_traits<Code>::parameters_type,
            CT
        >
{
    typedef projections::detail::iau2000_traits<Code> iau2000_traits;

    typedef proj_wrapper
        <
            typename iau2000_traits::parameters_type,
            CT
        > base_t;

public:
    proj_wrapper()
        : base_t(iau2000_traits::parameters())
    {}

    explicit proj_wrapper(srs::static_iau2000<Code> const&)
        : base_t(iau2000_traits::parameters())
    {}
};


} // namespace projections

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_IAU2000_HPP

/* iau2000.hpp
ShOUFcKEEl6iO/Wr7ytfYe7AOBJXTSBFendVl2knibPwUkRhId4jl96EvBGGs9IYZTlJVqHtRdVHgJ0M3ZoLa/JjkiM20cJ1EWn2Gp6wdgljULmJ+i+0D7rJ9UL0EzoPMUcxlbwesnBzocwNnVfBQHtsIOyXKGtJ1IIfWMBvc3U5CbEk7+pYTB+ej4hXToSovdxAIPm/6SdbRuUF5ZQDRSTRrC4M9DOe2BpTp7cRSdULknGYCG5f13DBSV14v/8j9c3I2GsEd+CWBfqiJIexjFetH32a39Yll/yG+l1tvUhJXQ7raelz2eP7tlQkmLiP8Y+BR88EiS/aGicXL9cLvhDQgPxIHQAGpHRnRdIOjx4P0rHoWgUwReNxlt6raURTQGgyhBtqIsAKxFSUmwg2oGpo+zk5/kwCvHQz6T0soe/lsJ+M11znScyUEUXtyvrovxVQ3cZ+1j6NZ+Go8cLJIYixM8PN92Tq3qGyw7+2e6cqaOEFQ7IgsmNQMTvR7IURu3gDFnZhNdUTxsVdHhbC6g52qYsOBQPz+wJvIUoAT+0LLS7IKUy+mYI16w==
*/