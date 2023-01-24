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
va+LLNZ30qsZHV7o8B6aFKgVAFrQODcIEaLiFTu8iemwT/0xpIO5/axx8U7/5MUDwkyCdKX5JFOLqAVVMuyrDK+qVh8cU0pCpVbias9YuP7QjTAjW9uEfmNgEdWjP9+8M3CJZLbocYhhZBAbVoP6pN7ZgK2VqFF1bE7Rf/9Qj8df7ss7LyF1VJ0NC12tbjAYy61AaghAaE/nR3q8qZZYfyuXS29Y1j7IIrehST2nSt8H/Jl+1AT8vRqpVI3+M+lVfQ3X3wZf0IW+p0lmhuToHLMs6NeBDw5tbGfhzMFvJm/5jHvn0IdtW2GBH+h+HNuaZGGxWfrTdWSOgcReFBVWj5J8hoghccpaQ4ear14xaRbFw6bVC+Skpd2K85q3r6Xz9j1Wbp8afOBYypaDgZrIkEsMz4OBK7J+KH2KXQPCqyJU55cAlC8+iILMIspFCZXvggYIXiUv8f6yJZwqGbRK6pTUB5PSJRYWVvP0MSH6cG3AuQUzXvHWZNTKbKqbYNJefE/ngT6r/fhWXAv8GS09G4JJlmDJyttnO2fuHCmgSQziqUfKFbmv0GUxzyx7ngGXbYWG9cr39nnIeBg/Q7jcj5AvmaASETP/L1hiFlXsS+IwlqoHKClPLFiOAeFHGVa13D+olyjW1FmxprzZNcYRnYkey2gvZX3mazdTJyzzvJ4gH7VZF5QyZfxSin7YFIm+xlSYq+keDKv9gOPQ
*/