// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_POINT_ORDER_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_POINT_ORDER_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/point_order.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace point_order
{

template
    <
        typename FormulaPolicy = strategy::andoyer,
        typename Spheroid = srs::spheroid<double>,
        typename CalculationType = void
    >
struct geographic
{
    typedef azimuth_tag version_tag;

    template <typename Geometry>
    struct result_type
    {
        typedef typename geometry::select_calculation_type_alt
            <
                CalculationType, Geometry
            >::type type;
    };

    geographic()
    {}

    explicit geographic(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    template <typename Point>
    inline bool apply(Point const& p1, Point const& p2,
                      typename result_type<Point>::type & azi,
                      typename result_type<Point>::type & razi) const
    {
        typedef typename result_type<Point>::type calc_t;

        if (equals_point_point(p1, p2))
        {
            return false;
        }

        formula::result_inverse<calc_t> res = FormulaPolicy::template inverse
            <
                calc_t, false, true, true, false, false
            >::apply(geometry::get_as_radian<0>(p1),
                     geometry::get_as_radian<1>(p1),
                     geometry::get_as_radian<0>(p2),
                     geometry::get_as_radian<1>(p2),
                     m_spheroid);

        azi = res.azimuth;
        razi = res.reverse_azimuth;

        return true;
    }

    template <typename Point>
    inline typename result_type<Point>::type
    apply(Point const& /*p0*/, Point const& /*p1*/, Point const& /*p2*/,
          typename result_type<Point>::type const& azi1,
          typename result_type<Point>::type const& azi2) const
    {
        // TODO: support poles
        return math::longitude_distance_signed<radian>(azi1, azi2);
    }

private:
    template <typename Point>
    static bool equals_point_point(Point const& p0, Point const& p1)
    {
        return strategy::within::spherical_point_point::apply(p0, p1);
    }

    Spheroid m_spheroid;
};

namespace services
{

template <>
struct default_strategy<geographic_tag>
{
    typedef geographic<> type;
};

} // namespace services

}} // namespace strategy::point_order

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_POINT_ORDER_HPP

/* point_order.hpp
Y0kESSTrSQ4pTGQcWG4I0zaf5UZchzAecpxlMRZ96BZBEvk9mWSQk+Q8SaJ7CaZj3aFMOxlMfEku3ZIwjRwnZ/owP/AqUW5c2JOL9NMGw0gyySJ5RDmBcSLnh1En9CFhpIS/V6CHN/vvPowLA0gSSSdZC5gHeIacXcA4hlMXUqgMj/Gk7mOMkyQPp39ykvTg7xKsOYKyyVjiR7cQXEGyyBlSSPI+pJzHTB+K5Ea8SCp/Z5Mkfk8hmeQMfx/Hi6RAKR+dfeifBBC7JJY/umAyZpGuSZSPfliEzqPoj7QhPYgfWcL/jIoklWQqJjEuPEMKlWFGM53ElXgSb3I8ibqQEmK/kLqTELonkfXEh79zMJ/EL2T8WG4MdVtIHTEN+2MOhindSSY5S64S+7HMO+JDAoiRLCFp5Dg5z3D5WECqjmP8pAfxIUaynuSQEvrLw3xyldQcz/hJVxJAEkkGySHOi5hmvEi68rsPKRpP+ROYt4sok7jyexb6YiJJJukkh+TTPQ+vkKq+9Ev6kzCynpQsYljMJQWkiNhPpD7EezHzFiPQB5MxEdMxj6ROZFhSRK4uNp38O02insR1CfXBCDKY35MwjWSRk0r3JdQJS/owGL/f5PdMPKuUMZlljJ7Yn4wldktZR0jIZOqCyZhJjpMzxEi3S5iKN7GuH8OTbP7ujwEkkaSRHJK3lOBZ9gHFxImHlV4khKwgGeQsKSJO/fgfCSCJJIOcJUXEiYea/UkESSEnSTFx4iFnDxJG1pNccpXUHUh3EkJSSBY5S4qJyyDKIhEklZwkV0jdwQxDokkaySc3iecQyiHrSR65SpyGUlcSTTJIAbEbRr8khKwgOaSA1PSmXBJCUkg2OU9uEmcevg4mRpJCsshZUkjsR3BcI4NJBFlBsshZcoVUHcn/iTeJIMkkg+SSQmLHzZU2ZDCJJutJHrlCqo5iWOJD4kkGySNXSc3RTAfxJfEkneSRQuI0hukmYSSN5JECUm4s00J6kACSRDJJPikmTuP4HwkhySSTnCVXiT0nzV2JH0kimSSfFJG6ExiOBJAlJJOcIVdIOV+mj3iTMLKEpJEckk+ukqoTmRbiR5JIBsklV4ndJNYF4kUCyBKSSfLIFVJ1MuUTPxJP0sl5Ukzs/agX8SNJJINcIjeJ2xSOd8RI0kguuUTsplIe8SXxJI3kkQKiPCR3JYNJCEkiaSSPFBC7AOYv8STeJIysJ7mkiNQMZLzEiwSQJJJGTpKL5CZxCaJ8Ek1SyXFynhSRmsEMT3xJPEkjeeQKqRpCvYkviSdp5CQpIOUM1Jv0JwEkiaSR46SA1OQDHDyIH1lCMsh5Ukxcp1EfEkFSSBY5T0qIcxhlEiNJIydJAbELZzpIVxJAkkg6ySWXSLnp1JWMJUkkneSS86SQ3P+5/3P/5/7P/Z/7P/d/7v/c/7n/c//n3/2xI0HlyjtAuf7d/aKiDZGxUXExwQbTr7ERbYPiwiNC2rZv176dR2jb2bEdPNp30f4X39mzbWxYYIwhpG2IIShumvn//E+Jf3hkuLFdVNB0niOU6+HAQ0bayzxI+4XnA8tpDg8PjomKjQo1uriNbuUyMtoYPjN8bnjkNJd+UTOjwyMMMbw/WtPBSP3WT1Lupccao6KjDTyvVrvXQaOpO+MLCow18AxU+o+36q5WRh2utfw/Uf1/lLmi/lqfaqcYg9Gf57wyjiStrFhjDLWLpVtTKWfJ7f/TRsVzEOlnxW3jiogKDPG3GMRynJ1lmOTbhomMuuNgvN/l7eBfRxneXl2eRmmDr3zeiyMOxylOpgc2/DrSZ8CIMWO8tWlnvtWxH6y/mvR1UD9Xz8HBR95PHlk+KtoYyzKgmy8=
*/