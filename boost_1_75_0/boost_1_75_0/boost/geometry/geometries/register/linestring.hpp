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
Z9D5DPs+ZlzYZAGZvl+scG8ka43Zypv9jk4hWQ0qmLbJqDx29QP+jDXyYQ0NWanA7kek096vv2mwPedf0v0LetyTOEeeQKx55C4lDCiqKs9UepbuOWJ1h1cx01RovLSoOnGR031ZxvSKvENEagGVHzfQNLr82jY3bM+utdo6FrFUvT1Cd7lPQkh2zBffdzQpaj71zThyEwwx94L/MprqlLWAubR2oXQnAnyBiDLwqTifZXU5mE1S579P0eVTrwP6n7KIX7uu/aAiTLmXKQ2DDlHF/dnHufpMd5xltRhNm0zqhC9U4J56u2HtFHLH/nLAU/Q2UPKaGX1gnLd8cScf9Bv5bNhnkROBp4W5wHbE+KYg9982BS7c2cCe0g/s+8uHphB+9d2FrWNXjNZvi5IG1RH/Pr1U2d0acQ77InApm4cHHblVuFpaQUjU67k9DBrz/iS0fUTsMfnh0AOU19zWW5+22TOTc5TooD65EAGZlReREIE7YAGTRjq2OasUqVQut4xdJl6Txids/nW9FX1ORq2PvdzNwTKMnnSNsBZLKfNatk6gsuvDGYEoC3gJY6HGTEbFYtjXnEKM1cRG+RnLxuLek7560On/Bksxuzck8KsrWD13wG/3kS/ortexuJW8cVW197YrO53lpm+197wr3Y60rhVa/HKQqbQaY1VIAn4GPLEqxLYOrrSpocegZ+KXAjd/yg1+Weooun/O
*/