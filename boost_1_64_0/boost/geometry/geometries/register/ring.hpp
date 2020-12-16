// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_REGISTER_RING_HPP
#define BOOST_GEOMETRY_GEOMETRIES_REGISTER_RING_HPP


#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

/*!
\brief \brief_macro{ring}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_RING, ring} The
    ring may contain template parameters, which must be specified then.
\param Ring \param_macro_type{ring}

\qbk{
[heading Example]
[register_ring]
[register_ring_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_RING(Ring) \
namespace boost { namespace geometry { namespace traits {  \
    template<> struct tag<Ring> { typedef ring_tag type; }; \
}}}


/*!
\brief \brief_macro{templated ring}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_RING_TEMPLATED, templated ring}
    \details_macro_templated{ring, point}
\param Ring \param_macro_type{ring (without template parameters)}

\qbk{
[heading Example]
[register_ring_templated]
[register_ring_templated_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_RING_TEMPLATED(Ring) \
namespace boost { namespace geometry { namespace traits {  \
    template<typename P> struct tag< Ring<P> > { typedef ring_tag type; }; \
}}}


#endif // BOOST_GEOMETRY_GEOMETRIES_REGISTER_RING_HPP

/* ring.hpp
63aVgLPOO5I+Jdc645svdXwT5ykztjFzhO3yzA7eRJEtfVaOPKum7R9+bUaZscwPeti5S/Nc7RxE6VjmSztn/McyNTVcrciXxyVcexjLpDmHnku438F9PObmOR/Koefih2Oeifkmdc9wKYnBhpg7KlXzf9k8591OEvYqi35H9Gb4/Ee/Lo+IlDLpmC1FbTFuPJXMWEj9LMb8VIKs03f3P5vP/7ne+Rq/xfvxo1KSnLGBu2POcxd/aD83XNyomQs3mxw3ejedrZy+8+MU2uMk+jRl92TKG8reU5uI/IkZI/3na0ydqgTOaZuqrGOfCq07pauenjNYpt3hbAhpY/huJSHwXLB3lvgC09ZL/wMbwQV235tWvu/VUw6C9btqv7X53i2sKjJZkeRxh1qvVzf1zTcbZ0T+xFPH2uY2Z3Lo3Mt5zs/VPOYdarbxo5vUvd34Xf57EP2eWewleet7LH2v7bitI/F5Xha3rzDvruMk/Kc8EZT9Sn5nIvivO9dNl77D/QVzy1TTr/lOA5qcW5Dv7D3fCX+XZ0VTv51nTZ6lJwaY+U2yPPOEhz8Nk6yZu9K1Dy6Q5412f+wKY50gkp29TU1/fEN126xWQH88WNKKvtKvPz4veq/Tcy0z7yFGiL/XuKuR6rpWX+Zchp4JbeYWyX2KRyWMDTy2vcGl3zJLw5qofWz1dN/69glWMWSuR906doNvrTY2fOEnMX3pDMJ6yRrXhe4hLZFnXaYyZ0xpHMu1/7q//wex/6k7WHvfT9PkkNhpLnp9tL1/Hz3/+yv402clqj3aeaN3sX7Prfc3XE++3OC0c/G0HfGVbP266A1DaTsaX1RT2yg1y0NtMW7CokwbrX4exfxJaWOPmwl4VJi++8Rsm/rNLPMX/I+K0na+tpofQRX73EvP7/XEZAXcSarKyZ93ikz+LPPlT3deNV/4DpIbSDe5v1DXlhaJ3M9zp9ur60tOnrUJmmddkO4TN9M9ZfJM3K+BW8R8uMqWkwcBebpA7AwOyNObRa9bhfPUOXtksrhb71lGObLT+jjpmFPk9OPPO/14mJ1uXvS7oExfuY809u+T1c5ElPbJz5ddX6ipzygpcvL7LvI70Zff4boGjNk6lOb3Bju/o538VvODqGKfe/Jbth20A56y+V1f87tksea3p1psWCLLDmGR/B8T4eT8hfK9jea72ectci9PB+t3S/RMe7SQ2npJ0LzPQuor7l4ImffjxHzIBfO+jtgZLXrZmveJohdhhcr77IC8r2fy3i3uwrwTKY92uh8mTUct1rzPNVkveeJCPwvl5P0czXqp42o+DOXL91zJdrMmr34fXKzj+7DWkvYxs+2tJ+ERvGqTZ4zD/L7SZ3iH2stJsXr/sJofQBX7+RFONjLSjtKdDmK37Hu1dqT1pym0MX7qMx2/fA6/QB1T+Uvowf6vetYeekZ9lVKq+iWZM3hkzFP4J2OeB6oHruUUlxnf7AxyNvRuOfMq8F3YgSDnquw079EC+uLAe2hu8QWoGRWkCqwB7XFPRs3y4x49lSfkt0ftxU2k5wVMdZyi/qSHGvuoeQMz3ugtcphnJ6EMNvbJNm7qmu/Veogc7nk22BlPOkbpJHbiPXtdOu4x/tTAjhmzzGVZZcKs3Bxxl4rOLrEzwt3clazz4lJ7l8+YJO+oE3VP97Vi9133Pe7Gfmv4U6fo237znfUEsVfTWsRa9jbXWPPNxmein+Aq8322GRddV0vW/tlH+BN6/m7Osd5/1m+dXpLLrOUkibuxQd3UtOsgY9+ON+v7a2+N2OhoTwoVlRU4nQPfxPvxm3XO0FmmKk67LmZZmG0xbnHpSSmdA6v/rlt0Dlz0KhvOudir64U=
*/