// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2020 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_LINE_LINE_INTERSECTION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_LINE_LINE_INTERSECTION_HPP

#include <boost/geometry/algorithms/detail/make/make.hpp>
#include <boost/geometry/arithmetic/infinite_line_functions.hpp>
#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{

struct line_line_intersection
{
    template <typename Point>
    static Point between_point(Point const& a, Point const& b)
    {
        Point result;
        geometry::set<0>(result, (geometry::get<0>(a) + geometry::get<0>(b)) / 2.0);
        geometry::set<1>(result, (geometry::get<1>(a) + geometry::get<1>(b)) / 2.0);
        return result;
    }

    template <typename Point>
    static bool
    apply(Point const& pi, Point const& pj, Point const& qi, Point const& qj,
          Point const& vertex, bool equidistant, Point& ip)
    {
        // Calculates ip (below) by either intersecting p (pi, pj)
        // with q (qi, qj) or by taking a point between pj and qi (b) and
        // intersecting r (b, v), where v is the original vertex, with p (or q).
        // The reason for dual approach: p might be nearly collinear with q,
        // and in that case the intersection points can lose precision
        // (or be plainly wrong).
        // Therefore it takes the most precise option (this is usually p, r)
        //
        //             /qj                     |
        //            /                        |
        //           /      /                  |
        //          /      /                   |
        //         /      /                    |
        //        /qi    /                     |
        //              /                      |
        //   ip *  + b * v                     |
        //              \                      |
        //        \pj    \                     |
        //         \      \                    |
        //          \      \                   |
        //           \      \                  |
        //            \pi    \                 |
        //
        // If generated sides along the segments can have an adapted distance,
        // in a custom strategy, then the calculation of the point in between
        // might be incorrect and the optimization is not used.

        using ct = typename coordinate_type<Point>::type;

        auto const p = detail::make::make_infinite_line<ct>(pi, pj);
        auto const q = detail::make::make_infinite_line<ct>(qi, qj);

        using line = decltype(p);
        using arithmetic::determinant;
        using arithmetic::assign_intersection_point;

        // The denominator is the determinant of (a,b) values of lines p q
        // | pa pa |
        // | qb qb |
        auto const denominator_pq = determinant<line, &line::a, &line::b>(p, q);
        constexpr decltype(denominator_pq) const zero = 0;

        if (equidistant)
        {
            auto const between = between_point(pj, qi);
            auto const r = detail::make::make_infinite_line<ct>(vertex, between);
            auto const denominator_pr = determinant<line, &line::a, &line::b>(p, r);

            if (math::equals(denominator_pq, zero)
                && math::equals(denominator_pr, zero))
            {
                // Degenerate case (for example when length results in <inf>)
                return false;
            }

            ip = geometry::math::abs(denominator_pq) > geometry::math::abs(denominator_pr)
                 ? assign_intersection_point<Point>(p, q, denominator_pq)
                 : assign_intersection_point<Point>(p, r, denominator_pr);
        }
        else
        {
            if (math::equals(denominator_pq, zero))
            {
                return false;
            }
            ip = assign_intersection_point<Point>(p, q, denominator_pq);
        }

        return true;
    }
};


}} // namespace detail::buffer
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_LINE_LINE_INTERSECTION_HPP

