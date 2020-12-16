// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_REGISTER_MULTI_POINT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_REGISTER_MULTI_POINT_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

/*!
\brief \brief_macro{multi_point}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_MULTI_POINT, multi_point} The
    multi_point may contain template parameters, which must be specified then.
\param MultiPoint \param_macro_type{multi_point}

\qbk{
[heading Example]
[register_multi_point]
[register_multi_point_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_MULTI_POINT(MultiPoint) \
namespace boost { namespace geometry { namespace traits {  \
    template<> struct tag<MultiPoint> { typedef multi_point_tag type; }; \
}}}


/*!
\brief \brief_macro{templated multi_point}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_MULTI_POINT_TEMPLATED, templated multi_point}
    \details_macro_templated{multi_point, point}
\param MultiPoint \param_macro_type{multi_point (without template parameters)}

\qbk{
[heading Example]
[register_multi_point_templated]
[register_multi_point_templated_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_MULTI_POINT_TEMPLATED(MultiPoint) \
namespace boost { namespace geometry { namespace traits {  \
    template<typename Point> struct tag< MultiPoint<Point> > { typedef multi_point_tag type; }; \
}}}


#endif // BOOST_GEOMETRY_GEOMETRIES_REGISTER_MULTI_POINT_HPP

/* multi_point.hpp
lQ7VDxWI+9fd31luTVvHz7qB5VTL4J4T+u2flsEHxa4XuZv0s4+I/FDAmN6MNbXtOSB2rnGvssJk/D7L0nvMRX+kK1X0fJoHRS/ffRt2a+rYqFD0DroLqfefkEq/0vpUxbxc+dU76Df+S/e54n6a3V+I+5dlvaG23/vSdJ17LRfz363e+D2LMtXRusfMw/4qfj3j9ywdO6rbd8Tt9aRmPd6w/MOEwXNCw6D+rBJ/Nrlqa5xOiLth7r6k7TRCcjPqUdcu3l83pC/mmywKy7oh3J2Vgl9F2eFeT7yc6ZHMd1exsA6qASrF/sQ3KbxybFyi9ltl+m0t+20wi8VsL/r7tFzvhC+gXjR7dKEzP6lwnxeW8Oi/Ljw+y/N7dxY47gqcl0wrUz90LUL1sKV1JvGEqTMBfeyoEb6A5VBXasEBWmfifwpZZ/Rrx+D7ADqKu/q6LuD40wS7zvxwrrnje66YnbeiTRmbZd7H//OUzF1N2fhN5CSpH7OR24lbr3ur1VPdcOrLaW0/xQ4rByJnIjtrXjMZm5euE14nfpz2vwPd9BvbxWyp1cLqo/XY8a9N+fmD1tm94maeJbKx38Lv7vNp9oeTZErp/Pg9ceMReQZ+fCByjiWy+uHMWfISfGuTLr/3Jnli/2fpYz3h5hmmHs8T818tvzHLdL0r2YRhs6RtrJmjvyByvEvbflnryyO+r6XQR+k635eog8jpth7qc+THpT7ACrb95NcF6wCyrsHNNWWdOCJrHCnX0ae1XJd5FzxupN5bpvUmHyXl+kyQcj1raqF8z1EwO9i4Ud00NWneSeRVZcaM+o5BzCa5Uk15z5uUk5M7y+9OfmnLu4u9K4Kum1SB7cV8fIXexZfZl23mALFjfBaHuPXbfdi1OvH52aQBq4z2hsVgM4DA+l1b63dDcdvK3Y3nXIlajmrNu9YzKE0v9T8t1Lc9al5MzbgWf9FDulX0elhxjH+Hsea3lf7qBGPtS+T9r7O2La+oTT87/6yebahlvan40dod7N75kWJm1+UYWqMU0xd1Fz8SrShGDO9h5tSBB8V+ZPm6rm1XCzHPdF9MvzORstZlNG1GCmketbA4plJMo/BwToWL9HjpbpLs7ob6X/Z9fbmxvG3nFfH3Y1cCJXkWNp6jBDhn5b0sYQ3zH5eZedZTqMqoaB2nDdf3UOhjx66fFf8WN+g+gcBvp7Q+Ioue5IvpewaLnqYXdXS4xIn2Nl7Hb2edvQSBdXb1uNL3mTVgW/3u3vWrllfz2b0UVPm2Y25+0Lmeuskw9TJD5MZWqPOI64j5MdcSXGj5Uj/qmHlC298k/aU9r63r0fl5gfV2hrgpNPOgYyJPlq/MQ32z/5jYWYn5EJStp88KWFf1tdqJ2h+2Fzc7ORltjPaRluuU6FWSM03iqfu7x+r353UojfHy/XmMc77lRMzuQznfn7eMaQu8EXbZcsx3oTap+1hPXKxXv08XO/qMjHGUZdvOINv3WnKGoW22D7fn1H/PLPHauHfMq+N2h7ilpkRjp1KE8V/XU2RdbGv8f7amYO/Dq/HbhffhyZpu+e/JTNvZMEfbTgJRD7aAdllc+1vQsqiNpn1cxdypVJBgZVLdNjRl8oDIjcLKlEkzlnpNzGPDtDyq+8Zmb3Skq9Auembt9n0xP+Y96YniPme39lcWd257ZK7i/25gkui5A94NPC16TYK9bxF3r5zX+SjyTJy8K8+rGnbK43X2c/PHkSP5080a7KdiJyYs2NkRgzHP+t02/0XX1tiV/4dvvSJBxnqOm1mTZk6lts8pMPOjeAlLujWTtZZ0HW+dELfnrAzOxP2cmx3zrfZl/NDzi3UedkTClhpW+t5X9iwGjM8=
*/