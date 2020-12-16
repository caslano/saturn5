// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_ALGORITHMS_NOT_IMPLEMENTED_HPP
#define BOOST_GEOMETRY_ALGORITHMS_NOT_IMPLEMENTED_HPP


#include <boost/mpl/assert.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


namespace info
{
    struct UNRECOGNIZED_GEOMETRY_TYPE {};
    struct POINT {};
    struct LINESTRING {};
    struct POLYGON {};
    struct RING {};
    struct BOX {};
    struct SEGMENT {};
    struct MULTI_POINT {};
    struct MULTI_LINESTRING {};
    struct MULTI_POLYGON {};
    struct GEOMETRY_COLLECTION {};
    template <size_t D> struct DIMENSION {};
}


namespace nyi
{


struct not_implemented_tag {};

template
<
    typename Term1,
    typename Term2,
    typename Term3
>
struct not_implemented_error
{

#ifndef BOOST_GEOMETRY_IMPLEMENTATION_STATUS_BUILD
# define BOOST_GEOMETRY_IMPLEMENTATION_STATUS_BUILD false
#endif

    BOOST_MPL_ASSERT_MSG
        (
            BOOST_GEOMETRY_IMPLEMENTATION_STATUS_BUILD,
            THIS_OPERATION_IS_NOT_OR_NOT_YET_IMPLEMENTED,
            (
                types<Term1, Term2, Term3>
            )
        );
};

template <typename Tag>
struct tag_to_term
{
    typedef Tag type;
};

template <> struct tag_to_term<geometry_not_recognized_tag> { typedef info::UNRECOGNIZED_GEOMETRY_TYPE type; };
template <> struct tag_to_term<point_tag>                   { typedef info::POINT type; };
template <> struct tag_to_term<linestring_tag>              { typedef info::LINESTRING type; };
template <> struct tag_to_term<polygon_tag>                 { typedef info::POLYGON type; };
template <> struct tag_to_term<ring_tag>                    { typedef info::RING type; };
template <> struct tag_to_term<box_tag>                     { typedef info::BOX type; };
template <> struct tag_to_term<segment_tag>                 { typedef info::SEGMENT type; };
template <> struct tag_to_term<multi_point_tag>             { typedef info::MULTI_POINT type; };
template <> struct tag_to_term<multi_linestring_tag>        { typedef info::MULTI_LINESTRING type; };
template <> struct tag_to_term<multi_polygon_tag>           { typedef info::MULTI_POLYGON type; };
template <> struct tag_to_term<geometry_collection_tag>     { typedef info::GEOMETRY_COLLECTION type; };
template <int D> struct tag_to_term<boost::mpl::int_<D> >   { typedef info::DIMENSION<D> type; };


}


template
<
    typename Term1 = void,
    typename Term2 = void,
    typename Term3 = void
>
struct not_implemented
    : nyi::not_implemented_tag,
      nyi::not_implemented_error
      <
          typename boost::mpl::identity
              <
                  typename nyi::tag_to_term<Term1>::type
              >::type,
          typename boost::mpl::identity
              <
                  typename nyi::tag_to_term<Term2>::type
              >::type,
          typename boost::mpl::identity
              <
                  typename nyi::tag_to_term<Term3>::type
              >::type
      >
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_NOT_IMPLEMENTED_HPP

