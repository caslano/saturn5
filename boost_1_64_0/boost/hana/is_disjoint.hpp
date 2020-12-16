/*!
@file
Defines `boost::hana::is_disjoint`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_IS_DISJOINT_HPP
#define BOOST_HANA_IS_DISJOINT_HPP

#include <boost/hana/fwd/is_disjoint.hpp>

#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/contains.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/none_of.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto is_disjoint_t::operator()(Xs&& xs, Ys&& ys) const {
        using S1 = typename hana::tag_of<Xs>::type;
        using S2 = typename hana::tag_of<Ys>::type;
        using IsDisjoint = BOOST_HANA_DISPATCH_IF(
            decltype(is_disjoint_impl<S1, S2>{}),
            hana::Searchable<S1>::value &&
            hana::Searchable<S2>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S1>::value,
        "hana::is_disjoint(xs, ys) requires 'xs' to be Searchable");

        static_assert(hana::Searchable<S2>::value,
        "hana::is_disjoint(xs, ys) requires 'ys' to be Searchable");
    #endif

        return IsDisjoint::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    namespace detail {
        template <typename Ys>
        struct in_by_reference {
            Ys const& ys;
            template <typename X>
            constexpr auto operator()(X const& x) const
            { return hana::contains(ys, x); }
        };
    }

    template <typename S1, typename S2, bool condition>
    struct is_disjoint_impl<S1, S2, when<condition>> : default_ {
        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs const& xs, Ys const& ys) {
            return hana::none_of(xs, detail::in_by_reference<Ys>{ys});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_IS_DISJOINT_HPP

/* is_disjoint.hpp
jpUW1UYjtedi7edU3qCL8Z2bGo8ePtPUEWu5puVMQ6wpKKgwUe/cgXprigvraktqqyJnWjvie+/V21kU5F86UG9VpKq6tq6mtLQqUtza1NCh2tbWpIrbz3W0t3Ua851iHhiUsZlcxsOixyoLKypKq+N1NnUFNR5N9DP0jKS8xUWR2pKiurLy8qKk+g7277Ayms52trSd7UzuZ05yOQXFVUXF5bXF1ZGGxsYD/exI1FtwoN6ySLS8pLK2orokciKe/YIqLaidAb+25fqms/FeR/bm9XRyOVdU6Gp5xbFovN6Opqc0nUlUfCZRb/uBessjNeXRwqrKiqrI8Xj2/1fxfr1DB/pbXVJVHq2qqo10NsUaWlsaggmJ34ok1lNy/qKySFXlsWO1FcXRyFVNF1a6X4D9E3Oa4sne/vkVx6q122psbDi/V9c1ieNmJrmuaFWkrq6kqrKsuDJS3nbD0cOtbWevtYRaTKy5bG/pOH/0cNs1qnW4tlx7tqnxwDEb6k7up6GtrKsss5aam848telsY6Lu1sT4pnUn110eKaspqis5Fq2OFMf3OHr4huYmZwaj6r+7/Q5aET9xtERCieOgvDt5vMojpXV11aV1JdFISVeLXS6T+RoNbjuad/Sw/8efnG2LHTwOUiaSxuzh1ceKjtUVl1VF4r18atP5eN79+k4fqK8iUlpjOVaV1Zmf1nhF9kk094aWWLPh6rh2t4T9serqTl6LReWVJbXFlSWRrsN5V8TaOpqetpt//xjo6z54DFSUFNZVlkYr988xySujpU0LlOIUGzNjCrpf4pzx0aR+PrSsvKq08FhFRWSvxsS6mDgwN4WRimPFhcU1JRWRirOqM4idF1TZtF+hMVbjfp0F70uq8/JjVYWFZVWKLC7crfJwos6VA310GovWHiusLak0rrFgEdjnQJ2qum7nHHC1RJXuzWfqM5PKOlxXa3yri4rUuTeboeKaIG9Gct5oUaSosqy0trawOHIiUaWdDlZVV1K9c8Rf12AdRat26748KK8uuby6SFVtWa0rQrnKz3Q0aXVnU0dLQ+vB8T5tn/2+10Uqiiuri8sKo5Hi+C5q3N3Jyj133dXxY+Kaltam+Fomtlv94cTaGnjmgetIVWFZdXVxqeqTK/aX1In2jiTnr45UFdcU1tUUVhv23SpVlbhWXZeoY2UlaU5NVWlteVF1ZTR+UqtPriZxTttIzl9UGqmLHispLrbyrrqgX7G2o4fPdTZdeE4LXZ18TiuuqNan6rJIbO8qpW2JY2XiwFhGI0VVhdZbNHErYCFdsHBbHC3xknTVsRJJrNv25yTVeVlZaXlxXZE6i4MKY3vXYfXt98114lhtUXFt5d69h3sGy0idbY0qi6+a/fNwon8FJcnnn5KSumPVFUWFEY3aH/1E/zYu6N+x0mhdYWVRbaRU1sQ556QzyWMfmnwJjo+tg3b/urQRTZ5DS664uK6qsjiyv8vBNZpxY3K9hZHK8qoafXXeczWUXd862q6L9/PsNS3XeqY5F0zo4UR/J7qS+1tbVez0IsPZhuua2tpjB/s7JW/yfUe02JKuqS2PPLaho6XtXOcFs6kM/1VK4r5jb4y1f7/O4qqyimiN63B853+rMyJvcp2Vrr9FJdGq/1JnzJgdqHPvPja5nCtKy45VVdWUVu5eE5vb9m52rknU25Wcv6guUlJ0rNrVu273mnhBrc4+CtKWvZL27zmUkzS3ZZVFhbUV5aXBxfi6hpYLzj9jF8xtTVFhdWVFXdX/rjepoND+3M4dGOfy2tLS2rqy6G7VLe0Hx3nhgnGuihaXVde6gf+f9ba0x2/aVBrZu49NLudhxUVlpaWV1fFrTPxw26k=
*/