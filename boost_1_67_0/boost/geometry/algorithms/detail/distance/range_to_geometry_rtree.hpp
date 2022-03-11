// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_RANGE_TO_GEOMETRY_RTREE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_RANGE_TO_GEOMETRY_RTREE_HPP

#include <iterator>
#include <utility>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/iterators/has_one_element.hpp>

#include <boost/geometry/strategies/distance.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>

#include <boost/geometry/algorithms/detail/closest_feature/range_to_range.hpp>
#include <boost/geometry/algorithms/detail/distance/is_comparable.hpp>
#include <boost/geometry/algorithms/detail/distance/iterator_selector.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template
<
    typename PointOrSegmentIterator,
    typename Geometry,
    typename Strategy
>
class point_or_segment_range_to_geometry_rtree
{
private:
    typedef typename std::iterator_traits
        <
            PointOrSegmentIterator
        >::value_type point_or_segment_type;

    typedef iterator_selector<Geometry const> selector_type;

    typedef detail::closest_feature::range_to_range_rtree range_to_range;

public:
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<point_or_segment_type>::type,
            typename point_type<Geometry>::type
        >::type return_type;

    static inline return_type apply(PointOrSegmentIterator first,
                                    PointOrSegmentIterator last,
                                    Geometry const& geometry,
                                    Strategy const& strategy)
    {
        namespace sds = strategy::distance::services;

        BOOST_GEOMETRY_ASSERT( first != last );

        if ( geometry::has_one_element(first, last) )
        {
            return dispatch::distance
                <
                    point_or_segment_type, Geometry, Strategy
                >::apply(*first, geometry, strategy);
        }

        typename sds::return_type
            <
                typename sds::comparable_type<Strategy>::type,
                typename point_type<point_or_segment_type>::type,
                typename point_type<Geometry>::type
            >::type cd_min;

        std::pair
            <
                point_or_segment_type,
                typename selector_type::iterator_type
            > closest_features
            = range_to_range::apply(first,
                                    last,
                                    selector_type::begin(geometry),
                                    selector_type::end(geometry),
                                    sds::get_comparable
                                        <
                                            Strategy
                                        >::apply(strategy),
                                    cd_min);

        return
            is_comparable<Strategy>::value
            ?
            cd_min
            :
            dispatch::distance
                <
                    point_or_segment_type,                    
                    typename std::iterator_traits
                        <
                            typename selector_type::iterator_type
                        >::value_type,
                    Strategy
                >::apply(closest_features.first,
                         *closest_features.second,
                         strategy);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_RANGE_TO_GEOMETRY_RTREE_HPP

/* range_to_geometry_rtree.hpp
3ci1Guf6ZDqIdd9cGEthvM1bf1TxLBa4tmlXms5UrloTsarkUzUTkoJlYdudSbfajDR0GiuJN9BGAbkhrbYQ4rbXTVStnRdpWmrPwFosvGxwt+V9HJOlOcXcWXDVgQ9NbCe9yGyz19Cc/0mW7F84Aytnm9I1po8PFxjIl5Q5M3+63W36NYjvXZUe3Aad8FNv+MLguS0QZYc/eKqn8AtkQmAuvFYn90D8nWYb4ET8obqoYmfm/iiMfjAnL4w7aaMrEQAALP/Tt0mUF4BJ8w6ix8JzDgJt2VqwLIR5ZGcYzrHusW1MBAWGZJlH9++/ck2ci9zh1JSh6UqBsZ10h7jNKY2Wto8hhwkkPXB7m0UhleGRVVq1Y6koU9pTunAebSJuXNCEqzXmZtH2wQxouDWBrV+MlKV9tAs9gpx17yXHREswmW35MfwgEuD28N9RfpVxWknVXBH6ZmdxwVyMK4HU+IzVKxEHGPwkx5cuIjGPBPevhdSIR8wuLh8ZU4fQ1yNO6hvK5aCZdOprsbg1YY6tS+fckPaZDGZgteAJ+1vlBuFvag7QZj8D4usEiNt5ETo6Gdl7uF9TI9l3zLTHloGJC4waG6ksvgMSO3rjFeosT6g8g6/8UXVwZlOWzokHGEgQZDBBfncABml5Q/KAmGDuC9LTJo98qIlEWc8bkP596r/mq2N6yyawi9l5Gle/mHLoevfsZgz5eDz3jYKWN2Y35b/jzeJCkTTkD+gPB01eeiaSocwc0T+QVLYcnS85yiL6SATmaxNNoEcqC3X6DAOL5fDpespLvKlTl4306nJru64raTSFy8z+nAJj2JGMDXxefVkrCNLv1wFYwkq5gHstGeTh4ePOVWXqDdUVQlnGGP1Nj3vy2S8GHcRtZ5Zq6Qc88aF0BWqqVNaChj5uoDsHomTtS3cloQYlieuulU69QG1rEODDq21uCu5uCitfM6ZqlbOJim45k+BQ8o0nPgKZTC/yFUqHJLnnt5E784b2UHVMh1SIBhVEtnfm7PSSPTYzKaabdjp8EeIuGDeCvyCER/CKxA0wgAYKVKAxLVjYgxx+lznUKrPQGFejQj0P2YhgFZiq6K4AhUbJESX3R0BoNlhVAR8WCyOCDYw+/p26YLu3K8cJ52+w2XBIttQEOW6x7KoHHnQoHvNDK12e0djjc+O/nedU2ido9BBu/4coZ6oaTgLggcaa4XRpuuVh2wJW8Sm+9v39rUSvWyEhQtPQzHqpL2tcmr568GyoghUZBBCydFVwD4m223Hw9qS5jxKKUwNv2RZLpbF/RJWoBuuXDmzE4zS5ZywbYFJ7lI2WTone2+I3TenJVHzN5sGNRL/XsilwcUjFMDText2n0Gu+de+K/dKfKWTOneg1Mb6AtTFgD5X228X4XgyTkRV7lSZx6cMJhg5v4EpzrPKzKGw5vb+v3uOxNXvlueLMt9ji1uQjKzJiARqqTVHwQW9aTVmWvryS7ioC/+ZDb99hVLbmWNroT//ghA7mcduYlZz/2ToaznIWUS2rJ+7VUkTHpGYbKKiHfiFJ0kHiwTq1w/ySKelhxKi6f72fEPdX6/YBIWr8SkX/qVDGImAAe3dpdbRm8OQM375FY7yNVdYz84PLihEcf5UTEyay/dpDnEOHW7DaId+8Hws/3ZMsWOkm2PK0F35c7YGrqcR2CAF72HADbB+3amzhu0QCG8XVvf5WPdoqqjPVxHxKNdKhtXP5M/rgfShagEI7YtvaeW8snUBBIk4RRH6UwUYPCujoUVGqzFRknZckPO4UrlgbRmvHXXRZiDKYPIElRqFFIVKczlfiqZuX5EyZzO8xTlEUiv/JctR2R1LQWI7LdXlXnYeCXCisA1u2p/esYV601ErXr54uxJ7y+WRJNNt+FfzVPs+lv+RT92e5FIS3hgSDPvwhqkpaKrDnZVKWCobz/HNgqchoczu5tda2ASjp3Cy6OE9x1sDvyXZUw7ED83R3jzN+/eNk0IlmPLpEq4LeaU6hZWMivz5pKSU6uPD+9B3+Dsp9N0tsn3iXk9qqe5/bYkdfmh+e93QPXs1pE/XPNvA8ihlTceas3XRUV59z80rH7T8RAWa2R55Axyb7mcHMzW8oWjbBaNQEVcBA68Bd1MDe60ty3JNQWw8dhTL/aERqK1ahHN3DigkGj2Y8olxBtrmvvrBbslv9nJPcOrfdYdgX2P6pJaC6tnd28XLbGx+F5HLA6/tjERJhm55vJ3DdSjvW5K3oDPCN+P2uYcg4kDe9PxqFHg+1CzX764/jkuey6CJQXU/wvqzq975MEvMH8reHVtT+7H8/wubA0Uy1guEUngVk6K5dsQEu92HrvvHbCwCD8/xRWOznuZgooWHWoCHbq4j7bIFXASs45nguFIDZl7+geJPwEzLqAlUYgiOkmD64G4E5Yg7Hwijar2Ck5+Tbd7lPhLj+7GdX5oStGXYi1s74WUJOpDcL/6NuQGAQNkODJpBrvHogMeVx3qss83wJmQm7njq46PmUbXKZUSLPKNju+ccw+bLaPcjNMlv0bx0aiF+LJC6tFq8zqgWcb+DVLwD3A1w9/5CAZFaK10GKtG5z+3WTlqRlC5z4zVIZMKxhy27UFYQz8ruGRsb/z82li0dnjYiJYhbP5BoyEO8pflrUd6/rrp//CQMLQ3YtwjcAV7vHmGly/ak2F8bYKjiLwj440teQiv/OtJdyANAw/Vvd+uCt8sDLqdKNbmUcQdiBQ2sr9i5LkqA297d4pPKqW0JsGT7h276/E/bbFkQM3apsL7uqdj/yqqYxTmzBd6EFlfGzg1Z+FDjve+r5vGpY1hklrcXieb2cUiGv6m1kZV2ggk8lPzFqvRA0rq2IDObumZverXe3Os1bNZ8QOKF+sqJHgGqaLnpHBby6QgWW2b68+j7g4TLjfnmNqI9pWJLj5yAfbAzA37sd/ZyMvZ6UfyJOHpVQfOVyssDHD94I42ts+I5fLwAJG2yzjehmSkNIY7r9nXewxVcLxh9fC/yM4OHnCEbuYgVsi/Gn5CV7to9DFuEepQwhhsvc7R7CPwLhzn+zVjiJ2yVwGP0RgFSatnJfRDNqjtIkuXntKTX6Xe0j9newZc/ClLP26XtA1hrkCLogFQW9Cv2ERy00mTmOWP1KphuuFkYtWnp0x67qkUX+lesW+5Txi3X/3ZAyDkr+8BszFxxBe9mPDsOYIpWf4WeMLGZhlnFjTlr1UfRlFsFxY/f6DMUWc+CSV273Ryil42a59lLzZVbBUQsABfGvbRd8iphtx6dROnLUdwyBHhX+IyFOoi5y8j46hiokodf8iB9TCfJcOjd6JkTxl5f9vfvYj08qu8m5YouBDxUsvoOTLI9TiSOT1S3UQ/u17ulDlhlEcneKDHAiAC7nsMGz1YAQ5UwCZpOid1dMKyFwKvCoiB9XIkueJxF0qQgjtxFoHIAc5XBXD9qcZ+8S7ptAHhhPF2VA6iFcdzCpMWtUjTV+tZUghjTUL412kII5YYj6YqTDIrSotUuKAvZGsCKnyRXhTJguIbIBjbITVVViaG1gBCcc+Gtm7eAe1umu3OAPv6XlchOAsy2dkj2k7YfGY7nrtYH2Ui7+PPbE+K0P8BtZbP8nj7SGRMkMBPukSYGaJ9yopjL4hRKzeqX2RFKvlByA7c0YdsgWoAuI2bUQFKL24mPVO1BxjWBrQCh86cZth9TWMlUaIALlLXA6aAXtfucZlovQVBsN/flPg6BTkKAqNd3yfClcQIqAZCsX9GNUYGwawkGBLWBTyPTgukQMxw+r7REmCOQrMQG/DRoyevuz5mJFc93HGjj9IJ8X6TDRRKsbQFIOInmzTzPy3lIUJGRjNTD3zCeNBlQNgYnhVAd+Uo2Aw8qUnxcA8zMLuWX7G4Z7c09AVHnZIzj3dk1TT4A4AeTcD5pWi2JvHh3MTRQyTkgOmd5w4CdnSm1qKv8aSexaqEAxI533e8wQ/bUJSMHHwYW0CS6MW4tPt4DphkMZgC0bShzH1ilaByZdAuC2dyUUGoL6RFj7JnfrNzhxAgd+uS2+wINsr92QOr4ueFdGPzlanWP0IUQwojnkRA09cA51pI5fzqhKI54c7YRYom+on4hVa9y1n7wOrZX62wCeAaKGDKZwrRRjsoL/iLB8bQWDrcngVUryNH6jYFxXzY7N4MFO88iA3WVhaQu+J7CIZ67kFgNNz5kp5/DCzBSkVfHVN/vaQCoJslEtoZH5SczWKPonkUYuj/I8ydtUN0E3e1xGTVSLuM1dGhQsYZ7fO+573FhzlnwW9+Gl+CDPYD8eAEdWAGQHiiFHwV8aYuof6NcUMfB3vjxA6cN4iArAGF67tVTCN6TBxl1rPFqBsLc1WCJi3Z9HkhVN72vEWqjgBoE1uR8oZsMgRhnV4j49Isoypi/qlVPFcns3UZmsAGko1Anf9xLycZ4QourcENZBg+LlungJcpbjGuei4Q7Q8po3V8hTFjsasa5hZLgOfc5bIyolYrlWmBwbMoCCDH2N4x0Pr9FyWu1PMq++jQB31c4QEg83WROByKNiiV7JNZhMbXG6F79QKZLd3a8ifoJp09R2biEK89AxSeXZ6mLZkNiyjVNFpMe0pFjvpvTOo08PMBxRpSUAflAA+r063HQKzPgfWP77+qM6IDob2R3aZDHprvxqGU8jtjK1ZxvFAsQWRWMZJ+3HuEY009ewDWgYwAK5Yz8b8QRNuz7YDXBA3qZ3VIlNmWeyVTTj+Ipi40IvqBpPIYlI4VN8p7qnZUnH/E/hyEIjMDZIRLqDWDJgtnxdoyrjfCg/0mnFiobB7YoQSu07kKvpWEA431tN7uxXP4jbXRgMkf8+KB7ygfZWXmq7IWYiBgYhjQcRg2U9NS+IYB0RzjgThj0WoAyQFRfnHxAqYpUpA5+IHhZijL8mNu5gFPdRkaUxZ7HUukGETlY3T/dHQoiUpxEELKoquXY2x8IKlhd6/vreWffClbCe+fq6/tLZgGH6qMPd0bzw4vNmSoJT68gblVqxzYX7wGPlNuxFofEJ17v11BDRyV2ul23sXWyd17PRq7PyILUrp+0/Xbyvlmo7OnvchmrtR11ocj2nOSw91Et+4vBcf5bS0NIgtR0vRA2CVsAniOIVUjqzJPiatkgX7HGiXPNYkRJvXlWRTYUGcm3X3q2C6VspTqs+vAvy2APPaUAmcaXjvOhpr+ddIxbnWOxpmTYke8XRYdja9wGGt3DyE1wFBRDC0Q4NbIkX9W1LcU2x5Y/2sbbqXCwdJbv8k6CuETFEUVpacLKyJMBXuBO8bK4nwHahA5fwLMJ5J6k34OE5IWgHeiZL9nUiFUTawtsde4U1SdsJxJ+0IJLxnNiiSM0wUVfEAMqYdhqPRSVppnldPsFTakIXGaFiAq7cn6MWoTgIURRUzeVBU7ykZc5wk/ucUAdAaxIqd+405pEPaPf0ymjOvl5efpZmW17fkre+SfQdbHmlMVPbzUy5GjCt03pnbPtJZ5fvcFXCbrQ4InfDGC+0BVXbxNPT1TvkhjzU/Y3yjJ0Y48Jz5zCoCE7czOYkfCO1KqsGeXCJEZJhr+FF7iX8U4JZv0JWYzfre+efR7DgvZgfzVyvZYzsrL+/ndVPYXa80TifatAiq7hhLIpvc+SWP3Xj3r0jqiMKPxSnjew69XDU0O6oxylTXLMocWFNgR0ir5F8FakP3XqLNOHWSdq6rhEzYBW4OufJlZQVU/0oWyPPD885g3cxGOvqwfXEjCasu06k7zqjDa/msiMzLqlm2tl8j2ytjEHUvh5BQ+pdHW1Jrl8ezva4ZZ50Oh6my3U4DyXKN/OHpK4m0Zh0lzgHeloBfHeywkftOYka6RwOiARPkEI8jRTOfGdX65tia8w5f5MrR3+scCPkQIXWbgu/5r06QIJQak1y5yzJ1Hp83cf4dO91M/thpJOFm4eDy6BqpeKo1ruaG1PNvhpWaazS/2dymE2BKd1KUe54fhqSGx0lafktUkl3rMQpQWYkKHa4MaQgVhQ9uccoqpwzG6OJ/QAchrouCrrxhJ5CjEp1uOsbcvnC2sQ6Q6axfTX5emnbz1JYtTV0oDoHtprrDNIKPsg6Vmbub9f6Jh5yYgulB4PhCker/6wkY4XtXlJHf3IAOlCqSOEiycYq8IIKoBMqDPWYXrDFQyXarXotVPEkdf8prqV31VRDzVhebtGxqBoj9hOmnsqKkfdgfGkcIbbeB9QTdjvvS+az5J+ac2WD5ApPfwAKsF61x1lasksDNu8UR9EweHk3kNXq8Tr/ob6qv1eky1poUdvygj6f+Z4bhuiTGjiV9X/UHW0zjwW+t/3rIkrcSyUazpxLXftmwBOv8a9NFh3KZ/WAGRmgpCxXnAQRP75XWXiV5HX04r1o1e9NWa6qBjIN+qpTOks6/wmvdPqQ2P2pxfHWIwDHwhaGQyBO5VxTc9QkjfoQl8OSRYGVGoBdCbBZpsX9xkZ5lvSjhmpoF4UBcwIO3Ui1j8ed3W61zjeBkVzg/E5u3+FLjl/TU00fvSyqEM1HyhNr6UlbD6OB/kQhaI0WUjo1qx96KdMfAf+bIjnRWKBH3H4ol0JneTTTIDaZbicWtt0gHLmRuR2dgeuhYNre5i7DjFlZWkrwRqmwEw5zNL7OGbVTVqljcCcn9h69i601y1eokoW3mBpaHC7MSfIQyg5uH3S7Hqxz/7jH4sdcfzzxHCeS55GglE6UWI4IReNIaCOMAoXTv0dd7tSYvU9HhV11c5ddwYUR0pVJDT784xkpMsExIPy9LDnrcYhvtBPtzVsDBW/OQpaGr/zpIY5hXgFnfpNTUA0ROh6RW+NtcJR/1FhkSrQf3j5+fVkZd2Ec/dfMtS92txaMSJqlCsZ70dk3cU9WxxzPOKYXuJufkLfELfMB0koS1qalaojI0wlPtWV4FbjFBe5c4RlyblJKrj5lRxJrs6KLufKibrN2D8VpwIboHYsODRHtSVlfvKRAFQ5V0DkJXDHNGb7BgfmmTS0yAWjQzyXLBIc79szPQQfcjixNCJLBgRhUEqKVmTsOfKl5DyKq/4v1xVBb6p2Nh4u8Bb9OxIBmxoad6KPn3zgJGLxFRmo6CF8E3Mg40wRWe2/RW6XwUd8C3AxnlM2OIt4RhOnFuIjI4x/Lwmui0w/snm7/XnROp9FH1kuMW58AXZr8YofetCvkMOOLdTmToLan4t1ZEw7kAz9hcYnr3RZ2yOgsfGC9y3nnIjJdGg4Jnlc5oixtLCBnbCxfuONa0iR+xq7bHNG0tRn95Xi3IDrGfePzxO1KPvKWueGX1aMTojchJj/8GmrWNUKTGqZV59Dm1KKGbB7KKVjumzRyjrIUGJCoAwgpONAvs0AZO1fX+43G5BX2oG+2PhXs00W2cWV4IU4oQgtm2781PFfcpbFQp9fXSA+hTn5dyl6OuuWgo0offd/i1ihBBGX1YIEJe61X24GpwCZLVWSY1/e3ccWSfcFShzxTol6Jurdxu50N1Jd0gcXlxqXisR7q3WuvUUWGUJ2AsVbzWPprOlUfPshxL8FITSiYI3fbBx1+K/BM3nd+0rwundBrn7I40AQ6WVeLd/KfZUZkJdhUPS0CXnBYESDH7AqMMBUidugESyaDQq0yBTGOp1jRCX7fuBIX67CNVMQZXp9X0NhFGNzDJBniw0/Yt30sdfMVWw8WxAuszXvFJETtz/twFtIbUIII1iG3N1UNgCaFRURZ8Z35JSp1LRo+V/kfiymk2hlCGcepp0Odud+3hyLmGNg0LYJvOpZO1q0U043coHz97HayWRAO/VEy7AXD5h2Mq5EZkySkAVZvRqu6qNwxLdSPKeYiB7VnlELIX2fvM3eStagvF/Mz+IGfY8yx+PBbq84hnVqnLNcnm2Efvt052Om2zmbM2w+XuYDtUx8kHlnUzxZdZ8FzoQgQZT/YcRJ5WxRIQYRvL7NPCzXK68xS3FI2MlEIOz6QSdLBvTtzaMZR+KpFohM1RaruMJzwOVd6izn6rXWB4SP9T35nnohNx6fs/rkxxx8I5r6OdpPPIs56ZUzUnB92gpZ9ttv9K83nsBq439vOyeYHOJmLJFk3rIRjR9geDXc+EVZNx/YLT9PVVm553wMrsHLdthEg+ig2SzhXPzEFdDWgcUwng5tIjibLVa8YBjkcRY/7dUNRWnKvuLNqG7lDsm8H+Ea9nlJfLNoZlPCdGkKIiqdqmV0DDR1jSqfmdqZaZ2tNMS+QG9bEp+NXeTM9459askhSOFzxrvPXOdQUqMIHVqWQqmmTuLO829ylWA9/IfBbxD7mVzS+JNLCzM0WJCCIR2dc+V9yFtmuoxrScE/5tiYhK4XCzncNKoYW5K427EIMDC/ejTn6Dhe8IHHc+BGbq+VwKz3AOLdPMnKn9KkWIunnp2IF25dYajURhjLeVIBUM+BR3ZHqf9o7BabUsKwtg3RsxO/Lt1zC2U51x3KuPtug5FKKmchWt5DszsdTYohi8jmumj1S/MopBoS+UqcaBmtLp9Et8Un6bUJu2xYjYMzx5nFhprkWimqKuqo/IJeyRarpNEFcZBz0FBjh4bozgNtXKmpoidaZXlmvnjwGztMPTaSc/HxSWbtgyN1hiFSwDAr/jGVD1uCeyDOCypcSxEa2EV9pQTaqOlXsAqMqA/AyLHp8u5uFpF0U+VH1PwbpIQNZ9rAXBSAPKWKtZQt1n02OtHau06lgYmFjNVhceWNXpl2ShppdESocitTq0ts1z4VteYqjxtxtNqFKJrS+s9t7YJSrj1j1+fzxCGpWbCqlxvZNuV69pQGCOqFIzNMURf+niAVJhBxlrKvq/iECScjI2ptBQNcwSmIhTRRxoUKrZhtnNso34bTKx4Tuz4fHXx/+bXlmx3Fno7J6kMcYCH2fpLHHa0dTrjih46EaWPCE40mds914XUwX4tzWu4vEheh1Znonk/ztW81OzMAUNEpfEUs3V3bOBxV9uMUzFC2IlbRgCYWhVM8CrkYAwR3ELh4dmj5BNKpmEAOj7ELVpWkiwtbIiu590daLGj5ZIaXXWinw8WWt6kK2V6bvAAemHPKWsRCFg6LGrbzu0eH5jk2DcakJnCK2IQGLuNK46rR9Eh8+mQOxcI7QRXAL1j/fyfuWRYBrNuvmzZYNgbSINguFvUIskHq4+RA7IzrIzZseSwYJevI=
*/