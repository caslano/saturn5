// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INDEXED_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INDEXED_HPP

#include <cstddef>
#include <functional>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>

#include <boost/geometry/algorithms/dispatch/expand.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace expand
{


template
<
    std::size_t Index,
    std::size_t Dimension, std::size_t DimensionCount
>
struct indexed_loop
{
    template <typename Box, typename Geometry>
    static inline void apply(Box& box, Geometry const& source)
    {
        typedef typename select_coordinate_type
                <
                    Box,
                    Geometry
                >::type coordinate_type;

        coordinate_type const coord = get<Index, Dimension>(source);

        std::less<coordinate_type> less;
        std::greater<coordinate_type> greater;
        
        if (less(coord, get<min_corner, Dimension>(box)))
        {
            set<min_corner, Dimension>(box, coord);
        }

        if (greater(coord, get<max_corner, Dimension>(box)))
        {
            set<max_corner, Dimension>(box, coord);
        }

        indexed_loop
            <
                Index, Dimension + 1, DimensionCount
            >::apply(box, source);
    }
};


template <std::size_t Index, std::size_t DimensionCount>
struct indexed_loop
    <
        Index, DimensionCount, DimensionCount
    >
{
    template <typename Box, typename Geometry>
    static inline void apply(Box&, Geometry const&) {}
};



// Changes a box such that the other box is also contained by the box
template <std::size_t Dimension, std::size_t DimensionCount>
struct expand_indexed
{
    template <typename Box, typename Geometry>
    static inline void apply(Box& box, Geometry const& geometry)
    {
        indexed_loop
            <
                0, Dimension, DimensionCount
            >::apply(box, geometry);

        indexed_loop
            <
                1, Dimension, DimensionCount
            >::apply(box, geometry);
    }
};


}} // namespace detail::expand
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INDEXED_HPP

