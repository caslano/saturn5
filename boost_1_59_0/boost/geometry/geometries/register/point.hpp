// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_REGISTER_POINT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_REGISTER_POINT_HPP


#include <cstddef>
#include <type_traits>


#ifndef DOXYGEN_NO_SPECIALIZATIONS

// Starting point, specialize basic traits necessary to register a point
#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, Dim, CoordinateType, CoordinateSystem) \
    template<> struct tag<Point> { typedef point_tag type; }; \
    template<> struct dimension<Point> : std::integral_constant<std::size_t, Dim> {}; \
    template<> struct coordinate_type<Point> { typedef CoordinateType type; }; \
    template<> struct coordinate_system<Point> { typedef CoordinateSystem type; };

// Specialize access class per dimension
#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, Dim, CoordinateType, Get, Set) \
    template<> struct access<Point, Dim> \
    { \
        static inline CoordinateType get(Point const& p) { return p. Get; } \
        static inline void set(Point& p, CoordinateType const& value) { p. Set = value; } \
    };

// Const version
#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, Dim, CoordinateType, Get) \
    template<> struct access<Point, Dim> \
    { \
        static inline CoordinateType get(Point const& p) { return p. Get; } \
    };


// Getter/setter version
#define BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, Dim, CoordinateType, Get, Set) \
    template<> struct access<Point, Dim> \
    { \
        static inline CoordinateType get(Point const& p) \
        { return  p. Get (); } \
        static inline void set(Point& p, CoordinateType const& value) \
        { p. Set ( value ); } \
    };

#endif // DOXYGEN_NO_SPECIALIZATIONS


/*!
\brief \brief_macro{2D point type}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_2D, two-dimensional point type}
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Field0 \param_macro_member{\macro_x}
\param Field1 \param_macro_member{\macro_y}

\qbk{[include reference/geometries/register/point.qbk]}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_2D(Point, CoordinateType, CoordinateSystem, Field0, Field1) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 2, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, 0, CoordinateType, Field0, Field0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, 1, CoordinateType, Field1, Field1) \
}}}

/*!
\brief \brief_macro{3D point type}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_3D, three-dimensional point type}
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Field0 \param_macro_member{\macro_x}
\param Field1 \param_macro_member{\macro_y}
\param Field2 \param_macro_member{\macro_z}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_3D(Point, CoordinateType, CoordinateSystem, Field0, Field1, Field2) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 3, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, 0, CoordinateType, Field0, Field0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, 1, CoordinateType, Field1, Field1) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS(Point, 2, CoordinateType, Field2, Field2) \
}}}

/*!
\brief \brief_macro{2D point type} \brief_macro_const
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_2D_CONST, two-dimensional point type}. \details_macro_const
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Field0 \param_macro_member{\macro_x}
\param Field1 \param_macro_member{\macro_y}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_2D_CONST(Point, CoordinateType, CoordinateSystem, Field0, Field1) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 2, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, 0, CoordinateType, Field0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, 1, CoordinateType, Field1) \
}}}

/*!
\brief \brief_macro{3D point type} \brief_macro_const
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_3D_CONST, three-dimensional point type}. \details_macro_const
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Field0 \param_macro_member{\macro_x}
\param Field1 \param_macro_member{\macro_y}
\param Field2 \param_macro_member{\macro_z}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_3D_CONST(Point, CoordinateType, CoordinateSystem, Field0, Field1, Field2) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 3, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, 0, CoordinateType, Field0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, 1, CoordinateType, Field1) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_CONST(Point, 2, CoordinateType, Field2) \
}}}

/*!
\brief \brief_macro{2D point type} \brief_macro_getset
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET, two-dimensional point type}. \details_macro_getset
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Get0 \param_macro_getset{get, \macro_x}
\param Get1 \param_macro_getset{get, \macro_y}
\param Set0 \param_macro_getset{set, \macro_x}
\param Set1 \param_macro_getset{set, \macro_y}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_2D_GET_SET(Point, CoordinateType, CoordinateSystem, Get0, Get1, Set0, Set1) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 2, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, 0, CoordinateType, Get0, Set0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, 1, CoordinateType, Get1, Set1) \
}}}

/*!
\brief \brief_macro{3D point type} \brief_macro_getset
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_POINT_3D_GET_SET, three-dimensional point type}. \details_macro_getset
\param Point \param_macro_type{Point}
\param CoordinateType \param_macro_coortype{point}
\param CoordinateSystem \param_macro_coorsystem
\param Get0 \param_macro_getset{get, \macro_x}
\param Get1 \param_macro_getset{get, \macro_y}
\param Get2 \param_macro_getset{get, \macro_z}
\param Set0 \param_macro_getset{set, \macro_x}
\param Set1 \param_macro_getset{set, \macro_y}
\param Set2 \param_macro_getset{set, \macro_z}
*/
#define BOOST_GEOMETRY_REGISTER_POINT_3D_GET_SET(Point, CoordinateType, CoordinateSystem, Get0, Get1, Get2, Set0, Set1, Set2) \
namespace boost { namespace geometry { namespace traits {  \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(Point, 3, CoordinateType, CoordinateSystem) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, 0, CoordinateType, Get0, Set0) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, 1, CoordinateType, Get1, Set1) \
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_ACCESS_GET_SET(Point, 2, CoordinateType, Get2, Set2) \
}}}

