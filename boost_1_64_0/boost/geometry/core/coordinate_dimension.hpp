// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_COORDINATE_DIMENSION_HPP
#define BOOST_GEOMETRY_CORE_COORDINATE_DIMENSION_HPP


#include <cstddef>

#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/util/bare_type.hpp>

namespace boost { namespace geometry
{

namespace traits
{

/*!
\brief Traits class indicating the number of dimensions of a point
\par Geometries:
    - point
\par Specializations should provide:
    - value (should be derived from boost::mpl::int_<D>
\ingroup traits
*/
template <typename Point, typename Enable = void>
struct dimension
{
   BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_POINT_TYPE, (types<Point>)
        );
};

} // namespace traits

#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

// Base class derive from its own specialization of point-tag
template <typename T, typename G>
struct dimension : dimension<point_tag, typename point_type<T, G>::type> {};

template <typename P>
struct dimension<point_tag, P>
    : traits::dimension<typename geometry::util::bare_type<P>::type>
{
    BOOST_MPL_ASSERT_MSG(
        (traits::dimension<typename geometry::util::bare_type<P>::type>::value > 0),
        INVALID_DIMENSION_VALUE,
        (traits::dimension<typename geometry::util::bare_type<P>::type>)
    );
};

} // namespace core_dispatch
#endif

/*!
\brief \brief_meta{value, number of coordinates (the number of axes of any geometry), \meta_point_type}
\tparam Geometry \tparam_geometry
\ingroup core

\qbk{[include reference/core/coordinate_dimension.qbk]}
*/
template <typename Geometry>
struct dimension
    : core_dispatch::dimension
        <
            typename tag<Geometry>::type,
            typename geometry::util::bare_type<Geometry>::type
        >
{};

/*!
\brief assert_dimension, enables compile-time checking if coordinate dimensions are as expected
\ingroup utility
*/
template <typename Geometry, int Dimensions>
inline void assert_dimension()
{
    BOOST_STATIC_ASSERT(( static_cast<int>(dimension<Geometry>::value) == Dimensions ));
}

/*!
\brief assert_dimension, enables compile-time checking if coordinate dimensions are as expected
\ingroup utility
*/
template <typename Geometry, int Dimensions>
inline void assert_dimension_less_equal()
{
    BOOST_STATIC_ASSERT(( static_cast<int>(dimension<Geometry>::type::value) <= Dimensions ));
}

template <typename Geometry, int Dimensions>
inline void assert_dimension_greater_equal()
{
    BOOST_STATIC_ASSERT(( static_cast<int>(dimension<Geometry>::type::value) >= Dimensions ));
}

/*!
\brief assert_dimension_equal, enables compile-time checking if coordinate dimensions of two geometries are equal
\ingroup utility
*/
template <typename G1, typename G2>
inline void assert_dimension_equal()
{
    BOOST_STATIC_ASSERT(( static_cast<size_t>(dimension<G1>::type::value) == static_cast<size_t>(dimension<G2>::type::value) ));
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_COORDINATE_DIMENSION_HPP

/* coordinate_dimension.hpp
72a+geNFkSVwGbptXJ5MCEmTUZ5l+yuFd2/0PLjYQlWacxFqLcMN6ITKNa8HVPWcIHEaiiTOi2Y3j0gryl32gjnBg2Ljc9cb6gTyJK8F3QZupKZAunZualUR2oI7Ua+ZckEgKiyOn0CMkTM7ZSVGqxulPQhxRHUe1ifWaweZe/Bi7BQh13KWXY03VLkSH/wtcIOFvHwLws7PY45RzoGg1T9YlHxR0aX4PQa/8Mu+L4ORl2UW8jvEBYJ2/6BwWn/6MuonOoedvxPOVHN8pqx7MlTVLJTudypWGYffd6uu0/OXEOIV0lwR5lLtJG3xc68UrIEKUIM7TuoKt+ljyHZu0V/5c/I7wiBNuX7mvTp9JP3CYZJ0mrofSespaVEgKDMeKE61uJ8aft9fhvyEkiLiXu5hw5K73j/PXV2YinF0qQyIBbjrLUgOpjyKN1xUDZPnu/mMUGnqfYm8F6TBIRkKktLcmQXyl+zOrHOvDdIg/T54yVQ/Jr8COdB1mAWvlN/kLey+bXgdh1fJ/sldMsi4KRWCSXN0t24iuDg+mOJcqjt9y/keA82zsijC/nKJzRJ2ewxuTe/iiF+9x63Fe71+/qM8h37HLPXKXJjoMFeP44OtZfqox+ruUqbtmBwyNwb+ep57R6P29hpx36dfncvYRgnVgbfPG7wFATwtODQQwBDX+tBvJuM3kZyM6zcxjzq9Ga5RLueT+YldCquTErHKSMU+iw7xYKcrL6x2bC6EEr9eLsOT5M7Zjq0CGDbsdVBNXhYPVvUBzVBcU9cqc4imrRxeW19TeBkUh2Rb/Z+68Wvgu6rIKipADb+7tp1NPNypztsPT6DYbTj6ZgiRpM7/7CJy7p4Z9nBjkwjJasgcxAHvdjsfa1+absPN4HA1pz1qbd7Xyjc2z1TpJJjF+ZgHTzP3j5N6MefyEsjnGF7bnEB5Yo9amUxr7QST3E8nqJFT/VZ0+ssLOf1JQp1M20Q1F5rLZNL9oJU0Gec+ZMW8GkF0gGOMFR6qI5b+22RecqEUxd8Nkm79neTCbbNbD4IyVrwq64spcqve2qDRdC3We8fpD+bnE5R+OTTuHn1sFjae7yQKH51HPDB6XIm31sokdZSN7DHK6Wh6LfdMzifiDva2WaAuWtFR1FfGNePd3J6HihgzIVyDXcxU9dIG6V1agDp8f1l9q2SL4frSY1Nu+eipSNEC3TlLf0P+Xavzlt9xD6EKNQSjrCy5x8rvLk5Q267htVTNDOd8cS5Wzlc3/91tpBzoZrOwwxkbA7vOgz4doajZIR0Uo9su/JnOZNq79ziTC3c7O8aZZ9osR/p1bL8L7qEwb+JZ3N6FvSnu10ArGoFI4lDyctfGSZ5neU5Q/dzRvmUqJBPqbhi39uyDQf917hlxH+ABa6df00pKrshmr5xWo3qlK9U/2Tt4o/NJVxd39UWpUCKERw4K3uqkLW6cMXlytvtSjXFJXoi6bWvkYVjwQlwxBpGNA5r/gkaI2Z8fMbAo3fIDeWqLThkP28Y+mnqiA7RqM8teM4u9snLBF2m35A1/gvuWlBvSbJqK9cjw5aN/DF/Lstd8jiUv+TtgEdgLXR2Wc6x0NB3tyHj41M6uNrmcxwCamdIHiXAE3uKGnA5/W5mTp8Up8q4daCh2+Jt5cBARrpiRtmLkPQZhLVJ/LEU2SXVM/c9ntEg9ESo6mhKQGFbkSPtp+Da9B5KGVvrmAnQV976d3Wv37Qw26i6o5x3E4kug7y/xKM/hvlH9cHouFgXuig9q46RzqJ3oZrsa/Iytzw8M9C2VSJiId2e+5KrZ5oB/s105BFN+9gOpmZ+Z7CR37IQn6oM7LUN8RCpNaIdTvYu+DBTZ5dQ=
*/