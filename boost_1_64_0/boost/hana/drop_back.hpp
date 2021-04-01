/*!
@file
Defines `boost::hana::drop_back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DROP_BACK_HPP
#define BOOST_HANA_DROP_BACK_HPP

#include <boost/hana/fwd/drop_back.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr auto drop_back_t::operator()(Xs&& xs, N const& n) const {
        using S = typename hana::tag_of<Xs>::type;
        using DropBack = BOOST_HANA_DISPATCH_IF(drop_back_impl<S>,
            hana::Sequence<S>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::drop_back(xs, n) requires 'xs' to be a Sequence");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::drop_back(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        static_assert(N::value >= 0,
        "hana::drop_back(xs, n) requires 'n' to be non-negative");

        return DropBack::apply(static_cast<Xs&&>(xs), n);
    }

    template <typename Xs>
    constexpr auto drop_back_t::operator()(Xs&& xs) const {
        return (*this)(static_cast<Xs&&>(xs), hana::size_c<1>);
    }
    //! @endcond

    template <typename S, bool condition>
    struct drop_back_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...n>
        static constexpr auto drop_back_helper(Xs&& xs, std::index_sequence<n...>) {
            return hana::make<S>(hana::at_c<n>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            return drop_back_helper(static_cast<Xs&&>(xs),
                                    std::make_index_sequence<(n > len ? 0 : len - n)>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DROP_BACK_HPP

/* drop_back.hpp
s4IX+lC9KZfN6/7YIksjqwev7ndOt9Vtsn+x6pQ20S+h1qzT4nIo76D0RroviuEoUmzZ2a1TG4jZ8xwvvFw99iTdZZ+OZzxiIXJLGursdyk7I2yxnS6ly4T6StrvDH3lrFy7+FITW7BZIdQ9rLZ2AQpoS3MHMx4stf1nRLV1KhzNX4gOfT8TqCaPbO1YCl+tRy7ya3WnIeOywmB/rNwkiDWAhbFMzXewh2Oo/w/4prGYw52oQpOybU9e0IiyVqo85u5ipm5SJPIZxQerREdgFuDimOgea9nn1Nvg36Z6C9wHcEJW0kyHyFCkGEr5cadGqyphOyajSEyR3RIalp1y4Mmwnb5Atz4R2BlMDWKTLi/Lef72CH8R3GnOrxKAoU1eIDSuKGbRrawVq39b4nPg1KmYZf9Gbz1MWag/M6aJj+6m+jkhzzM3zVuJ4gysJmiyW62K+Pps9mQqJ+Ky94iHFmocQ7VFI9HJgWn5GTw/HevMMbtv5oPHuj0sc4zQykEecnri6Y4674FvKs0T7VxiZBmSOUKjS2vieeUOq39LkyoYFc7yoQ5yoJe5lA==
*/