// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_BOUNDARY_CHECKER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_BOUNDARY_CHECKER_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/sub_range.hpp>
#include <boost/geometry/algorithms/num_points.hpp>

#include <boost/geometry/policies/compare.hpp>

#include <boost/geometry/util/has_nan_coordinate.hpp>
#include <boost/geometry/util/range.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

enum boundary_query { boundary_front, boundary_back, boundary_any };

template
<
    typename Geometry,
    typename Strategy,
    typename Tag = typename geometry::tag<Geometry>::type
>
class boundary_checker {};

template <typename Geometry, typename Strategy>
class boundary_checker<Geometry, Strategy, linestring_tag>
{
    typedef typename point_type<Geometry>::type point_type;

public:
    boundary_checker(Geometry const& g, Strategy const& s)
        : m_has_boundary( boost::size(g) >= 2
                       && ! detail::equals::equals_point_point(range::front(g),
                                                               range::back(g),
                                                               s) )
#ifdef BOOST_GEOMETRY_DEBUG_RELATE_BOUNDARY_CHECKER
        , m_geometry(g)
#endif
        , m_strategy(s)
    {}

    template <boundary_query BoundaryQuery>
    bool is_endpoint_boundary(point_type const& pt) const
    {
        boost::ignore_unused(pt);
#ifdef BOOST_GEOMETRY_DEBUG_RELATE_BOUNDARY_CHECKER
        // may give false positives for INT
        BOOST_GEOMETRY_ASSERT( (BoundaryQuery == boundary_front || BoundaryQuery == boundary_any)
                   && detail::equals::equals_point_point(pt, range::front(m_geometry), m_strategy)
                   || (BoundaryQuery == boundary_back || BoundaryQuery == boundary_any)
                   && detail::equals::equals_point_point(pt, range::back(m_geometry), m_strategy) );
#endif
        return m_has_boundary;
    }

    Strategy const& strategy() const
    {
        return m_strategy;
    }

private:
    bool m_has_boundary;
#ifdef BOOST_GEOMETRY_DEBUG_RELATE_BOUNDARY_CHECKER
    Geometry const& m_geometry;
#endif
    Strategy const& m_strategy;
};

template <typename Geometry, typename Strategy>
class boundary_checker<Geometry, Strategy, multi_linestring_tag>
{
    typedef typename point_type<Geometry>::type point_type;

public:
    boundary_checker(Geometry const& g, Strategy const& s)
        : m_is_filled(false), m_geometry(g), m_strategy(s)
    {}

    // First call O(NlogN)
    // Each next call O(logN)
    template <boundary_query BoundaryQuery>
    bool is_endpoint_boundary(point_type const& pt) const
    {
        typedef geometry::less<point_type, -1, typename Strategy::cs_tag> less_type;

        typedef typename boost::range_size<Geometry>::type size_type;
        size_type multi_count = boost::size(m_geometry);

        if ( multi_count < 1 )
            return false;

        if ( ! m_is_filled )
        {
            //boundary_points.clear();
            m_boundary_points.reserve(multi_count * 2);

            typedef typename boost::range_iterator<Geometry const>::type multi_iterator;
            for ( multi_iterator it = boost::begin(m_geometry) ;
                  it != boost::end(m_geometry) ; ++ it )
            {
                typename boost::range_reference<Geometry const>::type
                    ls = *it;

                // empty or point - no boundary
                if (boost::size(ls) < 2)
                {
                    continue;
                }

                typedef typename boost::range_reference
                    <
                        typename boost::range_value<Geometry const>::type const
                    >::type point_reference;

                point_reference front_pt = range::front(ls);
                point_reference back_pt = range::back(ls);

                // linear ring or point - no boundary
                if (! equals::equals_point_point(front_pt, back_pt, m_strategy))
                {
                    // do not add points containing NaN coordinates
                    // because they cannot be reasonably compared, e.g. with MSVC
                    // an assertion failure is reported in std::equal_range()
                    if (! geometry::has_nan_coordinate(front_pt))
                    {
                        m_boundary_points.push_back(front_pt);
                    }
                    if (! geometry::has_nan_coordinate(back_pt))
                    {
                        m_boundary_points.push_back(back_pt);
                    }
                }
            }

            std::sort(m_boundary_points.begin(),
                      m_boundary_points.end(),
                      less_type());

            m_is_filled = true;
        }

        std::size_t equal_points_count
            = boost::size(
                std::equal_range(m_boundary_points.begin(),
                                 m_boundary_points.end(),
                                 pt,
                                 less_type())
            );

        return equal_points_count % 2 != 0;// && equal_points_count > 0; // the number is odd and > 0
    }

