// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_BUFFER_DISTANCE_ASYMMETRIC_HPP
#define BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_BUFFER_DISTANCE_ASYMMETRIC_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace buffer
{


/*!
\brief Let the buffer for linestrings be asymmetric
\ingroup strategies
\tparam NumericType \tparam_numeric
\details This strategy can be used as DistanceStrategy for the buffer algorithm.
    It can be applied for (multi)linestrings. It uses a (potentially) different
    distances for left and for right. This means the (multi)linestrings are
    interpreted having a direction.

\qbk{
[heading Example]
[buffer_distance_asymmetric]
[heading Output]
[$img/strategies/buffer_distance_asymmetric.png]
[heading See also]
\* [link geometry.reference.algorithms.buffer.buffer_7_with_strategies buffer (with strategies)]
\* [link geometry.reference.strategies.strategy_buffer_distance_symmetric distance_symmetric]
}
 */
template<typename NumericType>
class distance_asymmetric
{
public :
    //! \brief Constructs the strategy, two distances must be specified
    //! \param left The distance (or radius) of the buffer on the left side
    //! \param right The distance on the right side
    distance_asymmetric(NumericType const& left,
                NumericType const& right)
        : m_left(left)
        , m_right(right)
    {}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    //! Returns the distance-value for the specified side
    template <typename Point>
    inline NumericType apply(Point const& , Point const& ,
                buffer_side_selector side)  const
    {
        NumericType result = side == buffer_side_left ? m_left : m_right;
        return negative() ? math::abs(result) : result;
    }

    //! Used internally, returns -1 for deflate, 1 for inflate
    inline int factor() const
    {
        return negative() ? -1 : 1;
    }

    //! Returns true if both distances are negative
    inline bool negative() const
    {
        return m_left < 0 && m_right < 0;
    }

    //! Returns the max distance distance up to the buffer will reach
    template <typename JoinStrategy, typename EndStrategy>
    inline NumericType max_distance(JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy) const
    {
        boost::ignore_unused(join_strategy, end_strategy);

        NumericType const left = geometry::math::abs(m_left);
        NumericType const right = geometry::math::abs(m_right);
        NumericType const dist = (std::max)(left, right);
        return (std::max)(join_strategy.max_distance(dist),
                          end_strategy.max_distance(dist));
    }

    //! Returns the distance at which the input is simplified before the buffer process
    inline NumericType simplify_distance() const
    {
        NumericType const left = geometry::math::abs(m_left);
        NumericType const right = geometry::math::abs(m_right);
        return (std::min)(left, right) / 1000.0;
    }

#endif // DOXYGEN_SHOULD_SKIP_THIS

private :
    NumericType m_left;
    NumericType m_right;
};


}} // namespace strategy::buffer


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_BUFFER_DISTANCE_ASYMMETRIC_HPP

