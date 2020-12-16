/*!
@file
Defines `boost::hana::at_key`.

@copyright Louis Dionne 2013-2017
@copyright Jason Rice 2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_AT_KEY_HPP
#define BOOST_HANA_AT_KEY_HPP

#include <boost/hana/fwd/at_key.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/at.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/find.hpp>
#include <boost/hana/find_if.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/functional/on.hpp>
#include <boost/hana/index_if.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/second.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Key>
    constexpr decltype(auto) at_key_t::operator()(Xs&& xs, Key const& key) const {
        using S = typename hana::tag_of<Xs>::type;
        using AtKey = BOOST_HANA_DISPATCH_IF(at_key_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::at_key(xs, key) requires 'xs' to be Searchable");
    #endif

        return AtKey::apply(static_cast<Xs&&>(xs), key);
    }
    //! @endcond

    template <typename S, bool condition>
    struct at_key_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Key>
        static constexpr auto apply(Xs&& xs, Key const& key) {
            return hana::find(static_cast<Xs&&>(xs), key).value();
        }
    };

    namespace at_key_detail {
        template <typename T>
        struct equal_to {
            T const& t;
            template <typename U>
            constexpr auto operator()(U const& u) const {
                return hana::equal(t, u);
            }
        };
    }

    template <typename S>
    struct at_key_impl<S, when<hana::Sequence<S>::value>> {
        template <typename Xs, typename Key>
        static constexpr decltype(auto) apply(Xs&& xs, Key const& key) {
            using Result = decltype(hana::index_if(
                static_cast<Xs&&>(xs), at_key_detail::equal_to<Key>{key}));

            return hana::at(static_cast<Xs&&>(xs), Result{}.value());
        }
    };

    template <typename S>
    struct at_key_impl<S, when<hana::Struct<S>::value>> {
        template <typename X, typename Key>
        static constexpr decltype(auto) apply(X&& x, Key const& key) {
            auto accessor = hana::second(*hana::find_if(hana::accessors<S>(),
                hana::equal.to(key) ^hana::on^ hana::first
            ));
            return accessor(static_cast<X&&>(x));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_AT_KEY_HPP

/* at_key.hpp
Dj6nvhSjFpffOgzbJAxxUcNgbphq2xjv8NHybt65w+DibNsyq8MwUrf3JQxdzxkGda4+R7EscFtd5pn7n18v41TnDEeqLfXMP3g7z6jWiiCO23vvXez1eBBR0cPxSImCICDBXmJILhANSSRBsWPH3nvvvff+7L3zFBUBERV773Vz73+WW/bGLzP6xacn7/x2ts7dmf3PFn7t/9JtEDlzdP0T0t8v3QaR82cTXw2AvydKtkGEXb8talG+G8pWgQBeu3X9U7C3Du/7tKpA059j7ndd/wL6+3d8FsrvtpzLJbH59zLacFPJNpQXr/TYv102oX6oReyrdBtE2E+D/W34/FOfbTLnYkMdfJLw+aecBAT9mHPntf4t2jDmsT/a0doesQ8CXf+JeeyJ31CPPNxhIx8LMJboS/PGPPX4g3/KZwY+HALunFE9/hG8Wwhh041nLl7o4W6Dth9tGDGPP8r/8LLXJX9oO+R+G8ZebfqsTJpvD4A5NBVk2uVfqO4Lc24yfXOVQzd/MGizyP2Q/v4B9xQDV20yWGe8bP3+twF5f1NmtlrcrFwa62vA/dKwvpRqv9j6Jv7apNtfgq+iGexn+9Y05uCfFc4vd75+raRKrlVFQnjbob9/oad/Wal2qEnAPQ46/xP89d838tn3GlpzZU34xgnhKol3sbG/Qf2X/d8h7G7LvnVQEUQE6Jlze6gd5c3IA/0svB2Z/t5YfwYTUag/HkA77hgOb4c1kCtmVxUch4v3TpXO/Oodkes+FdYOZLvb1wC8ubk6/oU2TL1bug3ceeA0FvWkx19iLFQBNFVrXmZ/1N9/aMfQh6Ht2FRd/8ZTzPnD1A/Nrfj2Cu+Hcp0CKOAb6PqnaMcFn5VqR9wZj8IAaxt0/c823IOY9ysR34j80FlgX+SdB43b25bLMCvVYwebPeljCsQmaZwfAHMFz7pvj+zS2hSpF87hpjm/bTvqvIa2oc86EC54fbzAPuYbUl+gHVeMGNohkHtKe05VFBotJvvtmICd2JOqYM4B1fp/4O/js3sn4TdH63dgr/vIxxV6E7IJ+X7gPu/nCr7T0P7/zniz6O/r/+mtxhXgf+3nC76ZoPFeYRfoUPj7XegNAe2rp4Bb/a6PK/COgJhz7Ao/wt/PgvvIIJiTfqZwzi34iofvi9kmvtrCrExxZbHH0mhuHwb+j377BfOoaLy/Bfs0P1vg7Kb+zu0ObU3/vBbOBSH+t+AP+9ezc2bFC4W+4rdkYYD5O1Lbvwd0kkrzWxrrefm6/iP4zeQjIh20va01GkFVQKm53rMn3k58ZmZL5B9Tv0+DvV2Y3fYNgtw+07MXxj3MdpUvKhmbmgL/+XB+Js6cN0Fn6F57472Oqe8Fvk3I5hFwH5vt4bY2N9btHmtprY8InKXE7tgHMTH3dyC035zuLv4PXrt1/hfYq5jYamvnftOg458xvEOkOaa1zrWzFOsSupufBfa2s8PYvN/7xK3aF30d5GYzVjqVYd5PtP4puH8P+7n8eQY6/qF+Yfss7/uZMu//ydYLwD0wwOV/90/79Qqdzq9b3vUxcUhmktYAnq2I8C8Av6EEH44CK5/W8jIJaA2a+Za65mb/5tL6r2DPE1hT/DkM+v1b0vl1bdBe29aia8L9bljrH4F92EiAneSOZWr9AzD3CNpLie/KbBkfvGAhX+CjAFs5wQ7YccJ5z2bi/wj+drPD+ZJrK9fl/Hrfd018mbWlv3/A7gqyIy0d7bur1S2aQ5zrRm3wUvxkvBBntl9//4B/zoiZL+kf9fQgju05s5tbW5t2bnNO0GSKO1ZFZ/cE2BeY2F2pNLfNxN0thZi5iZso9HHngtKe+jK4y7nXuK3uyX8=
*/