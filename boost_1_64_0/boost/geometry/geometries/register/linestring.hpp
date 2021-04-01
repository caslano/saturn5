// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_REGISTER_LINESTRING_HPP
#define BOOST_GEOMETRY_GEOMETRIES_REGISTER_LINESTRING_HPP


#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

/*!
\brief \brief_macro{linestring}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_LINESTRING, linestring} The
    linestring may contain template parameters, which must be specified then.
\param Linestring \param_macro_type{linestring}

\qbk{
[heading Example]
[register_linestring]
[register_linestring_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_LINESTRING(Linestring) \
namespace boost { namespace geometry { namespace traits {  \
    template<> struct tag<Linestring> { typedef linestring_tag type; }; \
}}}


/*!
\brief \brief_macro{templated linestring}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_LINESTRING_TEMPLATED, templated linestring}
    \details_macro_templated{linestring, point}
\param Linestring \param_macro_type{linestring (without template parameters)}

\qbk{
[heading Example]
[register_linestring_templated]
[register_linestring_templated_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_LINESTRING_TEMPLATED(Linestring) \
namespace boost { namespace geometry { namespace traits {  \
    template<typename P> struct tag< Linestring<P> > { typedef linestring_tag type; }; \
}}}


#endif // BOOST_GEOMETRY_GEOMETRIES_REGISTER_LINESTRING_HPP

/* linestring.hpp
4WZl6w/SAO8TeXiAOD6d/08e0tqslmM4EMPD++xtyGjNBh10TfP3cpOL5DZOMKZtrCN6xyT9QLXT9T5CdFB4Zw3lWbWTm7BwD8TBEZNTd76VszVqUR8EoOXxVkAWgCqud/ojUIDtfdZqaEY7J7ieWZcP/wGDjExR2y6BUqZZpTWxYH+SgiST4EfXS6Sw5DxJDKqyAIUozgN1/G/kSzsKf2e+HgeTJP1HpmnnPxP5YvegfIpJ2gHzsXE+jtl1MclOuFpRGO9aNZuYJY2kT9x4iD3KcQXor1CXLI3aOs/bEtiBfLNqP2qcoyKfRKlDGWdr8tsZmQL2eB5qpsnK2mGDkhxpSGm2ZmxeVsN+bXhHAF9ZhAQGb/c/ez/oOihZvUSbPNENT4h1yZKAOma8pyBKB034vrnulLrxpuxyoOYazQFsRVxTAEsdNQa4v+BKzOFGJbqz2EaP6wW2QUwSrSU0/Vcon/VndZsWaJRWgs0hbSN7eCD3gFJQ6yD48y4GElDn0uBbsw/M/sADfZOyquWdlkF4l6u+kDtgef+KUYk/d7JdYl/qsPn2Q96Ezg==
*/