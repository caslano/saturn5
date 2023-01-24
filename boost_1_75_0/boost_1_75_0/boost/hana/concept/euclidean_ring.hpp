/*!
@file
Defines `boost::hana::EuclideanRing`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_EUCLIDEAN_RING_HPP
#define BOOST_HANA_CONCEPT_EUCLIDEAN_RING_HPP

#include <boost/hana/fwd/concept/euclidean_ring.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/div.hpp>
#include <boost/hana/mod.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename R>
    struct EuclideanRing
        : hana::integral_constant<bool,
            !is_default<mod_impl<typename tag_of<R>::type,
                                 typename tag_of<R>::type>>::value &&
            !is_default<div_impl<typename tag_of<R>::type,
                                 typename tag_of<R>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_EUCLIDEAN_RING_HPP

/* euclidean_ring.hpp
PM0SKRpfXqylowOXC2Du2O5kpZtQxNze9Qie6nI4m9hW/yae7gCmIzK1U4ySqy4/92zIu3+t6ZbABSykH//5w7O5wJyPIzjaHoziyHhSw1Hxr4lq+ejunKmP7ppU4dyxI/yaC9g6XxP40thw9vQXkUKuiynk6RNaISef5lo3u3vmua148WltL5oDZQLP5rmYlbWf3ZC1/4iU8dnn0TIy9TIefjqmIRP0hvhWKLj/5lUeKJ9ONmP3BiOQno6B9FWPBmkxhwSy/CIjSVMv0MOfJFxyPxbDYOALl60WbuSdNh6VJZRc/QW72RU+tDS27cI4+HgqmEZrKUhrKRFaGxlDa0BpR+V3hNqjUjZVebfT0wlUwVo/j1S4uyta4av1Cv/0Karwbif7iYAVRtFkN0omA76oZPJrieS6e0hzgeeH+fOPQPnCJgXw0oZOAPvZ3w8KBjzR4jntRIulvz6fRqL+ip99pW1zTeRVY3lQSyf79VeCttW1aCRJj2s3ofRorVdQelwB79hElNlA5muPyodP/Yp2zNgIj+zMBkS6Rb2a6/Hk6eEv6KZ9K6cM7J313B3a03YVytOFyBCk7pISe2tuVgXb4KmqOIXGSHGnebNvIuaQQ8sk8tO2AWdCyzFrhxKWBA8skUOTfRPk0I2+0TEf34CPwb/UFZwKbkc7xjzVYQtneFLmYWGdX6K0Cw1cFBQ92fTqJYynWTL7qDsS
*/