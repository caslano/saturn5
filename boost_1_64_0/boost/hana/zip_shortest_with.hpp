/*!
@file
Defines `boost::hana::zip_shortest_with`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZIP_SHORTEST_WITH_HPP
#define BOOST_HANA_ZIP_SHORTEST_WITH_HPP

#include <boost/hana/fwd/zip_shortest_with.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/algorithm.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/take_front.hpp>
#include <boost/hana/zip_with.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename F, typename Xs, typename ...Ys>
    constexpr auto
    zip_shortest_with_t::operator()(F&& f, Xs&& xs, Ys&& ...ys) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(detail::fast_and<
            hana::Sequence<Xs>::value, hana::Sequence<Ys>::value...
        >::value,
        "hana::zip_shortest_with(f, xs, ys...) requires 'xs' and 'ys...' to be Sequences");
    #endif

        return zip_shortest_with_impl<typename hana::tag_of<Xs>::type>::apply(
            static_cast<F&&>(f),
            static_cast<Xs&&>(xs),
            static_cast<Ys&&>(ys)...
        );
    }
    //! @endcond

    template <typename S, bool condition>
    struct zip_shortest_with_impl<S, when<condition>> : default_ {
        template <typename F, typename ...Xs>
        static constexpr decltype(auto) apply(F&& f, Xs&& ...xs) {
            constexpr std::size_t lengths[] = {
                decltype(hana::length(xs))::value...
            };
            constexpr std::size_t min_len =
                *detail::min_element(lengths, lengths + sizeof...(xs));
            return hana::zip_with(static_cast<F&&>(f),
                hana::take_front(static_cast<Xs&&>(xs), hana::size_c<min_len>)...
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZIP_SHORTEST_WITH_HPP

/* zip_shortest_with.hpp
jH6E8GVGRlyM7lIrB3qdsgKpZEyi/Muyf+3vIAdze4MYc/GHXI35MI6NYsbvH+e8hPo2xBzquRh+xyM9v5iLjH9Yo9yxtd8rBu6yqJ+0yii5my/GuOmJME51iuRXSuDn5uuZmAzjIhEVeVQS+JmGzBid4fSLCYYtvCmXdUUWb6YfHvcNRBf5feZ2KEO3Efj8eDx0AdZZF58rrizRB9Vc1pK9fWNw8o2liTE4Llr6pMm1IFfxQsVxV2LjsOBib+nQ6YpD8xG5r2wM6Nir2XRr0cY+h+PN3rvZXuXfu0vZWnFlcbFWza8Uz9Sy6Wpa+LDdeATzKyyVlstVdW2cKRdKVXpi8w2VmdqLZxQGZT8iLrtG9PRCtjCosExWcN/DmPdGH7vFkkjCBvb3VOpRxIvOdA2VrIdcTDkkC/t9TW/T+yX1i/RAU7SZwHnrG4Le6ihiEzn7m4cewbS1+kXlA7Sq6v9IpR/+/qjUIxyeOmKNyj146Elj6/WYQynqV/V9gfws0mfThUVWLZVKjnrJ0B8Zor9kBvRHuXT6F+XUBH1PiD4T1W84tl+YHu4XTbP7hXiSte659G5MKXc2V6zyCAkBIJ5EfxHokhTRXkA0j6Rps+q7jEtVsvSsyJ5Af/PhscA43v9QJJv9YaPWrtfjNxnk7+98J35PfTj+fSjw++TvhD+m5eHEA5aHcjXKskBvInFsNOi9mF5t9bfalEkMtgNFn/oX09dH9X5Texm2G9HZl/v8KSe8NuB3pw343W4D8HYbFJ7kZZJ+36Prv7iYO52mRK5PpL5vUN+ny/yuXk7V5fH020fot80mhWgMo///FcqtUyudXTir6W2in14pZA3+EwqvPzimx+y/9Ff1+wv09z8C9GB/3f0z9xdZHOjUSHdfA/3wWtRfBw5Nqb3h11Q7T2yr5X9waSv1bM17g3i/mr4dtMgRkBJ26f5ukCmlzfKvy5iIymA3jro62K22wHva4f0UzbtJvF+VqhHLC4PhBVpfNa8r/xbj22wPevVhYyMaYkoI1gPfyRvhOg+J7xuSv0c5n/1T1C+nK3m6j9ls9TOqbZnu1la3w/1HY/3NZyrdk9tutHhRUddk7c6oVSE3jsaG6j8as+8Q5lwlfTZXW1guL6WrKf37t+l32jpnlrM5vW2iNtLv36PfS+XqYm2lkivTZmk5k6tUapwdNFelfbb5/vsKV8rN1xazZa3HlZyxvlxcLp5Wfyn9248Iu0h+ZtHT9tFvP1bfZ5aLVXp12OiHn9FvuXOZXKmqnoEn78lqoZiT7VhaqnFT0uVcmpYhJZM/1/VIad31C/X/V4pvKBSztTyVuUxv6fN2T9fl4b2KrtzdStWy/u1X9I3+RPUH1+U33A8rRd53LKwUM6pOup6/VbTTlVo+Xcwu5tB8Lv+bVhuyhUppuVLQ3x4n+u+JHqqe6Ztn63lYKlVq9GkVQ1AoFqqiT1Tb1duMS+T6k9b1+qOql9+B3H//Ef3COYr1N3uOW32eyyyXsynTV8pBhHZ0PQrmHWr8UwlfUs1KVzN5arseQqb9BOXbzI4J/f5KT6ZTmBvbjwTdl3mZ10GtZ2Le6xmvY3u2yORGWNKRD+8Se0xjr4axmJO3/iJ1FWDQWDi3iz1RebiZqfeGRFfTk+xE0v/Yxi2yCXhh1GGnqFyHDLHC/9rGnm33h6P65krnHVG87RBvLwjcSmeD+7EJFbFAERuRbdPgZwWetm2Jn2AvLfCnW8PMqN+nPixFT3kL29b5FHCx4jcwwqFPeT0tDDSp219ocW7Okn4wxOC+bNaJenvQcrue59YBkmWV903tZ2hyogHk/cAuPTTOhPmrktEDGqOHRCOYx3Hi8eD9pLs=
*/