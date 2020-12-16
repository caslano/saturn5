// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_INVALID_POINT_HPP
#define BOOST_GEOMETRY_PROJECTIONS_INVALID_POINT_HPP


#include <cmath>

#include <boost/geometry/core/access.hpp>


namespace boost { namespace geometry { namespace projections
{

// Originally in pj_transform()
template <typename Point>
inline void set_invalid_point(Point & point)
{
    geometry::set<0>(point, HUGE_VAL);
    geometry::set<1>(point, HUGE_VAL);
}

template <typename Point>
inline bool is_invalid_point(Point const& point)
{
    return geometry::get<0>(point) == HUGE_VAL;
}

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_INVALID_POINT_HPP

/* invalid_point.hpp
Pwbg6nf441qA85PlAuBiPrjNAXQ7A+j2AednlysCcI8Dzq9Pvwy4dT64DwXgTgHX6oO7NUCWpp6AWAhwfnTbgPOzyyXA+cky1hNwdg/cUr+xpycg1gpckw/uGHCr/ezZE5CXEED3gwC7/DEAt3Snv13WAedHtwW4mJ9/BuD2BeDGA3DTwPnZ5ckBuOcC52ezYwG6HwfOr90/E1DfjTsDcqICcLFd/jzX7grI0wHOr68MBNClgPNr25kA3JXANfngrg6Q5Z3AtfrZEzi/fnRTAO7XAfrV9/rjzuv1l3Nzr7+c/QF0473+cs4E4J7R6+/zL+n198HXBuDeFiDniV5/H/xRgM3+EoCL9QX4bl+A7wbQbQ/ADQXgLg+or+SLc6xnABcTOKvNyC9HO2gc6PrMNUoA7gMAtPrgvhxA9wMAVvrg/gjAeT642CX+dBcAt8YH1wncWh/c5QE8iwG4pwbU92rg/HS4AbjVfjYLwN0cwDO621+WtcD58dwMnJ9+vcC1+OAeFkCXA26F8rOLDdxjgNN9+hLTngG4owG4lwTgXhuAe1sA7jrgWn1wJ4Fr88Hdom0G3R9stlF/pb5+A9fEcJcauNXANSrcbrNtGd2AgWsHrsmH5+YAXCerz+TZy+hM3AhwK3xwY8C1+OBKwJ3ng7sKuHU+uGuBW+OD+1wA7mbgWn1w1qX+OqwAbrUP7gLg/NqhAzg/m20Drk35S6fZx4Bbp3BdBu4xDLfdwL2C4boZbpH7L71/1PlAAxfzwS1Wv/cLHP7fZeAKEcz/dbNxS/DfcuAsK2L9Az/i7uCKBmuJC4sSrDEdsZa5sDqCnU5Yqlw9wWa2a1hDBTasYYsIdqeIhi0m2IsXaVgjwb7egqeolFXA9O8h6zaYsQ36HLAOW9dYx61TUKEt0hlJRJ4YeXXko5EfROqid4vujE5EZ6JXR2+Ifif69+jauovrLq97bN3L6z5U99262+rOr39wfbz+ifWvrv9I/Q/w30/qf1V/uv6v9UsaljTcseE+DRc27G440DDTcGXDixre3PChhs81nGr4fsMPGn7VcNrz328bftfw94bbjP/arNn/3QX/6bt17lMz7i8QUIU5X97Rv3cVMNwLKy/GtVT4Pq5V1jJrJf5txb/i7hzAVqIV0U4oxX8EbCku86cMf3g5nOPOsORv8LsNZBO4vx7XCrTFVbg+iGsZcA4cby/uj6DMyGLc4/ca0L8TfH6K63yw34Pr5bh+CtwuOOmzcf0Cz2vRfpO4Xobr57iuB/4hkhb3sn7UCz5SHsiCcloOkgF1U73Evy8m5AatlAtyyDpRH8mzVtUNfVCv1AO647eXP/CgBy9WD8qDr5QL8kI2lIkpPfEMmYg/9EDdUpdJpefPpRyoT+rTZtjGkBP1SF6oh+QVtEcYnWm339/BlQVyk93IFkw/0gl6Q44zV/+n51n/fO3/yjucGfvPt/7JM1i/9nddN3CQSeBJLi4PeEo5NtyB6oeM1JaoT8pr+j7qh3y8j8+vft32f1lxZuqfj/0/vuLM2L+KD4AmvBxXhZTDlOHypSQH9SE8A4fLp19ombVcqRUkG8kFviTbbLmonUyZuB9QPajT7L+oF/IZvrCtRj9Q+qJerfOZG4diK/6149BPlodr/+tDjgPX14drA27/pyxfmP3fsZzmWdQl69iyBPGXJXwuVnMz8KiDeIE3yfrQ5VL+NtUeqJvqWaPaDfpAfikf5ES9Uq+9sg2gD/EjHUFDOgje25dpuUCvbI76II+sD/yhB+kEfaQM4E22EXXddznZCDJI/aAb5FxYf4gsoD1gc94ncE9yQCZcyo8mcX29SfJDvVTf+VXWXiiD8sSH183HFcg=
*/