    Strategy const& strategy() const
    {
        return m_strategy;
    }

private:
    mutable bool m_is_filled;
    // TODO: store references/pointers instead of points?
    mutable std::vector<point_type> m_boundary_points;

    Geometry const& m_geometry;
    Strategy const& m_strategy;
};

}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_BOUNDARY_CHECKER_HPP

/* boundary_checker.hpp
TRqXwArRE70Lxfl5IaV2Cey9epKMJg1s8bIhfpx06nm177anb4gyjJ+YgHk8TiWFA1qP3Kil8stttnrHkcoMBJw1EvElTsGFtuasumNaoGv6Np1Au+DbzmEHrIVmrx0yYDgqLbTxzmFGxde+KX4kQbD/E+aLfvYkk51hR87GAOOmgZN2g06ZrTT1KU1HYFUpFVQuIY79zJIbZai9XQ6qpHk36V4Kb8C4ZZAGCc9ByHUyHjuwhc2FaHZOlu9U7ZIikuDBbNWTR2fg16GlipfhNgODGMcSyZG95R6RvvAnncCHC2mPjciu4CX4G7D3jRaS17eNOoO6o/0IqaCYoLFvbQoeZrfPBjVtvO1j+eLsk7lNEo7t//GxBbFCqjsG6hz1QncjfoO6fGF9hES0oxZUwsL83pebEOH3MKHNo2C81n/LNh0WmfwuJjC87CTbOVhqLHksOnW9/SVzR9AIxOWij55IikkZBeOhY4cEO10YU6uALCdFxyJci6HQ41hF4QMNeu3rUNd2uIewrFCXAesy0FtZXYbBumbE1sViHZn5xLP7vIGEOW0Tt0Gtv4fPyXss+LVP8BUfYXGv5TSIrC+UfcD2DeOE+7hOZ9spT1cs5DrbmbWpPlXXnOJTE7wjSYkZGHeJCfTs7K5cp2h8sIN09D6Gub67fM1WFfgnSYabmTuVxSalmHJw6CK5uEieXmRsXYxl15tYnt6GdNvrakMaTDtj9qB947i+E7wO/tlIvdn2+uC9BPUdbLNiN/WOjRRhe1371hnzIryE4Cx9xq3tir2v91OmrrQ76QMtCQLL4ttEBVIoyb/wmJygs3gwu0Mfd1miz87pUVV7N7F3w5IwRS+Jm1YHVcW+H54s9RepHZ+IZaRUUn/ccRiPA/bTlI/Qg6CbFO+HYhLb/QUdIa6x8rAyqMdffKTMiQ3xgOi5h56YomMtgSYaX0VdyCTboCBt9oIzMAI/HzEFRqjew056eroOeO9hDBGjVQsxkU/fCCFhfdtPvmOGWAMw5dYDd4whhSbmcVN8xHdaBQETNFCT4rbQZceTYqE6MMDCxNzIJixix6EoaBWQ/TByMH3tuF1dD6qIBYu5FkSF3EbRm2ErlryXkSIr3PQaSVE6PpxhKzbIVwQNpMKQuyS9QbS9V59GivJ97Rn41m6ohSRgfJy6n+wP/g0koiGMl+G8jq/5duQ7jTs++O6TRvrwuhPcpzWJNpfDwvhs2XEV+Hd4B8fF1XtLOR7C7kAZrzq3KMG4dSfZ2TnoaBYik+hBfmwskUqDv2R8MNFfMtb9In7gSaiszh3jTfJ1iMGUapKbuLcaRuJkVfTNMXjzgPfk4NXJznzZkn2gtd344E7/orE6v6GsmujwYbv3pH9uYqXv8MCy+GR9Sb52SzDR1z5Wa6kEFbSLwZHVBDhaApb7bfRNid3s8n5r3C7Br2xgvp76DR3fw9fG7V3+Al0SVBOvt5nZ1oFCPR0zgP4XcUk4VoeSBJbWkm79RXwWDpZI0NwLw3zNsSRhOIXQxDyeiw3AMGUtGbEWtD3ZAEtxNx01kqlLR+n+sjjrqQHz0oCg1IlRFt/jdPjnmbyJ/nmScbuQ7/SIaqoTyB10WMymKiK0MqZiIhc7y0GPWJim2E8oyaSTuVzBnHZS4XvmwAVXJ7+LLc4CC1a6iXRGLdk/3w770J6OTxKZZ2KhQfNMvEUS0DuxSmo91Lwa3TJ20RtZsf2wmXYcTvQ1DQjyGFJqIC6zYpb8JRZSLwWNxu0lJuI2KAYTEBKZ9SKf0DHe8S/iyFbnliXAmtjr+8S4/vQIbxKavxKyu9BHxG0g3n5lQYKYWyGtvR9kNcQnhuVdFXXWFlkKRI96bjKwJJOZmwNi4Nox0cC7S+OVexRnudq9i36H3g39SlMo83uyC3Z8+p8B3rddtHOADZkDh8yBM+C75YRAvCFgQa3tzbNJNwiZ8Nq1iHwLgih03IuLptqXe5d3RMB+guWpSCa7M/fqigduJCHvvtyKE14GdiqpsHG0MxPngEdQU9ebNck7id5RqrJ9hnwEz1z0k+4eNfEUTADpVNDuOxA9jaQplN2VfRLYpoLIAP0kQJ8d4K1R7CF/ITaoEBo0+y4v8yjJezY4CzqQecrlxuNy2gKF67wSK50ePBtddLXKABmhrdZNzNgZckAdNm/f2ocZ2Emfz7BJJZ1DJqWsPPsQQ8fOrTDIOa+EWC5YWGhPtSaxC9LvVlPNPJ13qhOu2/n1bESBwVHoZtJXYesh2ciEvAGiKwehNJ30+5prBFhZeH5nQpMtHphpKZ5iMKeO9Pv6rDjBJqAOZYEVM1Dr83vduBFWoKecfvJyqwVm5sZ0eGqhh87wk/oCqzVQYGXwnqjpjWRncKJvpdUgwP9MAryQVu27TtAWXaFo3F6VADcz2upB4PcFpGpbt1wCrAl/HW0NcBOv8rQ7OW2N/I6xFZM0Bq2+71X5at9aKNkreZJU2ZoW1IPmIlvNXHWBok1kgdVAoF6Ss0ktsCLebhe0JV3Ab0vh4XR/gTXdCd9Md8MoydbZ8C8Dp/Z2hiIsZ5Ll1nQ82IJ6rAJsjrMQrhA0nXJ+nmgrsFq8I5XlVlMwCQo2C4lrrfiuWTC2mtBQjJfyBNQWbqzB8z6PQNP6YLyg6nI6FscBhkxT2+MB3PJrkEO9z7JSLylwtR7iAQHA38KXmm1vArR0NWlDFJbgZCXZuL1QrGYpYhHWZMUckP1qV5F9tH4FfLEOY0xg/+k2bl+PRvtqpkzii9fAi6SflK5C4niZYYaL8Jey6RE2XavIJmZowSOLehHUGmhE62roYxVvK6ktCGbSvAUYiw7j/G3UQZnZx3JoCvJIovAyVCeCl7xTGZc/GGjPo9Ysv/TDxpUI/C84N/ShAye3EL2mtFixKeUut3bD6W+xPgt3VmKuCQGtR9iUJjPxpiFd4ZItsOYbt9st8Gsmdiv8zIYVDT8W2UncUjURlEVWmbhF+GmsBt5ZDRdr4WI02YeXzXBpqoaKEUO9mhSafR2WamWrlfFguI2mO/9aq4wLwfiqO8X4auFo46tVkvHVUkPiTngB5wRauYmJjQXW6WpteuIe5TErQ87Zyh4rm1m31NS1QFecOpvSxbrJZJLv9nTRtwtxxoHhqqnWpz5p9OdUJh6aVpEOXUiHd60a7uYCazqdmoOwTm13YtTMY9Y2LHm5NQf+TYd/WdW5MASyIZ/9Glv/D6dB7y864duFg5QHHTDZ9hjvYdOjN26vFH2rrCa9b5cenhbM0Qm69d5ZBP+Yjot6l8mFdcKfOfTmbJBFcY3ln/B8vTRztw6K8st6HXBceBzM8qTRzdUgBzBDbxpZZC1QGBRNkRlWgbVaWSKiD3yRBU/RkImwJW3ciCkFoNi87EPT7OkboNEDKlstFuTHfj5mZU5UjZb8+RNmIFwOvwj8CS1zurAk2lGLeQAXWM2cd2TuNm5/79ShCYdg1Rdln7yse1cLGyedIltNuTJM4ebnsP8LrBkeHZ31Mc++8DucQuAlyCas2V2cMcEopsE6Y+bmcqTDxxgk0TXZqtvPC8XpXkCKatw0HUFVoQZYaS7MYE8PgurvuQhNUVDkIrXeCmz8EuDd0GTlnq28ujT/fcignfTAzB7oA4xktXLPI5xhTFfueYxfZSnMwxmGLF2QU6C0dOBLCIF4Ui4jDiv0ZHb2SUXngCEp0jor0Ftq2cim4WHE3JkYEU0283WkICghZjJZRvgAZ79BU94AtgDcKR3rm+1LB40x+OyQYAFSIrrpXbPxUAk24dQiBPU3CFpMhhgrH5YdBfmwD1sirxxWPmzH5BfjPk+KDdIehNtZcC64HY/U9hi6LFx+lFtK+gL6zQvQUhJwiE/ABcOOMTMQGUlptgQcaSksmzEKLvRmPNgNyFJAWL+AmQvanWSv4khn5zd7kLdOIt4+UpKerdr2yXrGCKG49LbSlHfw9LkPhJmfHU2KxxOzhM08ehcdf/sJNQ6q7CB6BF7XE7HsYHs58F06cE6tFmACdNajX6kBPfaCZsIlPdUTV9VqKbs9aCElEuO5RhQWdOycA50I0bXlSNwhBTvMQZ1sowMIYq4UHOV3IurL17k/0RA6voZ/l7n8q0W1Xvx/g/ZnEaBIAIBDS519D3xUxbXwbnaTLLCwN7CBRQIGWW0UaoMLmHVRg8mGWEjc/NsNSgJfizSu9DWSuxAlifA2oVyHRWqxte+z1dcnFVvfV1stRKsYCE1AESlQGkqsWKNOummNEiFI4H7nnLl3s5sgr7/H77fk3jv/zpw5c+bMzPnj4ymHPlJRi3W0z5J4Nf34bVYynzOy6lv0ql3HqlFFFDZAPOvwP2F3dRfbP+qGiH/dQDL/0lF63pgoicTH4hNrbFbY2HXhxm7vQwMq7d6e96qqfvLC5Qfxq5zaafABLmMqzzAUEz9A/68fJhuCTl4MuRIIM5k/A4Iq39QzcoC1MfnxT/6pXl2Dtl/L+V3ImaBRhzIfeqpvTc41bIx+T6kadFeb163StEm673m13qdUDalpIFZ72hvmumdgcAO8QD0iTqSiHQGXikXS2WRSMilT532JF3OLPU3mtdEV6gKlWrNmguRlygwomiKKMu+gbpYFc+chnDvRvyWj+6fwDXRs7GrDjU5u/NHEmyvRZVxKNA2kWH7XXara6htPE8ASvsMAvcBTtegYmHEoCbraePGHySPvNj93HQuwC3gAJPq8yF1hkQc8++X+MubAqzHXIbffCRRse3KfPxBZOiapxKeWSayrRZUnhjvseIZMVgkd8+5ZFvqMtaP2fRxKcakJja3BuvnBb3ykltn2/GVfdMJqxZf9WIUU/tC4xXfLYxV2pTKTVWVu8blYhUOptIOUpvjMrMKKeh1OpXAO+ZwRzmccii+rMzcDu3Sf54I8Fp4xDixOh4oMzx/l1HBhBqxj1oTgd2UwLqzLc16EMTrfbsg0oBJtCnCZdSCvH30O1q0HbXvaMZb3fYXyNzGc+MJC+a4w3xCqwGuPd+VivK8EKugDKihRJRz3TtnNLAF1AYyf9n6jRgczgfQk4P7ABbCNidpnC6ILVwXlDoABJo2cvulDjAh5/jiIFmPI1M2w64P6FcMWemUBdZ2d3Y5fUX3V4TqtVNvxySI2iEq1A98kpdpCmq1KNTxa488jIhWovP66xWBobpOnwnqUjrLZPfYH27JhNbPYVyspLxmjSbeM8GSBxTp4iyg2EYsUYxEoYTYVWK7gXbCMfJ24V1htmzEwul8cSS2Gjc/GhRZj6A6Q2Vi5Q2L5DhBmLZH8JFP4zBBsKfD/hRaTvBYzyCaz6TP5O0C/8rcQWdhvmADRCki07ck32cOD4+W08OAY2UrZHWbTekv0pqvXbQhN1jOjWjb02mHnH6JJEAULCrdnexZbbf+OsYpHRhuKp1/L12GFrrAo0mqgTEHBdiJfBxEu0GYmiFI6wZpH0KxSmJFTlAm75ooMjXyBxD2fEb0mKbUWoGVBuvXWxBur7MQI1/6A6zT7EtaoxhPAqsbStO3FOKaei/LnyKm6Smvm+IhTdSGn6na1/epX7qruhvXM2xVMUkI9StVRperMfUoV39uzYHd9pLFv585IxZnSSMXRUnjoKQ0adxLBWqE0Buw9Uz8Pd+fMhwZnSey45626SUyyvVl+yxzWeEKxP74Ipn/0DEMnamNLxKBBKZ/+1IXngDqb646pt93WnjzsBjlY01qNJ/Hn3kvGze3eIZhmkcatO/FE17rT9mTbzp0d3k/pdl50+a/JwNPOKaEzqL5UdKaE2DPs7PGmR1K8Bz0djXS7AIB4OoabP9i7MxkjO/NInR2ozNbyfbqWO2yIFB0uqckAxJHuClaCagYP3ygcrR4e7oJWaVyfOntLkvHo/DCgv8xR6o+UWUsRfRTYlAqfe3gSCrBTMBuV6bXCY0deBm5trRp3MMO7MXx/lwEY/TzUeWF51nh2f/TeKCkcLVO8XaiW+zovXiicGrcWTkK+D3tbxHVo2igQaSnoRZcHivcAxmRF+6eN9+LykSdpjrKBVxW18oseChaPH1p/ptUa3gA7eyvsVPVD6megHcXbg+6RjnqWWG3hYox3nCd1wErz4KFslmc37WM+1KD2lDltm29IAjk9XG8fb2uehleJSzLDF5JCPlbEw/tM4Q+G2Gfhfanw13VM8UlQWIEELzebvIdBSL9g2104pbQE/p9cotZKtj2FdvhrUSpOMG8PD+CpV+hE78uovnbBGAqxiqOvIkddPQZ2NUtgq3m4M98oYXfYEoBvrJHV2U39GNmDn0egizjzS5GlFrUwaDh/dNbBkkj+WJNSdMK2u3gKNFo8ucS2p9gOfCRSnxr+ZKi0BDiv0kjwKY0HWT8FXNvY+Kkh5EX9ynORiuciRU93ep9W0F2l91mMlqmEnlNCu/gcgNUdek5OJeKOjnWHdsnWvVafIPSdROAw/t2GoB2GKJWfqaTAG91x4/MKv++24fG5I10bn8ZuA+wJG4/CopzOQl2j12W1TmLzyQTipBo6EP62ZFBPLut1XVbVSGgrzEnYTETqzcx7dCeweIAEMBccfy/su42IxBgGN9hNg4r3MGy37DDD+O4kgcCApIa6CYeIQUQg4qs2NfzxkL+EcHkP4vKeySWl6KWi4iAbhLGDOUhYDLXxP55X1d75AI1tj88e/nJ86IEYGsbwU4FRaHiJl7uH0eCdHIeG6wkNtmZyknglVPT2Qzt7t3h311Oow72b8ADBczJkUnMlItxX6YTBXWgPjWWFEoo8wMOx642xjr9BWro8Apskdo+Eve6P5M/FXgcNEV9q+G9DpUqF6F1Fm213YIq/FP6fXApdL0EMYPd59zm8fzkMbYa9PfMU2WKmS6SMRb2/wKNPjyHkL+P9X+Ah7sGWtofzQLLcYF3nSOzUYujVMs8G69p/XmmINT6wbFlLW+8FPBw0deSajeFv40E+B+SO4w1+4gEWlCFf5JdvBRlyxxSNl+RZKJbxDdCsbfNrl0bic7jp3p+SeS2PBZ2HZ2hWdaHeQUUX3/4FnuKHD9iBD44HOLUQrBukZQCprl8+iqt28J91DW88N9ZnGPwB+XpWa3WpIMTYWa6djQ23WdwW2bo43Jbtubx24Ja26HTltugUBnP/ITRqZmMj+dmq5+D6j2YfUca+ZNQNf15AFiGbg+bK9hdQFgx98QKJY+ZgUmW7bc/B8IXCR6fIZ+BtNjxPWp+qOiPHHSfrg5bK9k29ZEvnuFtOv1t+925UOYFc8ri7ZcvdcnIU1tvc9mOQ9xHt96u43yNxv2Nx3/T0d7WfXl5/17cu6nprbJDXO2EOLxt2NF6Ce4Y9J/Hi30pHz75AiYK+Xxxis60NzTrtWpn2E/O0/QRuxBuHxDLzQDksMwfsSoE1Ogk3Fr3zgShemCo2FmiwZI3bWkja1uLsyeSRoc7IUYa2rahhFuF3ObaPUtNwea1Pw53KLD+3nMXbC1hvNWX92NIancNSkGhB9IUUdQErlpjfym8/SxdDsIlaFk8yK/Rgsq2OogTbkDJy/L0g96IaLp6DFh0u2MKvKiJzDqUpiwJHa3GkxTkenfkoTT6lqVxpqlSalitNK5WmVUpTrdIkK3vxGFHZu5X+pxPEvXSAuPcp+v9p+h/Pg/jU
*/