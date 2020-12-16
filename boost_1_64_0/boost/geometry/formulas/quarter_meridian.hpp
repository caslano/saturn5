// Boost.Geometry

// Copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_QUARTER_MERIDIAN_HPP
#define BOOST_GEOMETRY_FORMULAS_QUARTER_MERIDIAN_HPP

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/formulas/flattening.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace formula_dispatch
{

template <typename ResultType, typename Geometry, typename Tag = typename tag<Geometry>::type>
struct quarter_meridian
    : not_implemented<Tag>
{};

template <typename ResultType, typename Geometry>
struct quarter_meridian<ResultType, Geometry, srs_spheroid_tag>
{
    //https://en.wikipedia.org/wiki/Meridian_arc#Generalized_series
    //http://www.wolframalpha.com/input/?i=(sum(((2*j-3)!!%2F(2*j)!!)%5E2*n%5E(2*j),j,0,8))
    static inline ResultType apply(Geometry const& geometry)
    {
        //order 8 expansion
        ResultType const C[] =
        {
            1073741824,
            268435456,
            16777216,
            4194304,
            1638400,
            802816,
            451584,
            278784,
            184041
        };

        ResultType const c2 = 2;
        ResultType const c4 = 4;
        ResultType const f = formula::flattening<ResultType>(geometry);
        ResultType const n = f / (c2 - f);
        ResultType const ab4 = (get_radius<0>(geometry)
                                + get_radius<2>(geometry)) / c4;
        return geometry::math::pi<ResultType>() * ab4 *
                 horner_evaluate(n*n, C, C+8) / C[0];
    }

private :
    //TODO: move the following to a more general space to be used by other
    //      classes as well
    /*
        Evaluate the polynomial in x using Horner's method.
    */
    template <typename NT, typename IteratorType>
    static inline NT horner_evaluate(NT x,
                                     IteratorType begin,
                                     IteratorType end)
    {
        NT result(0);
        if (begin == end)
        {
            return result;
        }
        IteratorType it = end;
        do
        {
            result = result * x + *--it;
        }
        while (it != begin);
        return result;
    }
};

} // namespace formula_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Geometry>
ResultType quarter_meridian(Geometry const& geometry)
{
    return formula_dispatch::quarter_meridian<ResultType, Geometry>::apply(geometry);
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_QUARTER_MERIDIAN_HPP

/* quarter_meridian.hpp
TH4UrcEFb8vlZXV1Lvdj2UnCD9O4m9GPG1B2We4BuYXkh4hfbpSjJuceuM7gAeRPzF0MCxd94CtL+77ywY9fQc8pxX8+T2oGzZOCkltOYTZom8A6Ssyj7bPk0TGUR+uTggo4LmB1einlkXkpmZpHlB9Cdv2VzkuYHUVZ7Fh3aGY7trfb0ZPNju3/gR1ivnZeBjsuBDsSwg77UrmMtiRWgS01a2a2ZZnVFtmfZrRl2T+wRYxb0bW5IHu3uQG7hvPF8OMpbku25QBme6hN/YBxPDncPqFjDMrOG8FkvdiWZhncLtq24P1oxHK0SacxrCJnHRj3ttZW0zrgvBecz4C3tvfBWerpgTR5m/wW9eyIabYZejfFNnxrKdoXFH1tM/ArkJ+H8jsIedA/xJBfqJWS/Xcxe8CS4TjPcLO1QeCNiJPD7qnwnkiO0VhtDNkai+xcuJ4I/Qario+U8zZ/X/mf+/1X+8u1aCyYN4Jde3lfYVz34FgxA65vxfko5RFgbQa2EGXmGnMD9A3rTgPVnaHwLwsf0D3s03BcvgHk2+lYdwZbSpKx/ryF8a6n+s30yHvZApRlzYHGTYMfi9cdcP0xXt9G8mLOy+W9wL+L/I143WbE30SR70kmqK7sYPBbIh/fgHk63WuqS8hfAb7Px7+H95jS7z9OxxPlf6ZfN/XjRtkU4DX6jFibgaFfvHwMDGy33DcdUMoTYWupR8H5RzimQfkvPwPL588sZ8lYTsPOZPFfpnIS+rbCfErz+8SwMb8x+C2MNrsGxv+Qy6OFwaiQZ4ZvjHwLv4Zfz+F1pTbEeKbRNejzjCdXwfMMNu6nsd6TL6ZnHF1wPblkI2YXzit5vo/X1ub9e5mYT8p+ftw6MI6dhfnObm5gGeGEWsbJugeoMWdksnLO2I9aIIqSRw3IrzdI318503hmYNQRSMNSR8LDuPTDkOY6cL6D5oQJbivUD2PJIr+xFttdaSVb5jFbxN/SKPOz8HpaDvWzEPqRmwPcicidpXCzjDZ7OnLeHFlXMFHk+4C/BvkDlLgDRn9wBXLjc+geGAJf9am24etQZn/UX4ky6T7RB/iZ3csYPw7yuaWkDsr1Jcik3cHXvH33K8wdOmQo/JNfNkg5ruDxM5Yjy++8sxlfgGPOOvDrO5RvgPuQAignb4kYL56COv00HM/A8Swct0K5bcOe3cF5Uqnsb94qgTPV//qVzCUfXWaeS+4i2wDW7xzG4zMLc535tJwrGs76AjgXUZ256mxbnaHOZeV1hvUrT2L8zynvhL6RxthcpM0y6tPUcxh3CORbY8m65NhLKB8mjD9gvegc3o6UemeU/Sso/4mWqW4xF19H/iPNUjeM+rU76t7cuO95jsro+Wzl86fGgoISbrMsl7Ysc7eh5PjLdM/6APXvxediOch7VVMXb877csr7zTHONdo+oP9COHgZCF3rqX171OjbDb4c/uPlMhqv79EOhn+vhKMC8qaAPZcv58dbw3jevPA35jR4f2v0y8KOySUnsjT5fS/LH77OC56F7pDL1nmdf03hLZttc9RPW51RdOk8/1LYuDy+hOFTvx+zmf+7PQ++bPr8dT9d7XD4UE5HDsMvnbf73E8Ljzp/74vKlj92wbGwgXtXlL/4rPOb9s/P+60hNOmS2NuTgtB3IP7La/cUnbr3vsdMf/m7YGTHTZdDndMYftPT177w8/rT97h/++STD9TdexTYVsrwT4+oPK3qvtgv+6447+b9zht5OfTUeQxPVxz67b47LJ1/4Ng5ZxbXrf4utHW0P/FU30HffrnZw88e1zhi3Dv1d8I4XsTwvDtLwl27VZ299NJr5vw26jFYhLhpPsNfPPadhxv0yFk=
*/