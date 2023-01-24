// Boost.Geometry

// Copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_LINE_INTERPOLATE_HPP
#define BOOST_GEOMETRY_STRATEGIES_LINE_INTERPOLATE_HPP


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace line_interpolate
{

namespace services
{

template <typename CSTag>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_CS
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::line_interpolate

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_LINE_INTERPOLATE_HPP

/* line_interpolate.hpp
TB/zHo4slxCgSEuaM1+smZGTQyLgCL+7a7W3i3yUB4/R3lxxlZgJO5OmuvVqo3zL4N3TMYIILALt9ZVsX/lne4uuOO9SObVcxTWvPsqsOoVTOVElOgn7nC8/xQGuKAbPMl1PT8BZCYSQgDwyBkTc67gbj+I3iA38qVJMjdNbQpgU95Cq5ilrU6svigEjffa6xchBE3UNEBE7KRK80ETTgTIPMkoLYjM49QnfM2PWIwvAA7iwavTL3qdc+UO23xYHXa6Eck7aN6M0kmrmZEHG/Pazd27tvYWY9w0J4M8Zp6w2f1Q0F6pvRHIqS8rBCK6T3X/atDe47B4TZYeexoWobwRm7zQ+KNZH704p52QMpmx2TJKTaI6S5dDruK3kCOsP6oX6JAeaAPk7kBkOhNOMNAb9qhk6Xz1MJpIz1/PMHo2F+Mj1aIT4jPL149YDB+JI/uzT6GUPUrbyGk8rcYw0snzHtMrtZDUmDswT1aB4IlwfXqhTqoxfHGlfpopyN+rzDk1Teag1WEb2NsCnR8F94Dv3W1NY7A1b3crDCuSeysqhVriLukUCtxC5rfTYeQ2/IHJpXRkvrYB3C7rjCKp0dWw4sFXoVtqVc76j238ZcIlweVwbW6wLH+3OYXjwMjXZq9s6yathO94kkQn+fUaFCi5lTdh0Qed75Y9qXSsIdbIVNVmFtv9UhcrIwYVUGRAKLx3PNew7VDRwBA6w
*/