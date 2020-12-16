// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_SEGMENT_CONCEPT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_SEGMENT_CONCEPT_HPP

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/point_type.hpp>


namespace boost { namespace geometry { namespace concepts
{


/*!
\brief Segment concept.
\ingroup concepts
\details Formal definition:
The segment concept is defined as following:
- there must be a specialization of traits::tag defining segment_tag as type
- there must be a specialization of traits::point_type to define the
  underlying point type (even if it does not consist of points, it should define
  this type, to indicate the points it can work with)
- there must be a specialization of traits::indexed_access, per index
  and per dimension, with two functions:
  - get to get a coordinate value
  - set to set a coordinate value (this one is not checked for ConstSegment)

\note The segment concept is similar to the box concept, defining another tag.
However, the box concept assumes the index as min_corner, max_corner, while
for the segment concept there is no assumption.
*/
template <typename Geometry>
class Segment
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename point_type<Geometry>::type point_type;

    BOOST_CONCEPT_ASSERT( (concepts::Point<point_type>) );


    template <size_t Index, size_t Dimension, size_t DimensionCount>
    struct dimension_checker
    {
        static void apply()
        {
            Geometry* s = 0;
            geometry::set<Index, Dimension>(*s, geometry::get<Index, Dimension>(*s));
            dimension_checker<Index, Dimension + 1, DimensionCount>::apply();
        }
    };

    template <size_t Index, size_t DimensionCount>
    struct dimension_checker<Index, DimensionCount, DimensionCount>
    {
        static void apply() {}
    };

public :

    BOOST_CONCEPT_USAGE(Segment)
    {
        static const size_t n = dimension<point_type>::type::value;
        dimension_checker<0, 0, n>::apply();
        dimension_checker<1, 0, n>::apply();
    }
#endif
};


/*!
\brief Segment concept (const version).
\ingroup const_concepts
\details The ConstSegment concept verifies the same as the Segment concept,
but does not verify write access.
*/
template <typename Geometry>
class ConstSegment
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS
    typedef typename point_type<Geometry>::type point_type;
    typedef typename coordinate_type<Geometry>::type coordinate_type;

    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<point_type>) );


    template <size_t Index, size_t Dimension, size_t DimensionCount>
    struct dimension_checker
    {
        static void apply()
        {
            const Geometry* s = 0;
            coordinate_type coord(geometry::get<Index, Dimension>(*s));
            boost::ignore_unused(coord);
            dimension_checker<Index, Dimension + 1, DimensionCount>::apply();
        }
    };

    template <size_t Index, size_t DimensionCount>
    struct dimension_checker<Index, DimensionCount, DimensionCount>
    {
        static void apply() {}
    };

public :

    BOOST_CONCEPT_USAGE(ConstSegment)
    {
        static const size_t n = dimension<point_type>::type::value;
        dimension_checker<0, 0, n>::apply();
        dimension_checker<1, 0, n>::apply();
    }
#endif
};


}}} // namespace boost::geometry::concepts


#endif // BOOST_GEOMETRY_GEOMETRIES_CONCEPTS_SEGMENT_CONCEPT_HPP

/* segment_concept.hpp
x1jY8gnTTV/V2QdL9Iig9bH1Eyeuj9/KddP96uOnYjbTMdC/PnK9hvVxbDPKMkrr43Cpj94+GrNdiNSvcT71S+0OItvUj1/90jAnUi73WvUr3lXlKgmPcIeFSv06hN8Ul12/QntQv0Kb6/p9tR+L/Xa7fkW7IsND8O4aBPh+4l9b1wZYdc3tDbm/XiFT75PlT9Sva4uQoPVL3fcPeq9UeymHHS76XLeWQ7pkgtUOxa4Iu+1yL3AtwDayhTu8+Y+9HwS7V+7VfffGakhjkGX43x0w/f2CpV/dR9r9/V7Rs8V9WsP8UPdjvfnh5v7XXPNjSF1+pKndCuwexs4d5nBFugpkw9yIWHeY2/HjxxBpQfLlixbeEM7SkGZrvqQ+GShfMoPli7p32fnSQ/ScwPliu4+0+6l00adLPu1rTl600HyaXJdPXdRuC3ZXJXjzyeXNJ2esmVfR/5y8svbZLNYQh3mBOe/h8L+xQV7RLvPK8wvP9VQFfJbSPvJ28TfEkcX/mo8alrOx/lrdDAs6HlN7yctj5NXelpqXp/iMx9QuFPMHEZeTvoqEJ5t5jHsHZltM82auU1yj+PCzWbj4+6F5K3uzBuq3Ao/Z7PrZUzfKtPrJVsgCwqj1y/Nyj+dcBmmOoM9T6j46cL9l2yf9oOetwH1P3fN3emzDfZUX8l/0Uw3SIAP1RtKhfhKCj9XVPnDdsO1/VDpPZsxttZmhum9fXx3j9EIWE2ZGw7TXTUAET7/66xh0riFb7JPoWcI0Tyw/0YHzxLZPlzxJP4n5Ac8PnB+w6kN8vJ5brqF31zpd3iBP9GYcPD/UT2rgem3bR9ppXebNvx9V/sHq+XFN11AvZN3VeZhtD5yufo2kS/247Hg/KnqfwPcT232k/R37TtEzf1Q604Kk87A25Cka0mRNp2NPwHRmNpJO9eOy4+0SfVTgdIp7//FHpOhj/qHptNputO4xabWJrsgSs542TGfdDS94WtVfeqP3NnUTtK2qvXxPe4Ry2Jqo96lwc3Td0jVSblXfbwzg+QfcpzZqXoX5zJVfa9Z9v7yq8Czks3UmqYPlkboP+0Hl6RufdXrDzEPidLw7OYXxqF982EpiUVF1eaAy0/neN8R9P42f+td526WJDeqn2ifaexK8JvpYh37rL/v/zOF+eLJzsYH6Wq6r9dV/LjC7dcP5sJ7xmD8taTZTS8H1s8cJYXL/xLQu/9VtSv1zNOx5mRFi3/qky4drEFe5hl9cj/vEtbmW0SFsyr1xLczPK1qUV8hjnO7p8TZ2hiNf42m5i/OxK9AyUDvud1HkOarjNc3v9Mb23dD8Jizimy96lq0X+NetZK/HQRpAlu5TslHj7qlgzwN2BckvLS1b6ikKtCeJuu2uOvtTie5sLF8D7jsk8ym6P8hE3QcvzkBgOBxKBtcStu7HYG+JXewhcnlLPBUl85cH3jfF8tfWfifR/BlT/5J9BYyAz0ETbD/JjkTtr6LEz2OOFcT0Mkfn+vsW2HvbLhN3F1FqmTIGX08ej2rLfYw4OfuxA1yUu9lA3DU2ZzhawohWnV3aRO8adI5mhtiPVp09G0RPDDRnQ37os4+46ShmE3TOpr+Ypas7cajXTlN33LFss7bWPkaSzmIa6VspOocz2+WR2bzmzobvhbQ/Gi9hLHD09qYTMyudYRJeDmHtQqz5vzzXABDllGcetT+IbJPn7NlczBlpP9dofLLb6vziEJn/kflFp8b3EH5T2taFP8WcX9T7jWU/FPu71b87rCVX8NpbYpVvDe4eMOMRGueKwqk7Sue1MF+h13B25SqRobb/RPX7Fvb3Yc9ugevdkVFB75drJW8iJe6r8HMQuR9/XE59atw=
*/