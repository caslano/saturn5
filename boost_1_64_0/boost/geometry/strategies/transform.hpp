// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_TRANSFORM_HPP
#define BOOST_GEOMETRY_STRATEGIES_TRANSFORM_HPP

#include <cstddef>

#include <boost/mpl/assert.hpp>

#include <boost/geometry/strategies/tags.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace transform { namespace services
{

/*!
    \brief Traits class binding a transformation strategy to a coordinate system
    \ingroup transform
    \details Can be specialized
    - per coordinate system family (tag)
    - per coordinate system (or groups of them)
    - per dimension
    - per point type
    \tparam CoordinateSystemTag 1,2 coordinate system tags
    \tparam CoordinateSystem 1,2 coordinate system
    \tparam D 1, 2 dimension
    \tparam Point 1, 2 point type
 */
template
<
    typename CoordinateSystemTag1, typename CoordinateSystemTag2,
    typename CoordinateSystem1, typename CoordinateSystem2,
    std::size_t Dimension1, std::size_t Dimension2,
    typename Point1, typename Point2
>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_POINT_TYPES
            , (types<Point1, Point2>)
        );
};

}}} // namespace strategy::transform::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_TRANSFORM_HPP

/* transform.hpp
Xu5+Sq2fe/BTtAnjXGv9PJTyuYwf10bej5pj/TzqPr/I0c9i6+cv6mcT4llu/fzVfX6Ro5/V1k9j6vgE8LOR99nC1xg/T7jxydFP1Pp5Uv1sQjwx6+cpNz45+olbPzPSxieH/cf6udCNT45+Fvh+8Kd+NiGeJdbPRW58cvTTbP30Szu+Nv68s9r6GejGJ0c/BdcaP4PUzybEU2j9DHbjk6OfmPVT7e5H5XicTrV+Euv8+MFEsvtp/f2g9TNZ/WzC/rPE+pni/OQYT4v1M9t9LpMSj7cR4xyeY+9vpPoJrH9d98vxRK2fa/zPZXKPJ2b9XOv7yT2euPUzp9GeB3OMp876uc75yTGeBuvner1+3oT5Wm79zFU/mzBfcp3xM50q5lreHKz5qX78l0kLBLzs95Gsn/NS/ER8V5l+PN9P9vcFRdbP+WuNn3qxAXnZ42nTxst+/WP9XJjiJ+KPY7Z4fD/Z379bP1uk7M/hlOvngB3ntYxztw2tH+vnmtR9Pj/LfvgLfuqtn+vcPp+jn8XWz/XqZxPiabJ+5rp9fiP9bH5tfm1+bX5tfm1+bX5tfv0nXmt5LbjJXJecEFwHya43+CrnKzn+deAL9vtCntH1Vl9u85dbfaPV+X83eozVRVZfYOuXWn2qzY9bPc7qOVaPtrrB6olWN1od9Wz7VveyeoXVQ61ebfVYW7+gyehtbX7U6oSL1+oaq0dYPcWNh9VnunitPsn6W+D8Wd1odamL1+oyq1usnubie9HoWhef1ee4+Fy+i8/q6VZXWn2u1TOtPs/qOqsv9ez4Wn2Z1UusPt+Wb7b6ArHjafXpno33peT9KV93t/oiq4utvtjFZ/U/XXxWz7K63uoT3PhZfamLx+r93PxafZlr/+Xk9zBM+1bf4dpz+bb+Yqt7u/mw+gVbPrLM3t928Vt9t4vX6nvd8WD1/e54eCX5uaOvC61+1OqpVjeKjcfqJW68rX7Gzf+rRj/r+mP1c76mntVXuPpWX+naf83oq1z7Vndx68Hqi914WD3blo8ut/dLXPtWH+3Wj9X7W53/D6P7Wl1k9WSr66y+3B2/Vo906+v15PtHM/5WX+v2B6uXiq1v9eNu/t6w90GsLrX6Ojd/Vl/t2fVl9RVWR95Mvl807Vs919W3ep6bf6unuf6/ZfQk13+rh1sdt7rS9cfqAjceVv/WxfO20ae5/li9zO1HVk+35ZusvtLF8469L231CKsrPFvf6mI3HlYPcvtRs/1+v9sPrZ7t5t/qepsv7xq9neu/1Te78bT6NqsXWH2W67+vSXfH9z+T3/8x8Vt9l9vfrB7t4rF6oc0Pv2c/57b5Masb3PhZ/Qc3n1bf5/bn95PfjzD9sfoBdzxY/aA7nq0+0h1PVj/s1ucHRh/hzo9WPyJ2/qw+383fh8nPgcx8WP1Xdz61+jh3PFs90LVv9WNuP/jI6Kl+Pmz1GLf/Wr3c7SdWX+XWw4rk5zemvtVPuvn0tf95imnf6hFuPXxs9N/c8WT1e26/t3obtx98YvTTNj9m9YVu/Vo9051vrb7GavnU6L+78bP6HXc8Wd3s1oPV77r91eqXXX+sLnTH50qjX3H+rN7TXT9ZfYw7Pq2OWR3+zOhj3fq0+jW3vqw+3p2/rD7Rjc/nRje548vqDq681Z3ceHxh9LWuPasrXbxWv+nWo9VjXbwt9nrO7SdWj3PXQ1ZXufVn9WFu/XxpdJFbf1b3cPFavV3IxvuV0WuCdv1Y3cnmx63uaHWD1Z1d/a+NbmN1odVhV9/q7UM2fqvbW73C6q9s+92/sePr6ls9ye3nVp/l1rPV77vj/1ujP3DzZfWH7vixusaNn9Vnu/rf2fXu9kOr93Y=
*/