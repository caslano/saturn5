// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_CARTESIAN_IO_HPP
#define BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_CARTESIAN_IO_HPP


#include <boost/geometry/strategies/io.hpp>

#include <boost/geometry/strategies/cartesian/point_order.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_winding.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace io
{

template <typename CalculationType = void>
struct cartesian
{
    typedef strategy::point_order::cartesian<CalculationType> point_order_strategy_type;
    
    static inline point_order_strategy_type get_point_order_strategy()
    {
        return point_order_strategy_type();
    }

    template <typename Geometry1, typename Geometry2>
    struct point_in_geometry_strategy
    {
        typedef strategy::within::cartesian_winding
            <
                typename point_type<Geometry1>::type,
                typename point_type<Geometry2>::type,
                CalculationType
            > type;
    };

    template <typename Geometry1, typename Geometry2>
    static inline typename point_in_geometry_strategy<Geometry1, Geometry2>::type
        get_point_in_geometry_strategy()
    {
        typedef typename point_in_geometry_strategy
            <
                Geometry1, Geometry2
            >::type strategy_type;
        return strategy_type();
    }
};

namespace services
{

template <>
struct default_strategy<cartesian_tag>
{
    typedef cartesian<> type;
};

} // namespace services

}} // namespace strategy::io

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_CARTESIAN_IO_HPP

/* io.hpp
G45mdY7jBVzH+tzEBjzEhvyJFzJSzo1YmRfxUl7My9mEiWzKJDbjRDbno4znPF7GJWzJrbycn7INv+QVjHyP2ZZleCXPYHuezWtDuaTlyriH3bYK11cj6z87lMto09XkGDbmfbyME9mOj3AAJ/FmPs4n+ASf4WSu4RS+xaf4NafyGz7NI5zGipF2jHU4gw34LFtwJm/gLCbzOY7g87yPczifc7mIaXyfi7iNi0P9e5nfcykLRr63YFUuC/VxOTtxBbtwNSdwTahva7mK67ier3MT3wj17U0WiLRfLMWNbMi3eTE3sRv/xIF8jxO4mQ/xQ67iR9zET/ght/Fzfsov+UXYfvUj65wa+hWG87AqkfoYtt/ByPkcf2Bz/sgreZg38ifewp95P+MKRLdfLi5nbq5lXn7AfNzF/CxkHiewBAuyAU9iCxbiDSzMZBblXJbgyyzJdTyFe1iK37I0j7AcC1mX8qzNCryAldiFlfkAz+AUnslFPItreDa/YlXu429YUPnUYBGexwPhGdHhPnbndNHya+jfH2b0i4jMnxexAS9mUzZmSzblIDbjMDbnKF7CWbyU89mS7/ByfsFW/IptQvldwUpsy0vYjq14La9lZ/bhdRzH6zmR3biY3bmCPbiRCTzIRP7IJBazboNYikPYnjfxWt7MrryTvXgXB/NuPspRnMx7OZtj+D3HsWLk+gVb8X624XgO42OcwSf4OWfyJ85m1ch1BnbnPKYyjXdzGadzOfdxFb/mGlbIZ/9jda5nW77OK/kmO3EjB/FtDubmsL3XSriH3b3tpgvPhFkSzoevD8eBhNDOJbI9e3Ioe/E29uHz7Mt3eAPfZ38W8eYDWJYDeRGTeAmT2Zcp/D1TQ3s+mH/kjaHdGsadvIknRbYPi/BWluRdzPj+ufHtof3O4fvn3K7flmYens28rM0T2IAFeTlP4kAWYiqLcRGLczlLcAdL8kuW5k8sw0g/rrKsy3K8mqfxWlZkIivxZlbmHTyDf2AVzuZZXMGzuZ5VuZfV+A2rM3/kuz9WY03WYm3WZx024rm8guezC+uxFy/gGDbgeDbkg7yQS3gRt7Ixd7EJ97A5y6ivl7ACW/AMXsYGbMnGvJzXsBVvZhuOYFuOYjvO5JWcz6u4kB24kVdzM6/hVnZk5Py3E0/k9azCLmzOruzF7ryHPTiNvfkc+/BF9uVC9uebHMAtTOIODuK3TOYPTGH693InZN6D7978aL3aFtn+4VnLKXmUC1NZiYN5DoexLm/mb3k7O/BOdufd7M9HOZ5PcgGncBGf5lt8ht9wOg9xBn/mTJ4ROQ9gNc5mQz7PVpzDNpzHZM7nEC7gMC7i77mYT/NlruESvsGV/IKr+DNXc1TkuM/7uY4PcD0f5QZO4Zt8jW9xJzfxZ/6JJ0SO8yzELSzNz9mFO3kHv+AYfsnx3MPHuJdTuY+ruZ+v8ztG+jUcYi/+wIH8kan8mZOZK6/lYn6WyWe/ZyMW4CU8kS1ZiNewMDuzKKexGGezODeyBP/IUtzF0tzPU1kyv/aAZVie9Xgar2AFXsPTeTMrcgTP5sOsyhk8h/NZk9tZi7tZm0XVvTo8heexFi9gWzZgXzbkKF7IXbyI+3kxSxawX7MMm7EcL+HVvJTXswVvZzxHsSWnsBUXsDVXsQ3f4BXcx7b0WSauHYvwSpbkNTyLfXgl+7E3+7M/BzCZAzmBw7iQN/N1Duc7vIXv8Va+zxHcx5E8yLtZuaDjNM/mGF7IsWzOcUzggxzNCZzMSZzPR7mYj3EJH+dSPsFVnMoNfJpf8xl+y2fpWBI3k2dyFi/ibDbmc2zKOWzFeWzP+RzKF3gLF3Ic0zidi7iei/kWV3M=
*/