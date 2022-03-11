// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2009-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2016.
// Modifications copyright (c) 2016, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_IO_SVG_WRITE_HPP
#define BOOST_GEOMETRY_IO_SVG_WRITE_HPP

#include <ostream>
#include <string>

#include <boost/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/range.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>

#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace svg
{


template <typename Point>
struct svg_point
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Point const& p, std::string const& style, double size)
    {
        os << "<circle cx=\"" << geometry::get<0>(p)
            << "\" cy=\"" << geometry::get<1>(p)
            << "\" r=\"" << (size < 0 ? 5 : size)
            << "\" style=\"" << style << "\"/>";
    }
};


template <typename Box>
struct svg_box
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
                Box const& box, std::string const& style, double)
    {
        // Prevent invisible boxes, making them >=1, using "max"
        BOOST_USING_STD_MAX();

        typedef typename coordinate_type<Box>::type ct;
        ct x = geometry::get<geometry::min_corner, 0>(box);
        ct y = geometry::get<geometry::min_corner, 1>(box);
        ct width = max BOOST_PREVENT_MACRO_SUBSTITUTION (ct(1),
                    geometry::get<geometry::max_corner, 0>(box) - x);
        ct height = max BOOST_PREVENT_MACRO_SUBSTITUTION (ct(1),
                    geometry::get<geometry::max_corner, 1>(box) - y);

        os << "<rect x=\"" << x << "\" y=\"" << y
           << "\" width=\"" << width << "\" height=\"" << height
           << "\" style=\"" << style << "\"/>";
    }
};

template <typename Segment>
struct svg_segment
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
        Segment const& segment, std::string const& style, double)
    {
        typedef typename coordinate_type<Segment>::type ct;
        ct x1 = geometry::get<0, 0>(segment);
        ct y1 = geometry::get<0, 1>(segment);
        ct x2 = geometry::get<1, 0>(segment);
        ct y2 = geometry::get<1, 1>(segment);
        
        os << "<line x1=\"" << x1 << "\" y1=\"" << y1
            << "\" x2=\"" << x2 << "\" y2=\"" << y2
            << "\" style=\"" << style << "\"/>";
    }
};

/*!
\brief Stream ranges as SVG
\note policy is used to select type (polyline/polygon)
*/
template <typename Range, typename Policy>
struct svg_range
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
        Range const& range, std::string const& style, double)
    {
        typedef typename boost::range_iterator<Range const>::type iterator;

        bool first = true;

        os << "<" << Policy::prefix() << " points=\"";

        for (iterator it = boost::begin(range);
            it != boost::end(range);
            ++it, first = false)
        {
            os << (first ? "" : " " )
                << geometry::get<0>(*it)
                << ","
                << geometry::get<1>(*it);
        }
        os << "\" style=\"" << style << Policy::style() << "\"/>";
    }
};



template <typename Polygon>
struct svg_poly
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
        Polygon const& polygon, std::string const& style, double)
    {
        typedef typename geometry::ring_type<Polygon>::type ring_type;
        typedef typename boost::range_iterator<ring_type const>::type iterator_type;

        bool first = true;
        os << "<g fill-rule=\"evenodd\"><path d=\"";

        ring_type const& ring = geometry::exterior_ring(polygon);
        for (iterator_type it = boost::begin(ring);
            it != boost::end(ring);
            ++it, first = false)
        {
            os << (first ? "M" : " L") << " "
                << geometry::get<0>(*it)
                << ","
                << geometry::get<1>(*it);
        }

        // Inner rings:
        {
            typename interior_return_type<Polygon const>::type
                rings = interior_rings(polygon);
            for (typename detail::interior_iterator<Polygon const>::type
                    rit = boost::begin(rings); rit != boost::end(rings); ++rit)
            {
                first = true;
                for (typename detail::interior_ring_iterator<Polygon const>::type
                        it = boost::begin(*rit); it != boost::end(*rit);
                    ++it, first = false)
                {
                    os << (first ? "M" : " L") << " "
                        << geometry::get<0>(*it)
                        << ","
                        << geometry::get<1>(*it);
                }
            }
        }
        os << " z \" style=\"" << style << "\"/></g>";

    }
};



