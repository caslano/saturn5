// Boost.Geometry

// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERIOR_ITERATOR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERIOR_ITERATOR_HPP

#include <boost/range/iterator.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/interior_type.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

/*!
\brief Structure defining the type of interior rings iterator
\note If the Geometry is const, const iterator is defined.
\tparam Geometry \tparam_geometry
 */
template <typename Geometry>
struct interior_iterator
{
    typedef typename boost::range_iterator
        <
            typename geometry::interior_type<Geometry>::type        
        >::type type;
};

template <typename BaseT, typename T>
struct copy_const
{
    typedef T type;
};

template <typename BaseT, typename T>
struct copy_const<BaseT const, T>
{
    typedef T const type;
};

template <typename Geometry>
struct interior_ring_iterator
{
    typedef typename boost::range_iterator
        <
            typename copy_const
                <
                    typename geometry::interior_type<Geometry>::type,
                    typename boost::range_value
                        <
                            typename geometry::interior_type<Geometry>::type
                        >::type
                >::type
        >::type type;
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERIOR_ITERATOR_HPP

/* interior_iterator.hpp
mCc5xDVxN/0OKAZtfy8gBEfuUki+PfWLXage6YldN8b5vnGme1DnfGdj83jHtijcjTfkR2kR2vyZyIn/NdsY2HY3dPnpQXfxRSvQgsL4CTPXiyyQHz0B2D/5nPFSfimAeBHwNsv36eOqFSLPoyc7cyrj2uykYsBo/9tX0RJZQVgPA90lcWR06++9IbkAUq7cE+nMXNl6/lWpZuz67mG+V1LBLNgxWhQU2mfym9qVcYWW0P2/4NfoNQpsDcMYmaKDFhYBYUxnIcNvzy9UhJQelFt+1vLSD54Lm9OGlZfPRS/fu+Ep/4YFnHtFzHw9nfqQVEY6oomLoWBOTirvxVcWz6VeI9Qj3JsTL+vDsn/5FgH8OHNQoapjxvQOfmZkgcDjzwQrjkJFgfDXyBSBTJY3WOXK2pT+lMpLsZinxU4Do4U5va7QKINnvZMYZ+hthjtddeO57p+sCQ4b+so/P7wuMv7FAUJPdRGVyrTHoKkW+lgJyhvffYextLOh4eMpsxnOQwQn3WdEM9NWLa5WJRVcXGPKRMqbzdEClb4OjwqelzA/i7ddUvVGE+PzfA==
*/