/* buffer_distance_asymmetric.hpp
EVym1sX9BS/oxH1cNLrE4/1g0khRzWe1m1FO2KkH8pd1zFG4v0anFoPqmuSygUREWGJnry0CK2oKLw8hwfdvdz22NG54f+b1b1bE2bflftKt2V8+iJlzVqbyC0nINmxXUkzYOWipmEGH0Nx9zMO0GhP0LLqsFsO2qLTN9D13Hzna5zhgmzzIfiaMMiJP4F2mmjtFTKKdgsqNNPrdqX6jkjLxGJyRqCkH6REfe8BF1mWHrVXKhEmbzR7XTp+u2HR9ECxnTndtyA7UaYqPdRuil45broKrd0+rvRRSlezCIKYJzpa8Z6a3ve3MEBDXGsLj7YsvQEXOylYNZ5bfpZzPG6QAHNGk9xHKlO/sv7JuLEX+3k5UlO7LmeluQ0wWxpdJPO0p/6drednnMr2MDF8idVZOgWJ7BSMFwApfEedvQtK7YXb8RrfAlbH07j2nRNMm4iGTa8sffSpDkANoat/ZRHI01aTdnTO+n+jex51Xqf8NvrG9j6p8xc+xPufHCAGftt83WE0ffC9sqsXRK3G0VPAfGjpmXLLabVUrmK1VyCesH5DEZ/5YILc3SAwYZBj5BhEg9BgZXX56SBeEBSHE8sJPpVBtwfKfRCgkAWQkylLNe1J8nV4HNh4eQ9wrMc6PtERWkdZN2od7XmpKzVXuZUgD51d3PBl4Dl6+fKUf45re5+7kd27mgu2HnjecQD5bgq8Rr/ffkrOUZz8QS7BuQ102OW5Ht54QVQrNn0b7TJZOIJ5Et5Biq99mALFA20M5cs0PQNj7I2uAjcCxsOnRNILO4lTfOIJMTGNGW+UoFxieJI3QotJYCCWw2RZL/+AX2VFnLDR5uOth1e7zY6CNhDuNU7aFh/rOnF1NI5tz9LRk3yXe5aFgtamFm7SW/6r2CR97df/bGQQaWoZOqN0onPY75gc2scNaMjhaZWLF7MYHci77xJL+I9BYqz9HUG0Mq6fQ+F2xi23hagVYxJ0EZSLfQrN2WMf15h2CufTuZciTtWbtVwlL/WLZsQAxSGrx9G/Xe1jHX/du5t7z81XQYJqeaOAC1AJ0BW7RxJnHDy/nD0yt1lMLY2ST6+FT5PRVF0eblRl9C9YJGCIzQCzgClPQqgEX9wm3Y0NAjFE7XYSPuiWwc6xOJfSk1Sbw8RNXGCsuDu+gY2Cs5lU6TjEFuNbZP5wBEwftxHC2bb2cMaT6Q+bC3maBCyYP60aZcT181+GBGCdFTVe4+rODG4DCOhQFYv2UN91hAxg9xSh8mQh0/1VGaGDNc7K/srILyzlWXw4X6ppw8XCOykV/ZCxG6vXftqVEuVhYnFPDCCbQ7cB8tvWR7wGvjeYx+a58Wgl4LLezNlzYU9h17xk7X0g2HvzreDQffML2FG/gL2Adkhj0E8dLaqfw1zctCONsy1s7rz9QryJmDh5EgO69PI8c0/2DlEiWkooIBB4IVGkEFJuK9OUp37MXQc7RxUKPrRMCQcQgB5ILYUYESg6SZi/arE/A4ZZldPMu0U8eB3AvDsJuWFYu+tVcYj6AzQPoDKmeWQD9V3bHALGWZSJvbM+kil/B/D0UksYockl8yJCGzAWivBZPGFmzd1p44FvsZrxJY+UngF7rEghxyhOJl+Wa+xLmVexD5QMn94CpeDH5OQv1eG5HpeIwPbkzzRPlIyOR8fJodEFnrYv5KwPLt/UYn9sZzcI93xNlYZkHp6qbWRtrw+6BiExGj2n4KbUHlwTqC+KgfL4c+rDPcEqfexmL4oXNsGYlkYeyYfN983nc3LB31UIbMaLb2CSfsatk69EqxVGfAjubkQcat3wHKGy/WVZxiBeTnboCHbIyJzWAVD+gp/BkfMd6Kyz0oQ7MeSBZtJ1ZB3Ok0C3X7ptuRjBIgqhUnyJhleMAp1xJ4endZ/9gU2vn4zvUFWUc7FmmYfpXSWRUOaJt3KqYSRp5TKihBsx0YkI5ZVAfHiwXLq91jjAGwIjxKFbfTPC44HOQYE/fMPTySGgZ7Ar7Hq0XgXPNyVOBD0CbiXDyB2+f1VsCPlG/z8UpEre1yx0YHUj227JgDj+Kchk8S42Boj8t6yIvOaiKuJ9oXbzEgPzzh34KjF3kk6YOw4BTBd54Lvj4sVNsCHi+vwJa37c72WDBwYOMCNYEaJ1EfahbvVPNEbluAo5JzhPZmG6w3sRF8T04ywlxlCwndcDT0WBmCgpVWB6xje66Nn6LVgprmA673hZEgp6necNRlRoEc9YX7NXGdtQi4SxaqsgCoIVosYb9vCLKs9+oAw7rQwSBj9XcTWGtdB/zbTQHKspvjUi7F7MrNMYUmgmEXAONouK19SmRra/W6RXkn9e4kyr1ZKJUZ+BLYBFPzkmImgavba/ZWCuCu1eQHqtg3IHlOB3bIjKsvV65e2XeiOWKQl3K0YyvWclGeonlzVd2IM7o4WHoGe4Ec7jgys1EwT9qHR6DBNLE1sTP7Nbig9iY5t5ZGbBGG4p2roP72h7Lkw5dooQKQMoCaXNv6JeL5cVeKT0x7qGwaHm6vpwGykbVq5T7A9bgntzzQEeAP+DCw4PukkQrHy8nYtLmY4m0PNLNLDUQfdhS4I/cwL956UO2kcvHOT9P+2zQOkwl3IYG0iwkJeoxcQaDCzJlgLHS6mFtpESl6GciEUf90ZvFyFv6cItoOM8YwNwCWwF32jpDpRYq/CosDZnxeND+rBHIHWO7ljuLQwXnJr5yAXaOKUhTwpbxeGWZphafIYoq0z3STKDtxsi9kdTKDt6iEz8ULvw5ma3JzRtmQ+s9oi2utneAFMNR0l7NVqIc8pCATlNNk4/aSxUPZrC7am2tUdmfKOx/aXtLRX2DHahG3J1RlZmPqXyVp45Y2yqJ3jkvVC2WqY/VrL4snRlLs/RkGZxCu0KoHK4t1Pno0Qowxt8et5C7wgjxtb7HYVE5z7bQxBNiAPiMpMSwzucWpKg5mDRniDy4gq+cyHC2/KJ0jkC4oj4YJS3SGXK+p8MGnZMxJjlniwlZnxGUrVHoWUP05a43d+vNV48yeAQ2L70zKMUc4RXczaHhAJDh2a5Spd8gkYwXhXQ1HabQ3qGP+CTZ6nl7CTJxcEyO2eQNGC/RGJi0M6hI3epEemfhbMsN2qlyFmWpIfYssexKtoBu3xvYw3TZMmH8nO62o1iNawIwrKHULJpD9thyf3CL9YSemPhwhtp68scinqn+RhtZ12vjRgqrP2hwZcbFwSJm4DgP7Z+CXVEJSugUxZvd6PUFmy4ZK8J1qzpvD/H5mN4NOKX2ok6WvzDbZ80HXXnGiYfrxlSW4gTyUScBvUF5UMNR8trx3LAhCAsQP3g8ro0kVrFY8vS9MpvmXoJRrJDZCPf3a1mKK5208sDmJEShm0gKPVQj0YRrf4HAyhUMPKftCiKXyiSGRcpUz26L0EfNlNE3TLgL4oUmN3O2SoJWXCv7FIfR3HD13njqNXjMPalGGGD5ncyWfS3LLldBvAOz68Z9khK815RQk2IXVQYDKTQebGOTqeQlqZmNWjKTs8Rhs4kc3kJ4YMfUwUvJCIecvGUz1ChwjgP9bskELEfH8KoBcHTCafwUY3vuW0DvdlGicZ0M+rUV4fQKhCpdAGlVZrX8ZwrSUVsK9XNDxvVJncKDzxQicQsJhXkccMWk9VAJF5q85hcNI4Q5sny71zSWWV8onDS7+oE1YZigNLpoCw3DrkNgF8Cu/87mSpSMCQamMu1pTzxknTDQwb0LAA2N1WH4njIbjaRlnGsEfsyEP7Vf4jx3+cmuWi6WaP/sRaFvHsXzp3jrFN39EgXY8zR/JQ6jAvZsnVW4kzq4M3Z1bTEamcPprepbBPSwxrxkXumwv4zVQDq4LgVrNHDKpavZ59rp0HCL7Vvfx6EIqw0wroWx9N8Z4P3mpTPxauqaSeHaGhVc8OOCtjWKajNwroa4rCbDlS9crD3x6nUsuCn/3nWCp9P5b9xcKAZ3g/2lWLorLnl6z2NOu+PyuW/XynHUyWTMjXYJ3/iks+tWUvm0UYNoYUSHlPElfV6X2rSzGYJ7DnHHIPRXbxT7+7ZSaNoAl3YyPdoGBeX2c5YxffCyQD80Tl72WtDz0ozak9DClZUT4p3ITrEdHCYEcLF+7iPf1u0SIAA/km+GWFgo8pjPTHdqwl3dD6yuYsPq4Us2jn1NzpaXSwLD6QvyfYxohBtC8qA6T6HdzSjPcisBUB19nXy4VuZ6i4eKjOsGfe4pnid/HeDdRaBBz8izQH5UwbK9T9/Q4k7b5az0tqGR0qFOJm1n6+W0ncCq25NkVSWlQ+QJD0zYmOaAd23v5zUFk96/lfc8jZtwXt1aPH2v2//avNPfc6oEe6d5veO9cgRfwSLJyY5zeADzAPvCctQe5mR0e2k7e21KcvXUdJvQ72I9RK9VG7x/vCApRy5y8lriPlNsb7GD9zR12o9tEz2AIdxljJJj4llOMzpeKj+BQSq0ZhV6nRKVH1DHGGtxAxfKebL9126cuEmJLBI3fNDZjbPi9pUW6z3atbDc4lDd6hCbyZ7NTgHIzpyKmwtva/BPGU1jEsXgbaQQuMbRj926g7LcewPRe+Xp3E76yS4SPnDjTheIGx3mF3FWiRsjeIMzqln0J39Ujt1AttqEDh8vkFmR/7gaqkitJDBF9lsAbN78qe0IPbQcMSvdzeyUCTzFTU1dWXYXmNIk9IvLnAqpA78OODzqsb7jGgBB8nRXHV9JL2+b1kjmVfRtcDCQcXp+W3Gw8LHh6BRzPG90+5txurPFS4i3Ycd5vq9B+TcQrEatTaUqJ7PCA2q2EVW53uFRxXTHrzVQGAqm5u6C46POQ69mU2OdkMijxbBs94OmNHy6h1omOo2A3BWK2QDGo0Dtip8DkD9ESJ9yXQBIcy8jKnOwT7mLcsnrVbG/ENJzwJHNRnLVk0p0mgPzbAdIhEGJVgmnzxItfdzF+Bq16vijQPtWDhFZGmp+Ba+lr69mV9j5ETq5UR+7w4IDUZUbOPrxcmYdNNBfKxANG8jlSYfgXf1JfeOKuVkp/alRCU2/jNW2NBAuT0v9+NKOTeP2Y72CEBzdfWSnbSr91D1uLvb+FH2agjzqT4i35CdI2IsGexpICSHXc0b242Nfn6lUfx+wovz84+bX2kji6qnlUaT6MkQoqGgzsVDZ39t9Sm5bdiBehkD0i2lyzHo937HPb+ZNyC8sCyvbp8F1t5DNsPJaLQbbee/ky/vvScKVVmZs26X1T3a0/lLuWHTUyhaCx/VN7iZUfHoeWZ2fLyMXo9L6frwaVwqPPaBuEy5Tu8eulRdMxIsVy6MOYIunMj6u2cjCRSbfmm4AyO0ajOm77HXkMuOtu9HFN9aZQDtBcsJmP/6Qk5Gs5O6GVlebqhTTjtL0TXtWd0/hJLIc448Xh43PEjrtHnxYKObRw4MzncB8tm8Rx1zZ6sp9N1EoG8ET7lBdyw0KmNTLicnrgAxsb+muAHFL+oue10ND2UoRcOBNQddry8oQEpUlG4SKOzYrslcOoXddkvVbJYIGIJoIQ84kvPdGZpZ0fQUdQQ1V7ZKx9+nIGg9j4fEBdiHIg11ZGnNxOJ+GuhsrhGv+q34+aquq3hfK2/jGj9yLokfYmfk47MyYWcU9TRersEuzZHNrg6gV9JS8QtnlWuSOIBhC+wNkTcTBSFqotYLDLzs5w/jHA3Z/Nr5/nCdxAi3B0Q1/GjlDg9vJbbS2HHOLkpfZvuu32PmjBWqSz8EypBlmRFIzOwb2A9hllCufPc1ygyBdBHaGNr+pV9mXqAENFAfX2PYDmk2TZw+IulVBe5N0brhHMWi6qZjhao3JEeK4lClHug6P6bbYpN1pgrskk0nftU0ILNFg/RECVpxtdmCwc+2PPKuhVUMHoOsCel9PsziorOLimcxTd8ASJMXCaD0ctEVoJusASO0Ir1pL8sc70Vb5fYiulmTlElvfSW4BDbncx5//+khmRtaoMKcymsZ5NMlMLilrfYniDY+vnMMl8lLwwE4ci9fa0tcdebSVXaZlJTJkhRqcSwX3FjljGzIP9RoaWrzx8Ltyvr64g136cQ7tW+ErXtVkxZ0u2US0OAAFLPrTcduFsurvx0QD7+y3vgue2WnNji9eu/WZmT4c0A00psbCbvQpsTmX3MVfjPpT393aznl3nmur1PhNjS+VFpgJ3fGzg9oyTVUOqCiimLbx8wkCnYPhX0DgDS5ciP1wXoEgdTZFZdYTl/JNZ6dbV1dkiUAHplIMarRGWS4d7iC1jaNMNfzoP+tvNYaxlALkfMeVzstPq9fBhWKo0lCJsLPOI3bJNi9wr10T7lboUpG0RITna9e7zZLAMuwwXtidwiTKBcrABA68OfGzD9TujJIF3U0Z0vXF5Rx0dWHadi2BRnx9hoA1aAb6EueB9rVGJYMAb8zd+LFb9oOC6eJxKhPw/pVHTT2DUgaeXSMZ4B6+cD7KsGpNDIoNELlDf5Dfo0TiQlKrsAmykcdJ7g3a8S0D+AAeEaUFE0BWiCil4yJbvUtEtxW8Xg+FdakGH46dkH3hfOorjhK6UsZ2BFK9bVhzHuV+35vQL4ucDsafIWk7EgO+2a6ZzCGsiK6vLdkf9qJNwLrs35odHwHn3ke7YsMWeR4Uy6/nbdguxGL7TkFIDykvUBepKwGXNERb1MG7g9U4hb15Ue+o3cnxci3hKR/zduznJKjmtwmRdfKbXrfeWi7EIqh+ojun/CqiMMROor31PGkvoslTOSlNmUCnnZHO2dxG3Jmx35k/4aHd3a49yciZaTybfiTfce24zjSj7zvpuDlZQn98XEGc5tp4brwHR99JJC6qpJu96RT2GF+vdj2e8V6jMzEuwiulK/JG/qGX8q2SOlnPasdXo5QtrcyawZiYestxk+5iUGrW7BHwMixacNoS1Fhntjg9pUx69DBIzOuqFAfXjFVAlW21VgR/q+bhYYGvXOAJy64+1WDOI7DSOuW+oNs8evbAfu/UV+L/rBDC1+5kDJ61hbvPzj7V6Gg028LRfPaa4tXpTkfaCczgKAFhQwHNitYt79eccyWFGtgoPMJ5de8iGMG52KIQRgZaEoCMV8qO4jnvgSpdccmci3hWdoHqe4mjXKbGrpFZKeaSlqMFS4Z8zljApZnfhJWxgzpW4uySzbA86uYPSj05PnscZYlHdQhyoO0hBqFxMnT69mHVbJGvLNO2o71FQIMU84mm6qmuvFqNVcdEIGnonY2NhOCLVuPuvaPOyq5NgdHOg20xlxJOEALgAKWSBc/ez2AWInvhpdHMJdvlpRgpCWnWjIy0ZpZ6AagwzsXo6Us982vEGB7zPIA6nHOV/rrnmEOpBSFBV8C9J19NbJpYt7+6NwX7wFwlhGqcE8V1hRwFIutTbcI+d3gHHZITsRt/oY1OAg9pXJKBEElvP77NyAEH23uAHtTgNDfIaNeAIcUzfkNWTnW3lg+sNnwximXtAKEDYKHVK24PS7kVQ5y3GDgFgqwVKtVT+bo1zeIYAXeeKxRzBgStYIhV3lEG4OokfAtrR1/OP5mj9Vhw4L3OFthAtxYXohOkCPEysDeV5tM/SpxQ6Lf0yxz6p6WzLhfDk08x9onEu5vljtN8Dfx9BsaIx0kOeA5B24BZMLqQkhzSLGjf
*/