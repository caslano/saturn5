/*!
@file
Defines `boost::hana::make`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_MAKE_HPP
#define BOOST_HANA_CORE_MAKE_HPP

#include <boost/hana/fwd/core/make.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Datatype, typename>
    struct make_impl : make_impl<Datatype, when<true>> { };
    //! @endcond

    template <typename Datatype, bool condition>
    struct make_impl<Datatype, when<condition>> : default_ {
        template <typename ...X>
        static constexpr auto make_helper(int, X&& ...x)
            -> decltype(Datatype(static_cast<X&&>(x)...))
        { return Datatype(static_cast<X&&>(x)...); }

        template <typename ...X>
        static constexpr auto make_helper(long, X&& ...) {
            static_assert((sizeof...(X), false),
            "there exists no constructor for the given data type");
        }

        template <typename ...X>
        static constexpr decltype(auto) apply(X&& ...x)
        { return make_helper(int{}, static_cast<X&&>(x)...); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_MAKE_HPP

/* make.hpp
b90qbO0e9hd5lrAoZIdvfGVMCEYEnvNB3wWoPX47r+ONVQfnP1E9wfv6O10e/YA8CGUxO3DxyFUmHrQbMpEZPKY6pF0EFJj4rvoWCjvZ28vOVUwhqgWmeHjMKtnuzw9KvJrakT4twqVkS5r1GauIp68e6aHbHlvYa5/fGmC+urc/o7cblSLEHLbJAlikdv5FbUYV3SAiLHnbWVGuBVB6mMZ4edUwu4q7hQK+LpfC9VJGt7q19KtaGhHHy+NdU2+LJs6Nj/1pcf1APCBXMs/pdriT+7G83yohDhxGL9keyhjVyXWHhtkeBlSN1QwFqPcbmIFZM5RkWKn5LG0E2MsPAKV9xh2tQuqW8KgOLL6JG3N3LWpcVwYQKf0rjX8P2vGiY3TaoFezUf9G6CyRh7mzQemBLeG3bDO5vhJfXyWXKuAuyunaP9z/X5yNrNkbBz8n/QjD3Yda6CWXb2zvDVtavXp3Ke3ww15ymIrdqyubx6sllZs0IbOvzxBSr6Bsjp9yUSZ0qVy+HbcG1+ip3MoPJ7xPoT83AgceSPBPi++OgK0FfTHnie8hC0kzRg==
*/