#endif // BOOST_GEOMETRY_GEOMETRIES_REGISTER_POINT_HPP

/* point.hpp
b5ugddeZ1+FR/j1CkSQfUmVnaprxWVFbH+FO7O0PzRKIIUzsCv7c3mvhZtVCuIPYd1KcL96Losvu43+Ny9X3/bmI9vf+utD9+ZhtovloluP7avLwu/F56ZzNOXhZrvVJ/kGIF3dEULSigfo/5LH8TyoD9v/GexGVF+j+L/FeQMb/U5foarmXHsQec/Tu5WErVqeSDlzAIG9A75AvbgRfL/mfcuHI/lVl0giUKUBlgLg05y+OFC+u4XH1q+av5YdPZsxL+k3yLI/r7Av8/eE408aYtzc9LvoHIJJ6c6bO3j1OXzz/xYy+e733mGbcrhWO8vaqTwGkFMop96p6JrMNIjuFB94TXJZzrmLzQGE5Sx0wa8wDSwOsYVdHJtpPz8VcuV61F7vZbkbX+a37MFXifDO5OIxvo4XPabu6cF4z5mNt+qpISkRDW8sx+JGJ4qWsn6+w3/ll0as3LIFnI9d47EZUctBaba8UgxT/b9bsdObcW2XPd1bA2Udi/fpeh9/GzthX4JbtGjBL/oEggVpYoO746QE/bRhq2m2z1QIBCr9CPFgADYY/guPUL6Z0pwxagDhB6okTfHpTSQSbZ+aeM0gJCWJ4TOB3VuF8t7y9qWeCFDOTMdPZXa+c+GmbTT5b9gCi2CGZcdyGt/l/idMj+G+9+v/0W1rwV+3/Vs8n6z/9xj45nCgAHciAKKI7RB2EIy/s2rEiIz/Wsd2chMdwiHhWIikdip4h+HOOgDDA8CPW/IWJ5NSZhcpPadvRL/ks2+NyHQACQOEb27bZ2LbtpLFt27Ztm42txrbV2OZNdmdnf3wz5yXO+XDJecSK5s7bugfB+4sOaHk8YeJa7eJzRLIdOV2rLcmPNboqUy0Q6npvlJBz9TQ9tK4htKbVQa4+aw4iwAJjtxBzrYYImhPD2Z9Yp6xbacLC6lydxoP7cjYQlMaXLx2RkernhzP7R3Bf9gUJ/zuGkUi5aPsnmFHj3w8nA/PwEqLHik/GLblNN96wBhwTOjQtMtFyhvULVBRmVaCEnkKzeCSj8Ee0Q3SK9IOIRo2rMgdrr9jih6JMFR3ilF9RJ6TXcDGuvXdwEyVKmVoyExutAIoZaJIceGWjIADaE7q7bpXXJmnu+JiR6cxmO+1pLjNI8Ui7/VSQ+etuetOvW2KRx8pJt/ekeKqLeWyMZ42f278wfhIrKFYS80mUjm2rHJGnoqp0f2lhwXEjBuuzHqwTwvOxh7iOZ5p3cU/tlaFTn9fbwcFCRZGceL6Ss/a3lhZ6amooOTmxjl3wa68nZ+0SMhra8NDQLL29PvGARDc5RZXWwZFJnaDBxgem8TYov1aw7zTnoo4T167DEidryzUXg3njl4/K/N9wSOc3ZO1baaidfirT+/cTuvRJ7nQ+WxilH68CbWDWkx9UNBisEKCFp7PR7u/RA1dt6Mfxs4ZnU5d0nbZoMl0UOGyqS/JP6rSoLt+ycV4pMT29nUefGE7IkYK/t9/xRPZ55qdASscliJGHMTXn9RWTTJwPxL1za98ByVPig9NOnXbdUpy4dJd9mMDnAFNx6/afw3Q074VBQjJyCggyMrQ6QCtoQ0jZ6vYjewvS4QQ7GUeaPkyPFxXNy/21nc3KNdBt+Lq1+vpDUtXF2coKJt1gmCUwcC+5wtUTYwm565tIe2pqSl5e3seGVkVwkJ9+ynarf0e/oa+NIKLd6NnaJ28r/8Pbk82ON68dqqG+nhhmVBZr8E09KOtuC55SkZA6eqVrG1sV1bSnn4mtkSk7z5lrz9ZX2OZiOYLE/s7zJmOhumzd2s3n3t3gbwL+CM2eqa23PeL6AaOGzQTaWHt9QvvbADfQ6K0/IOFtmbe+fPr1NVb/1XedXDalzMIU0L7Q8eXm+oewfqKJsO2iNkot8m2NCM7i6BcZBel1SBF0BzHCs4qlH++OMRa0pw1SQ8majp3e8/P98/Pz8kAk5J6aXJeY6n5ViuSxGfq/+0MT/iTsdArTOM4Exq5MI5SXxIzorD7GJOY/va/3TfrikRVIE8Shoo3eHh4absMZZ/9UNcZ+uM41ploDru8cq3bZy+FKoSMxI1tcLFqmDLG7rEYrlXdsPJ6Ctmw4X2cbm+5lSo7tSK9GgPNBIT5tjb38wA5y8mwickS1XTSQhp27ZUOPsFFns+ko1o9isNrj9YHE2eP1g4tF+kvrkxUDn9aOwv29fxqsbl1kOjpbrlimRQeSSjclQuDh6ciuOxfvHhE0KXBWNfFqa3cTgzfTE4WO6m6tzq5Pqr8CmxmP4ULqq5t7cpODxLHqRcW/Qa5OHyCHX7tCGLi5syTk+zBa4fG5KVza0oPz8/FZ9jVT0MtopAsy5F/CzsASVvOQuyhJLVVUknuKTygtUaXgaajrhkYaTAn1eRynZ8uwbotL1QJwC5o5/Z8GLNFppAIkHGUWnSloG8n308ncf8Nxck5vRHBBPCWeBZCeplR1qn8lCE6gfjKH5eblzaQkq8Z27rsonGRkiIeGCmnX/jAHBpPPVgIopgzZSlIv/k3v/Yk9j81JGIbyqFM3gYoI/fYHceWpY7J55oWU2ZzBbBpxKhkAe1kj1AsM4vHucATZb4+x53+BYdKwgOEdBxHNRCbh0jZc9sw2tToyNtRRee1QFg0QXRFybR7Sjpm+dU12tQqRxyKm12JcHflrsMw8Y7PKTXXfQvWIG37xS7mb7c8fyaC1tWezFBeaSIwYBPXsjpJUnYfUwb8XP/ZU0Q4h6t2fbUyU9V49JihCYsdENzsWEUhYiJHgMPD/IvrZdxG+BZBDS4vLw4taI8psBnW9tZc2406UG0Gx8fBSiEVH9x+vDBVFHRsYXQle4uLSzq2tjQXhuPzrKTR9Q+3xRqy0aFNLXvYL+u7y8sEyAGp+N6R+pzfguscSYAOGI9KJWYG91oa8qhoKdJFhvWfOF+kaGri+AX14o8ZOXIHFgdtF24H4PDiiu3t7AVHLzR6Eons6uJzG0VtImeoZmhqY30e01woEAsRaiSKCzsSE9uHlNb3yzG/pASJzAia1V8eHu+GvwfU1MS6/AjMz1O4S7DY63GfnFNe67plBTJkMbMKa9kp4H5+Py+EsFNwkjmCCFw5WGVxYS3T0fZJ6W6XF7g+dmssu7NxDD4aCBdst3vh3LeBG2ROt2e2obHXrCwLiGEjTqbz89CU0+ZxHtFill8p+mofbtX4iXkTttJKQJpzs7PO5jX8qH1zKzrf80WhfW4Dzr78S8PH1Zok4btYo+nJGy8mAZe4tEJuC9oj+Fh/QgsyNZUcO2xyqkgncmVu7+flS5foOTbt0Yz/c+5fBL6DwGEhyx5Xmjdf2XgVpjbqhiSlJdroe3Li09hgqmEtGFsuFvDyHKljtnTso8uWLBWIt17n+9th/9Zt8CBWtXrxezp3IynSSV3p0uwK8aAQGICAhjS0funJNFWUnz3BtBUri4lvB5tdB2enmGBl2/x5rN+/97PgN2/90poNVlfpwC9nFL/xcx3Xb6fqm2vGkqG44pSZXVWnZDxZ9VIlPmFX7DCM2GG0AXTk/hh7dK7euX/iOJyojUYquV+nAbLfX9j+Fv1sKOrOOvOxCoXmCrbCFhJLamo006JfY+bQTyj/nMz9XnhuJJl/BfeCsxjQll1A2y47oEQITLj21N3R3rDYYp6858HuG/r5yzVi8U4Wc4nJzaGho98rvEl1iC9zGUefV99L7qinxBTwYu5GL8KhUTsLpai/MbD9hTjSwe+fOWlapt23mzuLGmpWysaFPptGmPzHd31u4vLlnaazu6Nm3I9nn33fodjH8PQy7Er8brtXXTGpI2DIn5XAnnSZNdTJzLGy4qmYJA7YMDSJdDjePbUXvFY+2EIU7H0hFqnFedzrK6eXinxOk9kMNQ2rmw+7O/XNtx9bawW07MKsplTqvnq5upJsa3aMRjruxUPhcTnV4k/XGr3DV+8NmSux9k2KT1zOprcCayog/6qmO5J2zi7jevPP8gTZARpV8tLyPmxg6w0w2LiRH3I6Js3sX2d/VbwNJxm1hWLfme9VaK1CfN6Wh1u5nT2SiI/Ajsv+pYHF+pphXLZHgoSP2jC2+Iy+YLsYKyzb6N15ib9CEZYcb76FN3oO/q+uwg//loW8P3ZD2yGLZYu2FwcFXb+q5p3/0oQ9f/s8VR3o/6toGvNEhmbSiPFeRL0XZI6komiKxBgBK7K8fa9tpKuTu07Jew9pbRKo/kcvE+ZO2L//+JkeWuy+vruFdJ54UTu65CrX/2oMLiTXIYyjyfnfKn7MwIYht95m3+1Gm4hRdpLUrpe1Kdl59eoxb6qlGv9e9lxDPVWvOgP7RRrvIq3q10z4Krzp6v8E4y4Hzu7zNkMVrFAnhWDFFcQWz7uGjT7JEkOaQZyUzpeRa+friCXbCNY66ODPnACfenhv2jIbStXXtAP5kRiT3HlUOaWzX++Dvi5BHxVMOAFWjuMMvVaG6JqghzqfoyXMwCM0ei0KFGfaCwNtdNqmBk9SpE1fF9n2Q31v26i+9wcLjuzSVXxNnIZGlcM2/6MqgzLFjzZOzQAspOAF7oLB4zO/Ef0mWOXm999q2beYyNkzzKu72Cz+dexq2rFzc+tLhC6Bsq94mITeZDkkXccKQM8b2LAFQlto88FDfDCNILrlJd9NiN/80V1ro78bWUjp69BU4pvD6+Rhu5+/au9u0Gk+3CEh+fj8sRA4LdZxfwzjcp20NoH9sLxay6RCZ+y5QzJdBXOSuPaU37z4INvf19YHO0AfGK4Df2mTWuCo2fDgG21Ej3VQvExoaBzFNVTOhNc+C3s+b8a+z+fdSGuYG1iUMkzG3bxEmTeoakDScbgGFl4a6yyQCh17pcg6xihFsruBBk5i6l4M9E2UyKfJBc89oTDH1xEFxLJm3oUvZBr+gG1dO0YXc+eetjzgwP09NPUAWcAQrNh4KCGxVgV6Ahac82C57tNHTggFe49VQNnMrEfl2BXOmkM2CXjRYAJ7y8J/oTYSeQu7JV77pxIkRm24umRV+MG2tzuvLHpVyBXWdV9C+iygzpYRgY2Iw7NXl5Db5XOuP30mxSmIbrB2drcOERb81tXJuFxeRus7q2H1x9CPbv9JSVn9CMfjwp5nA830CiFZMewoJCTHgSZFA21YjnsCeT4M58tX2dg2rV5UofpRIOm48WC32Ma7FjCWR72zGlj59GlJfdKHAyWkRYwSaT7Aiwb8mrsgYfYoMaxZ0ybB2uqAszsRoO5JeaIZs9V2nCgOZ8XfCjxRJZGxJe5ZH5nxR8vKgEhXA+ck0IFEiWd9Vx9XrkrJzmVB2KK5dznAl0bm+xe5sGsW3bJ4cbB514qGLkw3ITHvIjjgp0g49UiDsUCe0bIdaeef/Eb2QZXak+0tB09yTqpAPBnL5/XKqBDkjgncVRgDF1bK00VKOfOdOLTSkmPvTp8waKmJRVjh014UvvJTFdSWf1d4POyTpGIMxy6rCjDtJG+R0F5y86AQ8VKIxRBd2i4T1rzTKlJb/skk8CVL4wsuszAxS0oN/GfBl+/tN5hVyW9qY6VgcruB/p3A1jbp+zEZBgW72C9G8P4MxmfxfFHlc6yjjBlpINjKVcTn4pBAUufhCv60qTDVG8B/RC3I4QtMttQOINRilwWETeIvpYg0mYVX4rSts7mp2Y7PfuaTBm6nsuNjGS0eiEGC4yFWxA89gJatk5RDEVXGp7I+RqiSBNMowkDZamm25y12Gu9BCw0WK3C4tatXHusuSl59nuFGB0cQtQ3TGOW/cDysHNHyqYvVpC1C4oTLJ6M+mbLqxifgY8xIDYBDjUrrUjJ3Y372aaRozqnPGF14PX843Med4LJqXe7Ys+UKlNBrhjVKJpB2I6o65enQMFB2zPONasUnRe7dZZtukyQX/7hmcHJsOaTB+7JjKMfpWxKOyWCK1LMEx5RTRWWZBf8laBUgfYzjvCcJvq+zI9BNb9sCec/bjJi24wiWXSpH8nEuAeQaUUa3SEVK1qLEyaub4VxDY3qOpqdIv536/n+krh2JuSsGTYhqBCV6WaTt2uBIPCygyF2Iz7y4p+ReBWBkDkoUHFJm5G6z/veyXWqu8H26NubEusWJUyOyQd1wg6KIEMmcTtkLSQzAbWOCm+tdxbqP3RGhD0mbip+qbYZjKSf0KfvPepNqj9w3YFlQp2Tq6u2j8iu+9XH1y7v5OchmjMyxSoCnkPEVawWFPp8cFmVaUwxNfEjQvhcRHB/NfpwTgFalD2P3YkOskopfJJ5mA5k33kX58vos/aLVqr53SczOzPD92H3BzaKJ1x61YiIaieT3MZTb6ZL/fQnORW0gJoxgP1ion2e/R9NbJSqWa3Z9NY40rUtNhNM4dY63UJFxiadahIsRuhAaayX5NWWWxHcfYyOXwQrk254jkClVvTmcJtAZRC4USm8QOoltWxxIt9mAR87gkO1kpG6PUBJivhAOt4uTrc/Iy1iJ0TDJgGlQSpc+Lt1zaa6quL4zm6Rey63jW4HkArv/MZsHammH8ZwXEr9QzuSlBtRKUeOg77ASiqcjQNwU1Ge7XEvZ4OaagQGOmXn/fCJpEVnlrSfZ6WbR8D0+9D6B/CfstHAjTsZVo8ZojjiOQy60zneNlzvNI5Q5AyzBFDVAP1v3KihSEl1TKvtMcJ2ShKjBIKUGdWthsHzXl3lsbJrixpPPnvH343G1/dcfRbeOEDH9wV1Q8de5UVUZjgVDFZpFMJA9iOReCSHSu5DNDRggONOUizQ9WNkB3ym7EdS1TEXr4unlVCPOgSwB+MqVcFFyY3Vy4730Of9zaen/hTZ8r5mWlQ6ZL6+C7geJDUyAKYwxR7HdI+WsHNZONH1O/k0kNCVdu0hQHHLoHV6IOvTQffj0PVnjxHmwued9JKBsrPWw18Xm3ypm0l5RtfY6j918aG4EflrfEXymG7icX4NoOMh66HPrhSfklfNNBS1bumCWkyGT+3k0ASIakZGnszUZXoGZN28R9BPfT0K3ywq1XsdDR0VFET04RVApRQ/Xzv0KMrQkoUJIY3yt12d3PMXDt2LukMfobpzF+uKA2uH8M5Unb+ZOS42DBk8JIoRiMneC0tndKNXGDzcVJtpD5BmXw2pcfWgw3qP62KXPpeb4iAEvb2iqOg6SPXY4K+Inal3T/PP6H8vK7lhqYmfZzhHFpY2YmSGv/dZ8b8K7WVwz7sk07tkaffPzCEJYH4q9XfzlhIXedY/3ErkdJR7ZbLgj66BYz2JwkPfAqrcfi0tmulODkfgF+W2x97YSvX3f+udKj0vXJXd/l7bS4tfK8cvagRtCtWZq8NkO/D7aNLltoajOPKI7vtA3nV54aofvlDYkW9gky2P1yt/hz9cMGV4AZ27Dke/3dWjUhMbVh7+tuq9Mk9hkSVnziTgm4ioaPVeJat9fSiPsOI1pG4Uk4LeBhwUOjZth7PDNpciLg3BAyiNvqXf19wLe+ddLyVc/UpZLXiYriHfQz88uHwoWaQ2ddHgdiDx4qNujQfZPzq3o4H5fiCIeP1/MAYRorO5pXqozGT415B11DyqcR2JRl9Ag0q9K+rnpsaQZt4kGx9no0wqFoovqsxCI2GKAb+NzofpESvXajW/S0kdQACx4YwxzORl4gbRciG0PN
*/