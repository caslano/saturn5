// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_NULL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_NULL_HPP

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct calculate_null
{
    template<typename ReturnType, typename Geometry, typename Strategy>
    static inline ReturnType apply(Geometry const& , Strategy const&)
    {
        return ReturnType();
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_NULL_HPP

/* calculate_null.hpp
zQdtfX3iQlHnodfB+MSOCocuQ1vOEijcFQBfsDrFVTrqnRpXYEemzOdETYZRexXXtvfe2Eme/8nyCqVljl33REYJ/62Vm3Ewk03DbQtmym6i0yPwxzf/QRJBCjsszcu36u44XWcRk5pd1jvZNRsCB1WwwtcvEgPzlTQ5JkWUTZmNSalg58sAsCb150kY1d1jP4sZe/r9zI7Hz7E6QWrVsT2VDTN2BDqlnYsWsK9T0JuDmx9MTKF7IBFQRupHos3uVqQKx01+J2S+kEq0/0SqzZOeu/vwGzs42KFT1YfCzsYJB69+gxfDA5GhkIjKeItxIYhDmMHS08h5N/4viecyQAlCRJPDDy6ZqBp2jJLCvU4n+bk+h6uptEjG6fh/26St5OSFs+yyqJkp2OUrxGhWWmDk1GB0MDoc0aOwjmhjkIrvqaVNhFJQL3bYDtpIyQRL4SSMRD7lcXC8bo5OYeMWwS735NS8v6Uqguuk/cFym0AhaGF6zOaI8v2ME9K93eYvTbWiAWs95/CjThW8jKe6H5cFAjisERToAIKmV5Uh9ZVW9Z2wR5AjbcKA3A==
*/