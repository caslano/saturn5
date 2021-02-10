// Boost.Geometry

// This file was modified by Oracle on 2018, 2019.
// Modifications copyright (c) 2018, 2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_GRIDS_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_GRIDS_HPP


#include <boost/geometry/srs/projections/impl/pj_gridinfo.hpp>

#include <fstream>


namespace boost { namespace geometry
{


namespace projections { namespace detail
{


struct grids_tag {};
struct shared_grids_tag {};


}} // namespace projections::detail

namespace srs
{

class grids
{
public:
    std::size_t size() const
    {
        return gridinfo.size();
    }

    bool empty() const
    {
        return gridinfo.empty();
    }

    typedef projections::detail::grids_tag tag;

    projections::detail::pj_gridinfo gridinfo;
};

struct ifstream_policy
{
    typedef std::ifstream stream_type;

    static inline void open(stream_type & is, std::string const& gridname)
    {
        is.open(gridname.c_str(), std::ios::binary);
    }
};

template
<
    typename StreamPolicy = srs::ifstream_policy,
    typename Grids = grids
>
struct grids_storage
{
    typedef StreamPolicy stream_policy_type;
    typedef Grids grids_type;

    grids_storage()
    {}

    explicit grids_storage(stream_policy_type const& policy)
        : stream_policy(policy)
    {}

    stream_policy_type stream_policy;
    grids_type hgrids;
};


template <typename GridsStorage = grids_storage<> >
class projection_grids
{
public:
    projection_grids(GridsStorage & storage)
        : m_storage_ptr(boost::addressof(storage))
    {}

    typedef GridsStorage grids_storage_type;

    GridsStorage & grids_storage() const
    {
        return *m_storage_ptr;
    }

private:
    GridsStorage * const m_storage_ptr;

public:
    std::vector<std::size_t> hindexes;
};


template <typename GridsStorage = grids_storage<> >
struct transformation_grids
{
    explicit transformation_grids(GridsStorage & storage)
        : src_grids(storage)
        , dst_grids(storage)
    {}

    projection_grids<GridsStorage> src_grids;
    projection_grids<GridsStorage> dst_grids;
};


namespace detail
{

struct empty_grids_storage {};
struct empty_projection_grids {};

} // namespace detail


template <>
struct transformation_grids<detail::empty_grids_storage>
{
    detail::empty_projection_grids src_grids;
    detail::empty_projection_grids dst_grids;
};


}}} // namespace boost::geometry::srs


#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_GRIDS_HPP

/* grids.hpp
pFDXuCN+e3HkMUM1jE+lGxHQO5nFCck5kk90FR4HHsIUr7FN4nFc2BOn5bg5r3mTrr47eHR7D2Xfp8L4hrTJCwqjUr1LbbXBk4CgU/OoVg7dxF4ZTz5Gm+G/AVBLAwQKAAAACAAtZ0pSPRSKEWoEAAAIDQAAFwAJAGN1cmwtbWFzdGVyL2xpYi9zZW5kZi5oVVQFAAG2SCRgrVdtb+I4EP7Or5ijXwBlYbu6D9e76nQ00C1aDipCt0KqZDmJ0/g2sSPboXDqj7+xA4X2aCjSpmpenJl5ZuaZGYcznoiYJXAz7A+GM+LfzcYkGE4G1+SmcYYvuGAH3/U6P+9oQAeOHsT9Ezzw6jRulfyHReawNCHPUP2h1gNej4H0YKfyTNpwXOUZWk6FbFAu7T0hx4AerG/21LOaD8Te4gqqWU1fFmvFH1MDLb8N5xcXv8En+PL5y7kHAyo4yyAwTIRMPXpwGbuVv1K6WnU1+9MDZoBm3Y2peco1aJmYJ6oY4H3GIyY0i4FqiJmOFA/xgQswKYOEZwz86e1iNPnqwVPKo9QaWcsSdCrLLIaULhkoFjG+rGwUVBmQCaqj8ZhrgwZLw6XoIjYDw1SurQ0LTzMtgS4pz2iIQNRAakyhf+/1olJl6H0vlpHuRdvwu6nJXyJZ
*/