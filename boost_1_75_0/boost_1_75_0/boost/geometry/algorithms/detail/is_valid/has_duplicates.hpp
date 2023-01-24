// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_DUPLICATES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_DUPLICATES_HPP

#include <boost/core/ignore_unused.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/closure.hpp>

#include <boost/geometry/policies/compare.hpp>
#include <boost/geometry/policies/is_valid/default_policy.hpp>

#include <boost/geometry/views/closeable_view.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{

template <typename Range, closure_selector Closure, typename CSTag>
struct has_duplicates
{
    template <typename VisitPolicy>
    static inline bool apply(Range const& range, VisitPolicy& visitor)
    {
        boost::ignore_unused(visitor);

        typedef typename closeable_view<Range const, Closure>::type view_type;
        typedef typename boost::range_const_iterator
            <
                view_type const
            >::type const_iterator;

        view_type view(range);

        if ( boost::size(view) < 2 )
        {
            return ! visitor.template apply<no_failure>();
        }

        geometry::equal_to
            <
                typename boost::range_value<Range>::type,
                -1,
                CSTag
            > equal;

        const_iterator it = boost::const_begin(view);
        const_iterator next = it;
        ++next;
        for (; next != boost::const_end(view); ++it, ++next)
        {
            if ( equal(*it, *next) )
            {
                return ! visitor.template apply<failure_duplicate_points>(*it);
            }
        }
        return ! visitor.template apply<no_failure>();
    }
};



}} // namespace detail::is_valid
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry



#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_HAS_DUPLICATES_HPP

/* has_duplicates.hpp
2EahSi4JyJlizHrfDiqs/ZKhUMRsxBWjcz/Cp8X9WN6pHLPejrNgVyuxXFQ8cr50u/VmrBbaVqu5aElEB1a1ppKxmTUSuYFOcpO77KJumOL6f/0ct50Gnpv7I/ZWDbdk9hvMEvdqeC49r/e/itcABnFAeQDLActJLIdh482TXhc9gg+1EQUhRO0iK6olqGRJ7IzCBXihbcgZxTHImtiP8r0AnsuRcqznMqn6RO/mWD4pxwV2saP/OXy7EBB7SDEWWvrkkJIDjdICpchCjVGlSCVXNvE2yYA2ccVtk8ojGegoKcsN4Hn0iKb3zBVNV0WZSzBF9MWMas+0H9lVzD0FsWUf4Oc9C9nuXzmI74TSb4XVsVu507JNXQhEZY3FJ1dKW8XXXY9gR677PrLrtLlyHPn2AZvHms4amOw0tGo5kqoGLakKUd4NunLtw5wX+o7y9WYyeCrBNR81yLczdFYvZojyw2qPRstm3pjg/kQoELOlMrmO2owlqqZluIgqYRAe7fcSUQq0q+WCMigPSP1iKKFO4PNkz1GORz4CnkFwXxzV1gZu35c109kI418nd3bge+jy8IFensHHH4alcZQH0IBiLE3Dch7eJ+dbZgtKP+zKAXKXKVUMYbpTcc4Q85/me9808FSDW/h05B5AjrZS/vvcp/Wp+PduJ2oVLOMwUKpheqLI734nvA5T8hC5y23GPPaC+93TbI192JDo
*/