/*!
@file
Defines `boost::hana::contains` and `boost::hana::in`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONTAINS_HPP
#define BOOST_HANA_CONTAINS_HPP

#include <boost/hana/fwd/contains.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Key>
    constexpr auto contains_t::operator()(Xs&& xs, Key&& key) const {
        using S = typename hana::tag_of<Xs>::type;
        using Contains = BOOST_HANA_DISPATCH_IF(contains_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::contains(xs, key) requires 'xs' to be a Searchable");
    #endif

        return Contains::apply(static_cast<Xs&&>(xs),
                               static_cast<Key&&>(key));
    }
    //! @endcond

    template <typename S, bool condition>
    struct contains_impl<S, when<condition>> : default_ {
        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            return hana::any_of(static_cast<Xs&&>(xs),
                    hana::equal.to(static_cast<X&&>(x)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONTAINS_HPP

/* contains.hpp
dQKh+oBxqB+uD5iCY+E6gXIcu7KU9QIMBoPBYDAYDEa8+T/+B/2v9gfz/6TQ9/Ij8v/zbchlTPT71VrYtH3avtXK+DTFfrlDDM7hMEaCYeBvuQtjnbe8ss7pcpTXOmiAiE/uc6uu0aMUtV6lirKaUb1AveykMWKy5fWjR9Goa11jx5wgKvh99i57w+fl1f7wudr8tVocxP5pgnfnPZcATj28Xuxy4m+oVc4gjr+edA2ZCkni+I0/SC5utaK1Op8z0GC116jYQd/u8cx2qqJdU9oirUyx6g94fGqxvV7Y83F8iX5cOBecDdeGOl+I/b0CaYPkjncdd5ijwfrYpSOf9J68+e5nrwfnPkYcH9s89OCldyetVNbNNK8eWfezokySx9/IuWbbIef4fnr5jjWWy7+Yf7OiXC6PP9e+K6t10ZGzF44vGTHHuuAKcEb00VIKbsmci8FgMBgMBoPBYDD+lUhGmtHL/N9eM9sfmC3Y/3+S+9c6/faQmYZz/9ww7n8Ccf8VxP2n0nmfStw/Vef+WnM4Q6a0idoxu/+kXJkv1vOjckN4/TLJxz+6YOOc9FMK2iqWJl177aKj7+pdXj90mkkZM415PYPBYDAYDAaDwWDsz0hGquxl/l9dZ/M5ZAQAW8Bes/d6gBf/9XqA0BmH6wPMzaH6gLNIH/Ay6QMSFZKkD1i4W9MHhLZqddptLpfV7fGG2/a/ltw9Ie2W+18668bsowoumXJ4VcLi3tUBBMD/F7AOgMFgMBgMBoPBYDD2W8TD/7/aX2NzO8DeBfXfB/H/dhze8S5/gMj0MJqbGWkI3jm/cgvF/zunZLI2uHzhXy9j9H2cKV6VnlRvVzEAj7tYtXt8DkWL0Xdugl63n4zrl0tx/ZL6yDr+AMLvOf01qu9sn61W7ahzo6yTIvPnBbUh4vetlf3le3CK6wPUmyhXZJRLkX1NoL4OzxLlC0gPoPqopqwzVa8jz+mMNKFS+A3nQ7z/n9PF+//pFLcPc0fcvrC50+d5kJgnPu88T8T9k+NbK+uHzEXWnYzPMG581nnc0F0Y70O0JGuDmk76jxJx7VBvSeTrhXVR63F38xpobeRQPkF5R+YPjnlORRyFR2XZKcb1W0LXRVy/jfL6GQMrgFqHrp9ebrrsw9tHAfLlGxxyaGfZ/BiejNVYjLLLZdl8pS+tiz/kSyHT3Jc73Y5Cd5VHCVqDn8uyg2S5Q5WOdi+sqvKrAa3cbJR7RJYrlf1nB5WzeHxlNled6N5YN0/JshMxntCy+MOY9xpZJt2o0ybzBxprbSetNSXGWkuNupa0z83R14tYa1KPtlGutZDzbujBmpBqZRyKqW/+ds/m8Vc9eN7csYnXvLI0sedxKHorZmS0+BRDKS6DHoNh/TQtBoPFpsU/VMoQN6FMi5OQC2lBEvEOvJDzkBYhPY30LtLXZVrchm1lWsyG1ItMIXEbhiMvYjrmQSKGgxG/oRR5EcPBC7kQSY/lsAJ/B8dzWI98GxLFdQiL50AxHCiuY4rFpGQgTab4DePwt4jbUARJsRyNmA0uS+eYDfNxrMnCOkYGg8FgMBiMeCI+/J9eW99H/B8kX3KAbUrP48NHjjnXexygp9wjciy36FziE0XjEu2WkLhukk/kTDfhGTw+8d51HjAlcoz34FhuXcV1jxbTncFgMBgMBoPBYDAYvYw48X+fjEXXC/w/Cz70JvDl5n4JShJsrtbOpmolHWW2wjZY1J/KhJqjZRtZaGPXPPjhh7RR5HGKefpj7ykg9AwDzIphtx5DfgZj5Gfg2kino49H5Xv6861Wn83pV41oflUUlQ/9nJF2qrQ9q/ogrF5jFIphf35GtjOc7L96uwfGjOs=
*/