struct prefix_linestring
{
    static inline const char* prefix() { return "polyline"; }
    static inline const char* style() { return ";fill:none"; }
};


struct prefix_ring
{
    static inline const char* prefix() { return "polygon"; }
    static inline const char* style() { return ""; }
};


template <typename MultiGeometry, typename Policy>
struct svg_multi
{
    template <typename Char, typename Traits>
    static inline void apply(std::basic_ostream<Char, Traits>& os,
        MultiGeometry const& multi, std::string const& style, double size)
    {
        for (typename boost::range_iterator<MultiGeometry const>::type
                    it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(os, *it, style, size);
        }

    }

};


}} // namespace detail::svg
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

/*!
\brief Dispatching base struct for SVG streaming, specialized below per geometry type
\details Specializations should implement a static method "stream" to stream a geometry
The static method should have the signature:

template <typename Char, typename Traits>
static inline void apply(std::basic_ostream<Char, Traits>& os, G const& geometry)
*/
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct svg
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_OR_NOT_YET_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (Geometry)
        );
};

template <typename Point>
struct svg<Point, point_tag> : detail::svg::svg_point<Point> {};

template <typename Segment>
struct svg<Segment, segment_tag> : detail::svg::svg_segment<Segment> {};

template <typename Box>
struct svg<Box, box_tag> : detail::svg::svg_box<Box> {};

template <typename Linestring>
struct svg<Linestring, linestring_tag>
    : detail::svg::svg_range<Linestring, detail::svg::prefix_linestring> {};

template <typename Ring>
struct svg<Ring, ring_tag>
    : detail::svg::svg_range<Ring, detail::svg::prefix_ring> {};

template <typename Polygon>
struct svg<Polygon, polygon_tag>
    : detail::svg::svg_poly<Polygon> {};

template <typename MultiPoint>
struct svg<MultiPoint, multi_point_tag>
    : detail::svg::svg_multi
        <
            MultiPoint,
            detail::svg::svg_point
                <
                    typename boost::range_value<MultiPoint>::type
                >

        >
{};

template <typename MultiLinestring>
struct svg<MultiLinestring, multi_linestring_tag>
    : detail::svg::svg_multi
        <
            MultiLinestring,
            detail::svg::svg_range
                <
                    typename boost::range_value<MultiLinestring>::type,
                    detail::svg::prefix_linestring
                >

        >
{};

template <typename MultiPolygon>
struct svg<MultiPolygon, multi_polygon_tag>
    : detail::svg::svg_multi
        <
            MultiPolygon,
            detail::svg::svg_poly
                <
                    typename boost::range_value<MultiPolygon>::type
                >

        >
{};