/* indexed.hpp
RTBtaNJo02UhHpvfmy8FM5eIGfMZzZft2nwp+nfZVxozW398zLZrYzaO+JP52pi9CBXznv6knf//00zLj8+0+aPONDFfbhkW9I2YL/OT58v8yE3zzz9f5n/9+TL/fPMFpaIl5SLReOTSDcilj9z+KV3lKOnyl4+YSPNpIs2PT6SCrzf/UrMVnXf+qUjWmGsc5YIcxbH03rJykMV6vcN667SUZCWYrDIpWYd07zkE6H98oqg3+wvsXZmPIb/zx+JB3YUEXpXgjj+aaL3G8NU4k8i9UU0tI2taqtZkFpbRUBNqWIF9wkPGQYeMk0q0x9fGrDHvNvChk/Fj0Q6ccQ13fYJ3xCBjQtlUh1rB5zPF1a7c7JCbnRocei46A1rJA+OAXOHi69MwiDb5FwUCAVzV2W0X7WqAT10VZA1GVDmIKqCH3/zPHH1sECLpZh1JdEx/rFKU0uT6maSoTRAFn+J0cWmmUDLrKsO2plY2FIvvDViodmL+5hM8Ce0IkLPo2kFF3SVuB0r4709quwT0dxnCrclluXuTJyjsEmaQ/WElWHvrjDEHSa3qZLX2Yljyc0/vwrfc1ebwWFzswICkZLYxZCVhb5HLjPJEtic5s8hqpmtryFxpjFl0Uq8d3o9cgmap9+NwFpEauxTlb2CHaod6lw8x0yLcupCD7SUoSFSADkFzukcI1+Es2sRi2WjkVGsCvpeqFZK6MwW3a7T0Rl1617nTX4Bp1AZBVjywUkHBilLQK8mv7yQ6dBxMR998o6WtEx/uMFvaX0Z3oCX2wkG56Zjc1CM3cQxY0nREbhpybxwIfdfzfuiCGiX7RoQvWWtoRTn9+mZj4WBsctQ4g9+N03RfMN1fA0zfLdecVeBPLodpA2N1bFHQQLDtAT8QaUboTUs0RpehffOpequlrQ5v6cpsludus77ogE3F04XRMH1+frI1R5K9Axi+pNSmvVXCA0q2Dc1R+hFL79WzryqbLjv9IvZL+mey94Rli0xGkJhsdzzZZafTP2tYh+aS9EoOH4q/XY4mAZh6v/rpRPzTLL7y76Ihx3H8i9GKq+EqtDjwHkfITBymUnpp59P/nmgyuhkcxynO+gsVuiwxy9433MWW9lfQxPR047eY95inKzQJM/QsCuDWDcK2t0f2DsHXiZz/TRTGiRmBT1UkeCxxQndAR6zxvB+uh67c+p/YdV4OS8wUNFRXv+twBQL15XPREm2orxDj/d7hsrT9EDWN92GRy0+KFQRb0jpULC2mEdmK7kDiqGbW6DxzNWxYQz5lka2vlD4MYaYTsAoOLYqP4tYBsvQcCFewvbK3/6i3v333HZk9GS1pLzQw74mj3hOJ3++dYd5DvcsHer0DR72HdO+7eU8fDXHMCy0qY/h9QF/OoeT0UM6J3uX9vVjfiaRytvWhSxZ/6iPRb0eIwUBCGxcy7xHonbQaHGNsVrWT3s88R78diaeAVfmG2ism6BFO2w6Okts7FE6HxSEGcYwQEWDtwCf97x6YJfrfx6FG/W8OlOl/H4Ge1v+G8k+6G3JhxWJE5lIXLt59w4QkhB6e8FVucPX9Ht7QrhC9mQLokO7nntf1mhpX/KQOmjsycLdv+lsOQaNwklNMfCas18KjNfLy4Rq6iuvKegmlwJVm/o3JZxX31II3PmiwtD1G55aTFXg+Y1NxNwhN8CuHow2GVoW2hEy0/InZo8br+Q+52BQCftgN/FedVWQvRT0raB9MyaTuI9fzOfosl12F+0jiavAXOWeVXq+VNfFHkRaYpgvN1Ur4JLJUJMUKRY0LtplFJawrenMPz4M2vub6X+l5Yyfih+FLKqM8Qo+rHoXfh2XPf/WRdhRqt7+/xhJ6EbrvpHud+f8BTkSC+BhCAIBDS6V9DXxT5bn4SRPaAMEESLFKHXFGLRa1GPCSG9AiDVRtMW2xwUmBbczVyP5j8wSitsXutMjxJQiKn/OiXunGNudlg0GxDFOK/RDGl44PAQVl7u3KNlAsINXzf57nPSdN0oLbvfx+pMk57/f7vM/3+zzhTCBWItnu523paMPufBEGoucrKj7FG25G568eNkWg/gDiFNkdnWoig/BVjwIJv9/Ghkenm0oCZVrpjJCGz9Oy0a2y+CR/AKpPJStv9anyYDk+ShvbrQX4upHklovFT/LFr6DL1kky1466BZqsIHOtGc21YfiNiW5+hM9b+H4YfqpBe/8nF5mSq98p7bspaUqVyVO665GUKc0XU7p5pD6lZ27qM6Wb83BKR69MmNIbq3unVDQ2eUr/PVZM6aWxNCVzwpQa8/uciIc+EVvOdWbr2r8gsxUEbqsJATDIdrSln8AzUWPjmU44E5PEmXiczoSNYWRnjISlVp/sGh/QiWXKyRiJYD4XYIWdATAH6OUTbwAwD3Ooizci2A7+1vALmgHh020lJSWs2Im2t1luyyETK3YguP/EhkbMgdpPAJ+dBHgvZK0I775PRvwvYjkSvF84Hof3E98A74tOALxv+jhZcz4Zy1Jma6sQYKFSlaejPmZ/sZk1p3h3U+GRSYVXImbpWx4gbz66Zc7C4Z1H77ST3jmJkPeL7QLyNkP1rQh5BCczxwDkVfRgD9NslDcvbFMrTuFUVooQSad8LQvH5AewcPNCgI57bJQx+BQbOi2Il8pKtKcbKVkrlng5S5KgXQeXxuhOnf5TWNfBV98IdYtPseqTk0uCAT4lKw6ZDj7sZYRMB0Hm729KhkzrzQIypZsJMh88PkJKnfKDxy4y5fUt/U35B7kXn/Kx1CnvCvc/5RPxKf/qcn3KQ3JTpvybMUlTDlyeMOVRP++d8ts3Jk858yYx5SE30ZQXHuudcuOsXkFyb2hQ9C5rW1oRyjXD1zsk5XsW+O+OmycBYvdqhyP8zo/iEFukK7BDJn4F6vemW9tMp6ZujnAJ6nPbsRQtNjBkp73VVvlWb41THlsGxfmuP2D8GzRp8/8X0+8RDQUWWbapEWtvBNMaZ3jv/d4ai5zJploSCDWQMJE/MDXEGooVlmQJaBSbbDGEmJXvoxX1UkIQVpevwioOxATWOCYgs+DTO/v4hokeewWZa6FuX0Fm5R4y315clkH5yZIkPw2DhnT5aWW7cMOq6EdesyTIa0lTPUgX8C4hstFUhVwT7+jlxGiWvaWQ1FOpRAzyApV1pJSl68v2hCaPJS4ZlTB7Yi00Unh7REq6ZEnv00nblOCHMdmCqdOMYkF2nswht5LZA9iPlZiWgy2ywfxbgeK5tAVWdqsArqFbEbjQy9GDt6K7w0dnz2nh/tsMJTetIGp0oKVSXDWM59lCzF1LqiPLefJ6inVdKTwbXPUxWLr0IHk51McifwGQnNPH5IoKCvvGdszx0t7caT2MvzqODrCa3oocOQ9Pm7nDvjGGlsZThzqA0YYCqh/BgJ07eBoYePiNf899UO04VNEjtNgdFzNYwjQSbZZkpBxiGBlXbqGM5Mir/iWWaqfESP41sKY5GPEuyNM1ClB6BWw7soBTLcIuri3SKQ1NtL/63xL1W7+m+naoAJUNLUDBnL7aJ6o1HtN2BvkKUes64AcO+Z3Yq6MEHWJExz+xaGMxhS/+RZYTG3P209iEMlZhK+NTRGOj0YaGgek84ncWKptwSE6S47WHbdA2jG3enPt72wvNbTx4C3AoHR+MoBs3FU7V/yrFhQYO3v8C6nbC61T/Ku8ikOnvwagT/P2vNEr4hJZW34f2+r0oqy1y2+vfQRQ/MerfUK7f6QDkDb8CoYna+KyPj0dE2JqQg4+YSRER3wilAQ93v69VnitCmRav5WP/mC5F/XuQLABJWNPmX0eaoivhMZGgDfDETEnY85HfCJnKVf/Lh/0vR/1rA6EB5ZUYIhNW8g1Yyah/TSDIf/g5BhXyxNRp7rqKdQD//jXKD9Z9hR6GH14vdE7d0Ik8mPnX4sMOeMjmuMWdCAB8uYLBguB1VRjnsEBfRUVMKCo+PawrKrTwGyBixFwXNNQk3rsKd2GxBbU1976qhV9gw2AjmF376ZlAUCuZH/1BHf/oENCrrH729z/F/n6/h/Yzl0AH9rdM/L4SdxagRAAeNOowAGYB7XB/QJtLMMKHihayCfwcBpAIcUeHksqLAZ1+bnZduPS5KfyGc7P8Qn/npuhi50bvdeY39Br4hl6z+u11xsV6zRW1Pv7SWK54r+zeeMdkf555sY5vFXv4imjietzDek2+FveRoTX6Hps4/biBeOShsdJZtH82YFoTryMYLY4WKKT4y36gIJwABfLFhnRzGemgbaIBF80RhtNzPmltHhai1VwaSx8ymUj2Hu9D9ixoGDboXl1fupdUfemlqy/7huor+vqwpxZZ1X+RBG6gJJJqiEdL1MCLvO1TuyrVelpiUe/tIQ/TWFe1Uu2UwoOV6iwpPMDTMRmwUQe6t/7jUOzo3z46dvRQ9/aCR4cCYH3Q+dEx/J6BHJ/l6EFPrIwNI88IjHUQXZQDuMV1di+glWiF85odZw+WjIyd3RMttl3TDEx2j1aaVx97BHu0snR1moWI9P0dST4dYl7D2L0ItkgWcHleTeSE4nNjhujUcmk+am3/fFTi+r/xzVu0rk8RMVQ7KazFODdcfJyN8XE2Rp5O8Bw6agXa9uh7OjvPz39ueMuA1JmD9/7T56EwYCelMZ/0/gipbwKReb2XfOfSlSDPYdYcpDA/n4dhrzpx7N6ZlvAZHt5LR6gL48gFytVZ7kL4X4QB4uD/DBE1Ffh1zCxY5C7KLXIXYKZBVaZb/k61SFwVj2IiSEqm0tBwaIY7G7hyVwg6oghY+ssAxTIQd8vdGHjx8wZ+dg/gkyo32jEAVqIz3ONK4WMmKZeBYC8tQX2rDhnQ/3wRl6hl04g+iVPKifHMERzudDYtJ0Fa/2EOLd8PLRhgbL9gNQ71sqTXJbCkNeuhacd99wVRxHEiSxpnHPkbnrj3xeQc5bs5UiLfS9uPnV5uwAdPlOGRnvc6F656OjkBnfMzNOrmSG3py57tL/vPiM/+leAxhClx+jfyV3bTJD8P8md3kwa4JieoM4fxA5ehTrX0xxU/oi/i1cJf5wsWQFfzf9ARygFGHKaGkjFU7XuGwgNJOshJFBAa1yUbRuMdoOMQNalss8Vb7VV6xOULWmv9qOy8mJG1fp/hpWx79v/kpaztjkvS2BI5BWx6TzNMfU9AP7xtT199D03pBpTo7rTVd8ifEeXNAjJJLAo6MpQAhRuTMEFnHy3QTfHqbkCu5DzmKAeRoVznc7AFF8gNkQGwzAKk+qqSgObbkObrzBFu+rhL6p76qTDhkhWu0+eGPLo+skN+wzd34iVnmNmLHEscCSWtF+9EX0DoAVdAdOK8ZCffTqka18FlX7LaGCBTh/wuoxrymdCQwWJSA1kJDWSnGiMRAEaRpzLFc0hYzrxLLucoml0CN0t13Al1HP/KnuX8a3vW33Lm912XRn6xk6aQB4oDTtq4PicNkDC/ZgfiHsM0C1h9kUO5TZL135dz8w7ESOW6b1UGonebJzZ7TorHviNR3epI8ncpUR5x0HJ3AMvl6PWmQSkWmvwrS/bdMEp3ZUJpg/8p7AfT9LY9ANg50TieeqPxItbHKeSiZQMpZQkvOpJ9dBzKdx2pPjp0bcTalj4L1pZfhvEJgNf+X96UBZ5YNES5jwmoSBIQa2pJ9iEyeJdEnbUz1eSewkS6LsmCTrjk2zH9sFeoVSORwkoyAWC77Eu2kfcvtTGuvzZsCYgopx9msG8zWRfVkyWc1ZZLrJbtG1jy3lsNjZZnLnL4Vu8wyNy8/xuZy+qIk7l5BpnbszNO5l6FfvixjtQLAaijEfzA0OhkmzIBCf6gQCn6TQl/tQTotqVAdomBJPGw2JJOrSP51Hpi3sk2+7OxlkTPbq/fEc5Ax+60ipZAQLjTYz4JWyBk1jJfdW6MVPS5vID5/4azdFZ4DpEJUM/M9yn3NsZ1uml2t9b3WGGeqLRv9jUtqT/8yAD+89Fw/K+CI5XknW2R7iP70ANWCWY63RKs78AEenSt9eBiM2oCq3se0pxB3uzv0YIhKQBH3NA+OTpRLmA1Nt9Hi0ezqVbfQftylEXYe7l7Hoo5H9rnLDU3xyOQKNttncvxLWLL8NVQ/kXl4wzztuZzZuWcpXpAyDKza/BmjEzva65JY83mNkyJfLDKDGPxVvfYl3mRv9ZH44HRsOnWhzqcJdpCi+o/Fwzwf/yuW4NWWfU5tiO3HQcAb81t8QFgjmYx7e1utcYCW4ieZrOtc5LQJB5ZvF/JQzkOCZm+0qyy8rP7guycWtzTvc0kj4YSRU0PPPBAuu/Cw2nsI2SDPn+o2wlw38M/e3mwZAr35F4IH+26Hgpec7GCP5zarekFk0MRx731p2Wd3QN7vHutSR6kLbTyztWDpa7LynjmK4PRW8IFosH9OF3YND5ZwwQgvTEmyP1buHta9b2+Lw6utecwspbVW4u+OzWAGvJ1R/TNFGBCHoJX+sdBVeS4Wzwx463zEm9ZrTse4xC7QJVA2OGtRbmiarC3Ftnl6t6u4laHUk8swEylaGjQAhF+2/RzmrEbk/F6dOEZ+7PJmKq3VshkVMvoreaJefaptRSWlaRWlS73qyQAG0Pdkix1o17WoQqldr5FrY0lKUzatTjSqt0QzxmrNB6jbLRDlEYn6kuTVyMkNVb/BiTjudtHUErEXTzynKTnLMNUn23pY1YDxdy6MR0eLNCDVfL/gZ9wpC9/J0VKZis3kKeQlamNGPzAQReSkzFp2IZhXvnJtyWpdno2DCjfE2ubmvWf+G12YlKxaTiu9hYdn4reDX/BEY3p+gApoVcG/NQx7A9e7Itm+P/bnjDQyZY2k3PNpsjr8/cmXQHHWgZ1j7+/CLbay+8fC7joeyBbpi14CQB4W8tFI6oBci3DJKyH2N055W1TCHLZKYTNfF+rfDubkuPZV99tX7VNXRCBIswULNVDSjycE12YRXYNiuvaEJIo3NoUZwMFp6Dorqy4hwJopa8dkZIEKmUYSrXV1DsOMYACGMAEGIC6oEr0XK6tWPPv9rzsl6k9IwCU5JR5DgP1frZF/Rk5Lwwt00ot91dcfIgiyIqIffzCNYDRpuQAkKMFIctJUThvNsYYyPq3Btj1i8TYYpiVgq++vUcE0UTXH9bOnXjOjDPRuPO5ZDYBqP/3niG4VqcWorfvEnE0nK8m8wqdeKEiJRUihkhyUGDkdu3puWnJGd70m8MYJeZuYWBDdJXPqH20Y4UkbWFh5TC0toAMNDWHJidygd/4K6fU+zoerUR5YL40O+XIjcf83MHQf2j7Q7eyc9p+vB31iGWOamLNvYOvxNi3vP42sTAZrL3zAVJH6GvCn0tQpl39JhzNG2OGMs3/tEAZFGkFTk/Pa4Ay/jlIhJ5ajq7Wmrqk0iS8kWlucCY/iCXej8W1+nolNPMLLAd/5tEfUVm0mKy/ieeH10HnEKXsfjirHL3N9MiUwhDFHwjiHpSh7unppRg35nKMj186QVgMMe7UlJwGpfEMocmHE5b43V86xcIuw2QNp/hV0JDqP8ZaMfjhtZhKvBB9OJVPuwHyLErroPLKa5fCqDFvsrgzWdKgcIf6gyPsTIAPH9Kt3ceKj2lhjv4K6XAAV2DKmK4sdr8FE1mb
*/