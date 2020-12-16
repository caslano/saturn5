/*!
@file
Defines `boost::hana::detail::variadic::drop_into`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_DROP_INTO_HPP
#define BOOST_HANA_DETAIL_VARIADIC_DROP_INTO_HPP

#include <boost/hana/config.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    template <std::size_t n, typename F, typename = std::make_index_sequence<n>>
    struct dropper;

    template <std::size_t n, typename F, std::size_t ...ignore>
    struct dropper<n, F, std::index_sequence<ignore...>> {
        F f;

        template <typename ...Rest>
        constexpr auto go(decltype(ignore, (void*)0)..., Rest ...rest) const
        { return f(*rest...); }

        template <typename ...Xs>
        constexpr auto operator()(Xs ...xs) const
        { return go(&xs...); }
    };

    template <std::size_t n>
    struct make_dropper {
        template <typename F>
        constexpr auto operator()(F f) const
        { return dropper<n, decltype(f)>{f}; }
    };

    template <std::size_t n>
    constexpr make_dropper<n> drop_into{};
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_DROP_INTO_HPP

/* drop_into.hpp
0uyRCs0uYzQr844imj2a5nwK0eAyRoN9gPdjkPbqoaSjZYzW5Ph9oKFjGQ2l/JfG/7Vu01h+tKOuVQbmJxorjBVGgq2tDkwHrHJGmRV838yw/YFDSoYJTxOhGaEF9aG4AaS4jBLW1hxrZDA/+54y7XbzWB5VZucts/tJOaxtoVl5VCPP84WmRWL1wQhl8bGIFMorwtVj1keRFmIYobLpTt+qgnHcbUGCf5NDw1Eyjby8UFlR+YxYY3uE4wwX9cUyzEYs2rEg1s7wn7JMyHmpxTTj8Qg3HHNTF0WkdbsegqeIUDGeO6DxOXDMS1GoCU+Y1wbnqt9gfmqM6PRmhg3HHJXHGoIRtTzmpyoeA7G1dajtyPkplhxP/QZzUxvC0wNgqvSNK48jxYHrobJIJDTX6gHB5XzlyzAfzfFYFAhT6vv9iKkGbQPVVN8K8MSdiScelyRPbMenzuKitMUPKZEnf3dxBR6+2byQGuNsYDPaN/yCiP9ZPE+mVxDPg/3Q+DeJeN7xgFtjlzzvRKSVnthxKMANjZj3hxO/O6nL/G7LjFHG0jB5WhC30dukNkr8DO8xIAiJIzeb4iGL3vCeRntbPBixbXD1MfkG0yLQTjeinVO8aKetOR4KNqJeu48MZhEMA+SpH3jrcfXJ0YlaGSEtuTYkLZymyMJTmSyUeacTXZxBc6nkeepvZ5L+dpbcqxIdyXo5WqS+djaHKfSE8jY9SVykgJ7O4fS0hXHB9hwhOMGRTJRRbBaHGi0+jfTiYAf2P+49x3ledBGci1g7cyFQ6iObUKtYyS2i2yv1MVQk2xLp9hcotHE+ow2ZdyHRxkU0L0qeJ21cTLRxiU0bZr3Aha3HX4o076qqx5/PdKt5RBsrOW38SThZlNw+Mx5qCIVBQ8nsNJWy3vMeTW7e1Rr5KJNvjeb+cpp7y75wGdI5bI5l/hXGHOvib4R7ohOUVcoRnVxF5dQ8TieDiE6uJDq5mn5fg98HE72gfkYv8CtEOtHgjffhlX1fjkEjkWAHwiwFGkMtoWgjPjbxnApauo7RUtqfiOcDbDnVGInYPCa0JER/+4z32mB4tc+K2qOwNjSEm8KMJxXPLrbLyyD+ZYUy3STfkyNavcGLVmFuad8UZ1LKeNHmwcnRJtXkwtWmaydavIlo0bJ73oi06ruDOaW/FTj9EMymPVnnzQbt9Ra3KPSL+j3KaeI2KqfkedLvrUS3t9PvO/C7XjPp90aFflchTchw0e2NCt2i/6BHhLNi6XSxyHkLimB4H7IdDvDsHchIA6UlLnAeJCPGxWMR9s0IITUrPFIFQcnjDuYwuBV6zvpmAssDBdvwPAOOx9JCTh9KDZhVw9d2X8pFc7ixkWKvEWyGiIdkrQ1tIHPArXqrREM73o1bwGGzUdY0rgQMxEh67Ic1fCdbw3O2ID1K+2qcnQ8st/WG4iUNoRbraaxwtD1UvARxpSTAtl9uXKYmFIw3NNtr2c6vCLVi8HZS0Ppm3yOkAsytdVE8TyZ5QYm0+5Ct9R70D0e3hcXm4Y18JRKx1OXf5ur2ziMblOu9NAqXBTjB5AlFcEl4QfsCypLwhUYcrYL2pqZQXJadRPGx/s7mIF3AmaysEDHhcRhovWBZp8DQhZHe/GQGHHbyjU/MP+04dPdlsvikLC3UeKrIn6fxsRWaa2BWLN4o+PhqjKsmEmzHEjTkBTbOVNaCdRPVIeNFTby3aH2fKorla5mVIPXGEJXNAjyN4E1NraE21l4vE14TioQaEHjMrmc7u+5cQXUAh9JAQVWwOckw4HYVNry/XcdY9lbdjCWFrXE7PdhMB2YEW+3YqffjY78wTIzVobl4JhEcxsp7AHkrxewFC5w=
*/