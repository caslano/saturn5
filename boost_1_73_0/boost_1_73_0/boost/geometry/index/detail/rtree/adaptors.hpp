// Boost.Geometry Index
//
// R-tree queries range adaptors
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_ADAPTORS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_ADAPTORS_HPP

#include <deque>
#include <boost/static_assert.hpp>

#include <boost/geometry/index/adaptors/query.hpp>

namespace boost { namespace geometry { namespace index {

template <typename Value, typename Options, typename IndexableGetter, typename EqualTo, typename Allocator>
class rtree;

namespace adaptors { namespace detail {

template <typename Value, typename Options, typename IndexableGetter, typename EqualTo, typename Allocator>
class query_range< index::rtree<Value, Options, IndexableGetter, EqualTo, Allocator> >
{
public:
    typedef std::vector<Value> result_type;
    typedef typename result_type::iterator iterator;
    typedef typename result_type::const_iterator const_iterator;

    template <typename Predicates> inline
    query_range(index::rtree<Value, Options, IndexableGetter, EqualTo, Allocator> const& rtree,
                Predicates const& pred)
    {
        rtree.query(pred, std::back_inserter(m_result));
    }

    inline iterator begin() { return m_result.begin(); }
    inline iterator end() { return m_result.end(); }
    inline const_iterator begin() const { return m_result.begin(); }
    inline const_iterator end() const { return m_result.end(); }

private:
    result_type m_result;
};

}} // namespace adaptors::detail

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_ADAPTORS_HPP

/* adaptors.hpp
dWptw+ztnu62DUGWlcYoxJg8Wd7vu/cnP7ZOfrYAJrtr6vxyrYnjAI1p0/dfMWnA9Qf7h65GrEZjLEz+vbhfJIB9ccUgWkGQ9u5g+OelQ6HYfNy6QUyYu3bIR7rP19woGqmxU9zD/bfq7e6fJf/PSbhX6Wdhhqv2rVrV6+jHo5NTzS0Ee9PonuJUbRDjPcc5PTrdPVg6UF3W6fTOI7H2ZcYfoAqLcjWR1QhxO5LxKQc1c/hDY2IChcPRwfDwh9Mfny9bCEz/dHh4Kk1H74aHuwenv4xO9v/3cPl3P74//OnOX/n7AW1Ph6NXB2s3Hx7/PDxe9QGuHlYEfx/jojiF+UlYPIoYTs5PtPQ8TLa1Kvk+2TbFmdzH289cFSBz7D6J6sg35bitalqXi1y7NYlfzJKC9IGWRsGOg3x7OIKVArhFUPOF6UVWTHgt/ZAKS2gXM7wUumiJrYZ5CWM9W5yBRMFL2rqkaDl2ZW6h4fRpRxqCVTr0uym+11dk73wl6W3w2yFvSg6Z5HPwrE2v3MVY09jdGR7aeKYluzpifd3vtblmj41p4R9xz+30/n6bP53eKy/S//CuoZfuIA7V+9uDbYdJLXJjuLs/AqHuJ7ZwFnsi0Gix2an+NPqvbF7Czvw3rPfZl4ghV0nLWJ98
*/