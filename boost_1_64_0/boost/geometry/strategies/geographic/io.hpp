// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_GEOGRAPHIC_IO_HPP
#define BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_GEOGRAPHIC_IO_HPP


#include <boost/geometry/strategies/io.hpp>

#include <boost/geometry/strategies/geographic/point_order.hpp>
#include <boost/geometry/strategies/geographic/point_in_poly_winding.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace io
{

template
    <
        typename FormulaPolicy = strategy::andoyer,
        typename Spheroid = srs::spheroid<double>,
        typename CalculationType = void
    >
struct geographic
{
    typedef strategy::point_order::geographic
        <
            FormulaPolicy,
            Spheroid,
            CalculationType
        > point_order_strategy_type;
    
    point_order_strategy_type get_point_order_strategy() const
    {
        return point_order_strategy_type(m_spheroid);
    }

    template <typename Geometry1, typename Geometry2>
    struct point_in_geometry_strategy
    {
        typedef strategy::within::geographic_winding
            <
                typename point_type<Geometry1>::type,
                typename point_type<Geometry2>::type,
                FormulaPolicy,
                Spheroid,
                CalculationType
            > type;
    };

    template <typename Geometry1, typename Geometry2>
    typename point_in_geometry_strategy<Geometry1, Geometry2>::type
        get_point_in_geometry_strategy() const
    {
        typedef typename point_in_geometry_strategy
            <
                Geometry1, Geometry2
            >::type strategy_type;
        return strategy_type(m_spheroid);
    }

    geographic()
    {}

    geographic(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

private:
    Spheroid m_spheroid;
};

namespace services
{

template <>
struct default_strategy<geographic_tag>
{
    typedef geographic<> type;
};

} // namespace services

}} // namespace strategy::io

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_GEOGRAPHIC_IO_HPP

/* io.hpp
++Gl8EHYDT4E+8BH4WD4GBwKH4fmvq2nNPi+bZHs2z4JO8OnYQJcAxPhM3AGXAcXww3QbNexx4gXPmxv15wtoj+HP8H+8Gc4GP4L3g8ryfuER5vrSDycXSYe465uWpTsd8o89G3YFO6BLeA+OAK+C8fC/TARvgdvhR/AB+EBuAH+Ae6GH8L34cfwCDwET8DD8Cz8E9TmcUdgU3gUdoClsAc8BofCv8Ex8AuYBL+Ei+AJuBKehJvg1/Ad+C38K/wH/AmegbW0+RjsAH+Ew+FZ6IY/wUXwHLwf/gKfhL/CF2BUVfoZWAUegtXg32ENqLWH2jAG1oPtYDQcCOtDte75BfkObnR4v/5K1m9Owmbwa9gRfgOHwW9hAjwFp8LTcA78Dqr36y+CzxMfkn3kh6ELPgL1+oArkXDvSrhaME3CeXmuOcyHneGNUu5z4WQ4D06H82EOXAAL4EJ4G1wEX4c3wbdhgcgtwpX8HbmwjozDmt6rRO4yOV9xC+wGl8Pr4G0wFd4O8+AdcAG8E66EK+AD8C6phyvhC/BukV8o9fEe+Bm8F34F74OaMvfDGvAB/3MYX6InHOvQnudKuc2DreB82BUugH3hQtgfLoJj4E1+5VXwZfD9z+1SXq/AaPgqNOtRkYTzONSjP9Sj/cKDMBZ+BEfBQ3A0PAwnw09hJjwCZ8I/QzXunwj+ntpC+odY2Aq2hGrf+d/s3XlcFeUex3EX3JfATEhRUVFR1FBxzQX3DRV3VJT1ICgCwkFB0XDXQkVzQUNFRUVFRaUy06SisrKiNLOuFaWVFRYVGpXW/cyc3xnOkTlq2/3nyuv1fb1hmHnmmX175pxvbN9HK5Lnxz+gE/6I2vX5N7bnQ095Xt0LHbC31DNbiQz3mQz3IGbIcOuqmOr5JDbADdgaN2IH3ITdMBX74WachltwLj6FT2KaPMfYirtxGx7E7XgE0zEPd+DbuBPfw934Ae7BS7gXtefe39qe3k5yPdcZHbCLxX3sIhlutM79iE2VTNtpKrbFLdgJn8JumCbXY1vRfDwJKLTd7uWYtB/Jwbr4NLbGZ7ENHkftfleh7fskOxhfE9yJHTADu+Nu7IV7MBAz0bw/crlmKm+uzv7oOeZjPTyF6v0GbIqnsT3m4hB8EYfjSxiAL6N6/wEj8BWMw1dRu/8p4w3W2a4ek3YpSVgLF6IzLsI2uBhH4BIZ33IMwhWoXY9/Zyq/t878fkLKT8aWuArdcTX2wjWoPf+Rcqbr1DNL7sMdRFc8hO54GDtiNvbAIxiAR9GAx1A7z/he7lPo1POcrBfnZX14H3vjBeyDH6C2f5NyvHXW84/kvPsSDsICi+EK7jDcZRnuCxnua8t2TEW2tiuUdj3N0QFbWN7nvcNwrWS41jKcO2rTJ8O10BnutNxfyZX1/0VZv5MYIFuG6yv305TtzyjnX8E1TOt3GDbEcFSvZ9ETo3EAzsJRGIuTcTaG4hxMwHhcgQn4FM7FvTgPT+BSfBWX4Ye4HL/CFfgdrsRf8XEsT92ewFq4Ch1xLbbGjdgVN+EwTMUJuBmn41acjdtwJW7HTZiO23AH7sedeAR34SncjXmYiedwH36EB/BrzMIiPIR/4GGszPw8hrUwB9vjM9gVj2NPfA61485Ptp8Tn5f2XO9jW7yA2v5bhmuiM1yItD8yoDOGojxf5yTUNFyKzvP1F6X/l7A55qEnvoLe+Cr64msYhGdwGb6BT+CbqN1nLLa9Pm+V48s2Ob5sR227K7Z1/ogPyPaD9tgCZf/PSbVpuDFl9v8o20FvbIVe2BH74lAcgiNwKJrnU7SUF6Uzn9ylvHZS3iPoie3RGzviWPTEydgZDdgVp2M31JbHDds=
*/