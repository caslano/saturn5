// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_SUM_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_SUM_HPP

#include <boost/range.hpp>


namespace boost { namespace geometry
{
#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct multi_sum
{
    template <typename ReturnType, typename Policy, typename MultiGeometry, typename Strategy>
    static inline ReturnType apply(MultiGeometry const& geometry, Strategy const& strategy)
    {
        ReturnType sum = ReturnType();
        for (typename boost::range_iterator
                <
                    MultiGeometry const
                >::type it = boost::begin(geometry);
            it != boost::end(geometry);
            ++it)
        {
            sum += Policy::apply(*it, strategy);
        }
        return sum;
    }
};


} // namespace detail
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_SUM_HPP

/* multi_sum.hpp
GOBzjS8Bjt4Yw8sBb+9OtvYD68c7zKQfeNtjA3y+6bMBbnpj7QP9G/w+Wp3puwG3TuEWmv6bwHUk1/Unkx7jFgDX19+R7E+YJXKHO9L25aBHZ5IuieroSrf3d9EEU2sv+ppHmX4dWnuZ9uWmfwc4UsfwkwAPS3uz6esBL9PeYvoUgJu0Z/pInImacfsHjyb8oMAvTfX3nZxsz9BpWeJDKSOdM3RS9shFrq97LNFvAf26POhPIPqtgn/rWhIuSWGzBNFtY77RdG1Et13w81/ZSnYMpU0S7Q5HW9vXnrH6dBJsp0ehWgN3sPUEu9Oj1Vbkey+F7/M62roRPoXCu7wuu4rJ6zcEe9ijXmZrhg3q4zYS7nHP9kAD/nQqwZ/284imDX3ez3s9reuTSDJoNxP8RUebTkg0ZJxJ+Ne8ngFfx7Mp/LZZT/KHEITKCD/2ijpbKYs0gcVvNeWwyJVPglq9zjdlELD0Kf2eT1cOWEfXBqarAIwWid16GeBxnzaZhV9kyhvg8Me+XuA+b8pbkRlDUXZBt0tMOSuy+UVwgmG8tbhIjbcwrmouCo6rLjPlycBsQfSY7iTQ0cjM88d5nQZmC88bPB5MGRiKmj9OGyxKttPZSDlYs2OgGdRwbK8Ud3MU7X4MFH7nF4nLpGbXzjD5ZeX48Ycg8uBTO3tOCB8gNJ9+Xutoprt4e03eYK3DhF202lm479jBwMrBhjsY1HSwYoadynR7WVjSjonlfb5XVeq1El8PtViikKR8lA2gc6gNNILnQq6pzPY3rhTfV+A7WtapofaWCC3revCcFzWO1twA0nxuAJ82jJ+vrZTpd76/o1L6hYNdVyl9zsG+xLBTme5GCzN55u63of5QyU2V+aw3LvDOKwof0y+28flckBjb21ZVjO/b+9a2thsS8Q6SrV3tLhy5rl7ptaZ7ZyRMB8TGrzV1EWA0YBZ3L+N8Lt+9bMI4c8Rn821dZeOsGWf35vR1b/LE+ftW1rHTs3UJ5oxbzRyEXVOaKfasDDp+dqvMDAHfIuC1gD9H8rYC3tOHTUlvAnegaS/t4RXer3O1axvhGbarZeE323YQcOwb2pfK205RV+3MPdcbvleggDkiM9dzS2V2rucr8NU/wVdvNbqo8zQjxXka3o+kzgnNzPYJPedP+Z0JGrBngqjFsm5CMPjJLM9Mr8BPeA9G+B6ow9UeqAViDxSfm8AepWk4A3GbsHkz7KcMZywWMv4NH1PeUcljB95TmBLfJ+Obx0rgRTbJMY4Z4d0NvucgvhrH2J8ex9xbiXs/WI6UFRVvpPeNShemuoH3hBydveemIWE2eDavpCk08/+j61Y1ok1SuNX1y5b499gMU7i6lXXLbb0l5tseqETtajpkmGLjMO4xk3s/9RrKtyuxViTweh/jLoJZ2ymab1UGbfdgZfCuA70X+aHK4FpqTynmweV76IKHgZVgHYzoLI+HK9062D/K3ZhvkNbBZLiZwlHl3B3zSWao8LG7KiC3Q49WBudxS0r9efiOQH/4MZvfzCNbtkoMvKsnRXPmXZnuTQ117u4gSnvJT/Jsb8ZHvFP8UxMf79XVY83ucVEmY5TW1PqQ1AKs01sfZq8Cedg93LDZcdDb7sFVdd2h9p5a9HmPSvJ44wnTV9d2BH057jk35POxX+IXIr0VJm/BUlRFQSD0jHhr/tDEnNqEbaW6uA3QQE7nL3P0dcDL+YjkBJDk8zT49Oaw11M2r60SSxYC9itrK+eFWRu10UZFj21Wgb6HH46Lvsd83A31jLDh9ALKR7W8H8T1HZCvbfwdQ79kHvadPCdkledpo9qAXdbT+y3yrO36WhEm2etn2n445P1GyBsFeSna4d8=
*/