/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP
#define BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP

#include <boost/callable_traits/detail/forward_declarations.hpp>
#include <boost/callable_traits/detail/utility.hpp>

namespace boost { namespace callable_traits { namespace detail {

    // Here is where the magic happens
    template<typename T>
    using traits = typename BOOST_CLBL_TRTS_DISJUNCTION(
        function_object<unwrap_reference<T>>,
        function<T>,
        pmf<T>,
        pmd<T>,
        default_callable_traits<T>
    )::traits;

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP

/* traits.hpp
2v/fpP3/zdrv3wobw9tgM3g7bAG3wRS4HXaEd2p87tLnwB2wH9yl8XoQToOPQJPfGp/WLvl9v4/0hbtgMnzAUV4Pq79RLuW1SN9rztX2ewmsDZfBunAFbAnPg23gStgeroKp6t4TroW94TrYB66GI0W2469zmGCkS/zHajmZBGtA8kL7AYz6S3XpB3ZreX0YRsBHYG34qJbXPbARfAx2hqXQHlco0XBruowrXKbhXg7DYYm2R1eo/y2Yrer/bfVfD16i/qN0PKAuTFa5ncrjYD04GUbDM2AMzIL1YR5sCGfAWG0P4uAGGA9/AxPgbbAxfAo2hU/DRKjtrM7HoI90aWdbav1uDRNgG9gMtoWpsB3srnIG7AQHw85wIkyFZ6g8E3aFa2E3eClsD0tU/i3sAreqfKfqv6ny2yq/q7KOt+g8AtoYl/GWmpo/deAp8BTN77owDtaDrWAj7Sei9T5itF+or+OIDeAodZ8E4+AU9TcVNtT7Q9b2Tr+fwzSX9u7vGi8Kk7y3eGEk9MF6MBw2VjkZRsKWMAq2g7VgF1gH2tfbqdfLwPQIut7NOn51C2yo4xBxOs7QBN4OO8JtMFXtu8Ht8FSVe4msZ8fY35L1+3VS0Nkxg7Q9HQqbw2GwHRwOO8OJ2o6NhEPhKDgBjoYr4OlwFcyEa1X/OEwy317l+67Iyf78gf7ftxb5C/8OE+DPsAfEg7Q/p8EM6NXr+uBMGAZnq/t8WEOvGwEvUPlKWBP+DkbB22At+BysDV9Q/6/CevAgjIFvwfrwGGwGv4VJ8EeYDH+GzSFhWy1gHdgSRsNWMBGmwHTYFvaC7eFA2BEOhz3gWHiaeZ/U74mwl8v75F36PLYDRsO7YQt4L0xRuQPcCdPUvrvK2k7rd0DKvEs7fUjb6bdhHKTOmvb0sPpr4dKefq/j+D/AhvBHmKgyz0rmzJPVnI9xHWY35hDmO0yTyzhTA5N9WVT1mSj/ojNR3lkYValzUbLXRFX5bJTVl5GnmD2YQ5ivMQ0uj7K6YkZh8jCrMVsxuzEHMccwkWyw2gaTgZmCKcJcgtmG2Yc5jLGuYIcuTCpmFGYWZj1mK2Y35iDma0y936CDGYWZhdmIuQVTijmE+Q5T78ooqwNmGCYPswJzHWY35hDmGKb2JsLBDMNkb6rcWS7/lv3/5xbPL/QfAPAr9//373//t1irfH9Yn67p9tJmwSy4vKlFY6XzouXC+dPn4tdlTrLqtTF7HmwT+S4z5+WNPrInsNv8cPV7mjkf92GR31PZ9pvmuj4j0/jvLvJE5AdFPt0bdD6t2e+gc2/Z94txpxvVjtmsYhftKeXuy/1xsqxeJxbe3Ef3+Eaez3Xul+sc8/S2mKXCPhEHrcsZv91QIcx06z7CwA/38nsJo51j/6j+Zs3RixJeI2/wumd/+zxBwkr1XG7VUDsNnx6mhqSVHR5z/Bz7Jd7TR+LguN4AM2/8oFyvs3cS8yka2Gfxqpmsxv+t+gi8S83dam5QN6f8kNrtqsIZvqRH2Rm+hXlBZ0TmBJ3Rm+t2Rq/MSfmByO+UNQ6LcnKt6nMj3eZtjL1U5kPkltz00cAbO551dsTa9cOyW1WfG/lL53PI2IHd9mi7GckfnXRcWeYl49wGNoDtYUPYEbaAfWFLOAS2ghNga3gWbAuLYTu4BHaAJbAj3Ax7wBt07OQe2BPu0rGTl+AQeFi/kRyDw2AUcRoO68GRsCnMhB3gWNhJ5V4q94FyjiCcBIfByXAUnALHwqlwPJwBp8N5cCEshOvgfHg9LII3w2J4B1wMn4TLYISXsgbbwVWwA1wDO8O1sBtcB3vA9XAYnAknww0wC14Cd1efp/cvf3aszHNjVZ8=
*/