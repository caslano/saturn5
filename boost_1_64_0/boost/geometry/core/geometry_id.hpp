// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_GEOMETRY_ID_HPP
#define BOOST_GEOMETRY_CORE_GEOMETRY_ID_HPP


#include <boost/mpl/assert.hpp>
#include <boost/mpl/int.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename GeometryTag>
struct geometry_id
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<GeometryTag>)
        );
};


template <>
struct geometry_id<point_tag>            : boost::mpl::int_<1> {};


template <>
struct geometry_id<linestring_tag>       : boost::mpl::int_<2> {};


template <>
struct geometry_id<polygon_tag>          : boost::mpl::int_<3> {};


template <>
struct geometry_id<multi_point_tag>      : boost::mpl::int_<4> {};


template <>
struct geometry_id<multi_linestring_tag> : boost::mpl::int_<5> {};


template <>
struct geometry_id<multi_polygon_tag>    : boost::mpl::int_<6> {};


template <>
struct geometry_id<segment_tag>          : boost::mpl::int_<92> {};


template <>
struct geometry_id<ring_tag>             : boost::mpl::int_<93> {};


template <>
struct geometry_id<box_tag>              : boost::mpl::int_<94> {};


} // namespace core_dispatch
#endif



/*!
\brief Meta-function returning the id of a geometry type
\details The meta-function geometry_id defines a numerical ID (based on
    boost::mpl::int_<...> ) for each geometry concept. A numerical ID is
    sometimes useful, and within Boost.Geometry it is used for the
    reverse_dispatch metafuntion.
\note Used for e.g. reverse meta-function
\ingroup core
*/
template <typename Geometry>
struct geometry_id : core_dispatch::geometry_id<typename tag<Geometry>::type>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_GEOMETRY_ID_HPP

/* geometry_id.hpp
2637VxW7PsLfoGI+NFgLFynTUdsV9dtExx0ENNG14+tvOGk6njbmGUVTPTF8aH3OuGQ/jSbaYZRhOr3maInP1l2C5XlmV5s+ID5dxYmct5TEJUcjeM/N1uFH2ajFz95XDrK38q/xzS661BpLePBs54M9qBHVoSXEaFe1V7HxTVURnZGcjc6uEvqWGSpWzsi2a+s5mPx0X9nkM0ldeJrjktsICjMxdJ4QFvpgD4/8IM0Zc3+lVCjlJ+AhgpPolA7FC89ne84LM19gO13N0Y/MBNp5GtbTsEfQd9dcr2x5rmh6KmgHMn54CZTojDZrJBAfg7a+g+wXg/GVSoLxA20E/U6OuUil5aZhOPy857cITvF5IhqtQ0k6TkKE6FBEZzWhvtSw3r6CZNKT4DwUQWcuPxOgj8xfMR1twEAbo9tdY6wgG7NwjSE6mj54BJQQHPTSFWhcZA+2KMemcslH63OimPUGYCgHsj07fY38YkoPXTYSw4f7jRI7Je5PmnYiyyYS3+50IuSULvmCBkeyldHKWT3X9ohxzJbryMTZzrdW/xjNDDUc5AT0LHZUvrojW3Upe4msG2o+DY4gK3otkNtorFHKkimgdXwkCWjlWzOf7BOgMuRPzt1JZpZyqDvCVJetd0ALkIY9wueeicSnzuQUcsajKevojehp4sh7J9a0JOqiDPQSe8WQv4JBV53iFjI30Oj0hGoJsogmU9b9lBC/OmoVcTPSlmaR+HLZkqsP8OEfB7Pw41jB71hSvdN895BjMSd69DSNlb6ENgrzlVKIRvjQbJeND9z1bnQUNL02Xl8FtehsnVDmc3aP+iU3+wqo5mfr05v0luUowhOd5BuKb6YValoovcgYII4ezU/xTJC+ob58LX5sIhF+Y7koXS5v3W1g5p+aqDCd3+h7NBZ9lynBIB3PWeu9LxY6Ng1rPoNjfCudYS4ReugGpUWDVHNhwsqHNoXitQafynSphK5Zvr7dPULrgeeyUWW47tKalRmffXCN+LZuGNFhAon6lqbH5iEKz9+hqMey+AAvjUTCQzG6eHkOvRhacsk8rDjiwePKm+imp8AefVHMok5PkagBvGufS7TRny0WbEyYD9pCVIezxvYvyr9lrEjxa+k5ZqxIdHX1HTNGJHrt3oJ7XcLjqOAYzU6P/jjWeasxdFp8O33V7E7G8aFs2PlY6e1jQCs9Fb25Fc/kYx8DRvmQ4dp7p8QndmyIpvnsbq6/2VE5/+hCaswyxdGTSiL0IKRtY9TlMOT0HDaPWGx09j0UTM8L/IEJ9Tg+pgAkPy1LWeLD68FZoamhnVXBqhVcSg/S1Vsr5HR29/JsohxD885yq9wF+M0x1BkaGqKSTZdhNAYf23q8nU9V9jgmTAUY24/8rREZPStolcc+J2fwwzDKQhfcJ2qlI4XLWVV0YKFciItuOeEt/LjvQdvFxiaKj4jolwaMtOWeuhMRem7z4WxCdAODd7ekR+tziIxVQ9oN58ePW8cl+nBPS1Zrf2+vyUcPjPmgQTyfmqt9FF912Umd0CzbSKlYQeNaLJ8x+YZ6QsWRKipRcJ42uM3HiB/a5UP8wEOWDcYhGFHRtEwtPpiczo0T1qQP9BR8YyR8bT75UYMTz0sV87LlVJ4LFd/fHleJ4SNP1ut0fBJvk4G/uZGXsWvxIQ9fQtTJsB79/pwyd8iJOfH8RC0+WCEL5puHEP4+bwz8UFVoZBSnHwztTD5omNBJOuc+IlueUvZdidEvWZJtYnma7ATtHK3J0VKYsUe7Dj8a/Vn56A2Gmlt9+UxLD8uHZlht9d6DDdS3c8uY34LnrsTyM3eOxfBDH2+3z9DKL7rhsFaf2radTtcwKz3vpLE=
*/