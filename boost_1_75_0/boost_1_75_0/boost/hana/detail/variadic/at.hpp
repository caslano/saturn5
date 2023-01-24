/*!
@file
Defines `boost::hana::detail::variadic::at`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_AT_HPP
#define BOOST_HANA_DETAIL_VARIADIC_AT_HPP

#include <boost/hana/config.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    template <std::size_t n, typename = std::make_index_sequence<n>>
    struct at_type;

    template <std::size_t n, std::size_t ...ignore>
    struct at_type<n, std::index_sequence<ignore...>> {
    private:
        template <typename Nth>
        static constexpr auto go(decltype(ignore, (void*)0)..., Nth nth, ...)
        { return nth; }

    public:
        template <typename ...Xs>
        constexpr auto operator()(Xs ...xs) const
        { return *go(&xs...); }
    };

    template <std::size_t n>
    constexpr at_type<n> at{};
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_AT_HPP

/* at.hpp
0AHf4ZtkI259NiTWJy2lW5eD9LDXgwuZq5Q0TbCjwT4ITDu+Ac9t8m8uzPSaFibzr0F4UvNS0DX0K/FyVe1tOmZ8rCFRiWF0hM9Q6G8RKXqGwSzmCkETzsPt6XhFcRFMfgyOvNrb7vaeRRTnQmeYTMvxcv6V+trcabyJfP1/WHsX+Ciq63F8dnc22byYBRIIGiCUoNiIjSwgYUESZUO0xO/GyC5RA7bVNF3t/6swAz4IJJ2sZjNOa6u09uujWrXFr7ZiFQQruJtAHkhDAKuJEAka9cZBXRCTDYTd3zn3zj4C2Nrf/+dHsnfu49xzX+eee+4552ppEGU72NAhPOaIHCBaWinUzbcm37o0glb5J+jL63ZqtmWBuq9cmCLOAuZgOuQyAf7CriTYTO16w0oSWhYxlQysQ4dQFBwH3wNz0UKkLB14EEDXJE/jKKajdDLqkRQsXo3aOIvc+P5iWbrtoNI2JAEtWpMhvFJmDXxqzA/bh9dhlkkqfyUw1GTGpWgrpATJkbFUL0BpjWnXVA0k4xpYxAGR4kSTzd/icpP3r4KTy2Y728EkM9Sjfd9FkGxUUpNt+B7n3IFFnktH4lYPfKctAotsPRqHuoiEP2j0GFNnw4cULIDpUFOylr1wkWi4RulUK2PKDO+UmGhPSv3qNQYP7yRrLolN25/7qka0G5X9iboPdYsXoYWPIyRehe1zYO4gUk2xwA1UwUX+
*/