/* not_implemented.hpp
d4f/8ZRg7WAiz7aD+Xzit6DARHu4w/JU6JiOo18TrIOwO8FaP3+/TjCtEmOgEcsusC+zN1QJ1u5hRlu5F2yb5fqNOsP9rSvRVsJ09rAF75PuvEBnmDNc433hZS9YQrRHVrZVCqZt8JXfKxZ8Teu1u18QrG6zr896FYy2lVYwkfbXLBphGLfA3Ab7DfRWpv47XPgsuM6X9jcsFtK/QAusLlKP5V34/Her61mdrdlQdqOvjI5brpJjAFhVO2EfWJYtfT9v3jGdbVxW9W1NazDYPy20312y1o0RdJLB/mUZuWb6DfZRYqyqA2s36qclZO2yB0oWniv7l5t9+RIeQtN+xdJ2MFF+1pB1az64augR0f6ab0H/YtFZTMie0NL7U+aK+um4Fefihs/YkK7trwKsyWB2hblv89XrJIXVE5YMRuu8thN5ZqQvI+Tx0FeXjX5BsNof+fqlbLDHc9IvEHW+EazMSMNg/L3dazIXL9MZfr//bl++4G8qdWkPdWCtht1kz28bjDjVIVjzvb76MgVM2qFe23+MembYTfPcw1rx8G8FK7sPaTDYTLBXp4/fqTPcF3Q/ysFgnvsnWlZNmCKY4ye+Nn0J2A8aB7Xo7P1QN1iHUQc969ev1fx6imCtezAHM9rRZWCThnU2i3ldR6Ovr1uG+WDRhYeOCxa2z1fnr0R9+eCZY3tFW7ESVgkm+1ZsdjDhcwVY5bSmx4RPF7G7LiSEtCO0vyf0tlkDuxS8p22zgzDMIwlDwn7mY5maRtgKzSYY9GZQhvmZA8ymM2V+VrjRBdZgAUOezRPzQcF+jvQZegspw14KlmewLco4XQ3mMNh2he0iPnd0YVXLGsFE+p7QlhaSvmBZM7F7UiscTeetb4KF6enDYXTeOlJrA7MZdk9rYzTiUzsB5jQY5lKEXavZn9K0OIP9RhtN2EbNCSb03sS4Jhle54GJNLxLfaIHLCHsQ3TsNK9LCfsMc0zaT5QTlqaM/ZVgyQbLVlgNmMizHIXtAnMbbLDCjpP0DVXYCRLLMIV1EpanjOHWp31sOMZwyhyE5Sssj7ARCishrEBhpYQVKqycsJEKqyRslMJqwOwD9bbiogz1qv4tb1/uZRdbqrrUCe33Pp9zLIs0mmd2wq5W8tMJVmP4XKWwZjC3warUudsf0KYNnxuVNLSDiTpxPWUYOzoJuwHzJcrsbT5Wo7BcMFFftlGGMScPTKTvFkvXMWccsduJ+RJlJWCiXt+hsDLi806FVZA476IMWw3YujBvninzpRCt7R1ff3aAMmzWo75YDlsshC0tdIKJWI5Z1l5L+zoXsfs7zGifVQom2t/nlrXLJMO5Uj1YlVG2nZblhV3OEd716dlC9nSda4DlGn15rDrXaPfVl0QwWn4dYMIn5gyE4fUx0t4FE2M/YRjfCcP9u4RhfCcM1zvAxPiAcZowtCEwu5EGz3ULyur/5J0TednyLgzryScxVzR8VlKGrRpM1LOrFLaFsBUKqyFslRJLHZhdtD/MJyhrAPOm3e5uvkaxa6JM0WsRDGn4NnxS1s6wTobZP/TFqTInWIjVwyokk7F8au6z1YSF63MZY00OfQjmPZRZGWZnmINhToblMczFsBKGuRlWyrAyhpUzrIJhlQyrYli1KQvRagRD2V6BtVHKOohdjcI6GQZJU2ZlmJ1hDoY5GZYHJtJXgdAkQ72uJXbbFFbHsF0Mq2dYA8MaGdbEsGaGtTCslWFtDGtn2AmGdTCsk2EoQlNmZZidYQ6GORmWxzAXw0oY5mZYKcPKGFbOsAqGVTKsimHVDKthWC3D6hi2i2H1DGtgWCPDmhjWzLAWhrUyrI1h7Qw7wbAOhnUyDP/N2x/D7Aw=
*/