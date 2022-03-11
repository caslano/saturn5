// Boost.Geometry

// Copyright (c) 2017-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DENSIFY_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DENSIFY_HPP


#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/arithmetic/cross_product.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>
#include <boost/geometry/arithmetic/normalize.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/formulas/spherical.hpp>
#include <boost/geometry/formulas/interpolate_point_spherical.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/srs/sphere.hpp>
#include <boost/geometry/strategies/densify.hpp>
#include <boost/geometry/strategies/spherical/get_radius.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace densify
{


/*!
\brief Densification of spherical segment.
\ingroup strategies
\tparam RadiusTypeOrSphere \tparam_radius_or_sphere
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
[link geometry.reference.algorithms.densify.densify_4_with_strategy densify (with strategy)]
}
 */
template
<
    typename RadiusTypeOrSphere = double,
    typename CalculationType = void
>
class spherical
{
public:
    // For consistency with area strategy the radius is set to 1
    inline spherical()
        : m_radius(1.0)
    {}

    template <typename RadiusOrSphere>
    explicit inline spherical(RadiusOrSphere const& radius_or_sphere)
        : m_radius(strategy_detail::get_radius
                    <
                        RadiusOrSphere
                    >::apply(radius_or_sphere))
    {}

    template <typename Point, typename AssignPolicy, typename T>
    inline void apply(Point const& p0, Point const& p1, AssignPolicy & policy, T const& length_threshold) const
    {
        typedef typename AssignPolicy::point_type out_point_t;
        typedef typename select_most_precise
            <
                typename coordinate_type<Point>::type,
                typename coordinate_type<out_point_t>::type,
                CalculationType
            >::type calc_t;

        calc_t angle01;

        formula::interpolate_point_spherical<calc_t> formula;
        formula.compute_angle(p0, p1, angle01);

        BOOST_GEOMETRY_ASSERT(length_threshold > T(0));

        signed_size_type n = signed_size_type(angle01 * m_radius / length_threshold);
        if (n <= 0)
            return;

        formula.compute_axis(p0, angle01);

        calc_t step = angle01 / (n + 1);

        calc_t a = step;
        for (signed_size_type i = 0 ; i < n ; ++i, a += step)
        {
            out_point_t p;
            formula.compute_point(a, p);

            geometry::detail::conversion::point_to_point
                <
                    Point, out_point_t,
                    2, dimension<out_point_t>::value
                >::apply(p0, p);

            policy.apply(p);
        }
    }

private:
    typename strategy_detail::get_radius
        <
            RadiusTypeOrSphere
        >::type m_radius;
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <>
struct default_strategy<spherical_equatorial_tag>
{
    typedef strategy::densify::spherical<> type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::densify


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DENSIFY_HPP

/* densify.hpp
xBYYdtlarEozbztAYuPxRcVGcKRioHWYYCSAN64LnVIY/+LbUhiPaaHzoL64/SIE9KZ8snodrWEJmJLocCfbnqKlLMlXy1W0D1mU1OlzlqoKePthfWEL18tnayHzoU3txibBWAcXTreqhFZBUYQ8Pgy/OfZonPNjlUIM5fFPI+7bUgoHk0kOKONq8Wwc8Ou71ZF30kf+2NKJBfD5wQV8SvMtKozJgX/Bvk+IFW417Eqs/BcwntM8Gb9vLmzKTuFGVMcJreUdt3FDzKS1Ly0G1uScqlTSkZxj4/i8pupeE76xnYR2Pq9evdOVnv2AkksvLwUEHV5eqr7NNsRRq8knn7GL6513KbW8sV6tRQLl2bdxcGP16cYmwVandvP2WtcQKosK6J6PR75bSapXwUqKcXlYbWuw7Qe1/bBVaSF/jBOfBRZ9ViL7WFUDrnjTBYPxg4npvPxcfgLFRBGwZ9M8BveVNu7GZJtrc76wJ32P2ngg30xqx8hFUmcj7I0nnX3gqYAagDa4RuULxkZBIXVe6u88mnX+FjqrW6HrnpjUnAIhFqR/AERczM/2CZn6wrrEio8wpLbXC3DHh9L3zRB6ohzU+2aYSe+4Tl+6vQkIqi8K9jrXKMFYCzfmGw/DKWG04f7Rdl2ioxXBaAUib/ohtkP6wt22qYL9MMrNYiZto+ULlmBp0fvu/qQUmtP8dPADVVS1fqBq8Eu8/xcslKa+CDYIJhExZNrUVYNzqgaL+oXFHkefRREPwgak0AOVdRC2CcaT8tz8qhXnpunF57kn5sycO5eTNgcoYdtQWfjCtqpC3B6jH9ZG1ZUlg6Ur6+Fwa3CXbp8Sd7QxtrpGkbSl1KxXtMpm/dQ7LO/6CTzBSdkpNg9qnWaPIhVPzpmtd802O43LYM590avTx9uWCeO4aVtKcfJd4NKdOVjh9PDODq2Q4JyUC+2nhuw8FZM9q7fGFjNtCngSjeDOvz5JiRV1x2QBQDrG4vf9e56q1YIyF/PG/eAHWJX5pEOL0QFvPADKV6HDWZMpGA84p8CkzNTQ4mdlesHoFg47Gofs7NTubIxRa97CEavzNe1f6mxxVb0BfGJd2qprHYk+n9F9Bz5Km3v+fiCTXejjRgKtrCPOuzI1jstqu0a47FJb1UWGY/YEuCLOdyfu8+Rq2mtsQ60m3sUoJ3z1GW4+30QLo7RZlSY4asW0WL8EukU0w1UfqKabPEngmcEd97CQQ4sxTfuAwx6nssWYyPh1YIvHYW1VfWGcbZAVzMxJtt0zq3oOJxokV9jiioFrNLZYbDvqUguFJ32AOEeFXa5e5PA5aQrC46Iv7kqVsrKOGPbb+pE/n5Mfas+3xTRydm/uF8GYYPiSa8zWcSdn4p6DM8h7ysAiXML9cdBceQRIPO0nsf8tkUT5BAV3BmxA5ddcQ7lewR0X4kBUlV/bLvoykdxMMjWYnFjdOtVPq0ympUdatIZXQ3k20GL8nFNhGbku1zf+Kl9/e6TrBR2yc0RiZwbZqgpkh3q3RwzngeJCP8WWN9nb76nZySCgvATDfq5RUIKYjoOYjs4EEJnHdr2a7a/9j0n7fuRuP5H1jMjXu2g5sJ9xL0ejOx8Lg7MELtnoRmcwCYsAHjPTwo5ezCGryO1Y6NPmBQct60wnHLlJ+hmsjpNC9yuQCmRikT/e7qX57SMt8rCZbNjmGBB7+X8puNNMICcFfDvjKIrl/0xm6ywLebpTobBmYL2cRztF4LeVVLbb/ts6wULe1XrFRKlttoXM7gnY/Iwai1HOhThdqMekc6G38kRixXL0u1Nx5dVEXCOlEntJFjgdNko61TqfV7mSpQp6E5eqcDFAY9jzAhhZR16bz3qLmfzQwYoFcqOstOrfuwd81H9PrDxIP4RmOW8veV3Kebc1bxELBP49AdnTInuHlcheFvYwNNCCiLj/1C7oBQzdO1LG3UXipRUJCO0T1WQRmDKwOBcBCNUX9hrdU4q2lGJhzUyzhfT1X5ftw/CDeL9hzIGDMcetednungjd5w92fUumuPCJ6YQ8BAI+zkROXpL4NZHHm2AQe1yB3u5FJPcSUxNF8rZms/R9UfMPl8Ut2q3Sa0paRaDGYtFHVrIYUN3gAZ37/qz88LOWQBR2A2h49hDuF/r51gXosNnfoQ920KBDAm4V9zN4Hj+Rt85SlvkUuNVVjFvyMrQ5slWJlfsxdw7aUqX2io9jm5LqDXlBblmnpAPGly9QTgBPF4uijwCNcMIt55PklZIz1hecscTKF3G7K+qQjV2sUugL2xIrOKSopPEZSVSwDD1v82Kq5160B4Vt1eqKWs7knKbk89wTDdzdzh0q+AHE+Pzt9I0B1ya2J8JA52QlqvgIvd39/LDqa4T7vT4j/OeuihfqwVzCSbUaTidXKZGk7TPBjh9mGC6/oJxeHQtjTpxl62WdZSbTL6I2Gtwu1cQMbkBJGtwO5c9M8m6WleFdmoe6Ix7FFwcYPz4encht2A+vTXRUsE/4wanoL11l+wMZ3tzpfw/NTEZ6mch7NVORcwYc/1oVCtfQyvWyZpjJNeKZ7VZnmRKfRqeSNrjxZwtpEc9s/csNCq7PZPr2gDjbmt/CNx7I2Z9A0bJOgLhR8drIcTyfXYTfwX7tL1po6/+yXYcLQwuupRMuztcvhVYacECzTQvsus4GL+boegfUJoDzpN50cSe20DccbZ/cGUBUtEM3ElkZK98IskO6ADuky5+Bqv+RMrjsYwLF/qZfZBJ3vhGM/boA7NcFYb9I0RKS4hI/xdaFESgyGl5VsEVjNKb5adQsvEqudqsCuaI1XZlR6jgjE7Uwoq5hzCjpuhklJFRKsUIXaJcS0C5t8tNJXCjbJR21Swl+u4S7zpKU8yHsEkWitb9Jhml5AzNMSxpCGqYEyTDp/eO+42SGqYffMOlCGqbvLkiG6esL3QyTwucJMExfxciG6ainM8gwrQwwTDNvCDJM1TeENkyrXw9lmO66IBqmTGaYFHskw1RHpzfbqRdNN6mitkmHtmmbaGCGxci2aSzlMIxt+vNwGVaWipcSrWib2pqCbdMDAbZpnv+6ccw2PfxVF9s0FW3T9WCbaprwoSVR26QD24Qsf39JYhki5B/QPCX4zdPmH0TzZJLN07FA86QLslD+ipw68DnwG/SsdtADw17Qg9FNsh68ITA9GA86j0/9NL59YGjgrhHUhr2cFpqgv9Lfv0jsH4N1yZtPoyhAEKThNL0ZPtskMmGX74QmBDegNfnbadGMLadGC72uv3s94uN71W+ovJZ8MudtZqj2iobqD1hImX7yK1Sr0NawlyOtyi8Q4E3kiY5OqomGi4kVBiSlRvuAYhvwjkip+RrUddxa5zpqO5I1oAzzM33VsQVgaIYg0J9pZcaCG0mNjMlMWobRJ+oaAJanv9R4bJj8mHdSq/ONGm8f313eqaapiwKDJ9GxiapOAlywbliQr0M2nqLiokZHR6EizxsgL9tLZOEpZn+MZFAlXJvdj1miNzyeAEv0snhmu0e0RM+wBtESPSqe2dIlabhZtLE7Abeb5I1urm+zK8A6fYDHPtIHxtZn2+JJDzgA/eTjDBfxPZmsE6CAsjoOP8HU8aEiP9okoZ6VZEtPEfQtq518+Kb0KGkCKJ49xt1VdL8pcAP4vBbQyusMhxIrsFSyZQZJ/xITohd/LBjQXpDjeta019iqu3FjKQiHt7sNh0Aoc8FiCimkBP7w2RYWmrVYSCzN6OoArKbBL7g5ioZPcWWgIOOJAZuye9pSyWi8LMXizGvZlgm8zsi38MYW8q1XvPghvL2c43B7RRRKF2U8phB3Wi5McHh83HMOz2VujtnqM7HQELCrL8YzJhYc4ssrwgXXWGEcjTiPOtwxMIm2N+Ikwo1VyD0OTJfFYBqmh+9oPrnXgfnugxCyJ5jYxh5sMzst7lgVBzxASGmXL0c3obBrQDm7UZ6i218T7V2xvjeNwMAqNRTrddxxMaRcHS6kvNZPZJ5MxAEx5c8spvyx2AEmtL5bUDkzZFD5TYNM7SY/NT1So0EQUAPAqWc8XQwVVvJ+Cr+8GpFCt8ByR7jAcpyf5lJG0zW0WJ9Mw2Yw4g3UiP8DxVUXKbQ896NMZuqrVwgt6+K8oUPLOxO8ogWvP8Ys+OFj3S04LW+LZhSUaJ5/2O8rGRJjaapiB7iap5hQTlAT/j0VzSGzxTrLRJ4DcLRmmGCcko5OX5ANN5F/NXbKNtxEfr3IbLjKTPq0df67tmePi6rKf2YYYITBAUHFJKW0srS0MAUHE81BemBT6IyoaOVm0+zm816lTRQd5hfX27RtaZk9NqvddX1lqemWIYiBpKuQpqxgjjnbHppKS0ME4v6+33PuvfMAtP2jPn3kzj2Pe873/f2e7zmHXhzPzAfZucxCHW4nptZWRYfnwc8Z6s9Iz1J9QIefKelKh59rkReDZOcSB8WUQF2Ic7k64FwqCnzyZabAYXiLL7bSe6NQtLRRBU6PcUcFbifzr7SGK/BEbKqflI/qagTq1mTRcmFotcC31LXcamkpc4BilkZR9FwgwwPtR6Ait5NKZdBxrh/0Kztmohrv7z9C/tMo+2swaDs5qfqXdqI/AR8pAP+yQJaYF78MUuDsRqdT/4N/2U79S75RpYBjLnAfyxH9GQO5b1QHMy9Q4wOs8aZWcTDnZiRzXpLWGPAw18ke5sBGWTU/LnuYDV8pOLHKHmaN+uYe+ZOxc10rdOBj4qXCjgeZ0Acfc62XKjvVxzSpPmbtKvQxQXXHYJ86WXVv+pERoNjhbjaVnMFQcW67v99cV4uZG+B5Bf1jc+tiPHDZVa1zVehMu9HxnAvE1kjzDD2TOswdS3VitWm3RuzAhNEUvNCgryOHaeuyyyou11Nt3eNn6iMCkkgHJgfki7mXIg7S0ZgPLZ4ORdCqVGnFO4i2IcRHnCP7iN+eYjq6f3CeKvzI1qm/4kQYKUgsk/teTKslF47Jnp9MEt5jQZ6fooaPK0QR8NNWnFJxenplqHiPDxbvsgfzbFS71NmvGhPoZN3KMHEaHyxOu/SKbumyz2/+rfY58ep9sl7ujpbvxQvp5e1ALx3F//PIJoaMLMhfuy/Q7d9Zt/6bZFkf31nWY1cTImlXswpCLRpHqEWz4zSj8FCL5qcV3Vs0bpSloRaNb3iIRfNmPbVoXqkPtWg+0LfLFs2y+k4WzVP1ikUzu161aKYFLJqhke1BFg1XF7BoXnxxuGaOkueI2tH0URS9nXPMZtm/ii1ertVwIGmn+fFU8llBmpQe2JLgYkGeq9ejfX6zCfrMxspRYH5z2mx6l3TwSSlJ5K2TKqral9MLpvrSz2xa1SZ13ZQqYj3GNAKuz5JjVHhGWAzqdYxySY0kBdGdDY11vC6rdYs83QErO14GXC3ts7JjBfxdbFj5wwa0z6JW/oBbmgKfZVdMfIRHk+SH92ZXejOtrNpAbybEvhYFj5o1/yy4OTs/JYm8fkIFwZUiBAGUZxld3viweosD9eqC66UWYEL09ru2FxIRoIm31/rSymFg4BOtLaeOX3qg6StFzHzYQkXiq4vwkPai9uZsYxY/30YOLKIZGBLX39XSwfURaytaI8WDrrMDK85GRRjpYo4/8p+1ll2FzeMHr+Bvxar9sGqSeLDiSiQu/OCqj4dV3EMrZg0u5pLIri/VISTiEHJ9UkaRj+8nTdYXxog9TR9p8cp68DYurschBZKpjXIy9SWYQyUF96aFcu52d/nU79wl51ODjSvdj/3H0P5jCiofIS9j/wWVZBw4DVayH6+bqfT/6ExypI8ECN7HlLfYJhT40mrM/+ZTMnKNXF/SfFwd/pRl9ESZH2m+O5Sa3iw3V3CnEeTx5h8R5BXcUWx1SsDRjlwoZ4wrMH504W8F44cDg3z/WYDxEz6Nq8in4cZIMJq7OkFaeI1C2oueZwwYGfHYwB9XGj1JKGrMjOFrqqI14ViY96WChcELOp0nczgMD0NG0vz5cgTsBRgbXq5rAAABOfcl7x1TB6uDwe7BJv5hyCW6BWqOvYHM/x6kl2l3eRBFoDM0FwdzFvrEXRhk3Xw6lu7oYddImR4K6PGkZGIkov5xSUa90dFyN4xw8vEg5jEGmKftC3Wg+X9kzLOTMs/0+aHM89z83wqxhYEhnHgmwDw3IEp7ij1XWwylWtNH5VKUP5aqs4d2s5XaTkz0/jGKPjBmnpgX2ADRHdz+C2BxxjtSR+P+h2Mh+EsmvrpA/PcZBpbPKEvQs5hoLe5U8yQAzWw7+cO8/wk07/xK0JjcPOZAwIzH/3RFgvnayWdP49SReuxk51EMU9ol3scu513c0AaVvHawDY+iJk9RwNObDTzXl5HrNa0pzyHPfYFwKgLLfuzTneFUGwYn02iZvsi3Oui3PJVek/3eL0HCvsD/lUyBEde1MyuPfBpU+ft+7Z0rgxO4YQTMOC+tAa0bvDW94JJQ0CIUXPBrs4vvSeVaV0dlPsYNy1zE3Zi5FMTUQ7UqUrYupWJqHJjRn2gjgLdiXbntWn+PTzD0C4+6tJrx2auj7CXlppIKzN56ZsXHmiyNxl1jKsFj5Uxl5a6WPNOf0I/iVrhIqqmkGX0UEss9ksPd6yLJ3O0uEsPd4CJ6k1vAlSBLi8l9WIO5Ji2Ya+I6FN9UCX9jzzTthT/NlVkm91b6PqtpM612Aas1vUYLdSxGJlraXec6XN521yFdbDVMuamYXojdouE5td9U/zwXmcJNd5GenCWHG4GD6u0iUSY33vJ9uVJTrtHwlthT/kmuoksa3rzyiXZpnyRVWy7RHJg76dubekxtV94MlNskrDyEG1j8pj2aeABFPafHu7Zj67PxrmyT24ueadEFDR/V9ALmDlEUOCNsjpQxwCInPqdWCHDHcldVhIKh4nvG8vPkmpGO1DG4d8V2VKkZ66qKhG9q9Br/OKfBMYQWjw4uNmCxTuNPdUY7RtLiZLW4j6sqGou1msDXNFwvknNEJYO/8dA2xVGspR62x2LEgLOVjM6St6rSMxZSREsS2q85xrQaIUcvGIQc+D8Fw1A58eyWtDlzFmumTsm+PR33K8HfO0c9aKF7lybfd+9DEy0aGLwXgWA4inICXFdZBvCJ5ON/tcpHMvbj6ZGMc+1kgFM5zu5J41E7edApy4c77CSLPXdwN9rJSHiuaIn0jHQj59vJYCflbiYOomRJYCrL0Ref/aU0R6/wcyzlZ1JxhHKxwU6WPoVcrPBrfRj/fjlG1Q8YvoepFGbCVMYeoVNBX0VRWucPq4DN5Sh/oROM+yhbOvg4UkuLcfuX3+cuLzSYIzERZ1Ec2R0oqKLCj01BTKKiz1Q2UadPkyYNquYj/MfGF2cgY2uBsQ3A2H0yl/LPOXUzxMtpX9ww1Rh7PUoE/xzxjP97dzP3BLIpSeXykAXGushoLiGHuwV/JFF+uB/tX1x9ukkoMvpvBw8qRTy58hxyg38g/OoJvw4h2/sTShqe0dNLHc+1rzyETDd+tbaknIvwr2MjSitP14JwxDxK3EVLPlyB0lWgVw7Fky8P4QzxhvGmb5BLALXCLExKFLLjg9EiVpHb/qUoIe+TIXo7HC9/yJTxIgffFh5SoX90kewuqnceTQkUfsgK/f1Rsu4BcyFfPChEDfoc3gk2vfkgp2PHMYLVPBbwPBWQg4EWH6VbcxsqfjxwVRfo8dFF1Dd5hpkGF2kN7iuAyAD2eIy8txx1iwEaxpGazxVY+D8XCtrTB4KntutzpTNnB6asOTB3k5y6cIUuM7yLMUObHReb2HJAp72EPx+SbZ0tc695jt+Gscp+wizZDUoIdYOY95VIUj9XOHPFQsqZgx3FaiiONMpxuChZSkSTCzW48MNAlz4OQHfdoa5Al0yqa1TQ3bQw2DjIKDAyiDUKyJd9cTIAImonzLeTiXN/KxPq7sCIXl4gm1AFPn6QnbxQjXSMUYU8GstLLNVq0JSwkXXVIVaCggrn5zIqbnji6vs6h42T8eCxJFkD3mqPu4IX6kLL4sLK4q2qK/vTnd03a76z22YNIUXKSqnRSc2m+m9psjpulHwRcFqbBTjNrpEleFqDgtBE0lytUMrU+ZRSsoSBVDaaDzF8nkbcxrPnOmSTJIVNKtP7AUXsqlbhv6kaqYgMgu9UCrzPRhJ+J1NBttGFC04uFAvCLIMwAESIMEtvo/eeUZr0NTMGiVaQghuhMwZym4A+t6Y1wKjxRu3SOVf1B8qzZLw8jGIKmQQUo7y8biUo3NAKOZAkx+JlnkgKgLuOckYS5YMREwBmvQ527Tvsq1Jnff08xgcfMj4oorCq5hptpNecUD9i3JzfiglGBIbzwtMBPyJRuVcu3iZNNYTKH8Vz4KsVoT30cUUAdQffGyaodB8gRMeg3R8UkkMK5DoTMauwKaxCUAd/0m4plBcHuu6AVngqpAKKOjHbaN/o4p4Ri5LcuBNQ0nKRLknHO1ze8wKQnKTlTTaSDYpcazHmJ0yNT5NsxA2zhIb5JeXPGMAahXr+Phu1XK+NBq7nP3AnCB9dnZ0MhpnGzgYA/t9jABgrOTtBpxm0H6CIeDEBXfYkew60Bp3gzuTnhXuBbk59FuJV9SYvHAjkP/6eabEJwEug6WNcHTjuDh1/Cknw9KOyAWULkGWM1J322P2ZLLLmPfor9r2fuTdU716pDOS//F7Wu2zRyQfIWaCXRmDXQ9jXZcDvSY3HEyNS2qSwbUwgV2c9SvMDy/OFN8l5ScrI1hdFCNl6p9ZqzSPvjEfLNF5sET79DgqFtRfgX/cXK+KX6d3S4hj4eGxt03FMnqtEy1BPLUPXuYGC2wcVRU3FuaiIytU5g3U1tVcuZxtxmazU0wZFfF8xWy96sLvXhrb0/1ysFuuaROyop2gzileGLjcIn16C0ub9EaaSGZg08Cm205rcmDiQ9kWGdYSpBFc16s4Ln3px4DY9nyC6cZgiHWZTJnT3iLRgmLRgiLQL50aOgaEtXhDlweHEWs1c8hCTOw3AZV6WPMzkvhVtTo3Hg99+2IGOh8fTjs/SyGSpd0oC27sSQWtJu/A70q7v6L/0CwupKR8PIOppev40PTnHtOpLFGK0R/FNHKr536bnKjpw7xb27G7gRnvWxOHjA+b9i4euNhRfieMTPfdL5orFyZ4cbXFGDB8vVviNpo9qTGXCtMd3FUZUZLkb+Fo2tKE=
*/