/* line_line_intersection.hpp
T4XkduOPmwIv9UcFO07EMcPDMaxR5FVEt1v6f/Yg4LO8FdYA1syt24QfD3Kzomdmil4qBVdNAP5H0cWAegDDuK/GkOjTTRXrnY2XZ88FWZUwM5kDG7KztbuIR6d1EYb02LMawv7bNLur6DUQm2ViFP9aENToX8nPURAMY0d0wuxWTkLUGRjNMZLtt4ULVB4u031uve7gYG9pA/+olNCMFodZBcdDbMtsT0KJgYwFQwRhykTxLm9CSntgMJg0J7lI7maEMCEsxo84rRH4OmTy2nWyWgjizBPwOt2o6TQWM1FxBgLmsemGh0YY/N8EknGnrvoqngtGISN3tYxDs8QhduyOO4cpGyPS61qFX6SyzpH3SXrSt3qTVDGTAorD41GRkQiWep3+/WTnopk+711nFZgnITak5u3i/cnEO0VUhX8W1hq32gmcpdf5iMuuxd9IKWWaQ7nDRtUpxz/iZ4NlXZgdYVpAeWiEjxkGz9fKD73jh7GCw17A+vIPPwW3rOrAYY+NleVW5vhCHzOC9KzJkJnqJZRVsHHtAsoq1MjpNMw3DNvpP9B2eNWDhup17gvnw0/RQ4UloHLi8Tl2bAQ67JvNruRzdq/MnLrTj2ekU1/T/Kg1NN9GKCtE20fIZRfix2jhH4/SYxUc+zEB/5EM/3HPiuy2AUHGe/NF2VnuIbgulSxQ3THKB3PSdlGAqhhybxyYnipZnkxQeopQ3oX+i1ZAwXPhgHrPiUVZItcDi8Fi7OmhKYcMktlFzJyARlwG5DRKXcyYYj12dcxSle9quEfyyPgrfCJ8PB5q0Ry6NRo0WY3h+G7CctxUzWMPiWsnmWs4WY2dRigyCvkkwuxaNbk4tdFRzL7QjwtDQwUNaZyjID3bRVpmWs1sk2Ib2+8SXAQ4gUT6w2ZgjPPop1+JTP82GqR4jsSaSyjqoypEmW1tokWtVZmmB4J/syR+dYsmTNOZhB0hGJZRsOHiLsU47C8Fnm/DX+7o+i7joh3u/XKcydvK4rQ6muLndOuFWc03b4U/b9zWMplKMdU9c65t4Bf15OOZfAnMuyzkYnzxQ8gxAv71OHoLwTrgbOxZ/yR4a/weFMuK/CNC7Irc9AUJJzB1HMn3U/JNmALczbC40OSTmRn861vIpoz4M6LFP4z+937eTf5zcA7O4JL2RBOme4DwYpxQqaHkec5VYMap1b9Geu2W53z7k88+AnPhgg1fQxzm7t2IZqV5OVT5F2Fj71jRbQKEsHzPjUeWcopWQfrkpo7eGQwW/PbbTLTSQostn9fQro11x1MzJjSEEircRNSVOBaJyTk0WcSgeAPhrJYCX2w/db+RLUKy8kSQz8ETTx0nmxS5Nd2yY73BDD5IZ2FOksMcHlQI8cFbh/VCbfG9bujnvN6N6RzbsB7flI/dp2T/vNqQJbu5Heb48suV2riSxC9OJgmG2AzYl/5t9+VHSC5QiOeU9eWHtcoOPtTJKk8HjXI5GPsCke7VVcTQGZ9gL/K7z8YPGPWh9ocxoSQuc4vDXN0kN1rNJH5MtvxFC9LS8fwUL5ub61IfWrWKuhf6/lJtudnWgaEbdCRIvEqHq2maFcfQAkOqWXVt1QijWKdXWVqXha68+FpkoMDcXQeGxyguQJBUvySh+W31q+QSHrdqTi8rzsq/SzJK3Pfm1vS04/P3Cs1XCO+Z99BruK8qoGhYnCUVKo2W886quRSfB7huz0G8IibawVDbTgBikB32LvVukdz2FNJ2oXgA567ff403ruf+cGlOgPxIX0wHr+llZheArsEBljE3uaDSM89o9eu7ukpQroVVZjzjDAbAw/NXJ6eTNLYirEV45BXVteN0dKEXlFkcqL5n6Hhpefg8crKjdRY4r9O7Wmd9IyGyj8H/yeGdr3ht1hgn+MPm60etNohV4xquTaAdkHwzJOZ14jn+MSMPoYDEomIYWtuUZWvdga69NxdJI8alu4p50D+EDjU3QGe115ugbVyjiWD71kDTStHwew71it8fsQ25wtaLzWR6S1NLy9WrYU5Qtws+o9P/t3zA1903I6ALGlU0URlVRVTKfx4+xyl1melI8qp+MnydRbG1x0cQdF2jGXC8Msz4TJNnmR3s1Ps5mc/KOB9bAzkfO1WFVQrtuBrlKsRlhqUYkFQu/enYvgOx5VWbPdLNMzqMIbcR0dG0jx/cSXmSBwzFOFZoMWeb0cWfgHbmn5It6P+BmVNIHOL3gwkw3s9VBH9FyOV8ZnKZudwjHnSZUQN8bapRUrnX3VuUdin7s0L2Az4t+Kjg671tQvhq23bldkZ7z7z/W3uVy/logTK4R4F341KMivhyUuGfLVguZResvMMRir1gNf8kH/z02hf4pTtAzfT97Wzp3g50rE0u7sSRL99qE6Gl+TE8DNS4guBKtBI95rzDK/17NuAi+/+W2XCGWxwxJXF8YNIkf3z9hbne9W0/fIo65dev5ChObKyvpOG/fsuMhTI5ixmodFGW/6Evgi2ivM4/j+lHGkuvRf+KBwMP++ULbPQ3QSHWCWhVp5Vvev7X+U8Zdj25dZ0zFRWVtS92/MvHGncQRWGv0ytsLvlnPYiwxilLgJ/mf+SaAdY4ss+p+q7ndNBBkkB68O4CAUB5P394zCWyWpev/hzj8ZR0zwgonZ5P2rqCfchMTkq7JFxSAkAQdnLlsmt9nCLJn2LmRkcuWIqOZDq7jo/9ex7qiAsAGx4+F39ZDma30DzuCjwBSrsCQCeMwXqD/uPjJamPaPeZQQ/B6NrIOzfKmrtJN0D89HZMIA1DyqvyZqxlP0kKI5ey6lHCElz/naC499OP+5Tas7db83/+rAOCGLhJ20RgGfY1BeGnHq0pUTOsrfZbQu03kfG0Vd6Zi9OrmUnCcxB8WByhD9RwncdLq0NwdG/iFDQjnnuy6/z2p/r+GzoAn0iqA533UNcgRPjZR49vJWURWBKeVp3ql8MoPJhGmBESI8g4m5mSQOnWQ0M1eTGBdIzoBru4uL8mnFUJEzeCEpvQMC7NNvbc6Sb8zG9zu+O6pA+vwTwgom8xVgT7a5VkdWS20Rz5gP+ncgtGwxFMwyUd97rlGJFUInNIdcDndfexfbhfxzM2DezmTZwJPwN5SRrSMSey5o3XTWaJsZ/5FycT+X/mc/67FIg4yPlKY8sjZTF2lkZRpSWlOxOP7pgQi7BxBSAjffbyEj2kIWshw7g0LvhG8oTWWiPcNTSZ7FpGgOP0+SnvLOxOMLgXyyZ3XnbVpShS5LNuTpT7tSyrZi11ck0yAZ7TgEeRqNH3BK+WSIQ8NOWrjI8IpfsqLFaEG+/XOoGKDyFFZYabeE/IgtTWqggpmROct+IM/Q3tN7JRvRl+6L3cbMUzpVEaMJr+ofXam/W318eVXFdBp0/F4DMlkYuI0E7Cbju86jj+jaUmrs1lXP8DVhvP7g1TZGt1tgw50MCzy63CaD8zc01sKQDdWFhZuksx7h6kacOk9tO8xF8Ysw64TSm5l72k8XdPcRB0ZVPZDOSIvXO4RB2VzRd4rxPLjYJE/gAstcQadQvpnrV+eTMV9/S0lMqO0W8oB1LN/dra/ALn1CTP444ZDCjjWAY+nZ9Ve0ZMAAIs/dPjOPyT0Efdrh5HJwdmn2goXOTyNM6PiSNEMMzYgvFMUhBrlTPtvXSwp7YVgxq83Qy64A+uhxsyL9DL1k3lvigNWkc3bygo+XVxD+OnSLvSZmKlWAgSlTxtfXgZwDxoOiCR1ki+vBQMb2S+OsJYVDW8OwRbDCeiaV6gSO/gM+l/1m0uHwPrC3cOTMwX1Rru5bAX1ea7fJddWsa4TZE0hJr8jC6vIpfwwPe4QEMUYj7bgCOTw/W4uOVQUep2U8LrYTnbIH5//1v++n5ybq26Wuc0p6MK6bRjVcCi2tBe6aLdMnKCShfVCpsfjxfVBuwbqksadk6W9a/eZYjyay81o+iEPy40Ir6h+3dDfIjzsTwurmZQ8Txmb8o//PlEj+bIzhywJpdmBXrLcq8w+VjGgLv3nP7HFeHX2YnXEgApPVFxvWxB3owcXRMK22lX7waPp/n8d6ih7mn725sGIPnLx7VsB9tnu1YKcTE4+CB8LHyKOHNWuAPMz5eLfE1lGUfNOKf9WpTTiBefuD9f6UgnGQXoMLUCvAeL9yXBEaKEw4xnXVVb/qraokL31fTgiJg5uloc6HW/37C8Z8+ZcxmBqqj9Q6lMJzte2FnE8a2EgJACA9UqhrooPvTYMGBZ9z9fOit+fyZdes46GyV1Rf2rUmTW/0DIsU/5G2WYESLvoRJJCEx4Njr5J6MfKAUm/lCdvz/KqUyzZfQbJV9sg2WMi0TOepkWLMsaSr+mxyy1Dfo61FTeGuviTWWszir72fAfjQRuEzfE62rJkBKuCE6i2FCWGUvoMcD0/kHaDUSpPof1WGueTyCOF9RGSQIMPsiybsC4A3mSLB3xbd6UqtO+5SDcBseL8YgPkwb2+F5ITgiXpPY3FiVuxIThwOsF4Hj3v1hPO86LavmX5N9MX2HUMFN7mVLUqC9mN2G4TWNQOjB+/0v1KmmL9j6oL1FpSLlgXiXxUhumhk626nUJIZae09bGW8AzIB9w6wl93dr/+UJkc9cVHoXsSRfU+1UDdgOlsrUw0Qh2WTS8HtF8+09cmGu7Vq6E367ukf33+wLt/ps565QFxF5JH/6ARSXqQZYkz+DSFmwoX0Vv0Rzwyq56/vyq0vE76q12Zcyx96dU1I041+PzlTO3AdO/KFjXb8ti6nMzIf88Jwimvv/NQ9PxcxjSrMuThv5NYzzuC9v02dkYiLwwcC0/93xsqV3zNArYT2i9wwdGNVU1L8z0cL5PbM7k3m+sW9kRbszIWh+rOnyvzZs8m80oyrsSKno8bsmoy4tR7ZG58F8NyCjNYxStiT1t/DlyL6nM8MZM8WZ/zflPCmWOFQqEVnFK3i1vhLaDNgqz839NezK+/CqVfmz9PtIRD1bVFu757t3TpuP/fBQTPaJNr+QKchV61jn3ytcTe9XI8914Nqm+7iXtG0W/Xgxz9veHud0zFzwbi0g4K++Uedq1mxXz93dlTjkmVAoCdJKQ291xkbWq56hmzfd9j9UK9n/yPg7MJKFD81DHE8muVv+F+DXQhluqbnvKGvGk9SzWMh1ngSot9VhebfFuL8R4MUmqkZgADaYGnrt6wv0mCeUdSyWNmNBQO+T5hh3vGeO1I5Es2sy13ZJytn1XF/NY8/rnDTvMG/RP+yQKtOU16Okk3Hf3yRv2+b56ZuC6/pS2tFtZExKLM7jWF0AdUYW/wQvwhWFGXlNHsw98/RPb1dQTPEfmomdUN1ShmQGfN2xcl5HR8duqV5iA3JjLrOlIScpcn2MD2bcLt3iC+euIB6tMB4bDev74rAcILrbnZKxcnVPKQ4Cd/wIrI0Ng5VeqYaP9lmLYm5nzaL2m0Ra3tzEycUY+PRMT/uXMTmnTcB0BK9HWwIHLKRs9OjQbNOMS8+jfw/F0yX/51HbPV85L726gpx6Txs9yuD1xYn5wRZwRX8eS6uJV+KAYsTGVwK/voHXpEtVK3P7OeYxde6xKWipYsFQ1OHCEje2tfebP0Yz+Kn+UcnSin3SUks5iYcix2he8QgNjrmTspSdajFguMyMHggRP7V31WVqDU6Sk8JoSNvFBslbXC3G4IQXHI7Icad+g0XoJ18IFanAxbWS6Tmb3GvdpMQW9rsJYsoGGsZ4ieKNjBLPlSCfhv6S8aDgE1tPmixkyBRHYBE5McXIGy7806CZwvlAHzZfhqeBLIfZh+BsPGBO84vVR+D9TCxVUH57DTmjU81o6sz06htnHduBtoOomcGfby2VnVKL3v93bD+82bOhF8aTLmIL0YoKYvmRQFVjdv/laiNje1uCEyrOIvn+/A92W+ePxkAeIKPQfPqlFtXSTiNR6GNPB7zUg3CqTjb1/ZQmUaBe4SirfxmP4ktHck1GOLIORwfkoBzCg7epniZwsiSSPntSGyAT65r1BbaMq48y4sE4xfvI7AplV32RKhJz+kJW+p8yzGaT8jtDsG1v+yxsgyEaC0Yr2ckVQRnl2aDMhxHs+LXNHIspMu7HYmyGdD4YdJSNPeOVQKjAW61x2OW6ejy2Ns8zeRvwlHXAlTlf0gTA2UuZ36LzNHohq9RFxm45vpb8KB7yiJzjmAz38iWgkJWfr8KRDGSTMMP5iBbkybYK12Ofze+o2yYX2ZM1XeHHlwp8ZH/braqfavDpq0c5onZt18DWeW2K6PC7yWZAeDq4jHCw+CeKFN2Z41ovGNUonjQgsKTNYi9IHYrsvXcTO/KmdKbywA/S9eZ4kfKJK+ITP30aW5/2wazbwt9dF1cjgPPfvntntaKye/4T1Ho5U4BqwGfVj+SgGubxG/0b/5JmQsRX6+n0Iuum0t/+Gx1N8mZ8/MvC/CulIESl5flS7KQUVEuT4B8ZUn+/Xpk9LliLFLH88/nT5xFZOWdzD0XuhF0MsiwumzbgGaqasQHjSS5u3bndCWzrfxgKMpS8/fAvjp3r3uPr1vwXaSc22XEuOkcC8z26Rr9GBkdZnuXHWF2gUHtcxhsqu/I+fpcLagC7jrkeikGffkJ+5VzqFNxGEuPtvpDBvGbHILu8JMG/kAoxDz2VwT/BSYXyBK9+PRCNs9K3C+Hrj9cjeU8L+Z3yQiwuM+0Ex02vVPFCHMwAR1i5JdH9ykzzrfZsKLh+AtT38wA4NFydG9oLcLKgtuS1z90Pby1szlArzr3QmJi4SAu5uq8oKEPNjErtiDW/dMH3xGB56/mVCC90wy1sXClLm84MA8g99HwgXWx6yz5t3Th8v0Td1qyPS+lJ6xuq+UvmuIlkjx0I/dntEagJRHh8w5SghN8YKVdbABdgNVKIrP6A2VldZPUEDJgzIyV/v+lnQ99ELEcJp+NrZgphZa3jAdP0wk0D2QrXY3GiHCoijOYNxPyMnn0W4tLKolVbLwP368LDgXU0IuWL48P27DdH+T2Ln39SNNFcHmvU8oYJ7ffr0fMCvS9kfOw/AgoorX4aSpiuqVLQHXpKHGcgXAztGrd5JYy9TqCNQKwBaK/QqH/RimFaz97K9X1cnBL0cS5+sA94I7EJZifkSR89n398BSpKQXjG/czpU9P6yIT5sA8JbP/hhRvG5nVKU4DdhAgNNN+T+yxnPw7ZbISE0epUA1//mK/iz/kD0xwtkgecWig/07KqMN79D+LDF/YnZ/bqtANP8xsUM6U+z5KJUVQVdmSqDLrVTCrysWURKM3KQp8vDDIrg9Pgrj1wTJbahrFy8EOaZvzub2Kh4Ma6zBfoPhC60BFNbIjumbAKKeOrBDPOm+KkdyMjEKaTodkVYgjOWikqw2j23TdVR6OqVWMrdkBInnvXmroMObupsJs+HiclTNpq1ZcYMxKOKndfaGYl3TP3LApvoo36dxmFqwdqx2RwCOyUJytusZsvOdWt2JLwQ1ZnBVGuxOUJzzr/Um9NRLvX0xX9uUuyPJKSTp5eW7eVubjoyO9YDIOhVy/tsdOt57LR+TdO5B2z62OIWtgSz0clZ9jPWVTT8FPPry7/ElRLoNkmP1hy/L7Ks1gxmU6+RIkTwE4F5l9S9Lomtm2n50qLTC0TH
*/