template <typename Geometry>
struct devarianted_svg
{
    template <typename OutputStream>
    static inline void apply(OutputStream& os,
                             Geometry const& geometry,
                             std::string const& style,
                             double size)
    {
        svg<Geometry>::apply(os, geometry, style, size);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct devarianted_svg<variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename OutputStream>
    struct visitor: static_visitor<void>
    {
        OutputStream& m_os;
        std::string const& m_style;
        double m_size;

        visitor(OutputStream& os, std::string const& style, double size)
            : m_os(os)
            , m_style(style)
            , m_size(size)
        {}

        template <typename Geometry>
        inline void operator()(Geometry const& geometry) const
        {
            devarianted_svg<Geometry>::apply(m_os, geometry, m_style, m_size);
        }
    };

    template <typename OutputStream>
    static inline void apply(
        OutputStream& os,
        variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
        std::string const& style,
        double size
    )
    {
        boost::apply_visitor(visitor<OutputStream>(os, style, size), geometry);
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief Generic geometry template manipulator class, takes corresponding output class from traits class
\ingroup svg
\details Stream manipulator, streams geometry classes as SVG (Scalable Vector Graphics)
*/
template <typename Geometry>
class svg_manipulator
{
public:

    inline svg_manipulator(Geometry const& g, std::string const& style, double size)
        : m_geometry(g)
        , m_style(style)
        , m_size(size)
    {}

    template <typename Char, typename Traits>
    inline friend std::basic_ostream<Char, Traits>& operator<<(
                    std::basic_ostream<Char, Traits>& os, svg_manipulator const& m)
    {
        dispatch::devarianted_svg<Geometry>::apply(os,
                                                   m.m_geometry,
                                                   m.m_style,
                                                   m.m_size);
        os.flush();
        return os;
    }

private:
    Geometry const& m_geometry;
    std::string const& m_style;
    double m_size;
};

/*!
\brief Manipulator to stream geometries as SVG
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\param style String containing verbatim SVG style information
\param size Optional size (used for SVG points) in SVG pixels. For linestrings,
    specify linewidth in the SVG style information
\ingroup svg
*/
template <typename Geometry>
inline svg_manipulator<Geometry> svg(Geometry const& geometry,
            std::string const& style, double size = -1.0)
{
    concepts::check<Geometry const>();

    return svg_manipulator<Geometry>(geometry, style, size);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_IO_SVG_WRITE_HPP

/* write.hpp
FaiM1FPVQB2To6JHjFkrhLoUaM6ivUsW2ko/s1hYx01PrLWm0uudMbyR67VUPPKtEbaGxyvs6Y+vky9MdpcpVi7R7NoTsLUFivbu0Akqt8xyzblomprtmpCr9EI+V2dqRxFtzkfskaxIFyT00x88IDyfTa/mU2Il0jZ0BsqbUByoOiwVLGq2EJfjvr6lSUY4WczdpIVxh5DY7Bzam1cV0Z6qQCDPeBrH3UkyZTbJUgiVkb0NFV5asFPIUm5tI7rxo4y0fEzJTKgcA5RriQ2nfberPNdmscTexIFe/yYOdOStoyd1NvKwf13NQ9htrm3AH2o/bSVwh1hPPeJxOs5Ve2VBoIBY+Z9MKeOL2+/hRNmC+oitxceR8pp+Yn3s2RCNdpw0/Zsz6PwjYV+0Cvd8oZvLy/WBzvLKQQOd0SoMUF4+CH69n5bCrzc/XnCOHj7u8Q73yNXewT0wfUHxlz7dyA3OlpuJ1x/XDQD5bLGXW+zOXZpcp0yZOSCW0IXlTWB6JmLLPwMRK7A0ZOVaiIATGYvdSAxpWt053BdR6mYmZtn4wzNULUCjvvzjH3S9a1UHwvpC4LNoTt55Q5lqcAmXo0vh/7Q52xIaLq76oRGe1Anj/CnCOZniJ7DD3PoGTS22it65K7YJfw0SZCLeBLHIyRIWAfHHj2mPGaJo5lckv3zgflfJmUT/AZd/eQvyyE9rrzl8MpmrR8ybdCpV/+GOtPoPtlgnNod4PdssMmPLzEUuOb3f8k6UcTulFmorhve3oN6RUxvgo+8MVKKv5poHK0bIluyQRQy5Cylo77Ny9lKLyKRXGvD/+ESmRZQREJDLdmCQ3jfPfJ9Y2SvLUqTL54grl+8XQ+48pTdU414TwYNIaqR6TH9OJ8t/R/HfCfz3NvzdMZz/juC/V/PfEv57Y3+U3RljNQIN94gPX89Oo4zI0GvC5c+3n6VNM9IXnc7GHF07RuKU2LUXkYEqnqW9iEIKWjVe6m5QFrn4xepl2lJnNs53ufUfdF7WejOId048RYsKLWJTWjW6aSvw133AUYn6I9GxnMc6XJfpWiKgRF4Y4X9j+dm0+pNWJTPW+CXqBfGjA4I+fVKucUFMCqz08TslCIkDvNU1H1XutwJg4vRfaBckaAiaN4ON5s1ANAJkahkVhRvuDupbF1g543Gz4S1kO1coNTKeR1/Em0i4+lRW8HP9qsBR2QbwZhBZt8KHHkaI++CCJ6zIxA4f2zN4YJTqkBkDSEb1tIK59RyWtf8W8FZI5lCVvO1BVo/dUE7YcgUCjEJ3GwXajPjmjx4mTJYR5Ntw7jwcJNmN1WVaNQckeZsjS7FaraJZKzsc9EdXYOeImtGcJHx45EW5kbCpUMItDd8mUWuSJ56zRJa3PIfu0M9JAwPBMzI8aEdk7lVOCDt30X9NCCspnuG3dn1WliX53hOLjdLPBmL5waZsS/mdWMb+cWfjlpUkWIvPNwG37M4ysUppaUBu6h92ZXIkcHbfuvY8mFMyceCDAXHXEfBH2gEWM+wNtuFsS1+5gKWTPjBF1bA7IXGt/vIs2qai/hcwF48YRHu8egGy92OX87HYpVwQLsa4VkfVz6StqlF8fYfF0j7dalabDU2SWdzLLTTWZcW3EmWT1VXw2aI7GDEQaNmJsiBDilYzWGNGN/3+kNXvLy+5lcNRV4002kuYmS7w8xmkpVRvBmEr23sS1nGJS8Tf3zupo0pCplaC+hUlo/zlN98qe+OAiGuM3p5TYtuZXendEgvJaaFsKbY+zcTGLxTfNPLD4ob7TulyihbZcMRoGEYNupqQWPxmoet+vx95Aoa7T+uuC2fTXXWM68LlzZDdtOpEDlCdvR928yn+ncO/ESMaqXbybxv/zu3HwXe3cP5qe7kV32fYz/F9GjX6Pp8/KnHQ8J5fRz0PNjE/o3ZQMMB5KrjAvWk2JCfkASZIW4gdoJe0njRqK8WGEp7aRaLDTUDuL7wK5A5r7z0EdQ4KJO5xviehB8Q3HyK4mU4I8cDWKdSmJUTXXew00CFmjSY6zg9pJUNZjOsTZDFVdE9MsOSN+tBij+zfKa6j/uxswmKKPeoBKvCJlbeDW8iJXyBV+dE77XopB2F4On1iDjc6w0wxLMpQjUGRLE+RRtzig3DHI0IGp5UKLkNZMnHk+3B26cDP/fRTVLzKvqWxGoAidjCbDxxozPxs5MKGUoAYjtZsyXA0WPGr/QCIqCyfl2UE1zXrebsRWcJEi07comAoP7rjRub7guLhRdkgOehoR8UiQvNQzuilw6G6kVd6XgKZY18ZIy0d8RsREQiUUoQ9GvTLXuLE+IRuPB+pZitpXu2R84iPJkA/XR+pvhsvqZ/ORSqQVH8Hj6c8aM6UXngPPb+Y3y+H3HQb1POYnbyh2WlmV6fPSuNhjblBiPDpebEjmO3d7N4g4TR92i4TxU38HaE4SNIifsvZKO55VFjJ2JhG0iWIxSO9UjWDO245K6nenWcU0M4ISktnURcSQ0bUmGsz8I6abSTOSvONueN5YL+akDVGrNvNHPgrZEaOJh8RfQtRxHLIFfCfNpK6pNK2iHEvs5dZdAt2ueH2fyUnb7nS08kjQsV7uNDTbPUes3oSPB6RgWmhhM6T8yJ9qPE0QiGItG6QbOekciSHC6OJ08G0FYbv49+dILHhGfwbKufC8IP8O1HUBdeWDJgSIGSUR8OAgc/MPtQzu899nJCmFmQsIN6ZC/+iGj6bX8ww0tfuEy/QTyQp6PAFAj0gISauS0sWUvRokozdD4QR2mByg/dPgIRtZye0/Q1ZR3vn0kFAIiFxrYda9ojBrxiaVN6R4JEsRiHYFU7eWDn0998N1Whhjs9qfFnCM7NEQtYq+6qEfujK7fIZ14Th6k3uN5i5y0WWAv0NPl8HQhZDBOMZuDePkj0G0/3NV5s9Vi/n1/JMpk9LW9TT65Ms9fq+dOhX4AUc7pTm9bMCY6bfME99tk+elyifJp/YjRxA1Vfz7xj9Njjr/Nu7af9vMPd/uGOoQd2fHgtyPT+TWOf4CEhM0ht/v7icJL5QRgwYzQdDFCKp9LxKmW9sb7KqR1YSbMhtTvSq7otMg9hVMrRHyolnCuU2sGSjzMuZdMm1s38/vtuokmIt09fVmrowzRoIRp/A0NE3sFUnBYwCQUi7rthwHojulKSn8sn1Q8mC9P8nLk45G5Rr422BYnzkOfcWI1P6XL90foGiARkKSJYe7Av6fAE97zYUvKV/Nx9hXctlocwpTC+I29wC+Ea35Mrj+O8Nel6N7GSqHaZNn5oignIiX4vwdQY3tD8orNd36/EbkhA5Lyhmyla7vBdvTYKH2m5PtuFevK6HqqU0jRAQaupJCRyVy9numUYNZs7/v6cGt8PH8ZSaURK/2VXto5sKMtAQ6iJh55SBxz+95f+MNOwlzrI3CJ1VX8dJA2TBd5zBjXYlRxsUbrP5jGCyrSg/Fb+Q0wRfqJXYtetCEJIekKTVJ3J/l0DAx6fTdomJxQm9ibiJcRmof/qyod8VYsPwblY08rH9Ll3jn4YzovjqZdYzgrjig9lvQ/UGeRSjL2LjhXLT6sBKd4OgL7IDOzOy46f8dzb/xezFybnZiFP2axfC5NLA3XNh4d3h5E5c2mnH1fwX0NEPRasZmeqHIjvm8W2GJsuQkR2j+C8LOjsA3+lGMShDLI2llWv8vvvMijups7cc+jPeSNNw3b6ArpOYwB8IWXaECLwB+oFjjgyalYaCk4/FgkPsNtP6Ecet7Vud0KdNTU+wlCbYTM7lvT8JtXmcwdKiOk7rquZo+30EtN1s604JPGJslSwS6djWAH/Gxy5FapwS0yRfpKTVZg53DE9P1XUEXpLEZRqOR9L3oqiuhzwVSDn3pBHmNxCp0mlQokn3JnOqZ9FPk4wOfiChp1NPSKtp9JOJJ0mjtDiQUKafhZ62UtBQJqCFnqPaPlBRJqEyu5qWISNgp9PyjAC4SQ+nue1AROdMHDEMBwVCY1n7/NOZlu/iR5DqNLWsvz3B/IaWUdQFjiImByNOwCF5FMXkUf4fORIOz/p/4Eia7jc4kjv/C0D/vzEkV/8ixZAE7kkyJH3u+S6G5J1n0xiS3/yyRzUQ4izm8acqZgVQMSdzZ7nE11CNFmYJP0K4nXHIP0rXF4RfmSeZ2LK0hHgVdn2ujY727SMZ/9u0/Wk0I5faxDUje1CNoUmqMQStA0Yaher5blBMoOt4dsP4oearbBZzo2klI7SSO5McdM5ak4N+9bqzOeiWE8RB16+FkmBBv1xTY7waHMyctSmNseTFknrjx93wcBJ7VyZkGKC49taUWvilK1Jq4SI9+L/VCw8rr+ufew69cIPb1Auf3UPqhTdwj9xgUGqGg2LbsURSKzxmWLpWeNvXZ2qFW28m3unLF9LVgXqaOnDr6B5lct8DROqfB0TCjO0RS6E8JFy3GFkrXr0cWTKYHBGCvZiYGQ4dt5cGzSB8dt9VM2OoeE2P5IhBJItqK1hcGqkNKOVItUkj4WRKQuX8AsiXnGbi5/hZ3cTkRv5F1iTR9wWZtUKWYbsaPhTTdvm1acOD2sIRWkPhrhLXOGfFte5P535fm2jX6uN9NJ9ds7judXKd+m/imWPdnz7yBbX31yZeLcaEuqXlCfak/sHoRFtkulMEbzypaw3Tp6aZeoPR+bYQ1wLZWcObcqYfGo2f1cD6qk1zGiDXRnc2D3bGS5jiT+BKrASUm0Ps3f3BNiQQmHepoYZkBQo3vM0N879IZeskpqCWiMdUucnFD0Ynqz6zmTD6S+SOHi1ncinc9owlwFwkmrd0y8yCQfG1mzNFplu20gY4toUHuCTIdfWSz6/5b89rk+3u0uFzLnKXjph7vna7Pe7U6nGawd30dvkA5r1qR1Edz3v+KHPe0KDUShtatswFmNPD2BZEXZCAzE/s2Oah/7059W3OvnAOLZ+VwbmpWRGRMDoipj3UGUhlWS1Rzg9I+sFmdXDWr9FHZF0Nre4YpIKvTTNGOJE3F0H5Nks8gxpSzGhpuPjGDwY7LZCQ1R9oozkftbYIX0r/8Ldool10vvBPlvmorfOBCc0GggLh8UQpyx6ez0Ay6NgTf5EsExIs0iPeU663EcTOfj3dFl7a3ZyWOYfoPNi6vHvAu4vDyxI6F+Hrimdoswv8WqN4m029HbR8ppNvLuPYqt+y1TVS0SnZG2IY3MeVPkEadx2DrKpF+bEsB0LyQRkB52ZXxTH1Zs1zKkBsqLgxj7fBVQ2eTpxxd1mHgneWUrtWUuDyJFgyywHnMRoLjf+AHleQW44YAe8p9y0F6mV63ikanljd5K0seUsfPeYDM/O25nFOhSgD/287oZnpaT6KI/xGpv8gAaj4xxmIBthH03kbhMddr/YJL7Rf4KgE1Ye3ItTkxUCyc7KLkfD/kUHF6yAXPwbPzmLsB8fjnGbNewrBBPoj+fojuUIF79js/lS1w6kPLoiuCrsst7pkoc2KgosDaAohK/xGJOMY/6tj27h8x7aJuXI7BsvR228UhElkKiNhdy+E59RF8i1+cTmiqL05ISvXpaSx2rNZiF2IssifS7jEXobjFr8mn17TjoDJM15N/8xGEwpeFCPMWBnmrsd6rVhvek/wjEhmE2+SW0m7UN5VLpQvC2WUA0gyDhue4voh2sbtgDYPQlfKWDlVYz4ENw7lyWGOVL2cbg/F7XE2OZP+xXAamtO/GCubm21MNeo5Zviy0/NBJKZUjwkLrbodXDtmDFdvQ/JOTzAZ7hgls9WOd+3A2XBUvgbiXX5KOh+9CNklI/bjlADf5EuuvGox6yvwmB+1nY5FeIhwopdSqK3ArnDvU4ZBKeKbQUsZLO/Ba8k3I/IiurYjEYbfVXZMvYSPbfkAa1qoRQMPjTiN9jy6X97rLDs0Dtwu6M2OwUaN9Dfs4ww4+GUqPVWI7pNcOFvkl9JhnWej0xq/xU//pa9FyUPiS47s2i/+wYtXhseHsNYfmZlm6J5TcEemcfS8ZkTM8/zVbVoxPrNcDTFpmBjOq0+sgiv2R9JzkOZyLDnxj5KgyZKgcJUllBHhCvpk5/nLx6dD4aM49L+sraEvugrHyu8vD2WkwWgqy8XwZwcL9k/wDZHVhi4IqD/rn9IAH10BIbIh6ynqKZ4oOw2pdcyTKUfBHhr31kIkBCHOJMd0JYBGRVZGMbiXgBxQ/OWS00Yy3ZoB3Xq6uwTIXc6S+lyWnu3ibeqYZFHl7bL2aZeaZWJ1NZ8dgOSwKWt0BD16TiL3jBmbj9jFa9ee1TknfTr55nRyIcwbr9B9zuSY1GJ2MSdQfTnm7UyfN3RMM240IQGuXU6BBvX5tET6DCQdTMrSTtnLjHMZYtxxJtWAjaaSb9ou0Uh4pUcCYu2IqIHPTTiXNTJRjWfqGwP48z3zzigSOcbQ5wD3fYp4hHHlMPcL1/1MbsaEt9/GwU/XBKNbcpIJYQhxbJCu22dWQwtZxOeBhD5de0GqQuxS9QXpo4cIP7xn0A1Kvol/PMZF2opazl2ULJByQycxTfPSW1u1yaLQ26GpicLJbYVqp7tRtbm/UfoadYcYqqYoFXwwWdUAepcv/ykdNnZCzxM0dmjX7bQpWLtk1IMexvogOLOF2DMMyigixm+tYZVQ63QC/Q2F0AmNiF1+D50n10qZUU40ZOD0aFuQBMnI+VqkoxYVEf07ZX4Q9mb91/RuWbrTYLhmuI+rf2vwNP0UxczhMd/KvpQHIxVm1heSKjklVJ4CWj5U/OkqVAkqQH6V+md0swyWkW3pusegekD+R009SK++UluIMljJVMQDg5Ibc48tUFHXd4KshnWkSBezthN/PduGEngjCUHwzFczOJKlhZXHAIxvl7D2ui+MUt4OoW/shu9xE00IcoOxFlFeretyz7ETxqCpp6W4s09c+g2JZs0r0sWdP6SJOw0jUuJO7J4BsGHBu3WX4bK1BJR+l6nBlY6Rsh4FfMDCxbYFxCg6qhAdY4YclU0z4tUcnCpSuJ88qbcvsxiBR+ImszlHNl+untTjP+fII3HJGW1PhahtEoceiawz2r6cQW3XyYDvL8t6tr0/itqGcGyR2F8mg+SMvJVCnNDTkOMZizqevqgv0xa11HzD+YS7enhHHlpNy9uZXN707+xYo1DHZyxGlJW4zuw46MyOf3mIZj9brtr5nb3Ox/rvMNZ/33f16ipCal8Jid33MSTQB+Q4rVeGhEnuOWEST4fJJ2kwUdLemjZYXwDk7SRAJp67lx3QeDIJjRFmr4E9x0oDRea5u9w7nbp4JRz+PvWcXV4GEK6SQNg5lYGQB8qzP9VlKYl78WwjLfu0JJU5AxTd6aDoSAPFQ1O/66t/uIrWuSsJjZLv7HhwDnV8PgmQwVO/65Me/DGtRpEw+fre7+o1dBr1mijBsu87e824lnqNkJDZcC9DJv/s7XEboUAjsjQ3yXaAtkpfdR/HhIrwvUaMaY7mnKY1lum/uTtZ+zUFwiPpIGxKA+Hl96a+nfniWSsJJr9PAi/jHF28v6QujyfB1jbF6OJMdfnpLFrkjyXA6s7RvuM+ah8vQbXuHO0vj6T2KySQFk9hIJ2XDJ3Bwe7quXdyzgGjKjP/P+eDa3/Lkg4ZAx5ap6MK2VPNaj8mZHLMOfXjfL0yqVFclTD51z1GzGGxBMCn5rVTLvjAPWc8jFQv8TFytW+e2QiLXPwCudSn7+Gl9ksmCTb4uJSXHAkrR5AAy65tQYrdeG+/6PMW4rs7EV8ImuDilTmqXkpbTnHypcGgX2yI0vdbnPzEBWZjHzSu/gVBfpZcWFaPlj89SC13yiV2BNNbzptKLdfK9X3Qo+Xk96klXy4uFpSGPLpPU7ruPygRLX3fltSwh4Ka+fLihwcbvhxadUy6LfTxiZVb2MTh4CiFK+Yk2IfpePO0pBhXvBxFT+DPfgFAerfx9dlowk404YR5muiRJfADvAxxUruSvsfE1QW4xECk4pSRL/Lx5RbDJ5j9jyPj58mLTXyxQF6s4Z74FEsasJGiW/CXMwyGAWIN3kuLkwPhe0aqVyWv8fGnR6qx9dKYSWOTP7cxoUu/Lfum7pT4oE3OD99gUbNjQUv24njuLJJVMtQsTiXUod0yItILWjADaQRDGffQqrzOWS6PXR1ctVcdiMJe+bMi9oYS+yBpphxL7Go+sYaj0Uk5jzoVzopkNYyzF8r2S6r2LvyK7hh58H1c2b4VytFx9vinPI1p01OkzOP0B1AN6+tZrjK7mkffdQC/MZ/eCK0KjfiDoFaRX6Url3KXC6vqFp6PuhyrMfSsyMVaNVwcI+Pt1DWTx+edkstO7UapXPpmTtTRazEBca1jm8cecGxTc+o/d/bt1LIDcqrhnYhZJTn+nlmRDCUz8rA9bgs/YLewubkspQm6r0cVapRqRzbvNpo6vWpoIOI5rHkKghHi0z0jtK9lkPW+iKdZtN1N8iLL/hb5qZWRO+FqBhXr+/UccHexXzyI/OXQ3e7gW7LSN2osE4s8XMtaMkuhJ51I/tlqsPkVuX0bSBRpBR4A0x3ewTEAmme43DCOygasa2TUsx4JZnffiyq8IuJp0jxtHF97dAniR0uQ87lid8SzSeTeAvWhHZW1N7o/VTMjFZuN1OWboT9fj7gd34NG6N8HrG/ainfi1F3PR/CLkEPPs0HED3WxFH73X6FBPEo99kxIJGOu06NijVBkSFSaN1Ho7YxUc1b9FXXw0vIICBLxS2SiVvWoH+6kutrGGZrs4oJyKB4F9EQ74fSPoJLZfhk91ycown7Qv7hDZG3u1n1B8TBd03LNj1ONcylK6KZxBtPqLg8JyvDTs0t/prBBUZc0j0FsSa+d5ZPZO1GU68xKZSJr8gk9wP6m7GyqOTdsMLxPm2V5Oj/cTyeNSk7kiYA0iHGIjhH/TO8ov3FiLpI+PDap27Azl0KTEQhSP62YA18+8okRqhHOda1/O6QvYFbfJA5/Gcg6FJ/INLqo/4jnBPzcyqV5pmqeU9Lp0Azv2rYkm+jimK9BF7/ePoH+VbL9el7HIUiq3rXiLzd3y5xV+0XcY0bi909FfM3AaZPP84PikFm7eq34H1iAjixJec/0cOV1shY2yMbUDpRKT5OX/xcAAAD//5R9DWCT1dVw0qRtgJQESKFqlaooaHEyC0oWcHWQUpVgSqCBQVu2MdfldQ4=
*/