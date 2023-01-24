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
+JU74Q3WosfEH5iM9Z1w6MZXuGv/faspq94Wua08dnRb4soMljoQbS/XFQBvBBwjhkgRDu6PsIih7WcpCCDD8voEULAQKBeEtvdJ7hujCg7vnLp3dk16zt6ZSdquzWrbYGVbzGf9x+jOltQT/Hp0CsX8hZWECjAPklQjPAZXm8/bOjMp0qszP/+erVeXk37NGklFNjoF+d3eX3vNtt503RG41LKlj/bcy1Nv66sCBgemmGPPj55BUJhNeY/lY5CMR2vDxYVFXr2i1JaFfeKWdMcIlGQhL1+0VCoQVCsNHAVtrchrHd69NyZ8ztaZQhqqfUh15/u1XGS+yHnWahXdxtXONIk4caU7vY9wLG1s3ZX8caloE2LvEPo2xaWVQ8FcHe1bnSmHrN89X96mT4OXSm1xA6/uMXsSHZZ7T4UJnYveHvSLUKpi3ArSAP+lW0Dt3nX5DxnWAdVEmIRFEUQQTkGKNFFpIl16ExFQkCYiJTRFiNJCb4HQi9IsNIUQUJEO0ltC7yWhhx56gAABAgQIIcfdvevv7X7/7Dczu+/t2535/jE/wF8sPbH6+oJaHoOr1M3AK8t0gOM7j/V3NpaeFPPOEhGbX5xwNZBoPHiSHz0Ouh4NEen27a06AIxmY5oL+86N1myMo6WHC1l2YxAkI1ZXDZneHgRt/d1Y+KexPghST7UENG15rNVk6ZYUY3yUvFhXe4aSlk9cEtvE
*/