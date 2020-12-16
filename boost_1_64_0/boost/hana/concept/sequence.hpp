/*!
@file
Defines `boost::hana::Sequence`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_SEQUENCE_HPP
#define BOOST_HANA_CONCEPT_SEQUENCE_HPP

#include <boost/hana/fwd/concept/sequence.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename S, typename Tag = typename hana::tag_of<S>::type>
        struct sequence_dispatch
            : hana::integral_constant<bool,
                hana::Sequence<Tag>::value
            >
        { };

        template <typename S>
        struct sequence_dispatch<S, S>
            : hana::integral_constant<bool, false>
        { };
    }

    //! @cond
    template <typename S, bool condition>
    struct Sequence<S, when<condition>>
        : detail::sequence_dispatch<S>
    { };
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_SEQUENCE_HPP

/* sequence.hpp
sgsrh8cpc4J58Zl8ZdgjZQEwA1l+k7x+Uk+YE5l5pxa3lYVq9wuc5h4lNYNxfpdsSjyWusDy8/1Ot92gLAHmTvYsYoA8ZwqM6zln78w8ytK1+40fF9VM5jrR+JwoPe/VIKkLzJtsXpXXVaQuidr7tu7AVVIXWAGyjcvemktdYI5k81d3XSB1gfH7ocK5jARlkdpzvired42yGBjnd+boIAupGYznM+T49DryrtLu5/9q8EFlSdo1o3q09JN6as8yutu0Lcoytbo07xxRQmqNKbbm3u5fLrk7wficODDqYE5lvjB7sj52zrmlDzD1/7mQPUtJf42TmsGq8q/jbkzpIbnD+Nv7+biLlvIuhnFdOg4I/yL7BzMjO94mWHp0Hcbv8Jk3ckl+qTBTsn2B3pVkb7Vr7vk45arUGlaG38UPdsRIzY4b13OZ+8pcUjOYgWcieraTMn8Y78pKg9NQZYEwS96j8Z9+yVzDeHavb88t+xeqPcs782ryzTcMxmdyp7cDzGTmYfw9uPy38z2Za1h+smbF6gQpi4fxnNk99G0l32cw7sPT6Y59pO+aTVtb3V76DuOZyJtreH3prWaTl27MlN5q1tD/exfpH9WzQNZ/3pfeTtk7qkuWPT648IHsEfUoy744BkYqMzuBf1KczZiO02THYOZk1XemlFVm0OLy5Wp4WJkDLPs5Pf5nPW79mq3MTbtmZ7+ufsq8NfP6uaS6Mj9YMcoh6PCEgspCYEXIlpq4HZC9hXFdPIf0KKcsSsshbMeGycoWaHZs8AzpUYxmhw+FZShbptnA8zvilcVqNuz6dTmX1mrWcPRTOZPjtBxcG4YHyuyekPfD//OLl++QJM28CoSvVpYGcyUbl/xspLIfWh9+5VxbSWbiJK5DcZ1XlDwlPYKVJLPqc6mn9AjGz/Ih8MWfv2sCcyKresnVUXoEK0qW2tG2rrIEmBvZ00J7rsuOwXJSDh3nHDUoS4HxvOwuNET2yATZuJPV7u4i72kPmDNZ/ZnrrygLgBUmK5l3bpqyUJg3WZEpS6W3UTB+lr/b/jSV/GCeZB8/tNwv/dPMeV+DrdKj0/i1Itk/GT3HK/OF8Zz9GGV1Sb6hNZszo9Eb6S2MZ/Deu/M+yvxhfC7NXli+tNQFxrNU94fPV2WB2v2aP6wg31KNtbiWvYa0VdYKlot3+ttyG5kzWF56FtudK98rC9Oe86NphyIyg1p+J/9KlZmI0My7Y3U5yyO1ayafmPWnt1oOY28P/KksBuZLcXNyxst3eSLMkaxAp/1JMrva/aq8vjxXZgIWkGUeQQFZ+9T/9pKZMrtnZHazrVDdXt+kR7CyZNc3jZP33zCYqnWW9TtUaqfUBWZDcU1OZ85TNlOLM5s07YfkDitAcfenPpB3XDzMkmzn8XYVZB9gjmRtnS7++b1fWD6yp4Uey3ddOsyFzLJag8Hy/kuSHmXb67/+6qzMACtFcVXtojKkZjBTittp0em0zDWsIMUt32SzXVkojOvyNuOZmcwnrATFTXlx7ZWyWJgXWd47XeSaSbDcZNUKFfss8wIrTLbuVExjOee1HNY/SJddMTnL9r9/yPkC474f+RJRS5kTrAzZxTKRo6QuMAu65qa+i2T/gmCqLllz6urvKD9jDz4r3+zZZr++fHtl/WFmFJcyKM8BqSesHMVd6tj8krxvtfu5Xbx5S2YQ5kpx2x6MeC3fdZRDlpmviS8ktYaVpLhCp/YHy5ydM44L995SUOYMVoziKh0rLvkFwFzIGvcqEKQsBOZI1tml/Ull4VqcXZcP8t26AMY1G/iftE6ymzCutc/oIYuUbdFy6OjwcrLsJqwMxY3bXNRU9g+Wl6z36KWyR5k=
*/